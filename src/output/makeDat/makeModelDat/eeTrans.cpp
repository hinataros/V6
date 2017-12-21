#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeTrans(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector position
  for(int l=1; l<info.value.node; l++){
    name = "020_eePosLimb"+to_string(l);
    ofstream eePos((dir+name+".dat").c_str());
    if(!eePos)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
        eePos << setprecision(9) << scientific <<
          data.t[i] << " " << data.tm[i].eePosMatrix.col(l-1).transpose() << endl;

      eePos.close();
    }

    if(config.graph.gp){
      makeGp(config, "model", name, l, "EE pos. [mm]","K", 3, 20);
      load += "load 'model/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "model", "1.0", name);
    }
  }

  // end effector velocity
  for(int l=1; l<info.value.node; l++){
    name = "022_eeVelLimb"+to_string(l);
    ofstream eeVel((dir+name+".dat").c_str());
    if(!eeVel)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
        eeVel << setprecision(9) << scientific <<
          data.t[i] << " " << data.tm[i].eeVelMatrix.col(l-1).transpose() << endl;

      eeVel.close();
    }

    if(config.graph.gp){
      makeGp(config, "model", name, l, "EE vel. [m/s]","E", 3, 22);
      load += "load 'model/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "model", "1.0", name);
    }
  }

  return minipage;
}
