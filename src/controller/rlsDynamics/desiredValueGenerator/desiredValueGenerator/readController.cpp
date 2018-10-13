/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::readController()
{
  if(debug) DEBUG;

  yamlInfo->checkValue<int>(desiredBaseTranslationGeneratorNum,
                            "Desired base translation generator", "num");
  yamlInfo->checkValue<string>(desiredBaseTranslationGeneratorName,
                            "Desired base translation generator", "name");

  yamlInfo->checkValue<int>(desiredBaseOrientationGeneratorNum,
                            "Desired base orientation generator", "num");
  yamlInfo->checkValue<string>(desiredBaseOrientationGeneratorName,
                            "Desired base orientation generator", "name");

  yamlInfo->checkValue<int>(desiredComGeneratorNum,
                            "Desired CoM generator", "num");
  yamlInfo->checkValue<string>(desiredComGeneratorName,
                            "Desired CoM generator", "name");

  yamlInfo->checkValue<int>(desiredDcmGeneratorNum,
                            "Desired DCM generator", "num");
  yamlInfo->checkValue<string>(desiredDcmGeneratorName,
                            "Desired DCM generator", "name");

  yamlInfo->checkValue<int>(desiredExternalWrenchGeneratorNum,
                            "Desired external wrench generator", "num");
  yamlInfo->checkValue<string>(desiredExternalWrenchGeneratorName,
                            "Desired external wrench generator", "name");

  for(int i=0; i<info->controlNodeNum; i++){
    string name = info->controlNode[i].name;

    yamlInfo->checkValue<int>(desiredControlNodeMotionGeneratorNum[i],
                              "Desired control node motion generator", name, "num");
    yamlInfo->checkValue<string>(desiredControlNodeMotionGeneratorName[i],
                                 "Desired control node motion generator", name, "name");

    yamlInfo->checkValue<int>(desiredControlNodeForceGeneratorNum[i],
                              "Desired control node force generator", name, "num");
    yamlInfo->checkValue<string>(desiredControlNodeForceGeneratorName[i],
                              "Desired control node force generator", name, "name");
  }

  if(yamlInfo->key=="Sequence"){
    yamlInfo->checkValue<double>(sequence[yamlInfo->sequence].twf, "twf");

    yamlInfo->checkValue<Vector3d>(sequence[yamlInfo->sequence].rBf, "rBf");
    yamlInfo->checkValue<Vector3d>(sequence[yamlInfo->sequence].xiBf, "xiBf");

    yamlInfo->checkValue<Vector3d>(sequence[yamlInfo->sequence].rCf, "rCf");

    yamlInfo->checkValue<Vector3d>(sequence[yamlInfo->sequence].rXf, "rXf");

    yamlInfo->checkValue<Vector6d>(sequence[yamlInfo->sequence].cal_Fextf, "cal_Fextf");

    for(int i=0; i<info->controlNodeNum; i++){
      string name = info->controlNode[i].name;

      Vector6d temp = sequence[yamlInfo->sequence].cal_Xf.segment(6*i,6);
      yamlInfo->checkValue<Vector6d>(temp, "cal_Xf", name);
      sequence[yamlInfo->sequence].cal_Xf.segment(6*i,6) = temp;

      temp = sequence[yamlInfo->sequence].cal_Xfabs.segment(6*i,6);
      yamlInfo->checkValue<Vector6d>(temp, "cal_Xfabs", name);
      sequence[yamlInfo->sequence].cal_Xfabs.segment(6*i,6) = temp;

      temp = sequence[yamlInfo->sequence].cal_Ff.segment(6*i,6);
      yamlInfo->checkValue<Vector6d>(temp, "cal_Ff", name);
      sequence[yamlInfo->sequence].cal_Ff.segment(6*i,6) = temp;

      temp = sequence[yamlInfo->sequence].cal_Xtd.segment(6*i,6);
      yamlInfo->checkValue<Vector6d>(temp, "cal_Xtd", name);
      sequence[yamlInfo->sequence].cal_Xtd.segment(6*i,6) = temp;
    }
  }
}

