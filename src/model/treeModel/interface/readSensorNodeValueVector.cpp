/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::readSensorNodeValueVector(string value)
{
  if(debug) DEBUG;

  VectorXd x;

  if(value=="force torque sensor"){
    x = VectorXd(6*info->sensorNodeNum);
    for(int i=0; i<info->sensorNodeNum; i++){
      x.segment(6*i,6) <<
        link[info->sensorNode[i].num].f,
        link[info->sensorNode[i].num].n;
    }

  }else if(value=="6D position"){
    x = VectorXd(6*info->sensorNodeNum);
    for(int i=0; i<info->sensorNodeNum; i++){
      x.segment(6*i,6) <<
        link[info->sensorNode[i].num].r,
        R2xi(link[info->sensorNode[i].num].R);
    }

  }else{
    cout << "no such sensor value..." << endl;
  }

  return x;
}
