reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Base orient. [deg]'

set output MODEL_EPS.'001_baseOrient.eps'

plot MODEL_DAT.'001_baseOrient.dat' u 1:($2*RAD2DEG) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'001_baseOrient.dat' u 1:($3*RAD2DEG) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'001_baseOrient.dat' u 1:($4*RAD2DEG) t '' w l lw LINE_WIDTH

set terminal TERMINAL 1
if(VIEWMODE) replot

