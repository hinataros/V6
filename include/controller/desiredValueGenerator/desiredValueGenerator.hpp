/**
   @author Sho Miyahara 2018
*/

#ifndef DESIREDVALUEGENERATOR_HPP_
#define DESIREDVALUEGENERATOR_HPP_

#include "yamlInfo.hpp"

#include "interpolation.hpp"
#include "controllerTreeModel.hpp"

#include "walking.hpp"

namespace RLS{
  class DesiredValueGenerator:
    public Interpolation{
  private:
    const WorldModel *worldModel;
    const TreeModelInfo *info;
    const ControllerTreeModel *model;

    YamlInfo *yamlInfo;

    Walking walking;

    // boundary
    // ******************************
    Vector3d rC0;

    Vector3d rB0;
    Vector3d xiB0;

    Vector3d rX0;

    VectorXd cal_X0;

    Vector6d cal_Fext0;

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
    string desiredBaseTranslationGeneratorName;
    string desiredBaseOrientationGeneratorName;
    string *desiredControlNodeMotionGeneratorName;
    string *desiredControlNodeForceGeneratorName;
    string desiredComGeneratorName;
    string desiredDcmGeneratorName;
    string desiredExternalWrenchGeneratorName;

    int desiredBaseTranslationGeneratorNum;
    int desiredBaseOrientationGeneratorNum;
    int *desiredControlNodeMotionGeneratorNum;
    int *desiredControlNodeForceGeneratorNum;
    int desiredComGeneratorNum;
    int desiredDcmGeneratorNum;
    int desiredExternalWrenchGeneratorNum;

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
      VectorXd cal_Xfabs;
      VectorXd cal_XpreDesabs;

      Vector3d rCf;
      Vector3d rCpreDes;
      Vector3d rXf;
      Vector3d rXpreDes;

      VectorXd cal_Ff;
      VectorXd cal_FpreDes;

      Vector6d cal_Fextf;
      Vector6d cal_FextpreDes;

      VectorXd cal_Xtd;
    } *sequence;

    // // EE reference
    // int referenceSequence;
    // VectorXd cal_Xtd;
    // // ****************


    // desired value  generator
    // ******************************
    // base translation
    void desiredBaseTranslationZeroGenerator(const double&);
    void desiredBaseTranslationGeneratorCP(const double&);

    // base orientation
    void desiredBaseOrientationZeroGenerator(const double&);
    void desiredBaseOrientationGeneratorCP(const double&);

    // control node acceleration
    void desiredControlNodeMotionZeroGenerator(const int&, const double&);
    void desiredControlNodeMotionGeneratorCP(const int&, const double&);
    void desiredControlNodeMotionGeneratorCPabs(const int&, const double&);
    void desiredControlNodeMotionGeneratorWalking(const int&, const double&);

    // control node wrench
    void desiredControlNodeForceZeroGenerator(const int&, const double&);
    void desiredControlNodeForceGeneratorCP(const int&, const double&);

    // com
    void desiredComZeroGenerator(const double&);
    void desiredComGeneratorCP(const double&);

    // dcm
    void desiredDcmZeroGenerator(const double&);
    void desiredDcmGeneratorCP(const double&);
    void dcmHTWalking(const double&);

    // external wrench
    void desiredExternalWrenchZeroGenerator(const double&);
    void desiredExternalWrenchGeneratorCP(const double&);

    // select desired value generator
    void (RLS::DesiredValueGenerator::*desiredBaseTranslationGenerator_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*desiredBaseOrientationGenerator_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*desiredComGenerator_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*desiredDcmGenerator_ptr)(const double&)=0;
    void (RLS::DesiredValueGenerator::*desiredExternalWrenchGenerator_ptr)(const double&)=0;

    map<string, void (RLS::DesiredValueGenerator::*)(const double&)>
    desiredBaseTranslationGenerator_map,
      desiredBaseOrientationGenerator_map,
      desiredComGenerator_map,
      desiredDcmGenerator_map,
      desiredExternalWrenchGenerator_map;

    void (RLS::DesiredValueGenerator::**desiredControlNodeMotionGenerator_ptr)(const int&, const double&);
    map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)> *desiredControlNodeMotionGenerator_map;
    void (RLS::DesiredValueGenerator::**desiredControlNodeForceGenerator_ptr)(const int&, const double&);
    map<string, void (RLS::DesiredValueGenerator::*)(const int&, const double&)> *desiredControlNodeForceGenerator_map;

    void setModel(const WorldModel&, const TreeModelInfo&, const ControllerTreeModel&);
    void setYamlInfo(YamlInfo&);

    void resize();
    void resizeSequence();
    void resizeState();
    void setMap();
    void setInitialBoundary();
    void initializeWalking();

  public:
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

    VectorXd cal_FDes;

    Vector6d cal_FextDes;

    void initialize(const WorldModel&, const TreeModelInfo&, const ControllerTreeModel&, YamlInfo&);
    void finalize();

    void readController();
    void update(const double&);
    void update(const double&, const int&);
    void mapping();
    void desiredValueGenerator(const double&);

    // ~DesiredValueGenerator(){
    //   finalize();
    // }
  };
}

#endif // DESIREDVALUEGENERATOR_HPP_
