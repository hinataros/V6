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

  //for opt
  vwpOpt.col(0) = rf.col(0);

  for(int i=1; i<vwpNum+1; i++){
    rf.col(i) = vwp[i-1].head(3);
    vwpOpt.col(i) = vwp[i-1].head(3);


    // if(i<vwpNum){
    //   // first waypoint is right foot
    //   if(i%2==0)
    //     rf.col(i)(1) -= ht_config.offset;
    //   else
    //     rf.col(i)(1) += ht_config.offset;
    // }
  }

  // for dcm velocity convergence
  rf.col(vwpNum+1) = vwp[vwpNum-1].head(3);

  // ******************************
  Vector3d Dzvrp = (Vector3d()<<0., 0., g/(wX*wX)).finished();
  MatrixXd offsetV = MatrixXd::Zero(3, ht_config.convergenceNum);
  MatrixXd offsetT = MatrixXd::Zero(3, ht_config.convergenceNum);
  MatrixXd offsetH = MatrixXd::Zero(3, ht_config.convergenceNum);

  for(int i=1; i<(ht_config.convergenceNum-1); i++){
    if(i%2==0)
      offsetV.col(i)(1) -= ht_config.offset;
    else
      offsetV.col(i)(1) += ht_config.offset;
  }

  Vector3d toeOffset = (Vector3d()<<ht_config.toe, 0., 0.).finished();
  Vector3d heelOffset = (Vector3d()<<ht_config.heel, 0., 0.).finished();

  // backward calculation
  for(int i=ht_config.convergenceNum-1; i>0; i--){
    if(i==ht_config.convergenceNum-1){
      offsetT.col(i) = offsetV.col(i);
      offsetH.col(i) = offsetV.col(i);
    }
    else if(i==ht_config.convergenceNum-2){
      offsetT.col(i) = offsetV.col(i);
      offsetH.col(i) = offsetV.col(i) + heelOffset;
    }
    else if(i==1){
      offsetT.col(i) = offsetV.col(i) + toeOffset;
      offsetH.col(i) = offsetV.col(i);
    }
    else{
      offsetT.col(i) = offsetV.col(i) + toeOffset;
      offsetH.col(i) = offsetV.col(i) + heelOffset;
    }
  }

  // final desired VRP
  // rvrpTd.col(ht_config.convergenceNum) is unused
  rvrpHd.col(ht_config.convergenceNum) = rf.col(ht_config.convergenceNum) + Dzvrp;

  for(int i=1; i<vwpNum+1; i++){
    rvrpTd.col(i) = rf.col(i) + xi2R(vwp[i-1].tail(3)) * offsetT.col(i) + Dzvrp;
    rvrpHd.col(i) = rf.col(i) + xi2R(vwp[i-1].tail(3)) * offsetH.col(i) + Dzvrp;
  }

  rvrpHd.col(0) = rf.col(0) + Dzvrp;
  rvrpTd.col(0) = Vector3d::Zero();
  // rvrpTd.col(0) is not calculated

  // 補正
  for(int i=0; i<ht_config.convergenceNum; i++)
    vwpOpt.col(i) += Dzvrp;



  // for(int i(0); i<(signed int)vwp.size(); i++){
  //   o(i);
  //   o(vwp[i]);
  // }
  // o(rvrpTd);
  // o(rvrpHd);
  // gc;
}
