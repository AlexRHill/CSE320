#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sstream>
#include <string>
#include <netdb.h>
#include <algorithm>

#include "message.h"
#include "client.h"

using namespace std;

int main(int argc, char *argv[])
{
    unsigned short udp_port = 0;
    const char* server_host = "127.0.0.1";
    //process input arguments
	if ((argc != 3) && (argc != 5))
	{
		cout << "Usage: " << argv[0];
		cout << " [-s <server_host>] -p <udp_port>" << endl;
		return 1;
	}
	else
	{
		//system("clear");
		for (int i = 1; i < argc; i++)
		{				
			if (strcmp(argv[i], "-p") == 0)
				udp_port = (unsigned short) atoi(argv[++i]);
			else if (strcmp(argv[i], "-s") == 0)
			{
				server_host = argv[++i];
				if (argc == 3)
				{
				    cout << "Usage: " << argv[0];
		            cout << " [-s <server_host>] -p <udp_port>" << endl;
		            return 1;
				}
		    }
	        else
	        {
	            cout << "Usage: " << argv[0];
		        cout << " [-s <server_host>] -p <udp_port>" << endl;
		        return 1;
	        }
		}
	}
	
	int sk ; // socket descriptor
	struct sockaddr_in remote ; // socket address for remote

	// create the socket
	sk = socket(AF_INET,SOCK_DGRAM,0) ;
	
	// set up the socket
	remote.sin_family = AF_INET ; // internet family
	hostent *hp;
	

	// find remote host address
	hp = gethostbyname(server_host);
	memcpy(&remote.sin_addr, hp->h_addr, hp->h_length);
	remote.sin_port = htons(udp_port);
	
	
	Client_State_T client_state = WAITING;
	string in_cmd;
	while(true)
	{
	    usleep(100);
	    switch(client_state)
	    {
	        case WAITING:
	        {
	            cout<<"$ ";
	            cin>>in_cmd;
	            
	            if(in_cmd == "ls")
	            {
	                client_state = PROCESS_LS;
	            }
	            else if(in_cmd == "send")
	            {
	                client_state = PROCESS_SEND;
	            }
	            else if(in_cmd == "remove")
	            {
	                client_state = PROCESS_REMOVE;
	            }
	            else if(in_cmd == "shutdown")
	            {
	                client_state = SHUTDOWN;
	            }
	            else if(in_cmd == "quit")
	            {
	                client_state = QUIT;
	            }
	            else
	            {
	                cout<<" - wrong command."<<endl;
	                client_state = WAITING;
	            }
	            break;
	        }
	        case PROCESS_LS:
	        {
			
				struct CMD_MSG_tag MSG1;
				MSG1.cmd = CMD_LS;
							
				sendto(sk, (char*)&MSG1 , sizeof(MSG1), 0, (struct sockaddr *)&remote, sizeof(remote));
				
				struct CMD_MSG_tag responseMSG;

				int received = 0;
				int remoteSize = sizeof(remote);
				received = recvfrom(sk, (char *)&responseMSG, sizeof(responseMSG), 0, (sockaddr *)&remote, (socklen_t*) &remoteSize);

				if (responseMSG.cmd != CMD_LS)
				{
					cout << " - command response error." << endl;
					return 1;
				}
				
				int sizeS = ntohl(responseMSG.size);
				if (sizeS == 0)
				{
					cout << " - server backup folder is empty." << endl;
				}
				else
				{
					cout << "Number of files: " << sizeS << endl;
					for (int i = 0; i < sizeS; i++)
					{
						DATA_MSG_tag file;
						received = recvfrom(sk, (char *)&file, sizeof(file), 0, (struct sockaddr*)&remote, (socklen_t*) &remoteSize);

						cout << " - " << file.data << endl;
					}
				}
			
		        client_state = WAITING;
	            break;
				
	        }
	        case PROCESS_SEND:
	        {
			
	            string filename;
				cin >> filename;

				struct CMD_MSG_tag sendMSG;
				
				sendMSG.cmd = CMD_SEND;
				strcpy(sendMSG.filename, filename.c_str());
				sendMSG.error = htons(0);

				string path = string("./backup/").append(filename);

				ifstream file(path.c_str(), ios::binary | ios::ate );
				
				if (file)
				{
					//see if the file exists
					sendMSG.size = htonl(file.tellg());
					file.close();
				}
				
				else
				{
					//if the file doesn't exist locally
					cout << " - file with filename, " << filename << ", doesn't exist." << endl;
					client_state = WAITING;
					break;
				}

				sendto(sk, (char *)&sendMSG, sizeof(sendMSG), 0, (struct sockaddr *)&remote, sizeof(remote));

				//response part
				
				struct CMD_MSG_tag responseMSG;
				int received;
				int remoteSize = sizeof(remote);
				
				received = recvfrom(sk, (char *)&responseMSG, sizeof(responseMSG), 0, (struct sockaddr*)&remote, (socklen_t*) &remoteSize);

				if (responseMSG.cmd != CMD_SEND) 
				{
					//if it is a bad response
					cout << " - command response error. " << endl; 
					return 1;
				}
				
				if (ntohs(responseMSG.error) == 2)
				{
					//if the file already exists
					
					while (true) 
					{
						cout << " - the file, " << filename << ", exists. Overwrite? (y/n): ";
						string answer;	
						cin >> answer;

						if (answer == "y" || answer == "Y") 
						{	
							CMD_MSG_tag yesMSG;
							yesMSG.cmd = CMD_SEND;
							yesMSG.error = htons(0);

							sendto(sk, (char *)&yesMSG, sizeof(yesMSG), 0, (struct sockaddr *)&remote, sizeof(remote));
							
							received = recvfrom(sk, (char *)&responseMSG, sizeof(responseMSG), 0, (struct sockaddr*)&remote, (socklen_t*) &remoteSize);
							
							goto TCP;
						}
						else if (answer == "n" || answer == "N")
						{
							CMD_MSG_tag noMSG;
							noMSG.cmd = CMD_SEND;
							noMSG.error = htons(2);

							sendto(sk, (char *)&noMSG, sizeof(noMSG), 0, (struct sockaddr *)&remote, sizeof(remote));
							
							client_state = WAITING;
							goto END;
						}
						else
						{
							cout << " - invalid answer. " << endl;
						}
					}
				}

				TCP:
				if (ntohs(responseMSG.error) == 1 )
				{
					cout << "end" << endl;
					goto END;	
				}
				
				else
				{
					//set up the tcp socket
					int tcpSK;
					struct sockaddr_in tcpRemote;
					tcpSK = socket(AF_INET, SOCK_STREAM, 0);

					tcpRemote.sin_family = AF_INET;
					memcpy(&tcpRemote.sin_addr, hp->h_addr, hp->h_length);
					tcpRemote.sin_port = responseMSG.port;

					if (connect(tcpSK, (struct sockaddr *)&tcpRemote, sizeof(tcpRemote)) < 0) 
					{
						//do the tcp handshake
						cout << " - connection failed." << endl;
						close(tcpSK);
						return 1;
					}

					DATA_MSG_tag fileMSG;

					ifstream fileOpen( path.c_str(), ios::binary );
					if (!fileOpen)
					{
						cout << " - failed to open file, " << filename << "." << endl;
						goto END;
					}

					while (true)
					{
						//write the file
						fileOpen.read(fileMSG.data, sizeof(fileMSG.data));
						write(tcpSK, fileMSG.data, fileOpen.gcount());

						if (fileOpen.eof())
						{
							//done writing
							break;
						}
					}

					received = recvfrom(sk, (char *)&responseMSG, sizeof(responseMSG), 0, (struct sockaddr *)&remote, (socklen_t*) &remoteSize);

					if (responseMSG.cmd == CMD_ACK && responseMSG.error == 0)
					{
						cout << " - file successfully transferred. " << endl;
					}
					
					else
					{
						cout << " - file didn't transfer successfully. " << endl;
					}
					
					close(tcpSK);
					
				}

				END:
		        client_state = WAITING;
		        break;

	        }
			
	        case PROCESS_REMOVE:
	        {	     
				string filename;
				cin >> filename;

				struct CMD_MSG_tag removeMSG;
				struct CMD_MSG_tag responseMSG;

				removeMSG.cmd = CMD_REMOVE;
				strcpy(removeMSG.filename, filename.c_str());

				sendto(sk, (char *)&removeMSG, sizeof(removeMSG), 0, (struct sockaddr *)&remote, sizeof(remote));

				int received = 0;
				int remoteSize = sizeof(remote);
				received = recvfrom(sk, (char *)&responseMSG, sizeof(responseMSG), 0, (struct sockaddr *)&remote, (socklen_t*) &remoteSize);

				if (responseMSG.error)
				{
					//if there's an error
					cout << " - file doesn't exist." << endl;
				}
				else
				{
					if (responseMSG.cmd == CMD_ACK)
					{
						//if this is confirmation that the file was removed
						cout << " - file is removed." << endl;
					}
					else
					{
						cout << " - command response error." << endl;
						return 1;
					}
				}
			
	            client_state = WAITING;
	            break;
	        }	
			
	        case SHUTDOWN:
	        {	          
				struct CMD_MSG_tag shutdownMSG;
				struct CMD_MSG_tag ackMSG;

				shutdownMSG.cmd = CMD_SHUTDOWN;
				
				//now we send the shutdown message
				
				sendto(sk, (char *)&shutdownMSG, sizeof(shutdownMSG), 0, (struct sockaddr *)&remote, sizeof(remote));

				int received = 0;
				int remoteSize = sizeof(remote);
				received = recvfrom(sk, (char *)&ackMSG, sizeof(ackMSG), 0, (struct sockaddr *)&remote, (socklen_t*) &remoteSize);

				if (ackMSG.cmd == CMD_ACK)
				{
					if (ackMSG.error == 0)
					{
						cout << " - server shut down successfully." << endl;
					}
					else if (ackMSG.error == 1)
					{
						cout << " - other transmissions in progress." << endl;
					}
				}
				else
				{
					cout << " - command response error." << endl;
					return 1;
				}
				
				//then we shutdown
				return 0;
			}
	        case QUIT:
	        {	      
				cout << " - you quit." << endl;
				return 0;			
	        }
	        default:
	        {
	        	client_state = WAITING;
	            break;
	        }    
	    }
	}
    return 0;
}
