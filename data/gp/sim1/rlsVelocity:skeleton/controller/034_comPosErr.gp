reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'CoM pos. err. [mm]'

set output CONTROLLER_EPS.'034_comPosErr.eps'

plot CONTROLLER_DAT.'034_comPosErr.dat' u 1:($2*K) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'034_comPosErr.dat' u 1:($3*K) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'034_comPosErr.dat' u 1:($4*K) t '' w l lw LINE_WIDTH

set terminal TERMINAL 0
if(VIEWMODE) replot

