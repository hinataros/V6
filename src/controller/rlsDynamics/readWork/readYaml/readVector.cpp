#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> VectorXi RlsDynamics::readVector(Config &config, Info &info, YAML::Node &doc, string name, int size)
  {
    if(config.flag.debug) DEBUG;

    VectorXi vec = VectorXi::Zero(size);

    for(int i=0; i<size; i++)
      vec(i) = readValue<int>(config, info, doc, name, i);

    return vec;
  }

  template<> VectorXd RlsDynamics::readVector(Config &config, Info &info, YAML::Node &doc, string name, int size)
  {
    if(config.flag.debug) DEBUG;

    VectorXd vec = VectorXd::Zero(size);

    for(int i=0; i<size; i++)
	vec(i) = readValue<double>(config, info, doc, name, i);

    return vec;
  }

  template<> VectorXi RlsDynamics::readVector(Config &config, Info &info, YAML::Node &doc, string name, int node, int size)
  {
    if(config.flag.debug) DEBUG;

    VectorXi vec = VectorXi::Zero(size);

    for(int i=0; i<size; i++)
      vec(i) = readValue<int>(config, info, doc, name, node, i);

    return vec;
  }

  template<> VectorXd RlsDynamics::readVector(Config &config, Info &info, YAML::Node &doc, string name, int node, int size)
  {
    if(config.flag.debug) DEBUG;

    VectorXd vec = VectorXd::Zero(size);

    for(int i=0; i<size; i++)
      vec(i) = readValue<double>(config, info, doc, name, node, i);

      return vec;
  }
}
