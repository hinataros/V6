/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, string name3, string value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2, name3))
        return value;

      return readValue<string>(doc, node, num, phase, name1, name2, name3);
    }

    if(!checkNode(doc, node, phase, name1, name2, name3))
      return value;

    return readValue<string>(doc, node, phase, name1, name2, name3);
  }
  template<>
  int RlsDynamics::updateValue(YAML::Node &doc, bool multi, string node, int num, int phase, string name1, string name2, string name3, int value)
  {
    if(multi){
      if(!checkNode(doc, node, num, phase, name1, name2, name3))
        return value;

      return readValue<int>(doc, node, num, phase, name1, name2, name3);
    }

    if(!checkNode(doc, node, phase, name1, name2, name3))
      return value;

    return readValue<int>(doc, node, phase, name1, name2, name3);
  }
}
