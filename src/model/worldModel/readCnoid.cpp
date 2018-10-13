/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "worldModel.hpp"

void RLS::WorldModel::readCnoid()
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(include.path.c_str(), &statFile)!=0)
    cout << manip_error("WorldModel::readCnoid() error...") << endl
         << manip_error("no such file '"+include.path+"'") << endl;

  YAML::Node doc = YAML::LoadFile(include.path.c_str());

  t0 = doc["toolbars"]["TimeBar"]["minTime"].as<double>();
  tf = doc["toolbars"]["TimeBar"]["maxTime"].as<double>();
  dt = 1./doc["toolbars"]["TimeBar"]["frameRate"].as<int>();

  int worldItem = 0;
  int aistItem;
  bool aistFlag = false;

  int num = doc["items"]["children"][worldItem]["children"].size();
  for(int i=0; i<num; i++)
    if(doc["items"]["children"][worldItem]["children"][i]["name"].as<string>()=="AISTSimulator"){
      aistFlag = true;
      aistItem = i;
    }

  if(!aistFlag)
    cout << manip_warning("WorldModel::readCnoid(): warning: ")
         << manip_warning("not found 'AISTSimulator' item") << endl;

  if(doc["items"]["children"][worldItem]["children"][aistItem]["data"]["gravity"])
    for(int i=0; i<3; i++)
      ag(i) = doc["items"]["children"][worldItem]["children"][aistItem]["data"]["gravity"][i].as<double>();
}
