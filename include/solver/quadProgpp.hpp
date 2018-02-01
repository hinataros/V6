/**
   @author Sho Miyahara 2017
*/

#ifdef QUADPROGPP
#include "QuadProg++.hpp"
#endif

namespace RLS{
  class QuadProgpp{
  private:
  public:
    VectorXd solver(MatrixXd&, VectorXd&, VectorXd&);
    VectorXd solver(MatrixXd&, VectorXd&, string, MatrixXd&, VectorXd&, VectorXd&);
    VectorXd solver(MatrixXd&, VectorXd&, MatrixXd&, VectorXd&, MatrixXd&, VectorXd&, VectorXd&);
  };
}
