/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  int RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name, int i, int j)
  {
    int value;

    try{
      value = doc[node][num][phase][name][i][j].as<int>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name, int i, int j)
  {
    double value;

    try{
      value = doc[node][num][phase][name][i][j].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }
}
