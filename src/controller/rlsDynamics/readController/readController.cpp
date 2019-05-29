/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::readController()
{
  if(debug) DEBUG;

  if(yamlInfo.key==yamlInfo.sequenceKeyName)
    yamlInfo.checkValue<double>(sequence[yamlInfo.sequence].twf, "twf");

  string controlMethodKeyName = "control method";

  yamlInfo.checkValue<bool>(extInverseDynamicsController, controlMethodKeyName,
                            "ext inverse dynamics controller");
  yamlInfo.checkValue<bool>(extMotionController, controlMethodKeyName,
                            "ext motion controller");
  yamlInfo.checkValue<bool>(extMomentumController, controlMethodKeyName,
                            "ext momentum controller");
  yamlInfo.checkValue<bool>(extForceController, controlMethodKeyName,
                            "ext force controller");
  yamlInfo.checkValue<bool>(extTorqueController, controlMethodKeyName,
                            "ext torque controller");
  yamlInfo.checkValue<bool>(extExternalWrenchController, controlMethodKeyName,
                            "ext external wrench controller");

  yamlInfo.checkValue<string>(inverseDynamicsControllerName, controlMethodKeyName,
                              "inverse dynamics controller");
  yamlInfo.checkValue<string>(operationalSpaceControllerName, controlMethodKeyName,
                              "operational space controller");
  yamlInfo.checkValue<string>(motionControllerName, controlMethodKeyName,
                              "motion controller");
  yamlInfo.checkValue<string>(momentumControllerName, controlMethodKeyName,
                              "momentum controller");
  yamlInfo.checkValue<string>(internalForceControllerName, controlMethodKeyName,
                              "internal force controller");
  yamlInfo.checkValue<string>(forceControllerName, controlMethodKeyName,
                              "force controller");
  yamlInfo.checkValue<string>(torqueControllerName, controlMethodKeyName,
                              "torque controller");
  yamlInfo.checkValue<string>(externalWrenchControllerName, controlMethodKeyName,
                              "external wrench controller");

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
  }

  yamlInfo.checkValue<MatrixXd>(KDth, "KDth");
  yamlInfo.checkValue<MatrixXd>(KDdthH, "KDdthH"); //amiyata
  yamlInfo.checkValue<MatrixXd>(KDlCH, "KDlCH"); //amiyata
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
  for(int i=0; i<info.model.controlNodeNum; i++) {
    string name = info.model.controlNode[i].name;
    Vector3d temp3d = rkk.segment(3*i, 3);
    yamlInfo.checkValue<Vector3d>(temp3d, "rkk", name);
    rkk.segment(3*i, 3) = temp3d;
    // rkk = readVector<VectorXd>(doc, node, seq, "rkk", i, 3);
  }

  //amyata
  yamlInfo.checkValue<MatrixXi>(BwB_Diag, "BwB");
  yamlInfo.checkValue<MatrixXi>(BLC_Diag, "BLC");
  yamlInfo.checkValue<MatrixXi>(BwC_Diag, "BwC");
}
