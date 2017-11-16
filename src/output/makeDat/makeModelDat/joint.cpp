#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::joint(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // joint angle
  name = "010_jointAng";
  ofstream jointAng((dir+name+".dat").c_str());
  if(!jointAng)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      jointAng << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].th.transpose() << endl;
    jointAng.close();
  }

  if(config.graph.gp){
    makeGpTimeLimb(config, info, "model", name, "joint ang. [deg]","RAD2DEG", 10);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipageLimb(config, info, "model", "1.0", name);
  }

  // joint velocity
  name = "011_jointVel";
  ofstream jointVel((dir+name+".dat").c_str());
  if(!jointVel)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      jointVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].dth.transpose() << endl;
    jointVel.close();
  }

  if(config.graph.gp){
    makeGpTimeLimb(config, info, "model", name, "joint vel. [rad/s]","E", 15);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipageLimb(config, info, "model", "1.0", name);
  }

  return minipage;
}
