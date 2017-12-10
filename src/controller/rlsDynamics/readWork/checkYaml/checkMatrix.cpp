#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> MatrixXd RlsDynamics::checkMatrix(Config &config, Info &info, YAML::Node &doc, string name, MatrixXd A)
  {
    if(config.flag.debug) DEBUG;

    if(doc["Work"][info.sim.phase][name].size())
      A = readVector<VectorXd>(config, info, doc, name, A.diagonal().size()).asDiagonal();

    else{
      try{
	checkNode(config, info, doc, name);
      }
      catch(...){return A;}

      for(int i=0; i<A.diagonal().size(); i++)
	A(i,i) = readValue<double>(config, info, doc, name);
    }

    return A;
  }

  template<> MatrixXi RlsDynamics::checkMatrix(Config &config, Info &info, YAML::Node &doc, string name, int node, MatrixXi A)
  {
    if(config.flag.debug) DEBUG;

    if(doc["Work"][info.sim.phase][name].size())
      for(int i=0, temp=0, size=0; i<node; i++){
	if(size = doc["Work"][info.sim.phase][name][i].size()){
	  A.block(temp, temp, size, size) = readVector<VectorXi>(config, info, doc, name, i, size).asDiagonal();
	  temp += size;

	}else{
	  try{
	    temp += doc["Work"][info.sim.phase][name][i].as<int>();
	  }
	  catch(...){cout << "checkMatrix() error..." << endl;return A;}
	}
      }

    else{
      try{
	checkNode(config, info, doc, name);
      }
      catch(...){return A;}

      for(int i=0; i<A.diagonal().size(); i++)
  	A(i,i) = readValue<int>(config, info, doc, name);
    }

    return A;
  }

  template<> MatrixXd RlsDynamics::checkMatrix(Config &config, Info &info, YAML::Node &doc, string name, int node, MatrixXd A)
  {
    if(config.flag.debug) DEBUG;

    if(doc["Work"][info.sim.phase][name].size())
      for(int i=0, temp=0, size=0; i<node; i++){
	if(size = doc["Work"][info.sim.phase][name][i].size()){
	  A.block(temp, temp, size, size) = readVector<VectorXd>(config, info, doc, name, i, size).asDiagonal();
	  temp += size;

	}else{
	  try{
	    temp += doc["Work"][info.sim.phase][name][i].as<int>();
	  }
	  catch(...){cout << "checkMatrix() error..." << endl;return A;}
	}
      }

    else{
      try{
	checkNode(config, info, doc, name);
      }
      catch(...){return A;}

      for(int i=0; i<A.diagonal().size(); i++)
  	A(i,i) = readValue<double>(config, info, doc, name);
    }
    return A;
  }
}
