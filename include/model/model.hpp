#include "treeModel.hpp"

namespace RLS{
  class Model:
    public TreeModel{
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
