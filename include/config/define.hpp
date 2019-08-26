/**
   @author Sho Miyahara 2018
*/

#define PI M_PI
#define DEG2RAD M_PI / 180.
#define RAD2DEG 180. * M_1_PI

#define o(x) cout << #x << ":" << endl << setprecision(6) << scientific << x << endl
#define so(x) cout << #x << ":" << x.rows() << " × " << x.cols() << endl
#define gc cout << endl << "Please hit any key to continue !!" << endl; getchar()

#define tw(X) \
do{\
  struct timespec start,finish;\
  clock_gettime(CLOCK_REALTIME, &start);\
  X;\
  clock_gettime(CLOCK_REALTIME, &finish);\
  double ptime = (finish.tv_nsec - start.tv_nsec)*1e-6 + (finish.tv_sec - start.tv_sec)*1e+3;\
  cout << "Process time::" << #X << " = " << ptime <<" ms" << endl;\
}while(0)

#define DEBUG cout << "************************************************" << endl \
  << "file:  " << __FILE__ << endl << "function:  " << __func__ << endl \
  << "************************************************" << endl;
