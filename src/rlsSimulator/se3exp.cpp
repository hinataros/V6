/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::se3exp(Config &config, Vector3d &r, Matrix3d &R, Vector3d vo, Vector3d w, double dt)
{
  if(config.flag.debug) DEBUG;

  double norm_w = w.norm();

  if(norm_w==0.)
    r = rB + dt*vo;

  else{
    double th = dt*norm_w;
    Vector3d w_n = w/norm_w;
    Vector3d vo_n = vo/norm_w;
    Matrix3d rot(AngleAxisd(th, w_n));

    r = rot*rB + (Matrix3d::Identity() - rot)*cross(w_n)*vo_n + (w_n*w_n.transpose())*vo_n*th;
    R = rot*RB;
  }
}
