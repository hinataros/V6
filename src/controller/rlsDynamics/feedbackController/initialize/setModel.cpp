/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "feedbackController.hpp"

void RLS::FeedbackController::setModel(const TreeModelInfo &info, const ControllerTreeModel &model, const DesiredValueGenerator &desiredValueGenerator)
{
  if(debug) DEBUG;

  this->info = &info;
  this->model = &model;

  this->des = &desiredValueGenerator;
}
