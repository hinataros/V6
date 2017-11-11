#include <iostream>
#include <eigen3/Eigen/Dense>
#include <iomanip>

#include <limits>

using namespace std;

using namespace Eigen;
typedef Eigen::Matrix<double, 6, 1> Vector6d;
typedef Eigen::Matrix<double, 6, 6> Matrix6d;

#define PI M_PI
#define DEG2RAD M_PI / 180.
#define RAD2DEG 180. * M_1_PI

// #define CONFIG "config"
#define CONFIG "config"
#define LINK "/usr/local/etc/rls/sl/"

#define o(x) cout << #x << ":" << endl << setprecision(6) << scientific << x << endl
#define pause cout << endl << "Please hit any key to continue !!" << endl; getchar()
#define DEBUG cout << "************************************************" << endl \
  << "file:  " << __FILE__ << endl << "function:  " << __func__ << endl \
  << "************************************************" << endl;

namespace RLS{
  class Config{
  private:
    void readArgument(int, char**);
    string def;

    string path;

  public:
    string name;
    string link;
    string option;

    // smiyahara: この分け方びみょ Flagのcontrollerとdpとか
    // smiyahara: controllerの中のflagとかにしてflagは中に入れたい
    struct Flag{
      bool debug;
    } flag;

    // smiyahara: コマンドライン引数の処理は未実装
    struct Model{
      string name;
    } model;

    struct Solver{
      string input;
    } solver;

    struct Controller{
      bool flag;
      bool dynamics;
      string name;
      string work;
    } controller;

    struct Graph{
      bool flag;
      bool check;
      bool gp;
      bool tex;
      int st;
    } graph;

    struct Plane{
      bool flag;
      string xMin;
      string xMax;
      string yMin;
      string yMax;
      string zMin;
      string zMax;
    };

    struct Gif{
      bool flag;
      int st;
      string linkColor;
      string jointColor;
      bool terminal;
      bool dir;
      Plane yz;
      Plane xz;
      Plane xy;
      Plane all;
    } gif;

    struct Choreonoid{
      bool flag;
      int st;
    } cho;

    void readConfig();

    Config(){
      def = CONFIG;
      link = LINK;
      flag.debug = false; // smiyahara:ココ定義の仕方びみょー
    }
    Config(int argc, char *argv[]){
      def = CONFIG;
      link = LINK;
      flag.debug = false; // smiyahara:ココ定義の仕方びみょー

      readArgument(argc, argv);

      readConfig();
    }
  };
}
