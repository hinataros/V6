/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::createExtHTTrajectory()
{
  if(debug) DEBUG;

  wX = sqrt(g/rCw0(2));

  // double steplength = 0.01;
  // double steplength = 0.055;
  // double steplength = 0.08;

  double height = 0.;

  for(int i=0; i<ht_config.stepNum; i++){
    dT(i) = ht_config.dtstep;
  }
  for(int i=0; i<ht_config.stepNum+1; i++){
    dtDS(i) = ht_config.dtDSstep;
    alphaDS(i) = ht_config.alphaDSstep;
  }

  for(int i=1; i<ht_config.stepNum+1; i++){
    // dtDSini(0) = 0 define
    dtDSini(i) = alphaDS(i)*dtDS(i);

    // dtDSend(0) = 0 define
    // dtDSend(ht_config.stepNum) = 0 define
    if(i!=ht_config.stepNum)
      dtDSend(i) = (1 - alphaDS(i))*dtDS(i);
  }

  // HT
  for(int i=0; i<ht_config.stepNum; i++){
    alphaHT(i) = ht_config.alphaHTstep;

    // smiyahara: dtHT(0) is unused
    if(i)
      dtHT(i) = alphaHT(i)*dT(i);

    dtTH(i) = (1 - alphaHT(i))*dT(i);
  }

  // double heighttemp = 0.;
  // Vector2d rlegPos = cal_X.segment(0, 3).head(2);
  // Vector2d llegPos = cal_X.segment(6, 3).head(2);

  // // define foot print
  // // ******************************
  // // smiyahara: rf.col(0) is unused
  // // smiyahara: rf.col(ht_config.stepNum) is unused
  // for(int i=1; i<ht_config.stepNum-1; i++){
  //   // first swing is left leg
  //   if(i%2==0){
  //     rf.col(i).head(2) = llegPos;
  //     rf.col(i)(1) -= offset;
  //   }
  //   else{
  //     rf.col(i).head(2) = rlegPos;
  //     rf.col(i)(1) += offset;
  //   }

  //   rf.col(i)(2) += heighttemp; heighttemp += height;
  // }

  // rf.col(ht_config.stepNum-1)(0) = rlegPos(0);
  // rf.col(ht_config.stepNum-1)(1) = rC0(1);
  // rf.col(ht_config.stepNum-1)(2) += heighttemp; heighttemp += height;

  // double temp = 0.;
  // for(int i=2; i<ht_config.stepNum; i++){
  //   if(i!=ht_config.stepNum-1)
  //     temp += steplength;

  //   rf.col(i)(0) += temp;
  // }

  // rXHT.col(ht_config.stepNum)(0) = rlegPos(0) + temp;
  // rXHT.col(ht_config.stepNum)(1) = rC0(1);
  // rXHT.col(ht_config.stepNum)(2) = rC0(2) + heighttemp;
  // // ******************************

  // define foot print
  // ******************************
  // rf.col(0) << 0., 0., 0.;

  int num = 1;

  rf.col(num) <<   0., -0.039+ht_config.offset, 0.; num++;// 1
  rf.col(num) << 0.08,  0.039-ht_config.offset, 0.; num++;// 2
  rf.col(num) << 0.16, -0.039+ht_config.offset, 0.; num++;// 3
  rf.col(num) << 0.24,  0.039-ht_config.offset, 0.; num++;// 4
  rf.col(num) << 0.24,            0., 0.; num++;// 5
  rf.col(num) << 0.24,            0., 0.; num++;// 6

  // rf.col(num) <<   0., -0.039+ht_config.offset, 0.; num++;// 1
  // rf.col(num) << 0.08,  0.039-ht_config.offset, 0.; num++;// 2
  // rf.col(num) << 0.16, -0.039+ht_config.offset, 0.; num++;// 3
  // rf.col(num) << 0.24,  0.039-ht_config.offset, 0.; num++;// 4
  // rf.col(num) << 0.24,            0., 0.; num++;// 5
  // rf.col(num) << 0.24,            0., 0.; num++;// 6

  // backward calculation
  Vector3d toeOffset = (Vector3d()<<ht_config.toe, 0., 0.).finished();
  Vector3d heelOffset = (Vector3d()<<ht_config.heel, 0., 0.).finished();

  Vector3d Dzvrp = (Vector3d()<<0., 0., g/(wX*wX)).finished();

  Vector3d rHextDes = fext/(model->M*wX*wX);

  // final desired DCM position
  // rXTH.col(ht_config.stepNum) is unused
  rXHT.col(ht_config.stepNum) = rf.col(ht_config.stepNum) + Dzvrp - rHextDes;

  // final desired VRP
  // rvrpTd.col(ht_config.stepNum) is unused
  rvrpHd.col(ht_config.stepNum) = rXHT.col(ht_config.stepNum);

  for(int i=ht_config.stepNum-1; i>0; i--){
    if(i==ht_config.stepNum-1){
      rndvrpTd.col(i) = rf.col(i) + Dzvrp;
      rndvrpHd.col(i) = rf.col(i) + Dzvrp;
    }
    else if(i==ht_config.stepNum-2){
      rndvrpTd.col(i) = rf.col(i) + Dzvrp;
      rndvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
    }
    else if(i==1){
      rndvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
      rndvrpHd.col(i) = rf.col(i) + Dzvrp;
    }
    else{
      rndvrpTd.col(i) = rf.col(i) + toeOffset + Dzvrp;
      rndvrpHd.col(i) = rf.col(i) + heelOffset + Dzvrp;
    }

    rvrpTd.col(i) = rndvrpTd.col(i) - rHextDes;
    rvrpHd.col(i) = rndvrpHd.col(i) - rHextDes;

    rXTH.col(i) = rvrpTd.col(i) + exp(-wX*dtTH(i))*(rXHT.col(i+1) - rvrpTd.col(i));
    rXHT.col(i) = rvrpHd.col(i) + exp(-wX*dtHT(i))*(rXTH.col(i) - rvrpHd.col(i));
  }
  // ******************************

  // // ******************************
  // // final desired DCM position
  // // rXTH.col(ht_config.stepNum) is unused
  // rXHT.col(ht_config.stepNum) = rfH.col(ht_config.stepNum) + Dzvrp;

  // // rvrpTd.col(ht_config.stepNum) is unused
  // // final desired VRP
  // rvrpHd.col(ht_config.stepNum) = rXHT.col(ht_config.stepNum);

  // for(int i=ht_config.stepNum-1; i>0; i--){
  //   rvrpTd.col(i) = rfT.col(i) + Dzvrp;
  //   rvrpHd.col(i) = rfH.col(i) + Dzvrp;

  //   rXTH.col(i) = rvrpTd.col(i) + exp(-wX*dtTH(i))*(rXHT.col(i+1) - rvrpTd.col(i));
  //   rXHT.col(i) = rvrpHd.col(i) + exp(-wX*dtHT(i))*(rXTH.col(i) - rvrpHd.col(i));
  // }

  // dtHT(0) is unused
  // rvrpHd.col(0) is unused
  rvrpTd.col(0) = rCw0/(1 - exp(-wX*dtTH(0))) + rXHT.col(1)/(1 - exp(wX*dtTH(0)));
  // rXHT.col(0) is unused
  rXTH.col(0) = rCw0;

  // double sopport
  // ******************************
  // final
  rXeoDS.col(ht_config.stepNum) = rvrpHd.col(ht_config.stepNum);
  rXiniDS.col(ht_config.stepNum) = rvrpTd.col(ht_config.stepNum-1) + exp(-wX*dtDSini(ht_config.stepNum))*(rXHT.col(ht_config.stepNum) - rvrpTd.col(ht_config.stepNum-1));
  // ******************************
  drXeoDS.col(ht_config.stepNum) = wX*(rXeoDS.col(ht_config.stepNum) - rvrpHd.col(ht_config.stepNum));
  drXiniDS.col(ht_config.stepNum) = wX*(rXiniDS.col(ht_config.stepNum) - rvrpTd.col(ht_config.stepNum-1));

  // ******************************
  ddrXeoDS.col(ht_config.stepNum) = Vector3d::Zero();
  ddrXiniDS.col(ht_config.stepNum) = wX*wX*exp(-wX*dtDSini(ht_config.stepNum))*(rXHT.col(ht_config.stepNum) - rvrpTd.col(ht_config.stepNum-1));

  for(int i=ht_config.stepNum-1; i>0; i--){
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
