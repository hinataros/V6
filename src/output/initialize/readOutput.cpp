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

  string resultKeyName = "result";
  string gpKeyName = "gp";
  string texKeyName = "tex";
  string gifKeyName = "gif";
  string choreonoidKeyName = "choreonoid";

  struct stat statFile;
  if(stat(path_yaml_output.c_str(), &statFile)!=0)
    cout << manip_error("Output::readOutput() error...") << endl
         << manip_error("no such file '"+path_yaml_output+"'") << endl;

  YAML::Node doc = YAML::LoadFile(path_yaml_output.c_str());

  if(doc[resultKeyName]["composite data name"])
    result.cmp = doc[resultKeyName]["composite data name"].as<string>();
  if(doc[resultKeyName]["individual data name"])
    result.ind = doc[resultKeyName]["individual data name"].as<string>();

  if(doc[gpKeyName]){
    gp.flag = true;

    if(doc[gpKeyName]["check"])
      gp.check = doc[gpKeyName]["check"].as<bool>();
    if(doc[gpKeyName]["sampling time"])
      gp.st = doc[gpKeyName]["sampling time"].as<int>();
    if(doc[gpKeyName]["start time offset"])
      gp.tstart = doc[gpKeyName]["start time offset"].as<double>();
  }

  if(doc[texKeyName]){
    tex.flag = true;

    if(doc[texKeyName]["title"])
      tex.title = doc[texKeyName]["title"].as<string>();

    if(doc[texKeyName]["layout"])
      doc_layout = doc[texKeyName]["layout"];
  }

  // gif config
  if(doc[gifKeyName]){
    gif.flag = true;

    if(doc[gifKeyName]["sampling time"])
      gif.st = doc[gifKeyName]["sampling time"].as<int>();
    if(doc[gifKeyName]["link color"])
      gif.linkColor = doc[gifKeyName]["link color"].as<string>();
    if(doc[gifKeyName]["joint color"])
      gif.jointColor = doc[gifKeyName]["joint color"].as<string>();
    if(doc[gifKeyName]["out"]["terminal"])
      gif.terminal = doc[gifKeyName]["out"]["terminal"].as<bool>();
    if(doc[gifKeyName]["out"]["dir"])
      gif.dir = doc[gifKeyName]["out"]["dir"].as<bool>();

    if(doc[gifKeyName]["plane"]["y-z"]){
      gif.yz.flag = true;

      if(doc[gifKeyName]["plane"]["y-z"]["x min"])
        gif.yz.xMin = doc[gifKeyName]["plane"]["y-z"]["x min"].as<string>();
      if(doc[gifKeyName]["plane"]["y-z"]["x max"])
        gif.yz.xMax = doc[gifKeyName]["plane"]["y-z"]["x max"].as<string>();
      if(doc[gifKeyName]["plane"]["y-z"]["y min"])
        gif.yz.yMin = doc[gifKeyName]["plane"]["y-z"]["y min"].as<string>();
      if(doc[gifKeyName]["plane"]["y-z"]["y max"])
        gif.yz.yMax = doc[gifKeyName]["plane"]["y-z"]["y max"].as<string>();
    }

    if(doc[gifKeyName]["plane"]["x-z"]){
      gif.xz.flag = true;

      if(doc[gifKeyName]["plane"]["x-z"]["x min"])
        gif.xz.xMin = doc[gifKeyName]["plane"]["x-z"]["x min"].as<string>();
      if(doc[gifKeyName]["plane"]["x-z"]["x max"])
        gif.xz.xMax = doc[gifKeyName]["plane"]["x-z"]["x max"].as<string>();
      if(doc[gifKeyName]["plane"]["x-z"]["y min"])
        gif.xz.yMin = doc[gifKeyName]["plane"]["x-z"]["y min"].as<string>();
      if(doc[gifKeyName]["plane"]["x-z"]["y max"])
        gif.xz.yMax = doc[gifKeyName]["plane"]["x-z"]["y max"].as<string>();
    }

    if(doc[gifKeyName]["plane"]["x-y"]){
      gif.xy.flag = true;

      if(doc[gifKeyName]["plane"]["x-y"]["x min"])
        gif.xy.xMin = doc[gifKeyName]["plane"]["x-y"]["x min"].as<string>();
      if(doc[gifKeyName]["plane"]["x-y"]["x max"])
        gif.xy.xMax = doc[gifKeyName]["plane"]["x-y"]["x max"].as<string>();
      if(doc[gifKeyName]["plane"]["x-y"]["y min"])
        gif.xy.yMin = doc[gifKeyName]["plane"]["x-y"]["y min"].as<string>();
      if(doc[gifKeyName]["plane"]["x-y"]["y max"])
        gif.xy.yMax = doc[gifKeyName]["plane"]["x-y"]["y max"].as<string>();
    }

    if(doc[gifKeyName]["plane"]["3D"]){
      gif.all.flag = true;

      if(doc[gifKeyName]["plane"]["3D"]["x min"])
        gif.all.xMin = doc[gifKeyName]["plane"]["3D"]["x min"].as<string>();
      if(doc[gifKeyName]["plane"]["3D"]["x max"])
        gif.all.xMax = doc[gifKeyName]["plane"]["3D"]["x max"].as<string>();
      if(doc[gifKeyName]["plane"]["3D"]["y min"])
        gif.all.yMin = doc[gifKeyName]["plane"]["3D"]["y min"].as<string>();
      if(doc[gifKeyName]["plane"]["3D"]["y max"])
        gif.all.yMax = doc[gifKeyName]["plane"]["3D"]["y max"].as<string>();
      if(doc[gifKeyName]["plane"]["3D"]["z min"])
        gif.all.zMin = doc[gifKeyName]["plane"]["3D"]["z min"].as<string>();
      if(doc[gifKeyName]["plane"]["3D"]["z max"])
        gif.all.zMax = doc[gifKeyName]["plane"]["3D"]["z max"].as<string>();
    }
  }

  if(doc[choreonoidKeyName]){
    cho.flag = true;

    if(doc[choreonoidKeyName]["sampling time"])
      cho.st = doc[choreonoidKeyName]["sampling time"].as<int>();
  }
}
