/**
   @author Sho Miyahara 2017
*/

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
      "\\def\\model{" << config.body.name << "}" << endl <<
      "\\def\\controller{" << config.controller.name << "}" << endl <<
      "\\def\\cmp{" << config.result.name.cmp << "}" << endl <<
      "\\def\\ind{" << config.result.name.ind << "}" << endl;
    simInfo.close();
  }
}
