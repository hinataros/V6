#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeInterface(Config &config)
{
  if(config.flag.debug) DEBUG;

  string pathInterface = config.link + "data/pdf/interface.tex";

  ofstream interface(pathInterface.c_str());
  if(!interface)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    interface <<
      "\\def\\model{" << config.model.name << "}" << endl <<
      "\\def\\controller{" << config.controller.name << "}" << endl <<
      "\\def\\sim{" << config.name << "}" << endl;
    interface.close();
  }
}
