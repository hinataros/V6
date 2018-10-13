/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::resizeSequence()
{
  if(debug) DEBUG;

  sequence = new Sequence[yamlInfo->sequenceNum];

  for(int i=0; i<yamlInfo->sequenceNum; i++){
    sequence[i].phase = 0;
    sequence[i].tw0 = 0.;
    sequence[i].twf = 0.;

    sequence[i].rCf = Vector3d::Zero();
    sequence[i].rBf = Vector3d::Zero();
    sequence[i].xiBf = Vector3d::Zero();
    sequence[i].rXf = Vector3d::Zero();
    sequence[i].cal_Xf = VectorXd::Zero(6*info->controlNodeNum);
    sequence[i].cal_Xfabs = VectorXd::Zero(6*info->controlNodeNum);

    sequence[i].cal_Ff = VectorXd::Zero(6*info->controlNodeNum);

    sequence[i].cal_Fextf = Vector6d::Zero();


    // previous desired value
    // ******************************
    sequence[i].rCpreDes = Vector3d::Zero();
    sequence[i].rBpreDes = Vector3d::Zero();
    sequence[i].xiBpreDes = Vector3d::Zero();
    sequence[i].rXpreDes = Vector3d::Zero();
    sequence[i].cal_XpreDes = VectorXd::Zero(6*info->controlNodeNum);
    sequence[i].cal_XpreDesabs = VectorXd::Zero(6*info->controlNodeNum);

    sequence[i].cal_FpreDes = VectorXd::Zero(6*info->controlNodeNum);

    sequence[i].cal_FextpreDes = Vector6d::Zero();

    sequence[i].cal_Xtd = VectorXd::Zero(6*info->controlNodeNum);
  }
}
