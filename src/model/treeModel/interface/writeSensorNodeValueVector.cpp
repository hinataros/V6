/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::writeSensorNodeValueVector(string value, VectorXd x)
{
  if(debug) DEBUG;

  if(value=="force torque sensor"){
    for(int i=0; i<info.sensorNodeNum; i++){
      link[info.sensorNode[i].num].f = x.segment(6*i, 3);
      link[info.sensorNode[i].num].n = x.segment(6*1+3, 3);
    }

  }else{
    cout << "no such sensor value..." << endl;
  }
}
