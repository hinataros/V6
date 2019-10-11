/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::baseOfSupport(RlsDynamics *io)
{
  double margineX = 1.0e-2;
  double margineY = 1.0e-2;

  Vector2d pointF[2][4];
  Vector2d corner[4];

  corner[0] << 5.8e-2 - margineX, 3.15e-2 - margineY;
  corner[1] << -4.0e-2 + margineX, 3.15e-2 - margineY;
  corner[2] << -4.0e-2 + margineX, -3.15e-2 + margineY;
  corner[3] << 5.8e-2 - margineX, -3.15e-2 + margineY;
  

  for(int i=0; i<2; i++){
    for(int j=0; j<4; j++){
      pointF[i][j] = io->model->r[i].head(2) + io->model->R[i].block(0,0,2,2)*corner[j];
    }
  }

  for(int i=0; i<2; i++){
    bg::exterior_ring(Foot[i]) = boost::assign::list_of<point>
      (pointF[i][0](0), pointF[i][0](1))
      (pointF[i][1](0), pointF[i][1](1))
      (pointF[i][2](0), pointF[i][2](1))
      (pointF[i][3](0), pointF[i][3](1))
      (pointF[i][0](0), pointF[i][0](1))
      ;
  }

  if(io->constraintModel.info.constraint.c.all != 0){
    floating = false;

    if(io->constraintModel.info.constraint.c.controlNode[0] == 6){
      BoS = Foot[0];
    }

    if(io->constraintModel.info.constraint.c.controlNode[1] == 6){
      BoS = Foot[1];
    }

    if(io->constraintModel.info.constraint.c.all == 12){
      polygon all;

      bg::exterior_ring(all) = boost::assign::list_of<point>
        (pointF[0][0](0), pointF[0][0](1))
        (pointF[0][1](0), pointF[0][1](1))
        (pointF[0][2](0), pointF[0][2](1))
        (pointF[0][3](0), pointF[0][3](1))
        (pointF[1][0](0), pointF[1][0](1))
        (pointF[1][1](0), pointF[1][1](1))
        (pointF[1][2](0), pointF[1][2](1))
        (pointF[1][3](0), pointF[1][3](1))
        (pointF[0][0](0), pointF[0][0](1))
        ;

      bg::convex_hull(all, BoS);

    }
    
  }
  else{
    floating = true;
  }

}
