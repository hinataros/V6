/**
   @author Sho Miyahara 2018
*/

#include <iostream>

#include <iomanip>
#include <sstream>

#include <algorithm>

using namespace std;

namespace RLS{
  class TexMaker{
  private:
    void initialize();
    void initialize(string);

    string lzero3format(int i){
      ostringstream ss;
      ss << setw(3) << setfill('0') << i;
      string s(ss.str());
      return s;
    }

    // interface maker
    string path_interface;
    string name_model;
    string name_controller;
    string name_cmp;
    string name_ind;

    string input;

    string minipage;

    int numName;
    string main_tex_name;
    string path_result;
    string path_eps;
    string path_pdf;
    string input_dir;
    string category;
    string name;
    double width;

    string capRef;
    string texName;

  public:
    // interface maker
    void setInterfacePath(string);
    void setModelName(string);
    void setControllerName(string);
    void setCmpName(string);
    void setIndName(string);
    void makeSimInfo();

    // tex maker
    void reset();
    void setResultPath(string);
    void setEpsPath(string);
    void setPdfPath(string);
    void setCategory(string);
    void setName(string);
    void setWidth(double);
    void setCaption(string);
    void addMinipage();
    void addMinipage(int);
    void addMinipage(string);

    void setTexName(string);
    void makeTex();

    void addInput();

    void setMainTexName(string);
    void makeMainTex();

    TexMaker();
    TexMaker(string);
    ~TexMaker();
  };
}
