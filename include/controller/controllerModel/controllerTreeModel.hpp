/**
   @author Sho Miyahara 2018
*/

#ifndef CONTROLLERTREEMODEL_HPP_
#define CONTROLLERTREEMODEL_HPP_

namespace RLS{
  class ControllerTreeModel:
    virtual public Common{
  private:
    const WorldModel *worldModel;
    const TreeModelInfo *info;
    TreeModel *model;

    void contactCoordinate();
    void transform();

    void state();
    void base();
    void mix();
    void centroidal();
    void others();
    void rename();

    void cop();
    void cmp();
    void dcm();
    void index();

    void setModel(const WorldModel&, const TreeModelInfo&, TreeModel&);
    void resize();
    void setInitialValue();

  public:
    // initial value
    // ******************************
    VectorXd th0;
    Vector3d rC0;
    Vector3d rB0;
    Vector3d xiB0;
    Vector3d rX0;
    VectorXd cal_X0;
    Vector6d cal_FB0;

    VectorXd rpk0;

    // state
    // ******************************
    VectorXd th;
    VectorXd dth;

    Vector3d rB;
    Matrix3d RB;
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

    VectorXd cal_Xsensor;
    VectorXd cal_Fsensor;

    VectorXd dq;
    VectorXd dqM;

    double M;
    Vector3d ag;

    MatrixXd bb_Rk;
    MatrixXd bb_dRk;

    MatrixXd bb_TB2k;
    MatrixXd bb_dTB2k;
    MatrixXd bb_TC2k;
    MatrixXd bb_dTC2k;

    MatrixXd cal_J;
    MatrixXd cal_dJ;

    MatrixXd JB2C;
    MatrixXd dJB2C;

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
    MatrixXd Jth;
    MatrixXd dJth;

    // inertia
    MatrixXd MthHat;

    // nonlinear
    VectorXd cthHat;

    // index
    // ******************************
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

    void initialize(const WorldModel&, const TreeModelInfo&, TreeModel&);
    void update();
  };
}

#endif // CONTROLLERTREEMODEL_HPP_