/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

MatrixXd RLS::RlsDynamics::weight(Config &config, Info &info, Model &model, Vector3d rIndex)
{
  if(config.flag.debug) DEBUG;

  MatrixXd W = MatrixXd::Identity(6*info.value.joint, 6*info.value.joint);

  Vector3d Dr = model.hoap2.limb[1].node[info.limb[1].dof].r - model.hoap2.limb[2].node[info.limb[2].dof].r;

  Vector3d Drk;
  double wkz;

  double wz = 0.;
  double wzTilde;

  // only foot support
  for(int i=0; i<info.value.joint; i++){
    Drk = rIndex - model.hoap2.limb[i+1].node[info.limb[i+1].dof].r;
    wkz = abs(Dr.head(2).transpose()*Drk.head(2));

    wz += wkz;

    for(int j=0; j<6; j++)
      W(6*i+j,6*i+j) = wkz;
  }

  wzTilde = 1/wz;

  return W;
}
