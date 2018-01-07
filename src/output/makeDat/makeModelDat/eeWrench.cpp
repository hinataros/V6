/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeWrench(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector force
  for(int l=1; l<info.value.node; l++){
    name = "031_eeForceLimb"+to_string(l);
    ofstream eeForce((dir+name+".dat").c_str());
    if(!eeForce)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
        eeForce << setprecision(9) << scientific <<
          data.t[i] << " " << data.tm[i].eeForceMatrix.col(l-1).transpose() << endl;

      eeForce.close();
    }

    if(config.graph.gp){
      makeGp(config, "model", name,
             l, "EE force. [N]","E", 3,
             0);
      load += "load '"+config.dir.gp.ind+"model/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "model", "1.0", name);
    }
  }

  // end effector moment
  for(int l=1; l<info.value.node; l++){
    name = "032_eeMomentLimb"+to_string(l);
    ofstream eeMoment((dir+name+".dat").c_str());
    if(!eeMoment)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
        eeMoment << setprecision(9) << scientific <<
          data.t[i] << " " << data.tm[i].eeMomentMatrix.col(l-1).transpose() << endl;

      eeMoment.close();
    }

    if(config.graph.gp){
      makeGp(config, "model", name, l,
             "EE moment. [Nm]","E", 3,
             0);
      load += "load '"+config.dir.gp.ind+"model/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "model", "1.0", name);
    }
  }

  return minipage;
}
