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

  struct stat statFile;
  if(stat(path_yaml_model.c_str(), &statFile)!=0)
    cout << manip_error("WorldModel::readModel() error...") << endl
         << manip_error("no such file '"+path_yaml_model+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_model.c_str());

  if(doc["World model"]){
    if(doc["World model"]["include"]){
      if(doc["World model"]["include"]["type"])
        include.type = doc["World model"]["include"]["type"].as<string>();
      else
        cout << manip_error("WorldModel::readModel() error...") << endl
             << manip_error("Please set a 'type' key") << endl;

      if(doc["World model"]["include"]["search"])
        include.search = doc["World model"]["include"]["search"].as<string>();
      else
        cout << manip_error("WorldModel::readModel() error...") << endl
             << manip_error("Please set a 'search' key") << endl;

      if(doc["World model"]["include"]["path"])
        include.read = doc["World model"]["include"]["path"].as<string>();
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
      if(doc["WorldModel"]["Start time"])
        t0 = doc["WorldModel"]["Start time"].as<double>();
      if(doc["WorldModel"]["Finish time"])
        tf = doc["WorldModel"]["Finish time"].as<double>();
      if(doc["WorldModel"]["Frame rate"])
        dt = 1./doc["WorldModel"]["Frame rate"].as<int>();

      if(doc["WorldModel"]["Gravity"])
        for(int i=0; i<3; i++)
          ag(i) = doc["WorldModel"]["Gravity"][i].as<double>();
    }
  }

  n = (tf - t0)/dt;
}
