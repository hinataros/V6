#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::comPosErr(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // com position error
  name = "034_comPosErr";
  ofstream comPosErr((dir+name+".dat").c_str());
  if(!comPosErr)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      comPosErr << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].erC.transpose() << endl;
    comPosErr.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name, "CoM pos. err. [mm]","K", 3, 0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
string RLS::Output::comVelErr(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = comPosErr(config, info, dir, load);

  // com velocity error
  name = "034_comVelErr";
  ofstream comVelErr((dir+name+".dat").c_str());
  if(!comVelErr)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      comVelErr << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].evC.transpose() << endl;
    comVelErr.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name, "CoM vel. err. [m/s]","E", 3, 0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
