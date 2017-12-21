#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::jointTorque(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // joint torque
  name = "032_jointTorque";
  ofstream jointTorque((dir+name+".dat").c_str());
  if(!jointTorque)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      jointTorque << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].tau.transpose() << endl;
    jointTorque.close();
  }

  if(config.graph.gp){
    makeGpTimeLimb(config, info, "controller", name, "Joint torque [Nm]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipageLimb(config, info, "controller", "1.0", name);
  }

  return minipage;
}
