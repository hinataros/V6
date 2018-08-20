/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::analyticalDynamics()
{
  if(debug) DEBUG;

  // ********************************************
  Matrix3d Mv = all.m*Matrix3d::Identity();
  Matrix3d dMv = Matrix3d::Zero();

  // ********************************************
  Matrix3d Mvw = -all.m*cross(all.rC - link[info.rootNode].r);
  Matrix3d dMvw = -all.m*cross(all.vC - link[info.rootNode].v);

  // ********************************************
  Matrix3d IB = Matrix3d::Zero();
  Matrix3d rB2ix = Matrix3d::Zero();

  Matrix3d dIB = Matrix3d::Zero();
  Matrix3d drB2ix = Matrix3d::Zero();

  MatrixXd linkHv = MatrixXd::Zero(3,info.linkNum);
  MatrixXd linkHB = MatrixXd::Zero(3,info.linkNum);
  MatrixXd linkMth = MatrixXd::Zero(info.linkNum,info.linkNum);

  Matrix3d dIi = Matrix3d::Zero();
  MatrixXd linkdHv = MatrixXd::Zero(3,info.linkNum);
  MatrixXd linkdHB = MatrixXd::Zero(3,info.linkNum);
  MatrixXd linkdMth = MatrixXd::Zero(info.linkNum,info.linkNum);

  for(int i=0; i<info.linkNum; i++){
    rB2ix = cross(link[i].rC - link[info.rootNode].r);
    IB += link[i].I;
    IB += link[i].m*rB2ix.transpose()*rB2ix;

    drB2ix = cross(link[i].vC - link[info.rootNode].v);
    dIB += cross(link[i].w)*link[i].I + link[i].I*cross(link[i].w).transpose();
    dIB += link[i].m*drB2ix.transpose()*rB2ix + link[i].m*rB2ix.transpose()*drB2ix;

    // smiyahara:
    // if link[i].ri2C = 0 => link[i].rC = link[i].r
    // if link[i].jointAxis = "no axis" => link[i].sw = 0
    for(int j=i; j!=info.rootNode; j=link[j].parentNode){
      // if j=0 => through. Note that no probrem even if through here.
      link[i].Jvi.col(j) = cross(link[j].sw)*(link[i].rC - link[j].r);
      link[i].dJvi.col(j) = cross(link[j].dsw)*(link[i].rC - link[j].r) + cross(link[j].sw)*(link[i].vC - link[j].v);

      link[i].Jwi.col(j) = link[j].sw;
      link[i].dJwi.col(j) = link[j].dsw;
    }

    linkHv += link[i].m*link[i].Jvi;
    linkdHv += link[i].m*link[i].dJvi;

    linkHB += link[i].I*link[i].Jwi + link[i].m*rB2ix*link[i].Jvi;
    dIi = cross(link[i].w)*link[i].I + link[i].I*cross(link[i].w).transpose();
    linkdHB += dIi*link[i].Jwi + link[i].I*link[i].dJwi + link[i].m*rB2ix*link[i].dJvi + link[i].m*drB2ix*link[i].Jvi;

    linkMth += link[i].m*link[i].Jvi.transpose()*link[i].Jvi + link[i].Jwi.transpose()*link[i].I*link[i].Jwi;
    linkdMth += link[i].m*link[i].Jvi.transpose()*link[i].dJvi + link[i].m*link[i].dJvi.transpose()*link[i].Jvi
      + link[i].Jwi.transpose()*link[i].I*link[i].dJwi + link[i].Jwi.transpose()*dIi*link[i].Jwi + link[i].dJwi.transpose()*link[i].I*link[i].Jwi;
  }

  // ********************************************
  MatrixXd Hv = stateMatrixFilter(false,true, linkHv);
  MatrixXd HB = stateMatrixFilter(false,true, linkHB);
  MatrixXd Mth = stateMatrixFilter(true,true, linkMth);

  MatrixXd M = MatrixXd::Zero(info.dof.all,info.dof.all);
  M <<
    Mv,Mvw,Hv,
    Mvw.transpose(),IB,HB,
    Hv.transpose(),HB.transpose(),Mth;

  MatrixXd dHv = stateMatrixFilter(false,true, linkdHv);
  MatrixXd dHB = stateMatrixFilter(false,true, linkdHB);
  MatrixXd dMth = stateMatrixFilter(true,true, linkdMth);

  MatrixXd dM = MatrixXd::Zero(info.dof.all,info.dof.all);
  dM <<
    dMv,dMvw,dHv,
    dMvw.transpose(),dIB,dHB,
    dHv.transpose(),dHB.transpose(),dMth;

  Vector3d gf = all.m*ag;
  Vector3d gm = all.m*cross(all.rC - link[info.rootNode].r)*ag;
  VectorXd gth = Hv.transpose()*ag;

  VectorXd g = VectorXd::Zero(info.dof.all);
  g <<
    -gf,
    -gm,
    -gth;

  all.dM=dM;
  // ********************************************


  // centroidal
  Matrix3d rC2Bx = cross(link[info.rootNode].r - all.rC);
  Matrix3d drC2Bx = cross(link[info.rootNode].v - all.vC);

  Matrix3d IC = IB - all.m*rC2Bx*rC2Bx.transpose();
  Matrix3d dIC = dIB - all.m*drC2Bx*rC2Bx.transpose() - all.m*rC2Bx*drC2Bx.transpose();

  MatrixXd JB2C = Hv / all.m;
  MatrixXd dJB2C = dHv / all.m;

  MatrixXd HC = HB - all.m*rC2Bx.transpose()*JB2C;
  MatrixXd dHC = dHB - all.m*drC2Bx.transpose()*JB2C - all.m*rC2Bx.transpose()*dJB2C;

  MatrixXd MthC = Mth - all.m*JB2C.transpose()*JB2C;
  MatrixXd dMthC = dMth - all.m*dJB2C.transpose()*JB2C - all.m*JB2C.transpose()*dJB2C;

  MatrixXd MM = MatrixXd::Zero(info.dof.all,info.dof.all);
  MM <<
    Mv,Matrix3d::Zero(),MatrixXd::Zero(3,info.dof.joint),
    Matrix3d::Zero().transpose(),IC,HC,
    MatrixXd::Zero(3,info.dof.joint).transpose(),HC.transpose(),MthC;

  MatrixXd dMM = MatrixXd::Zero(info.dof.all,info.dof.all);
  dMM <<
    dMv,Matrix3d::Zero(),MatrixXd::Zero(3,info.dof.joint),
    Matrix3d::Zero().transpose(),dIC,dHC,
    MatrixXd::Zero(3,info.dof.joint).transpose(),dHC.transpose(),dMthC;

  all.JB2C=JB2C;
  all.dJB2C=dJB2C;
  all.MM=MM;
  all.dMM=dMM;
}
