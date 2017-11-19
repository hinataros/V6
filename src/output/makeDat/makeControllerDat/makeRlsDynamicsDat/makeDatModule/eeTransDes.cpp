#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eePosDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // desired end effector position
  for(int l=1; l<info.value.node; l++){
    name = "020_eePosDesLimb"+to_string(l);
    ofstream eePosDes((dir+name+".dat").c_str());
    if(!eePosDes)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eePosDes << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_XDes.segment(6*(l-1), 3).transpose() << endl;

      eePosDes.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE pos. [mm]","K",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
string RLS::Output::eeVelDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  minipage = eePosDes(config, info, dir, load);

  // desired end effector velocity
  for(int l=1; l<info.value.node; l++){
    name = "022_eeVelDesLimb"+to_string(l);
    ofstream eeVelDes((dir+name+".dat").c_str());
    if(!eeVelDes)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eeVelDes << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_VDes.segment(6*(l-1), 3).transpose() << endl;

      eeVelDes.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE vel. [m/s]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
string RLS::Output::eeAccDes(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = eeVelDes(config, info, dir, load);

  // desired end effector acceleration
  for(int l=1; l<info.value.node; l++){
    name = "024_eeAccDesLimb"+to_string(l);
    ofstream eeAccDes((dir+name+".dat").c_str());
    if(!eeAccDes)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eeAccDes << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_dVDes.segment(6*(l-1), 3).transpose() << endl;

      eeAccDes.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE acc. [m/s^2]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
