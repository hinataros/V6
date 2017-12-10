#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> string RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name)
  {
    if(config.flag.debug) DEBUG;

    string value;

    try{
      value = doc["Work"][info.sim.phase][name].as<string>();
    }
    catch(...){value="default";}

    return value;
  }

  template<> int RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name)
  {
    if(config.flag.debug) DEBUG;

    int value;

    try{
      value = doc["Work"][info.sim.phase][name].as<int>();
    }
    catch(...){value=0;}

    return value;
  }

  template<> double RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name)
  {
    if(config.flag.debug) DEBUG;

    double value;

    try{
      value = doc["Work"][info.sim.phase][name].as<double>();
    }
    catch(...){value=0.;}

    return value;
  }

  template<> int RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name, int i)
  {
    if(config.flag.debug) DEBUG;

    int value;

    try{
      value = doc["Work"][info.sim.phase][name][i].as<int>();

    }
    catch(...){value=0;}

    return value;
  }

  template<> double RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name, int i)
  {
    if(config.flag.debug) DEBUG;

    double value;

    try{
      value = doc["Work"][info.sim.phase][name][i].as<double>();

    }
    catch(...){value=0.;}

    return value;
  }

  template<> int RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name, int node, int i)
  {
    if(config.flag.debug) DEBUG;

    int value;

    try{
      value = doc["Work"][info.sim.phase][name][node][i].as<int>();

    }
    catch(...){value=0;}

    return value;
  }

  template<> double RlsDynamics::readValue(Config &config, Info &info, YAML::Node &doc, string name, int node, int i)
  {
    if(config.flag.debug) DEBUG;

    double value;

    try{
      value = doc["Work"][info.sim.phase][name][node][i].as<double>();

    }
    catch(...){value=0.;}

    return value;
  }
}
