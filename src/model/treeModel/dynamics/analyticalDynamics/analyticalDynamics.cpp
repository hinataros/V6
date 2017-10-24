#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::analyticalDynamics(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  // ********************************************
  Matrix3d Mv = Matrix3d::Zero();
  Mv = all.m*Matrix3d::Identity();
  // diff
  Matrix3d dMv = Matrix3d::Zero();

  // ********************************************
  Matrix3d Mvw = Matrix3d::Zero();
  Mvw = -all.m*cross(all.rC - limb[0].node[0].r);
  // diff
  Matrix3d dMvw = Matrix3d::Zero();
  dMvw = -all.m*cross(all.vC - limb[0].node[0].v);

  // ********************************************
  Matrix3d IB = Matrix3d::Zero();
  Matrix3d rB2ix = Matrix3d::Zero();
  // diff
  Matrix3d dIB = Matrix3d::Zero();
  Matrix3d drB2ix = Matrix3d::Zero();

  MatrixXd Jvi;
  MatrixXd Jwi;
  MatrixXd Hv = MatrixXd::Zero(3,info.dof.joint);
  MatrixXd Hw = MatrixXd::Zero(3,info.dof.joint);
  MatrixXd Mth = MatrixXd::Zero(info.dof.joint,info.dof.joint);

  // diff
  MatrixXd dJvi;
  MatrixXd dJwi;
  Matrix3d dIi = Matrix3d::Zero();
  MatrixXd dHv = MatrixXd::Zero(3,info.dof.joint);
  MatrixXd dHw = MatrixXd::Zero(3,info.dof.joint);
  MatrixXd dMth = MatrixXd::Zero(info.dof.joint,info.dof.joint);

  int cur=0, temp;
  for(int i=0; i<info.value.node; i++){
    if(i==0){
      rB2ix = cross(limb[0].node[0].rC - limb[0].node[0].r);
      IB += limb[0].node[0].I;
      IB += limb[0].node[0].m*rB2ix.transpose()*rB2ix;

      // diff
      drB2ix = cross(limb[0].node[0].vC - limb[0].node[0].v);
      dIB += cross(limb[0].node[0].w)*limb[0].node[0].I + limb[0].node[0].I*cross(limb[0].node[0].w).transpose();
      dIB += limb[0].node[0].m*drB2ix.transpose()*rB2ix + limb[0].node[0].m*rB2ix.transpose()*drB2ix;

    }else{
      Jvi = MatrixXd::Zero(3,info.dof.joint);
      Jwi = MatrixXd::Zero(3,info.dof.joint);
      dJvi = MatrixXd::Zero(3,info.dof.joint);
      dJwi = MatrixXd::Zero(3,info.dof.joint);

      temp=0;
      for(int j=0; j<info.limb[i].dof; j++){
	rB2ix = cross(limb[i].node[j].rC - limb[0].node[0].r);
	IB += limb[i].node[j].I;
	IB += limb[i].node[j].m*rB2ix.transpose()*rB2ix;

	// diff
  	drB2ix = cross(limb[i].node[j].vC - limb[0].node[0].v);
	dIB += cross(limb[i].node[j].w)*limb[i].node[j].I + limb[i].node[j].I*cross(limb[i].node[j].w).transpose();
  	dIB += limb[i].node[j].m*drB2ix.transpose()*rB2ix + limb[i].node[j].m*rB2ix.transpose()*drB2ix;

	for(int k=0; k<j+1; k++){
	  Jvi.col(cur+k) = cross(limb[i].node[k].sw)*(limb[i].node[j].rC - limb[i].node[k].r);
	  // diff
	  dJvi.col(cur+k) = cross(limb[i].node[k].dsw)*(limb[i].node[j].rC - limb[i].node[k].r)
	    + cross(limb[i].node[k].sw)*(limb[i].node[j].vC - limb[i].node[k].v);
	}

	Hv += limb[i].node[j].m*Jvi;
	// diff
	dHv += limb[i].node[j].m*dJvi;

	Jwi.col(cur+j) = limb[i].node[j].sw;
	// diff
	dJwi.col(cur+j) = limb[i].node[j].dsw;

	Hw += limb[i].node[j].I*Jwi + limb[i].node[j].m*rB2ix*Jvi;
	// diff
	dIi = cross(limb[i].node[j].w)*limb[i].node[j].I + limb[i].node[j].I*cross(limb[i].node[j].w).transpose();
	dHw += dIi*Jwi + limb[i].node[j].I*dJwi + limb[i].node[j].m*rB2ix*dJvi + limb[i].node[j].m*drB2ix*Jvi;

	Mth += limb[i].node[j].m*Jvi.transpose()*Jvi+Jwi.transpose()*limb[i].node[j].I*Jwi;
	// diff
	dMth += limb[i].node[j].m*Jvi.transpose()*dJvi + limb[i].node[j].m*dJvi.transpose()*Jvi +
	  Jwi.transpose()*limb[i].node[j].I*dJwi + Jwi.transpose()*dIi*Jwi + dJwi.transpose()*limb[i].node[j].I*Jwi;

	temp++;
      }
      cur += temp;
    }
  }

  // ********************************************
  Vector3d gf = Vector3d::Zero();
  gf = all.m*ag;
  Vector3d gm = Vector3d::Zero();
  gm = all.m*cross(all.rC - limb[0].node[0].r)*ag;
  VectorXd gth = VectorXd::Zero(1);
  gth = Hv.transpose()*ag;

  MatrixXd M = MatrixXd::Zero(info.dof.all,info.dof.all);
  M <<
    Mv,Mvw,Hv,
    Mvw.transpose(),IB,Hw,
    Hv.transpose(),Hw.transpose(),Mth;

  VectorXd dq = VectorXd::Zero(info.dof.all);
  dq <<
    limb[0].node[0].v,
    limb[0].node[0].w,
    all.dth;

  MatrixXd dM = MatrixXd::Zero(info.dof.all,info.dof.all);
  dM <<
    dMv,dMvw,dHv,
    dMvw.transpose(),dIB,dHw,
    dHv.transpose(),dHw.transpose(),dMth;

  VectorXd g = VectorXd::Zero(info.dof.all);
  g <<
    -gf,
    -gm,
    -gth;
  // ********************************************

  all.dM=dM;
}
