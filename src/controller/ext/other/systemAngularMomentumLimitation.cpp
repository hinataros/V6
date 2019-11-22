/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::systemAngularMomentumLimitation(RlsDynamics *io)
{

  Vector3d rvrpRef = io->model->rX - io->fb.drXfb/io->model->wX;
  // Vector3d rvrpRef = io->model->rC - io->fb.dvCfb/pow(io->model->wX,2);
  Vector2d rcmpRef = rvrpRef.head(2);
  double g = 9.81;

  MatrixXd S2X = MatrixXd::Zero(2,2);
  S2X <<
    0, 1,
    -1, 0;

  Vector2d DeltaCMP =  - 1 / (io->model->M * g) * S2X * io->dlCRef.head(2);

  // // ///////////////////////////////////////////////////

  Vector2d rpRef = rcmpRef + DeltaCMP;


  point CoPRef(rpRef(0), rpRef(1));

  bool CoPIn = bg::intersects(CoPRef, BoS);

  int pNum = bg::num_points(BoS);

  // // ///////////////////////////////////////////////////

  if(!CoPIn){
    Vector2d rpLimit;

    if(pNum == 0)
      BoS = BoSPre;
    
    if((io->constraintModel.info.constraint.c.all == 12 && ((io->model->cal_V.segment(3,3)).norm() >= 1.0 || (io->model->cal_V.segment(9,3)).norm() >= 1.0) ) ||
       (io->constraintModel.info.constraint.c.all == 6 && io->constraintModel.info.constraint.c.controlNode[0] == 6 && (io->model->cal_V.segment(3,3)).norm() >= 1.0) ||
       (io->constraintModel.info.constraint.c.all == 6 && io->constraintModel.info.constraint.c.controlNode[1] == 6 && (io->model->cal_V.segment(9,3)).norm() >= 1.0)
       )
      {
        rpLimit <<
          bg::get<0>(bg::return_centroid<point>(BoS)),
          bg::get<1>(bg::return_centroid<point>(BoS));
      }
    else{
      rpLimit = nearPoint(rpRef, BoS);
    }
    
    BoSPre = BoS;

    io->dlCRef.head(2) = - io->model->M * g * S2X * (rcmpRef - rpLimit);

  }
}
