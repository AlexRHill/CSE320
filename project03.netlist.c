
/******************************************************************************
  Project #3 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, 
  Signal, Signal, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal w, x, y, z, Present, a, b, c, d, e, f, g;

  // Code to generate four input signals
  
  //Switch ( SD("1a"), w, 'w' );         // Switch a controlled by 'w' key
  //Switch ( SD("2a"), x, 'x' );         // Switch a controlled by 'x' key
  //Switch ( SD("3a"), y, 'y' );         // Switch a controlled by 'y' key
  //Switch ( SD("4a"), z, 'z' );         // Switch a controlled by 'z' key
  
  Signal Strobe (1);   // Counter strobe input
  Signal ResetA (1);   // Counter reset signal (before complemented)
  Signal ResetB (1);   // Counter reset signal (after complemented)
  Signal Output (4);   // Counter output

  // A pulser is used to generate a temporary value of "One" on a specified
  // signal line (signal value:  Zero ==> One ==> Zero)

  Pulser ((SD("1a"), "r -- Reset counter"),  ResetA, 'r', 10000);
  Pulser ((SD("2a"), "s -- Strobe counter"), Strobe, 's', 10000);

  // Complement the reset signal (counter reset is active low)

  Not (SD("1b"), ResetA, ResetB);

  Counter ((SD("1c-2c"), "4-bit counter"), (ResetB, Strobe), (w,x,y,z));

  Probe ((SD("1d-2d"), "Output"), (w,x,y,z));

  circuits( SD("1e-4e"), w, x, y, z, Present, a, b, c, d, e, f, g);
  
  // Code to display eight output signals
  
  Probe ( (SD("1g"), "Present"), Present );        // Probe
  Probe ( (SD("2g"), "a"), a );        // Probe
  Probe ( (SD("3h"), "b"), b );        // Probe
  Probe ( (SD("5h"), "c"), c );        // Probe
  Probe ( (SD("6g"), "d"), d );        // Probe
  Probe ( (SD("5f"), "e"), e );        // Probe
  Probe ( (SD("3f"), "f"), f );        // Probe
  Probe ( (SD("4g"), "g"), g );        // Probe

}


/******************************************************************************
  Function "circuits" -- implementation of student circuits

  Do not alter the interface -- function "circuits" must receive four
  signals as inputs and return eight signals as outputs.
******************************************************************************/

void circuits( SD sd, Signal w, Signal x, Signal y, Signal z, 
  Signal Present, Signal a, Signal b, Signal c, Signal d, Signal e,
  Signal f, Signal g )    
{
  Module( (sd, "circuits"), (w, x, y, z), (Present, a, b, c, d, e, f, g) );

  // Declarations for any auxiliary Signals
  Signal notw, notx, noty, notz;
  
  Signal and1, and2, and3, and4, and5, and6;
  
  // Circuit implementation (Not, And, Or gates)
  
  Not ( SD(sd,"1a"), w, notw );           // NOT gates
  Not ( SD(sd,"2a"), x, notx );
  Not ( SD(sd,"3a"), y, noty );
  Not ( SD(sd,"4a"), z, notz );
  
  And ( SD(sd,"1b"), (notw, noty, notz), and1 );
  And ( SD(sd,"2b"), (notw, x, noty), and2 );   // AND gates for Present                                     
  And ( SD(sd,"3b"), (w, notx, noty, z), and3 ); 
  And ( SD(sd,"4b"), (notx, y, notz), and4 );
  
  And ( SD(sd,"5b"), (notw, notx), and5 ); // AND gate for D
  And ( SD(sd,"6b"), (notx, notz), and6 ); // AND gate for E
 
  Or ( SD(sd,"1c"), (and1, and2, and3, and4), Present );    // OR gates
  Or ( SD(sd,"2c"), (notx, z), a );
  Or ( SD(sd,"3c"), (w, notz), b );
  Or ( SD(sd,"4c"), (w, noty), c );
  Or ( SD(sd,"5c"), (and5, z), d );
  Or ( SD(sd,"6c"), (and6, and6), e );
  Or ( SD(sd,"7c"), (w, noty), f );
  Or ( SD(sd,"8c"), (x, y, z), g );





  
  

}
