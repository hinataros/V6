reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 desired EE orient. [deg]'

set output CONTROLLER_EPS.'021_eeOrientDesLimb2.eps'

plot CONTROLLER_DAT.'021_eeOrientDesLimb2.dat' u 1:($2*RAD2DEG) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'021_eeOrientDesLimb2.dat' u 1:($3*RAD2DEG) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'021_eeOrientDesLimb2.dat' u 1:($4*RAD2DEG) t '' w l lw LINE_WIDTH

set terminal TERMINAL 20
if(VIEWMODE) replot

