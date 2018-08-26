/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
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
  int RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name, int i, int j)
  {
    int value;

    try{
      value = doc[node][phase][name][i][j].as<int>();
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
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name, int i)
  {
    double value;

    try{
      value = doc[node][phase][name][i].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name, int i, int j)
  {
    double value;

    try{
      value = doc[node][phase][name][i][j].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }

  template<>
  string RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name)
  {
    string value;

    try{
      value = doc[node][num][phase][name].as<string>();
    }
    catch(...){value=NAN;}

    return value;
  }
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
  double RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name)
  {
    double value;

    try{
      value = doc[node][num][phase][name].as<double>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  double RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name, int i)
  {
    double value;

    try{
      value = doc[node][num][phase][name][i].as<double>();
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

  template<>
  string RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name1, string name2)
  {
    string value;

    try{
      value = doc[node][phase][name1][name2].as<string>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  int RlsDynamics::readValue(YAML::Node &doc, string node, int phase, string name1, string name2)
  {
    int value;

    try{
      value = doc[node][phase][name1][name2].as<int>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  string RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name1, string name2)
  {
    string value;

    try{
      value = doc[node][num][phase][name1][name2].as<string>();
    }
    catch(...){value=NAN;}

    return value;
  }
  template<>
  int RlsDynamics::readValue(YAML::Node &doc, string node, int num, int phase, string name1, string name2)
  {
    int value;

    try{
      value = doc[node][num][phase][name1][name2].as<int>();
    }
    catch(...){value=NAN;}

    return value;
  }
}
