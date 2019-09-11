/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::bwcDistribution()
{
  if(debug) DEBUG;

  int nc = 4;
  int np = 4;
  int nk = 2;

  double mu = 1.0;
  double mucopper = 1.;

  MatrixXd VquadrangularPyramid[nk];
  for(int i=0; i<nk; i++)
    VquadrangularPyramid[i] = MatrixXd::Zero(3,nc);

  VquadrangularPyramid[0] <<
    mucopper, -mucopper, -mucopper, mucopper,
    mucopper, mucopper, -mucopper, -mucopper,
    1., 1., 1., 1.;

  VquadrangularPyramid[1] <<
    mu, -mu, -mu, mu,
    mu, mu, -mu, -mu,
    1., 1., 1., 1.;

  // o(VquadrangularPyramid);

  Vector3d rF2p[np];
  for(int i=0; i<np; i++)
    rF2p[i] = Vector3d::Zero();

  // only "np = 4"
  rF2p[0] << 0.058, 0.0315, 0.;
  rF2p[1] << -0.04, 0.0315, 0.;
  rF2p[2] << -0.04, -0.0315, 0.;
  rF2p[3] << 0.058, -0.0315, 0.;

  MatrixXd VFCF[nk];
  MatrixXd bb_Tp2F_f[nk];
  for(int i=0; i<nk; i++){
    VFCF[i] = MatrixXd::Zero(3*np,nc*np);
    bb_Tp2F_f[i] = MatrixXd::Zero(6,3*np);
  }

  for(int i=0; i<nk; i++)
    for(int j=0; j<np; j++){
      VFCF[i].block(3*j,nc*j,3,nc) = VquadrangularPyramid[i];

      bb_Tp2F_f[i].block(0,3*j,6,3) <<
        Matrix3d::Identity(),
        -cross(rF2p[j]);
    }

  // o(VFCF[0]);
  // o(VFCF[1]);
  // o(bb_Tp2F_f[0]);
  // o(bb_Tp2F_f[1]);

  MatrixXd VCWC = MatrixXd::Zero(6*nk,nk*nc*np);
  for(int i=0; i<nk; i++)
    VCWC.block(6*i,nc*np*i,6,nc*np) = bb_Tp2F_f[i]*VFCF[i];

  // o(VCWC);

  MatrixXd VBWC = MatrixXd::Zero(6,nk*nc*np);
  VBWC = constraintModel.mbb_CcM*VCWC;

  // o(VBWC);
  VectorXd lambda = pInv(VBWC)*(cal_dLCRef + model->cal_GC);
  // o(lamda);

  cal_FcBarRef = VCWC*lambda;

  MatrixXd Winv = VCWC*VCWC.transpose();

  // o(Winv);

  VectorXd temp = Winv*constraintModel.mbb_CcM.transpose()*((constraintModel.mbb_CcM*Winv*constraintModel.mbb_CcM.transpose()).inverse())*(cal_dLCRef + model->cal_GC);

  // o(cal_FcBarRef);

  // Vector2d recmp = (des.rXDes - des.drXDes/model->wX).head(2);
  // MatrixXd Wecmpc = h_weight(recmp);

  // cal_FcBarRef =
  //   pInv(constraintModel.mbb_CcM, Wecmpc)*(cal_dLCRef + model->cal_GC)
  //   + N(constraintModel.mbb_CcM)*VCWC*lambda;

  // o(cal_FcBarRef);
  // gc;
}
