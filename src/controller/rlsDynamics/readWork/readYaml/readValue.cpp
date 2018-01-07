/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> string RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name)
  {
    string value;

    try{
      value = doc[node][seq][name].as<string>();
    }
    catch(...){value="default";}

    return value;
  }

  template<> int RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name)
  {
    int value;

    try{
      value = doc[node][seq][name].as<int>();
    }
    catch(...){value=0;}

    return value;
  }

  template<> double RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name)
  {
    double value;

    try{
      value = doc[node][seq][name].as<double>();
    }
    catch(...){value=0.;}

    return value;
  }

  template<> int RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name, int i)
  {
    int value;

    try{
      value = doc[node][seq][name][i].as<int>();
    }
    catch(...){value=0;}

    return value;
  }

  template<> double RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name, int i)
  {
    double value;

    try{
      value = doc[node][seq][name][i].as<double>();
    }
    catch(...){value=0.;}

    return value;
  }

  template<> int RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name, int i, int j)
  {
    int value;

    try{
      value = doc[node][seq][name][i][j].as<int>();
    }
    catch(...){value=0;}

    return value;
  }

  template<> double RlsDynamics::readValue(YAML::Node &doc, string node, int seq, string name, int i, int j)
  {
    double value;

    try{
      value = doc[node][seq][name][i][j].as<double>();
    }
    catch(...){value=0.;}

    return value;
  }
}
