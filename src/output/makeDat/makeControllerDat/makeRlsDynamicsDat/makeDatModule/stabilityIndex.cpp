/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::stabilityIndex(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  name = "050_xStabilityIndex";
  ofstream xStabilityIndex((dir+name+".dat").c_str());
  if(!xStabilityIndex)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      xStabilityIndex << setprecision(9) << scientific <<
        data.t[i] << " " << data.tm[i].rC(0) << " " << data.dc[i].rp(0) << " " << data.dc[i].rX(0) << endl;
    xStabilityIndex.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "x stability index [mm]","K", 3,
           "set yrange[-60:80]\n"
           "set object 1 rect from 0, -40 to 1e+3, 58 behind lw 0 fc rgb 'magenta' fill solid 0.2 noborder\n"
           "set object 2 rect from 0, -32 to 1e+3, 50 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n"
           "set arrow 1 from 2, -60 to 2, 80 nohead dt (10, 5)\n"
           "set arrow 2 from 12, -60 to 12, 80 nohead dt (10, 5)\n",
           // "set arrow 1 from 4.962, -60 to 4.962, 80 nohead dt (10, 5)\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  name = "050_yStabilityIndex";
  ofstream yStabilityIndex((dir+name+".dat").c_str());
  if(!yStabilityIndex)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      yStabilityIndex << setprecision(9) << scientific <<
        data.t[i] << " " << data.tm[i].rC(1) << " " << data.dc[i].rp(1) << " " << data.dc[i].rX(1) << endl;
    yStabilityIndex.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "y stability index [mm]","K", 3,
           "set yrange[-80:80]\n"
           "set object 1 rect from 0, (39-31.5) to 1e+3, (39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n"
           "set object 2 rect from 0, (-39-31.5) to 1e+3, (-39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  name = "050_stabilityIndex";
  ofstream stabilityIndex((dir+name+".dat").c_str());
  if(!stabilityIndex)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      stabilityIndex << setprecision(9) << scientific <<
        data.tm[i].rC(1) << " " << data.tm[i].rC(0) << " " <<
        data.dc[i].rp(1) << " " << data.dc[i].rp(0) << " " <<
        data.dc[i].rX(1) << " " << data.dc[i].rX(0) << endl;
    stabilityIndex.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "y stability index [mm]", "x stability index [mm]", "K", 3,
           "set xtics 40\n"
           "set parametric\n"
           "set size square\n"
           "set xrange[80:-80]\n"
           "set yrange[-80:80]\n"
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
