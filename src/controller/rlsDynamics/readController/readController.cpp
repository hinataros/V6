/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readController()
{
  if(debug) DEBUG;

  if(yamlInfo.key=="Sequence")
    yamlInfo.checkValue<double>(sequence[yamlInfo.sequence].twf, "twf");

  yamlInfo.checkValue<string>(inverseDynamicsControllerName,
                              "Inverse dynamics controller");
  yamlInfo.checkValue<string>(operationalSpaceControllerName,
                              "Operational space controller");
  yamlInfo.checkValue<string>(motionControllerName,
                              "Motion controller");
  yamlInfo.checkValue<string>(momentumControllerName,
                              "Momentum controller");
  yamlInfo.checkValue<string>(internalForceControllerName,
                              "Internal force controller");
  yamlInfo.checkValue<string>(forceControllerName,
                              "Force controller");

  yamlInfo.checkValue<string>(torqueControllerName,
                              "Torque controller");

  yamlInfo.checkValue<string>(externalWrenchControllerName,
                              "External wrench controller");

  yamlInfo.checkValue<Matrix2d>(Kpp, "Kpp");

  yamlInfo.checkValue<Matrix3d>(KDlC, "KDlC");

  for(int i=0; i<info.model.controlNodeNum; i++){
    string name = info.model.controlNode[i].name;

    Matrix6i temp6i = Bc_kDiag.block(6*i,6*i,6,6);
    yamlInfo.checkValue<Matrix6i>(temp6i, "Bc", name);
    Bc_kDiag.block(6*i,6*i,6,6) = temp6i;

    temp6i = Bm_kDiag.block(6*i,6*i,6,6);
    yamlInfo.checkValue<Matrix6i>(temp6i, "Bm", name);
    Bm_kDiag.block(6*i,6*i,6,6) = temp6i;

    Matrix2i temp2i = BpDiag.block(2*i,2*i,2,2);
    yamlInfo.checkValue<Matrix2i>(temp2i, "Bp", name);
    BpDiag.block(2*i,2*i,2,2) = temp2i;
  }

  yamlInfo.checkValue<MatrixXd>(KDth, "KDth");
  yamlInfo.checkValue<MatrixXd>(Kthinit, "Kthinit");

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
  // if(multiSequence){
  //   if(!checkNode(doc, node, num, phase, name))
  //     for(int i=0; i<controlNodeNum; i++)
  //       rkk[i] = readVector<VectorXd>(doc, node, seq, "rkk", i, 3);
}

