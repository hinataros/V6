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
    // TreeModel *model;

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
    // void setInitialValue();

  public:
    TreeModel *model; // amiyata linkが欲しい

    // initial value
    // ******************************
    VectorXd th0;
    Vector3d rB0;
    Matrix3d RB0;
    Vector3d *r0;
    Matrix3d *R0;
    Vector3d rC0;
    Vector3d rX0;
    Vector6d cal_FB0;

    VectorXd rpk0;

    // state
    // ******************************
    VectorXd th;
    VectorXd dth;

    Vector3d rB;
    Matrix3d RB;
    Vector3d vB;
    Vector3d wB;

    Vector3d wC; // amiyata

    Vector3d rC;
    Vector3d vC;

    Vector6d cal_VB;
    Vector6d cal_VM;
    Vector6d cal_VC;
    Vector3d *r;
    Matrix3d *R;
    VectorXd cal_V;
    VectorXd cal_F;

    Vector3d *rsensor;
    VectorXd cal_Fsensor;

    VectorXd dq;
    VectorXd dqM;

    double M;

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

    MatrixXd Jw; // amiyata

    // diff inertia
    MatrixXd cal_dAM;
    Matrix3d dIC;
    MatrixXd dHC;

    MatrixXd dJw; // amiyata

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
    double wX, wXt;
    double dwXt; // amiyata
    Vector3d rX, rXt;
    // ******************************

    void initialize(const WorldModel&, const TreeModelInfo&, TreeModel&);
    void finalize();
    void update();
    void update(VectorXd&); // amiyata rkk
    void setInitialValue(); // amiyata for sequence reset

  };
}

#endif // CONTROLLERTREEMODEL_HPP_
