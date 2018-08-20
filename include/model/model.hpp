/**
   @author Sho Miyahara 2017
*/

#include "treeModel.hpp"
#include "rigidBodyModel.hpp"

namespace RLS{
  class Model{
  private:
  public:
    TreeModel hoap2;
    RigidBodyModel object;

    void readModel(Config&);
    void deleteModel(Config&);
    void update(const bool);

    Model(){}
    Model(Config& config){
      readModel(config);
    }
    // ~Model(){
    //   deleteNode(config);
    // }
  };
}
