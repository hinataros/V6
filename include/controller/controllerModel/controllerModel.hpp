/**
   @author Sho Miyahara 2018
*/

#include "controllerTreeModel.hpp"

namespace RLS{
  class ControllerModel{
  private:
    const Info *info;

    void setModel(const Model&);

  public:
    const WorldModel *worldModel;
    ControllerTreeModel *treeModel;

    void initialize(Model&);
    void finalize();

    void update();
    void update(VectorXd&); //amiyata rkk

    // ControllerModel(const Info &info){
    //   initialize(info);
    // }

    // ~ControllerModel(){
    //   finalize();
    // }
  };
}
