/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::initialize(const TreeModelInfo &info, const ControllerTreeModel &model, YamlInfo &yamlInfo)
{
  if(debug) DEBUG;

  setModel(info, model);
  setYamlInfo(yamlInfo);

  resize();
  resizeSequence();
  resizeState();

  setMap();

  setInitialBoundary();
}
