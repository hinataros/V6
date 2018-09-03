/**
   @author Sho Miyahara 2017
*/

#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readSharedData(RLS::Config &config, RLS::RigidBodyModel &object, RLS::SharedData &sharedData)
{
  if(debug) DEBUG;

  for(int i=0; i<3; i++)
    object.rO(i) = sharedData.root.r[i];

  for(int i=0, j=0, k=0; k<9; k++){
    object.RO(i,j) = sharedData.root.R[k];
    if(j==2){
      i++;
      j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    object.vO(i) = sharedData.root.v[i];
    object.wO(i) = sharedData.root.w[i];
    object.fO(i) = sharedData.root.f[i];
    object.nO(i) = sharedData.root.n[i];
  }
}
