reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Desired base pos. [mm]'

set output CONTROLLER_EPS.'000_basePosDes.eps'

plot CONTROLLER_DAT.'000_basePosDes.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*K) t '' w l ls 1,\
CONTROLLER_DAT.'000_basePosDes.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*K) t '' w l ls 2,\
CONTROLLER_DAT.'000_basePosDes.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*K) t '' w l ls 3

set terminal TERMINAL 0
if(VIEWMODE) replot

