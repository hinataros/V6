/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readParameter()
{
  if(debug) DEBUG;

  if(yamlInfo.sequence >= 0){
    bool tLoad = false;
    yamlInfo.checkValue<bool>(tLoad, "tld"); // amiyata
    if(tLoad)
      sequence[yamlInfo.sequence].twf = des.twf[yamlInfo.sequence];
    else
      yamlInfo.checkValue<double>(sequence[yamlInfo.sequence].twf, "twf");
  }

  yamlInfo.checkValue<Vector2d>(distOffset, "distribution offset");

  yamlInfo.checkValue<Matrix2d>(Kpp, "Kpp");

  yamlInfo.checkValue<Matrix3d>(KDlC, "KDlC");
  yamlInfo.checkValue<Matrix3d>(KDwC, "KDwC"); // amiyata

  for(int i=0; i<info.model.controlNodeNum; i++){
    string name = info.model.controlNode[i].name;

    Matrix6i temp6i = constraintModel.Bc_kDiag.block(6*i,6*i,6,6);
    yamlInfo.checkValue<Matrix6i>(temp6i, "Bc", name);
    constraintModel.Bc_kDiag.block(6*i,6*i,6,6) = temp6i;

    temp6i = constraintModel.Bm_kDiag.block(6*i,6*i,6,6);
    yamlInfo.checkValue<Matrix6i>(temp6i, "Bm", name);
    constraintModel.Bm_kDiag.block(6*i,6*i,6,6) = temp6i;

    Matrix2i temp2i = constraintModel.BpDiag.block(2*i,2*i,2,2);
    yamlInfo.checkValue<Matrix2i>(temp2i, "Bp", name);
    constraintModel.BpDiag.block(2*i,2*i,2,2) = temp2i;

    Matrix6d temp6d = Matrix6d::Zero();
    if(yamlInfo.checkValue<Matrix6d>(temp6d, "WF", name))
      WF.block(6*i,6*i,6,6) = temp6d;

    Matrix2d temp2d = Matrix2d::Zero();
    if(yamlInfo.checkValue<Matrix2d>(temp2d, "Wp", name))
      Wp.block(2*i,2*i,2,2) = temp2d;
  }

  yamlInfo.checkValue<MatrixXd>(KDth, "KDth");
  yamlInfo.checkValue<MatrixXd>(KDth, "KPth");
  yamlInfo.checkValue<MatrixXd>(KDdthH, "KDdthH"); // amiyata
  yamlInfo.checkValue<MatrixXd>(KDlCH, "KDlCH"); // amiyata
  yamlInfo.checkValue<MatrixXd>(Kthinit, "Kthinit");

  // weight
  yamlInfo.checkValue<MatrixXd>(Wth, "Wth"); // amiyata
  yamlInfo.checkValue<Matrix6d>(Wdh, "Wdh"); // amiyata

  // high gain control
  yamlInfo.checkValue<MatrixXd>(KpHG, "KpHG");
  yamlInfo.checkValue<MatrixXd>(KdHG, "KdHG");

  // Wp = updateValue<MatrixXd>(doc, multi, node, num, phase, "Wp", info.controlNodeNum, Wp);
  // WF = updateValue<MatrixXd>(doc, multi, node, num, phase, "WF", info.controlNodeNum, WF);
  // WFmin = updateValue<MatrixXd>(doc, multi, node, num, phase, "WFmin", info.controlNodeNum, WFmin);
  // Wm = updateValue<MatrixXd>(doc, multi, node, num, phase, "Wm", info.controlNodeNum, Wm);
  // WJ = updateValue<MatrixXd>(doc, multi, node, num, phase, "WJ", info.controlNodeNum, WJ);
  // Wth = updateValue<MatrixXd>(doc, multi, node, num, phase, "Wth", info.controlNodeNum, Wth);

  // // optimization weight
  // Wdh = updateValue<Matrix6d>(doc, multi, node, num, phase, "Wdh", Wdh);

  // // transform offset
  for(int i=0; i<info.model.controlNodeNum; i++) {
    string name = info.model.controlNode[i].name;
    Vector3d temp3d = rkk.segment(3*i, 3);
    yamlInfo.checkValue<Vector3d>(temp3d, "rkk", name);
    rkk.segment(3*i, 3) = temp3d;
    // rkk = readVector<VectorXd>(doc, node, seq, "rkk", i, 3);
  }

  // amiyata
  yamlInfo.checkValue<MatrixXi>(BwB_Diag, "BwB");
  yamlInfo.checkValue<MatrixXi>(BLC_Diag, "BLC");
  yamlInfo.checkValue<MatrixXi>(BwC_Diag, "BwC");
}
