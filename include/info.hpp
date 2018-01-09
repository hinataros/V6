/**
   @author Sho Miyahara 2017
*/

#include "common.hpp"

namespace RLS{
  class Info:
    virtual public Common{
  private:
  public:
    struct Sim{
      double t0;
      double tf;
      double dt;
      double n;

      // state
      double trev;
      int state;
      // recovery phase
      double trecf;

      // sequence
      double twf;
      double tw0;
      int phase;
    } sim;

    struct Value{
      int node;
      int joint;
      int all;
    } value;

    struct Dof{
      int all;
      int joint;
    } dof;

    struct Limb{
      int value;
      int dof;
    } *limb;

    void initialize(Config&);
    void finalize(Config&);

    Info(){}
    Info(Config &config){
      initialize(config);
    }
  };
}
