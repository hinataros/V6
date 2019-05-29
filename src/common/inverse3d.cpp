/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"

Matrix3d RLS::Common::inverse3d(Matrix3d A)
{
  double det=0.;

  Matrix3d Ainv; //ここに逆行列が入る
  double buf; //一時的なデータを蓄える
  int i,j,k; //カウンタ
  int n=3;  //配列の次数

  //単位行列を作る
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      Ainv(i,j)=((i==j)?1.0:0.0);
    }
  }
  //掃き出し法
  for(i=0;i<n;i++){
    buf=1/A(i,i);
    for(j=0;j<n;j++){
      A(i,j)*=buf;
      Ainv(i,j)*=buf;
    }
    for(j=0;j<n;j++){
      if(i!=j){
        buf=A(j,i);
        for(k=0;k<n;k++){
          A(j,k)-=A(i,k)*buf;
          Ainv(j,k)-=Ainv(i,k)*buf;
        }
      }
    }
  }

  return Ainv;
}
