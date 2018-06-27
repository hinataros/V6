/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::indexPrint(Config &config, Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(config.flag.debug) DEBUG;

  reset();
  setFileName("indexPrint");
  makeDat("index print");

  string reset = "reset\n";
  string set = "set term gif font 'Times' 45 animate delay 1 optimize size 1280, 1024\n";

  string macro =
    "DIR_DAT = '"+config.dir.dat.ind+"'\n"
    "DIR_GIF = '"+config.dir.gif.ind+"'\n"
    "M = 1e+3\n"
    "PS = 2";

  string output = "set output DIR_GIF.'"+file_name+".gif'\n";

  string key = "set key outside right top\n";

  string add =
    "set xtics 160\n"
    "set size ratio "+to_string(390./140)+"\n"
    "set xrange[70:-70]\n"
    "set yrange[-30:360]\n";

  // smiyahara: config.gp.stではなくconfig.gif.stにしたい
  // smiyahara: ほかはevery使っているから統一感がない
  string start = "start = "+to_string(static_cast<int>(config.gp.tstart/(config.gp.st*info.sim.dt)))+"\n";
  string end = "end = "+to_string(static_cast<int>(info.sim.n/config.gp.st))+"\n";

  string plot =
    "do for [i = start:end]{\n"
    // smiyahara: config.gp.stではなくconfig.gif.stにしたい
    "\tset title sprintf('t = %5.3f', i*"+to_string(config.gp.st*info.sim.dt)+")\n\n"
    "\tplot\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($2*M):($1*M) notitle w l lw 3 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($4*M):($3*M) notitle w l lw 3 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($6*M):($5*M) notitle w l lw 2 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($8*M):($7*M) notitle w l lw 2 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($10*M):($9*M) t 'gCoM' w p pt 7 ps PS lc rgb 'red',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($12*M):($11*M) t 'netCoP' w p pt 5 ps PS lc rgb 'green',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($14*M):($13*M) t 'xCoM' w p pt 13 ps PS lc rgb 'blue'\n"
    "}\n";

  ofstream indexPrint((config.dir.gp.ind+"src/"+file_name+".gp").c_str());
  if(!indexPrint)
    cout << config.dir.gp.ind+"src/"+file_name+".gp" << ": " << endl << "file open error..." << endl;
  else{
    indexPrint <<
      reset << endl <<
      set << endl <<
      macro << endl <<
      output << endl <<
      key << endl <<
      add << endl <<
      start << endl <<
      end << endl <<
      plot << endl;
    indexPrint.close();
  }
}
