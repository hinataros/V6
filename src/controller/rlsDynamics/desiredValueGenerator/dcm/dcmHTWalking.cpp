/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::dcmHTWalking(const double &t)
{
  if(debug) DEBUG;

  walking.setStartTime(tw0[dcmNum]);
  walking.setFinishTime(twf[dcmNum]);
  walking.setStartValue(rXpreDes);
  walking.setFinishValue(rXf);

  // walking.ht(t);

  if(constraintModel->getControlNodeVector(cal_FDes,"all","RARMEE").norm()==0.){
    if(!walking.oscF)
      walking.ht(t);
    else
      walking.htOscillate(t);
  }else{
    VectorXd cal_FHcBarRef = constraintModel->getControlNodeVector(constraintModel->Bc.transpose()*cal_FDes,"c","RARMEE");
    MatrixXd bb_CcMH = constraintModel->getControlNodeMatrix(constraintModel->mbb_CcM,false,true,"c","RARMEE");

    Vector3d ez(0.,0.,1.);
    Matrix3d St = diag(3, 1.,1.,0.);
    MatrixXd TX = MatrixXd::Zero(3,6);
    TX.block(0,0,3,3) = (1/(model->M*model->wX*model->wX))*St;
    TX.block(0,3,3,3) = -(1/(model->M*abs(worldModel->ag(2))))*cross(ez);

    walking.setExt(TX*bb_CcMH*cal_FHcBarRef);

    walking.eht(t);
  }

  rXDes = walking.rXDes;
  drXDes = walking.drXDes;
}
