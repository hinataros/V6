/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name1, string name2, string name3)
  {
    string value;

    try{
      value = doc[node][phase][name1][name2][name3].as<string>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  int RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name1, string name2, string name3)
  {
    int value;

    try{
      value = doc[node][phase][name1][name2][name3].as<int>();
    }
    catch(...){value=NAN;}

    return value;
  }
}
