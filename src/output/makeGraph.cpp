/**
   @author Sho Miyahara 2017
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeGraph(Config &config)
{
  if(config.flag.debug) DEBUG;

  FILE *gp;

  gp = popen("gnuplot -persist ", "w");
  fprintf(gp,"cd '%s'\n", (config.dir.gp.ind).c_str());
  fprintf(gp,"load 'model.gp'\n");
  fprintf(gp,"load 'controller.gp'\n");
  pclose(gp);

  cout << "made graphs..." << endl;

  if(config.graph.check){
    cout << "Please hit any key...";
    getchar();
  }

  int check = system("pkill gnuplot_x11");
  if(check==0)
    cout << "Graph closed successfully!" << endl;

  // eps handler target
  ofstream flag((config.dir.interface+"handler.flag").c_str());
  flag.close();
}
