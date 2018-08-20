/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::identityVectorMethod()
{
  if(debug) DEBUG;

  VectorXd cal_Q = VectorXd::Zero(info.dof.all);
  VectorXd ddq = VectorXd::Zero(info.dof.all);

  link[info.rootNode].dv_rne = ddq.head(3);
  link[info.rootNode].dw_rne = ddq.segment(3,3);
  writeJointStateVector("rne joint acceleration", ddq.tail(info.dof.joint));

  all.b = recursiveNewtonEuler();

  for(int i=0; i<info.dof.all; i++){
    ddq(i) = 1.;

    link[info.rootNode].dv_rne = ddq.head(3);
    link[info.rootNode].dw_rne = ddq.segment(3,3);
    writeJointStateVector("rne joint acceleration", ddq.tail(info.dof.joint));

    all.M.col(i) = recursiveNewtonEuler() - all.b;

    ddq = VectorXd::Zero(info.dof.all);
  }

  all.g = gravity();
  all.c = all.b - all.g;
}
