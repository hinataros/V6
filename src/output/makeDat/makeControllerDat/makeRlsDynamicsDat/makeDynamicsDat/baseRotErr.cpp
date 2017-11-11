#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseRotErr(Config &config, Info &info, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // base orientation error
  name = "031_baseOrientErr";
  ofstream baseOrientErr((path+name+".dat").c_str());
  if(!baseOrientErr)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseOrientErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].eoB.transpose() << endl;
    baseOrientErr.close();
  }

  if(config.graph.gp){
    // smiyahara: eoの単位要検討
    makeGpTime3D(config, "controller", name, "Base orient. err. [rad]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // base angular velocity error
  name = "033_baseAngVelErr";
  ofstream baseAngVelErr((path+name+".dat").c_str());
  if(!baseAngVelErr)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAngVelErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].ewB.transpose() << endl;
    baseAngVelErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Base ang. vel. err. [rad/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
