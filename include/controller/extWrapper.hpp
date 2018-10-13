/**
   @author Sho Miyahara 2018
*/

#ifdef EXT
#include "_ext.hpp"
#endif

namespace RLS{
  class ExtWrapper{
  private:
#ifdef EXT
    Ext ext;
#endif

  public:
    void setControllerMap(RlsDynamics*);
  };
}

