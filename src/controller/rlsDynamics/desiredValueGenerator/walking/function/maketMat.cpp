#include "config.hpp"
#include "walkingFunction.hpp"


MatrixXd RLS::WalkingFunction::maketMat(int num, int dim, double ts)
{
  int i,j;
  MatrixXd t = MatrixXd::Zero(num, dim);

  // for(i=0; i<dim; i++){
  //   t(0,i) = intPow(ts, i);
  // }
  for(i=0; i<num; i++){
    for(j=i; j<(dim); j++){
      t(i,j) = factorio(j,i) * intPow(ts, j-i);
    }
  }

  return t;
}

MatrixXd RLS::WalkingFunction::maketMat(int dim, double ts)
{
  return maketMat(dim, dim*2, ts);
}


MatrixXd RLS::WalkingFunction::makedtMat(int num, int dim, double ts)
{
  int i,j;
  MatrixXd dt = MatrixXd::Zero(num+1, dim);

  for(i=0; i<dim; i++){
    dt(0,i) = intPow(ts, i);
  }
  for(i=1; i<num+1; i++){
    for(j=i; j<(dim); j++){
      dt(i,j) = factorio(j,i) * intPow(ts, j-i);
    }
  }

  return dt.block(1,0, num,dim);
}

MatrixXd RLS::WalkingFunction::makedtMat(int dim, double ts)
{
  return makedtMat(dim, dim*2, ts);
}
