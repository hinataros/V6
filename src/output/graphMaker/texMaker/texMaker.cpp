/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "texMaker.hpp"

RLS::TexMaker::TexMaker()
{
  initialize();
}

RLS::TexMaker::~TexMaker()
{
  vector<bool>().swap(flag);
}

void RLS::TexMaker::initialize()
{
  input = "";
  numName = 1;

  reset();
}

void RLS::TexMaker::reset()
{
  minipage = "";
  name = "";
  numLimb = 1;
  texName = "";
  width = 1.0;

  vector<bool>().swap(flag);
  flag.push_back(true);
}

void RLS::TexMaker::setResultPath(string arg)
{
  path_result = arg;
}

void RLS::TexMaker::setEpsPath(string arg)
{
  path_eps = arg;
}

void RLS::TexMaker::setPdfPath(string arg)
{
  path_pdf = arg;
}

void RLS::TexMaker::setName(string arg)
{
  name = arg;
}

void RLS::TexMaker::setLimb(int arg)
{
  numLimb = arg;

  flag.resize(arg, true);
}

void RLS::TexMaker::setLimbNum(int arg0, bool arg1)
{
  flag[arg0-1] = arg1;
}

void RLS::TexMaker::setWidth(double arg)
{
  width = arg;
}

void RLS::TexMaker::setCaption(string arg)
{
  capRef = arg;
}

void RLS::TexMaker::setNewline()
{
  minipage += "\\par";
}

void RLS::TexMaker::addMinipage()
{
  for(int l=1; l<numLimb+1; l++){
    if(flag[l-1]){
      if(numLimb==1)
        addMinipage("");
      else
        addMinipage("Limb"+to_string(l));
    }
  }
}

void RLS::TexMaker::addMinipage(string suffix)
{
  string temp = path_eps;
  temp.replace(0, path_result.size(), "");

  minipage +=
    "\\begin{minipage}{0.24\\linewidth}\n"
    "\\centering\n"
    "\\includegraphics[width="+to_string(width)+"\\hsize]{\\result/"+temp+name+suffix+".eps}\n"
    "\\par\\footnotesize{}\n"
    "\\end{minipage}\n";
}

void RLS::TexMaker::setTexName(string arg)
{
  texName = lzero3format(numName)+"_"+arg;

  numName++;
}

void RLS::TexMaker::makeTex()
{
  string begin =
    "\\begin{figure}[h]\n"
    "\\centering";

  string caption =
    "\\caption{"+capRef+"}";
  // // for color package
  // string caption =
  //   "\\vspace{5mm}\n"
  //   "\\caption{"+capRef+"}";

  string end =
    "\\end{figure}";

  ofstream texMaker((path_pdf+texName+".tex").c_str());
  if(!texMaker)
    cout << path_pdf << ": " << endl << "file open error..." << endl;
  else{
    texMaker <<
      begin << endl <<
      minipage << endl <<
      caption << endl <<
      end << endl;
    texMaker.close();
  }

  addInput();
}

void RLS::TexMaker::addInput()
{
  string temp = path_pdf;
  temp.replace(0, path_result.size(), "");

  input += "\\input{\\result/"+temp+texName+"}\n";
}

void RLS::TexMaker::setMainTexName(string arg)
{
  main_tex_name = arg+".tex";
}

void RLS::TexMaker::makeMainTex()
{
  ofstream main((path_pdf+main_tex_name).c_str(), ios::app);
  if(!main)
    cout << path_pdf+main_tex_name << ": " << endl << "file open error..." << endl;
  else{
    main << input << endl;
    main.close();
  }
}
