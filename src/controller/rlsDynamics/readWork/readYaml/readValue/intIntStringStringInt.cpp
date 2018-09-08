/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  int RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name1, string name2, int i)
  {
    int value;

    try{
      value = doc[node][num][phase][name1][name2][i].as<int>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name1, string name2, int i)
  {
    double value;

    try{
      value = doc[node][num][phase][name1][name2][i].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }
}
