/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::handWrenchControlAndCentroidalEcmpDistribution()
{
  if(debug) DEBUG;

  // (this->*internalForceController_ptr)(info);

  VectorXd cal_FHcBarRef = getControlNodeVector(Bc.transpose()*fb.cal_Ffb,"c","RARMEE");

  MatrixXd bb_CcMH = getControlNodeMatrix(cal_PcM,false,true,"c","RARMEE");
  VectorXd cal_FCextRef = cal_dLCRef + model->cal_GC - bb_CcMH*cal_FHcBarRef;

  MatrixXd bb_CcMF = getControlNodeMatrix(cal_PcM,false,true,"c",2,"RLEGEE","LLEGEE");

  VectorXd cal_FFcBarRef;
  if(info.constraint.c.controlNode[info.model.controlNodeID["RLEGEE"]]==6&&
     info.constraint.c.controlNode[info.model.controlNodeID["LLEGEE"]]==6){
    Vector2d rFr = getControlNodeVector(model->cal_X,"all","RLEGEE").head(2);
    Vector2d rFl = getControlNodeVector(model->cal_X,"all","LLEGEE").head(2);

    Vector2d recmp = (model->rX - des.drXDes/model->wX).head(2);

    MatrixXd WecmpF = h_weight(recmp, rFr, rFl);

    cal_FFcBarRef = pInv(bb_CcMF, WecmpF)*(cal_FCextRef);
  }
  else{
    cal_FFcBarRef = pInv(bb_CcMF)*(cal_FCextRef);
  }

  cal_FcBarRef <<
    cal_FFcBarRef,
    cal_FHcBarRef;
}
