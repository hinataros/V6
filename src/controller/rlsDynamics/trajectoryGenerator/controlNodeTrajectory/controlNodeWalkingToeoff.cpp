/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

// namespace RLS{
//   class MakeTrajectory{
//   private:
//     string mode;
//     string interpolation;

//     struct Des{
//       Vector3d pos;
//       Vector3d vel;
//       Vector3d acc;
//     } des;

//     double w;
//     Vector3d rO2p, drO2p, ddrO2p;
//     Vector3d ex, ey, ez;
//     Matrix3d Rw2O;

//   public:
//     double set_angular_frequency(double tf, double anglef)
//     {
//       w = anglef/tf;
//     }

//     void update(Vector3d rO, Vector3d axis, double radius, double t, Vector3d rinit)
//     {
//       update(rO, axis, radius, radius, t, rinit);
//     }

//     // smiyahara: rOが先端部から回転中心までの相対距離
//     void update(Vector3d rO, Vector3d axis, double major, double minor, double t, Vector3d rinit)
//     {
//       // smiyahara: 先端部の位置をt=0の場合の位置とするため
//       ex = -rO.normalized();;
//       ez = axis;
//       ey = ez.cross(ex);

//       Rw2O << ex, ey, ez;

//       rO2p <<
//         major*cos(w*t),
//         minor*sin(w*t),
//         0.;
//       drO2p <<
//         major*w*sin(w*t),
//         minor*w*cos(w*t),
//         0.;
//       drO2p <<
//         major*w*w*cos(w*t),
//         minor*w*w*sin(w*t),
//         0.;

//       // smiyahara: Rは目標なので変化しないと仮定
//       des.pos = rO + Rw2O*rO2p;
//       des.vel = Rw2O*drO2p;
//       des.acc = Rw2O*ddrO2p;
//     }

//     MakeTrajectory(string mode, string interpolation){
//       this->mode = mode;
//       this->interpolation = interpolation;

//       des.pos = des.vel = des.acc = Vector3d::Zero();

//       w = 0.;
//       rO2p = drO2p = ddrO2p = Vector3d::Zero();
//       ex = ey = ez = Vector3d::Zero();
//       Rw2O = Matrix3d::Zero();
//     }
//     ~MakeTrajectory(){}
//   };
// }

// namespace RLS{
//   class Reference{
//   private:
//     struct TrajectoryParameter{
//       int phase;
//       double tw0;
//       double twf;

//       double initial_value;
//       double end_value;
//     };

//   public:
//     void reference();
//   };
// }


void RLS::RlsDynamics::controlNodeWalkingToeoff(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  // MakeTrajectory desdes("arc", "spline5");

  // Vector3d rO = Vector3d::Zero();
  // Vector3d axis = Vector3d::Zero();
  // double a = 1.;
  // double b = 1.;
  // double alphaf = 90.*DEG2RAD;

  // desdes.set_angular_frequency(info.sim.twf, alphaf);
  // desdes.update(rO, axis, a, b, t-info.sim.tw0, cal_XpreDes.segment(6*0,3));

  // Reference hoge;
  // hoge.TrajectoryParameter hogehoge[24];

  // for(int i=0; i<6*info.value.joint; i++){
  //   des = makeSpline5(t-hogehoge[i].tw0, hogehoge[i].twf, cal_XpreDes(i), cal_Xf(i));

  //   cal_XDes(i) = des(0) + cal_X0(i);
  //   cal_VxiDes(i) = des(1);
  //   cal_dVxiDes(i) = des(2);
  // }

  // for(int i=0; i<6*info.value.joint; i++){
  //   des = makeSpline5(t-info.sim.tw0, info.sim.twf, cal_XpreDes(i), cal_Xf(i));

  //   cal_XDes(i) = des(0) + cal_X0(i);
  //   cal_VxiDes(i) = des(1);
  //   cal_dVxiDes(i) = des(2);
  // }

  if(referenceSequence==info.sim.phase){
    cal_XpreDes = cal_X;

    referenceSequence++;
  }

  for(int i=0; i<info.value.joint; i++){
    for(int j=0; j<6; j++){
      des = makeSpline5(t-info.sim.tw0, info.sim.twf, cal_XpreDes(6*i+j), cal_Xf(6*i+j));

      if(j==2){
        if(round_cast(t-info.sim.tw0, 3)<round_cast(info.sim.twf/2, 3)){
          des = makeSpline5(t-info.sim.tw0, info.sim.twf/2, cal_XpreDes(6*i+j), cal_Xf(6*i+j));
        }
        else{
          if(round_cast(t-info.sim.tw0, 3) == round_cast(info.sim.twf/2, 3)){
            cal_XpreDes(6*i+j) = cal_X(6*i+j);
            // cal_XpreDes(6*i+j) = cal_Xf(6*i+j);
            cal_Xf(6*i+j) = cal_Xtd(6*i+j);
          }

          des = makeSpline5(t-(info.sim.tw0+info.sim.twf/2), info.sim.twf/2, cal_XpreDes(6*i+j), cal_Xf(6*i+j));
        }
      }

      // cal_XDes(6*i+j) = des(0) + cal_X0(6*i+j);
      cal_XDes(6*i+j) = des(0);
      cal_VxiDes(6*i+j) = des(1);
      cal_dVxiDes(6*i+j) = des(2);
    }
  }

  for(int i=1; i<info.value.node; i++){
    cal_VDes.segment(6*(i-1), 6) <<
      cal_VxiDes.segment(6*(i-1), 3),
      dxi2w(cal_VxiDes.segment(6*(i-1)+3, 3), cal_X.segment(6*(i-1)+3, 3));
    cal_dVDes.segment(6*(i-1), 6) <<
      cal_dVxiDes.segment(6*(i-1), 3),
      ddxi2dw(cal_dVxiDes.segment(6*(i-1)+3, 3), cal_X.segment(6*(i-1)+3, 3), w2dxi(cal_V.segment(6*(i-1)+3, 3), cal_X.segment(6*(i-1)+3, 3)));

    cal_Ep.segment(6*(i-1), 6) <<
      cal_XDes.segment(6*(i-1), 3) - cal_X.segment(6*(i-1), 3),
      0.5*(cross(model.hoap2.limb[i].node[info.limb[i].dof].R.col(0))*xi2R(cal_XDes.segment(6*(i-1)+3, 3)).col(0)
	      + cross(model.hoap2.limb[i].node[info.limb[i].dof].R.col(1))*xi2R(cal_XDes.segment(6*(i-1)+3, 3)).col(1)
	      + cross(model.hoap2.limb[i].node[info.limb[i].dof].R.col(2))*xi2R(cal_XDes.segment(6*(i-1)+3, 3)).col(2));
  }
  cal_Ev = cal_VDes - cal_V;

  // velocityController
  cal_VRef = cal_VDes + Kpv*cal_Ep;

  cal_dVRef = cal_dVDes + Kdv*cal_Ev + Kpv*cal_Ep;
}
