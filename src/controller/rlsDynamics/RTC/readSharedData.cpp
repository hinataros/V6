#include "rlsDynamicsRTC.h"

void RlsDynamicsRTC::readSharedData(RLS::Config &config, RLS::Info &info, RLS::Model &model, RLS::SharedData &sharedData)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++)
    model.rO(i) = sharedData.rR[i];

  for(int i=0, j=0, k=0; k<9; k++){
    model.RO(i,j) = sharedData.RR[k];
    if(j==2){
      i++;
      j=0;
    }else j++;
  }

  for(int i=0; i<3; i++){
    model.vO(i) = sharedData.vR[i];
    model.wO(i) = sharedData.wR[i];
    model.fO(i) = sharedData.fR[i];
    model.nO(i) = sharedData.nR[i];
  }
}
