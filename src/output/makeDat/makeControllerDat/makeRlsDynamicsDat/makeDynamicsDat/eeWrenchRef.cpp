#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeWrenchRef(Config &config, Info &info, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector force reference
  for(int l=1; l<info.value.node; l++){
    name = "033_eeForceRefLimb"+to_string(l);
    ofstream eeForceRef((path+name+".dat").c_str());
    if(!eeForceRef)
      cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeForceRef << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_FBarRef.segment(6*(l-1), 3).transpose() << endl;

      eeForceRef.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" "+"EE force reference. [N]","E",0);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  // end effector moment reference
  for(int l=1; l<info.value.node; l++){
    name = "034_eeMomentRefLimb"+to_string(l);
    ofstream eeMomentRef((path+name+".dat").c_str());
    if(!eeMomentRef)
      cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeMomentRef << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.dc[i].cal_FBarRef.segment(6*(l-1)+3, 3).transpose() << endl;

      eeMomentRef.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" "+"EE moment reference. [Nm]","E",0);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}
