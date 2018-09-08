/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name, int i)
  {
    double value;

    try{
      value = doc[node][phase][name][i].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }
}
