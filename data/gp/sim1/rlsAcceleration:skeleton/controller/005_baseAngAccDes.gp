reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Desired base ang. acc. [rad/s^2]'

set output CONTROLLER_EPS.'005_baseAngAccDes.eps'

plot CONTROLLER_DAT.'005_baseAngAccDes.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'005_baseAngAccDes.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'005_baseAngAccDes.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 0
if(VIEWMODE) replot

