reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Base orient. [deg]'

set output MODEL_EPS.'001_baseOrient.eps'

plot MODEL_DAT.'001_baseOrient.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*RAD2DEG) t '' w l ls 1,\
MODEL_DAT.'001_baseOrient.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*RAD2DEG) t '' w l ls 2,\
MODEL_DAT.'001_baseOrient.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*RAD2DEG) t '' w l ls 3

set terminal TERMINAL 1
if(VIEWMODE) replot

