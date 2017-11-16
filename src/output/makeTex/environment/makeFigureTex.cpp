#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeFigureTex(Config &config, string name, string minipage, string capRef)
{
  if(config.flag.debug) DEBUG;

  string begin =
    "\\begin{figure}[h]\n"
    "\\centering";

  string caption =
    "\\caption{"+capRef+"}";

  string end =
    "\\end{figure}";

  ofstream tex((config.dir.pdf.sub+name+".tex").c_str());
  if(!tex)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    tex <<
      begin << endl <<
      minipage << endl <<
      caption << endl <<
      end << endl;
    tex.close();
  }
}
