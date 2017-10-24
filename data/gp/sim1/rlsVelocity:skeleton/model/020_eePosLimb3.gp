reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 EE pos. [mm]'

set output MODEL_EPS.'020_eePosLimb3.eps'

plot MODEL_DAT.'020_eePosLimb3.dat' u 1:($2*K) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'020_eePosLimb3.dat' u 1:($3*K) t '' w l lw LINE_WIDTH,\
MODEL_DAT.'020_eePosLimb3.dat' u 1:($4*K) t '' w l lw LINE_WIDTH

set terminal TERMINAL 20
if(VIEWMODE) replot

