/**
   @author Sho Miyahara 2017
*/

#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readSharedData(RLS::Model &model, const RLS::SharedData &sharedData)
{
  if(debug) DEBUG;

  // for(int i=0; i<3; i++)
  //   model.rigidBodyModel[i].rR(i) = sharedData.root.r[i];

  // for(int i=0, j=0, k=0; k<9; k++){
  //   model.rigidBodyModel[i].RR(i,j) = sharedData.root.R[k];
  //   if(j==2){
  //     i++;
  //     j=0;
  //   }else j++;
  // }

  // for(int i=0; i<3; i++){
  //   model.rigidBodyModel[i].vR(i) = sharedData.root.v[i];
  //   model.rigidBodyModel[i].wR(i) = sharedData.root.w[i];
  //   model.rigidBodyModel[i].fR(i) = sharedData.root.f[i];
  //   model.rigidBodyModel[i].nR(i) = sharedData.root.n[i];
  // }
}
