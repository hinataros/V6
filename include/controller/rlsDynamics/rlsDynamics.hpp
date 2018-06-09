/**
   @author Sho Miyahara 2017
*/

#include <map>

#include "yaml-cpp/yaml.h"
#include "interpolation.hpp"
#include "solver.hpp"
#include "common.hpp"

#include "rlsDynamicsList.hpp"

namespace RLS{
  class RlsDynamics:
    public Interpolation,
    public Solver,
    virtual public Common
  {
  private:
    bool initialValueFlag;

    string motionControllerName;
    string momentumControllerName;
    string forceControllerName;
    string torqueControllerName;
    string inverseDynamicsControllerName;

    double g;

    MatrixXi Bc_kDiag;
    MatrixXd Bc_k;

    MatrixXi Bm_kDiag;
    MatrixXd Bm_k;

    MatrixXi BpDiag;
    MatrixXd Bp;

    // ******************************
    Vector6d cal_XB;
    Vector6d cal_VB;
    Vector6d cal_VM;
    Vector6d cal_VC;
    VectorXd cal_X;
    VectorXd cal_V;

    VectorXd cal_F;

    VectorXd dq;
    VectorXd dqM;

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

    MatrixXd JcM;
    MatrixXd JmM;
    MatrixXd dJcM;
    MatrixXd dJmM;

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

    // objective
    // ******************************
    MatrixXd Pc;

    // rename
    // ******************************
    Vector3d rB2C;
    Vector3d drB2C;

    // inertia
    Matrix3d IB;
    Matrix6d MB;
    MatrixXd HBth;
    MatrixXd cal_AB;
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
    Matrix6d MC;
    MatrixXd HMth;
    MatrixXd HC;
    MatrixXd cal_AM;
    MatrixXd MthC;

    // diff inertia
    Matrix3d dIC;
    MatrixXd dHC;

    // nonlinear
    Vector6d cal_CM;
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
    Matrix2d bb_Spx;
    MatrixXd cal_Sp;

    // cop
    VectorXd rpw2k;
    VectorXd rpk;
    Vector2d rp;

    // cmp
    Vector2d rcmp;

    // dcm
    double wX;
    Vector3d rX;

    // ******************************

    // boundary
    // ******************************
    Vector3d rC0;
    Vector3d rCf;

    Vector3d rB0;
    Vector3d rBf;
    Vector3d xiB0;
    Vector3d xiBf;

    Vector3d rX0;
    Vector3d rXf;

    VectorXd cal_X0;
    VectorXd cal_Xf;

    Vector6d cal_Fext0;
    Vector6d cal_Fextf;

    VectorXd rpk0;

    Vector3d des;

    // previous state
    // ******************************
    Vector3d rCpreState;
    Vector3d vCpreState;
    Vector3d rBpreState;
    Vector3d vBpreState;
    Vector3d xiBpreState;
    Vector3d dxiBpreState;
    Vector3d rXpreState;
    Vector3d drXpreState;

    VectorXd cal_XpreState;
    VectorXd cal_VpreState;

    // previous desired value
    // ******************************
    Vector3d rCpreDes;
    Vector3d rBpreDes;
    Vector3d xiBpreDes;
    VectorXd cal_XpreDes;

    Vector3d rXpreDes;

    Vector6d cal_FextpreDes;

    // desired value
    // ******************************
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

    Vector3d rXDes;
    Vector3d drXDes;

    VectorXd cal_XDes;
    VectorXd cal_VxiDes;
    VectorXd cal_dVxiDes;

    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    Vector6d cal_FextDes;

    // high gain control
    VectorXd thDes;

    // dcmWalkiing
    // ******************************
    int phaseDS;
    bool flagDS;

    int stepNum;
    int stepPhase;
    double tstep0;
    double tstep;
    double tDS0;

    VectorXd dt;
    MatrixXd rf;
    MatrixXd rvrpd;

    MatrixXd rXeos;

    // double sopport
    VectorXd dtDS;
    VectorXd alphDS;
    VectorXd dtDSini;
    VectorXd dtDSend;

    MatrixXd rXiniDS;
    MatrixXd rXeoDS;
    MatrixXd drXiniDS;
    MatrixXd drXeoDS;
    MatrixXd ddrXiniDS;
    MatrixXd ddrXeoDS;

    // ******************************

    // error
    Vector3d erC;
    Vector3d evC;

    Vector3d erB;
    Vector3d evB;

    Vector3d eoB;
    Vector3d ewB;

    Vector3d eX;

    VectorXd cal_Ep;
    VectorXd cal_Ev;

    // reference
    // **********************
    // velocityController
    // **********************
    Vector3d vBRef;
    Vector3d wBRef;
    VectorXd dthRef;
    VectorXd dqBRef;

    Vector3d vCRef;

    VectorXd dqMRef;

    Vector6d cal_VBRef;
    Vector6d cal_VMRef;

    VectorXd cal_VRef;
    // **********************

    Vector3d dvBRef;
    Vector3d dwBRef;
    VectorXd ddthRef;

    VectorXd ddqBRef;
    VectorXd ddqBoptRef;

    Vector3d dvCRef;

    VectorXd ddqMRef;
    VectorXd ddqMoptRef;

    Vector3d drXRef;

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

    Vector6d cal_FextRef;

    VectorXd tau;

    VectorXd input;

    // gain
    Matrix3d KpC;
    Matrix3d KdC;

    Matrix3d KpvB;
    Matrix3d KdvB;

    Matrix3d KpwB;
    Matrix3d KdwB;

    Matrix3d KX;

    MatrixXd Kpv;
    MatrixXd Kdv;

    Matrix2d Kpp;

    Matrix3d KDlC;
    MatrixXd KDth;
    MatrixXd KDq;

    // high gain control
    MatrixXd KpHG;
    MatrixXd KdHG;

    // optimization weight
    Matrix6d WFSD;
    MatrixXd Wp;
    MatrixXd WF;
    MatrixXd Wm;
    MatrixXd WJ;
    MatrixXd Wth;

    // trigger flag
    bool flagInit;
    bool flagHip;
    bool flagStay;

    // selective matrix for forward kinematics
    Matrix6d bb_ScB;

    void initialValue(Config&, Info&, Model&);
    void resize(Config&, Info&, Model&);

    void cop(Config&, Info&, TreeModel&);
    void cmp(Config&, Info&, TreeModel&);
    void dcm(Config&, Info&, TreeModel&);
    void index(Config&, Info&, Model&);

    // state transition
    bool resetState(Config&, Info&, Model&, double&);
    bool resetSequence(Config&, Info&, double&);
    void mapping(Config&);

    int checkContact(Config&, Info&, Model&, double&);
    int staticCheckContact(Config&, Info&, Model&, double&);
    int ankleStratagy(Config&, Info&, Model&, double&);
    int ankleHipStratagy(Config&, Info&, Model&, double&);
    int walking(Config&, Info&, Model&, double&);
    int stateTriggerConfig(Config&, Info&, Model&, double&);

    bool sequenceTriggerConfig(Config&, Info&, double&);

    bool configurationManager(Config&, Info&, Model&, double&);

    int readWork(Config&, Info&, string, int);

    void reconfigure(Config&, Info&);

    void decompose(Config&, Model&);
    int objective(Config&, Info&, Model&);
    void rename(Config&, Info&, Model&);
    void update(Config&, Info&, Model&);

    // reference
    //com
    void comSequence(Config&, Info&, Model&, double&);
    void dcm2com(Config&, Info&, Model&, double&);

    // base translation
    void baseTranslationSequence(Config&, Info&, Model&, double&);

    // base orientation
    void baseOrientationSequence(Config&, Info&, Model&, double&);
    void baseOrientationAnkleHip(Config&, Info&, Model&, double&);

    // DCM
    void dcmSequence(Config&, Info&, Model&, double&);
    void dcmAnkleHip(Config&, Info&, Model&, double&);
    void dcmSSWalking(Config&, Info&, Model&, double&);
    void dcmDSWalking(Config&, Info&, Model&, double&);

    // end effector
    void endEffectorSequence(Config&, Info&, Model&, double&);
    void endEffectorDSWalking(Config&, Info&, Model&, double&);

    // external wrench
    void externalWrenchSequence(Config&, Info&, Model&, double&);

    void reference(Config&, Info&, Model&, double&);

    // add function
    Vector2d F2rp(Vector6d);
    MatrixXd weight(Config&, Info&, Model&, int, Vector3d);

    // zero controller
    VectorXd zeroDynamics(Config&, Info&, Model&);
    VectorXd zeroMotion(Config&, Info&, Model&);
    void zeroMomentum(Config&, Info&, Model&);
    void zeroDistribution(Config&, Info&, Model&);
    void zeroTorque(Config&, Info&, Model&);

    // velocity controller
    VectorXd baseVelocitySynergy(Config&, Info&, Model&);
    VectorXd mixedVelocitySynergy(Config&, Info&, Model&);

    // acceleration controller
    VectorXd workAcceleration(Config&, Info&, Model&);
    VectorXd baseAccelerationSynergy(Config&, Info&, Model&);
    VectorXd mixedAccelerationSynergy(Config&, Info&, Model&);
    VectorXd centroidalAccelerationSynergy(Config&, Info&, Model&);
    VectorXd noname(Config&, Info&, Model&);
    VectorXd baseGeneralizedMomentum(Config&, Info&, Model&);
    VectorXd mixedGeneralizedMomentum(Config&, Info&, Model&);
    VectorXd accelerationSolver(Config&, Info&, Model&);
    VectorXd hinata(Config&, Info&, Model&);

    // acceleration dumper
    VectorXd ddthD(Config&, Model&);
    VectorXd ddqD(Config&, Info&, Model&);

    // momentum controller
    void linearMomentum(Config&, Info&, Model&);
    void dcmMomentum(Config&, Info&, Model&);
    void centroidalAngularMomentum(Config&, Info&, Model&);
    void baseAngularMomentum(Config&, Info&, Model&);
    void baseMomentum(Config&, Info&, Model&);
    void baseDcmMomentum(Config&, Info&, Model&);
    void centroidalMomentum(Config&, Info&, Model&);
    void centroidalDcmMomentum(Config&, Info&, Model&);
    void centroidalCmpMomentum(Config&, Info&, Model&);

    // force controller
    void baseDistribution(Config&, Info&, Model&);
    void centroidalDistribution(Config&, Info&, Model&);
    void centroidalDcmDistribution(Config&, Info&, Model&);
    void distributionSolver(Config&, Info&, Model&);

    // torque controller
    void jointSpace(Config&, Info&, Model&);
    void staticControl(Config&, Info&, Model&);
    void base(Config&, Info&, Model&);
    void mixed(Config&, Info&, Model&);
    void mixedmixed(Config&, Info&, Model&);
    void crb(Config&, Info&, Model&);
    void baseOpt(Config&, Info&, Model&);
    void mixedOpt(Config&, Info&, Model&);
    void mixedmixedOpt(Config&, Info&, Model&);

    // inverse dynamics controller
    VectorXd fullDynamicsController(Config&, Info&, Model&);
    VectorXd momentumInverseDynamicsController(Config&, Info&, Model&);
    VectorXd highGainController(Config&, Info&, Model&);
    VectorXd spatialDynamicsSolver(Config&, Info&, Model&);
    VectorXd atlasSolver(Config&, Info&, Model&);

    void controlMethod(Config&, Info&, Model&);

    void velocityOutputConfig(Config&, Info&, Model&);
    void accelerationOutputConfig(Config&, Info&, Model&);
    void torqueOutputConfig(Config&, Info&, Model&);
    void outputConfig(Config&, Info&, Model&);

    // readWork
    void checkNode(YAML::Node&, string, int, string);
    void checkNode(YAML::Node&, string, int, string, int);
    void checkNode(YAML::Node&, string, int, string, int, int);
    template <class T> T checkValue(YAML::Node&, string, int, string, T);
    template <class T> T checkVector(YAML::Node&, string, int, string, T);
    template <class T> T checkVector(YAML::Node&, string, int, string, int, T);
    template <class T> T checkMatrix(YAML::Node&, string, int, string, T);
    template <class T> T checkMatrix(YAML::Node&, string, int, string, int, T);

    template <class T> T readValue(YAML::Node&, string, int, string);
    template <class T> T readValue(YAML::Node&, string, int, string, string);
    template <class T> T readValue(YAML::Node&, string, int, string, int);
    template <class T> T readValue(YAML::Node&, string, int, string, int, int);
    template <class T> T readVector(YAML::Node&, string, int, string, int);
    template <class T> T readVector(YAML::Node&, string, int, string, int, int);

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
    // smiyahara: 要検討(とりあえず外乱のみを考慮し"6"にしといた)
    Vector6d virtualInput;

    // smiyahara: 名前は変えたい
    void initialize(Config&, Info&);
    VectorXd rlsDynamics(Config&, Info&, Model&, double&);

    RlsDynamicsList dc_list;
  };
}
