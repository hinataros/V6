/**
   @author Sho Miyahara 2017
*/

// #include "objectList.hpp"

namespace RLS{
  class Object{
  private:
    bool initialValueFlag;

    void initialValue(Config&, Info&, Model&);

  public:
    void initialize(Config&, Info&);
    VectorXd object(Config&, Info&, Model&, double&);
  };
}
