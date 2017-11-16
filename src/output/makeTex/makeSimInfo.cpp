#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeSimInfo(Config &config)
{
  if(config.flag.debug) DEBUG;

  ofstream simInfo((config.dir.interface+"simInfo.tex").c_str());
  if(!simInfo)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    simInfo <<
      "\\def\\model{" << config.model.name << "}" << endl <<
      "\\def\\controller{" << config.controller.name << "}" << endl <<
      "\\def\\data{" << config.data.name.main << "}" << endl <<
      "\\def\\sub{" << config.data.name.sub << "}" << endl;
    simInfo.close();
  }
}
