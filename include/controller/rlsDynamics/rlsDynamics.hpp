#include <map>

#include "yaml-cpp/yaml.h"
#include "interpolation.hpp"
#include "common.hpp"

#include "rlsDynamicsList.hpp"

namespace RLS{
  class RlsDynamics:
    public Interpolation, virtual public Common
  {
  private:
    bool initialValueFlag;

    string motionControllerName;
    string momentumControllerName;
    string forceControllerName;
    string torqueControllerName;
    string inverseDynamicsControllerName;

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
    Vector6d cal_VC;
    VectorXd cal_X;
    VectorXd cal_V;

    VectorXd cal_F;

    VectorXd dq;

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

    MatrixXd Jc;
    MatrixXd Jm;
    MatrixXd dJc;
    MatrixXd dJm;

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

    MatrixXd Jth;
    MatrixXd cal_JcHat;
    MatrixXd cal_JmHat;
    MatrixXd dJth;
    MatrixXd cal_dJcHat;
    MatrixXd cal_dJmHat;

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

    // ******************************
    // inertia
    MatrixXd MthHat;

    // nonlinear
    VectorXd cthHat;

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
    Vector6d cal_dVCRef;

    VectorXd cal_dVRef;

    // momentum
    Vector3d dpRef;
    Vector3d dlBRef;
    Vector3d dlCRef;
    Vector6d cal_dLBRef;
    Vector6d cal_dLCRef;

    // force
    VectorXd cal_FcBarRef;

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
    Matrix3d KpC;
    Matrix3d KdC;

    Matrix3d KpvB;
    Matrix3d KdvB;

    Matrix3d KpwB;
    Matrix3d KdwB;

    MatrixXd Kpv;
    MatrixXd Kdv;

    Matrix3d KDlC;
    MatrixXd KDth;
    MatrixXd KDq;

    // high gain control
    MatrixXd KpHG;
    MatrixXd KdHG;

    void initialValue(Config&, Info&, Model&);
    void resize(Config&, Info&, Model&);
    void reset(Config&, Info&, double&);

    int readWork(Config&, Info&);

    void reconfigure(Config&, Info&);

    void decompose(Config&, Model&);
    void rename(Config&, Info&, Model&);

    void cop(Config&, Info&, TreeModel&);
    void index(Config&, Info&, Model&);

    void comReference(Config&, Info&, Model&, double&);
    void baseReference(Config&, Info&, Model&, double&);
    void endEffectorReference(Config&, Info&, Model&, double&);
    void reference(Config&, Info&, Model&, double&);

    // velocity controller
    VectorXd baseVelocitySynergy(Config&, Info&, Model&);
    VectorXd mixedVelocitySynergy(Config&, Info&, Model&);

    // acceleration controller
    VectorXd baseAccelerationSynergy(Config&, Info&, Model&);
    VectorXd mixedAccelerationSynergy(Config&, Info&, Model&);
    VectorXd centroidalAccelerationSynergy(Config&, Info&, Model&);
    VectorXd noname(Config&, Info&, Model&);
    VectorXd baseGeneralizedMomentum(Config&, Info&, Model&);
    VectorXd mixedGeneralizedMomentum(Config&, Info&, Model&);

    // acceleration dumper
    VectorXd ddthD(Config&, Model&);
    VectorXd ddqD(Config&, Info&, Model&);

    // momentum controller
    void baseMomentum(Config&, Info&, Model&);
    void centroidalMomentum(Config&, Info&, Model&);

    // force controller
    void baseDistribution(Config&, Info&, Model&);
    void centroidalDistribution(Config&, Info&, Model&);

    // torque controller
    void base(Config&, Info&, Model&);
    void mixed(Config&, Info&, Model&);
    void mixedmixed(Config&, Info&, Model&);
    void crb(Config&, Info&, Model&);

    // inverse dynamics controller
    VectorXd fullDynamicsController(Config&, Info&, Model&);
    VectorXd highGainController(Config&, Info&, Model&);

    void controlMethod(Config&, Info&, Model&);

    void velocityOutputConfig(Config&, Model&);
    void accelerationOutputConfig(Config&, Model&);
    void torqueOutputConfig(Config&, Model&);
    void outputConfig(Config&, Model&);

    // readWork
    void checkNode(Config&, Info&, YAML::Node&, string);
    void checkNode(Config&, Info&, YAML::Node&, string, int);
    void checkNode(Config&, Info&, YAML::Node&, string, int, int);
    template <class T> T checkValue(Config&, Info&, YAML::Node&, string, T);
    template <class T> T checkVector(Config&, Info&, YAML::Node&, string, T);
    template <class T> T checkVector(Config&, Info&, YAML::Node&, string, int, T);
    template <class T> T checkMatrix(Config&, Info&, YAML::Node&, string, T);
    template <class T> T checkMatrix(Config&, Info&, YAML::Node&, string, int, T);

    template <class T> T readValue(Config&, Info&, YAML::Node&, string);
    template <class T> T readValue(Config&, Info&, YAML::Node&, string, string);
    template <class T> T readValue(Config&, Info&, YAML::Node&, string, int);
    template <class T> T readValue(Config&, Info&, YAML::Node&, string, int, int);
    template <class T> T readVector(Config&, Info&, YAML::Node&, string, int);
    template <class T> T readVector(Config&, Info&, YAML::Node&, string, int, int);

    // select controller
    VectorXd (RLS::RlsDynamics::*motionController_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;
    void (RLS::RlsDynamics::*momentumController_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;
    void (RLS::RlsDynamics::*forceController_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;
    void (RLS::RlsDynamics::*torqueController_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;
    VectorXd (RLS::RlsDynamics::*inverseDynamicsController_ptr)(RLS::Config&, RLS::Info&, RLS::Model&)=0;

    map<string, VectorXd (RLS::RlsDynamics::*)(RLS::Config&, RLS::Info&, RLS::Model&)>
    map_motionController, map_inverseDynamicsController;
    map<string, void (RLS::RlsDynamics::*)(RLS::Config&, RLS::Info&, RLS::Model&)>
    map_momentumController, map_forceController, map_torqueController;

  public:
    // smiyahara: 名前は変えたい
    void initialize(Config&, Info&);
    VectorXd rlsDynamics(Config&, Info&, Model&, double&);

    RlsDynamicsList dc_list;
  };
}
