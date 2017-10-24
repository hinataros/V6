reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb1 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVel.eps'

plot MODEL_DAT.'011_jointVel.dat' u 1:($2*E) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($3*E) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($4*E) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($5*E) t '4' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($6*E) t '5' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($7*E) t '6' w l lw LINE_WIDTH

set terminal TERMINAL 16
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVel.eps'

plot MODEL_DAT.'011_jointVel.dat' u 1:($8*E) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($9*E) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($10*E) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($11*E) t '4' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($12*E) t '5' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($13*E) t '6' w l lw LINE_WIDTH

set terminal TERMINAL 17
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVel.eps'

plot MODEL_DAT.'011_jointVel.dat' u 1:($14*E) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($15*E) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($16*E) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($17*E) t '4' w l lw LINE_WIDTH

set terminal TERMINAL 18
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 joint vel. [rad/s]'
set output MODEL_EPS.'011_jointVel.eps'

plot MODEL_DAT.'011_jointVel.dat' u 1:($18*E) t '1' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($19*E) t '2' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($20*E) t '3' w l lw LINE_WIDTH,\
MODEL_DAT.'011_jointVel.dat' u 1:($21*E) t '4' w l lw LINE_WIDTH

set terminal TERMINAL 19
if(VIEWMODE) replot


