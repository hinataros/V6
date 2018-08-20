/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "treeModel.hpp"

VectorXd RLS::TreeModel::readEndEffectorValueVector(const string value)
{
  if(debug) DEBUG;

  VectorXd x;

  if(value=="position"){
    x = VectorXd(3*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(3*j,3) = link[i].r;
        j++;
      }
    }
  }else if(value=="orientation"){
    x = VectorXd(3*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(3*j,3) = R2xi(link[i].R);
        j++;
      }
    }
  }else if(value=="6D position"){
    x = VectorXd(6*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(6*j,6) <<
          link[i].r,
          R2xi(link[i].R);
        j++;
      }
    }
  }else if(value=="velocity"){
    x = VectorXd(3*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(3*j,3) = link[i].v;
        j++;
      }
    }
  }else if(value=="angular velocity"){
    x = VectorXd(3*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(3*j,3) = link[i].w;
        j++;
      }
    }
  }else if(value=="spatial velocity"){
    x = VectorXd(6*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(6*j,6) <<
          link[i].v,
          link[i].w;
        j++;
      }
    }
  }else if(value=="force"){
    x = VectorXd(3*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(3*j,3) = link[i].f;
        j++;
      }
    }
  }else if(value=="moment"){
    x = VectorXd(3*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(3*j,3) = link[i].f;
        j++;
      }
    }
  }else if(value=="wrench"){
    x = VectorXd(6*info.eeNum);
    for(int i=1, j=0; i<info.linkNum; i++){
      if(link[i].linkType=="end effector"){
        x.segment(6*j,6) <<
          link[i].f,
          link[i].n;
        j++;
      }
    }
  }else{
    cout << "no such end effector value..." << endl;
  }

  return x;
}
