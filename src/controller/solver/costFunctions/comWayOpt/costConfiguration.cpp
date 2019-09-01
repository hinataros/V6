#include "config.hpp"
#include "common.hpp"

#include "walkingFunction.hpp"
#include "comWayOpt.hpp"


RLS::comWayOpt::comWayOpt(MatrixXd vrpWay, MatrixXd fwp, int ipDimention, double omega)
{
  if(CWO_DEBUG) DEBUG;

  vwp = vrpWay;
  ipDim = ipDimention;
  wX = omega;

  // rCnum = fwp.cols()-1;
  rCnum = vwp.cols();
  Tnum = vwp.cols() - 1;
  // nparam = Tnum;

  comDes = VectorXd::Zero(3*Tnum);

  for(int i=0; i<Tnum/2; i++)
    comDes.segment((i*2)*3,3) = comDes.segment((i*2+1)*3,3) = fwp.col(i);

  Cp = wf.makeCMat(ipDim*2, 1./wX);
  Cm = wf.makeCMat(ipDim*2, -1./wX);

  WT = MatrixXd::Identity(Tnum, Tnum);
  WC = MatrixXd::Identity(3*Tnum, 3*Tnum);
}

RLS::comWayOpt::comWayOpt()
{

}

RLS::comWayOpt::~comWayOpt()
{

}
