/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::reset()
{
  if(debug) DEBUG;

  ht_config.convergenceNum = vwpNum + convergencePhaseNum;

  dT = VectorXd::Zero(ht_config.convergenceNum);
  rf = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  rvrpd = MatrixXd::Zero(3,ht_config.convergenceNum+1);

  rXeos = MatrixXd::Zero(3,ht_config.convergenceNum+1);

  // double sopport
  dtDS = VectorXd::Zero(ht_config.convergenceNum+1);
  alphaDS = VectorXd::Zero(ht_config.convergenceNum+1);
  dtDSini = VectorXd::Zero(ht_config.convergenceNum+1);
  dtDSend = VectorXd::Zero(ht_config.convergenceNum+1);

  rXiniDS = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  rXeoDS = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  drXiniDS = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  drXeoDS = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  ddrXiniDS = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  ddrXeoDS = MatrixXd::Zero(3,ht_config.convergenceNum+1);

  // HT
  alphaHT = VectorXd::Zero(ht_config.convergenceNum);
  dtHT = VectorXd::Zero(ht_config.convergenceNum);
  dtTH = VectorXd::Zero(ht_config.convergenceNum);

  rfT = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  rfH = MatrixXd::Zero(3,ht_config.convergenceNum+1);

  rXHT = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  rXTH = MatrixXd::Zero(3,ht_config.convergenceNum+1);

  rvrpTd = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  rvrpHd = MatrixXd::Zero(3,ht_config.convergenceNum+1);

  // ext HT
  rndvrpTd = MatrixXd::Zero(3,ht_config.convergenceNum+1);
  rndvrpHd = MatrixXd::Zero(3,ht_config.convergenceNum+1);
}
