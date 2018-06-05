/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "texMaker.hpp"

void RLS::TexMaker::setInterfacePath(string arg)
{
  path_interface = arg;
}

void RLS::TexMaker::setModelName(string arg)
{
  name_model = arg;
}

void RLS::TexMaker::setControllerName(string arg)
{
  name_controller = arg;
}

void RLS::TexMaker::setTitle(string arg)
{
  title = arg;
}

void RLS::TexMaker::setCmpName(string arg)
{
  name_cmp = arg;
}

void RLS::TexMaker::setIndName(string arg)
{
  name_ind = arg;
}

void RLS::TexMaker::makeSimInfo()
{
  ofstream simInfo((path_interface+"simInfo.tex").c_str());
  if(!simInfo)
    cout << path_interface+"simInfo.tex" << ": " << endl << "file open error..." << endl;
  else{
    simInfo <<
      "\\def\\title{" << title << "}" << endl <<
      "\\def\\cmp{" << name_cmp << "}" << endl <<
      "\\def\\ind{" << name_ind << "}" << endl;
    simInfo.close();
  }
}
