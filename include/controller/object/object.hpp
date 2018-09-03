/**
   @author Sho Miyahara 2017
*/

// #include "objectList.hpp"

namespace RLS{
  class Object{
  private:
    bool initialValueFlag;

    void initialValue(Model&);

  public:
    void initialize();
    VectorXd object(Config&, Model&, double&);
  };
}
