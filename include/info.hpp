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

    // smiyahara: 良い名前が浮かばなかった
    struct Each{
      int all;
      int axis[6];
    };

    struct Contact{
      string name;
      int num;
      Each c;
      Each m;
    } contact;

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
      // smiyahara: 初期化の位置めちゃびみょー
      bool contact;
      int c;
      int m;
    } *limb;

    void initialize(Config&);
    void finalize(Config&);

    Info(){}
    Info(Config &config){
      initialize(config);
    }
  };
}
