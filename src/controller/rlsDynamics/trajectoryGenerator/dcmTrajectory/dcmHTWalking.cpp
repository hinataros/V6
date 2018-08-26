 /**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

Matrix3d Rz(double th)
{
  double s = sin(th);
  double c = cos(th);

  return (Matrix3d()<<
          c,-s, 0,
          s, c, 0,
          0, 0, 1).finished();
}

void setFootPrint(MatrixXd &rfT, MatrixXd &rfH, double offset, double toe, double heel)
{
  Matrix3d Sinit = Matrix3d::Identity(); Sinit(0,0) = 0.;

  Vector3d offsetRT3D = (Vector3d()<< toe, offset,0.).finished();
  Vector3d offsetRH3D = (Vector3d()<<heel, offset,0.).finished();
  Vector3d offsetLT3D = (Vector3d()<< toe,-offset,0.).finished();
  Vector3d offsetLH3D = (Vector3d()<<heel,-offset,0.).finished();

  int num = 1;
  rfT.col(num)<<0.,-0.039,0.; rfT.col(num) += (Vector3d()<<   0., 0., 0.).finished(); rfT.col(num) += offsetRT3D;
  rfH.col(num)<<0.,-0.039,0.; rfH.col(num) += (Vector3d()<<   0., 0., 0.).finished(); rfH.col(num) += Sinit*offsetRH3D; num++;// 1
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.08, 0., 0.).finished(); rfT.col(num) += offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.08, 0., 0.).finished(); rfH.col(num) += offsetLH3D; num++;// 2
  rfT.col(num)<<0.,-0.039,0.; rfT.col(num) += (Vector3d()<< 0.16, 0., 0.).finished(); rfT.col(num) += offsetRT3D;
  rfH.col(num)<<0.,-0.039,0.; rfH.col(num) += (Vector3d()<< 0.16, 0., 0.).finished(); rfH.col(num) += offsetRH3D; num++;// 3
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.24, 0., 0.).finished(); rfT.col(num) += offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.24, 0., 0.).finished(); rfH.col(num) += offsetLH3D; num++;// 4
  rfT.col(num)<<0.,-0.039,0.; rfT.col(num) += (Vector3d()<< 0.32, 0., 0.).finished(); rfT.col(num) += offsetRT3D;
  rfH.col(num)<<0.,-0.039,0.; rfH.col(num) += (Vector3d()<< 0.32, 0., 0.).finished(); rfH.col(num) += offsetRH3D; num++;// 5
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.40, 0., 0.).finished(); rfT.col(num) += offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.40, 0., 0.).finished(); rfH.col(num) += offsetLH3D; num++;// 6
  rfT.col(num)<<0.,-0.039,0.; rfT.col(num) += (Vector3d()<< 0.48, 0., 0.).finished(); rfT.col(num) += offsetRT3D;
  rfH.col(num)<<0.,-0.039,0.; rfH.col(num) += (Vector3d()<< 0.48, 0., 0.).finished(); rfH.col(num) += offsetRH3D; num++;// 7
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.56, 0., 0.).finished(); rfT.col(num) += offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.56, 0., 0.).finished(); rfH.col(num) += offsetLH3D; num++;// 8
  rfT.col(num)<<0.,-0.039,0.; rfT.col(num) += (Vector3d()<< 0.56, 0., 0.).finished(); rfT.col(num) += Rz(-0.5236)*offsetRT3D;
  rfH.col(num)<<0.,-0.039,0.; rfH.col(num) += (Vector3d()<< 0.56, 0., 0.).finished(); rfH.col(num) += Rz(-0.5236)*offsetRH3D; num++;// 9
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078, 0.).finished(); rfT.col(num) += Rz(-1.0472)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078, 0.).finished(); rfH.col(num) += Rz(-1.0472)*offsetLH3D; num++;// 10
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<<  0.56, -0.078-0.08, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetRT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<<  0.56, -0.078-0.08, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetRH3D; num++;// 11
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078-0.16, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078-0.16, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetLH3D; num++;// 12
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<<  0.56, -0.078-0.24, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetRT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<<  0.56, -0.078-0.24, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetRH3D; num++;// 13
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078-0.32, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078-0.32, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetLH3D; num++;// 14
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<<  0.56, -0.078-0.40, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetRT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<<  0.56, -0.078-0.40, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetRH3D; num++;// 15
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078-0.48, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078-0.48, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetLH3D; num++;// 16
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<<  0.56, -0.078-0.56, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetRT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<<  0.56, -0.078-0.56, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetRH3D; num++;// 17
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078-0.64, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078-0.64, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetLH3D; num++;// 18
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<<  0.56, -0.078-0.72, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetRT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<<  0.56, -0.078-0.72, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetRH3D; num++;// 19
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078-0.80, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078-0.80, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetLH3D; num++;// 20
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<<  0.56, -0.078-0.48, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetRT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<<  0.56, -0.078-0.48, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetRH3D; num++;// 21
  rfT.col(num)<<0., 0.039,0.; rfT.col(num) += (Vector3d()<< 0.638, -0.078-0.48, 0.).finished(); rfT.col(num) += Rz(-1.5708)*offsetLT3D;
  rfH.col(num)<<0., 0.039,0.; rfH.col(num) += (Vector3d()<< 0.638, -0.078-0.48, 0.).finished(); rfH.col(num) += Rz(-1.5708)*offsetLH3D; num++;// 22
}

void upDownFootPrint(MatrixXd &rf, double offset)
{
  int num = 1;
  rf.col(num) <<   0., -0.039+offset,   0.; num++;// 1
  rf.col(num) << 0.07,  0.039-offset,   0.; num++;// 2
  rf.col(num) << 0.14, -0.039+offset, 0.02; num++;// 3
  rf.col(num) << 0.21,  0.039-offset, 0.04; num++;// 4
  rf.col(num) << 0.28, -0.039+offset, 0.06; num++;// 5
  rf.col(num) << 0.35,  0.039-offset, 0.08; num++;// 6
  rf.col(num) << 0.42, -0.039+offset, 0.10; num++;// 7
  rf.col(num) << 0.49,  0.039-offset, 0.12; num++;// 8
  rf.col(num) << 0.56, -0.039+offset, 0.12; num++;// 9
  rf.col(num) << 0.63,  0.039-offset, 0.10; num++;// 10
  rf.col(num) << 0.70, -0.039+offset, 0.08; num++;// 11
  rf.col(num) << 0.77,  0.039-offset, 0.06; num++;// 12
  rf.col(num) << 0.84, -0.039+offset, 0.04; num++;// 13
  rf.col(num) << 0.91,  0.039-offset, 0.02; num++;// 14
  rf.col(num) << 0.98, -0.039+offset,   0.; num++;// 15
  rf.col(num) << 1.05,  0.039-offset,   0.; num++;// 16
  rf.col(num) << 1.05,            0.,   0.; num++;// 17
  rf.col(num) << 1.05,            0.,   0.; num++;// 18
}

void upDownHTFootPrint(MatrixXd &rfT, MatrixXd &rfH, double y, double t, double h)
{
  int num = 1;
  rfH.col(num) <<     0., -0.039+y,   0.;
  rfT.col(num) <<   0.+t, -0.039+y,   0.; num++;// 1
  rfH.col(num) << 0.07+h,  0.039-y,   0.;
  rfT.col(num) << 0.07+t,  0.039-y,   0.; num++;// 2
  rfH.col(num) << 0.14+h, -0.039+y, 0.02;
  rfT.col(num) << 0.14+t, -0.039+y, 0.02; num++;// 3
  rfH.col(num) << 0.21+h,  0.039-y, 0.04;
  rfT.col(num) << 0.21+t,  0.039-y, 0.04; num++;// 4
  rfH.col(num) << 0.28+h, -0.039+y, 0.06;
  rfT.col(num) << 0.28+t, -0.039+y, 0.06; num++;// 5
  rfH.col(num) << 0.35+h,  0.039-y, 0.08;
  rfT.col(num) << 0.35+t,  0.039-y, 0.08; num++;// 6
  rfH.col(num) << 0.42+h, -0.039+y, 0.10;
  rfT.col(num) << 0.42+t, -0.039+y, 0.10; num++;// 7
  rfH.col(num) << 0.49+h,  0.039-y, 0.12;
  rfT.col(num) << 0.49+t,  0.039-y, 0.12; num++;// 8
  rfH.col(num) << 0.56+h, -0.039+y, 0.12;
  rfT.col(num) << 0.56+t, -0.039+y, 0.10; num++;// 9
  rfH.col(num) << 0.63+h,  0.039-y, 0.10;
  rfT.col(num) << 0.63+t,  0.039-y, 0.08; num++;// 10
  rfH.col(num) << 0.70+h, -0.039+y, 0.08;
  rfT.col(num) << 0.70+t, -0.039+y, 0.06; num++;// 11
  rfH.col(num) << 0.77+h,  0.039-y, 0.06;
  rfT.col(num) << 0.77+t,  0.039-y, 0.04; num++;// 12
  rfH.col(num) << 0.84+h, -0.039+y, 0.04;
  rfT.col(num) << 0.84+t, -0.039+y, 0.02; num++;// 13
  rfH.col(num) << 0.91+h,  0.039-y, 0.02;
  rfT.col(num) << 0.91+t,  0.039-y,   0.; num++;// 14
  rfH.col(num) << 0.98+h, -0.039+y,   0.;
  rfT.col(num) << 0.98+t, -0.039+y,   0.; num++;// 15
  rfH.col(num) << 1.05+h,  0.039-y,   0.;
  rfT.col(num) <<   1.05,  0.039-y,   0.; num++;// 16
  rfH.col(num) <<   1.05,       0.,   0.;
  rfT.col(num) <<   1.05,       0.,   0.; num++;// 17
  rfH.col(num) <<   1.05,       0.,   0.;
  rfT.col(num) <<   1.05,       0.,   0.; num++;// 18
}

void straightWalkFootPrint(MatrixXd &rf, double offset)
{
  int num = 1;

  rf.col(num) <<  0., -0.039+offset, 0.; num++;// 1
  rf.col(num) << 0.1,  0.039-offset, 0.; num++;// 2
  rf.col(num) << 0.2, -0.039+offset, 0.; num++;// 3
  rf.col(num) << 0.3,  0.039-offset, 0.; num++;// 4
  rf.col(num) << 0.4, -0.039+offset, 0.; num++;// 5
  rf.col(num) << 0.5,  0.039-offset, 0.; num++;// 6
  rf.col(num) << 0.6, -0.039+offset, 0.; num++;// 7
  rf.col(num) << 0.7,  0.039-offset, 0.; num++;// 8
  rf.col(num) << 0.7,            0., 0.; num++;// 9
  rf.col(num) << 0.7,            0., 0.; num++;// 10

  // rf.col(num) <<   0., -0.039+offset, 0.; num++;// 1
  // rf.col(num) << 0.09,  0.039-offset, 0.; num++;// 2
  // rf.col(num) << 0.18, -0.039+offset, 0.; num++;// 3
  // rf.col(num) << 0.27,  0.039-offset, 0.; num++;// 4
  // rf.col(num) << 0.36, -0.039+offset, 0.; num++;// 5
  // rf.col(num) << 0.45,  0.039-offset, 0.; num++;// 6
  // rf.col(num) << 0.54, -0.039+offset, 0.; num++;// 7
  // rf.col(num) << 0.63,  0.039-offset, 0.; num++;// 8
  // rf.col(num) << 0.63,            0., 0.; num++;// 9
  // rf.col(num) << 0.63,            0., 0.; num++;// 10

  // rf.col(num) <<   0., -0.039+offset, 0.; num++;// 1
  // rf.col(num) << 0.08,  0.039-offset, 0.; num++;// 2
  // rf.col(num) << 0.16, -0.039+offset, 0.; num++;// 3
  // rf.col(num) << 0.24,  0.039-offset, 0.; num++;// 4
  // rf.col(num) << 0.32, -0.039+offset, 0.; num++;// 5
  // rf.col(num) << 0.40,  0.039-offset, 0.; num++;// 6
  // rf.col(num) << 0.48, -0.039+offset, 0.; num++;// 7
  // rf.col(num) << 0.56,  0.039-offset, 0.; num++;// 8
  // rf.col(num) << 0.56,            0., 0.; num++;// 9
  // rf.col(num) << 0.56,            0., 0.; num++;// 10
}

void testFootPrint(MatrixXd &rf, double offset)
{
  int num = 1;
  // rf.col(num) << 0., 0.039-offset,   0.; num++;// 1
  // rf.col(num) << 0., 0.039-offset,   0.; num++;// 1
  // rf.col(num) << 0.03, -0.039+offset,   0.; num++;// 1
  // rf.col(num) << 0.03, -0.039+offset,   0.; num++;// 1
  rf.col(num) << 0., 0.,   0.; num++;// 1
  rf.col(num) << 0., 0.,   0.; num++;// 1
  rf.col(num) << 0.03, 0.,   0.; num++;// 1
  rf.col(num) << 0.03, 0.,   0.; num++;// 1
}
void RLS::RlsDynamics::dcmHTWalking(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  // setting
  // straight walk on flat ground
  // ********************************
  double tstab = 2.;

  // // straight walk toe off
  // double dtstep = .5;
  // double dtDSstep = .2;
  // double alphDSstep = .3;
  // double alphaHTstep = 0.6;
  // double offset = 0.015;
  // double toe = 0.025;
  // double heel = 0.;

  // // straight walk
  // double dtstep = .5;
  // double dtDSstep = .1;
  // double alphDSstep = .5;
  // double alphaHTstep = 0.5;
  // double offset = 0.01;
  // double toe = 0.025;
  // double heel = -0.015;

  // updown
  double dtstep = 1.;
  double dtDSstep = .5;
  double alphDSstep = .5;
  double alphaHTstep = .5;
  double offset = 0.01;
  double toe = 0.025;
  double heel = -0.015;

  // // rough updown
  // double dtstep = 1.;
  // double dtDSstep = .5;
  // double alphDSstep = .5;
  // double alphaHTstep = .5;
  // double offset = 0.01;
  // double toe = 0.025;
  // double heel = -0.015;

  // // updown HT
  // double dtstep = .8;
  // double dtDSstep = .3;
  // double alphDSstep = .3;
  // double offset = 0.01;
  // double toe = 0.026;
  // double heel = 0.;
  // double alphaHTstep = 0.5;

  // double steplength = 0.01;
  // double steplength = 0.055;
  // double steplength = 0.08;

  double height = 0.;

  // HT
  // setting
  // ********************************

  double tf = tstab + dtstep*(1.-alphaHTstep) + dtstep*(stepNum-1);

  if(t==0.){
    for(int i=0; i<stepNum; i++){
      dt(i) = dtstep;
     }
    for(int i=0; i<stepNum+1; i++){
      dtDS(i) = dtDSstep;
      alphDS(i) = alphDSstep;
    }

    for(int i=1; i<stepNum+1; i++){
      // dtDSini(0) = 0 define
      dtDSini(i) = alphDS(i)*dtDS(i);

      // dtDSend(0) = 0 define
      // dtDSend(stepNum) = 0 define
      if(i!=stepNum)
        dtDSend(i) = (1 - alphDS(i))*dtDS(i);
    }

    // HT
    for(int i=0; i<stepNum; i++){
      alphaHT(i) = alphaHTstep;

      // smiyahara: dtHT(0) is unused
      if(i)
        dtHT(i) = alphaHT(i)*dt(i);

      dtTH(i) = (1 - alphaHT(i))*dt(i);
    }

    // double heighttemp = 0.;
    // Vector2d rlegPos = cal_X.segment(0, 3).head(2);
    // Vector2d llegPos = cal_X.segment(6, 3).head(2);

    // // define foot print
    // // ******************************
    // // smiyahara: rf.col(0) is unused
    // // smiyahara: rf.col(stepNum) is unused
    // for(int i=1; i<stepNum-1; i++){
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

    // rf.col(stepNum-1)(0) = rlegPos(0);
    // rf.col(stepNum-1)(1) = rC0(1);
    // rf.col(stepNum-1)(2) += heighttemp; heighttemp += height;

    // double temp = 0.;
    // for(int i=2; i<stepNum; i++){
    //   if(i!=stepNum-1)
    //     temp += steplength;

    //   rf.col(i)(0) += temp;
    // }

    // rXHT.col(stepNum)(0) = rlegPos(0) + temp;
    // rXHT.col(stepNum)(1) = rC0(1);
    // rXHT.col(stepNum)(2) = rC0(2) + heighttemp;
    // // ******************************

    // define foot print
    // ******************************
    // rf.col(0) << 0., 0., 0.;

    // backward calculation
    Vector3d toeOffset = (Vector3d()<<toe, 0., 0.).finished();
    Vector3d heelOffset = (Vector3d()<<heel, 0., 0.).finished();

    Vector3d Dzvrp = (-model.hoap2.ag)/(wX*wX);

    // testFootPrint(rf, offset);
    // setFootPrint(rfT, rfH, offset, toe, heel);
    upDownFootPrint(rf, offset);
    // upDownHTFootPrint(rfT, rfH, offset, toe, heel);
    // straightWalkFootPrint(rf, offset);

    // ******************************
    // final desired DCM position
    // rXTH.col(stepNum) is unused
    rXHT.col(stepNum) = rf.col(stepNum) + Dzvrp;

    // rvrpTd.col(stepNum) is unused
    // final desired VRP
    rvrpHd.col(stepNum) = rXHT.col(stepNum);

    for(int i=stepNum-1; i>0; i--){
      if(i==stepNum-1){
        rvrpTd.col(i) = rf.col(i) + Dzvrp;
        rvrpHd.col(i) = rf.col(i) + Dzvrp;
      }
      else if(i==stepNum-2){
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
    // // rXTH.col(stepNum) is unused
    // rXHT.col(stepNum) = rfH.col(stepNum) + Dzvrp;

    // // rvrpTd.col(stepNum) is unused
    // // final desired VRP
    // rvrpHd.col(stepNum) = rXHT.col(stepNum);

    // for(int i=stepNum-1; i>0; i--){
    //   rvrpTd.col(i) = rfT.col(i) + Dzvrp;
    //   rvrpHd.col(i) = rfH.col(i) + Dzvrp;

    //   rXTH.col(i) = rvrpTd.col(i) + exp(-wX*dtTH(i))*(rXHT.col(i+1) - rvrpTd.col(i));
    //   rXHT.col(i) = rvrpHd.col(i) + exp(-wX*dtHT(i))*(rXTH.col(i) - rvrpHd.col(i));
    // }
    // // ******************************

    // dtHT(0) is unused
    // rvrpHd.col(0) is unused
    rvrpTd.col(0) = rC0/(1 - exp(-wX*dtTH(0))) + rXHT.col(1)/(1 - exp(wX*dtTH(0)));
    // rXHT.col(0) is unused
    rXTH.col(0) = rC0;

    // double sopport
    // ******************************
    // final
    rXeoDS.col(stepNum) = rvrpHd.col(stepNum);
    rXiniDS.col(stepNum) = rvrpTd.col(stepNum-1) + exp(-wX*dtDSini(stepNum))*(rXHT.col(stepNum) - rvrpTd.col(stepNum-1));
    // ******************************
    drXeoDS.col(stepNum) = wX*(rXeoDS.col(stepNum) - rvrpHd.col(stepNum));
    drXiniDS.col(stepNum) = wX*(rXiniDS.col(stepNum) - rvrpTd.col(stepNum-1));

    // ******************************
    ddrXeoDS.col(stepNum) = Vector3d::Zero();
    ddrXiniDS.col(stepNum) = wX*wX*exp(-wX*dtDSini(stepNum))*(rXHT.col(stepNum) - rvrpTd.col(stepNum-1));

    for(int i=stepNum-1; i>0; i--){
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

  double twalk = t - tstab;
  if(round_cast(t, 3)<round_cast(tstab, 3)){
    for(int i=0; i<3; i++){
      des = makeSpline5(t-info.sim.tw0, info.sim.twf, rXpreDes(i), rXf(i));
      rXDes(i) = des(0) + rX0(i);
      drXDes(i) = des(1);
    }
  }
  else if(round_cast(t, 3)<round_cast(tf, 3)){
    // DCM dynamics based exponential interpolation
    // // toe to heel
    // // ******************************
    // if(round_cast(twalk, 3)<500){
    //   rXDes = rvrpTd.col(i) +
    //     exp(wX*(tstep-dtTH(i)))*(rXHT.col(i+1) - rvrpTd.col(i));

    //   drXDes = wX*(rXDes - rvrpTd.col(i));
    // }

    // // heel to toe
    // // ******************************
    // else if(round_cast(twalk, 3)<500+500){
    //   rXDes = rvrpHd.col(i) +
    //     exp(wX*(tstep-dtHT(i)))*(rXTH.col(i) - rvrpHd.col(i));

    //   drXDes = wX*(rXDes - rvrpHd.col(i));
    // }

    double twDS;
    if(initial_walking){
      tphasef = dtTH(stepPhase) - dtDSini(stepPhase+1);
      // same as dtHT(stepPhase) - dtDSend(stepPhase) + dtTH(stepPhase) - dtDSini(stepPhase+1)

      twDS = twalk - tDS0;
      for(int i=0; i<3; i++){
        des = makeSpline5(twDS, tphasef,
                          rXiniDS.col(stepPhase)(i),
                          drXiniDS.col(stepPhase)(i),
                          ddrXiniDS.col(stepPhase)(i),
                          rXiniDS.col(stepPhase+1)(i),
                          drXiniDS.col(stepPhase+1)(i),
                          ddrXiniDS.col(stepPhase+1)(i));
        rXDes(i) = des(0);
        drXDes(i) = des(1);
      }

      if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
        support = 1;

        tDS0 = twalk;
        stepPhase++;
        initial_walking = false;
      }
    }

    else{
      twDS = twalk - tDS0;

      if(support==0){
        tphasef = dtHT(stepPhase) - dtDSend(stepPhase) + dtTH(stepPhase) - dtDSini(stepPhase+1);

        for(int i=0; i<3; i++){
          des = makeSpline5(twDS, tphasef,
                            rXeoDS.col(stepPhase)(i),
                            drXeoDS.col(stepPhase)(i),
                            ddrXeoDS.col(stepPhase)(i),
                            rXiniDS.col(stepPhase+1)(i),
                            drXiniDS.col(stepPhase+1)(i),
                            ddrXiniDS.col(stepPhase+1)(i));
          rXDes(i) = des(0);
          drXDes(i) = des(1);
        }

        if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
          support = 1;
          tDS0 = twalk;
          stepPhase++;
        }
      }

      else if(support==1){
        tphasef = dtDSini(stepPhase)+dtDSend(stepPhase);

        for(int i=0; i<3; i++){
          des = makeSpline5(twDS, tphasef,
                            rXiniDS.col(stepPhase)(i),
                            drXiniDS.col(stepPhase)(i),
                            ddrXiniDS.col(stepPhase)(i),
                            rXeoDS.col(stepPhase)(i),
                            drXeoDS.col(stepPhase)(i),
                            ddrXeoDS.col(stepPhase)(i));
          rXDes(i) = des(0);
          drXDes(i) = des(1);
        }

        if(round_cast(twDS, 3) == round_cast(tphasef, 3)){
          support = 0;
          tDS0 = twalk;
        }
      }
    }
  }
  else{
    rXDes = rXHT.col(stepNum);
    drXDes = wX*(rXDes - rXHT.col(stepNum));
  }

  eX = rXDes - rX;

  drXRef = drXDes + KX*eX;
}
