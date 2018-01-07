/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::baseTrans(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // base position
  name = "000_basePos";
  ofstream basePos((dir+name+".dat").c_str());
  if(!basePos)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      basePos << setprecision(9) << scientific <<
        data.t[i] << " " << data.tm[i].rB.transpose() << endl;
    basePos.close();
  }

  if(config.graph.gp){
    makeGp(config, "model", name,
           "Base pos. [mm]","K", 3,
           0);
    load += "load '"+config.dir.gp.ind+"model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  // base velocity
  name = "002_baseVel";
  ofstream baseVel((dir+name+".dat").c_str());
  if(!baseVel)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseVel << setprecision(9) << scientific <<
        data.t[i] << " " << data.tm[i].vB.transpose() << endl;
    baseVel.close();
  }

  if(config.graph.gp){
    makeGp(config, "model", name,
           "Base vel. [m/s]","E", 3,
           2);
    load += "load '"+config.dir.gp.ind+"model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  return minipage;
}
