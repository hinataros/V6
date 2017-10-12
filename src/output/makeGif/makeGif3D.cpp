#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeGif3D(Config &config, Model &model, string out)
{
  if(config.flag.debug) DEBUG;

  FILE *gp;
  gp = popen("gnuplot -persist ", "w");

  if(out=="terminal")
    fprintf(gp, "set terminal qt 0 size 640, 480\n");
  else if(out=="dir"){
    fprintf(gp, "set term gif animate delay 1 optimize size 1280, 1024\n");
    fprintf(gp, "MODEL = '%s'\n", ("data/gif/"+config.model.name+"/3D.gif").c_str());
    fprintf(gp, "set output MODEL\n");
  }

  fprintf(gp, "reset\n");
  fprintf(gp, "unset key\n");
  fprintf(gp, "set size ratio -1\n");
  fprintf(gp, "set xrange[%s:%s]\n", config.gif.all.xMin.c_str(), config.gif.all.xMax.c_str());
  fprintf(gp, "set yrange[%s:%s]\n", config.gif.all.yMin.c_str(), config.gif.all.yMax.c_str());
  fprintf(gp, "set zrange[%s:%s]\n", config.gif.all.zMin.c_str(), config.gif.all.zMax.c_str());

  double t;
  for(int i=0; i<model.n/config.gif.st+1; i++){
    t = model.t0 + i*config.gif.st*model.dt;

    fprintf(gp, "t = %f\n", t);
    fprintf(gp, "time = sprintf(\"t = %%4.2f\", t)\n");
    fprintf(gp, "set title time\n");
    fprintf(gp, "splot ");
    for(int j=1; j<model.value; j++){
      fprintf(gp, "'data/dat/%s/gif/allJointPosLimb%c.dat'", config.model.name.c_str(), '0'+j);
      fprintf(gp, "index %d w l lw 5 lc rgb '%s',", i, config.gif.linkColor.c_str());
      fprintf(gp, "'' index %d w p pt 7 ps 2 lc rgb '%s'", i, config.gif.jointColor.c_str());
      if(j<model.value-1)
	fprintf(gp, ",");
      else
	fprintf(gp, "\n");
    }
    fflush(gp);
  }

  fprintf(gp, "exit\n");
  fclose(gp);
  int check = system("pkill gnuplot_qt");
  if(check==0)
    cout << "GIF closed successfully!" << endl;
}
