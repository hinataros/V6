/**
   @author Sho Miyahara 2018
*/

#include "rlsDynamics.hpp"

namespace RLS{
  class Controller{
  private:
    void makeRlsDynamics(const string&);

  public:
    int controllerNum;

    RlsDynamics *rlsDynamics;

    void initialize(const string&, Model&);
    void finalize();

    Controller(const string &path_yaml_controller, Model &model){
      initialize(path_yaml_controller, model);
    }

    ~Controller(){
      finalize();
    }
  };
}

