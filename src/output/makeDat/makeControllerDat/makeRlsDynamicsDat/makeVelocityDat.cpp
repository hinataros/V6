#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeVelocityDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  path = config.link + "data/dat/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/controller/";

  string path_temp;
  string name;

  string load;

  // desired base position
  name = "000_basePosDes";
  path_temp = path + name + ".dat";

  ofstream basePos(path_temp.c_str());
  if(!basePos)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      basePos << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].rBDes.transpose() << endl;
    basePos.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base pos. [mm]","K",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  // desired base orientation
  name = "001_baseOrientDes";
  path_temp = path + name + ".dat";
  ofstream baseOrient(path_temp.c_str());
  if(!baseOrient)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseOrient << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].xiBDes.transpose() << endl;
    baseOrient.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base orient. [deg]","RAD2DEG",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  // desired base velocity
  name = "002_baseVelDes";
  path_temp = path + name + ".dat";
  ofstream baseVel(path_temp.c_str());
  if(!baseVel)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].vBDes.transpose() << endl;
    baseVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base vel. [m/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  // desired base angular velocity
  name = "003_baseAngVelDes";
  path_temp = path + name + ".dat";
  ofstream baseAngVel(path_temp.c_str());
  if(!baseAngVel)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseAngVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].wBDes.transpose() << endl;
    baseAngVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Desired base ang. vel. [rad/s]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  // desired end effector position
  for(int l=1; l<info.value.node; l++){
    name = "020_eePosDesLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eePos(path_temp.c_str());
    if(!eePos)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eePos << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.vc[i].cal_XDes.segment(6*(l-1), 3).transpose() << endl;

      eePos.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE pos. [mm]","K",20);
      load += "load 'controller/"+name+".gp'\n";
    }
  }

  // desired end effector orientation
  for(int l=1; l<info.value.node; l++){
    name = "021_eeOrientDesLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eeOrient(path_temp.c_str());
    if(!eeOrient)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeOrient << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.vc[i].cal_XDes.segment(6*(l-1)+3, 3).transpose() << endl;

      eeOrient.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE orient. [deg]","RAD2DEG",20);
      load += "load 'controller/"+name+".gp'\n";
    }
  }

  // desired end effector velocity
  for(int l=1; l<info.value.node; l++){
    name = "022_eeVelDesLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eeVel(path_temp.c_str());
    if(!eeVel)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeVel << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.vc[i].cal_VDes.segment(6*(l-1), 3).transpose() << endl;

      eeVel.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE vel. [m/s]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
  }

  // desired end effector angular velocity
  for(int l=1; l<info.value.node; l++){
    name = "023_eeAngVelDesLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eeAngVel(path_temp.c_str());
    if(!eeAngVel)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeAngVel << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.vc[i].cal_VDes.segment(6*(l-1)+3, 3).transpose() << endl;

      eeAngVel.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "controller", name, "Limb"+to_string(l)+" desired EE ang. vel. [rad/s]","E",20);
      load += "load 'controller/"+name+".gp'\n";
    }
  }

  // base position error
  name = "030_basePosErr";
  path_temp = path + name + ".dat";
  ofstream basePosErr(path_temp.c_str());
  if(!basePosErr)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      basePosErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].erB.transpose() << endl;
    basePosErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Base pos. err. [mm]","K",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  // base orientation error
  name = "031_baseOrientErr";
  path_temp = path + name + ".dat";
  ofstream baseOrientErr(path_temp.c_str());
  if(!baseOrientErr)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseOrientErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].eoB.transpose() << endl;
    baseOrientErr.close();
  }

  if(config.graph.gp){
    // smiyahara: eoの単位要検討
    makeGpTime3D(config, "controller", name, "Base orient. err. [rad]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  // com position error
  name = "034_comPosErr";
  path_temp = path + name + ".dat";
  ofstream comPosErr(path_temp.c_str());
  if(!comPosErr)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      comPosErr << setprecision(9) << scientific <<
  	data.t[i] << " " << data.vc[i].erC.transpose() << endl;
    comPosErr.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "CoM pos. err. [mm]","K",0);
    load += "load 'controller/"+name+".gp'\n";
  }

  string pathGp = config.link + "data/gp/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/controller.gp";

  ofstream rlsVelocityGp(pathGp.c_str());
  if(!rlsVelocityGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    rlsVelocityGp << load << endl;
    rlsVelocityGp.close();
  }
}
