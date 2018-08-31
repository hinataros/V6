/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<>
  Vector3d RlsDynamics::updateVector(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Vector3d vec)
  {
    if(multi){
      if(doc[node][num][phase][name].size()==3)
        for(int i=0; i<3; i++)
          vec(i) = readValue<double>(doc, node, num, phase, name, i);
      else
        return vec;
    }
    else{
      if(doc[node][phase][name].size()==3)
        for(int i=0; i<3; i++)
          vec(i) = readValue<double>(doc, node, phase, name, i);
      else
        return vec;
    }

    return vec;
  }

  template<>
  Vector6d RlsDynamics::updateVector(YAML::Node &doc, bool multi, string node, int num, int phase, string name, Vector6d vec)
  {
    if(multi){
      if(doc[node][num][phase][name].size()==6)
        for(int i=0; i<6; i++)
          vec(i) = readValue<double>(doc, node, num, phase, name, i);
      else
        return vec;
    }
    else{
      if(doc[node][phase][name].size()==6)
        for(int i=0; i<6; i++)
          vec(i) = readValue<double>(doc, node, phase, name, i);
      else
        return vec;
    }

    return vec;
  }
}
