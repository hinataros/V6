/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::initialize(const string &input)
{
  if(debug) DEBUG;

  this->input = input;
}
