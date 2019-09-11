/**

   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalEcmpTSDistribution()
{
  if(debug) DEBUG;

  MatrixXd bb_CcMH = constraintModel.getControlNodeMatrix(constraintModel.mbb_CcM,false,true,"c","RARMEE");
  MatrixXd bb_CcMF = constraintModel.getControlNodeMatrix(constraintModel.mbb_CcM,false,true,"c",2,"RLEGEE","LLEGEE");

  Vector3d rvrpDes = des.rXDes - des.drXDes/model->wX;
  Vector3d rvrpRef = model->rX - fb.drXfb/model->wX;

  // Vector2d rndvrpRef = model->rX0.head(2) + 0.5*(model->rX0.head(2) - model->rp);
  Vector2d rndvrpRef = model->rX0.head(2);
  Vector2d DeltarextRef = rvrpDes.head(2) - rndvrpRef;

  o(des.rXDes);
  o(des.drXDes);
  o(rvrpDes.head(2));
  o(rndvrpRef);
  o(DeltarextRef);

  Vector3d ez(0.,0.,1.);
  Matrix3d St = diag(3, 1.,1.,0.);
  MatrixXd TX = MatrixXd::Zero(2,6);
  o(St.block(0,0,2,3));
  o((cross(ez).block(0,0,2,3)));

  TX.block(0,0,2,3) = (1/(model->M*model->wX*model->wX))*St.block(0,0,2,3);
  TX.block(0,3,2,3) = -(1/(model->M*abs(worldModel->ag(2))))*(cross(ez).block(0,0,2,3));

  o(TX);
  MatrixXd CX = TX*bb_CcMH;
  // MatrixXd W = MatrixXd::Identity(6,6);
  // W = diag(6, 0.000001,1.,1.,1.,1.,1.);
  o(CX);
  o(pInv(CX));
  // o(pInv(CX,W));
  // VectorXd cal_FHcBarRef = pInv(CX,W)*DeltarextRef;
  VectorXd cal_FHcBarRef = pInv(CX)*DeltarextRef;
  o(cal_FHcBarRef);

  VectorXd cal_FCextRef = cal_dLCRef + model->cal_GC - bb_CcMH*cal_FHcBarRef;
  // (this->*internalForceController_ptr)(info);

  VectorXd cal_FFcBarRef;
  if(info.constraint->c.controlNode[info.model.controlNodeID["RLEGEE"]]==6&&
     info.constraint->c.controlNode[info.model.controlNodeID["LLEGEE"]]==6){

    Vector2d rFr = model->r[info.model.controlNodeID["RLEGEE"]].head(2);
    Vector2d rFl = model->r[info.model.controlNodeID["LLEGEE"]].head(2);

    // Vector2d recmp = (rvrpRef).head(2);
    // Vector2d recmp = (rndvrpRef).head(2);
    Vector2d recmp = model->rp;
    MatrixXd WecmpF = h_weight(recmp, rFr, rFl);

    cal_FFcBarRef = pInv(bb_CcMF, WecmpF)*(cal_FCextRef);
  }
  else{
    cal_FFcBarRef = pInv(bb_CcMF)*(cal_FCextRef);
  }

  cal_FcBarRef <<
    cal_FFcBarRef,
    cal_FHcBarRef;

  o(cal_FcBarRef);
  gc;
}
