#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeVelocityDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string dir = config.dir.dat.ind + "controller/";

  string name;
  string load;
  string minipage;

  string input_dir = "\\input{\\result/"+config.controller.name+":"+config.body.name+"/"+config.result.name.cmp+"/"+"pdf/src/"+config.result.name.ind+"/";
  string input;

  name = "100_baseTransDes";
  minipage = baseVelDes(config, info, dir, load);

  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
		  "Desired base translation values."
		  );
    input += input_dir+name+"}\n";
  }

  name = "101_baseRotDes";
  minipage = baseAngVelDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired base rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "110_eeTransDes";
  minipage = eeVelDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired End effector translation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "111_eeRotDes";
  minipage = eeAngVelDes(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Desired End effector rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "120_baseTransErr";
  minipage = basePosErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base error translation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "121_baseRotErr";
  minipage = baseOrientErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base error rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "122_comErr";
  minipage = comPosErr(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "CoM error values."
  		  );
    input += input_dir+name+"}\n";
  }

  ofstream rlsDynamicsGp((config.dir.gp.ind+"controller.gp").c_str());
  if(!rlsDynamicsGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    rlsDynamicsGp << load << endl;
    rlsDynamicsGp.close();
  }
  ofstream tex((config.dir.pdf.ind+config.result.name.ind+".tex").c_str(), ios::app);
  if(!tex)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    tex << input << endl;
    tex.close();
  }
}
