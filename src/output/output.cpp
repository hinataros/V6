/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::output(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.tex.flag){
    TexMaker interfaceMaker;
    interfaceMaker.setInterfacePath(config.dir.interface);
    interfaceMaker.setModelName(config.body.name);
    interfaceMaker.setControllerName(config.controller.name);
    interfaceMaker.setTitle(config.tex.title);
    interfaceMaker.setCmpName(config.result.name.cmp);
    interfaceMaker.setIndName(config.result.name.ind);

    interfaceMaker.makeSimInfo();

    // clean tex
    ofstream clean((config.dir.pdf.ind+config.result.name.ind+".tex").c_str());
  }

  if(config.gp.flag){
    GpMaker libraryMaker;
    libraryMaker.setGpPath(config.dir.gp.ind);
    libraryMaker.setDatPath(config.dir.dat.ind);
    libraryMaker.setEpsPath(config.dir.eps.ind);
    libraryMaker.setDt(info.sim.dt);
    libraryMaker.setST(config.gp.st);
    libraryMaker.setStartTime(config.gp.tstart);

    libraryMaker.makeLibrary();

    // controller graph config
    if(config.controller.name=="rlsDynamics"){
      if(config.controller.input=="velocity")
        velocityGraphConfig(config, info);
      else if(config.controller.input=="acceleration")
        accelerationGraphConfig(config, info);
      else if(config.controller.input=="torque")
        masterGraphConfig(config, info);
        // torqueGraphConfig(config, info);
    }
    runGnuplot(config);
  }

  if(config.cho.flag)
    makeMotionYaml(config, info);

  // if(config.gif.flag){
  //   makeGifDat(config, model);
  //   makeGif(config, model);
  // }
}
