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

    string baseTranslationFeedbackControllerName;
    string baseOrientationFeedbackControllerName;
    string controlNodeAccelerationFeedbackControllerName;
    string controlNodeWrenchFeedbackControllerName;
    string comFeedbackControllerName;
    string dcmFeedbackControllerName;
    string externalWrenchFeedbackControllerName;

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
    void baseTranslationFBPI();

    // base orientation
    void baseOrientationFBPI();

    // control node acceleration
    void controlNodeAccelerationFBPI();

    // control node wrench
    void controlNodeWrenchFBFF();

    // com
    void comFBPI();
    void comFBDcmControl();

    // dcm
    void dcmFBPI();

    // external wrench
    void externalWrenchFBFF();

    void spatialFeedbackController();

    // select reference
    void (RLS::FeedbackController::*baseTranslationFeedbackController_ptr)()=0;
    void (RLS::FeedbackController::*baseOrientationFeedbackController_ptr)()=0;
    void (RLS::FeedbackController::*controlNodeAccelerationFeedbackController_ptr)()=0;
    void (RLS::FeedbackController::*controlNodeWrenchFeedbackController_ptr)()=0;
    void (RLS::FeedbackController::*comFeedbackController_ptr)()=0;
    void (RLS::FeedbackController::*dcmFeedbackController_ptr)()=0;
    void (RLS::FeedbackController::*externalWrenchFeedbackController_ptr)()=0;

    map<string, void (RLS::FeedbackController::*)()>
    map_baseTranslationFeedbackController,
      map_baseOrientationFeedbackController,
      map_controlNodeAccelerationFeedbackController,
      map_controlNodeWrenchFeedbackController,
      map_comFeedbackController,
      map_dcmFeedbackController,
      map_externalWrenchFeedbackController;

    void setModel(const TreeModelInfo&, const ControllerTreeModel&, const DesiredValueGenerator&);
    void setYamlInfo(YamlInfo&);

    void resize();
    void setMap();

    void stack();

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
