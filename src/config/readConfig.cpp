#include <unistd.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"

void RLS::Config::readConfig()
{
  if(flag.debug) DEBUG;

  string path = dir.link + "yaml/config/" + def+".conf";
  YAML::Node doc = YAML::LoadFile(path.c_str());

  // execution config
  result.name.cmp = doc["Execution"]["Composite data name"].as<string>();
  result.name.ind = doc["Execution"]["Individual data name"].as<string>();
  flag.shm = doc["Execution"]["Shared memory"].as<bool>();

  if(option!="-d")
    flag.debug = doc["Execution"]["Debug mode"].as<bool>();

  // model config
  body.name = doc["Model"]["Body name"].as<string>();
  cnoid.name = doc["Model"]["cnoid name"].as<string>();


  // controller config
  controller.flag = doc["Controller"]["Flag"].as<bool>();
  controller.name = doc["Controller"]["Name"].as<string>();
  controller.input = doc["Controller"]["Input"].as<string>();
  controller.work = doc["Controller"]["Work"].as<string>();
  controller.dynamics = doc["Controller"]["Dynamics"].as<bool>();

  // graph config
  graph.flag = doc["Graph"]["Flag"].as<bool>();
  graph.check = doc["Graph"]["Check"].as<bool>();
  graph.gp = doc["Graph"]["Make gp"].as<bool>();
  graph.tex = doc["Graph"]["Make tex"].as<bool>();
  graph.st = doc["Graph"]["Sampling time"].as<int>();

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
