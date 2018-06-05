/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "gpMaker.hpp"

void RLS::GpMaker::setGpPath(string arg)
{
  path_gp_ind = arg;
}

void RLS::GpMaker::setDatPath(string arg)
{
  path_dat_ind = arg;
}

void RLS::GpMaker::setEpsPath(string arg)
{
  path_eps_ind = arg;
}

void RLS::GpMaker::setDt(double arg)
{
  dt = arg;
}

void RLS::GpMaker::setST(int arg)
{
  st = arg;
}

void RLS::GpMaker::makeLibrary()
{
  makeMacro();
  makeConfig();
  makeSet();
}

void RLS::GpMaker::makeMacro()
{
  string path_macro =
    "DIR_LIB = '" + path_gp_ind+"library/" +"'\n"
    "DIR_DAT = '" + path_dat_ind+"'\n"
    "DIR_EPS = '" + path_eps_ind+"'\n";

  string unit_macro =
    "E = 1e+0\n"
    "M = 1e+3\n"
    "K = 1e-3\n";

  string rotation_macro =
    "PI = 3.14159265358979323846\n"
    "RAD2DEG = 180/PI\n";

  ofstream macro((path_gp_ind+"library/macro.gp").c_str());
  if(!macro)
    cout << path_gp_ind+"library/macro.gp" << ": " << endl
         << "file open error..." << endl;
  else{
    macro <<
      path_macro << endl <<
      unit_macro << endl <<
      rotation_macro << endl;
    macro.close();
  }
}

void RLS::GpMaker::makeConfig()
{
  string font_config =
    "FONT = 'Times New Roman'\n"
    "FONT_SIZE = 35\n"
    "EPS_FONT_SIZE = 45\n";

  string line_config =
    "LINE_WIDTH = 5\n";

  string decimal_config =
    "DECIMAL_COORD_X = 0.29\n"
    "DECIMAL_COORD_Y = 0.94\n";

  string ylabel_config =
    "YLABEL_OFFSET_X = -0.35\n"
    "YLABEL_OFFSET_Y = 0.5\n";

  string etc_config =
    "VIEWMODE = 0# 1:on 0:off\n"
    "KEY = 0\n";

  string terminal_config =
    "TERMINAL = 'x11'\n";

  string time_config =
    "T_OFFSET = 0\n"
    "SAMPLING = "+to_string(static_cast<int>(1/(st*dt)))+"\n";

  ofstream libConfig((path_gp_ind+"library/config.gp").c_str());
  if(!libConfig)
    cout << path_gp_ind+"library/config.gp" << ": " << endl
         << "file open error..." << endl;
  else{
    libConfig <<
      font_config << endl <<
      line_config << endl <<
      decimal_config << endl <<
      ylabel_config << endl <<
      etc_config << endl <<
      terminal_config << endl <<
      time_config << endl;
    libConfig.close();
  }
}

void RLS::GpMaker::makeSet()
{
    // set
  string terminal_set =
    "set terminal postscript EPS_FONT_SIZE eps color solid 'Times' enhanced\n";

  string key_set =
    "if(!KEY) set nokey\n";

  string etc_set =
    "set xzeroaxis\n"
    "# set grid\n";

  string margin_set =
    "set lmargin 8\n"
    "set rmargin 2\n";

  string autotics_set =
    "set xtics autofreq\n"
    "set ytics autofreq\n";

  string format_set =
    "";
    // "set format y '%3.1f'\n";

  string line_style_set =
    "set style line 1 lw LINE_WIDTH lc 1\n"
    "set style line 2 lw LINE_WIDTH lc 2\n"
    "set style line 3 lw LINE_WIDTH lc 3\n"
    "set style line 4 lw LINE_WIDTH lc 4\n"
    "set style line 5 lw LINE_WIDTH lc 5\n"
    "set style line 6 lw LINE_WIDTH lc rgb 'orange'\n";

  ofstream libSet((path_gp_ind+"library/set.gp").c_str());
  if(!libSet)
    cout << path_gp_ind+"library/set.gp" << ": " << endl
         << "file open error..." << endl;
  else{
    libSet <<
      terminal_set << endl <<
      key_set << endl <<
      etc_set << endl <<
      margin_set << endl <<
      autotics_set << endl <<
      format_set << endl <<
      line_style_set << endl;
    libSet.close();
  }
}
