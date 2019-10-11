/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::kineticEnergy(RlsDynamics *io, const double &t)
{
  if(debug) DEBUG;

  static double Kpre = 0;

  MatrixXd MM = MatrixXd::Zero(io->info.model.dof.all,io->info.model.dof.all);

  MM <<
    io->model->M*Matrix3d::Identity(), Matrix3d::Zero(), MatrixXd::Zero(3, io->info.model.dof.joint),
    Matrix3d::Zero(), io->model->IC, io->model->HC,
    MatrixXd::Zero(io->info.model.dof.joint, 3), io->model->HC.transpose(), io->model->MthC;
  
  K = 0.5 * io->model->dqM.transpose() * MM * io->model->dqM;

  dK = (K - Kpre) / io->worldModel->dt;

  if(impact && !reflex){
    if(abs(dK) <= 0.001){
      impact = false;
      reflex = true;
      t_reflex = t;
      
      KpwBinit = io->fb.KpwB;
      KdwBinit = io->fb.KdwB;
    }
  }

  Kpre = K;
}
