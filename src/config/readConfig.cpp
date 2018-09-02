/**
   @author Sho Miyahara 2017
*/

#include <unistd.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"

void RLS::Config::readConfig()
{
  if(debug) DEBUG;

  cout << "config: " << def << ".conf"<< endl;

  string path = dir.link + "yaml/config/" + def+".conf";
  YAML::Node doc = YAML::LoadFile(path.c_str());

  // execution config
  result.name.cmp = doc["Execution"]["Composite data name"].as<string>();
  result.name.ind = doc["Execution"]["Individual data name"].as<string>();
  flag.shm = doc["Execution"]["Shared memory"].as<bool>();

  if(option!="-d")
    debug = doc["Execution"]["Debug mode"].as<bool>();

  // model config
  model.name = doc["Model"].as<string>();

  // controller config
  controller.flag = doc["Controller"]["Flag"].as<bool>();
  controller.name = doc["Controller"]["Name"].as<string>();
  controller.input = doc["Controller"]["Input"].as<string>();
  controller.work = doc["Controller"]["Work"].as<string>();
  controller.driven = doc["Controller"]["Driven"].as<string>();

  if(controller.driven=="event"||controller.driven=="mix"){
    if(doc["Controller"]["Trigger"])
      controller.trigger = doc["Controller"]["Trigger"].as<string>();
    else
      controller.trigger = "default";
  }

  controller.dynamics = doc["Controller"]["Dynamics"].as<bool>();

  // gp config
  gp.flag = doc["Gp"]["Flag"].as<bool>();
  gp.check = doc["Gp"]["Check"].as<bool>();
  gp.st = doc["Gp"]["Sampling time"].as<int>();
  gp.tstart = doc["Gp"]["Start time offset"].as<double>();

  // tex config
  tex.flag = doc["Tex"]["Flag"].as<bool>();
  tex.title = doc["Tex"]["Title"].as<string>();

  // gif config
  gif.flag = doc["Gif"]["Flag"].as<bool>();
  gif.st = doc["Gif"]["Sampling time"].as<int>();
  gif.linkColor = doc["Gif"]["Link color"].as<string>();
  gif.jointColor = doc["Gif"]["Joint color"].as<string>();
  gif.terminal = doc["Gif"]["Out"]["Terminal"].as<bool>();
  gif.dir = doc["Gif"]["Out"]["Dir"].as<bool>();
  gif.yz.flag = doc["Gif"]["Plane"]["y-z"]["Flag"].as<bool>();
  gif.yz.xMin = doc["Gif"]["Plane"]["y-z"]["x min"].as<string>();
  gif.yz.xMax = doc["Gif"]["Plane"]["y-z"]["x max"].as<string>();
  gif.yz.yMin = doc["Gif"]["Plane"]["y-z"]["y min"].as<string>();
  gif.yz.yMax = doc["Gif"]["Plane"]["y-z"]["y max"].as<string>();
  gif.xz.flag = doc["Gif"]["Plane"]["x-z"]["Flag"].as<bool>();
  gif.xz.xMin = doc["Gif"]["Plane"]["x-z"]["x min"].as<string>();
  gif.xz.xMax = doc["Gif"]["Plane"]["x-z"]["x max"].as<string>();
  gif.xz.yMin = doc["Gif"]["Plane"]["x-z"]["y min"].as<string>();
  gif.xz.yMax = doc["Gif"]["Plane"]["x-z"]["y max"].as<string>();
  gif.xy.flag = doc["Gif"]["Plane"]["x-y"]["Flag"].as<bool>();
  gif.xy.xMin = doc["Gif"]["Plane"]["x-y"]["x min"].as<string>();
  gif.xy.xMax = doc["Gif"]["Plane"]["x-y"]["x max"].as<string>();
  gif.xy.yMin = doc["Gif"]["Plane"]["x-y"]["y min"].as<string>();
  gif.xy.yMax = doc["Gif"]["Plane"]["x-y"]["y max"].as<string>();

  gif.all.flag = doc["Gif"]["Plane"]["3D"]["Flag"].as<bool>();
  gif.all.xMin = doc["Gif"]["Plane"]["3D"]["x min"].as<string>();
  gif.all.xMax = doc["Gif"]["Plane"]["3D"]["x max"].as<string>();
  gif.all.yMin = doc["Gif"]["Plane"]["3D"]["y min"].as<string>();
  gif.all.yMax = doc["Gif"]["Plane"]["3D"]["y max"].as<string>();
  gif.all.zMin = doc["Gif"]["Plane"]["3D"]["z min"].as<string>();
  gif.all.zMax = doc["Gif"]["Plane"]["3D"]["z max"].as<string>();

  // choreonoid motion yaml config
  cho.flag = doc["Choreonoid"]["Flag"].as<bool>();
  cho.st = doc["Choreonoid"]["Sampling time"].as<int>();

  setDir();
}
