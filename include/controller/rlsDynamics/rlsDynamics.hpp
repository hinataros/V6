#include "interpolation.hpp"
#include "common.hpp"

#include "rlsDynamicsList.hpp"

namespace RLS{
  class RlsDynamics:
    public Interpolation, virtual public Common
  {
  private:
    void initialValue(Config&, Info&, Model&);
    void rename(Config&, Info&, Model&);
    void resize(Config&, Info&, Model&);
    void reset(Config&, Info&, double&);
    void readWork(Config&, Info&);
    void reconfigure(Config&, Info&);

    void decompose(Config&, Model&);

    void comReference(Config&, Info&, Model&, double&);
    void baseReference(Config&, Info&, Model&, double&);
    void endEffectorReference(Config&, Info&, Model&, double&);
    void reference(Config&, Info&, Model&, double&);

    VectorXd ddthD(Config&, Model&);
    void cl_Bcoord(Config&, Model&);
    void noname(Config&, Info&, Model&);
    void accelerationController(Config&, Info&, Model&);

    void momentumController(Config&, Info&, Model&);
    void forceController(Config&, Info&, Model&);
    void torqueController(Config&, Info&, Model&);
    void control(Config&, Info&, Model&);

    void outputConfig(Config&);

  public:
    // smiyahara: 名前は変えたい
    void initialize(Config&, Info&);

    RlsDynamicsList dc_list;

    int c;
    MatrixXi Bc_kDiag;
    MatrixXd Bc_k;

    int m;
    MatrixXi Bm_kDiag;
    MatrixXd Bm_k;

    // ******************************
    Vector6d cal_XB;
    Vector6d cal_VB;
    Vector6d cal_VM;
    VectorXd cal_X;
    VectorXd cal_V;

    // ******************************
    MatrixXd cal_J;
    // smiyahara: bbではないから要検討
    MatrixXd bb_Rk;
    MatrixXd TB2k;

    MatrixXd Bc;
    MatrixXd Bm;
    MatrixXd cal_Pc;
    MatrixXd cal_Pm;
    MatrixXd cal_Jc;
    MatrixXd cal_Jm;

    // diff
    MatrixXd cal_dJ;
    // smiyahara: bbではないから要検討
    MatrixXd bb_dRk;
    MatrixXd dTB2k;

    MatrixXd dBc;
    MatrixXd dBm;
    MatrixXd cal_dPc;
    MatrixXd cal_dPm;
    MatrixXd cal_dJc;
    MatrixXd cal_dJm;

    // ******************************
    MatrixXd TC2k;
    MatrixXd Pcf;
    MatrixXd PcMm;
    MatrixXd cal_PcM;
    MatrixXd cal_JcM;

    // diff
    MatrixXd dTC2k;
    MatrixXd dPcf;
    MatrixXd dPcMm;
    MatrixXd cal_dPcM;
    MatrixXd cal_dJcM;

    // rename
    // ******************************
    // inertia
    MatrixXd IB;
    MatrixXd HBth;
    MatrixXd Mth;

    // nonlinear
    Vector6d cal_CB;
    VectorXd cth;

    // gravity
    Vector6d cal_GB;
    VectorXd gth;

    // ******************************
    // inertia
    MatrixXd IC;
    MatrixXd HC;
    MatrixXd MthC;

    // diff inertia
    Matrix3d dIC;
    MatrixXd dHC;

    // nonlinear
    Vector6d cal_CM;
    VectorXd cthC;

    // gravity
    Vector6d cal_GC;

    // ******************************
    Vector3d rC0;
    Vector3d rCf;

    Vector3d rB0;
    Vector3d rBf;
    Vector3d xiB0;
    Vector3d xiBf;

    VectorXd cal_X0;
    VectorXd cal_Xf;

    Vector3d des;

    Vector3d rCtemp;
    Vector3d rBtemp;
    Vector3d xiBtemp;
    VectorXd cal_Xtemp;

    Vector3d rCDes;
    Vector3d vCDes;
    Vector3d dvCDes;

    Vector3d rBDes;
    Vector3d vBDes;
    Vector3d dvBDes;

    Vector3d xiBDes;
    Vector3d dxiBDes;
    Vector3d ddxiBDes;
    Matrix3d RBDes;
    Vector3d wBDes;
    Vector3d dwBDes;

    VectorXd cal_XDes;
    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    // error
    Vector3d erC;
    Vector3d evC;

    Vector3d erB;
    Vector3d evB;

    Vector3d eoB;
    Vector3d ewB;

    Vector3d dvCRef;

    Vector3d dvBRef;
    Vector3d dwBRef;

    Vector6d cal_dVBRef;
    Vector6d cal_dVMRef;

    VectorXd cal_dVRef;

    // acceleration controller
    VectorXd cal_dVcBarRef;

    VectorXd cal_dVmBarRef;
    VectorXd cal_dVmTildeRef;
    MatrixXd cal_JmBar;

    // nonlinear
    VectorXd hc;
    VectorXd hm;
    VectorXd h;

    // momentum
    Vector6d cal_dLBRef;
    Vector6d cal_dLCRef;

    // force
    VectorXd cal_FcBarRef;

    VectorXd ddthcRef;
    VectorXd ddthmRef;

    VectorXd ddthRef;

    VectorXd tau;

    // gain
    double kpC;
    double kdC;

    double kpvB;
    double kdvB;

    double kpwB;
    double kdwB;

    VectorXd rlsDynamics(Config&, Info&, Model&, double&);

    // RlsDynamics(){}
    // RlsDynamics(Config &config, Model &model){
    //   activate(config, model);
    // }
  };
}
