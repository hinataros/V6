/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readControlNode(YAML::Node &doc, const TreeModel::Info &info, bool multi, string node, int num, int phase)
{
  for(int i=0; i<info.controlNodeNum; i++){
    controlNodeTrajectoryNum[i] = updateValue<int>(doc, multi, node, num, phase, "Control node trajectory", info.controlNode[i].name, "num", controlNodeTrajectoryNum[i]);
    controlNodeTrajectoryName[i] = updateValue<string>(doc, multi, node, num, phase, "Control node trajectory", info.controlNode[i].name, "name", controlNodeTrajectoryName[i]);

    if(node=="Sequence"){
      sequence[num].cal_Xf.segment(6*i,6) = updateValue<Vector6d>(doc, multi, node, num, phase, "cal_Xf", info.controlNode[i].name, sequence[num].cal_Xf.segment(6*i,6));

      sequence[num].cal_Xtd.segment(6*i,6) = updateValue<Vector6d>(doc, multi, node, num, phase, "cal_Xtd", info.controlNode[i].name, sequence[num].cal_Xtd.segment(6*i,6));
    }

    Bc_kDiag.block(6*i,6*i,6,6) = updateValue<Matrix6i>(doc, multi, node, num, phase, "Bc", info.controlNode[i].name, Bc_kDiag.block(6*i,6*i,6,6));
    Bm_kDiag.block(6*i,6*i,6,6) = updateValue<Matrix6i>(doc, multi, node, num, phase, "Bm", info.controlNode[i].name, Bm_kDiag.block(6*i,6*i,6,6));

    BpDiag.block(2*i,2*i,2,2) = updateValue<Matrix2i>(doc, multi, node, num, phase, "Bp", info.controlNode[i].name, BpDiag.block(2*i,2*i,2,2));

    Kpv.block(6*i,6*i,6,6) = updateValue<Matrix6d>(doc, multi, node, num, phase, "Kpv", info.controlNode[i].name, Kpv.block(6*i,6*i,6,6));
    Kdv.block(6*i,6*i,6,6) = updateValue<Matrix6d>(doc, multi, node, num, phase, "Kdv", info.controlNode[i].name, Kdv.block(6*i,6*i,6,6));
  }

  // Bc_kDiag = updateValue<MatrixXi>(doc, multi, node, num, phase, "Bc", info.controlNodeNum, Bc_kDiag);
  // Bm_kDiag = updateValue<MatrixXi>(doc, multi, node, num, phase, "Bm", info.controlNodeNum, Bm_kDiag);

  // BpDiag = updateValue<MatrixXi>(doc, multi, node, num, phase, "Bp", info.controlNodeNum, BpDiag);

  // Kpv = updateValue<MatrixXd>(doc, multi, node, num, phase, "Kpv", info.controlNodeNum, Kpv);
  // Kdv = updateValue<MatrixXd>(doc, multi, node, num, phase, "Kdv", info.controlNodeNum, Kdv);

  KDth = updateValue<MatrixXd>(doc, multi, node, num, phase, "KDth", info.controlNodeNum, KDth);
  Kthinit = updateValue<MatrixXd>(doc, multi, node, num, phase, "Kthinit", info.controlNodeNum, Kthinit);

  // high gain control
  KpHG = updateValue<MatrixXd>(doc, multi, node, num, phase, "KpHG", info.controlNodeNum, KpHG);
  KdHG = updateValue<MatrixXd>(doc, multi, node, num, phase, "KdHG", info.controlNodeNum, KdHG);

  Wp = updateValue<MatrixXd>(doc, multi, node, num, phase, "Wp", info.controlNodeNum, Wp);
  WF = updateValue<MatrixXd>(doc, multi, node, num, phase, "WF", info.controlNodeNum, WF);
  WFmin = updateValue<MatrixXd>(doc, multi, node, num, phase, "WFmin", info.controlNodeNum, WFmin);
  Wm = updateValue<MatrixXd>(doc, multi, node, num, phase, "Wm", info.controlNodeNum, Wm);
  WJ = updateValue<MatrixXd>(doc, multi, node, num, phase, "WJ", info.controlNodeNum, WJ);
  Wth = updateValue<MatrixXd>(doc, multi, node, num, phase, "Wth", info.controlNodeNum, Wth);
}
