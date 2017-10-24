reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Desired base orient. [deg]'

set output CONTROLLER_EPS.'001_baseOrientDes.eps'

plot CONTROLLER_DAT.'001_baseOrientDes.dat' u 1:($2*RAD2DEG) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'001_baseOrientDes.dat' u 1:($3*RAD2DEG) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'001_baseOrientDes.dat' u 1:($4*RAD2DEG) t '' w l lw LINE_WIDTH

set terminal TERMINAL 0
if(VIEWMODE) replot

