/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::initialize(const TreeModelInfo &info, const ControllerTreeModel &model, YamlInfo &yamlInfo, const DesiredValueGenerator &desiredValueGenerator)
{
  if(debug) DEBUG;

  setModel(info, model, desiredValueGenerator);
  setYamlInfo(yamlInfo);

  resize();

  setMap();
}
