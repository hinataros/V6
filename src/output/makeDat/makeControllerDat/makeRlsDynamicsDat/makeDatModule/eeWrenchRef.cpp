#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::eeForceRef(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector force reference
  for(int l=1; l<info.value.node; l++){
    name = "033_eeForceRefLimb"+to_string(l);
    ofstream eeForceRef((dir+name+".dat").c_str());
    if(!eeForceRef)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
        eeForceRef << setprecision(9) << scientific <<
          data.t[i] << " " << data.dc[i].cal_FBarRef.segment(6*(l-1), 3).transpose() << endl;

      eeForceRef.close();
    }

    if(config.graph.gp){
      makeGp(config, "controller", name, l, "EE force ref. [N]","E", 3, 0);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}

string RLS::Output::eeMomentRef(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // end effector moment reference
  for(int l=1; l<info.value.node; l++){
    name = "034_eeMomentRefLimb"+to_string(l);
    ofstream eeMomentRef((dir+name+".dat").c_str());
    if(!eeMomentRef)
      cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<info.sim.n+1; i+=config.graph.st)
        eeMomentRef << setprecision(9) << scientific <<
          data.t[i] << " " << data.dc[i].cal_FBarRef.segment(6*(l-1)+3, 3).transpose() << endl;

      eeMomentRef.close();
    }

    if(config.graph.gp){
      makeGp(config, "controller", name, l, "EE moment ref. [Nm]","E", 3, 0);
      load += "load 'controller/"+name+".gp'\n";
    }
    if(config.graph.tex){
      minipage += makeMinipage(config, "controller", "1.0", name);
    }
  }

  return minipage;
}

string RLS::Output::eeWrenchRef(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  minipage = eeForceRef(config, info, dir, load);
  minipage += eeMomentRef(config, info, dir, load);

  return minipage;
}
