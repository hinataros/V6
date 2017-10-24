#include "common.hpp"
#include "interpolation.hpp"

#include "rlsVelocityList.hpp"

namespace RLS{
  class RlsVelocity:
    public Interpolation, virtual public Common{
  private:
    int c;
    MatrixXi Bc_kDiag;
    MatrixXd Bc_k;

    int m;
    MatrixXi Bm_kDiag;
    MatrixXd Bm_k;

    VectorXd cal_X;

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

    MatrixXd TC2k;
    MatrixXd cal_PcM;
    MatrixXd cal_PmM;
    MatrixXd cal_JcM;
    MatrixXd cal_JmM;

    // rename
    MatrixXd IB;
    MatrixXd HBth;
    MatrixXd Mth;

    MatrixXd BJC;

    // ******************************
    Vector3d rC0;
    Vector3d rCf;

    Vector3d rB0;
    Vector3d rBf;
    Vector3d xiB0;
    Vector3d xiBf;

    VectorXd cal_X0;
    VectorXd cal_Xf;

    Vector3d des;

    Vector3d rCtemp;
    Vector3d rBtemp;
    Vector3d xiBtemp;
    VectorXd cal_Xtemp;

    Vector3d rCDes;
    Vector3d vCDes;

    Vector3d rBDes;
    Vector3d vBDes;

    Vector3d xiBDes;
    Vector3d dxiBDes;
    Matrix3d RBDes;
    Vector3d wBDes;

    VectorXd cal_XDes;
    VectorXd cal_VDes;

    // error
    Vector3d erC;

    Vector3d erB;
    Vector3d eoB;

    Vector3d vCRef;

    Vector3d vBRef;
    Vector3d wBRef;

    Vector6d cal_VBRef;
    Vector6d cal_VMRef;

    VectorXd cal_VRef;

    // velocity controller
    VectorXd cal_VcBarRef;

    VectorXd cal_VmBarRef;
    VectorXd cal_VmTildeRef;
    MatrixXd cal_JmBar;

    VectorXd dthcRef;
    VectorXd dthmRef;

    VectorXd dthRef;
    VectorXd dqRef;

    // gain
    double kpC;

    double kpvB;
    double kpwB;

    void initialValue(Config&, Info&, Model&);
    void rename(Config&, Info&, Model&);
    void resize(Config&, Info&, Model&);
    void reset(Config&, Info&, double&);
    void readWork(Config&, Info&);
    void reconfigure(Config&, Info&);

    void decompose(Config&);

    void comReference(Config&, Info&, Model&, double&);
    void baseReference(Config&, Info&, Model&, double&);
    void endEffectorReference(Config&, Info&, Model&, double&);
    void reference(Config&, Info&, Model&, double&);

    void cl_Bcoord(Config&);
    void cl_Mcoord(Config&);
    void velocityController(Config&);

    void outputConfig(Config&);

  public:
    RlsVelocityList vc_list;

    void initialize(Config&, Info&);
    VectorXd rlsVelocity(Config&, Info&, Model&, double&);
  };
}
