#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeAccelerationDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string dir = config.dir.dat.sub + "controller/";

  string name;
  string load;
  string minipage;

  string input_dir = "\\input{\\result/"+config.controller.name+":"+config.model.name+"/"+config.data.name.main+"/"+"pdf/src/"+config.data.name.sub+"/";
  string input;

  name = "100_baseTransDes";
  minipage = baseAccDes(config, info, dir, load);

  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
		  "Desired base translation values."
		  );
    input += input_dir+name+"}\n";
  }

  name = "101_baseRotDes";
  minipage = baseAngAccDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired base rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "110_eeTransDes";
  minipage = eeAccDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired End effector translation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "111_eeRotDes";
  minipage = eeAngAccDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired End effector rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "120_baseTransErr";
  minipage = baseVelErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base error translation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "121_baseRotErr";
  minipage = baseAngVelErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base error rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  ofstream rlsDynamicsGp((config.dir.gp.sub+"controller.gp").c_str());
  if(!rlsDynamicsGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    rlsDynamicsGp << load << endl;
    rlsDynamicsGp.close();
  }
  ofstream tex((config.dir.pdf.sub+config.data.name.sub+".tex").c_str(), ios::app);
  if(!tex)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    tex << input << endl;
    tex.close();
  }
}