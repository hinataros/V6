/**
   @author Sho Miyahara 2018
*/

#include "yamlInfo.hpp"

#include "controllerTreeModel.hpp"
#include "desiredValueGenerator.hpp"

namespace RLS{
  class FeedbackController:
    virtual public Common{
  private:
    const TreeModelInfo *info;
    const ControllerTreeModel *model;

    YamlInfo *yamlInfo;

    const DesiredValueGenerator *des;

    string baseTranslationName;
    string baseRotationName;
    string controlNodeMotionName;
    string controlNodeForceName;
    string comName;
    string dcmName;
    string externalWrenchName;

    Matrix3d KpC;
    Matrix3d KdC;

    Matrix3d KpvB;
    Matrix3d KdvB;

    Matrix3d KpwB;
    Matrix3d KdwB;

    Matrix3d KX;

    MatrixXd Kpv;
    MatrixXd Kdv;

    // base translation
    void baseTranslationPI();

    // base rotation
    void baseRotationPI();

    // control node motion
    void controlNodeMotionPI();

    // control node force
    void controlNodeForceFF();

    // com
    void comPI();
    void comDcmControl();

    // dcm
    void dcmPI();

    // external wrench
    void externalWrenchFF();

    void spatialFeedbackController();

    // select reference
    void (RLS::FeedbackController::*baseTranslation_ptr)()=0;
    void (RLS::FeedbackController::*baseRotation_ptr)()=0;
    void (RLS::FeedbackController::*controlNodeMotion_ptr)()=0;
    void (RLS::FeedbackController::*controlNodeForce_ptr)()=0;
    void (RLS::FeedbackController::*com_ptr)()=0;
    void (RLS::FeedbackController::*dcm_ptr)()=0;
    void (RLS::FeedbackController::*externalWrench_ptr)()=0;

    map<string, void (RLS::FeedbackController::*)()>
    baseTranslation_map,
      baseRotation_map,
      controlNodeMotion_map,
      controlNodeForce_map,
      com_map,
      dcm_map,
      externalWrench_map;

    void setModel(const TreeModelInfo&, const ControllerTreeModel&, const DesiredValueGenerator&);
    void setYamlInfo(YamlInfo&);

    void resize();
    void setMap();

    void stack();

    Vector3d orientationError(const Matrix3d&, const Matrix3d&);

  public:
    Vector3d erC;
    Vector3d evC;

    Vector3d erB;
    Vector3d evB;

    Vector3d eoB;
    Vector3d ewB;

    Vector3d eX;

    VectorXd cal_Ep;
    VectorXd cal_Ev;

    Vector3d vBfb;
    Vector3d dvBfb;

    Vector3d wBfb;
    Vector3d dwBfb;

    Vector6d cal_VBfb;
    Vector6d cal_dVBfb;

    Vector6d cal_VMfb;
    Vector6d cal_dVMfb;

    VectorXd cal_Vfb;
    VectorXd cal_dVfb;

    Vector3d vCfb;
    Vector3d dvCfb;

    Vector6d cal_dVCfb;

    Vector3d drXfb;

    VectorXd cal_Ffb;

    Vector6d cal_Fextfb;

    void initialize(const TreeModelInfo&, const ControllerTreeModel&, YamlInfo&, const DesiredValueGenerator&);

    void readController();
    void mapping();
    void feedbackController();
  };
}
