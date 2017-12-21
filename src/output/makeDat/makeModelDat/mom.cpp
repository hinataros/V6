#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::mom(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // linear momentum
  name = "041_linMom";
  ofstream linMom((dir+name+".dat").c_str());
  if(!linMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      linMom << setprecision(9) << scientific <<
        data.t[i] << " " << data.tm[i].p.transpose() << endl;
    linMom.close();
  }

  if(config.graph.gp){
    makeGp(config, "model", name, "Linear mom. [Ns]","E", 3, 0);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage = makeMinipage(config, "model", "1.0", name);
  }

  // angular momentum
  name = "041_angMom";
  ofstream angMom((dir+name+".dat").c_str());
  if(!angMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      angMom << setprecision(9) << scientific <<
        data.t[i] << " " << data.tm[i].lC.transpose() << endl;
    angMom.close();
  }

  if(config.graph.gp){
    makeGp(config, "model", name, "Angular mom. [Nms]","E", 3, 0);
    load += "load 'model/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "model", "1.0", name);
  }

  return minipage;
}
