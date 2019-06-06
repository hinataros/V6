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
    if(doc["links"][i]["elements"][0]["elements"][forceSensorNode]["type"]){ // amiyata 肉付きに対応
      if(doc["links"][i]["elements"][0]["elements"][forceSensorNode]["type"].as<string>()=="ForceSensor"){
        sensor.push_back(i);
        sensorName.push_back(link[i].name);
      }
    }

    // amiyata get foot size
    link[i].eeSize = MatrixXd::Zero(0,0);
    bool primF=true;
    string EEnames[4] = {"RLEGEE", "LLEGEE", "RARMEE", "LARMEE"};

    for(int ee=0; ee<4; ee++) {
      if(link[i].name == EEnames[ee]) {
        string typeBox;
        try{
          typeBox = doc["links"][i]["elements"][0]["elements"][0]["geometry"]["type"].as<string>();
        }catch(...){typeBox = "non"; primF=false;}

        if(typeBox == "non"){
          try{
            typeBox = doc["links"][i]["elements"][0]["elements"][1]["elements"][0]["geometry"]["type"].as<string>();
          }catch(...){typeBox = "non";}
        }

        if(typeBox != "Box"){
          // cout << "EE not box or primitive!" << endl;
          break;
        }

        Vector3d trans, box;
        Vector3i rot=Vector3i::Zero();
        double rotate=0.;
        if(primF){
          try{
            rotate = doc["links"][i]["elements"][0]["elements"][0]["rotation"][3].as<double>();
          }catch(...){rotate = 0.;}
          for(int sq=0; sq<3; sq++){
            try{
              trans(sq) = doc["links"][i]["elements"][0]["elements"][0]["translation"][sq].as<double>();
            }catch(...){trans=Vector3d::Zero();}
            try{
              rot(sq) = doc["links"][i]["elements"][0]["elements"][0]["rotation"][sq].as<int>();
            }catch(...){rot << 1,0,0;}
            try{
              box(sq) = doc["links"][i]["elements"][0]["elements"][0]["geometry"]["size"][sq].as<double>();
            }catch(...){box=Vector3d::Zero();}
          }
        } else {
          try{
            rotate = doc["links"][i]["elements"][0]["elements"][1]["elements"][0]["rotation"][3].as<double>();
          }catch(...){rotate = 0.;}
          for(int sq=0; sq<3; sq++){
            try{
              trans(sq) = doc["links"][i]["elements"][0]["elements"][1]["elements"][0]["translation"][sq].as<double>();
            }catch(...){trans=Vector3d::Zero();}
            try{
              rot(sq) = doc["links"][i]["elements"][0]["elements"][1]["elements"][0]["rotation"][sq].as<int>();
            }catch(...){rot << 1,0,0;}
            try{
              box(sq) = doc["links"][i]["elements"][0]["elements"][1]["elements"][0]["geometry"]["size"][sq].as<double>();
            }catch(...){box=Vector3d::Zero();}
          }
        }

        // generate rotation matrix
        Matrix3d Ree = Matrix3d::Identity();
        // MatrixXd exR = MatrixXd::Zero(5,5);
        // exR(2,2) = 1.;
        // exR(1,0) = exR(1,3) = exR(4,3) = sin(rotate*DEG2RAD);
        // exR(0,1) = exR(3,1) = exR(3,4) = -sin(rotate*DEG2RAD);
        // exR(0,0) = exR(1,1) = exR(3,3) = exR(4,4) = cos(rotate*DEG2RAD);
        // for(int el=0; el<3; el++)
        //   if(rot(el))
        //     Ree = exR.block(2-el,2-el, 3,3);
        if(rot(0))
          Ree = R("x", rotate*DEG2RAD);
        else if(rot(1))
          Ree = R("y", rotate*DEG2RAD);
        else if(rot(2))
          Ree = R("z", rotate*DEG2RAD);

        //    y
        // 3 --- 0
        // |Front|
        // |     | x
        // |(Leg)|
        // 2 --- 1
        //
        link[i].eeSize = MatrixXd::Zero(4,2);
        link[i].eeSize <<
          trans(0) + (Ree*box)(0)/2., trans(1) + (Ree*box)(1)/2.,
          trans(0) - (Ree*box)(0)/2., trans(1) + (Ree*box)(1)/2.,
          trans(0) - (Ree*box)(0)/2., trans(1) - (Ree*box)(1)/2.,
          trans(0) + (Ree*box)(0)/2., trans(1) - (Ree*box)(1)/2.;
        // o(link[i].eeSize);
      }
    }
    // *** amiyata
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
