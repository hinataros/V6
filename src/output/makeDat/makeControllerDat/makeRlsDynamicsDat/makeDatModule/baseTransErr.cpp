/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::basePosErr(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // base position error
  name = "030_basePosErr";
  ofstream basePosErr((dir+name+".dat").c_str());
  if(!basePosErr)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      basePosErr << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].erB.transpose() << endl;
    basePosErr.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Base pos. err. [mm]","K", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
string RLS::Output::baseVelErr(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = basePosErr(config, info, dir, load);

  // base velocity error
  name = "032_baseVelErr";
  ofstream baseVelErr((dir+name+".dat").c_str());
  if(!baseVelErr)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      baseVelErr << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].evB.transpose() << endl;
    baseVelErr.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "Base vel. err. [m/s]","E", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
