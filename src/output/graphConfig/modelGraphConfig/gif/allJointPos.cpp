/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::allJointPos(const Config &config, const TreeModel::Info &info, GpMaker &gpMaker, TexMaker &texMaker)
{
  if(debug) DEBUG;

  string path_temp;

  int limb[4] = {7,7,5,5};

  int cur=0;
  // for(int l=1; l<model.value; l++){
  // smiyahara: 未実装
  for(int l=1; l<5; l++){
    path_temp = config.dir.gif.ind + "allJointPosLimb"+to_string(l)+".dat";
    ofstream gif(path_temp.c_str());
    if(!gif)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<config.clock.n+1; i+=config.gif.st)
        gif << setprecision(9) << scientific <<
          data.tm[i].posGifMatrix.col(0).transpose() << endl <<
          data.tm[i].posGifMatrix.block(0,cur+1,3,limb[l-1]).transpose() <<
          endl << endl << endl;

      gif.close();
    }

    cur += limb[l-1];
  }

  FILE *gp;
  gp = popen("gnuplot -persist ", "w");

  string out = "dir";
  if(out=="terminal")
    fprintf(gp, "set terminal qt 0 size 640, 480\n");
  else if(out=="dir"){
    fprintf(gp, "set term gif animate delay 1 optimize size 1280, 1024\n");
    fprintf(gp, "MODEL = '%s'\n", (config.dir.gif.cmp+"3D.gif").c_str());
    fprintf(gp, "set output MODEL\n");
  }

  fprintf(gp, "reset\n");
  fprintf(gp, "unset key\n");
  fprintf(gp, "set size ratio -1\n");
  fprintf(gp, "set xrange[%s:%s]\n", config.gif.all.xMin.c_str(), config.gif.all.xMax.c_str());
  fprintf(gp, "set yrange[%s:%s]\n", config.gif.all.yMin.c_str(), config.gif.all.yMax.c_str());
  fprintf(gp, "set zrange[%s:%s]\n", config.gif.all.zMin.c_str(), config.gif.all.zMax.c_str());

  double t;
  for(int i=0; i<config.clock.n/config.gif.st+1; i++){
    t = i*config.gif.st*config.clock.dt;
    o(config.clock.n);
    o(config.gif.st);
    o(config.clock.dt);
    // t = model.t0 + i*config.gif.st*model.dt;

    fprintf(gp, "t = %f\n", t);
    fprintf(gp, "time = sprintf(\"t = %%4.2f\", t)\n");
    fprintf(gp, "set title time\n");
    fprintf(gp, "splot ");
    // for(int j=1; j<model.value; j++){
    for(int j=1; j<5; j++){
      fprintf(gp, "'%sallJointPosLimb%c.dat'", config.dir.gif.ind.c_str(), '0'+j);
      fprintf(gp, "index %d w l lw 5 lc rgb '%s',", i, config.gif.linkColor.c_str());
      fprintf(gp, "'' index %d w p pt 7 ps 2 lc rgb '%s'", i, config.gif.jointColor.c_str());
      // if(j<model.value-1)
      if(j<5-1)
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
