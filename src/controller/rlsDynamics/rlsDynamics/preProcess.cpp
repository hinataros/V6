/**
   amiyata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"


void RLS::RlsDynamics::preProcess()
{
  if(debug) DEBUG;

  // foot Print record
  for(int i=0; i<info.model.controlNodeNum; i++){
    if(model->cal_F(6*i+2) > 0.) {
      if(contactFlag[i]==false && i < 2){
        struct FootPrint tempFP = {model->r[i], model->R[i], (short)i};
        // FootPrint.pos = model->r[i];
        // FootPrint.att = model->R[i];
        // FootPrint.ee = (short)i;
        extractor.footPrintList.push_back(tempFP);
      }
      contactFlag[i] = true;
    }
    else
      contactFlag[i] = false;
  }
}
