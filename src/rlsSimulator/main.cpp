/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

int main(int argc, char *argv[])
{
  RLS::Config config(argc, argv);
  RLS::Info info(config);

  RLS::Model model(config, info);
  RLS::Controller controller(config, info);
  RLS::Output output;

  RLS::RlsSimulator rlsSimulator(config, info);

  rlsSimulator.run(config, info, model, controller, output);

  return 0;
}
