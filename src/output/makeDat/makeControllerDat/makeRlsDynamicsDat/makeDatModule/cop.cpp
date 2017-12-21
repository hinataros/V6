 #include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::cop(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // com position error
  name = "050_copTimeRel";
  ofstream cop((dir+name+".dat").c_str());
  if(!cop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      cop << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].rp.transpose() << endl;
    cop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name, "CoP [mm]","K", 2, 0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
