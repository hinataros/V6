/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::runGnuplot()
{
  if(debug) DEBUG;

  FILE *fp;

  fp = popen("gnuplot -persist ", "w");
  fprintf(fp,"cd '%s'\n", (dir.gp.ind).c_str());
  fprintf(fp,"load 'main.gp'\n");
  pclose(fp);

  cout << "made graphs..." << endl;

  if(gp.check){
    cout << "Please hit any key...";
    getchar();
  }

  int check = system("pkill gnuplot_x11");
  if(check==0)
    cout << "Graph closed successfully!" << endl;

  // eps handler target
  ofstream flag((dir.interface+"handler.flag").c_str());
  flag.close();
}
