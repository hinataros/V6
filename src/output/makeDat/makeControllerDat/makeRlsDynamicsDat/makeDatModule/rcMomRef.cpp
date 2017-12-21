#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::rcMomRef(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // rate of chage of linear mom. reference
  name = "030_rcLinMomRef";
  ofstream rcLinMomRef((dir+name+".dat").c_str());
  if(!rcLinMomRef)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      rcLinMomRef << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].dpRef.transpose() << endl;
    rcLinMomRef.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name, "R. C. linear mom. ref. [N]","E", 3, 0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // rate of chage of angular mom. reference
  name = "031_rcAngMomRef";
  ofstream rcAngMomRef((dir+name+".dat").c_str());
  if(!rcAngMomRef)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      rcAngMomRef << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].dlRef.transpose() << endl;
    rcAngMomRef.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name, "R. C. angular mom. ref. [Nm]","E", 3, 0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
