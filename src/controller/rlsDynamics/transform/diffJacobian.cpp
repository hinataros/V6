/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

MatrixXd RLS::RlsDynamics::diffJacobian(Config &config, Info &info, TreeModel &model, int k)
{
  if(config.flag.debug) DEBUG;

  return diffJacobian(config, info, model, k, Vector3d::Zero());
}

MatrixXd RLS::RlsDynamics::diffJacobian(Config &config, Info &info, TreeModel &model, int k, Vector3d offset)
{
  if(config.flag.debug) DEBUG;

  MatrixXd dJ = MatrixXd::Zero(6, info.limb[k].dof);

  Vector3d eePos = model.limb[k].node[info.limb[k].dof].r + model.limb[k].node[info.limb[k].dof].R*offset;
  Vector3d eeVel = model.limb[k].node[info.limb[k].dof].v + w2dR(model.limb[k].node[info.limb[k].dof].w, model.limb[k].node[info.limb[k].dof].R)*offset;

  for(int j=0; j<info.limb[k].dof; j++)
    dJ.col(j) <<
      cross(model.limb[k].node[j].dsw)*(eePos - model.limb[k].node[j].r) + cross(model.limb[k].node[j].sw)*(eeVel - model.limb[k].node[j].v),
      model.limb[k].node[j].dsw;

  return dJ;
}

