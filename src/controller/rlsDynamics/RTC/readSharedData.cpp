#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readSharedData(RLS::Config &config, RLS::Info &info, RLS::RigidBodyModel &object, RLS::SharedData &sharedData)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++)
    object.rO(i) = sharedData.rR[i];

  for(int i=0, j=0, k=0; k<9; k++){
    object.RO(i,j) = sharedData.RR[k];
    if(j==2){
      i++;
      j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    object.vO(i) = sharedData.vR[i];
    object.wO(i) = sharedData.wR[i];
    object.fO(i) = sharedData.fR[i];
    object.nO(i) = sharedData.nR[i];
  }
}
