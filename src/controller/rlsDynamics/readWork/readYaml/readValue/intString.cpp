/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name)
  {
    string value;

    try{
      value = doc[node][phase][name].as<string>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name)
  {
    double value;

    try{
      value = doc[node][phase][name].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }
}
