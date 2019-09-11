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

  VectorXd cal_FHcBarRef = constraintModel.getControlNodeVector(constraintModel.Bc.transpose()*fb.cal_Ffb,"c","RARMEE");
  MatrixXd bb_CcMH = constraintModel.getControlNodeMatrix(constraintModel.mbb_CcM,false,true,"c","RARMEE");

  VectorXd cal_FCextRef = cal_dLCRef + model->cal_GC - bb_CcMH*cal_FHcBarRef;

  MatrixXd bb_CcMF = constraintModel.getControlNodeMatrix(constraintModel.mbb_CcM,false,true,"c",2,"RLEGEE","LLEGEE");

  VectorXd cal_FFcBarRef;
  if(info.constraint->c.controlNode[info.model.controlNodeID["RLEGEE"]]==6&&
     info.constraint->c.controlNode[info.model.controlNodeID["LLEGEE"]]==6){
    Vector2d rFr = model->r[info.model.controlNodeID["RLEGEE"]].head(2);
    Vector2d rFl = model->r[info.model.controlNodeID["LLEGEE"]].head(2);

    Vector3d ez(0.,0.,1.);
    Matrix3d St = diag(3, 1.,1.,0.);
    MatrixXd TX = MatrixXd::Zero(3,6);
    TX.block(0,0,3,3) = (1/(model->M*model->wX*model->wX))*St;
    TX.block(0,3,3,3) = -(1/(model->M*abs(worldModel->ag(2))))*cross(ez);

    Vector3d rextHDes = TX*bb_CcMH*cal_FHcBarRef;
    Vector3d rvrpDes = des.rXDes - des.drXDes/model->wX;
    Vector3d rndvrpDes = rvrpDes + rextHDes;

    // Vector2d recmp = (rvrpDes).head(2);
    Vector2d recmp = (rndvrpDes).head(2);

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
