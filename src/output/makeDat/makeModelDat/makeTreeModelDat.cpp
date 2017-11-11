#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeTreeModelDat(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  path = config.link + "data/dat/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/model/";

  string name;

  string load;

  string minipage;

  string input_dir = "\\input{\\data/pdf/"+config.controller.name+":"+config.model.name+"/src/"+config.name+"/";
  string input;

  name = "000_baseTrans";
  minipage = baseTrans(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
		  "Base translation values."
		  );
    input += input_dir+name+"}\n";
  }

  name = "001_baseRot";
  minipage = baseRot(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Base rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "010_joint";
  minipage = joint(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Joint values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "020_eeTrans";
  minipage = eeTrans(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector translation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "021_eeRot";
  minipage = eeRot(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "End effector rotation values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "030_com";
  minipage = com(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "CoM values."
  		  );
    input += input_dir+name+"}\n";
  }

  name = "040_mom";
  minipage = mom(config, info, load);
  if(config.graph.tex){
    makeFigureTex(config, name, minipage,
  		  "Linear and angular momentum."
  		  );
    input += input_dir+name+"}\n";
  }

  string pathGp = config.link + "data/gp/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/model.gp";
  ofstream modelGp(pathGp.c_str());
  if(!modelGp)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    modelGp << load << endl;
    modelGp.close();
  }
  string pathTex = config.link + "data/pdf/" + config.controller.name + ":" + config.model.name + "/src/" + config.name + "/" + config.name + ".tex";
  ofstream tex(pathTex.c_str());
  if(!tex)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    tex << input << endl;
    tex.close();
  }
}
