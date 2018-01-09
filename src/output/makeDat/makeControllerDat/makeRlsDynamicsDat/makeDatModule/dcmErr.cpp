/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::dcmErr(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // com position error
  name = "034_dcmErr";
  ofstream dcmErr((dir+name+".dat").c_str());
  if(!dcmErr)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      dcmErr << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].eX.transpose() << endl;
    dcmErr.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "DCM err. [mm]","K", 3,
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
