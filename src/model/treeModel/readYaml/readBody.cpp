/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readBody()
{
  if(debug) DEBUG;

  YAML::Node doc = YAML::LoadFile(info.path.body.c_str());

  info.linkNum = doc["links"].size();

  link = new Link[info.linkNum];

  initializeInfo();
  initializeLink();

  int rigidBodyNode = 0;
  for(int i=0; i<info.linkNum; i++){
    link[i].name = doc["links"][i]["name"].as<string>();

    try{
      link[i].parent = doc["links"][i]["parent"].as<string>();
    }catch(...){info.rootNode=i;}

    try{
      if(doc["links"][i]["jointId"].as<int>()>=0){
        link[i].active = true;
        info.dof.joint++;
      }
    }catch(...){}

    try{
      link[i].jointType = doc["links"][i]["jointType"].as<string>();
    }catch(...){link[i].jointType="no joint";}

    try{
      link[i].jointAxis = doc["links"][i]["jointAxis"].as<string>();
    }catch(...){link[i].jointAxis="no axis";}

    // joint distance
    try{
      for(int j=0; j<3; j++)
        link[i].d(j) = doc["links"][i]["translation"][j].as<double>();
    }catch(...){link[i].d=Vector3d::Zero();}

    // mass
    try{
      link[i].m = doc["links"][i]["elements"][rigidBodyNode]["mass"].as<double>();
      all.m += link[i].m;
    }catch(...){link[i].m=0.;}

    // com
    try{
      for(int j=0; j<3; j++)
        link[i].ri2C(j) = doc["links"][i]["elements"][rigidBodyNode]["centerOfMass"][j].as<double>();
    }catch(...){link[i].ri2C=Vector3d::Zero();}

    // inertia matrix
    try{
      for(int j=0, l=0; j<3; j++)
        for(int k=0; k<3; k++, l++)
          link[i].Iw_C(j,k) = doc["links"][i]["elements"][rigidBodyNode]["inertia"][l].as<double>();
    }catch(...){link[i].Iw_C=Matrix3d::Zero();}
  }

  setInfo();

  initializeAll();

  // smiyahara: 場所がびみょ～
  joints();
}
