reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb1 joint ang. [deg]'
set output MODEL_EPS.'010_jointAng.eps'

plot MODEL_DAT.'010_jointAng.dat' u 1:($2*RAD2DEG) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($3*RAD2DEG) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($4*RAD2DEG) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($5*RAD2DEG) t '4' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($6*RAD2DEG) t '5' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($7*RAD2DEG) t '6' w l lw LINE_WIDTH

set terminal TERMINAL 11
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 joint ang. [deg]'
set output MODEL_EPS.'010_jointAng.eps'

plot MODEL_DAT.'010_jointAng.dat' u 1:($8*RAD2DEG) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($9*RAD2DEG) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($10*RAD2DEG) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($11*RAD2DEG) t '4' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($12*RAD2DEG) t '5' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($13*RAD2DEG) t '6' w l lw LINE_WIDTH

set terminal TERMINAL 12
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 joint ang. [deg]'
set output MODEL_EPS.'010_jointAng.eps'

plot MODEL_DAT.'010_jointAng.dat' u 1:($14*RAD2DEG) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($15*RAD2DEG) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($16*RAD2DEG) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($17*RAD2DEG) t '4' w l lw LINE_WIDTH

set terminal TERMINAL 13
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 joint ang. [deg]'
set output MODEL_EPS.'010_jointAng.eps'

plot MODEL_DAT.'010_jointAng.dat' u 1:($18*RAD2DEG) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($19*RAD2DEG) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($20*RAD2DEG) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'010_jointAng.dat' u 1:($21*RAD2DEG) t '4' w l lw LINE_WIDTH

set terminal TERMINAL 14
if(VIEWMODE) replot


