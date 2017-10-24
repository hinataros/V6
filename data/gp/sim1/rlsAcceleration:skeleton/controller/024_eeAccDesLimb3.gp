reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 desired EE acc. [m/s^2]'

set output CONTROLLER_EPS.'024_eeAccDesLimb3.eps'

plot CONTROLLER_DAT.'024_eeAccDesLimb3.dat' u 1:($2*E) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'024_eeAccDesLimb3.dat' u 1:($3*E) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'024_eeAccDesLimb3.dat' u 1:($4*E) t '' w l lw LINE_WIDTH

set terminal TERMINAL 20
if(VIEWMODE) replot

