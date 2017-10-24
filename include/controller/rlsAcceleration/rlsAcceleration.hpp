#include "common.hpp"
#include "interpolation.hpp"

#include "rlsAccelerationList.hpp"

namespace RLS{
  class RlsAcceleration:
    public Interpolation, virtual public Common{
  private:
    int c;
    MatrixXi Bc_kDiag;
    MatrixXd Bc_k;

    int m;
    MatrixXi Bm_kDiag;
    MatrixXd Bm_k;

    // ******************************
    Vector6d cal_VB;
    VectorXd cal_X;
    VectorXd cal_V;

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
    Vector3d rB0;
    Vector3d rBf;
    Vector3d xiB0;
    Vector3d xiBf;

    VectorXd cal_X0;
    VectorXd cal_Xf;

    Vector3d des;

    Vector3d rBtemp;
    Vector3d xiBtemp;
    VectorXd cal_Xtemp;

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
    VectorXd cal_VDes;
    VectorXd cal_dVDes;

    // error
    Vector3d erB;
    Vector3d evB;
    Vector3d eoB;
    Vector3d ewB;

    Vector3d dvBRef;
    Vector3d dwBRef;
    Vector6d cal_dVBRef;

    VectorXd cal_dVRef;

    // acceleration controller
    VectorXd cal_dVcBarRef;

    VectorXd cal_dVmBarRef;
    VectorXd cal_dVmTildeRef;
    MatrixXd cal_JmBar;

    // nonlinear
    VectorXd hc;
    VectorXd hm;
    VectorXd h;

    VectorXd ddthcRef;
    VectorXd ddthmRef;

    VectorXd ddthRef;
    VectorXd ddqRef;

    // gain
    double kpvB;
    double kpwB;
    double kdvB;
    double kdwB;

    void initialValue(Config&, Info&, Model&);
    void rename(Config&, Info&, Model&);
    void resize(Config&, Info&, Model&);
    void reset(Config&, Info&, double&);
    void readWork(Config&, Info&);
    void reconfigure(Config&, Info&);

    void decompose(Config&);

    void baseReference(Config&, Info&, Model&, double&);
    void endEffectorReference(Config&, Info&, Model&, double&);
    void reference(Config&, Info&, Model&, double&);

    void cl_Bcoord(Config&, Model&);
    void accelerationController(Config&, Model&);

    void outputConfig(Config&);

  public:
    RlsAccelerationList ac_list;
    void initialize(Config&, Info&);

    VectorXd rlsAcceleration(Config&, Info&, Model&, double&);
  };
}
