#include "config.hpp"
#include "common.hpp"
#include "model.hpp"

#include "postureGenerator.hpp"

#include <math.h>


void RLS::postureGenerator::makeFuncCoef(double *p1, double *p2, double *ab)
{
  ab[0] = (p2[1] - p1[1]) / (p2[0] - p1[0]);
  ab[1] = p1[1] - ab[0] * p1[0];
}

bool RLS::postureGenerator::inTriangle(double *p1, double *p2, double *p3, double *pEval) //中にあれば1 でなければ0
{
  double func[2], sig[3][2];

  makeFuncCoef(p1, p2, func);
  sig[0][0] = p3[1] - (func[0] * p3[0] + func[1]);
  sig[0][1] = pEval[1] - (func[0] * pEval[0] + func[1]);
  makeFuncCoef(p2, p3, func);
  sig[1][0] = p1[1] - (func[0] * p1[0] + func[1]);
  sig[1][1] = pEval[1] - (func[0] * pEval[0] + func[1]);
  makeFuncCoef(p3, p1, func);
  sig[2][0] = p2[1] - (func[0] * p2[0] + func[1]);
  sig[2][1] = pEval[1] - (func[0] * pEval[0] + func[1]);

  for(int i=0; i<3; i++) {
    if(abs(sig[i][1]) <= 1.E-9)
      return 1;
    else if(abs(sig[i][0]) <= 1.E-9)
      return 0;
  }

  if(sig[0][0]*sig[0][1] > 0 && sig[1][0]*sig[1][1] > 0 && sig[2][0]*sig[2][1] > 0)
    return 1;

  //else
  return 0;

}

void RLS::postureGenerator::convexFull(double *p, int num) //p[num][2]
{
  bool pIn[num];
  for(int i(0); i<num; i++)
    pIn[i] = 1;

  for(int i(0); i<num-2; i++) {
    if(pIn[i] == 0)
      continue;
    for(int j(i+1); j<num-1; j++) {
      if(pIn[j] == 0)
        continue;
      for(int k(0); k<num; k++) {
        if(pIn[k] == 0)
          continue;
        for(int l(0); l<num; l++) {
          if(pIn[l]!=0 && l!=i && l!=j && l!=k)
            pIn[l] = inTriangle(p+(2*i), p+(2*j), p+(2*k), p+(2*l));
        }
      }
    }
  }

}

VectorXd RLS::postureGenerator::calcCoM(double *x)
{
  // int i,j;
  // int cur=0;
  //
  // MatrixXd Rk[5][8], RB;
  // VectorXd rk[5][8], rB, rCk[5][8], rC;
  //
  // for(i=0;i<5;i++)
  //   for(j=0;j<8;j++) {
  //     jR[i][j] = MatrixXd::Zero(3,3);
  //     rk[i][j] = VectorXd::Zero(3);
  //     rCk[i][j] = VectorXd::Zero(3);
  //   }
  // RB = MatrixXd::Identity(3,3);
  // rC = rB = VectorXd::Zero(3);
  //
  // cur=0;
  // for(i=1; i<limbs; i++){
  //   Rk[i][0] = RB*R(jointType[i][0], x[cur]); //RB計算なし
  //   rk[i][0] = rB + RB*lk[i][0]; //rB計算なし
  //
  //   for(j=1; j<dof[i]; j++){
  //     Rk[i][j] = Rk[i][j-1]*R(jTk[i][j], x[cur+j]);
  //     rk[i][j] = rk[i][j-1] + Rk[i][j-1]*lk[i][j];
  //   }
  //
  //   Rk[i][dof[i]] = Rk[i][dof[i]-1];
  //   rk[i][dof[i]] = rk[dof[i]-1] + Rk[i][dof[i]-1]*lk[i][dof[i]];
  //
  //   cur += dof[i];
  // }
  //
  // RB = REE[fixed] * Rk[fixed][dof[fixed]].transpose();
  // rB = rEE[fixed] - rk[fixed][dof[fixed]];
  //
  // //RB,rb include
  // for(i=1; i<limbs; i++){
  //   for(j=0; j<dof[i]; j++){
  //     Rk[i][j] = RB * Rk[i][j];
  //     rk[i][j] = rB + rk[i][j];
  //
  //     rCk[i][j] = rk[i][j] + Rk[i][j]*ri2C[i][j];
  //     rC += (rCk[i][j]*mk[i][j])/mall;
  //   }
  //
  //   Rk[i][dof[i]] = RB * Rk[i][dof[i]];
  //   rk[i][dof[i]] = rB + rk[dof[i]];
  //
  //   rCk[i][[dof[i]]] = rk[i][dof[i]] + Rk[i][dof[i]]*r2Ck[i][dof[i]];
  //   rC += (rCk[i][dof[i]]*mk[i][dof[i]])/mall;
  // }
  //
  // rCk[0][0] = rB + RB*r2Ck;[0][0];
  // rC += (rCk[0][0]*mk[0][0])/mall; //base CoM

  return VectorXd::Zero(3);
}


VectorXd RLS::postureGenerator::calcdCoM(double *x)
{
  // int i,j;
  // int cur=0;// smiyahara: 無いなこれは...
  // MatrixXd Rk[5][8], RB,  dRk[5][8], dRB;
  // VectorXd drk[5][8], drB, drCk[5][8], drC;
  //
  // for(i=0;i<5;i++)
  //   for(j=0;j<8;j++) {
  //     jR[i][j] = MatrixXd::Zero(3,3);
  //     rk[i][j] = VectorXd::Zero(3);
  //     rCk[i][j] = VectorXd::Zero(3);
  //   }
  // RB = MatrixXd::Identity(3,3);
  //
  // cur=0;
  // for(i=1; i<limbs; i++){
  //   Rk[i][0] = RB*R(jointType[i][0], x[cur]); //RB計算なし
  //   dRk[i][0] = dRB*R(jointType[i][0], x[cur]) + RB*dR(jointType[i][0], x[cur]); //dRB計算なし
  //   rk[i][0] = drB + dRB*lk[i][0]; //drB計算なし
  //
  //   for(j=1; j<dof[i]; j++){
  //     Rk[i][j] = Rk[i][j-1]*R(jTk[i][j], x[cur+j]);
  //     dRk[i][j] = dRk[i][j-1]*R(jTk[i][j], x[cur+j]) + Rk[i][j-1]*dR(jTk[i][j], x[cur+j]);
  //     drk[i][j] = drk[i][j-1] + dRk[i][j-1]*lk[i][j];
  //   }
  //
  //   Rk[i][dof[i]] = Rk[i][dof[i]-1];
  //   dRk[i][dof[i]] = dRk[i][dof[i]-1];
  //   drk[i][dof[i]] = drk[dof[i]-1] + dRk[i][dof[i]-1]*lk[i][dof[i]];
  //
  //   cur += dof[i];
  // }
  //
  // RB = REE[fixed] * Rk[fixed][dof[fixed]].transpose();
  // dRB = REE[fixed] * dRk[fixed][dof[fixed]].transpose();
  // drB = - drk[fixed][dof[fixed]];
  //
  // //RB,rb include
  // for(i=1; i<limbs; i++){
  //   for(j=0; j<dof[i]; j++){
  //     Rk[i][j] = RB * Rk[i][j];
  //     dRk[i][0] = dRB*R(jointType[i][0], x[cur]) + RB*dR(jointType[i][0], x[cur]); //dRB計算なし
  //     rk[i][j] = rB + rk[i][j];
  //
  //     rCk[i][j] = rk[i][j] + Rk[i][j]*ri2C[i][j];
  //     rC += (rCk[i][j]*mk[i][j])/mall;
  //   }
  //
  //   Rk[i][dof[i]] = RB * Rk[i][dof[i]];
  //   rk[i][dof[i]] = rB + rk[dof[i]];
  //
  //   rCk[i][[dof[i]]] = rk[i][dof[i]] + Rk[i][dof[i]]*r2Ck[i][dof[i]];
  //   rC += (rCk[i][dof[i]]*mk[i][dof[i]])/mall;
  // }
  //
  // rCk[0][0] = rB + RB*r2Ck[0][0];
  // rC += (rCk[0][0]*mk[0][0])/mall; //base CoM

  return VectorXd::Zero(3);

}
