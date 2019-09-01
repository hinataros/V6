#include "config.hpp"
#include "common.hpp"

#include "walkingFunction.hpp"
#include "comWayOpt.hpp"


namespace RLS{ // staticクラスメンバ変数は別に定義し直さないといけないらしい
  int comWayOpt::Tnum, comWayOpt::rCnum, comWayOpt::ipDim;
  double comWayOpt::wX;
  VectorXd comWayOpt::comDes;
  MatrixXd comWayOpt::vwp,  comWayOpt::Cp, comWayOpt::Cm;
  MatrixXd comWayOpt::WT, comWayOpt::WC, comWayOpt::WV;

  WalkingFunction comWayOpt::wf; // 嘘だろ
}

VectorXd a2v(int, double*);

void RLS::comWayOpt::objection(int nparam, int j, double *x, double *fj, void *cd)
{
  if(CWO_DEBUG) DEBUG;

  VectorXd X = a2v(nparam, x);
  // cout << "obj" << endl;
  // o(X);

  MatrixXd comWP = calcCwp(X, calcDwp(X));
  VectorXd cwp = VectorXd::Zero(3*Tnum);
  for(int i=1; i<rCnum; i++) // rC(0)はいらない
    cwp.segment((i-1)*3, 3) = comWP.col(i);

  VectorXd ans = 0.5 * X.head(Tnum).transpose() * WT * X.head(Tnum) + 0.5 * (cwp - comDes).transpose() * WC * (cwp - comDes);
  *fj = ans(0);

  return;
}

void RLS::comWayOpt::gradientObjection(int nparam, int j, double *x, double *gradfj, void (*dummy)(int, int, double*, double*, void*), void *cd)
{
  if(CWO_DEBUG) DEBUG;
  // cout << "gradobj" << endl;

  int i,k;

  VectorXd X = a2v(nparam, x);
  VectorXd ans;

  for(i=0; i<nparam; i++)
    gradfj[i] = WT(i,i)*X(i);

  MatrixXd dwp = calcDwp(X);
  MatrixXd cwp = calcCwp(X, dwp);

  MatrixXd dTnDwp, dTnCwp;
  Matrix3d WCk;
  Vector3d eCk;
  for(i=0; i<nparam; i++) {
    dTnDwp = calcdTnDwp(i, X, dwp);
    dTnCwp = calcdTnCwp(i, X, cwp, dwp, dTnDwp);

    for(k=1; k<nparam; k++){ // k=0では0
      WCk = WC.block(k,k, 3,3);
      eCk = cwp.col(k) - comDes.segment(k*3, 3);
      ans = 0.5*dTnCwp.col(k).transpose()*WCk*eCk + 0.5*eCk.transpose()*WCk*dTnCwp.col(k);
      gradfj[i] += ans(0);
    }
  }

  return;
}


void RLS::comWayOpt::constraint(int nparam, int j, double *x, double *gj, void *cd)
{
  if(CWO_DEBUG) DEBUG;

  *gj = -x[j-1];  //<= 0

  return;
}

void RLS::comWayOpt::gradientConstraint(int nparam, int j, double *x, double *gradgj, void (*dummy)(int, int, double*, double*, void*), void *cd)
{
  if(CWO_DEBUG) DEBUG;

  for(int i=0; i<nparam; i++){
    if(i==(j-1))
      gradgj[i] = -1;
    else
    gradgj[i] = 0;
  }

  return;
}
