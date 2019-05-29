/**
   @author Sho Miyahara 2018
*/

#ifndef CONSTRAINTMODEL_HPP_
#define CONSTRAINTMODEL_HPP_

#include "constraintInfo.hpp"

#include "controllerTreeModel.hpp"

namespace RLS{
  class ConstraintModel:
    virtual public Common{
  private:
    const ControllerTreeModel *model;

    void setModel(TreeModelInfo&, const ControllerTreeModel&);
    void initializeConstraintInfo();
    void resize();

    // umekage convex solvers
    MatrixXd compute_FC_span(string);
    MatrixXd compute_CWC_span();

  public:
    struct Info{
      ConstraintInfo constraint;
      TreeModelInfo *model;
    } info;

    MatrixXi Bc_kDiag;
    MatrixXd Bc_k;

    MatrixXi Bm_kDiag;
    MatrixXd Bm_k;

    MatrixXi BpDiag;
    MatrixXd Bp;

    // objective
    // ******************************
    MatrixXd Pc;

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
    MatrixXd dBc;
    MatrixXd dBm;
    MatrixXd cal_dPc;
    MatrixXd cal_dPm;
    MatrixXd cal_dJc;
    MatrixXd cal_dJm;

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

    MatrixXd cal_JcHat;
    MatrixXd cal_JmHat;
    MatrixXd cal_dJcHat;
    MatrixXd cal_dJmHat;

    // umekage CWC matrix
    VectorXi contactLimbs;
    MatrixXd V_cwc;

    // selective matrix for forward kinematics
    Matrix6d bb_ScB;

    void initialize(TreeModelInfo&, const ControllerTreeModel&);
    void finalize();

    void reconfigure();

    // update
    // ****************
    void decompose();
    void objective();
    void rename();
    void update();

    VectorXd getControlNodeVector(const VectorXd, const string, const string);
    VectorXd getControlNodeVector(const VectorXd, const string, const int, ...);
    MatrixXd getControlNodeMatrix(const MatrixXd, const bool, const bool, const string, const string);
    MatrixXd getControlNodeMatrix(const MatrixXd, const bool, const bool, const string, const int, ...);


  };
}

#endif // CONSTRAINTMODEL_HPP_
