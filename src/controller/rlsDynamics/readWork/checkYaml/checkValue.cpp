/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> string RlsDynamics::checkValue(YAML::Node &doc, string node, int seq, string name, string value)
  {
    try{
      checkNode(doc, node, seq, name);
    }
    catch(...){return value;}

    return readValue<string>(doc, node, seq, name);
  }

  template<> double RlsDynamics::checkValue(YAML::Node &doc, string node, int seq, string name, double value)
  {
    try{
      checkNode(doc, node, seq, name);
    }
    catch(...){return value;}

    return readValue<double>(doc, node, seq, name);
  }
}
