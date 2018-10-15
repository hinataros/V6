/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>

#include "config.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::readModel(const string &dir_share, const string &path_yaml_model)
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(path_yaml_model.c_str(), &statFile)!=0)
    cout << manip_error("RigidBodyModel::readModel() error...") << endl
         << manip_error("no such file '"+path_yaml_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_model.c_str());

  if(!doc["Rigid body model"][uniqueNum])
    doc_rigidBodyModel = doc["Rigid body model"];
  else
    doc_rigidBodyModel = doc["Rigid body model"][uniqueNum];

  info->name = doc_rigidBodyModel["Name"].as<string>();

  // m = doc["Body model"]["Mass"][i][j].as<double>();

  // inertia matrix
  // Iw_C(0,0) = doc["Body model"]["Inertia matrix"][i][j][0].as<double>();
  // Iw_C(0,1) = doc["Body model"]["Inertia matrix"][i][j][1].as<double>();
  // Iw_C(0,2) = doc["Body model"]["Inertia matrix"][i][j][2].as<double>();
  // Iw_C(1,0) = doc["Body model"]["Inertia matrix"][i][j][3].as<double>();
  // Iw_C(1,1) = doc["Body model"]["Inertia matrix"][i][j][4].as<double>();
  // Iw_C(1,2) = doc["Body model"]["Inertia matrix"][i][j][5].as<double>();
  // Iw_C(2,0) = doc["Body model"]["Inertia matrix"][i][j][6].as<double>();
  // Iw_C(2,1) = doc["Body model"]["Inertia matrix"][i][j][7].as<double>();
  // Iw_C(2,2) = doc["Body model"]["Inertia matrix"][i][j][8].as<double>();

  // initial configuration
  // for(int i=0; i<6; i++){
  //   if(i<3){
  //     rR0(i) = doc["Initial configuration"]["Initial position"][i].as<double>();
  //     vR0(i) = doc["Initial configuration"]["Initial velocity"][i].as<double>();
  //   }else{
  //     xiR0(3+i) = doc["Initial configuration"]["Initial position"][i].as<double>()*DEG2RAD;
  //     wR0(3+i) = doc["Initial configuration"]["Initial velocity"][i].as<double>();
  //   }
  // }
}
