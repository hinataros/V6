/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

MatrixXd RLS::RlsDynamics::jacobian(Config &config, Info &info, TreeModel &model, int k)
{
  if(config.flag.debug) DEBUG;

  return jacobian(config, info, model, k, Vector3d::Zero());
}

MatrixXd RLS::RlsDynamics::jacobian(Config &config, Info &info, TreeModel &model, int k, Vector3d offset)
{
  if(config.flag.debug) DEBUG;

  MatrixXd J = MatrixXd::Zero(6, info.limb[k].dof);

  Vector3d eePos = model.limb[k].node[info.limb[k].dof].r + model.limb[k].node[info.limb[k].dof].R*offset;

  for(int j=0; j<info.limb[k].dof; j++)
    J.col(j) <<
      cross(model.limb[k].node[j].sw) * (eePos - model.limb[k].node[j].r),
      model.limb[k].node[j].sw;

  return J;
}
