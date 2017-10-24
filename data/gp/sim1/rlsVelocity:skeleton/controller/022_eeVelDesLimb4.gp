reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 desired EE vel. [m/s]'

set output CONTROLLER_EPS.'022_eeVelDesLimb4.eps'

plot CONTROLLER_DAT.'022_eeVelDesLimb4.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'022_eeVelDesLimb4.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'022_eeVelDesLimb4.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 20
if(VIEWMODE) replot

