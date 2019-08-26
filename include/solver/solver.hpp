/**
   @author Sho Miyahara 2017
*/

#ifndef SOLVER_HPP_
#define SOLVER_HPP_

#include "quadProgpp.hpp"
#include "convexSolver.hpp"
#include "cfsqp.hpp"

namespace RLS{
  class Solver:
    public QuadProgpp,
    public CFSQP{
  public:
  };
}

#endif //SOLVER_HPP_
