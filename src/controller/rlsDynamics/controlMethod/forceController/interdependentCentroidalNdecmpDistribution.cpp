/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::interdependentCentroidalNdecmpDistribution()
{
  if(debug) DEBUG;

  string namek = "LARMEE";
  string namekBar[2] = {"RLEGEE","LLEGEE"};

  // (this->*internalForceController_ptr)(info);

  VectorXd cal_FckRef = constraintModel.getControlNodeVector(constraintModel.Bc.transpose()*fb.cal_Ffb,"c",namek);
  MatrixXd bb_CcMk = constraintModel.getControlNodeMatrix(constraintModel.cal_PcM,false,true,"c",namek);

  VectorXd cal_FCRef = cal_dLCRef + model->cal_GC - bb_CcMk*cal_FckRef;

  MatrixXd bb_CcMkBar = constraintModel.getControlNodeMatrix(constraintModel.cal_PcM,false,true,"c",2,namekBar[0].c_str(), namekBar[1].c_str());

  VectorXd cal_FckBarRef;
  if(info.constraint->c.controlNode[info.model.controlNodeID[namekBar[0]]]==6&&
     info.constraint->c.controlNode[info.model.controlNodeID[namekBar[1]]]==6){
    Vector2d rFkBar1 = model->r[info.model.controlNodeID[namekBar[0]]].head(2);
    Vector2d rFkBar2 = model->r[info.model.controlNodeID[namekBar[1]]].head(2);

    Vector3d ez(0.,0.,1.);
    Matrix3d St = diag(3, 1.,1.,0.);
    MatrixXd cal_KX = MatrixXd::Zero(3,6);
    cal_KX.block(0,0,3,3) = (1/(model->M*model->wX*model->wX))*St;
    cal_KX.block(0,3,3,3) = -(1/(model->M*abs(worldModel->ag(2))))*cross(ez);

    Vector3d rvrpkDes = cal_KX*bb_CcMk*cal_FckRef;

    Vector3d rvrpDes = des.rXDes - des.drXDes/model->wX;
    Vector2d recmpkBarDes = (rvrpDes + rvrpkDes).head(2);
    MatrixXd WecmpkBar = h_weight(recmpkBarDes, rFkBar1, rFkBar2);

    cal_FckBarRef = pInv(bb_CcMkBar, WecmpkBar)*(cal_FCRef);
  }
  else{
    cal_FckBarRef = pInv(bb_CcMkBar)*(cal_FCRef);
  }

  cal_FcBarRef <<
    cal_FckBarRef,
    cal_FckRef;
}
