/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeWalking(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // dcmWalkiing
  // ******************************
  phaseDS = 0;
  flagDS = true;

  // stepNum = 10;
  stepNum = 18;
  stepPhase = 0;
  tstep0 = 0.;
  tstep = 0.;
  tDS0 = 0.;

  dt = VectorXd::Zero(stepNum);
  rf = MatrixXd::Zero(3,stepNum+1);
  rvrpd = MatrixXd::Zero(3,stepNum+1);

  rXeos = MatrixXd::Zero(3,stepNum+1);

  // double sopport
  dtDS = VectorXd::Zero(stepNum+1);
  alphDS = VectorXd::Zero(stepNum+1);
  dtDSini = VectorXd::Zero(stepNum+1);
  dtDSend = VectorXd::Zero(stepNum+1);

  rXiniDS = MatrixXd::Zero(3,stepNum+1);
  rXeoDS = MatrixXd::Zero(3,stepNum+1);
  drXiniDS = MatrixXd::Zero(3,stepNum+1);
  drXeoDS = MatrixXd::Zero(3,stepNum+1);
  ddrXiniDS = MatrixXd::Zero(3,stepNum+1);
  ddrXeoDS = MatrixXd::Zero(3,stepNum+1);

  // HT
  alphaHT = VectorXd::Zero(stepNum);
  dtHT = VectorXd::Zero(stepNum);
  dtTH = VectorXd::Zero(stepNum);

  rfT = MatrixXd::Zero(3,stepNum+1);
  rfH = MatrixXd::Zero(3,stepNum+1);

  rXHT = MatrixXd::Zero(3,stepNum+1);
  rXTH = MatrixXd::Zero(3,stepNum+1);

  rvrpTd = MatrixXd::Zero(3,stepNum+1);
  rvrpHd = MatrixXd::Zero(3,stepNum+1);

  // polynomial
  initial_walking = true;
  tphasef = 0.;
  support = 0;

  // EE reference
  referenceSequence = 1;
  cal_Xtd = VectorXd::Zero(6*info.controlNodeNum);
}
