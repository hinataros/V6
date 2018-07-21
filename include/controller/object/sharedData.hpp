/**
   @author Sho Miyahara 2017
*/

#ifndef SHAREDDATA_HPP_
#define SHAREDDATA_HPP_

namespace RLS{
  struct Root{
    double r[3];
    double R[9];
    double v[3];
    double w[3];
    double f[3];
    double n[3];
  };

  struct SharedData{
    Root root;
  };
}

#endif // SHAREDDATA_HPP_
