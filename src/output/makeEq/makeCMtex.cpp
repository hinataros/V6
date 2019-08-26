/**
   @author AKinori Miyata 2019
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeCMtex()
{
  string controllerName = "controlMethod.tex";
  string inputEqs = "";

  inputEqs += "\\input{\\srces/sectionDVG}\n";


  ofstream eqTex((dir.eq.ind+controllerName).c_str(), ios::out);
  if(!eqTex)
    cout << dir.eq.ind+controllerName << ": " << endl << "file open error..." << endl;
  else{
    eqTex << inputEqs << endl;
    eqTex.close();
  }
}
