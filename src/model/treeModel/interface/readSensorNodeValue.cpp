/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

namespace RLS{
  template<>
  Vector3d RLS::TreeModel::readSensorNodeValue(const int node, const string value)
  {
    if(debug) DEBUG;

    Vector3d x;

    if(value=="position")
      x = link[info->sensorNode[node].num].r;

    else
      cout << "no such control node value..." << endl;

    return x;
  }

  template<>
  Matrix3d RLS::TreeModel::readSensorNodeValue(const int node, const string value)
  {
    if(debug) DEBUG;

    Matrix3d x;

    if(value=="orientation")
      x = link[info->sensorNode[node].num].R;

    else
      cout << "no such control node value..." << endl;

    return x;
  }
}

VectorXd RLS::TreeModel::readSensorNodeValue(string value)
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

  }else{
    cout << "no such sensor value..." << endl;
  }

  return x;
}
