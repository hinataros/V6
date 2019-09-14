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

  yamlInfo->checkValue<string>(baseTranslationName, desiredValueGeneratorKeyName, "base translation", "name");
  yamlInfo->checkValue<string>(baseRotationName, desiredValueGeneratorKeyName, "base rotation", "name");

  yamlInfo->checkValue<string>(comName, desiredValueGeneratorKeyName, "CoM", "name");
  yamlInfo->checkValue<string>(dcmName, desiredValueGeneratorKeyName, "DCM", "name");

  yamlInfo->checkValue<string>(externalWrenchName, desiredValueGeneratorKeyName, "external wrench", "name");

  for(int i=0; i<info->controlNodeNum; i++){
    string name = info->controlNode[i].name;

    yamlInfo->checkValue<string>(controlNodeTranslationName[i], desiredValueGeneratorKeyName, "control node translation", name, "name");
    yamlInfo->checkValue<string>(controlNodeRotationName[i], desiredValueGeneratorKeyName, "control node rotation", name, "name");

    yamlInfo->checkValue<string>(controlNodeForceName[i], desiredValueGeneratorKeyName, "control node force", name, "name");
    yamlInfo->checkValue<string>(controlNodeMomentName[i], desiredValueGeneratorKeyName, "control node moment", name, "name");
  }

  if(yamlInfo->sequence >= 0) { // amiyata
    bool tLoad = false;
    yamlInfo->checkValue<bool>(tLoad, "tld");
    if(tLoad)
      twf[yamlInfo->sequence] = walking.Topt(yamlInfo->sequenceState);
    else
      yamlInfo->checkValue<double>(twf[yamlInfo->sequence], "twf");

    if(yamlInfo->checkValue<Vector3d>(rBf, "rBf"))
      baseTranslationNum = yamlInfo->sequence;
    if(yamlInfo->checkValue<Vector3d>(xiBf, "xiBf")){
      if(yamlInfo->angleUnit=="degree")
        xiBf *= DEG2RAD;
      qBf = Quaternion4d::xi2q(xiBf);
      baseRotationNum = yamlInfo->sequence;
    }

    if(yamlInfo->checkValue<Vector3d>(rCf, "rCf"))
      comNum = yamlInfo->sequence;

    if(yamlInfo->checkValue<Vector3d>(rXf, "rXf")){
      dcmNum = yamlInfo->sequence;
    }
    else if(yamlInfo->checkValue<Vector3d>(rXfabs, "rXfabs")){
      dcmNum = yamlInfo->sequence;
      rXfabs(2) = rX0(2);
      rXf = rXfabs - rX0;
    }

    if(yamlInfo->checkValue<Vector6d>(cal_Fextf, "cal_Fextf"))
      externalWrenchNum = yamlInfo->sequence;

    for(int i=0; i<info->controlNodeNum; i++){
      string name = info->controlNode[i].name;

      if(yamlInfo->checkValue<Vector3d>(rf[i], "rf", name))
        controlNodeTranslationNum[i] = yamlInfo->sequence;
      else if(yamlInfo->checkValue<Vector3d>(rfabs[i], "rfabs", name))
        controlNodeTranslationNum[i] = yamlInfo->sequence;

      if(yamlInfo->checkValue<Vector3d>(xif[i], "xif", name)){
        if(yamlInfo->angleUnit=="degree")
          xif[i] *= DEG2RAD;
        qf[i] = Quaternion4d::xi2q(xif[i]);
        controlNodeRotationNum[i] = yamlInfo->sequence;
      }
      else if(yamlInfo->checkValue<Vector3d>(xifabs[i], "xifabs", name)){
        if(yamlInfo->angleUnit=="degree")
          xifabs[i] *= DEG2RAD;
        qfabs[i] = Quaternion4d::xi2q(xifabs[i]);
        controlNodeRotationNum[i] = yamlInfo->sequence;
      }

      if(yamlInfo->checkValue<Vector3d>(ff[i], "ff", name))
        controlNodeForceNum[i] = yamlInfo->sequence;
      if(yamlInfo->checkValue<Vector3d>(nf[i], "nf", name))
        controlNodeMomentNum[i] = yamlInfo->sequence;
    }
  }
  // amiyata
  for(int i=0; i<info->controlNodeNum; i++){
    string name = info->controlNode[i].name;
    yamlInfo->checkValue<double>(rAp[i], "rApex", name);
  }
}
