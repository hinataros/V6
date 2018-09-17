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

    double dt;
    double g;

    MatrixXi Bc_kDiag;
    MatrixXd Bc_k;

    MatrixXi Bm_kDiag;
    MatrixXd Bm_k;

    MatrixXi BpDiag;
    MatrixXd Bp;

    // state
    // ******************************
    VectorXd th;
    VectorXd dth;

    Vector3d rB;
    Vector3d xiB;
    Vector3d vB;
    Vector3d wB;

    Vector3d rC;
    Vector3d vC;

    Vector6d cal_XB;
    Vector6d cal_VB;
    Vector6d cal_VM;
    Vector6d cal_VC;
    VectorXd cal_X;
    VectorXd cal_V;
    VectorXd cal_F;

    // VectorXd cal_Xsensor;
    // VectorXd cal_Fsensor;

    VectorXd dq;
    VectorXd dqM;

    double M;
    Vector3d ag;
    MatrixXd JB2C;
    MatrixXd dJB2C;

    // transform offset
    Vector3d *rkk;

    // jacobian
    // ******************************
    // smiyahara: bbではないから要検討
    MatrixXd bb_Rk;

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
    // smiyahara: bbではないから要検討
    MatrixXd bb_dRk;

    MatrixXd dBc;
    MatrixXd dBm;
    MatrixXd cal_dPc;
    MatrixXd cal_dPm;
    MatrixXd cal_dJc;
    MatrixXd cal_dJm;

    // ******************************
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

    // ******************************

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
    MatrixXd cal_dAB;
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
    MatrixXd cal_dAM;
    Matrix3d dIC;
    MatrixXd dHC;

    // nonlinear
    Vector3d cmm;
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
    VectorXd th0;

    Vector3d rC0;

    Vector3d rB0;
    Vector3d xiB0;

    Vector3d rX0;

    VectorXd cal_X0;

    Vector6d cal_Fext0;

    VectorXd rpk0;

    Vector3d des;

    // previous state
    // ******************************
    struct State{
      int num;

      Vector3d rBpreDes;
      Vector3d vBpreDes;
      Vector3d xiBpreDes;
      Vector3d dxiBpreDes;
      Vector3d rCpreDes;
      VectorXd cal_XpreDes;
      VectorXd cal_VpreDes;

      Vector3d vCpreDes;
      Vector3d rXpreDes;
      Vector3d drXpreDes;
    } state;

    // trajectory
    // ******************************
    bool multiSequence;
    int seqNum;

    string baseTranslationTrajectoryName;
    string baseOrientationTrajectoryName;
    string *controlNodeTrajectoryName;
    string comTrajectoryName;
    string dcmTrajectoryName;
    string externalWrenchTrajectoryName;

    int baseTranslationTrajectoryNum;
    int baseOrientationTrajectoryNum;
    int *controlNodeTrajectoryNum;
    int comTrajectoryNum;
    int dcmTrajectoryNum;
    int externalWrenchTrajectoryNum;

    struct Sequence{
      int phase;
      double tw0;
      double twf;

      Vector3d rBf;
      Vector3d rBpreDes;
      Vector3d xiBf;
      Vector3d xiBpreDes;
      VectorXd cal_Xf;
      VectorXd cal_XpreDes;

      Vector3d rCf;
      Vector3d rCpreDes;
      Vector3d rXf;
      Vector3d rXpreDes;

      Vector6d cal_Fextf;
      Vector6d cal_FextpreDes;

      VectorXd cal_Xtd;
    } *sequence;

    // select trajectory generator
    void (RLS::RlsDynamics::*baseTranslationTrajectory_ptr)(const double&)=0;
    void (RLS::RlsDynamics::*baseOrientationTrajectory_ptr)(const double&)=0;
    void (RLS::RlsDynamics::*comTrajectory_ptr)(const double&)=0;
    void (RLS::RlsDynamics::*dcmTrajectory_ptr)(const double&)=0;
    void (RLS::RlsDynamics::*externalWrenchTrajectory_ptr)(const double&)=0;

    map<string, void (RLS::RlsDynamics::*)(const double&)>
    map_baseTranslationTrajectory,
      map_baseOrientationTrajectory,
      map_comTrajectory,
      map_dcmTrajectory,
      map_externalWrenchTrajectory;

    void (RLS::RlsDynamics::**controlNodeTrajectory_ptr)(const int&, const double&);
    map<string, void (RLS::RlsDynamics::*)(const int&, const double&)>
    *map_controlNodeTrajectory;

    // desired value
    // ******************************
    Vector3d rBDes;
    Vector3d vBDes;
    Vector3d dvBDes;

    Vector3d xiBDes;
    Vector3d dxiBDes;
    Vector3d ddxiBDes;
    Matrix3d RBDes;
    Vector3d wBDes;
    Vector3d dwBDes;

    Vector3d rCDes;
    Vector3d vCDes;
    Vector3d dvCDes;

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

    VectorXd dT;
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

    // HT
    // ****************
    VectorXd alphaHT;
    VectorXd dtHT;
    VectorXd dtTH;

    MatrixXd rfT;
    MatrixXd rfH;

    MatrixXd rXHT;
    MatrixXd rXTH;

    MatrixXd rvrpTd;
    MatrixXd rvrpHd;

    // polynomial
    bool initial_walking;
    int support;
    double tphasef;

    // EE reference
    int referenceSequence;
    VectorXd cal_Xtd;
    // ****************

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
    string baseTranslationReferenceName;
    string baseOrientationReferenceName;
    string controlNodeReferenceName;
    string comReferenceName;
    string dcmReferenceName;
    string externalWrenchReferenceName;

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

    VectorXd ddqwoptRef;

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

    string motionControllerName;
    string momentumControllerName;
    string forceControllerName;
    string torqueControllerName;
    string inverseDynamicsControllerName;

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
    MatrixXd Kthinit;

    // high gain control
    MatrixXd KpHG;
    MatrixXd KdHG;

    // optimization weight
    Matrix6d Wdh;
    MatrixXd Wp;
    MatrixXd WF;
    MatrixXd WFmin;
    MatrixXd Wm;
    MatrixXd WJ;
    MatrixXd Wth;

    // trigger flag
    bool flagInit;
    bool flagHip;
    bool flagStay;

    // selective matrix for forward kinematics
    Matrix6d bb_ScB;

    void initializeState(const TreeModel::Info&);
    void initializeSequence(const string&, const TreeModel::Info&);
    void initializeWalking(const TreeModel::Info&);
    void initializeTriggerMap(const string&);
    void initializeReferenceMap();
    void initializeTrajectoryGeneratorMap(const TreeModel::Info&);
    void initializeControllerMap();

    void initialValue(const string&, Model&);
    void resize(Model&);

    void cop(const TreeModel&);
    void cmp(const TreeModel&);
    void dcm(const TreeModel&);
    void index(const Model&);

    // // state transition
    void updateState(const Model&, const double&);
    void updateSequence(const double&, const int&);
    void mapping(const int&);

    // triggre config
    int noTrigger(const Model&, const double&);
    int checkContact(const Model&, const double&);

    // select reference
    int (RLS::RlsDynamics::*customTrigger_ptr)(const Model&, const double&)=0;
    map<string, int (RLS::RlsDynamics::*)(const Model&, const double&)> map_customTrigger;

    int stateTrigger(const Model&, const double&);
    bool sequenceTrigger(const double&, const double, const int&);

    bool configurationManager(const Config&, const Model&, const double&);

    void readSequence(YAML::Node&, bool, string, int, int, int);
    void readControlNode(YAML::Node&, const TreeModel::Info&, bool, string, int, int);
    int readWork(string, const TreeModel::Info&, bool, string, int, int);

    void reconfigure(TreeModel::Info&);

    // // update
    // // ******************************
    void transform(Model&);

    void contactCoordinate(const Model&);
    void basis();
    void decomposeBase(const Model&);
    void decomposeMix(const Model&);
    void decompose(const Model&);

    int objective(const TreeModel::Info&);

    void renameState(const TreeModel&);
    void renameBase(const TreeModel&);
    void renameMix(const TreeModel&);
    void renameCentroidal(const TreeModel&);
    void renameOthers(const Config::Clock&, const Model&);
    void renameDebug(const Model&);
    void rename(const Config::Clock&, const Model&);

    void update(const Config::Clock&, Model&);
    // ******************************

    // trajectory generator
    // ******************************
    // base translation
    void baseTranslationZeroTrajectory(const double&);
    void baseTranslationTrajectoryCP(const double&);

    // base orientation
    void baseOrientationZeroTrajectory(const double&);
    void baseOrientationTrajectoryCP(const double&);

    // control node
    void controlNodeZeroTrajectory(const int&, const double&);
    void controlNodeTrajectoryCP(const int&, const double&);
    void controlNodeTrajectoryWalking(const int&, const double&);

    // com
    void comZeroTrajectory(const double&);
    void comTrajectoryCP(const double&);

    // dcm
    void dcmZeroTrajectory(const double&);
    void dcmTrajectoryCP(const double&);
    void dcmHTWalking(const double&);

    // external wrench
    void externalWrenchZeroTrajectory(const double&);
    void externalWrenchTrajectoryCP(const double&);

    void trajectoryGenerator(const int&, const double&);

    // reference
    // ******************************
    // base translation
    void baseTranslationReferencePI(const TreeModel&);

    // base orientation
    void baseOrientationReferencePI(const TreeModel&);

    // control node
    void controlNodeReferencePI(const TreeModel&);

    // com
    void comReferencePI(const TreeModel&);
    void comReferenceDcmControl(const TreeModel&);

    // dcm
    void dcmReferencePI(const TreeModel&);

    // external wrench
    void externalWrenchReferenceFF(const TreeModel&);

    void spatialReference(const Model&);

    void reference(const Model&);

    // select reference
    void (RLS::RlsDynamics::*baseTranslationReference_ptr)(const TreeModel&)=0;
    void (RLS::RlsDynamics::*baseOrientationReference_ptr)(const TreeModel&)=0;
    void (RLS::RlsDynamics::*controlNodeReference_ptr)(const TreeModel&)=0;
    void (RLS::RlsDynamics::*comReference_ptr)(const TreeModel&)=0;
    void (RLS::RlsDynamics::*dcmReference_ptr)(const TreeModel&)=0;
    void (RLS::RlsDynamics::*externalWrenchReference_ptr)(const TreeModel&)=0;

    map<string, void (RLS::RlsDynamics::*)(const TreeModel&)>
    map_baseTranslationReference,
      map_baseOrientationReference,
      map_controlNodeReference,
      map_comReference,
      map_dcmReference,
      map_externalWrenchReference;

    // ******************************

    // add function
    Vector2d F2rp(const Vector6d&);
    MatrixXd weight(const TreeModel::Info&, const Vector3d&);

    // controller
    // ******************************
    // zero controller
    VectorXd zeroDynamics(const TreeModel::Info&);
    VectorXd zeroMotion(const TreeModel::Info&);
    void zeroMomentum(const TreeModel::Info&);
    void zeroDistribution(const TreeModel::Info&);
    void zeroTorque(const TreeModel::Info&);

    // velocity controller
    VectorXd baseVelocitySynergy(const TreeModel::Info&);
    VectorXd mixedVelocitySynergy(const TreeModel::Info&);

    // acceleration controller
    VectorXd workAcceleration(const TreeModel::Info&);
    VectorXd baseAccelerationSynergy(const TreeModel::Info&);
    VectorXd mixedAccelerationSynergy(const TreeModel::Info&);
    VectorXd centroidalAccelerationSynergy(const TreeModel::Info&);
    VectorXd rest_cmlC(const TreeModel::Info&);
    VectorXd rest_clCm(const TreeModel::Info&);
    VectorXd baseGeneralizedMomentum(const TreeModel::Info&);
    VectorXd mixedGeneralizedMomentum(const TreeModel::Info&);
    VectorXd accelerationSolver(const TreeModel::Info&);
    VectorXd raa(const TreeModel::Info&);
    VectorXd hogehogeMomentum(const TreeModel::Info&);

    // acceleration dumper
    VectorXd ddthD(const TreeModel::Info&);
    VectorXd ddqthD(const TreeModel::Info&);
    VectorXd ddqthinit(const TreeModel::Info&);

    // momentum controller
    void linearMomentum(const TreeModel::Info&);
    void dcmMomentum(const TreeModel::Info&);
    void centroidalAngularMomentum(const TreeModel::Info&);
    void baseAngularMomentum(const TreeModel::Info&);
    void baseMomentum(const TreeModel::Info&);
    void baseDcmMomentum(const TreeModel::Info&);
    void centroidalMomentum(const TreeModel::Info&);
    void centroidalDcmMomentum(const TreeModel::Info&);
    void centroidalCmpMomentum(const TreeModel::Info&);

    // force controller
    void baseDistribution(const TreeModel::Info&);
    void centroidalDistribution(const TreeModel::Info&);
    void centroidalDcmDistribution(const TreeModel::Info&);
    void distributionSolver(const TreeModel::Info&);

    // torque controller
    void jointSpace(const TreeModel::Info&);
    void staticControl(const TreeModel::Info&);
    void base(const TreeModel::Info&);
    void mixed(const TreeModel::Info&);
    void mixedmixed(const TreeModel::Info&);
    void crb(const TreeModel::Info&);
    void baseOpt(const TreeModel::Info&);
    void mixedOpt(const TreeModel::Info&);
    void mixedmixedOpt(const TreeModel::Info&);

    // inverse dynamics controller
    VectorXd fullDynamicsController(const TreeModel::Info&);
    VectorXd momentumInverseDynamicsController(const TreeModel::Info&);
    VectorXd highGainController(const TreeModel::Info&);
    VectorXd spatialDynamicsSolver(const TreeModel::Info&);
    VectorXd dlrSolver(const TreeModel::Info&);

    void controlMethod(const string&, const TreeModel::Info&);

    // select controller
    VectorXd (RLS::RlsDynamics::*motionController_ptr)(const TreeModel::Info&)=0;
    void (RLS::RlsDynamics::*momentumController_ptr)(const TreeModel::Info&)=0;
    void (RLS::RlsDynamics::*forceController_ptr)(const TreeModel::Info&)=0;
    void (RLS::RlsDynamics::*torqueController_ptr)(const TreeModel::Info&)=0;
    VectorXd (RLS::RlsDynamics::*inverseDynamicsController_ptr)(const TreeModel::Info&)=0;

    map<string, VectorXd (RLS::RlsDynamics::*)(const TreeModel::Info&)>
    map_motionController, map_inverseDynamicsController;
    map<string, void (RLS::RlsDynamics::*)(const TreeModel::Info&)>
    map_momentumController, map_forceController, map_torqueController;

    // ******************************

    // output config
    // velocity output config
    void velocityOutputConfig(const TreeModel::Info&);

    // acceleration output config
    void accelerationOutputConfig(const TreeModel::Info&);

    // torque output config
    void torqueOutputDesConfig(const TreeModel::Info&);
    void torqueOutputErrConfig(const TreeModel::Info&);
    void torqueOutputRefConfig(const TreeModel::Info&);
    void torqueOutputIndexConfig(const TreeModel::Info&);
    void torqueOutputIndexPrintConfig(const TreeModel::Info&);
    void torqueOutputConfig(const TreeModel::Info&);

    void outputConfig(const string&, const TreeModel::Info&);

    // readWork
    // ****************************************************************
    YAML::Node checkNode(YAML::Node&, string, int, string);
    YAML::Node checkNode(YAML::Node&, string, int, string, string);
    YAML::Node checkNode(YAML::Node&, string, int, string, string, string);
    YAML::Node checkNode(YAML::Node&, string, int, string, int, string);
    YAML::Node checkNode(YAML::Node&, string, int, int, string);
    YAML::Node checkNode(YAML::Node&, string, int, int, string, string);
    YAML::Node checkNode(YAML::Node&, string, int, int, string, string, string);
    YAML::Node checkNode(YAML::Node&, string, int, int, string, int, string);

    // update value
    template <class T> T updateValue(YAML::Node&, bool, string, int, int, string, T);
    template <class T> T updateValue(YAML::Node&, bool, string, int, int, string, int, T);
    template <class T> T updateValue(YAML::Node&, bool, string, int, int, string, int, string, T);
    template <class T> T updateValue(YAML::Node&, bool, string, int, int, string, string, T);
    template <class T> T updateValue(YAML::Node&, bool, string, int, int, string, string, string, T);

    template <class T> T readValue(YAML::Node&, string, int, string);
    template <class T> T readValue(YAML::Node&, string, int, string, int);
    template <class T> T readValue(YAML::Node&, string, int, string, int, int);
    template <class T> T readValue(YAML::Node&, string, int, string, int, string);
    template <class T> T readValue(YAML::Node&, string, int, string, string);
    template <class T> T readValue(YAML::Node&, string, int, string, string, int);
    template <class T> T readValue(YAML::Node&, string, int, string, string, string);

    template <class T> T readValue(YAML::Node&, string, int, int, string);
    template <class T> T readValue(YAML::Node&, string, int, int, string, int);
    template <class T> T readValue(YAML::Node&, string, int, int, string, int, int);
    template <class T> T readValue(YAML::Node&, string, int, int, string, int, string);
    template <class T> T readValue(YAML::Node&, string, int, int, string, string);
    template <class T> T readValue(YAML::Node&, string, int, int, string, string, int);
    template <class T> T readValue(YAML::Node&, string, int, int, string, string, string);
    // ****************************************************************

  public:
    // smiyahara: 要検討(とりあえず外乱のみを考慮し"6"にしといた)
    Vector6d virtualInput;

    // smiyahara: 名前は変えたい
    void initialize(const Config&, const TreeModel::Info&);
    void finalize();
    VectorXd rlsDynamics(const Config&, Model&, const double&);

    RlsDynamicsList dc_list;

    RlsDynamics(){}
    RlsDynamics(const Config &config, const TreeModel::Info &info){
      initialize(config, info);
    }
  };
}
