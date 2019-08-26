/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readController()
{
  if(debug) DEBUG;

  // if(yamlInfo.key==yamlInfo.sequenceKeyName)
  // yamlInfo.checkValue<double>(sequence[yamlInfo.sequence].twf, "twf");

  string controlMethodKeyName = "control method";

  yamlInfo.checkValue<bool>(extInverseDynamicsController, controlMethodKeyName,
                            "ext inverse dynamics controller");
  yamlInfo.checkValue<bool>(extMotionController, controlMethodKeyName,
                            "ext motion controller");
  yamlInfo.checkValue<bool>(extMomentumController, controlMethodKeyName,
                            "ext momentum controller");
  yamlInfo.checkValue<bool>(extForceController, controlMethodKeyName,
                            "ext force controller");
  yamlInfo.checkValue<bool>(extTorqueController, controlMethodKeyName,
                            "ext torque controller");
  yamlInfo.checkValue<bool>(extExternalWrenchController, controlMethodKeyName,
                            "ext external wrench controller");


  yamlInfo.checkValue<string>(inverseDynamicsControllerName, controlMethodKeyName,
                              "inverse dynamics controller");
  yamlInfo.checkValue<string>(operationalSpaceControllerName, controlMethodKeyName,
                              "operational space controller");
  yamlInfo.checkValue<string>(motionControllerName, controlMethodKeyName,
                              "motion controller");
  yamlInfo.checkValue<string>(momentumControllerName, controlMethodKeyName,
                              "momentum controller");
  yamlInfo.checkValue<string>(internalForceControllerName, controlMethodKeyName,
                              "internal force controller");
  yamlInfo.checkValue<string>(forceControllerName, controlMethodKeyName,
                              "force controller");
  yamlInfo.checkValue<string>(torqueControllerName, controlMethodKeyName,
                              "torque controller");
  yamlInfo.checkValue<string>(externalWrenchControllerName, controlMethodKeyName,
                              "external wrench controller");
}


void RLS::RlsDynamics::readController(vector<string> &CM)
{
  if(debug) DEBUG;

  // if(yamlInfo.key==yamlInfo.sequenceKeyName)
    // yamlInfo.checkValue<double>(sequence[yamlInfo.sequence].twf, "twf");

  string controlMethodKeyName = "control method";

  yamlInfo.checkValue<bool>(extInverseDynamicsController, controlMethodKeyName,
                            "ext inverse dynamics controller");
  yamlInfo.checkValue<bool>(extMotionController, controlMethodKeyName,
                            "ext motion controller");
  yamlInfo.checkValue<bool>(extMomentumController, controlMethodKeyName,
                            "ext momentum controller");
  yamlInfo.checkValue<bool>(extForceController, controlMethodKeyName,
                            "ext force controller");
  yamlInfo.checkValue<bool>(extTorqueController, controlMethodKeyName,
                            "ext torque controller");
  yamlInfo.checkValue<bool>(extExternalWrenchController, controlMethodKeyName,
                            "ext external wrench controller");

  // amiyata メタ糞気持ち悪いがうまいやり方が思いつかない
  yamlInfo.checkValue<string>(inverseDynamicsControllerName, controlMethodKeyName, "inverse dynamics controller");
  if(yamlInfo.checkValue<string>(operationalSpaceControllerName, controlMethodKeyName, "operational space controller"))
    CM.push_back("operationalSpaceController/"+operationalSpaceControllerName);
  if(yamlInfo.checkValue<string>(motionControllerName, controlMethodKeyName, "motion controller"))
    CM.push_back("configurationSpaceController/"+motionControllerName);
  if(yamlInfo.checkValue<string>(momentumControllerName, controlMethodKeyName, "momentum controller"))
    CM.push_back("momentumController/"+momentumControllerName);
  yamlInfo.checkValue<string>(internalForceControllerName, controlMethodKeyName, "internal force controller");
  if(yamlInfo.checkValue<string>(forceControllerName, controlMethodKeyName, "force controller"))
    CM.push_back("forceController/"+forceControllerName);
  if(yamlInfo.checkValue<string>(torqueControllerName, controlMethodKeyName, "torque controller"))
    CM.push_back("torqueController/"+torqueControllerName);
  if(yamlInfo.checkValue<string>(externalWrenchControllerName, controlMethodKeyName, "external wrench controller"))
    CM.push_back("externalWrenchController/"+externalWrenchControllerName);
}
