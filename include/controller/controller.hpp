/**
   @author Sho Miyahara 2017
*/

#include "rlsDynamics.hpp"

namespace RLS{
  class Controller:
    public RlsDynamics
  {
  private:
    void initialize(Config&, Info&);

    VectorXd u;

  public:
    VectorXd controller(Config&, Info&, Model&, double&);

    Controller(){}
    Controller(Config &config, Info &info){
      initialize(config, info);
    }
  };
}
