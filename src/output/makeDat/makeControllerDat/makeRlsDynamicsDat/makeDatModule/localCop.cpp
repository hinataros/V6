/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::localCop(Config &config, Info &info, string dir, string &load)
{
  string name;
  string minipage;

  name = "051_LxlocalCopTimeRel";
  ofstream LxlocalCop((dir+name+".dat").c_str());
  if(!LxlocalCop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      LxlocalCop << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].rpk(2) << endl;
    LxlocalCop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "L. xCoP [mm]","K", 1,
           "set yrange[-60:80]\n"
           "set object 1 rect from 0, -40 to 1e+3, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  name = "051_LylocalCopTimeRel";
  ofstream LylocalCop((dir+name+".dat").c_str());
  if(!LylocalCop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      LylocalCop << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].rpk(3) << endl;
    LylocalCop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "L. yCoP [mm]","K", 1,
           "set yrange[0:80]\n"
           "set object 1 rect from 0, (39-31.5) to 1e+3, (39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // ***************************************************************************************************************
  name = "051_RxlocalCopTimeRel";
  ofstream RxlocalCop((dir+name+".dat").c_str());
  if(!RxlocalCop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      RxlocalCop << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].rpk(0) << endl;
    RxlocalCop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "R. xCoP [mm]","K", 1,
           "set yrange[-60:80]\n"
           "set object 1 rect from 0, -40 to 1e+3, 58 behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // ***************************************************************************************************************
  name = "051_RylocalCopTimeRel";
  ofstream RylocalCop((dir+name+".dat").c_str());
  if(!RylocalCop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      RylocalCop << setprecision(9) << scientific <<
        data.t[i] << " " << data.dc[i].rpk(1) << endl;
    RylocalCop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "R. yCoP [mm]","K", 1,
           "set yrange[-80:0]\n"
           "set object 2 rect from 0, (-39-31.5) to 1e+3, (-39+31.5) behind lw 0 fc rgb 'cyan' fill solid 0.2 noborder\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // ***************************************************************************************************************
  name = "051_LlocalCopTimeRel";
  ofstream LlocalCop((dir+name+".dat").c_str());
  if(!LlocalCop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      LlocalCop << setprecision(9) << scientific <<
        data.dc[i].rpk(3) << " " << data.dc[i].rpk(2) << endl;
    LlocalCop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "L. yCoP [mm]", "L. xCoP [mm]","K", 1,
           "set xtics 40\n"
           "set parametric\n"
           "set size ratio 2\n"
           "set xrange[80:0]\n"
           "set yrange[-80:80]\n"
           "INIT_LX = 0.0\n"
           "INIT_LY = 39.00\n"
           "PMAX_X  = 58.0\n"
           "PMIN_X  =-40.0\n"
           "PMAX_Y  = 31.5\n"
           "PMIN_Y  =-31.5\n"
           "set arrow 5 from INIT_LY+PMIN_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMIN_X nohead lw 2\n"
           "set arrow 6 from INIT_LY+PMAX_Y, INIT_LX+PMIN_X to INIT_LY+PMAX_Y, INIT_LX+PMAX_X nohead lw 2\n"
           "set arrow 7 from INIT_LY+PMAX_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMAX_X nohead lw 1\n"
           "set arrow 8 from INIT_LY+PMIN_Y, INIT_LX+PMAX_X to INIT_LY+PMIN_Y, INIT_LX+PMIN_X nohead lw 1\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // ***************************************************************************************************************
  name = "051_RlocalCopTimeRel";
  ofstream RlocalCop((dir+name+".dat").c_str());
  if(!RlocalCop)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      RlocalCop << setprecision(9) << scientific <<
        data.dc[i].rpk(1) << " " << data.dc[i].rpk(0) << endl;
    RlocalCop.close();
  }

  if(config.graph.gp){
    makeGp(config, "controller", name,
           "R. yCoP [mm]", "R. xCoP [mm]","K", 1,
           "set xtics 40\n"
           "set parametric\n"
           "set size ratio 2\n"
           "set xrange[0:-80]\n"
           "set yrange[-80:80]\n"
           "INIT_RX = 0.0\n"
           "INIT_RY =-39.00\n"
           "PMAX_X  = 58.0\n"
           "PMIN_X  =-40.0\n"
           "PMAX_Y  = 31.5\n"
           "PMIN_Y  =-31.5\n"
           "set arrow 1 from INIT_RY+PMIN_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMIN_X nohead lw 1\n"
           "set arrow 2 from INIT_RY+PMAX_Y, INIT_RX+PMIN_X to INIT_RY+PMAX_Y, INIT_RX+PMAX_X nohead lw 1\n"
           "set arrow 3 from INIT_RY+PMAX_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMAX_X nohead lw 2\n"
           "set arrow 4 from INIT_RY+PMIN_Y, INIT_RX+PMAX_X to INIT_RY+PMIN_Y, INIT_RX+PMIN_X nohead lw 2\n",
           0);
    load += "load '"+config.dir.gp.ind+"controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
