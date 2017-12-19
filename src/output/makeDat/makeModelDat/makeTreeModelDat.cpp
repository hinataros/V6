#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeTreeModelDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string dir = config.dir.dat.ind + "model/";

  string name;
  string load;
  string minipage;

  string input_dir = "\\input{\\result/"+config.controller.name+":"+config.body.name+"/"+config.result.name.cmp+"/"+"pdf/src/"+config.result.name.ind+"/";
  string input;

  name = "000_baseTrans";
  minipage = baseTrans(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
		  "Base translation values."
		  );
    input += input_dir+name+"}\n";
  }

  name = "001_baseRot";
  minipage = baseRot(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "010_joint";
  minipage = joint(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Joint values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "020_eeTrans";
  minipage = eeTrans(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector translation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "021_eeRot";
  minipage = eeRot(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "030_eeWrench";
  minipage = eeWrench(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector wrench values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "030_com";
  minipage = com(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "CoM values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "040_mom";
  minipage = mom(config, info, dir, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Linear and angular momentum."
  		  );
    input += input_dir+name+"}\n";
  }

  ofstream modelGp((config.dir.gp.ind+"model.gp").c_str());
  if(!modelGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    modelGp << load << endl;
    modelGp.close();
  }
  ofstream tex((config.dir.pdf.ind+config.result.name.ind+".tex").c_str());
  if(!tex)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    tex << input << endl;
    tex.close();
  }
}
