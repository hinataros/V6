/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::finalize(Config &config, Info &info, Model &model, Controller &controller, Output &output)
{
  if(config.flag.debug) DEBUG;

  controller.finalize(config, info);

  output.finalize(config);

  model.deleteModel(config, info);
  info.finalize(config);
}
