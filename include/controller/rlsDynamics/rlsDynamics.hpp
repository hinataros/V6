#include <map>

#include "interpolation.hpp"
#include "common.hpp"

#include "rlsDynamicsList.hpp"

namespace RLS{
  class RlsDynamics:
    public Interpolation, virtual public Common
  {
  private:
    bool initialValueFlag;

    string mc_name;
    string tc_name;

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

    VectorXd cal_F;

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
    MatrixXd Pmf;
    MatrixXd PcMm;
    MatrixXd cal_PcM;
    MatrixXd cal_PmM;
    MatrixXd cal_JcM;
    MatrixXd cal_JmM;

    // diff
    MatrixXd dTC2k;
    MatrixXd dPcf;
    MatrixXd dPmf;
    MatrixXd dPcMm;
    MatrixXd cal_dPcM;
    MatrixXd cal_dPmM;
    MatrixXd cal_dJcM;
    MatrixXd cal_dJmM;

    // rename
    // ******************************
    Vector3d rB2C;
    Vector3d drB2C;

    // inertia
    Matrix3d IB;
    Matrix6d MB;
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
    Matrix3d IC;
    MatrixXd HC;
    MatrixXd MthC;

    // diff inertia
    Matrix3d dIC;
    MatrixXd dHC;

    // nonlinear
    VectorXd cthC;

    // gravity
    Vector3d gf;
    Vector6d cal_GC;

    // index
    // ******************************
    VectorXd rpk;
    Vector2d rp;

    // ******************************

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
    VectorXd cal_VxiDes;
    VectorXd cal_dVxiDes;

    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    // high gain control
    VectorXd thDes;

    // error
    Vector3d erC;
    Vector3d evC;

    Vector3d erB;
    Vector3d evB;

    Vector3d eoB;
    Vector3d ewB;

    VectorXd cal_Ep;
    VectorXd cal_Ev;

    Vector3d dvCRef;

    Vector3d dvBRef;
    Vector3d dwBRef;

    Vector6d cal_dVBRef;
    Vector6d cal_dVMRef;

    VectorXd cal_dVRef;

    // momentum
    Vector3d dpRef;
    Vector3d dlBRef;
    Vector3d dlCRef;
    Vector6d cal_dLBRef;
    Vector6d cal_dLCRef;

    // force
    VectorXd cal_FcBarRef;
    VectorXd cal_FcMBarRef;

    // velocityController
    // **********************
    Vector3d vCRef;

    Vector3d vBRef;
    Vector3d wBRef;

    Vector6d cal_VBRef;
    Vector6d cal_VMRef;

    VectorXd cal_VRef;
    VectorXd dthRef;
    VectorXd dqRef;
    // **********************

    VectorXd ddthRef;
    VectorXd ddqRef;

    VectorXd tau;

    VectorXd input;

    // gain
    double kpC;
    double kdC;

    double kpvB;
    double kdvB;

    double kpwB;
    double kdwB;

    double kpv;
    double kdv;

    double kthD;

    // high gain control
    double kpHG;
    double kdHG;

    void initialValue(Config&, Info&, Model&);
    void resize(Config&, Info&, Model&);
    void reset(Config&, Info&, double&);
    void readWork(Config&, Info&);
    void reconfigure(Config&, Info&);

    void decompose(Config&, Model&);
    void rename(Config&, Info&, Model&);

    void cop(Config&, Info&, Model&);
    void index(Config&, Info&, Model&);

    void comReference(Config&, Info&, Model&, double&);
    void baseReference(Config&, Info&, Model&, double&);
    void endEffectorReference(Config&, Info&, Model&, double&);
    void reference(Config&, Info&, Model&, double&);

    // velocity controller
    VectorXd cl_Bvel(Config&, Info&, Model&);
    VectorXd cl_Mvel(Config&, Info&, Model&);

    // acceleration controller
    VectorXd ddthD(Config&, Model&);
    VectorXd cl_Bacc(Config&, Info&, Model&);
    VectorXd cl_Macc(Config&, Info&, Model&);
    VectorXd noname(Config&, Info&, Model&);

    void momentumController(Config&, Info&, Model&);
    void forceController(Config&, Info&, Model&);

    // torque controller
    VectorXd fullDynamicsController(Config&, Info&, Model&);
    VectorXd highGainController(Config&, Info&, Model&);

    void control(Config&, Info&, Model&);

    void velocityOutputConfig(Config&, Model&);
    void accelerationOutputConfig(Config&, Model&);
    void torqueOutputConfig(Config&, Model&);
    void outputConfig(Config&, Model&);

    VectorXd (RLS::RlsDynamics::*mc_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;
    VectorXd (RLS::RlsDynamics::*tc_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;
    map<string, VectorXd (RLS::RlsDynamics::*)(RLS::Config&, RLS::Info&, RLS::Model&)> map_mc, map_tc;

  public:
    // smiyahara: 名前は変えたい
    void initialize(Config&, Info&);
    VectorXd rlsDynamics(Config&, Info&, Model&, double&);

    RlsDynamicsList dc_list;
  };
}
