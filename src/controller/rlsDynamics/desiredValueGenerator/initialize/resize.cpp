/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::resize()
{
  if(debug) DEBUG;

  rC0 = Vector3d::Zero();

  rB0 = Vector3d::Zero();
  xiB0 = Vector3d::Zero();

  rX0 = Vector3d::Zero();

  cal_X0 = VectorXd::Zero(6*info->controlNodeNum);
  cal_Fext0 = Vector6d::Zero();

  des = Vector3d::Zero();

  rCDes = vCDes = dvCDes = Vector3d::Zero();

  rBDes = vBDes = dvBDes = Vector3d::Zero();
  xiBDes = dxiBDes = ddxiBDes = Vector3d::Zero();
  RBDes = Matrix3d::Zero();
  wBDes = dwBDes = Vector3d::Zero();

  rXDes = drXDes = Vector3d::Zero();

  cal_XDes = cal_VxiDes = cal_dVxiDes = VectorXd::Zero(6*info->controlNodeNum);
  cal_VDes = cal_dVDes = VectorXd::Zero(6*info->controlNodeNum);

  cal_FDes = VectorXd::Zero(6*info->controlNodeNum);

  cal_FextDes = Vector6d::Zero();

  desiredBaseTranslationGeneratorNum = 0;
  desiredBaseOrientationGeneratorNum = 0;

  desiredControlNodeMotionGeneratorNum = new int[info->controlNodeNum];
  desiredControlNodeMotionGeneratorName = new string[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    desiredControlNodeMotionGeneratorNum[i] = 0;
    desiredControlNodeMotionGeneratorName[i] = "default";
  }

  desiredControlNodeForceGeneratorNum = new int[info->controlNodeNum];
  desiredControlNodeForceGeneratorName = new string[info->controlNodeNum];
  for(int i=0; i<info->controlNodeNum; i++){
    desiredControlNodeForceGeneratorNum[i] = 0;
    desiredControlNodeForceGeneratorName[i] = "default";
  }

  desiredComGeneratorNum = 0;
  desiredDcmGeneratorNum = 0;
  desiredExternalWrenchGeneratorNum = 0;

  desiredBaseTranslationGeneratorName
    = desiredBaseOrientationGeneratorName
    = desiredComGeneratorName
    = desiredDcmGeneratorName
    = desiredExternalWrenchGeneratorName
    = "default";

  desiredControlNodeMotionGenerator_ptr =
    (void (RLS::DesiredValueGenerator::**)(const int&, const double&))malloc(sizeof(void (RLS::DesiredValueGenerator::*)(const int&, const double&))*info->controlNodeNum);
  desiredControlNodeForceGenerator_ptr =
    (void (RLS::DesiredValueGenerator::**)(const int&, const double&))malloc(sizeof(void (RLS::DesiredValueGenerator::*)(const int&, const double&))*info->controlNodeNum);

  // // EE reference
  // referenceSequence = 1;
  // cal_Xtd = VectorXd::Zero(6*info->controlNodeNum);
}
