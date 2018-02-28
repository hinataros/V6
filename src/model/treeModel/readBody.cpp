/**
   @author Sho Miyahara 2017
*/

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::readBody(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  int rigidBodyNode = 0;

  string jointTypetemp;
  int nodetemp = 0;
  double mtemp = 0.;
  Vector3d ri2Ctemp = Vector3d::Zero();
  Vector3d dtemp = Vector3d::Zero();
  Matrix3d Iw_Ctemp = Matrix3d::Zero();

  vector<int> node;
  vector<string> jointType;
  vector<double> m;
  vector<Vector3d> ri2C, d;
  vector<Matrix3d> Iw_C;

  YAML::Node doc = YAML::LoadFile((config.dir.body+"skeleton/"+config.body.name+".body").c_str());

  int nodeNum = doc["links"].size();

  info.value.node = 1;

  //**************** get root's data ****************
  string parent = doc["links"][0]["name"].as<string>();

  jointTypetemp = doc["links"][0]["jointType"].as<string>();
  mtemp = doc["links"][0]["elements"][rigidBodyNode]["mass"].as<double>();

  for(int i=0; i<3; i++){
    ri2Ctemp(i) = doc["links"][0]["elements"][rigidBodyNode]["centerOfMass"][i].as<double>();
  }

  for(int i=0, k=0; i<3; i++){
    for(int j=0; j<3; j++, k++){
      Iw_Ctemp(j,i) = doc["links"][0]["elements"][rigidBodyNode]["inertia"][k].as<double>();
    }
  }

  node.push_back(1);
  jointType.push_back(jointTypetemp);
  m.push_back(mtemp);
  d.push_back(dtemp);
  ri2C.push_back(ri2Ctemp);
  Iw_C.push_back(Iw_Ctemp);

  //**************** get all data ****************
  for(int i=1; i<nodeNum; i++){
    try{
      doc["links"][i]["jointId"].as<int>();

      // if(doc["links"][i]["elements"][rigidBodyNode]["type"].as<string>() == "RigidBody"){
      jointTypetemp = doc["links"][i]["jointAxis"].as<string>();
      mtemp = doc["links"][i]["elements"][rigidBodyNode]["mass"].as<double>();
      try{
        for(int j=0; j<3; j++)
          dtemp(j) = doc["links"][i]["translation"][j].as<double>();
      }catch(...){dtemp = Vector3d::Zero();}

      for(int j=0; j<3; j++)
        ri2Ctemp(j) = doc["links"][i]["elements"][rigidBodyNode]["centerOfMass"][j].as<double>();

      for(int j=0, l=0; j<3; j++)
        for(int k=0; k<3; k++, l++)
          Iw_Ctemp(j,k) = doc["links"][i]["elements"][rigidBodyNode]["inertia"][l].as<double>();

      nodetemp++;
      jointType.push_back(jointTypetemp);
      m.push_back(mtemp);
      d.push_back(dtemp);
      ri2C.push_back(ri2Ctemp);
      Iw_C.push_back(Iw_Ctemp);

    }catch(...){
      try{
        doc["links"][i+1]["parent"].as<string>();

        if(doc["links"][i]["name"].as<string>()!=doc["links"][i+1]["parent"].as<string>()){
          try{
            for(int j=0; j<3; j++)
              dtemp(j) = doc["links"][i]["translation"][j].as<double>();
          }catch(...){dtemp = Vector3d::Zero();}

          nodetemp++;
          node.push_back(nodetemp);
          jointType.push_back("fix");
          m.push_back(0.);
          d.push_back(dtemp);
          ri2C.push_back(Vector3d::Zero());
          Iw_C.push_back(Matrix3d::Identity());

          nodetemp=0;
          info.value.node++;
          info.value.joint++;
        }
      }catch(...){
        try{
          for(int j=0; j<3; j++)
            dtemp(j) = doc["links"][i]["translation"][j].as<double>();
        }catch(...){dtemp = Vector3d::Zero();}

        nodetemp++;
        node.push_back(nodetemp);
        jointType.push_back("fix");
        m.push_back(0.);
        d.push_back(dtemp);
        ri2C.push_back(Vector3d::Zero());
        Iw_C.push_back(Matrix3d::Identity());

        nodetemp=0;
        info.value.node++;
        info.value.joint++;
      }
    }
  }

  info.limb = new Info::Limb[info.value.node];
  limb = new Limb[info.value.node];

  for(int i=0; i<info.value.node; i++){
    if(i==0)
      info.limb[i].dof = 6;
    else{
      info.limb[i].dof = node[i]-1;
      info.dof.joint += info.limb[i].dof;
    }

    info.limb[i].value = node[i];

    info.value.all += info.limb[i].value;
    info.dof.all += info.limb[i].dof;

    limb[i].node = new Node[info.limb[i].value];
  }

  initialize(config, info);

  for(int i=0, k=0; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].value; j++, k++){
      limb[i].node[j].jointType = jointType[k];
      limb[i].node[j].d = d[k];
      limb[i].node[j].m = m[k];
      all.m += limb[i].node[j].m;
      limb[i].node[j].ri2C = ri2C[k];
      limb[i].node[j].Iw_C = Iw_C[k];
    }
  }

  // smiyahara: 場所がびみょ～
  joints(config, info);
}
