/**
   @author Sho Miyahara 2017
*/

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <iomanip>

#include <limits>
// setprecision(numeric_limits<double>::max_digits10)

using namespace std;

using namespace Eigen;
typedef Eigen::Matrix<double, 6, 1> Vector6d;
typedef Eigen::Matrix<double, 6, 6> Matrix6d;

#define PI M_PI
#define DEG2RAD M_PI / 180.
#define RAD2DEG 180. * M_1_PI

// #define CONFIG "config"
#define CONFIG "rlsDynamics"
// #define CONFIG "master_rlsDynamics"
// #define CONFIG "temp"
#define LINK "/usr/local/etc/rls/sl/"

#define o(x) cout << #x << ":" << endl << setprecision(6) << scientific << x << endl
#define gc cout << endl << "Please hit any key to continue !!" << endl; getchar()
#define DEBUG cout << "************************************************" << endl \
  << "file:  " << __FILE__ << endl << "function:  " << __func__ << endl \
  << "************************************************" << endl;

namespace RLS{
  class Config{
  private:
    void readArgument(int, char**);
    void setDir();

    string def;

    // string path;

  public:
    string option;

    // smiyahara: この分け方びみょ Flagのcontrollerとdpとか
    // smiyahara: controllerの中のflagとかにしてflagは中に入れたい

    struct Compos{
      string cmp;
      string ind;
    };

    struct Dir{
      string link;
      string share;
      string cnoid;
      string body;
      string work;
      string result;
      string set;
      string cmp;
      Compos dat;
      Compos eps;
      Compos gp;
      Compos pdf;
      string interface;
    } dir;

    struct Result{
      Compos name;
    } result;

    struct Flag{
      bool shm;
      bool debug;
    } flag;

    struct Cnoid{
      string name;
    } cnoid;

    // smiyahara: コマンドライン引数の処理は未実装
    struct Body{
      string name;
    } body;

    struct Controller{
      bool flag;
      bool dynamics;
      string name;
      string input;
      string work;
      string driven;
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
      dir.link = LINK;
      flag.debug = false; // smiyahara:ココ定義の仕方びみょー
    }
    Config(int argc, char *argv[]){
      def = CONFIG;
      dir.link = LINK;
      flag.debug = false; // smiyahara:ココ定義の仕方びみょー

      readArgument(argc, argv);

      readConfig();
    }
  };
}
