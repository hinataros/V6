/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::readWork(Config &config, Info &info, string node, int seq)
{
  if(config.flag.debug) DEBUG;

  YAML::Node doc = YAML::LoadFile(config.dir.work.c_str());

  if(node=="Sequence")
    try{
      checkNode(doc, node, seq, "twf");
    }
    catch(...){cout << "no work time..." << endl;return -1;}

  info.sim.twf = checkValue<double>(doc, node, seq, "twf", info.sim.twf);

  info.sim.trecf = checkValue<double>(doc, node, seq, "trecf", info.sim.trecf);

  inverseDynamicsControllerName = checkValue<string>(doc, node, seq, "Inverse dynamics controller", inverseDynamicsControllerName);
  motionControllerName = checkValue<string>(doc, node, seq, "Motion controller", motionControllerName);
  momentumControllerName = checkValue<string>(doc, node, seq, "Momentum controller", momentumControllerName);
  forceControllerName = checkValue<string>(doc, node, seq, "Force controller", forceControllerName);
  torqueControllerName = checkValue<string>(doc, node, seq, "Torque controller", torqueControllerName);

  Bc_kDiag = checkMatrix<MatrixXi>(doc, node, seq, "Bc", info.value.joint, Bc_kDiag);
  Bm_kDiag = checkMatrix<MatrixXi>(doc, node, seq, "Bm", info.value.joint, Bm_kDiag);

  BpDiag = checkMatrix<MatrixXi>(doc, node, seq, "Bp", info.value.joint, BpDiag);

  rCf = checkVector<VectorXd>(doc, node, seq, "rCf", rCf);
  rBf = checkVector<VectorXd>(doc, node, seq, "rBf", rBf);
  xiBf = checkVector<VectorXd>(doc, node, seq, "xiBf", xiBf);

  rXf = checkVector<VectorXd>(doc, node, seq, "rXf", rXf);

  cal_Fextf = checkVector<VectorXd>(doc, node, seq, "cal_Fextf", cal_Fextf);

  cal_Xf = checkVector<VectorXd>(doc, node, seq, "cal_Xf", info.value.joint, cal_Xf);

  KpC = checkMatrix<MatrixXd>(doc, node, seq, "KpC", KpC);
  KdC = checkMatrix<MatrixXd>(doc, node, seq, "KdC", KdC);

  KpvB = checkMatrix<MatrixXd>(doc, node, seq, "KpvB", KpvB);
  KdvB = checkMatrix<MatrixXd>(doc, node, seq, "KdvB", KdvB);

  KpwB = checkMatrix<MatrixXd>(doc, node, seq, "KpwB", KpwB);
  KdwB = checkMatrix<MatrixXd>(doc, node, seq, "KdwB", KdwB);

  KX = checkMatrix<MatrixXd>(doc, node, seq, "KX", KX);

  Kpv = checkMatrix<MatrixXd>(doc, node, seq, "Kpv", info.value.joint, Kpv);
  Kdv = checkMatrix<MatrixXd>(doc, node, seq, "Kdv", info.value.joint, Kdv);

  KDlC = checkMatrix<MatrixXd>(doc, node, seq, "KDlC", KDlC);
  KDth = checkMatrix<MatrixXd>(doc, node, seq, "KDth", info.value.joint, KDth);
  KDq = checkMatrix<MatrixXd>(doc, node, seq, "KDq", info.value.node, KDq);

  // high gain control
  KpHG = checkMatrix<MatrixXd>(doc, node, seq, "KpHG", info.value.joint, KpHG);
  KdHG = checkMatrix<MatrixXd>(doc, node, seq, "KdHG", info.value.joint, KdHG);

  // optimization weight
  WFSD = checkMatrix<MatrixXd>(doc, node, seq, "WFSD", WFSD);
  Wp = checkMatrix<MatrixXd>(doc, node, seq, "Wp", Wp);
  WF = checkMatrix<MatrixXd>(doc, node, seq, "WF", WF);
  Wm = checkMatrix<MatrixXd>(doc, node, seq, "Wm", info.value.joint, Wm);
  WJ = checkMatrix<MatrixXd>(doc, node, seq, "WJ", info.value.joint, WJ);
  Wth = checkMatrix<MatrixXd>(doc, node, seq, "Wth", info.value.joint, Wth);

  return 0;
}
