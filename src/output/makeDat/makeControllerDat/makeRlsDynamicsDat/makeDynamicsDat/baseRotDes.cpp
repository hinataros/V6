#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseRotDes(Config &config, Info &info, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // desired base orientation
  name = "001_baseOrientDes";
  ofstream baseOrientDes((path+name+".dat").c_str());
  if(!baseOrientDes)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseOrientDes << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].xiBDes.transpose() << endl;
    baseOrientDes.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base orient. [deg]","RAD2DEG",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // desired base angular velocity
  name = "003_baseAngVelDes";
  ofstream baseAngVelDes((path+name+".dat").c_str());
  if(!baseAngVelDes)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAngVelDes << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].wBDes.transpose() << endl;
    baseAngVelDes.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base ang. vel. [rad/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // desired base anguler acceleration
  name = "005_baseAngAccDes";
  ofstream baseAngAccDes((path+name+".dat").c_str());
  if(!baseAngAccDes)
    cout << path+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAngAccDes << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].dwBDes.transpose() << endl;
    baseAngAccDes.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base ang. acc. [rad/s^2]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
