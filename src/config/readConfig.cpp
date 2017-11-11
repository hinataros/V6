#include <unistd.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"

void RLS::Config::readConfig()
{
  if(flag.debug) DEBUG;

  path = link + "yaml/config/" + def + ".yaml";

  YAML::Node doc = YAML::LoadFile(path.c_str());

  // // default config
  name = doc["Default config"]["Simulation name"].as<string>();
  model.name = doc["Default config"]["Model name"].as<string>();
  controller.name = doc["Default config"]["Controller name"].as<string>();
  if(option!="-d")
    flag.debug = doc["Default config"]["Debug mode"].as<bool>();

  // simulation config
  solver.input = doc["Simulation config"]["Solver"]["Control input"].as<string>();

  controller.flag = doc["Simulation config"]["Controller"]["Flag"].as<bool>();
  controller.dynamics = doc["Simulation config"]["Controller"]["Dynamics"].as<bool>();
  controller.work = doc["Simulation config"]["Controller"]["Work"].as<string>();

  graph.flag = doc["Simulation config"]["Graph"]["Flag"].as<bool>();
  graph.check = doc["Simulation config"]["Graph"]["Check"].as<bool>();
  graph.gp = doc["Simulation config"]["Graph"]["Make gp"].as<bool>();
  graph.tex = doc["Simulation config"]["Graph"]["Make tex"].as<bool>();
  graph.st = doc["Simulation config"]["Graph"]["Sampling time"].as<int>();

  gif.flag = doc["Simulation config"]["Gif"]["Flag"].as<bool>();
  gif.st = doc["Simulation config"]["Gif"]["Sampling time"].as<int>();
  gif.linkColor = doc["Simulation config"]["Gif"]["Link color"].as<string>();
  gif.jointColor = doc["Simulation config"]["Gif"]["Joint color"].as<string>();
  gif.terminal = doc["Simulation config"]["Gif"]["Out"]["Terminal"].as<bool>();
  gif.dir = doc["Simulation config"]["Gif"]["Out"]["Dir"].as<bool>();
  gif.yz.flag = doc["Simulation config"]["Gif"]["Plane"]["y-z"]["Flag"].as<bool>();
  gif.yz.xMin = doc["Simulation config"]["Gif"]["Plane"]["y-z"]["x min"].as<string>();
  gif.yz.xMax = doc["Simulation config"]["Gif"]["Plane"]["y-z"]["x max"].as<string>();
  gif.yz.yMin = doc["Simulation config"]["Gif"]["Plane"]["y-z"]["y min"].as<string>();
  gif.yz.yMax = doc["Simulation config"]["Gif"]["Plane"]["y-z"]["y max"].as<string>();
  gif.xz.flag = doc["Simulation config"]["Gif"]["Plane"]["x-z"]["Flag"].as<bool>();
  gif.xz.xMin = doc["Simulation config"]["Gif"]["Plane"]["x-z"]["x min"].as<string>();
  gif.xz.xMax = doc["Simulation config"]["Gif"]["Plane"]["x-z"]["x max"].as<string>();
  gif.xz.yMin = doc["Simulation config"]["Gif"]["Plane"]["x-z"]["y min"].as<string>();
  gif.xz.yMax = doc["Simulation config"]["Gif"]["Plane"]["x-z"]["y max"].as<string>();
  gif.xy.flag = doc["Simulation config"]["Gif"]["Plane"]["x-y"]["Flag"].as<bool>();
  gif.xy.xMin = doc["Simulation config"]["Gif"]["Plane"]["x-y"]["x min"].as<string>();
  gif.xy.xMax = doc["Simulation config"]["Gif"]["Plane"]["x-y"]["x max"].as<string>();
  gif.xy.yMin = doc["Simulation config"]["Gif"]["Plane"]["x-y"]["y min"].as<string>();
  gif.xy.yMax = doc["Simulation config"]["Gif"]["Plane"]["x-y"]["y max"].as<string>();

  gif.all.flag = doc["Simulation config"]["Gif"]["Plane"]["3D"]["Flag"].as<bool>();
  gif.all.xMin = doc["Simulation config"]["Gif"]["Plane"]["3D"]["x min"].as<string>();
  gif.all.xMax = doc["Simulation config"]["Gif"]["Plane"]["3D"]["x max"].as<string>();
  gif.all.yMin = doc["Simulation config"]["Gif"]["Plane"]["3D"]["y min"].as<string>();
  gif.all.yMax = doc["Simulation config"]["Gif"]["Plane"]["3D"]["y max"].as<string>();
  gif.all.zMin = doc["Simulation config"]["Gif"]["Plane"]["3D"]["z min"].as<string>();
  gif.all.zMax = doc["Simulation config"]["Gif"]["Plane"]["3D"]["z max"].as<string>();

  cho.flag = doc["Simulation config"]["Choreonoid"]["Flag"].as<bool>();
  cho.st = doc["Simulation config"]["Choreonoid"]["Sampling time"].as<int>();
}
