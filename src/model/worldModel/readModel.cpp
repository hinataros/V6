/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "worldModel.hpp"

void RLS::WorldModel::readModel(const string &path_yaml_model)
{
  if(debug) DEBUG;

  string worldModelKeyName = "world model";

  struct stat statFile;
  if(stat(path_yaml_model.c_str(), &statFile)!=0)
    cout << manip_error("WorldModel::readModel() error...") << endl
         << manip_error("no such file '"+path_yaml_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_model.c_str());

  if(doc[worldModelKeyName]){
    if(doc[worldModelKeyName]["include"]){
      if(doc[worldModelKeyName]["include"]["type"])
        include.type = doc[worldModelKeyName]["include"]["type"].as<string>();
      else
        cout << manip_error("WorldModel::readModel() error...") << endl
             << manip_error("Please set a 'type' key") << endl;

      if(doc[worldModelKeyName]["include"]["search"])
        include.search = doc[worldModelKeyName]["include"]["search"].as<string>();
      else
        cout << manip_error("WorldModel::readModel() error...") << endl
             << manip_error("Please set a 'search' key") << endl;

      if(doc[worldModelKeyName]["include"]["path"])
        include.read = doc[worldModelKeyName]["include"]["path"].as<string>();
      else
        cout << manip_error("WorldModel::readModel() error...") << endl
             << manip_error("Please set a 'path' key") << endl;

      setPath();

      if(include.type == "cnoid")
        readCnoid();

      else
        cout << manip_error("WorldModel::readModel() error...") << endl
             << manip_error("no such type '"+include.type+"'") << endl;
    }

    else{
      if(doc[worldModelKeyName]["start time"])
        t0 = doc[worldModelKeyName]["start time"].as<double>();
      if(doc[worldModelKeyName]["finish time"])
        tf = doc[worldModelKeyName]["finish time"].as<double>();
      if(doc[worldModelKeyName]["frame rate"])
        dt = 1./doc[worldModelKeyName]["frame rate"].as<int>();

      if(doc[worldModelKeyName]["gravity"])
        for(int i=0; i<3; i++)
          ag(i) = doc[worldModelKeyName]["gravity"][i].as<double>();
    }
  }

  n = (tf - t0)/dt;
}
