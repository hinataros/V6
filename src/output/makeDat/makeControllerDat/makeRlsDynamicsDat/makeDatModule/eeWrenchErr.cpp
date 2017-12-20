#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeForceErr(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector force reference
  for(int l=1; l<info.value.node; l++){
    name = "033_eeForceErrLimb"+to_string(l);
    ofstream eeForceErr((dir+name+".dat").c_str());
    if(!eeForceErr)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeForceErr << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_FErr.segment(6*(l-1), 3).transpose() << endl;

      eeForceErr.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "EE force err. [N]","E",0);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}

string RLS::Output::eeMomentErr(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector moment reference
  for(int l=1; l<info.value.node; l++){
    name = "034_eeMomentErrLimb"+to_string(l);
    ofstream eeMomentErr((dir+name+".dat").c_str());
    if(!eeMomentErr)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeMomentErr << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_FErr.segment(6*(l-1)+3, 3).transpose() << endl;

      eeMomentErr.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, l, "EE moment err. [Nm]","E",0);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
