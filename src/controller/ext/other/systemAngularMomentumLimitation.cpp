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

  Vector2d rcopRef = rcmpRef + DeltaCMP;


  point CMPRef(rcmpRef(0), rcmpRef(1));
  point CoPRef(rcopRef(0), rcopRef(1));
  point CoPCur(io->model->rp(0), io->model->rp(1));

  bool CMPIn = bg::intersects(CMPRef, BoS);
  bool CoPIn = bg::intersects(CoPRef, BoS);
  bool EMSTOP = bg::disjoint(CoPCur, BoS);

  int pNum = bg::num_points(BoS);

  // // ///////////////////////////////////////////////////

  if(!CoPIn){
    Vector2d rpLimit;
    double d;

    Vector2d PointA, PointB;

    int nearCount = 0;
    int nearID;
    Vector2d nearPoint[2];

    d = bg::distance(CoPRef, BoS);
      
    for(int k=0; k<pNum-1; k++){

      PointA <<
        bg::get<0>(BoS.outer()[k]),
        bg::get<1>(BoS.outer()[k]);

      PointB <<
        bg::get<0>(BoS.outer()[k+1]),
        bg::get<1>(BoS.outer()[k+1]);

      bg::model::linestring<point> sideEdge = boost::assign::list_of<point>(PointA(0), PointA(1))(PointB(0), PointB(1));

      if(abs(d - bg::distance(CoPRef, sideEdge)) <= 1.0e-4){
        nearID = k;
        nearCount++;
      }
    }
    if(nearCount == 1){
      nearPoint[0] <<
        bg::get<0>(BoS.outer()[nearID]),
        bg::get<1>(BoS.outer()[nearID]);

      nearPoint[1] <<
        bg::get<0>(BoS.outer()[nearID+1]),
        bg::get<1>(BoS.outer()[nearID+1]);

      Vector2d nearVec = nearPoint[1] - nearPoint[0];
      double s = sqrt( (pow((nearPoint[0] - rcopRef).norm(), 2) - pow(d, 2)) / pow(nearVec.norm(), 2) );

      rpLimit = nearPoint[0] + s*nearVec;
    }
      
    else if(nearCount == 2){
      if(nearID == pNum-2){
        point end(bg::get<0>(BoS.outer()[0]), bg::get<1>(BoS.outer()[0]));
        if(abs(d - bg::distance(CoPRef, end)) <= 1.0e-4){
          nearID = 0;
        }
      }

      rpLimit <<
        bg::get<0>(BoS.outer()[nearID]),
        bg::get<1>(BoS.outer()[nearID]);

    }

    else{
      cout << "error" << endl;
    }

    if(EMSTOP){
      // rpLimit <<
      //   bg::get<0>(bg::return_centroid<point>(BoS)),
      //   bg::get<1>(bg::return_centroid<point>(BoS));
      // rpLimit = rpLimit + (rpLimit - io->model->rp);
    }

    io->dlCRef.head(2) = - io->model->M * g * S2X * (rcmpRef - rpLimit);

  }

  bg::clear(BoS);
  bg::clear(Foot[0]);
  bg::clear(Foot[1]);

}
