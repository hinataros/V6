#include "config.hpp"
#include "common.hpp"

#include "walkingFunction.hpp"
#include "comWayOpt.hpp"
#include "cfsqp.hpp"

// #include <functional>

// #include <boost/bind.hpp>
// #include <boost/function.hpp>


// void RLS::CFSQP::solver(postureGenerator& pg, VectorXd& xRet)
// {
//   nparam = pg.nparam;
//   nineqn = 0; //非線形拘束
//   nineq = pg.ni;
//   neqn = 0; //非線形拘束
//   neq = pg.ne;
//
//   configuration();
//   // cost.initialSearcher(x);
//   for(int i(0); i<xRet.rows(); i++)
//     x[i] = xRet(i);
//
//   #ifdef CFSQP_LINK
//     cfsqpspace::cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
//       mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,f,g,lambda,
//       pg.objection,pg.constraint,pg.gradientObjection,pg.gradientConstraint,cd);
//   #endif
//
//   xRet = arrayd2Vector(nparam, x);
//
// }

// pseudo QuadProgpp
void RLS::CFSQP::solver(MatrixXd& G, VectorXd& g0, VectorXd& xRet)
{
  MatrixXd Czero = MatrixXd::Zero(0, xRet.size());
  VectorXd czero = VectorXd::Zero(0);

  solver(G, g0, Czero, czero, Czero, czero, xRet);
}

void RLS::CFSQP::solver(MatrixXd& G, VectorXd& g0, string c, MatrixXd& C, VectorXd& c0, VectorXd& xRet)
{
  MatrixXd Czero = MatrixXd::Zero(0, xRet.size());
  VectorXd czero = VectorXd::Zero(0);

  if(c=="e"){
    solver(G, g0, C, c0, Czero, czero, xRet);
  }
  if(c=="i"){
    solver(G, g0, Czero, czero, C, c0, xRet);
  }
}

void RLS::CFSQP::solver(MatrixXd& G, VectorXd& g0, MatrixXd& CE, VectorXd& ce0, MatrixXd& CI, VectorXd& ci0, VectorXd& xRet)
{

  if(CE.rows() != ce0.rows() || CI.rows() != ci0.rows() || CE.cols() != xRet.rows() || CI.cols() != xRet.rows()){
    std::cout << "element size does not match!!" << std::endl;
    xRet = VectorXd::Zero(xRet.rows());
    return;
  }

  nparam = xRet.rows();
  nineqn = 0; //非線形拘束
  nineq = CI.rows();
  neqn = 0; //非線形拘束
  neq = CE.rows();

  costFunctionQPpp cost;
  cost.configuration(G, g0, CE, ce0, CI, ci0);
  configuration();
  cost.initialSearcher(x);

  // std::function<void(int, int, double *, double *,void *)> objc = std::bind(&RLS::costFunctionQPpp::objection, &cost, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4, placeholders::_5);
  // std::function<void(int,int,double *,double *, void *,void *)> grob = std::bind(&RLS::costFunctionQPpp::gradientObjection, &cost, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4, placeholders::_5, placeholders::_6);
  // std::function<void(int,int,double *,double *,void *)> cnst = std::bind(&RLS::costFunctionQPpp::constraint, &cost, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4, placeholders::_5);
  // std::function<void(int,int,double *,double *, void *,void *)> grcn = std::bind(&RLS::costFunctionQPpp::gradientConstraint, &cost, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4, placeholders::_5, placeholders::_6);

  #ifdef CFSQP_LINK
    cfsqpspace::cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
      mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,f,g,lambda,
      cost.objection,cost.constraint,cost.gradientObjection,cost.gradientConstraint,cd);
    // cfsqpspace::cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
    //   mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,f,g,lambda,
    //   objc,cnst,grob,grcn,cd);
  #endif

  xRet = arrayd2Vector(nparam, x);
  cost.preX = xRet;

  if(CE.rows() != 0)
    Ejudgement(CE, ce0, xRet);
  if(CI.rows() != 0)
    Ijudgement(CI, ci0, xRet);
}

// comWayOpt
void RLS::CFSQP::solver(MatrixXd vwp, MatrixXd fwp, int ipDim, double wX, double init, VectorXd &xRet)
{
  nparam = vwp.cols() - 1;
  nineqn = 0; //非線形拘束
  nineq = nparam;
  neqn = 0; //非線形拘束
  neq = 0;

  // comWayOpt cost;
  comWayOpt cost(vwp, fwp, ipDim, wX);
  // cost.configuration(vwp, fwp, ipDim, wX);
  configuration();
  // cost.initialSearcher(nparam, x, init);
  cost.initialSearcher(nparam, x);

  #ifdef CFSQP_LINK
    cfsqpspace::cfsqp(nparam,nf,nfsr,nineqn,nineq,neqn,neq,ncsrl,ncsrn,mesh_pts,
      mode,iprint,miter,&inform,bigbnd,eps,epsneq,udelta,bl,bu,x,f,g,lambda,
      cost.objection,cost.constraint,cost.gradientObjection,cost.gradientConstraint,cd);
  #endif

  xRet = arrayd2Vector(nparam, x);

  o(xRet);
  gc;
}
