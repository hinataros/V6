#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeGif2D(Config &config, Model &model, string out, string plane1, string plane2)
{
  if(config.flag.debug) DEBUG;

  FILE *gp;
  gp = popen("gnuplot -persist ", "w");

  if(out=="terminal")
    fprintf(gp, "set terminal qt 0 size 640, 480\n");
  else if(out=="dir"){
    fprintf(gp, "set term gif animate delay 1 optimize size 1280, 1024\n");
    fprintf(gp, "MODEL = '%s'\n", ("data/gif/"+config.model.name+"/"+plane1+plane2+".gif").c_str());
    fprintf(gp, "set output MODEL\n");
  }

  int p1,p2;
  p1 = setPlane(plane1);
  p2 = setPlane(plane2);

  fprintf(gp, "reset\n");
  fprintf(gp, "unset key\n");
  fprintf(gp, "set size ratio -1\n");
  if(plane1=="y"&&plane2=="z"){
    fprintf(gp, "set xrange[%s:%s]\n", config.gif.yz.xMin.c_str(), config.gif.yz.xMax.c_str());
    fprintf(gp, "set yrange[%s:%s]\n", config.gif.yz.yMin.c_str(), config.gif.yz.yMax.c_str());
  }else if(plane1=="x"&&plane2=="z"){
    fprintf(gp, "set xrange[%s:%s]\n", config.gif.xz.xMin.c_str(), config.gif.xz.xMax.c_str());
    fprintf(gp, "set yrange[%s:%s]\n", config.gif.xz.yMin.c_str(), config.gif.xz.yMax.c_str());
  }else if(plane1=="x"&&plane2=="y"){
    fprintf(gp, "set xrange[%s:%s]\n", config.gif.xy.xMin.c_str(), config.gif.xy.xMax.c_str());
    fprintf(gp, "set yrange[%s:%s]\n", config.gif.xy.yMin.c_str(), config.gif.xy.yMax.c_str());
  }

  double t;
  for(int i=0; i<model.n/config.gif.st+1; i++){
    t = model.t0 + i*config.gif.st*model.dt;

    fprintf(gp, "t = %f\n", t);
    fprintf(gp, "time = sprintf(\"t = %%4.2f\", t)\n");
    fprintf(gp, "set title time\n");
    fprintf(gp, "plot ");
    for(int j=1; j<model.value; j++){
      fprintf(gp, "'data/dat/%s/gif/allJointPosLimb%c.dat'", config.model.name.c_str(),'0'+j);
      fprintf(gp, "index %d u %d:%d w l lw 5 lc rgb '%s',", i, p1, p2, config.gif.linkColor.c_str());
      fprintf(gp, "'' index %d u %d:%d w p pt 7 ps 2 lc rgb '%s'", i, p1, p2, config.gif.jointColor.c_str());
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
