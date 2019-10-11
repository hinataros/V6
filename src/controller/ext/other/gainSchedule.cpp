/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::gainSchedule(RlsDynamics *io, const double &t)
{
  if(debug) DEBUG;

  static double dt_impact = 0.02;
  static double dt_reflex = 0.2;

  static double KpwBlow = 0;
  static double KdwBlow = 0;

  static double KpwBmid = 30;
  static double KdwBmid = 5;

  static double KpwBhigh = 300;
  static double KdwBhigh = 50;

  forceEstimation(io, t);
  kineticEnergy(io, t);

  Vector3d des = VectorXd::Zero(3);
  if(impact){
    for(int i=0; i<3; i++){
      des = makeSpline3(t_impact, t_impact+dt_impact, KpwBinit(i,i), KpwBlow);
      io->fb.KpwB(i,i) = des(0);
    }
    for(int i=0; i<3; i++){
      des = makeSpline3(t_impact, t_impact+dt_impact, KdwBinit(i,i), KdwBlow);
      io->fb.KdwB(i,i) = des(0);
    }
  }

  else if(reflex){
    // for(int i=0; i<3; i++){
    //   des = makeSpline3(t_reflex, t_reflex+dt_reflex, KpwBinit(i,i), KpwBmid);
    //   io->fb.KpwB(i,i) = des(0);
    // }
    for(int i=0; i<3; i++){
      des = makeSpline3(t_reflex, t_reflex+dt_reflex, KdwBinit(i,i), KdwBmid);
      io->fb.KdwB(i,i) = des(0);
    }
  }

}
