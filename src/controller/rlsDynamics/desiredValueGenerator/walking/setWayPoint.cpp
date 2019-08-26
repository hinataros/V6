/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"


void RLS::Walking::setWayPoint()
{
  if(debug) DEBUG;

  rf.col(0) = rCw0;
  rf.col(0)(2) = 0.; // reset height

  for(int i=1; i<vwpNum+1; i++){
    rf.col(i) = vwp[i-1].head(3);

    if(i<vwpNum){
      // first waypoint is right foot
      if(i%2==0)
        rf.col(i)(1) -= ht_config.offset;
      else
        rf.col(i)(1) += ht_config.offset;
    }
  }

  // for dcm velocity convergence
  rf.col(vwpNum+1) = vwp[vwpNum-1].head(3);

  // ******************************
  Vector3d Dzvrp = (Vector3d()<<0., 0., g/(wX*wX)).finished();

  // final desired VRP
  // rvrpTd.col(ht_config.convergenceNum) is unused
  rvrpHd.col(ht_config.convergenceNum) = rf.col(ht_config.convergenceNum) + Dzvrp;

  Vector3d toeOffset = (Vector3d()<<ht_config.toe, 0., 0.).finished();
  Vector3d heelOffset = (Vector3d()<<ht_config.heel, 0., 0.).finished();

  // backward calculation
  for(int i=ht_config.convergenceNum-1; i>0; i--){
    if(i==ht_config.convergenceNum-1){
      rvrpTd.col(i) = rf.col(i) + Dzvrp;
      rvrpHd.col(i) = rf.col(i) + Dzvrp;
    }
    else if(i==ht_config.convergenceNum-2){
      rvrpTd.col(i) = rf.col(i) + Dzvrp;
      rvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
    }
    else if(i==1){
      rvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
      rvrpHd.col(i) = rf.col(i) + Dzvrp;
    }
    else{
      rvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
      rvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
    }
  }

  rvrpHd.col(0) = rf.col(0) + Dzvrp;
  // rvrpTd.col(0) is not calculated

  for(int i=1; i<vwpNum+1; i++){
    rvrpTd.col(i) = xi2R(vwp[i-1].tail(3)).transpose() * rvrpTd.col(i);
    rvrpHd.col(i) = xi2R(vwp[i-1].tail(3)).transpose() * rvrpHd.col(i);
  }

  // o(rvrpTd);
  // o(rvrpHd);
  // gc;
}
