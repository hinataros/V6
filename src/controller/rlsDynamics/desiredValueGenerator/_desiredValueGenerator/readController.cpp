/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::readController()
{
  if(debug) DEBUG;

  string desiredValueGeneratorKeyName = "desired value generator";

  yamlInfo->checkValue<int>(baseTranslationNum, desiredValueGeneratorKeyName,
                            "base translation", "num");
  yamlInfo->checkValue<string>(baseTranslationName, desiredValueGeneratorKeyName,
                               "base translation", "name");

  yamlInfo->checkValue<int>(baseRotationNum, desiredValueGeneratorKeyName,
                            "base rotation", "num");
  yamlInfo->checkValue<string>(baseRotationName, desiredValueGeneratorKeyName,
                               "base rotation", "name");

  yamlInfo->checkValue<int>(comNum, desiredValueGeneratorKeyName,
                            "CoM", "num");
  yamlInfo->checkValue<string>(comName, desiredValueGeneratorKeyName,
                               "CoM", "name");

  yamlInfo->checkValue<int>(dcmNum, desiredValueGeneratorKeyName,
                            "DCM", "num");
  yamlInfo->checkValue<string>(dcmName, desiredValueGeneratorKeyName,
                               "DCM", "name");

  yamlInfo->checkValue<int>(externalWrenchNum, desiredValueGeneratorKeyName,
                            "external wrench", "num");
  yamlInfo->checkValue<string>(externalWrenchName, desiredValueGeneratorKeyName,
                               "external wrench", "name");

  for(int i=0; i<info->controlNodeNum; i++){
    string name = info->controlNode[i].name;

    yamlInfo->checkValue<int>(controlNodeTranslationNum[i], desiredValueGeneratorKeyName,
                              "control node translation", name, "num");
    yamlInfo->checkValue<string>(controlNodeTranslationName[i], desiredValueGeneratorKeyName,
                                 "control node translation", name, "name");
    yamlInfo->checkValue<int>(controlNodeRotationNum[i], desiredValueGeneratorKeyName,
                              "control node rotation", name, "num");
    yamlInfo->checkValue<string>(controlNodeRotationName[i], desiredValueGeneratorKeyName,
                                 "control node rotation", name, "name");

    yamlInfo->checkValue<int>(controlNodeForceNum[i], desiredValueGeneratorKeyName,
                              "control node force", name, "num");
    yamlInfo->checkValue<string>(controlNodeForceName[i], desiredValueGeneratorKeyName,
                                 "control node force", name, "name");
    yamlInfo->checkValue<int>(controlNodeMomentNum[i], desiredValueGeneratorKeyName,
                              "control node moment", name, "num");
    yamlInfo->checkValue<string>(controlNodeMomentName[i], desiredValueGeneratorKeyName,
                                 "control node moment", name, "name");
  }

  if(yamlInfo->key==yamlInfo->sequenceKeyName){
    yamlInfo->checkValue<double>(twf[yamlInfo->sequence], "twf");

    if(baseTranslationNum==yamlInfo->sequence)
      yamlInfo->checkValue<Vector3d>(rBf, "rBf");
    if(baseRotationNum==yamlInfo->sequence){
      if(yamlInfo->checkValue<Vector3d>(xiBf, "xiBf")){
        if(yamlInfo->angleUnit=="degree")
          xiBf *= DEG2RAD;
        qBf = Quaternion4d::xi2q(xiBf);
      }
    }

    if(comNum==yamlInfo->sequence)
      yamlInfo->checkValue<Vector3d>(rCf, "rCf");
    if(dcmNum==yamlInfo->sequence)
      yamlInfo->checkValue<Vector3d>(rXf, "rXf");

    if(externalWrenchNum==yamlInfo->sequence)
      yamlInfo->checkValue<Vector6d>(cal_Fextf, "cal_Fextf");

    for(int i=0; i<info->controlNodeNum; i++){
      string name = info->controlNode[i].name;

      if(controlNodeTranslationNum[i]==yamlInfo->sequence){
        yamlInfo->checkValue<Vector3d>(rf[i], "rf", name);
        yamlInfo->checkValue<Vector3d>(rfabs[i], "rfabs", name);

        yamlInfo->checkValue<Vector3d>(rtd[i], "rtd", name);
      }
      if(controlNodeRotationNum[i]==yamlInfo->sequence){
        if(yamlInfo->checkValue<Vector3d>(xif[i], "xif", name)){
          if(yamlInfo->angleUnit=="degree")
            xif[i] *= DEG2RAD;
          qf[i] = Quaternion4d::xi2q(xif[i]);
        }
        if(yamlInfo->checkValue<Vector3d>(xifabs[i], "xifabs", name)){
          if(yamlInfo->angleUnit=="degree")
            xifabs[i] *= DEG2RAD;
          qfabs[i] = Quaternion4d::xi2q(xifabs[i]);
        }
      }

      if(controlNodeForceNum[i]==yamlInfo->sequence)
        yamlInfo->checkValue<Vector3d>(ff[i], "ff", name);
      if(controlNodeMomentNum[i]==yamlInfo->sequence)
        yamlInfo->checkValue<Vector3d>(nf[i], "nf", name);
    }
  }
}

