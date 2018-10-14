/**
   @author Sho Miyahara 2018
*/

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "info.hpp"
#include "worldModel.hpp"
#include "treeModel.hpp"
#include "rigidBodyModel.hpp"

namespace RLS{
  class Model{
  private:
  public:
    WorldModel worldModel;

    Info info;

    TreeModel *treeModel;
    RigidBodyModel *rigidBodyModel;

    void initialize(const string&, const string&);
    void finalize();
    void initializeInfo();
    void makeModel(const string&);
    void setID();
    void initialUpdate();
    void update();

    Model(){}
    Model(const string &dir_share, const string &path_yaml_model){
      initialize(dir_share, path_yaml_model);
    }

#ifndef RLSDYNAMICSRTC
    ~Model(){
      finalize();
    }
#endif
  };
}

#endif // MODEL_HPP_
