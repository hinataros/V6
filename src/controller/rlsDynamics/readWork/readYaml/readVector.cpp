/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> VectorXi RlsDynamics::readVector(YAML::Node &doc, string node, int seq, string name, int size)
  {
    VectorXi vec = VectorXi::Zero(size);

    for(int i=0; i<size; i++)
      vec(i) = readValue<int>(doc, node, seq, name, i);

    return vec;
  }

  template<> VectorXd RlsDynamics::readVector(YAML::Node &doc, string node, int seq, string name, int size)
  {
    VectorXd vec = VectorXd::Zero(size);

    for(int i=0; i<size; i++)
      vec(i) = readValue<double>(doc, node, seq, name, i);

    return vec;
  }

  template<> VectorXi RlsDynamics::readVector(YAML::Node &doc, string node, int seq, string name, int i, int size)
  {
    VectorXi vec = VectorXi::Zero(size);

    for(int j=0; j<size; j++)
      vec(j) = readValue<int>(doc, node, seq, name, i, j);

    return vec;
  }

  template<> VectorXd RlsDynamics::readVector(YAML::Node &doc, string node, int seq, string name, int i, int size)
  {
    VectorXd vec = VectorXd::Zero(size);

    for(int j=0; j<size; j++)
      vec(j) = readValue<double>(doc, node, seq, name, i, j);

    return vec;
  }
}
