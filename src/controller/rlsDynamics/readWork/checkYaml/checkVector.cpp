/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> VectorXd RlsDynamics::checkVector(YAML::Node &doc, string node, int seq, string name, VectorXd vec)
  {
    if(doc[node][seq][name].size())
      for(int i=0; i<vec.size(); i++)
        vec(i) = readValue<double>(doc, node, seq, name, i);

    else
      return vec;

    return vec;
  }

  template<> VectorXd RlsDynamics::checkVector(YAML::Node &doc, string node, int seq, string name, int limb, VectorXd vec)
  {
    if(doc[node][seq][name].size())
      for(int i=0, temp=0, size=0; i<limb; i++){
        if(size = doc[node][seq][name][i].size()){
          vec.segment(temp, size) = readVector<VectorXd>(doc, node, seq, name, i, size);
          temp += size;

        }else{
          try{
            temp += doc[node][seq][name][i].as<int>();
          }
          catch(...){cout << "checkVector() error..." << endl;return vec;}
        }
      }

    else
      return vec;

    return vec;
  }
}
