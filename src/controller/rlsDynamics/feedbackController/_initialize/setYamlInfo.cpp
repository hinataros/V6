/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::setYamlInfo(YamlInfo &yamlInfo)
{
  if(debug) DEBUG;

  this->yamlInfo = &yamlInfo;
}
