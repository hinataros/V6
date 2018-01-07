/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseOrientDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // desired base orientation
  name = "001_baseOrientDes";
  ofstream baseOrientDes((dir+name+".dat").c_str());
  if(!baseOrientDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseOrientDes << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].xiBDes.transpose() << endl;
    baseOrientDes.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Des. base orient. [deg]","RAD2DEG", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}

string RLS::Output::baseAngVelDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  minipage = baseOrientDes(config, info, dir, load);

  // desired base angular velocity
  name = "002_baseAngVelDes";
  ofstream baseAngVelDes((dir+name+".dat").c_str());
  if(!baseAngVelDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAngVelDes << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].wBDes.transpose() << endl;
    baseAngVelDes.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Des. base ang. vel. [rad/s]","E", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}

string RLS::Output::baseAngAccDes(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = baseAngVelDes(config, info, dir, load);

  // desired base anguler acceleration
  name = "003_baseAngAccDes";
  ofstream baseAngAccDes((dir+name+".dat").c_str());
  if(!baseAngAccDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseAngAccDes << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].dwBDes.transpose() << endl;
    baseAngAccDes.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Des. base ang. acc. [rad/s^2]","E", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
