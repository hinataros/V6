/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::footPrint(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  // foot plane
  name = "050_footPrint";
  ofstream cop((dir+name+".dat").c_str());
  if(!cop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      cop << setprecision(9) << scientific <<
        data.dc[i].rXDes(1) << " " << data.dc[i].rXDes(0) << endl;
    cop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "yDCM [mm]", "xDCM [mm]", "K", 1,
           // "set xtics 40\n"
           "set parametric\n"
           // "set size square\n"
           "set xrange[80:-80]\n"
           // "set yrange[-80:80]\n"
           "INIT_RX = 0.0\n"
           "INIT_RY =-39.00\n"
           "INIT_LX = 0.0\n"
           "INIT_LY = 39.00\n"
           "PMAX_X  = 58.0\n"
           "PMIN_X  =-40.0\n"
           "PMAX_Y  = 31.5\n"
           "PMIN_Y  =-31.5\n"
           "set arrow 1 from INIT_RY+PMIN_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMIN_X nohead lw 1\n"
           "set arrow 2 from INIT_RY+PMAX_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 1\n"
           "set arrow 3 from INIT_RY+PMAX_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMAX_X nohead lw 2\n"
           "set arrow 4 from INIT_RY+PMIN_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2\n"
           "set arrow 5 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMIN_X nohead lw 2\n"
           "set arrow 6 from INIT_LY+PMAX_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMAX_X nohead lw 2\n"
           "set arrow 7 from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMAX_X nohead lw 1\n"
           "set arrow 8 from INIT_LY+PMIN_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMIN_X nohead lw 1\n"
           "set arrow 9  from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 2\n"
           "set arrow 10 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
