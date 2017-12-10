#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::readWork(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  YAML::Node doc = YAML::LoadFile(config.dir.work.c_str());

  try{
    checkNode(config, info, doc, "twf");
  }
  catch(...){cout << "no work time..." << endl;return -1;}

  info.sim.twf = checkValue<double>(config, info, doc, "twf", info.sim.twf);

  mc_name = checkValue<string>(config, info, doc, "Motion controller", mc_name);
  tc_name = checkValue<string>(config, info, doc, "Torque controller", tc_name);

  Bc_kDiag = checkMatrix<MatrixXi>(config, info, doc, "Bc", info.value.joint, Bc_kDiag);
  Bm_kDiag = checkMatrix<MatrixXi>(config, info, doc, "Bm", info.value.joint, Bm_kDiag);

  rCf = checkVector<VectorXd>(config, info, doc, "rCf", rCf);
  rBf = checkVector<VectorXd>(config, info, doc, "rBf", rBf);
  xiBf = checkVector<VectorXd>(config, info, doc, "xiBf", xiBf);

  cal_Xf = checkVector<VectorXd>(config, info, doc, "cal_Xf", info.value.joint, cal_Xf);

  KpC = checkMatrix<MatrixXd>(config, info, doc, "KpC", KpC);
  KdC = checkMatrix<MatrixXd>(config, info, doc, "KdC", KdC);

  KpvB = checkMatrix<MatrixXd>(config, info, doc, "KpvB", KpvB);
  KdvB = checkMatrix<MatrixXd>(config, info, doc, "KdvB", KdvB);

  KpwB = checkMatrix<MatrixXd>(config, info, doc, "KpwB", KpwB);
  KdwB = checkMatrix<MatrixXd>(config, info, doc, "KdwB", KdwB);

  Kpv = checkMatrix<MatrixXd>(config, info, doc, "Kpv", info.value.joint, Kpv);
  Kdv = checkMatrix<MatrixXd>(config, info, doc, "Kdv", info.value.joint, Kdv);

  KDth = checkMatrix<MatrixXd>(config, info, doc, "KDth", info.value.joint, KDth);
  KDq = checkMatrix<MatrixXd>(config, info, doc, "KDq", info.value.node, KDq);

  // high gain control
  KpHG = checkMatrix<MatrixXd>(config, info, doc, "KpHG", info.value.joint, KpHG);
  KdHG = checkMatrix<MatrixXd>(config, info, doc, "KdHG", info.value.joint, KdHG);

  return 0;
}
