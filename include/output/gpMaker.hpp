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
    void initialize();

    // 要検討
    string timeLabelStr = "Time [s]";

    template<typename TYPE, std::size_t SIZE>
    std::size_t array_length(const TYPE (&)[SIZE]){return SIZE;}

    string limbName[5] = {
      "R. leg",
      "L. leg",
      "Torso",
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
    double tstart;

    string makeDashTimes();
    vector<double> tdash;
    int dashNum;
    bool flagX2;

    void makeMacro();
    void makeConfig();
    void makeSet();

    // gp maker
    string main_gp_name;
    string name;
    string suffix;
    int numLimb;
    string limbLabel;
    string xLabel;
    string yLabel;
    string unit;
    vector<bool> flag;
    vector<int> dimention;
    vector<string> scale;
    vector<int> exponent;
    vector<string> redef_str;
    vector<string> add_str;
    int terminal;

    int point;

  public:
    // library maker
    void setDatPath(string);
    void setEpsPath(string);
    void setDt(double);
    void setST(int);
    void setStartTime(double);
    void makeLibrary();
    void setDashTimes(vector<double>, int);

    void reset();
    void setGpPath(string);
    void setName(string);
    void setLimb(int);
    void setLimbNum(int, bool);
    void setXLabel(string);
    void setYLabel(string);
    void setUnit(string);
    void setDimention(int);
    void setDimention(int, int);
    void setScale(int);
    void setScale(int, int);
    void redef(string);
    void redef(int, string);
    void add(string);
    void add(int, string);
    void setTerminal(int);

    void setSuffix(int);
    void setLimbLabel(int);

    void makeGp();
    string makeCode(int);
    void addLoad();

    void setMainGpName();
    void makeMainGp();

    GpMaker();
    ~GpMaker();
  };
}
