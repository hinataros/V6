#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeGraph(Config &config)
{
  if (config.flag.debug) DEBUG;

  FILE *gp;

  gp = popen("gnuplot -persist ", "w");
  fprintf(gp,"cd '%s'\n", (config.link + "data/gp/"  + config.name + "/" + config.controller.name + ":" + config.model.name).c_str());
  fprintf(gp,"load 'model.gp'\n");
  fprintf(gp,"load 'controller.gp'\n");
  pclose(gp);

  cout << "Please hit any key to finish simulation!!";
  getchar();

  int check = system("pkill gnuplot_x11");
  if(check==0)
    cout << "Graph closed successfully!" << endl;
}
