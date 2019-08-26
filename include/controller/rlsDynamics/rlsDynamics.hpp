/**
   @author Sho Miyahara 2018
*/

#ifndef RLSDYNAMICS_HPP_
#define RLSDYNAMICS_HPP_

#include <map>

#include "solver.hpp"
#include "common.hpp"

#include "yamlInfo.hpp"

#include "controllerModel.hpp"
#include "constraintModel.hpp"
#include "rlsDynamicsInfo.hpp"

#include "desiredValueGenerator.hpp"
#include "feedbackController.hpp"
#include "rlsDynamicsList.hpp"
#include "rlsDynamicsExtractor.hpp" //amiyata
#include "_extList.hpp"

namespace RLS{
  class Ext;

  class RlsDynamics:
    public Solver,
    virtual public Common
  {
  private:
    ControllerModel controllerModel;

    Ext *ext;

    struct State{
      struct State *st_ptr_in; // recursive state
      int fork; // state nums
      // string mode; // state or sequence
      string trigger; // trigger config sellect
      YAML::Node doc; // load whole of phase yaml
      int condition; // current state num
      int sequenceID; // sequence identifier for sequence trigger
      bool ext; // nursing for ext
    } topState;

    struct Sequence{
      int phase;
      double tw0;
      double twf;
    } *sequence;

    int seqNum;

    void initializeExt();
    void setModelInfo(Info&);
    void setConstraintInfo(ConstraintInfo&);
    void setDefaultConfig();

    void readControllerHeader();
    void initializeConstraintInfo();
    void resize();
    void setControllerMap();

    void initializeStateTrigger();
    void localInitialize();

    void stateScanner(struct State&); // amiyata
    void statePrinter(struct State&, int fork=0, int nest=0); // amiyata

    // state transition
    void updateSequence(const double&, const int&);
    void mapping();

    // state trigger
    // ******************************
    bool extStateTrigger;

    // trigger config
    int defaultStateTrigger(const double&, const struct State&);
    int checkFootContact(const double&, const struct State&);
    int checkContact(const double&, const struct State&);
    int sequenceTrigger(const double&, const struct State&); // amiyata
    int continuousSequence(const double&, const struct State&); // amiyata

    // state trigger
    // int (RLS::RlsDynamics::*stateTrigger_ptr)(const double&, const int)=0;
    map<string, int (RLS::RlsDynamics::*)(const double&, const struct State&)> stateTrigger_map;

    // int stateTrigger(const double&);
    // bool sequenceTrigger(const double&, const int&);
    bool stateTrigger(const double&, struct State&); // amiyata

    bool configurationManager(const double&);
    void reconfigure();

    void allReadController();
    void readController();

    void readController(vector<string>&);
    void readParameter(); // amiyata

    // control method
    // ******************************
    bool extMotionController;
    bool extMomentumController;
    bool extForceController;
    bool extTorqueController;
    bool extInverseDynamicsController;
    bool extExternalWrenchController;

    string motionControllerName;
    string operationalSpaceControllerName;
    string momentumControllerName;
    string internalForceControllerName;
    string forceControllerName;
    string torqueControllerName;
    string inverseDynamicsControllerName;

    string externalWrenchControllerName;

    // default controller
    VectorXd defaultJointController();
    VectorXd defaultConfigurationController();
    void defaultController();

    // operational space controller
    // velocity controller
    void relativeVelocityBaseMap();
    void relativeVelocityMixedMap();

    // acceleration controller
    void decomposeEndEffectorAcceleration();
    void relativeAccelerationBaseMap();
    void relativeAccelerationMixedMap();
    void relativeAccelerationCentroidalMap();

    // configuration space acceleration controller
    // velocity controller
    VectorXd baseVelocitySynergy();
    VectorXd mixedVelocitySynergy();

    // acceleration controller
    VectorXd workAcceleration();
    VectorXd baseAccelerationSynergy();
    VectorXd mixedAccelerationSynergy();
    VectorXd centroidalAccelerationSynergy();
    VectorXd rest_cmlC();
    VectorXd rest_clCm();
    VectorXd baseGeneralizedMomentum();
    VectorXd mixedGeneralizedMomentum();
    VectorXd mixedGeneralizedMomentumStacked();
    VectorXd mixedBaseAngularDecomposedMomentum();
    VectorXd mixedBaseAngularDistributedMomentum(); //amiyata
    VectorXd mixedGeneralizedDeltaAngularMomentum(); //amiyata
    VectorXd mixedGeneralizedDeltaOmegaAcceleration(); //amiyata
    VectorXd accelerationSolver();
    VectorXd rcamd();
    VectorXd mixedRelativeAngularJointAcceleration(); //amiyata
    VectorXd mixedAccelerationSynergyStacked(); //amiyata
    VectorXd RNS_Macc(); //amiyata

    // velocity dumper
    VectorXd ddthD();
    VectorXd ddqthD();
    VectorXd ddqthinit();

    // momentum controller
    void linearMomentum();
    void vrpMomentum();
    void vrpZcomMomentum(); // amiyata
    void vrpMomentumwXt(); // amiyata
    void centroidalAngularMomentum();
    void baseAngularMomentum();
    void baseMomentum();
    void baseVrpMomentum();
    void centroidalMomentum();
    void centroidalVrpMomentum();
    void centroidalVrpMomentumDamping();
    void centroidalVrpMomentumTV(); // amiyata
    void centroidalVrpRNS();
    void centroidalCmpMomentum();
    void centroidalAngularMomentumDamping(); // amiyata
    void reactionNullSpaceMomentum(); // amiyata
    void deltaMomentum(); // amiyata

    // internal force controller
    void m_internalDistribution();

    // force controller
    void baseDistribution();
    void centroidalDistribution();
    void centroidalDcmDistribution();
    void centroidalEcmpDistribution();
    void centroidalEcmpInternalDistribution(); // amiyata
    void centroidalEcmpDistributionwXt(); // amiyata
    void handWrenchControlAndCentroidalEcmpDistribution();
    void bwcDistribution(); // umekage
    void CRBWCbaseDistribution(); // umekage

    void distributionSolver();

    // torque controller
    void jointSpace();
    void staticControl();
    void base();
    void mixed();
    void mixedmixed();
    void crb();
    void baseOpt();
    void mixedOpt();
    void mixedmixedOpt();

    // inverse dynamics controller
    VectorXd fullDynamicsController();
    VectorXd momentumInverseDynamicsController();
    VectorXd highGainController();
    VectorXd spatialDynamicsSolver();
    VectorXd dlrSolver();

    // external wrench controller
    void transformExternalWrench();

    void controlMethod();

    // select controller
    VectorXd (RLS::RlsDynamics::*motionController_ptr)()=0;
    map<string, VectorXd (RLS::RlsDynamics::*)()> motionController_map;

    void (RLS::RlsDynamics::*operationalSpaceController_ptr)()=0;
    map<string, void (RLS::RlsDynamics::*)()> operationalSpaceController_map;

    void (RLS::RlsDynamics::*momentumController_ptr)()=0;
    map<string, void (RLS::RlsDynamics::*)()> momentumController_map;

    void (RLS::RlsDynamics::*internalForceController_ptr)()=0;
    map<string, void (RLS::RlsDynamics::*)()> internalForceController_map;
    void (RLS::RlsDynamics::*forceController_ptr)()=0;
    map<string, void (RLS::RlsDynamics::*)()> forceController_map;

    void (RLS::RlsDynamics::*torqueController_ptr)()=0;
    map<string, void (RLS::RlsDynamics::*)()> torqueController_map;

    VectorXd (RLS::RlsDynamics::*inverseDynamicsController_ptr)()=0;
    map<string, VectorXd (RLS::RlsDynamics::*)()> inverseDynamicsController_map;

    void (RLS::RlsDynamics::*externalWrenchController_ptr)()=0;
    map<string, void (RLS::RlsDynamics::*)()> externalWrenchController_map;

    // output config
    void outputDesConfig();
    void outputErrConfig();
    void outputRefConfig();
    void outputIndexConfig();
    // void outputIndexPrintConfig();
    void outputExtConfig();

    void outputConfig();

    // umekage convex solver
    MatrixXd compute_BWC_span(MatrixXd&);

    bool *contactFlag; //amiyata footprintを足接触切替時に保存したいので保存

    Vector2d distOffset; // amiyata 分配用 足首からのオフセット

  public:
    ControllerInfo info;

    const WorldModel *worldModel;
    const ControllerTreeModel *model;
    ConstraintModel constraintModel;

    YamlInfo yamlInfo;

    DesiredValueGenerator des;
    FeedbackController fb;

    // transform offset
    VectorXd rkk;

    // index
    // ******************************
    Matrix2d bb_Spx;
    MatrixXd cal_Sp;
    // ******************************

    // high gain control
    VectorXd thDes;

    // operational space reference
    // velocityController
    // **********************
    VectorXd cal_VcBarRef;
    VectorXd cal_VmBarRef;

    VectorXd cal_VcBBarRef;
    VectorXd cal_VmBBarRef;
    VectorXd cal_VcMBarRef;
    VectorXd cal_VmMBarRef;

    // **********************
    VectorXd cal_dVcBarRef;
    VectorXd cal_dVmBarRef;

    VectorXd cal_dVcBBarRef;
    VectorXd cal_dVmBBarRef;
    VectorXd cal_dVcMBarRef;
    VectorXd cal_dVmMBarRef;
    VectorXd cal_dVcCBarRef;
    VectorXd cal_dVmCBarRef;

    // configuration space reference
    // velocityController
    // **********************
    VectorXd dthRef;
    VectorXd dqBRef;

    VectorXd dqMRef;

    // **********************
    VectorXd ddthRef;

    VectorXd ddqBRef;
    VectorXd ddqBoptRef;

    VectorXd ddqMRef;
    VectorXd ddqMoptRef;

    VectorXd ddqwoptRef;

    // momentum
    Vector3d dpRef;
    Vector3d dlBRef;
    Vector3d dlCRef;
    Vector6d cal_dLBRef;
    Vector6d cal_dLCRef;

    // force
    VectorXd cal_FcaBarRef;
    VectorXd cal_FcBarRef;

    VectorXd input;

    // gain
    Matrix2d Kpp;

    Matrix3d KDlC;
    Matrix3d KDwC;
    MatrixXd KDth;
    MatrixXd Kthinit;
    MatrixXd KDdthH; //amiyata
    MatrixXd KDlCH; //amiyata

    // amiyata  contrrol basis matrix
    MatrixXi BwB_Diag;
    MatrixXd BwB;
    MatrixXi BwC_Diag;
    MatrixXd BwC, BwCAut;
    MatrixXi BLC_Diag;
    MatrixXd BLC, BLCAut;
    int pcD, lCcD, wBcD, wCcD;

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

    VectorXd tau;

    // others
    Vector2d F2rp(const Vector6d&);
    MatrixXd h_weight(const Vector2d&);
    MatrixXd h_weight(const Vector2d&, const Vector2d&, const Vector2d&);

    // ext
    // ********************************
    // int (RLS::Ext::*ext_stateTrigger_ptr)(RlsDynamics*, const double&)=0;
    map<string, int (RLS::Ext::*)(RlsDynamics*, const double&)> ext_stateTrigger_map;

    VectorXd (RLS::Ext::*ext_motionController_ptr)(RlsDynamics*)=0;
    map<string, VectorXd (RLS::Ext::*)(RlsDynamics*)> ext_motionController_map;
    void (RLS::Ext::*ext_momentumController_ptr)(RlsDynamics*)=0;
    map<string, void (RLS::Ext::*)(RlsDynamics*)> ext_momentumController_map;
    void (RLS::Ext::*ext_forceController_ptr)(RlsDynamics*)=0;
    map<string, void (RLS::Ext::*)(RlsDynamics*)> ext_forceController_map;
    void (RLS::Ext::*ext_torqueController_ptr)(RlsDynamics*)=0;
    map<string, void (RLS::Ext::*)(RlsDynamics*)> ext_torqueController_map;
    VectorXd (RLS::Ext::*ext_inverseDynamicsController_ptr)(RlsDynamics*)=0;
    map<string, VectorXd (RLS::Ext::*)(RlsDynamics*)> ext_inverseDynamicsController_map;
    void (RLS::Ext::*ext_externalWrenchController_ptr)(RlsDynamics*)=0;
    map<string, void (RLS::Ext::*)(RlsDynamics*)> ext_externalWrenchController_map;
    // ******************************

    struct Config{
      string controlModel;
      int controlNodeNum;
      string input;
      // string driven; // amiyata 世の中みんなstate
      // string trigger; // amiyata どんなところにもtrigger
    } config;

    // smiyahara: 要検討(とりあえず外乱のみを考慮し"6"にしといた)
    Vector6d virtualInput;

    // smiyahara: 名前は変えたい
    void initialize(const int&, const string&, Model&);
    void finalize();

    VectorXd rlsDynamics(const double&);

    ExtList extList;
    RlsDynamicsList outputList;

    RlsDynamicsExtractor extractor; // amiyata
    // vector<Vector3d> footPrintList; //amiyata

    RlsDynamics(){}
    // RlsDynamics(const int controllerID, const string &path_yaml_controller, Info &info){
    //   initialize(controllerID, path_yaml_controller, info);
    // }

#ifndef RLSDYNAMICSRTC
    ~RlsDynamics(){
      finalize();
    }
#endif
  };
}

#endif // RLSDYNAMICS_HPP_
