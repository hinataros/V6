reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 desired EE vel. [m/s]'

set output CONTROLLER_EPS.'022_eeVelDesLimb4.eps'

plot CONTROLLER_DAT.'022_eeVelDesLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '' w l ls 1,\
CONTROLLER_DAT.'022_eeVelDesLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '' w l ls 2,\
CONTROLLER_DAT.'022_eeVelDesLimb4.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '' w l ls 3

set terminal TERMINAL 20
if(VIEWMODE) replot

