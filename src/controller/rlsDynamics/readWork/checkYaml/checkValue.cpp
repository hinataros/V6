#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> string RlsDynamics::checkValue(Config &config, Info &info, YAML::Node &doc, string name, string value)
  {
    if(config.flag.debug) DEBUG;

    try{
      checkNode(config, info, doc, name);
    }
    catch(...){return value;}

    return readValue<string>(config, info, doc, name);;
  }

  template<> double RlsDynamics::checkValue(Config &config, Info &info, YAML::Node &doc, string name, double value)
  {
    if(config.flag.debug) DEBUG;

    try{
      checkNode(config, info, doc, name);
    }
    catch(...){return value;}

    return readValue<double>(config, info, doc, name);;
  }
}
