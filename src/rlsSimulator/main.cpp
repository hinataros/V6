/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

int main(int argc, char *argv[])
{
  RLS::Config config(argc, argv);
  RLS::Model model(config.dir.share, config.path_yaml.model);
  RLS::Controller controller(config.path_yaml.controller, model);
  RLS::Output output(config.dir.link, config.path_yaml.output,
                     model.info, controller.controllerNum, model.worldModel);

  RLS::RlsSimulator rlsSimulator(config.path_yaml.rlsSimulator, model.info);

  rlsSimulator.run(model, controller, output);

  return 0;
}
