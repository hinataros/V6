#ifndef SHAREDDATA_HPP_
#define SHAREDDATA_HPP_

namespace RLS{
  struct SharedData{
    double rR[3];
    double RR[9];
    double vR[3];
    double wR[3];
    double fR[3];
    double nR[3];
  };
}

#endif // SHAREDDATA_HPP_
