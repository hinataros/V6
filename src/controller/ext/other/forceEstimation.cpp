/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::forceEstimation(RlsDynamics *io, const double &t)
{
  if(debug) DEBUG;

  static double g = 9.81;
  Matrix2d S;
  S <<
    0, 1,
    -1, 0;

  static VectorXd rCPre = io->model->rC;
  VectorXd dpRefPre = io->dpRef;
  VectorXd dlCRefPre = io->dlCRef;

  Vector2d rpRefPre = rCPre.head(2) - (dpRefPre.head(2)*rCPre(2) - S*dlCRefPre.head(2))/(io->model->M*g);

  Vector3d fext = Vector3d::Zero();
  fext.head(2) = (io->model->M*g)/io->model->rC(2) * (io->model->rp - rpRefPre);
  // fext(2) = (io->model->cal_Fsensor(2)+io->model->cal_Fsensor(8)) - ((io->model->M*g) - dpRefPre(2)); 

  if(!impact && !reflex){
    if(abs(fext.norm()) >= 3){
      impact = true;
      t_impact = t;
      
      KpwBinit = io->fb.KpwB;
      KdwBinit = io->fb.KdwB;
    }
  }

  rCPre = io->model->rC;

}
