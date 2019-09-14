/**
   @author Sho Miyahara 2018
*/

#ifndef QUATERNION_HPP_
#define QUATERNION_HPP_

#include <eigen3/Eigen/Dense>

namespace RLS{
  class Quaternion4d{
  private:
  public:
    double w;
    Eigen::Vector3d v;

    Quaternion4d operator=(Quaternion4d);
    Quaternion4d operator+(Quaternion4d);
    Quaternion4d operator-(Quaternion4d);
    Quaternion4d operator*(Quaternion4d);
    Quaternion4d operator*=(Quaternion4d);
    Quaternion4d operator/(Quaternion4d);
    Quaternion4d operator/=(Quaternion4d);

    int sign(double);

    static Quaternion4d Zero();
    static Quaternion4d Identity();
    static Quaternion4d xi2q(const Eigen::Vector3d&);
    static Quaternion4d R2q(const Eigen::Matrix3d&);

    static Eigen::Vector3d dq2w(const Quaternion4d&, const Quaternion4d&);
    static Eigen::Vector3d ddq2dw(const Quaternion4d&, const Quaternion4d&, const Quaternion4d&);

    Eigen::Matrix3d rotationMatrix();
  };
}

#endif // QUATERNION_HPP_
