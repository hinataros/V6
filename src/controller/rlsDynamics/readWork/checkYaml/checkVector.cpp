#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> VectorXd RlsDynamics::checkVector(Config &config, Info &info, YAML::Node &doc, string name, VectorXd vec)
  {
    if(config.flag.debug) DEBUG;

    if(doc["Work"][info.sim.phase][name].size())
      for(int i=0; i<vec.size(); i++)
	vec(i) = readValue<double>(config, info, doc, name, i);

    else
      return vec;

    return vec;
  }

  template<> VectorXd RlsDynamics::checkVector(Config &config, Info &info, YAML::Node &doc, string name, int node, VectorXd vec)
  {
    if(config.flag.debug) DEBUG;

    if(doc["Work"][info.sim.phase][name].size())
      for(int i=0, temp=0, size=0; i<node; i++){
	if(size = doc["Work"][info.sim.phase][name][i].size()){
	  vec.segment(temp, size) = readVector<VectorXd>(config, info, doc, name, i, size);
	  temp += size;

	}else{
	  try{
	    temp += doc["Work"][info.sim.phase][name][i].as<int>();
	  }
	  catch(...){cout << "checkVector() error..." << endl;return vec;}
	}
      }

    else
      return vec;

    return vec;
  }
}
