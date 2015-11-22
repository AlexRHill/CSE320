
/******************************************************************************
  Project #4 skeleton
******************************************************************************/

#include <Sim.h>

void circuits( SD, Signal, Signal, Signal, Signal, Signal, Signal );


/******************************************************************************
  Function "simnet"   -- test bed for student circuits
******************************************************************************/

void simnet()
{
  Signal Init, Clock, w, x, y, z;
  

  // Insert your Pulsers here
  
  Pulser ((SD("1a"), "c - Clock"),  Clock, 'c', 10000);
  Pulser ((SD("2a"), "i - Init"), Init, 'i', 10000);


  circuits( SD("5b-8b"), Init, Clock, w, x, y, z );

  // Insert your Probes here
  Probe ((SD("2d"), "w"), w);
  Probe ((SD("3d"), "x"), x);
  Probe ((SD("4d"), "y"), y);
  Probe ((SD("5d"), "z"), z);

}


/******************************************************************************
  Function "circuits" -- implementation of student circuits
******************************************************************************/

void circuits( SD sd, Signal Init, Signal Clock, 
  Signal w, Signal x, Signal y, Signal z )
{
  Module( (sd, "circuits"), (Init, Clock), (w, x, y, z) );

  // Insert your declarations for any auxiliary Signals here
  
  Signal W, X, Y, Z;

  // Insert your DFFs here
  
  Dff( SD("1b"), ( Init, W, Clock, Zero ), w );
  Dff( SD("2b"), ( Zero, X, Clock, Init ), x );
  Dff( SD("3b"), ( Init, Y, Clock, Zero ), y );
  Dff( SD("4b"), ( Zero, Z, Clock, Init ), z );

  // Insert your combinational logic here (Not, And, Or gates)
  
  Signal notx, noty, notz;
  Not ( SD(sd,"1d"), x, notx );
  Not ( SD(sd,"2d"), y, noty );
  Not ( SD(sd,"3d"), z, notz );
  
  Signal and1, and2, and3, and4;
  And ( SD(sd,"1e"), (notx, noty), and1 );
  And ( SD(sd,"2e"), (x, notz), and2 );                                        
  And ( SD(sd,"3e"), (w, y), and3 ); 
  And ( SD(sd,"4e"), (noty, notz), and4 );
  
  Or ( SD(sd,"1f"), (and1, and1), W ); 
  Or ( SD(sd,"2f"), (and2, and3), X ); 
  Or ( SD(sd,"3f"), (z, z), Y ); 
  Or ( SD(sd,"4f"), (and4, and4), Z ); 

}
