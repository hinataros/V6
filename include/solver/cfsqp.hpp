
#ifdef CFSQP_LINK
#include "cfsqpusr.hpp"
#endif

#include "model.hpp"
#include "info.hpp"

// #include "postureGenerator.hpp"
#include "costFunctionQPpp.hpp"
// #include "comWayOpt.hpp"


namespace RLS{
  class CFSQP:
    virtual public Common{
  private:
    int nparam,nf,nineq,neq,mode,iprint,miter,neqn,nineqn,ncsrl,ncsrn,nfsr,mesh_pts[1],inform;
    double bigbnd,eps,epsneq,udelta;
    double *x,*bl,*bu,*f,*g,*lambda;
    void *cd;

    // costFunctionQPpp cost;

    void configuration();

    void Ejudgement(MatrixXd CE, VectorXd ce0, VectorXd xRet);
    void Ijudgement(MatrixXd CI, VectorXd ci0, VectorXd xRet);

  public:
    CFSQP();
    ~CFSQP();

    // postureGenerator
    // void solver(postureGenerator&, VectorXd&);

    // pseudoQPpp
    void solver(MatrixXd&, VectorXd&, VectorXd&);
    void solver(MatrixXd&, VectorXd&, string, MatrixXd&, VectorXd&, VectorXd&);
    void solver(MatrixXd&, VectorXd&, MatrixXd&, VectorXd&, MatrixXd&, VectorXd&, VectorXd&);

    // comWayOpt
    void solver(MatrixXd, MatrixXd, int, double, double, VectorXd&);

  };
}
