#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeOrientDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // desired end effector orientation
  for(int l=1; l<info.value.node; l++){
    name = "021_eeOrientDesLimb"+to_string(l);
    ofstream eeOrientDes((dir+name+".dat").c_str());
    if(!eeOrientDes)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeOrientDes << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_XDes.segment(6*(l-1)+3, 3).transpose() << endl;

      eeOrientDes.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "des. EE orient. [deg]","RAD2DEG",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
string RLS::Output::eeAngVelDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  minipage = eeOrientDes(config, info, dir, load);

  // desired end effector angular velocity
  for(int l=1; l<info.value.node; l++){
    name = "023_eeAngVelDesLimb"+to_string(l);
    ofstream eeAngVelDes((dir+name+".dat").c_str());
    if(!eeAngVelDes)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeAngVelDes << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_VDes.segment(6*(l-1)+3, 3).transpose() << endl;

      eeAngVelDes.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "des. EE ang. vel. [rad/s]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
string RLS::Output::eeAngAccDes(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = eeAngVelDes(config, info, dir, load);

  // desired end effector angular acceleration
  for(int l=1; l<info.value.node; l++){
    name = "025_eeAngAccDesLimb"+to_string(l);
    ofstream eeAngAccDes((dir+name+".dat").c_str());
    if(!eeAngAccDes)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeAngAccDes << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_dVDes.segment(6*(l-1)+3, 3).transpose() << endl;

      eeAngAccDes.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "des. EE ang. acc. [rad/s^2]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
