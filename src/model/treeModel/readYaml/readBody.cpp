/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>

#include "config.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readBody()
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(include_mp.path.c_str(), &statFile)!=0)
    cout << manip_error("TreeModel::readBody() error...") << endl
         << manip_error("no such file '"+include_mp.path+"'") << endl;

  YAML::Node doc = YAML::LoadFile(include_mp.path.c_str());

  info->linkNum = doc["links"].size();

  link = new Link[info->linkNum];

  resizeLink();

  int rigidBodyNode = 0;
  int forceSensorNode = 2;
  vector<int> sensor;
  vector<string> sensorName;
  for(int i=0; i<info->linkNum; i++){
    link[i].name = doc["links"][i]["name"].as<string>();

    try{
      link[i].parent = doc["links"][i]["parent"].as<string>();
    }catch(...){info->rootNode=i;}

    try{
      if(doc["links"][i]["jointId"].as<int>()>=0){
        link[i].active = true;
        info->dof.joint++;
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

    if(doc["links"][i]["elements"][forceSensorNode]["type"]){
      if(doc["links"][i]["elements"][forceSensorNode]["type"].as<string>()=="ForceSensor"){
        sensor.push_back(i);
        sensorName.push_back(link[i].name);
      }
    }
  }

  info->sensorNodeNum = sensor.size();
  info->sensorNode = new ID[info->sensorNodeNum];

  for(int i=0; i<info->sensorNodeNum; i++){
    info->sensorNode[i].num = sensor[i];
    info->sensorNode[i].name = sensorName[i];
  }

  if(link[info->rootNode].jointType=="fixed")
    info->dof.root = 0;
  else if(link[info->rootNode].jointType=="free")
    info->dof.root = 6;

  info->dof.all = info->dof.root + info->dof.joint;

  // smiyahara: link[0].parentNode is 0 (no initialized)
  for(int i=0; i<info->linkNum; i++)
    for(int j=0; j<info->linkNum; j++)
      if(link[i].parent==link[j].name)
        link[i].parentNode = j;
}
