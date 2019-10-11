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

// smiyahara: tstartの初期化が面倒だからsetStartTime()は呼ぶ前提
void RLS::GpMaker::setStartTime(double arg)
{
  tstart = arg;
}

// hinata
void RLS::GpMaker::setDashTimes(vector<double> arg0, int arg1)
{
  flagX2 = true;

  dashNum = arg1;

  for(int i=0; i<dashNum; i++)
    tdash.push_back(arg0[i]);
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

// hinata
string RLS::GpMaker::makeDashTimes()
{
  int i;
  string dashtime_set;

  dashtime_set =
    "set x2tics (";

  for(i=0; i<dashNum-1; i++){
    dashtime_set += "\"\""+ to_string(tdash[i]-tstart);
    if(i<dashNum-2)
      dashtime_set += ",";
    else
      dashtime_set += ")\n";
  }

  dashtime_set += "set x2range [*:*]";

  return dashtime_set;
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
    "DECIMAL_COORD_X = 0.25\n"
    "DECIMAL_COORD_Y = 0.94\n";

  string lavel_color_config =
    "XLABEL_COLOR = 'black'\n"
    "YLABEL_COLOR = 'black'\n";

  string ylabel_config =
    "XLABEL_OFFSET_X = 0.5\n"
    "XLABEL_OFFSET_Y = -0.3\n"
    "YLABEL_OFFSET_X = -0.3\n"
    "YLABEL_OFFSET_Y = 0.5\n";

  string etc_config =
    "VIEWMODE = 0# 1:on 0:off\n"
    "XLABEL = 1\n"
    "KEY = 0\n";

  string background_config =
    "BACKGROUND = 0\n"
    "if(BACKGROUND) XLABEL_COLOR = 'white'\n"
    "if(BACKGROUND) YLABEL_COLOR = 'white'\n";

  string terminal_config =
    "TERMINAL = 'x11'\n";

  string time_config =
    "T_OFFSET = "+to_string(tstart)+"\n"
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
      lavel_color_config << endl <<
      ylabel_config << endl <<
      etc_config << endl <<
      background_config << endl <<
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

  string format_set =
    "";
    // "set format y '%3.2f'\n";

  string margin_set =
    "set lmargin 6.5\n"
    "set rmargin 1.2\n"
    "set tmargin 1.2\n"
    "set bmargin 2.8\n";

  string autotics_set =
    "set xtics autofreq\n"
    "set ytics autofreq\n"
    "set autoscale xfix\n";

  string dashtime_set;
  if(flagX2)
    dashtime_set = makeDashTimes();
  else
    dashtime_set = "\n";

  string line_style_set =
    "set style line 1 lw LINE_WIDTH lc 1\n"
    "set style line 2 lw LINE_WIDTH lc 2\n"
    "set style line 3 lw LINE_WIDTH lc 3\n"
    "set style line 4 lw LINE_WIDTH lc 4\n"
    "set style line 5 lw LINE_WIDTH lc 5\n"
    "set style line 6 lw LINE_WIDTH lc rgb 'orange'\n";

  string background_set =
    "if(BACKGROUND) set object 1000 rect behind from screen 0,0 to screen 1,1 fc rgb '#333333' fillstyle solid 1.0 border -1\n"
    "if(BACKGROUND) set xzeroaxis lc rgb 'white'\n"
    "if(BACKGROUND) set border lc rgb 'white'\n"
    "if(BACKGROUND) set xtics textcolor rgb 'white'\n"
    "if(BACKGROUND) set ytics textcolor rgb 'white'\n"
    "if(BACKGROUND) set key textcolor rgb 'white'\n"
    "if(BACKGROUND) set style line 1 lw LINE_WIDTH lc rgb 'magenta'\n"
    "if(BACKGROUND) set style line 2 lw LINE_WIDTH lc rgb 'greenyellow'\n"
    "if(BACKGROUND) set style line 3 lw LINE_WIDTH lc rgb 'cyan'\n";

  string dashline_set;
  if(flagX2){
    dashline_set =
      "set grid noxtics noytics x2tics lt 1 lw 2 lc rgb 'black' dt (10, 5)\n";
  }
  else
    dashline_set = "\n";

  ofstream libSet((path_gp_ind+"library/set.gp").c_str());
  if(!libSet)
    cout << path_gp_ind+"library/set.gp" << ": " << endl
         << "file open error..." << endl;
  else{
    libSet <<
      terminal_set << endl <<
      key_set << endl <<
      etc_set << endl <<
      format_set << endl <<
      margin_set << endl <<
      autotics_set << endl <<
      line_style_set << endl <<
      background_set << endl <<
      dashline_set << endl;
  libSet.close();
  }
}
