reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 EE orient. [deg]'

set output MODEL_EPS.'021_eeOrientLimb2.eps'

plot MODEL_DAT.'021_eeOrientLimb2.dat' u 1:($2*RAD2DEG) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'021_eeOrientLimb2.dat' u 1:($3*RAD2DEG) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'021_eeOrientLimb2.dat' u 1:($4*RAD2DEG) t '' w l lw LINE_WIDTH

set terminal TERMINAL 21
if(VIEWMODE) replot

