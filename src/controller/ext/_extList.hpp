/**
   @author Sho Miyahara 2018
*/

#ifndef EXTLIST_HPP_
#define EXTLIST_HPP_

namespace RLS{
  class ExtList{
  public:
    VectorXd lC;
    VectorXd lCRB;
    VectorXd lCAM;
    VectorXd dlC;
    VectorXd dlCRB;
    VectorXd dlCAM;

    VectorXd wC;
    VectorXd Dw;
    VectorXd wB;

    VectorXd DwLower;
    VectorXd DwUpper;

    VectorXd dwCRef;
    VectorXd dDwRef;
    VectorXd dwBRef;

    VectorXd dlCRefRoot;
    VectorXd dlCRefMotion;
    VectorXd dlCRefError;
    VectorXd dlCComponent;

    VectorXd jointLimitGradient;

    Vector3d WCRB;
    Vector3d dWCRB;
  };
}

#endif // EXTLIST_HPP_
