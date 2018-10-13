/**
   @author Sho Miyahara 2018
*/

#include <sys/stat.h>
#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::readOutput(const string &path_yaml_output)
{
  if(debug) DEBUG;

  struct stat statFile;
  if(stat(path_yaml_output.c_str(), &statFile)!=0)
    cout << manip_error("Output::readOutput() error...") << endl
         << manip_error("no such file '"+path_yaml_output+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_output.c_str());

  if(doc["Result"]["Composite data name"])
    result.cmp = doc["Result"]["Composite data name"].as<string>();
  if(doc["Result"]["Individual data name"])
    result.ind = doc["Result"]["Individual data name"].as<string>();

  if(doc["Gp"]){
    gp.flag = true;

    if(doc["Gp"]["Check"])
      gp.check = doc["Gp"]["Check"].as<bool>();
    if(doc["Gp"]["Sampling time"])
      gp.st = doc["Gp"]["Sampling time"].as<int>();
    if(doc["Gp"]["Start time offset"])
      gp.tstart = doc["Gp"]["Start time offset"].as<double>();
  }

  if(doc["Tex"]){
    tex.flag = true;

    if(doc["Tex"]["Title"])
      tex.title = doc["Tex"]["Title"].as<string>();

    if(doc["Tex"]["Layout"])
      doc_layout = doc["Tex"]["Layout"];
  }

  // gif config
  if(doc["Gif"]){
    gif.flag = true;

    if(doc["Gif"]["Sampling time"])
      gif.st = doc["Gif"]["Sampling time"].as<int>();
    if(doc["Gif"]["Link color"])
      gif.linkColor = doc["Gif"]["Link color"].as<string>();
    if(doc["Gif"]["Joint color"])
      gif.jointColor = doc["Gif"]["Joint color"].as<string>();
    if(doc["Gif"]["Out"]["Terminal"])
      gif.terminal = doc["Gif"]["Out"]["Terminal"].as<bool>();
    if(doc["Gif"]["Out"]["Dir"])
      gif.dir = doc["Gif"]["Out"]["Dir"].as<bool>();

    if(doc["Gif"]["Plane"]["y-z"]){
      gif.yz.flag = true;

      if(doc["Gif"]["Plane"]["y-z"]["x min"])
        gif.yz.xMin = doc["Gif"]["Plane"]["y-z"]["x min"].as<string>();
      if(doc["Gif"]["Plane"]["y-z"]["x max"])
        gif.yz.xMax = doc["Gif"]["Plane"]["y-z"]["x max"].as<string>();
      if(doc["Gif"]["Plane"]["y-z"]["y min"])
        gif.yz.yMin = doc["Gif"]["Plane"]["y-z"]["y min"].as<string>();
      if(doc["Gif"]["Plane"]["y-z"]["y max"])
        gif.yz.yMax = doc["Gif"]["Plane"]["y-z"]["y max"].as<string>();
    }

    if(doc["Gif"]["Plane"]["x-z"]){
      gif.xz.flag = true;

      if(doc["Gif"]["Plane"]["x-z"]["x min"])
        gif.xz.xMin = doc["Gif"]["Plane"]["x-z"]["x min"].as<string>();
      if(doc["Gif"]["Plane"]["x-z"]["x max"])
        gif.xz.xMax = doc["Gif"]["Plane"]["x-z"]["x max"].as<string>();
      if(doc["Gif"]["Plane"]["x-z"]["y min"])
        gif.xz.yMin = doc["Gif"]["Plane"]["x-z"]["y min"].as<string>();
      if(doc["Gif"]["Plane"]["x-z"]["y max"])
        gif.xz.yMax = doc["Gif"]["Plane"]["x-z"]["y max"].as<string>();
    }

    if(doc["Gif"]["Plane"]["x-y"]){
      gif.xy.flag = true;

      if(doc["Gif"]["Plane"]["x-y"]["x min"])
        gif.xy.xMin = doc["Gif"]["Plane"]["x-y"]["x min"].as<string>();
      if(doc["Gif"]["Plane"]["x-y"]["x max"])
        gif.xy.xMax = doc["Gif"]["Plane"]["x-y"]["x max"].as<string>();
      if(doc["Gif"]["Plane"]["x-y"]["y min"])
        gif.xy.yMin = doc["Gif"]["Plane"]["x-y"]["y min"].as<string>();
      if(doc["Gif"]["Plane"]["x-y"]["y max"])
        gif.xy.yMax = doc["Gif"]["Plane"]["x-y"]["y max"].as<string>();
    }

    if(doc["Gif"]["Plane"]["3D"]){
      gif.all.flag = true;

      if(doc["Gif"]["Plane"]["3D"]["x min"])
        gif.all.xMin = doc["Gif"]["Plane"]["3D"]["x min"].as<string>();
      if(doc["Gif"]["Plane"]["3D"]["x max"])
        gif.all.xMax = doc["Gif"]["Plane"]["3D"]["x max"].as<string>();
      if(doc["Gif"]["Plane"]["3D"]["y min"])
        gif.all.yMin = doc["Gif"]["Plane"]["3D"]["y min"].as<string>();
      if(doc["Gif"]["Plane"]["3D"]["y max"])
        gif.all.yMax = doc["Gif"]["Plane"]["3D"]["y max"].as<string>();
      if(doc["Gif"]["Plane"]["3D"]["z min"])
        gif.all.zMin = doc["Gif"]["Plane"]["3D"]["z min"].as<string>();
      if(doc["Gif"]["Plane"]["3D"]["z max"])
        gif.all.zMax = doc["Gif"]["Plane"]["3D"]["z max"].as<string>();
    }
  }

  if(doc["Choreonoid"]){
    cho.flag = true;

    if(doc["Choreonoid"]["Sampling time"])
      cho.st = doc["Choreonoid"]["Sampling time"].as<int>();
  }
}
