#include "treeModel.hpp"
#include "rigidBodyModel.hpp"

namespace RLS{
  class Model:
    public TreeModel, public RigidBodyModel{
  private:
  public:
    void readModel(Config&, Info&);
    void deleteModel(Config&, Info&);
    void update(Config&, Info&);

    Model(){}
    Model(Config& config, Info &info){
      readModel(config, info);
    }
    // ~Model(){
    //   deleteNode(config);
    // }
  };
}
