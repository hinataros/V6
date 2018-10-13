/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::finalize()
{
  if(debug) DEBUG;

  delete[] this->config.controlInput;
  delete[] k;
  delete[] u;
  delete[] state;
}
