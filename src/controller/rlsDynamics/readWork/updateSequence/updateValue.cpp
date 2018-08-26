/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  string RlsDynamics::updateValue(YAML::Node &doc, string node, int num, int phase, string name, string value)
  {
    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return value;

      return readValue<string>(doc, node, num, phase, name);
    }

    if(!checkNode(doc, node, phase, name))
      return value;

    return readValue<string>(doc, node, phase, name);
  }
  template<>
  double RlsDynamics::updateValue(YAML::Node &doc, string node, int num, int phase, string name, double value)
  {
    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name))
        return value;

      return readValue<double>(doc, node, num, phase, name);
    }

    if(!checkNode(doc, node, phase, name))
      return value;

    return readValue<double>(doc, node, phase, name);
  }

  template<>
  string RlsDynamics::updateValue(YAML::Node &doc, string node, int num, int phase, string name1, string name2, string value)
  {
    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return value;

      return readValue<string>(doc, node, num, phase, name1, name2);
    }

    if(!checkNode(doc, node, phase, name1, name2))
      return value;

    return readValue<string>(doc, node, phase, name1, name2);
  }
  template<>
  int RlsDynamics::updateValue(YAML::Node &doc, string node, int num, int phase, string name1, string name2, int value)
  {
    if(multiSequence){
      if(!checkNode(doc, node, num, phase, name1, name2))
        return value;

      return readValue<int>(doc, node, num, phase, name1, name2);
    }

    if(!checkNode(doc, node, phase, name1, name2))
      return value;

    return readValue<int>(doc, node, phase, name1, name2);
  }
}
