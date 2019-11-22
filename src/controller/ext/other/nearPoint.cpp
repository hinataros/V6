/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

Vector2d RLS::Ext::nearPoint(Vector2d position, polygon area)
{

  Vector2d returnPoint;

  int pNum = bg::num_points(area);

  point P(position(0), position(1));

  double d;

  Vector2d PointA, PointB;

  int nearCount = 0;
  int nearID;
  Vector2d sidePoint[2];

  d = bg::distance(P, area);
      
  for(int k=0; k<pNum-1; k++){

    PointA <<
      bg::get<0>(area.outer()[k]),
      bg::get<1>(area.outer()[k]);

    PointB <<
      bg::get<0>(area.outer()[k+1]),
      bg::get<1>(area.outer()[k+1]);

    bg::model::linestring<point> sideEdge = boost::assign::list_of<point>(PointA(0), PointA(1))(PointB(0), PointB(1));

    if(abs(d - bg::distance(P, sideEdge)) <= 1.0e-4){
      nearID = k;
      nearCount++;
    }
  }
  if(nearCount == 1){
    sidePoint[0] <<
      bg::get<0>(area.outer()[nearID]),
      bg::get<1>(area.outer()[nearID]);

    sidePoint[1] <<
      bg::get<0>(area.outer()[nearID+1]),
      bg::get<1>(area.outer()[nearID+1]);

    Vector2d nearVec = sidePoint[1] - sidePoint[0];
    double s = sqrt( (pow((sidePoint[0] - position).norm(), 2) - pow(d, 2)) / pow(nearVec.norm(), 2) );

    returnPoint = sidePoint[0] + s*nearVec;
  }
      
  else if(nearCount == 2){
    if(nearID == pNum-2){
      point end(bg::get<0>(area.outer()[0]), bg::get<1>(area.outer()[0]));
      if(abs(d - bg::distance(P, end)) <= 1.0e-4){
        nearID = 0;
      }
    }

    returnPoint <<
      bg::get<0>(area.outer()[nearID]),
      bg::get<1>(area.outer()[nearID]);

  }

  return returnPoint;

}
