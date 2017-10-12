#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeGifDat(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  path = config.link + "data/dat/" + config.name + "/" + config.controller.name + ":" + config.model.name+"/gif/";
  string path_temp;

  int cur=0;
  for(int l=1; l<model.value; l++){
    path_temp = path + "allJointPosLimb"+to_string(l)+".dat";
    ofstream gif(path_temp.c_str());
    if(!gif)
      cout << path_temp << ": " << endl << "file open error..." << endl;
    else{
      for(int i=0; i<model.n+1; i+=config.gif.st)
	gif << setprecision(9) << scientific <<
	  data.m[i].posGif.col(0).transpose() << endl <<
	  data.m[i].posGif.block(0,cur+1,3,model.limb[l].value).transpose() <<
	  endl << endl << endl;

      gif.close();
    }

    cur += model.limb[l].value;
  }
}
