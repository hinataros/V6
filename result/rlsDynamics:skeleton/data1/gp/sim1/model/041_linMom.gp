reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Linear momentum. [Ns]'

set output MODEL_EPS.'041_linMom.eps'

plot MODEL_DAT.'041_linMom.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '' w l ls 1,\
MODEL_DAT.'041_linMom.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '' w l ls 2,\
MODEL_DAT.'041_linMom.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '' w l ls 3

set terminal TERMINAL 0
if(VIEWMODE) replot

