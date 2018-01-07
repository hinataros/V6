/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::extForceRef(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  name = "001_extForceRef";
  ofstream extForceRef((dir+name+".dat").c_str());
  if(!extForceRef)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      extForceRef << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].cal_FextRef.head(3).transpose() << endl;
    extForceRef.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "External force ref. [N]","E", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}

string RLS::Output::extMomentRef(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  name = "001_extMomentRef";
  ofstream extMomentRef((dir+name+".dat").c_str());
  if(!extMomentRef)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      extMomentRef << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].cal_FextRef.tail(3).transpose() << endl;
    extMomentRef.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "External moment ref. [N/m]","E", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}

string RLS::Output::extWrenchRef(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = extForceRef(config, info, dir, load);
  minipage += extMomentRef(config, info, dir, load);

  return minipage;
}
