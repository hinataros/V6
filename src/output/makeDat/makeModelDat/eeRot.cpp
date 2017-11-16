#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeRot(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector orientation
  for(int l=1; l<info.value.node; l++){
    name = "021_eeOrientLimb"+to_string(l);
    ofstream eeOrient((dir+name+".dat").c_str());
    if(!eeOrient)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eeOrient << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.tm[i].eeOrientMatrix.col(l-1).transpose() << endl;

      eeOrient.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "model", name, "Limb"+to_string(l)+" EE orient. [deg]","RAD2DEG",21);
      load += "load 'model/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "model", "1.0", name);
    }
  }

  // end effector angular velocity
  for(int l=1; l<info.value.node; l++){
    name = "023_eeAngVelLimb"+to_string(l);
    ofstream eeAngVel((dir+name+".dat").c_str());
    if(!eeAngVel)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n; i+=config.graph.st)
  	eeAngVel << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.tm[i].eeAngVelMatrix.col(l-1).transpose() << endl;

      eeAngVel.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "model", name, "Limb"+to_string(l)+" EE ang. vel. [rad/s]","E",23);
      load += "load 'model/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "model", "1.0", name);
    }
  }

  return minipage;
}
