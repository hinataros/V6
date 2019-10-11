/**
   @author Sho Miyahara 2018
*/

#ifndef DESIREDVALUEGENERATOR_HPP_
#define DESIREDVALUEGENERATOR_HPP_

#include "yamlInfo.hpp"

#include "quaternion.hpp"

#include "interpolation.hpp"
#include "controllerTreeModel.hpp"
#include "constraintModel.hpp"

#include "walking.hpp"

namespace RLS{
  class DesiredValueGenerator:
    public Interpolation{
  private:
    const WorldModel *worldModel;
    const TreeModelInfo *info;
    const ControllerTreeModel *model;
    ConstraintModel *constraintModel;

    YamlInfo *yamlInfo;

    Walking walking;

    // struct State{
    //   int num;
    //
    //   Vector3d rBpreDes;
    //   Vector3d vBpreDes;
    //   Vector3d xiBpreDes;
    //   Vector3d dxiBpreDes;
    //   Vector3d rCpreDes;
    //   VectorXd cal_XpreDes;
    //   VectorXd cal_VpreDes;
    //
    //   Vector3d vCpreDes;
    //   Vector3d rXpreDes;
    //   Vector3d drXpreDes;
    // } state; // amiyata

    // trajectory
    // ******************************
    string baseTranslationName;
    string baseRotationName;
    string *controlNodeTranslationName;
    string *controlNodeRotationName;
    string *controlNodeForceName;
    string *controlNodeMomentName;
    string comName;
    string dcmName;
    string externalWrenchName;

    int baseTranslationNum;
    int baseRotationNum;
    int *controlNodeTranslationNum;
    int *controlNodeRotationNum;
    int *controlNodeForceNum;
    int *controlNodeMomentNum;
    int comNum;
    int dcmNum;
    int externalWrenchNum;

    bool baseTranslationSpec;
    bool baseRotationSpec;
    bool *controlNodeTranslationSpec;
    bool *controlNodeRotationSpec;
    bool *controlNodeForceSpec;
    bool *controlNodeMomentSpec;
    bool comSpec;
    bool dcmSpec;
    bool externalWrenchSpec;

    // double *tw0;
    // double *twf; // amiyata

    Quaternion4d dqBDes;
    Quaternion4d ddqBDes;

    Quaternion4d *dqDes;
    Quaternion4d *ddqDes;

    Vector3d rB0;
    Quaternion4d qB0;
    Matrix3d RB0; // amiyata for relative disired values
    Vector3d *r0;
    Quaternion4d *q0;
    Vector3d rC0;
    Vector3d rX0;
    Vector6d cal_Fext0;

    Vector3d rBpreDes;
    Quaternion4d qBpreDes;
    Vector3d *rpreDes;
    Vector3d *rpreDesabs;
    Quaternion4d *qpreDes;
    Quaternion4d *qpreDesabs;
    Vector3d *fpreDes;
    Vector3d *npreDes;
    Vector3d rCpreDes;
    Vector3d rXpreDes;
    Vector3d rXpreDesabs;

    // amiyata 前回の最終値設定
    // Vector3d rBfinCur;
    // Quaternion4d qBfinCur;
    // Vector3d *rfinCur;
    // Vector3d *rfinCurabs;
    // Quaternion4d *qfinCur;
    // Quaternion4d *qfinCurabs;
    // Vector3d *ffinCur;
    // Vector3d *nfinCur;
    // Vector3d rCfinCur;
    // Vector3d rXfinCur;
    // Vector3d rXfinCurabs;
    bool rBfinCur;
    bool qBfinCur;
    bool *rfinCur;
    bool *qfinCur;
    bool *ffinCur;
    bool *nfinCur;
    bool rCfinCur;
    bool rXfinCur;

    Vector3d rBf;
    Vector3d xiBf;
    Quaternion4d qBf;
    Vector3d *rf;
    Vector3d *rfabs;
    Vector3d *xif;
    Vector3d *xifabs;
    Quaternion4d *qf;
    Quaternion4d *qfabs;
    Vector3d *ff;
    Vector3d *nf;
    Vector3d rCf;
    Vector3d rXf;
    Vector3d rXfabs;

    Vector6d cal_Fextf;
    Vector6d cal_FextpreDes;

    // Vector3d *rtd; // amiyata
    double *rAp;

    // desired value  generator
    // ******************************
    // base translation
    void baseTranslationDefault(const double&);
    void baseTranslationCP(const double&);

    // base rotation
    void baseRotationDefault(const double&);
    void baseRotationCP(const double&);

    // control node translation
    void controlNodeTranslationDefault(const int&, const double&);
    void controlNodeTranslationCP(const int&, const double&);
    void controlNodeTranslationCPabs(const int&, const double&);
    void controlNodeTranslationSwing(const int&, const double&);
    void controlNodeTranslationSwingabs(const int&, const double&); // amiyata

    // control node rotation
    void controlNodeRotationDefault(const int&, const double&);
    void controlNodeRotationCP(const int&, const double&);
    void controlNodeRotationCPabs(const int&, const double&);

    // control node force
    void controlNodeForceDefault(const int&, const double&);
    void controlNodeForceCP(const int&, const double&);

    // control node moment
    void controlNodeMomentDefault(const int&, const double&);
    void controlNodeMomentCP(const int&, const double&);

    // com
    void comDefault(const double&);
    void comCP(const double&);
    void comHTWalking(const double&); // amiyata

    // dcm
    void dcmDefault(const double&);
    void dcmCP(const double&);
    void dcmCPabs(const double&); // amiyata
    void dcmHTWalking(const double&);
    void dcmvrpHTWalking(const double&); // amiyata

    // external wrench
    void externalWrenchDefault(const double&);
    void externalWrenchCP(const double&);
    void externalWrenchStep(const double&);

    // unit Spline
    void zeroToOneSpline(const int&, const double&);

    // select desired value generator
    void (RLS::DesiredValueGenerator::*baseTranslation_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*baseRotation_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*com_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*dcm_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*externalWrench_ptr)(const double&)=0;

    void (RLS::DesiredValueGenerator::**controlNodeTranslation_ptr)(const int&, const double&);
    void (RLS::DesiredValueGenerator::**controlNodeRotation_ptr)(const int&, const double&);
    void (RLS::DesiredValueGenerator::**controlNodeForce_ptr)(const int&, const double&);
    void (RLS::DesiredValueGenerator::**controlNodeMoment_ptr)(const int&, const double&);

    map<string, void (RLS::DesiredValueGenerator::*)(const double&)> baseTranslation_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const double&)> baseRotation_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const double&)> com_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const double&)> dcm_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const double&)> externalWrench_map;

    map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)> *controlNodeTranslation_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)> *controlNodeRotation_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)> *controlNodeForce_map;
    map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)> *controlNodeMoment_map;

    void setModel(const WorldModel&, const TreeModelInfo&, const ControllerTreeModel&, ConstraintModel&);
    void setYamlInfo(YamlInfo&);

    void resize();
    // void resizeState(); // amiyata state使ってない
    void setMap();
    // void setInitialBoundary();
    void initializeWalking();

  public:
    Vector3d rBDes;
    Vector3d vBDes;
    Vector3d dvBDes;

    Matrix3d RBDes;
    Quaternion4d qBDes;
    Vector3d wBDes;
    Vector3d dwBDes;

    Vector3d rCDes;
    Vector3d vCDes;
    Vector3d dvCDes;

    Vector3d rXDes;
    Vector3d drXDes;

    Vector3d *rDes;
    Matrix3d *RDes;
    Quaternion4d *qDes;
    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    VectorXd cal_FDes;

    Vector6d cal_FextDes;

    Vector3d zeroToOne; // amiyata

    double *tw0;
    double *twf; // amiyata

    void initialize(const WorldModel&, const TreeModelInfo&, const ControllerTreeModel&, ConstraintModel&, YamlInfo&);
    void finalize();

    void readController();
    void update(const double&);
    void updatePres(); // amiyata
    void update(const double&, const int&);
    void mapping();
    void desiredValueGenerator(const double&);

    void setInitialBoundary(); // amiyata for sequence reset
    void resetWalking(const double&); // amiyata for sequence reset

    int rvrpCalc; // rvrpの計算方法が制御法によって違う

    // ~DesiredValueGenerator(){
    //   finalize();
    // }
  };
}

#endif // DESIREDVALUEGENERATOR_HPP_
