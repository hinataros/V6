/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::initialize(const WorldModel &worldModel, const TreeModelInfo &info, const ControllerTreeModel &model, ConstraintModel &constraintModel, YamlInfo &yamlInfo)
{
  if(debug) DEBUG;

  setModel(worldModel, info, model, constraintModel);
  setYamlInfo(yamlInfo);

  resize();
  // resizeState();

  setMap();

  setInitialBoundary();

  string walkingKeyName = "walking";
  if(this->yamlInfo->doc.controllerKey[walkingKeyName])
    initializeWalking();
}
