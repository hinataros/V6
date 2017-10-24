reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 desired EE pos. [mm]'

set output CONTROLLER_EPS.'020_eePosDesLimb2.eps'

plot CONTROLLER_DAT.'020_eePosDesLimb2.dat' u 1:($2*K) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'020_eePosDesLimb2.dat' u 1:($3*K) t '' w l lw LINE_WIDTH,\
CONTROLLER_DAT.'020_eePosDesLimb2.dat' u 1:($4*K) t '' w l lw LINE_WIDTH

set terminal TERMINAL 20
if(VIEWMODE) replot

