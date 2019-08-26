/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputDesConfig()
{
  if(debug) DEBUG;

  outputList.rBDes = des.rBDes;
  outputList.vBDes = des.vBDes;
  outputList.dvBDes = des.dvBDes;

  outputList.xiBDes = antiDiag(3,1.,1.,1.)*R2xi(des.RBDes);
  outputList.wBDes = des.wBDes;
  outputList.dwBDes = des.dwBDes;

  outputList.rCDes = des.rCDes;
  outputList.vCDes = des.vCDes;
  outputList.dvCDes = des.dvCDes;

  outputList.rXDes = des.rXDes;
  outputList.drXDes = des.drXDes;

  if(des.rvrpCalc==1){
    outputList.rvrpDes = des.rCDes - des.dvCDes/(model->wX*model->wX);
  }
  else{
    outputList.rvrpDes = des.rXDes - des.drXDes/model->wX;
  }

  // outputList.rvrpBarDes = des.rXBarDes - des.drXBarDes/model->wX;
  outputList.rndvrpDes = des.rXDes - des.drXDes/model->wX;
  if(info.constraint->c.controlNode[info.model.controlNodeID["RARMEE"]]>0){
    MatrixXd bb_CcMH = constraintModel.getControlNodeMatrix(constraintModel.cal_PcM,false,true,"c","RARMEE");
    VectorXd cal_FHcBarRef = constraintModel.getControlNodeVector(constraintModel.Bc.transpose()*fb.cal_Ffb,"c","RARMEE");

    Vector3d ez(0.,0.,1.);
    Matrix3d St = diag(3, 1.,1.,0.);
    MatrixXd TX = MatrixXd::Zero(3,6);
    TX.block(0,0,3,3) = (1/(model->M*model->wX*model->wX))*St;
    TX.block(0,3,3,3) = -(1/(model->M*abs(worldModel->ag(2))))*cross(ez);

    Vector3d rextHDes = TX*bb_CcMH*cal_FHcBarRef;

    outputList.rndvrpDes += rextHDes;
  }

  outputList.rDes = outputList.vDes = outputList.dvDes
    = outputList.xiDes = outputList.wDes = outputList.dwDes
    = VectorXd::Zero(3*info.model.controlNodeNum);

  for(int i=0; i<info.model.controlNodeNum; i++){
    outputList.rDes.segment(3*i, 3) = des.rDes[i];
    outputList.xiDes.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*R2xi(des.RDes[i]);

    outputList.vDes.segment(3*i, 3) = des.cal_VDes.segment(6*i, 3);
    outputList.wDes.segment(3*i, 3) = des.cal_VDes.segment(6*i+3, 3);

    outputList.dvDes.segment(3*i, 3) = des.cal_dVDes.segment(6*i, 3);
    outputList.dwDes.segment(3*i, 3) = des.cal_dVDes.segment(6*i+3, 3);
  }

  outputList.quatB = Vector4d::Zero();
  outputList.quatBDes = Vector4d::Zero();
  Quaternion4d qB = Quaternion4d::R2q(model->RB);
  outputList.quatB.head(3) = qB.v;
  outputList.quatB(3) = qB.w;

  outputList.quatBDes.head(3) = des.qBDes.v;
  outputList.quatBDes(3) = des.qBDes.w;

  outputList.quat = VectorXd::Zero(4*info.model.controlNodeNum);
  outputList.quatDes = VectorXd::Zero(4*info.model.controlNodeNum);
  for(int i=0; i<info.model.controlNodeNum; i++){
    Quaternion4d q = Quaternion4d::R2q(model->R[i]);
    outputList.quat.segment(4*i, 3) = q.v;
    outputList.quat(4*i+3) = q.w;

    outputList.quatDes.segment(4*i, 3) = des.qDes[i].v;
    outputList.quatDes(4*i+3) = des.qDes[i].w;
  }
}
