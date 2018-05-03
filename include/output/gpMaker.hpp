/**
   @author Sho Miyahara 2018
*/

#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;

namespace RLS{
  class GpMaker{
  private:
    // 要検討
    string timeLabelStr = "Time [s]";

    template<typename TYPE, std::size_t SIZE>
    std::size_t array_length(const TYPE (&)[SIZE]){return SIZE;}

    string limbName[4] = {
      "R. leg",
      "L. leg",
      "R. arm",
      "L. arm"
    };

    string load;

    // library maker
    string path_gp_ind;
    string path_dat_ind;
    string path_eps_ind;
    double dt;
    int st;

    void makeMacro();
    void makeConfig();
    void makeSet();

    // gp maker
    string main_gp_name;
    string name;
    string suffix;
    string category;
    string CATEGORY;
    int numLimb;
    string limbLabel;
    string xLabel;
    string yLabel;
    string unit;
    vector<int> dimention;
    vector<string> scale;
    vector<int> exponent;
    vector<string> addStr;
    int terminal;

    int point;

  public:
    // library maker
    void setDatPath(string);
    void setEpsPath(string);
    void setDt(double);
    void setST(int);
    void makeLibrary();

    void reset();
    void setCategory(string);
    void setGpPath(string);
    void setName(string);
    void setLimb(int);
    void setXLabel(string);
    void setYLabel(string);
    void chUnit(string);
    void setDimention(int);
    void setDimention(int, int);
    void setScale(int);
    void setScale(int, int);
    void add(string);
    void add(int, string);
    void setTerminal(int);

    void setSuffix(int);
    void setLimbLabel(int);

    void makeGp();
    string makeCode(int);
    void addLoad();

    void setMainGpName(string);
    void makeMainGp();

    GpMaker();
    GpMaker(string);
    ~GpMaker();
  };
}
