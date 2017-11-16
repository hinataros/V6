#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::formulatedMom(Config &config, Info &info, string dir, string &load)
{
  if(config.flag.debug) DEBUG;

  string name;
  string minipage;

  // CRB linear momentum
  name = "041_crbMom";
  ofstream crbMom((dir+name+".dat").c_str());
  if(!crbMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      crbMom << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].pCRB.transpose() << endl;
    crbMom.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "CRB linear momentum [Ns]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // CRB angular momentum
  name = "041_crbAngMom";
  ofstream crbAngMom((dir+name+".dat").c_str());
  if(!crbAngMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      crbAngMom << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].lCRB.transpose() << endl;
    crbAngMom.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "CRB angular momentum [Nms]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // coupling momentum
  name = "041_coupMom";
  ofstream coupMom((dir+name+".dat").c_str());
  if(!coupMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      coupMom << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].pCth.transpose() << endl;
    coupMom.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Coupling momentum [Ns]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // coupling angular momentum
  name = "041_coupAngMom";
  ofstream coupAngMom((dir+name+".dat").c_str());
  if(!coupAngMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      coupAngMom << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].lCth.transpose() << endl;
    coupAngMom.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "Coupling angular momentum [Nms]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // linear momentum
  name = "041_formLinMom";
  ofstream formLinMom((dir+name+".dat").c_str());
  if(!formLinMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      formLinMom << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].p.transpose() << endl;
    formLinMom.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "linear mometum. [Ns]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  // angular momentum
  name = "041_formAngMom";
  ofstream formAngMom((dir+name+".dat").c_str());
  if(!formAngMom)
    cout << dir+name+".dat" << ": " << endl << "file open error..." << endl;
  else{
    for(int i=0; i<info.sim.n; i+=config.graph.st)
      formAngMom << setprecision(9) << scientific <<
  	data.t[i] << " " << data.dc[i].lC.transpose() << endl;
    formAngMom.close();
  }

  if(config.graph.gp){
    makeGpTime3D(config, "controller", name, "angular mometum. [Nms]","E",0);
    load += "load 'controller/"+name+".gp'\n";
  }
  if(config.graph.tex){
    minipage += makeMinipage(config, "controller", "1.0", name);
  }

  return minipage;
}
