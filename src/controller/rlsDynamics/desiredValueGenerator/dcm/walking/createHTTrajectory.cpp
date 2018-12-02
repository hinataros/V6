/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

// void setWaypoint(MatrixXd &rf, double offset)
// {
//   int num = 1;

//   rf.col(num) <<   0., -0.039+offset, 0.; num++;// 1
//   rf.col(num) << 0.08,  0.039-offset, 0.; num++;// 2
//   rf.col(num) << 0.16, -0.039+offset, 0.; num++;// 3
//   rf.col(num) << 0.24,  0.039-offset, 0.; num++;// 4
//   rf.col(num) << 0.24,            0., 0.; num++;// 5
//   rf.col(num) << 0.24,            0., 0.; num++;// 6
// }

void RLS::Walking::createHTTrajectory()
{
  if(debug) DEBUG;

  for(int i=0; i<ht_config.convergenceNum; i++){
    dT(i) = ht_config.dtstep;
  }

  for(int i=0; i<ht_config.convergenceNum+1; i++){
    dtDS(i) = ht_config.dtDSstep;
    alphaDS(i) = ht_config.alphaDSstep;
  }

  for(int i=1; i<ht_config.convergenceNum+1; i++){
    // dtDSini(0) = 0 define
    dtDSini(i) = alphaDS(i)*dtDS(i);

    // dtDSend(0) = 0 define
    // dtDSend(ht_config.convergenceNum) = 0 define
    if(i!=ht_config.convergenceNum)
      dtDSend(i) = (1 - alphaDS(i))*dtDS(i);
  }

  // HT
  for(int i=0; i<ht_config.convergenceNum; i++){
    alphaHT(i) = ht_config.alphaHTstep;

    // smiyahara: dtHT(0) is unused
    if(i)
      dtHT(i) = alphaHT(i)*dT(i);

    dtTH(i) = (1 - alphaHT(i))*dT(i);
  }

  // rf.col(0) is unused
  for(int i=1; i<vwpNum+1; i++){
    rf.col(i) = vwp[i-1];

    if(i<vwpNum){
      // first waypoint is right foot
      if(i%2==0)
        rf.col(i)(1) -= ht_config.offset;
      else
        rf.col(i)(1) += ht_config.offset;
    }
  }

  // for dcm velocity convergence
  rf.col(vwpNum+1) = vwp[vwpNum-1];

  // setWaypoint(rf, ht_config.offset);

  // ******************************
  Vector3d Dzvrp = (Vector3d()<<0., 0., g/(wX*wX)).finished();
  // final desired DCM position
  // rXTH.col(ht_config.convergenceNum) is unused
  rXHT.col(ht_config.convergenceNum) = rf.col(ht_config.convergenceNum) + Dzvrp;

  // final desired VRP
  // rvrpTd.col(ht_config.convergenceNum) is unused
  rvrpHd.col(ht_config.convergenceNum) = rXHT.col(ht_config.convergenceNum);

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

    rXTH.col(i) = rvrpTd.col(i) + exp(-wX*dtTH(i))*(rXHT.col(i+1) - rvrpTd.col(i));
    rXHT.col(i) = rvrpHd.col(i) + exp(-wX*dtHT(i))*(rXTH.col(i) - rvrpHd.col(i));
  }
  // ******************************

  // // ******************************
  // // final desired DCM position
  // // rXTH.col(ht_config.convergenceNum) is unused
  // rXHT.col(ht_config.convergenceNum) = rfH.col(ht_config.convergenceNum) + Dzvrp;

  // // rvrpTd.col(ht_config.convergenceNum) is unused
  // // final desired VRP
  // rvrpHd.col(ht_config.convergenceNum) = rXHT.col(ht_config.convergenceNum);

  // for(int i=ht_config.convergenceNum-1; i>0; i--){
  //   rvrpTd.col(i) = rfT.col(i) + Dzvrp;
  //   rvrpHd.col(i) = rfH.col(i) + Dzvrp;

  //   rXTH.col(i) = rvrpTd.col(i) + exp(-wX*dtTH(i))*(rXHT.col(i+1) - rvrpTd.col(i));
  //   rXHT.col(i) = rvrpHd.col(i) + exp(-wX*dtHT(i))*(rXTH.col(i) - rvrpHd.col(i));
  // }
  // // ******************************

  // dtHT(0) is unused
  // rvrpHd.col(0) is unused
  rvrpTd.col(0) = rCw0/(1 - exp(-wX*dtTH(0))) + rXHT.col(1)/(1 - exp(wX*dtTH(0)));
  // rXHT.col(0) is unused
  rXTH.col(0) = rCw0;

  // double sopport
  // ******************************
  // final
  rXeoDS.col(ht_config.convergenceNum) = rvrpHd.col(ht_config.convergenceNum);
  rXiniDS.col(ht_config.convergenceNum) = rvrpTd.col(ht_config.convergenceNum-1) + exp(-wX*dtDSini(ht_config.convergenceNum))*(rXHT.col(ht_config.convergenceNum) - rvrpTd.col(ht_config.convergenceNum-1));
  // ******************************
  drXeoDS.col(ht_config.convergenceNum) = wX*(rXeoDS.col(ht_config.convergenceNum) - rvrpHd.col(ht_config.convergenceNum));
  drXiniDS.col(ht_config.convergenceNum) = wX*(rXiniDS.col(ht_config.convergenceNum) - rvrpTd.col(ht_config.convergenceNum-1));

  // ******************************
  ddrXeoDS.col(ht_config.convergenceNum) = Vector3d::Zero();
  ddrXiniDS.col(ht_config.convergenceNum) = wX*wX*exp(-wX*dtDSini(ht_config.convergenceNum))*(rXHT.col(ht_config.convergenceNum) - rvrpTd.col(ht_config.convergenceNum-1));

  for(int i=ht_config.convergenceNum-1; i>0; i--){
    rXeoDS.col(i) = rvrpHd.col(i) + exp(wX*dtDSend(i))*(rXHT.col(i) - rvrpHd.col(i));
    rXiniDS.col(i) = rvrpTd.col(i-1) + exp(-wX*dtDSini(i))*(rXHT.col(i) - rvrpTd.col(i-1));

    drXeoDS.col(i) = wX*(rXeoDS.col(i) - rvrpHd.col(i));
    drXiniDS.col(i) = wX*(rXiniDS.col(i) - rvrpTd.col(i-1));

    ddrXeoDS.col(i) = wX*wX*exp(wX*dtDSend(i))*(rXHT.col(i) - rvrpHd.col(i));
    ddrXiniDS.col(i) = wX*wX*exp(-wX*dtDSini(i))*(rXHT.col(i) - rvrpTd.col(i-1));
  }

  // start
  // ******************************
  // rXeoDS.col(0) is unused
  // rXeoDS.col(0) = rvrpTd.col(0) + exp(wX*dtDSend(0))*(rXTH.col(0) - rvrpTd.col(0));
  rXiniDS.col(0) = rXTH.col(0);// assumption
  // ******************************
  // drXeoDS.col(0) is unused
  // drXeoDS.col(0) = wX*(rXeoDS.col(0) - rvrpTd.col(0));
  drXiniDS.col(0) = Vector3d::Zero();// assumption
  // ******************************
  // ddrXeoDS.col(0) is unused
  // ddrXeoDS.col(0) = wX*wX*exp(wX*dtDSend(0))*(rXTH.col(0) - rvrpTd.col(0));
  ddrXiniDS.col(0) = Vector3d::Zero();// assumption
}
