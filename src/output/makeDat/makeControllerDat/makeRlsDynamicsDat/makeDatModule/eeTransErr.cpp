#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eePosErr(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // end effector position error
  for(int l=1; l<info.value.node; l++){
    name = "020_eePosErrLimb"+to_string(l);
    ofstream eePosErr((dir+name+".dat").c_str());
    if(!eePosErr)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eePosErr << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_Ep.segment(6*(l-1), 3).transpose() << endl;

      eePosErr.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "EE pos. err. [mm]","K",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}

string RLS::Output::eeVelErr(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  minipage = eePosErr(config, info, dir, load);

  // end effector velocity error
  for(int l=1; l<info.value.node; l++){
    name = "022_eeVelErrLimb"+to_string(l);
    ofstream eeVelErr((dir+name+".dat").c_str());
    if(!eeVelErr)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eeVelErr << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_Ev.segment(6*(l-1), 3).transpose() << endl;

      eeVelErr.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "EE vel. err. [m/s]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
