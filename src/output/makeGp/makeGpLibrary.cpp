#include <fstream>

#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::makeGpLibrary(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  string pathLib = config.link + "data/gp/"  + config.controller.name + ":" + config.model.name + "/" + config.name + "/library";
  string pathLib_temp;

  // config
  string font_config =
    "FONT = 'Times New Roman'\n"
    "FONT_SIZE = 35\n"
    "EPS_FONT_SIZE = 30\n";

  string line_config =
    "LINE_WIDTH = 5\n";

  string etc_config =
    "VIEWMODE = 0# 1:on 0:off\n"
    "KEY = 0\n";

  string terminal_config =
    "TERMINAL = 'x11'\n";

  string time_config =
    "T_OFFSET = 10\n"
    "SAMPLING = "+to_string(static_cast<int>(1/(config.graph.st*info.sim.dt)))+"\n";

  pathLib_temp = pathLib + "/config.gp";
  ofstream libConfig(pathLib_temp.c_str());
  if(!libConfig)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    libConfig <<
      font_config << endl <<
      line_config << endl <<
      etc_config << endl <<
      terminal_config << endl <<
      time_config << endl;
    libConfig.close();
  }

  string pathDat_controller = config.link + "data/dat/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/controller/";
  string pathDat_model = config.link + "data/dat/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/model/";
  string pathEps_controller = config.link + "data/eps/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/controller/";
  string pathEps_model = config.link + "data/eps/" + config.controller.name + ":" + config.model.name + "/" + config.name + "/model/";

  // macro
  string path_macro =
    "CONTROLLER_DAT = '" + pathDat_controller +"'\n"
    "MODEL_DAT = '" + pathDat_model +"'\n"
    "CONTROLLER_EPS = '" + pathEps_controller +"'\n"
    "MODEL_EPS = '" + pathEps_model +"'\n";

  string unit_macro =
    "E = 1e+0\n"
    "K = 1e+3\n"
    "MM = 1e-3\n";

  string rotation_macro =
    "PI = 3.14159265358979323846\n"
    "RAD2DEG = 180/PI\n";

  pathLib_temp = pathLib + "/macro.gp";
  ofstream libMacro(pathLib_temp.c_str());
  if(!libMacro)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    libMacro <<
      path_macro << endl <<
      unit_macro << endl <<
      rotation_macro << endl;
    libMacro.close();
  }

  // set
  string terminal_set =
    "set terminal postscript EPS_FONT_SIZE eps color solid 'Times' enhanced\n";

  string key_set =
    "if(!KEY) set nokey\n";

  string etc_set =
    "set xzeroaxis\n"
    "# set grid\n";

  string line_style_set =
    "set style line 1 lw LINE_WIDTH lc 1\n"
    "set style line 2 lw LINE_WIDTH lc 2\n"
    "set style line 3 lw LINE_WIDTH lc 3\n"
    "set style line 4 lw LINE_WIDTH lc 4\n"
    "set style line 5 lw LINE_WIDTH lc 5\n"
    "set style line 6 lw LINE_WIDTH lc 6\n";

  pathLib_temp = pathLib + "/set.gp";
  ofstream libSet(pathLib_temp.c_str());
  if(!libSet)
    cout << path << ": " << endl << "file open error..." << endl;
  else{
    libSet <<
      terminal_set << endl <<
      key_set << endl <<
      etc_set << endl <<
      line_style_set << endl;
    libSet.close();
  }
}
