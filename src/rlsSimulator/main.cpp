/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

int main(int argc, char *argv[])
{
  RLS::Config config(argc, argv);

  RLS::Model model(config);
  RLS::RlsDynamics rlsDynamics(config, model.hoap2.info);
  RLS::Output output;

  RLS::RlsSimulator rlsSimulator(model.hoap2.info);

  rlsSimulator.run(config, model, rlsDynamics, output);

  return 0;
}
