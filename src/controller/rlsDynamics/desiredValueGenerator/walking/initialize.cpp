/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"


void RLS::Walking::initialize()
{
  if(debug) DEBUG;

  // resize();
  int setVwp = readController(); // amiyata
  resetMat();

  if(setVwp > 0){
    setWayPoint(); // amiyata
    createHTTrajectory();
    if(ToptimF)
      createVRPTrajTopt(); // amiyata
    else
      createVRPTrajectory(); // amiyata
  }
  else
    cout << "No VRP way point..." << endl;

}
