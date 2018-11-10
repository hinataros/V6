/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "treeModel.hpp"

namespace RLS{
  template<>
  Vector3d RLS::TreeModel::readControlNodeValue(const int node, const string value)
  {
    if(debug) DEBUG;

    Vector3d x;

    if(value=="position")
      x = link[info->controlNode[node].num].r;

    else
      cout << "no such control node value..." << endl;

    return x;
  }

  template<>
  Matrix3d RLS::TreeModel::readControlNodeValue(const int node, const string value)
  {
    if(debug) DEBUG;

    Matrix3d x;

    if(value=="orientation")
      x = link[info->controlNode[node].num].R;

    else
      cout << "no such control node value..." << endl;

    return x;
  }
}

VectorXd RLS::TreeModel::readControlNodeValue(string value)
{
  if(debug) DEBUG;

  VectorXd x;

  if(value=="position"){
    x = VectorXd(3*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(3*i,3) = link[info->controlNode[i].num].r;

  }else if(value=="orientation"){
    x = VectorXd(3*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(3*i,3) = R2xi(link[info->controlNode[i].num].R);

  }else if(value=="velocity"){
    x = VectorXd(3*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(3*i,3) = link[info->controlNode[i].num].v;

  }else if(value=="angular velocity"){
    x = VectorXd(3*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(3*i,3) = link[info->controlNode[i].num].w;

  }else if(value=="spatial velocity"){
    x = VectorXd(6*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(6*i,6) <<
        link[info->controlNode[i].num].v,
        link[info->controlNode[i].num].w;

  }else if(value=="force"){
    x = VectorXd(3*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(3*i,3) = link[info->controlNode[i].num].f;

  }else if(value=="moment"){
    x = VectorXd(3*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(3*i,3) = link[info->controlNode[i].num].n;

  }else if(value=="wrench"){
    x = VectorXd(6*info->controlNodeNum);
    for(int i=0; i<info->controlNodeNum; i++)
      x.segment(6*i,6) <<
        link[info->controlNode[i].num].f,
        link[info->controlNode[i].num].n;

  }else{
    cout << "no such end effector value..." << endl;
  }

  return x;
}
