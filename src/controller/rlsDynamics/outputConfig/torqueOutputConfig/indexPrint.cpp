/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputIndexPrintConfig(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd vertex =
    // test
    // (MatrixXd(2,4)<<
    //  1., 1.,-1.,-1.,
    //  1.,-1.,-1., 1.
     1.e-3*(MatrixXd(2,4)<<
     116./3, 116./3, -80./3, -80./3,
        21.,   -21.,   -21.,    21.
     ).finished();

  MatrixXd vertexr = MatrixXd::Zero(2,4);
  MatrixXd vertexl = MatrixXd::Zero(2,4);
  for(int i=0; i<4; i++){
    // test
    // vertexr.col(i) = (Vector2d()<<1.,-2.).finished()+vertex.col(i);
    // vertexl.col(i) = (Vector2d()<<0.,2.).finished()+vertex.col(i);
    vertexr.col(i) = cal_X.segment(0, 2)+vertex.col(i);
    vertexl.col(i) = cal_X.segment(6, 2)+vertex.col(i);
  }

  Vector2d rmax = (Vector2d()<<
                       vertexr.row(0).maxCoeff(),
                       vertexr.row(1).minCoeff()
                       ).finished();
  Vector2d lmax = (Vector2d()<<
                       vertexl.row(0).maxCoeff(),
                       vertexl.row(1).maxCoeff()
                       ).finished();


  // smiyahara: 足の回転考えていない
  // smiyahara: 逆向きはできない
  // smiyahara: 両足のy軸位置の端が一致した場合、逆行列が取れない
  MatrixXd A = Matrix2d::Zero();
  Vector2d b = Vector2d::Zero();
  Vector2d c = Vector2d::Zero();
  for(int i=0; i<4; i++){
    A <<
      rmax(1),1.,
      lmax(1),1.;
    b << rmax(0), lmax(0);

    c << vertexr.row(1)(i), 1.;
    if(vertexr.row(0)(i)>c.transpose()*A.inverse()*b)
      rmax = vertexr.col(i);

    c << vertexl.row(1)(i), 1.;
    if(vertexl.row(0)(i)>c.transpose()*A.inverse()*b)
      lmax = vertexl.col(i);
  }

  Vector2d rmin = (Vector2d()<<
                       vertexr.row(0).minCoeff(),
                       vertexr.row(1).minCoeff()
                       ).finished();
  Vector2d lmin = (Vector2d()<<
                       vertexl.row(0).minCoeff(),
                       vertexl.row(1).maxCoeff()
                       ).finished();

  for(int i=0; i<4; i++){
    A <<
      rmin(1),1.,
      lmin(1),1.;
    b << rmin(0), lmin(0);

    c << vertexr.row(1)(i), 1.;
    if(vertexr.row(0)(i)<c.transpose()*A.inverse()*b)
      rmin = vertexr.col(i);

    c << vertexl.row(1)(i), 1.;
    if(vertexl.row(0)(i)<c.transpose()*A.inverse()*b)
      lmin = vertexl.col(i);
  }

  dc_list.indexPrintMatrix = MatrixXd::Zero(2*4+2*3, 5);

  double contactr = 1., contactl = 1.;
  if(info.limb[0].contact==false&&info.limb[1].contact==true)
    contactr = NAN;
  if(info.limb[0].contact==true&&info.limb[1].contact==false)
    contactl = NAN;

  dc_list.indexPrintMatrix =
    (MatrixXd(2*4+2*3,5)<<
     contactr*vertexr, contactr*vertexr.col(0),
     contactl*vertexl, contactl*vertexl.col(0),
     contactr*rmax, contactl*lmax, NAN*MatrixXd::Zero(2,3),
     contactr*rmin, contactl*lmin, NAN*MatrixXd::Zero(2,3),
     model.hoap2.all.rC.head(2), NAN*MatrixXd::Zero(2,4),
     rp, NAN*MatrixXd::Zero(2,4),
     rX.head(2), NAN*MatrixXd::Zero(2,4)
     ).finished();
}
