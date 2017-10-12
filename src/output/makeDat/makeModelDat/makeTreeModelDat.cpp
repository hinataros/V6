#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeTreeModelDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  path = config.link + "data/dat/" + config.name + "/" + config.controller.name + ":" + config.model.name + "/model/";

  string path_temp;
  string name;

  string load;

  // base position
  name = "000_basePos";
  path_temp = path + name + ".dat";
  ofstream basePos(path_temp.c_str());
  if(!basePos)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      basePos << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].rB.transpose() << endl;
    basePos.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "Base pos. [mm]","K",0);
    load += "load 'model/"+name+".gp'\n";
  }

  // base orientation
  name = "001_baseOrient";
  path_temp = path + name + ".dat";
  ofstream baseOrient(path_temp.c_str());
  if(!baseOrient)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseOrient << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].xiB.transpose() << endl;
    baseOrient.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "Base orient. [deg]","RAD2DEG",1);
    load += "load 'model/"+name+".gp'\n";
  }

  // base velocity
  name = "002_baseVel";
  path_temp = path + name + ".dat";
  ofstream baseVel(path_temp.c_str());
  if(!baseVel)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].vB.transpose() << endl;
    baseVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "Base vel. [m/s]","E",2);
    load += "load 'model/"+name+".gp'\n";
  }

  // base angular velocity
  name = "003_baseAngVel";
  path_temp = path + name + ".dat";
  ofstream baseAngVel(path_temp.c_str());
  if(!baseAngVel)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      baseAngVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].wB.transpose() << endl;
    baseAngVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "Base ang. vel. [rad/s]","E",3);
    load += "load 'model/"+name+".gp'\n";
  }

  // joint angle
  name = "010_jointAng";
  path_temp = path + name + ".dat";
  ofstream jointAng(path_temp.c_str());
  if(!jointAng)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      jointAng << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].th.transpose() << endl;
    jointAng.close();
  }

  if(config.graph.gp){
    makeGpTimeLimb(config, info, "model", name, "joint ang. [deg]","RAD2DEG", 10);
    load += "load 'model/"+name+".gp'\n";
  }

  // joint velocity
  name = "011_jointVel";
  path_temp = path + name + ".dat";
  ofstream jointVel(path_temp.c_str());
  if(!jointVel)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      jointVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].dth.transpose() << endl;
    jointVel.close();
  }

  if(config.graph.gp){
    makeGpTimeLimb(config, info, "model", name, "joint vel. [rad/s]","E", 15);
    load += "load 'model/"+name+".gp'\n";
  }

  // end effector position
  for(int l=1; l<info.value.node; l++){
    name = "020_eePosLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eePos(path_temp.c_str());
    if(!eePos)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eePos << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.tm[i].eePosMatrix.col(l-1).transpose() << endl;

      eePos.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "model", name, "Limb"+to_string(l)+" EE pos. [mm]","K",20);
      load += "load 'model/"+name+".gp'\n";
    }
  }

  // end effector orientation
  for(int l=1; l<info.value.node; l++){
    name = "021_eeOrientLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eeOrient(path_temp.c_str());
    if(!eeOrient)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeOrient << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.tm[i].eeOrientMatrix.col(l-1).transpose() << endl;

      eeOrient.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "model", name, "Limb"+to_string(l)+" EE orient. [deg]","RAD2DEG",21);
      load += "load 'model/"+name+".gp'\n";
    }
  }

  // end effector velocity
  for(int l=1; l<info.value.node; l++){
    name = "022_eeVelLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eeVel(path_temp.c_str());
    if(!eeVel)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeVel << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.tm[i].eeVelMatrix.col(l-1).transpose() << endl;

      eeVel.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "model", name, "Limb"+to_string(l)+" EE vel. [m/s]","E",22);
      load += "load 'model/"+name+".gp'\n";
    }
  }

  // end effector angular velocity
  for(int l=1; l<info.value.node; l++){
    name = "023_eeAngVelLimb"+to_string(l);
    path_temp = path + name + ".dat";
    ofstream eeAngVel(path_temp.c_str());
    if(!eeAngVel)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
  	eeAngVel << setprecision(9) << scientific <<
  	  data.t[i] << " " << data.tm[i].eeAngVelMatrix.col(l-1).transpose() << endl;

      eeAngVel.close();
    }

    if(config.graph.gp){
      makeGpTime3D(config, "model", name, "Limb"+to_string(l)+" EE ang. vel. [rad/s]","E",23);
      load += "load 'model/"+name+".gp'\n";
    }
  }

  // CoM position
  name = "030_comPos";
  path_temp = path + name + ".dat";
  ofstream comPos(path_temp.c_str());
  if(!comPos)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      comPos << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].rC.transpose() << endl;
    comPos.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "CoM pos. [mm]","K",0);
    load += "load 'model/"+name+".gp'\n";
  }

  // com velocity
  name = "031_comVel";
  path_temp = path + name + ".dat";
  ofstream comVel(path_temp.c_str());
  if(!comVel)
    cout << path_temp << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n+1; i+=config.graph.st)
      comVel << setprecision(9) << scientific <<
  	data.t[i] << " " << data.tm[i].vC.transpose() << endl;
    comVel.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "model", name, "CoM vel. [m/s]","E",2);
    load += "load 'model/"+name+".gp'\n";
  }

  string pathGp = config.link + "data/gp/" + config.name + "/" + config.controller.name + ":" + config.model.name + "/model.gp";
  ofstream modelGp(pathGp.c_str());
  if(!modelGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    modelGp << load << endl;
    modelGp.close();
  }
}
