#include "rlsVelocity.hpp"
#include "rlsAcceleration.hpp"

namespace RLS{
  class Controller:
    public RlsVelocity,
    public RlsAcceleration
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
