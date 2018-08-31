/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, string value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return value;

      return readValue<string>(doc, node, num, phase, name);
    }

    if(!checkNode(doc, node, phase, name))
      return value;

    return readValue<string>(doc, node, phase, name);
  }
  template<>
  double RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name, double value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name))
        return value;

      return readValue<double>(doc, node, num, phase, name);
    }

    if(!checkNode(doc, node, phase, name))
      return value;

    return readValue<double>(doc, node, phase, name);
  }
}
