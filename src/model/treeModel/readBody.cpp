/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readBody(const string body_path)
{
  if(debug) DEBUG;

  vector<int> node, dof;

  YAML::Node doc = YAML::LoadFile(body_path.c_str());

  // try{
  //   if(doc["links"][0]["name"].as<string>()=="free")
  //     dof.push_back(6);
  // }catch(...){cout << "error... " << endl;};
  // dof.push_back(6);
  // info.dof.all += dof[0];

  // node.push_back(1);
  // info.value.node = node[0];
  // info.value.all += node[0];

  info.linkNum = doc["links"].size();

  link = new Link[info.linkNum];

  initializeLink();

  // for(int i=1; i<linkNum; i++){
  //   parent = doc["links"][i]["parent"].as<string>();

  //   try{
  //     if(doc["links"][i]["jointId"].as<int>()>=0)
  //       active[i] = true;
  //   }catch(...){
  //     active[i] = false;
  //   }
  // }

  // // info.limb = new Info::Limb[info.value.node];

  // for(int i=0; i<info.value.node; i++){
  //   info.limb[i].dof = dof[i];
  //   info.limb[i].value = node[i];
  // }

  // limb = new Limb[info.value.node];
  // for(int i=0; i<info.value.node; i++)
  //   limb[i].node = new Node[info.limb[i].value];

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

  if(link[info.rootNode].jointType=="fixed")
    info.dof.root = 0;
  else if(link[info.rootNode].jointType=="free")
    info.dof.root = 6;

  info.dof.all = info.dof.root + info.dof.joint;

  // smiyahara: link[0].parentNode is 0 (no initialized)
  for(int i=0, count=0; i<info.linkNum; i++, count=0){
    for(int j=0; j<info.linkNum; j++){
      if(link[i].parent==link[j].name)
        link[i].parentNode = j;

      if(link[i].name==link[j].parent)
        count++;
    }

    if(count)
      link[i].linkType = "limb";
    else{
      info.eeNum++;
      link[i].linkType = "end effector";
    }

    if(i==info.rootNode)
      link[i].linkType = "root";
  }

  initializeAll();

  // smiyahara: 場所がびみょ～
  joints();

  // o(info.rootNode);
  // o(info.dof.joint);

  // o(link[0].parent);

  // o(info.linkNum);
  // for(int i=0; i<info.linkNum; i++){
  //   // o(i);
  //   o(link[i].name);
  //   // o(link[i].name);
  //   // o(link[i].parentNode);
  //   // o(link[i].linkType);
  // //   o(link[i].parent);
  // //   o(link[i].jointType);
  // //   o(link[i].jointAxis);
  // //   o(link[i].d.transpose());
  // //   o(link[i].m);
  // //   o(link[i].ri2C.transpose());
  // //   o(link[i].Iw_C);
  // //   o(link[i].jS);
  // }
  // gc;
}
