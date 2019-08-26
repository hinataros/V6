#include "config.hpp"
#include "common.hpp"

#include "comWayOpt.hpp"


RLS::comWayOpt::comWayOpt(MatrixXd vwp, MatrixXd fwp, int ipDim, double wX)
{
  this->vwp = vwp;
  this->ipDim = ipDim;

  // rCnum = fwp.cols()-1;
  rCnum = vwp.cols();
  Tnum = vwp.cols() - 1;

  comDes = VectorXd::Zero(3*Tnum);

  for(int i=0; i<rCnum; i++)
    comDes.segment(i*2*3,3) = comDes.segment(i*2*3+3,3) = fwp.col(i);

  Cp = wf.makeCMat(ipDim*2, 1./wX);
  Cm = wf.makeCMat(ipDim*2, -1./wX);
}

RLS::comWayOpt::comWayOpt()
{

}

RLS::comWayOpt::~comWayOpt()
{

}
