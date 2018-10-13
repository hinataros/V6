/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::initialize(const string &path_yaml_rlsSimulator, const Info &info)
{
  if(debug) DEBUG;

  initializeState(info);

  readRlsSimulator(path_yaml_rlsSimulator, info);
}
