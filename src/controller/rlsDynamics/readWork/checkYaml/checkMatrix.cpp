/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

namespace RLS{
  template<> MatrixXd RlsDynamics::checkMatrix(YAML::Node &doc, string node, int seq, string name, MatrixXd A)
  {
    if(doc[node][seq][name].size())
      A = readVector<VectorXd>(doc, node, seq, name, A.diagonal().size()).asDiagonal();

    else{
      try{
        checkNode(doc, node, seq, name);
      }
      catch(...){return A;}

      for(int i=0; i<A.diagonal().size(); i++)
        A(i,i) = readValue<double>(doc, node, seq, name);
    }

    return A;
  }

  template<> MatrixXi RlsDynamics::checkMatrix(YAML::Node &doc, string node, int seq, string name, int limb, MatrixXi A)
  {
    if(doc[node][seq][name].size())
      for(int i=0, temp=0, size=0; i<limb; i++){
        if(size = doc[node][seq][name][i].size()){
          A.block(temp, temp, size, size) = readVector<VectorXi>(doc, node, seq, name, i, size).asDiagonal();
          temp += size;

        }else{
          try{
            temp += doc[node][seq][name][i].as<int>();
          }
          catch(...){cout << "checkMatrix() error..." << endl;return A;}
        }
      }

    else{
      try{
        checkNode(doc, node, seq, name);
      }
      catch(...){return A;}

      for(int i=0; i<A.diagonal().size(); i++)
        A(i,i) = readValue<int>(doc, node, seq, name);
    }

    return A;
  }

  template<> MatrixXd RlsDynamics::checkMatrix(YAML::Node &doc, string node, int seq, string name, int limb, MatrixXd A)
  {
    if(doc[node][seq][name].size())
      for(int i=0, temp=0, size=0; i<limb; i++){
        if(size = doc[node][seq][name][i].size()){
          A.block(temp, temp, size, size) = readVector<VectorXd>(doc, node, seq, name, i, size).asDiagonal();
          temp += size;

        }else{
          try{
            temp += doc[node][seq][name][i].as<int>();
          }
          catch(...){cout << "checkMatrix() error..." << endl;return A;}
        }
      }

    else{
      try{
        checkNode(doc, node, seq, name);
      }
      catch(...){return A;}

      for(int i=0; i<A.diagonal().size(); i++)
        A(i,i) = readValue<double>(doc, node, seq, name);
    }
    return A;
  }
}
