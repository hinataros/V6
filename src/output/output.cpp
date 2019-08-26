/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::output()
{
  if(debug) DEBUG;

  dirCheck(); // amiyata

  if(tex.flag){
    TexMaker interfaceMaker;
    interfaceMaker.setInterfacePath(dir.interface);
    interfaceMaker.setTitle(tex.title);
    interfaceMaker.setCmpName(result.cmp);
    interfaceMaker.setIndName(result.ind);

    interfaceMaker.makeSimInfo();

    // clean tex
    ofstream clean((dir.pdf.ind+result.ind+".tex").c_str());
  }

  if(gp.flag){
    GpMaker libraryMaker;
    libraryMaker.setGpPath(dir.gp.ind);
    libraryMaker.setDatPath(dir.dat.ind);
    libraryMaker.setEpsPath(dir.eps.ind);
    libraryMaker.setDt(worldModel->dt);
    libraryMaker.setST(gp.st);
    libraryMaker.setStartTime(gp.tstart);

    libraryMaker.makeLibrary();

    makeGraph();

    runGnuplot();
  }

  if(cho.flag)
    makeMotionYaml();

  // amiyata
  if(eq.flag)
    makeEquationTex();

  // // if(config.gif.flag){
  // //   makeGifDat(config, model);
  // //   makeGif(config, model);
  // // }
}
