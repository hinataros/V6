/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::reset()
{
  if(debug) DEBUG;

  dT = VectorXd::Zero(ht_config.stepNum);
  rf = MatrixXd::Zero(3,ht_config.stepNum+1);
  rvrpd = MatrixXd::Zero(3,ht_config.stepNum+1);

  rXeos = MatrixXd::Zero(3,ht_config.stepNum+1);

  // double sopport
  dtDS = VectorXd::Zero(ht_config.stepNum+1);
  alphaDS = VectorXd::Zero(ht_config.stepNum+1);
  dtDSini = VectorXd::Zero(ht_config.stepNum+1);
  dtDSend = VectorXd::Zero(ht_config.stepNum+1);

  rXiniDS = MatrixXd::Zero(3,ht_config.stepNum+1);
  rXeoDS = MatrixXd::Zero(3,ht_config.stepNum+1);
  drXiniDS = MatrixXd::Zero(3,ht_config.stepNum+1);
  drXeoDS = MatrixXd::Zero(3,ht_config.stepNum+1);
  ddrXiniDS = MatrixXd::Zero(3,ht_config.stepNum+1);
  ddrXeoDS = MatrixXd::Zero(3,ht_config.stepNum+1);

  // HT
  alphaHT = VectorXd::Zero(ht_config.stepNum);
  dtHT = VectorXd::Zero(ht_config.stepNum);
  dtTH = VectorXd::Zero(ht_config.stepNum);

  rfT = MatrixXd::Zero(3,ht_config.stepNum+1);
  rfH = MatrixXd::Zero(3,ht_config.stepNum+1);

  rXHT = MatrixXd::Zero(3,ht_config.stepNum+1);
  rXTH = MatrixXd::Zero(3,ht_config.stepNum+1);

  rvrpTd = MatrixXd::Zero(3,ht_config.stepNum+1);
  rvrpHd = MatrixXd::Zero(3,ht_config.stepNum+1);

  // ext HT
  rndvrpTd = MatrixXd::Zero(3,ht_config.stepNum+1);
  rndvrpHd = MatrixXd::Zero(3,ht_config.stepNum+1);
}
