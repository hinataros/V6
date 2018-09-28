/**
   @author Sho Miyahara 2017
*/

#include <sys/stat.h>
#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::readWork()
{
  struct stat statFile;
  if(stat(this->info.path_work.c_str(), &statFile)!=0){
    cout << manip_error("RlsDynamics::readWork() error...") << endl
         << manip_error("no such file '"+this->info.path_work+"'") << endl;

    return -1;
  }

  YAML::Node doc = YAML::LoadFile(this->info.path_work.c_str());

  string key = "Control type";

  if(doc[key]["Input"])
    this->info.input = doc[key]["Input"].as<string>();
  if(doc[key]["Driven"])
    this->info.driven = doc[key]["Driven"].as<string>();

  if(this->info.driven=="event"||this->info.driven=="mix")
    if(doc[key]["Trigger"])
      this->info.trigger = doc[key]["Trigger"].as<string>();

  return 1;
}
