reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 desired EE orient. [deg]'

set output CONTROLLER_EPS.'021_eeOrientDesLimb2.eps'

plot CONTROLLER_DAT.'021_eeOrientDesLimb2.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*RAD2DEG) t '' w l ls 1,\
CONTROLLER_DAT.'021_eeOrientDesLimb2.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*RAD2DEG) t '' w l ls 2,\
CONTROLLER_DAT.'021_eeOrientDesLimb2.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*RAD2DEG) t '' w l ls 3

set terminal TERMINAL 20
if(VIEWMODE) replot

