/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::dcmPosDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  name = "001_dcmPosDes";
  ofstream dcmPosDes((dir+name+".dat").c_str());
  if(!dcmPosDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      dcmPosDes << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].rXDes.transpose() << endl;
    dcmPosDes.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Des. DCM. [mm]","K", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}

string RLS::Output::dcmVelDes(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  minipage = dcmPosDes(config, info, dir, load);

  name = "002_dcmVelDes";
  ofstream dcmVelDes((dir+name+".dat").c_str());
  if(!dcmVelDes)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      dcmVelDes << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].drXDes.transpose() << endl;
    dcmVelDes.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Des. DCM vel. [m/s]","E", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
