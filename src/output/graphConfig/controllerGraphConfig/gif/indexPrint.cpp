/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::indexPrint(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

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

  // string key = "set key outside bottom\n";
  // string key = "set key at graph 0.5,-0.5 center bottom horizontal reverse Left\n";
  string key = "set key at graph 0.5,-1.0 center bottom horizontal reverse Left\n";

  string add =
    "set ytics 40\n"
    "set size ratio "+to_string(140./780)+"\n"
    "set xrange[-30:750]\n"
    "set yrange[-70:70]\n";

  // smiyahara: config.gp.stではなくconfig.gif.stにしたい
  // smiyahara: ほかはevery使っているから統一感がない
  string start = "start = "+to_string(static_cast<int>(config.gp.tstart/(config.gp.st*config.clock.dt)))+"\n";
  string end = "end = "+to_string(static_cast<int>(config.clock.n/config.gp.st))+"\n";

  string plot =
    "do for [i = start:end]{\n"
    // smiyahara: config.gp.stではなくconfig.gif.stにしたい
    "\tset title sprintf('t = %5.3f', (i - start)*"+to_string(config.gp.st*config.clock.dt)+") offset -12,-0.5\n\n"
    "\tplot\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($1*M):($2*M) notitle w l lw 3 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($3*M):($4*M) notitle w l lw 3 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($5*M):($6*M) notitle w l lw 2 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($7*M):($8*M) notitle w l lw 2 lc rgb 'grey10',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($9*M):($10*M) t 'CoM' w p pt 7 ps PS lc rgb 'red',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($11*M):($12*M) t 'CoP' w p pt 5 ps PS lc rgb 'green',\\\n"
    "\t\tDIR_DAT.'"+file_name+".dat' index i using ($13*M):($14*M) t 'DCM' w p pt 13 ps PS lc rgb 'blue'\n"
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
