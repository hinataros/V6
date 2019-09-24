/**
   @author Sho Miyahara 2018
*/

#include <iostream>

#include <iomanip>
#include <sstream>
#include <vector>

#include <algorithm>

using namespace std;

namespace RLS{
  class TexMaker{
  private:
    void initialize();

    string lzero3format(int i){
      ostringstream ss;
      ss << setw(3) << setfill('0') << i;
      string s(ss.str());
      return s;
    }

    // interface maker
    string path_interface;
    string title;
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
    string name;
    int numLimb;
    vector<bool> flag;
    double width;

    string capRef;
    string texName;

  public:
    // interface maker
    void setInterfacePath(string);
    void setTitle(string);
    void setCmpName(string);
    void setIndName(string);
    void makeSimInfo();

    // tex maker
    void reset();
    void setResultPath(string);
    void setEpsPath(string);
    void setPdfPath(string);
    void setName(string);
    void setLimb(int);
    void setLimbNum(int, bool);
    void setWidth(double);
    void setCaption(string);
    void setNewline();
    void addMinipage();
    void addMinipage(string);

    void setTexName(string);
    void makeTex();

    void addInput();

    void setMainTexName(string);
    void makeMainTex();

    TexMaker();
    ~TexMaker();
  };
}
