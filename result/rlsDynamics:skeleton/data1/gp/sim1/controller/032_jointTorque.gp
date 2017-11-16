reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb1 Joint torque [Nm]'
set output CONTROLLER_EPS.'032_jointTorqueLimb1.eps'

plot CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($2*E) t '1' w l ls 1,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($3*E) t '2' w l ls 2,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($4*E) t '3' w l ls 3,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($5*E) t '4' w l ls 4,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($6*E) t '5' w l ls 5,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($7*E) t '6' w l ls 6

set terminal TERMINAL 1
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb2 Joint torque [Nm]'
set output CONTROLLER_EPS.'032_jointTorqueLimb2.eps'

plot CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($8*E) t '1' w l ls 1,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($9*E) t '2' w l ls 2,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($10*E) t '3' w l ls 3,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($11*E) t '4' w l ls 4,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($12*E) t '5' w l ls 5,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($13*E) t '6' w l ls 6

set terminal TERMINAL 2
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb3 Joint torque [Nm]'
set output CONTROLLER_EPS.'032_jointTorqueLimb3.eps'

plot CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($14*E) t '1' w l ls 1,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($15*E) t '2' w l ls 2,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($16*E) t '3' w l ls 3,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($17*E) t '4' w l ls 4

set terminal TERMINAL 3
if(VIEWMODE) replot


reset
load 'library/config.gp'
load 'library/macro.gp'
load 'library/set.gp'

set xlabel 'Time [s]'
set ylabel 'Limb4 Joint torque [Nm]'
set output CONTROLLER_EPS.'032_jointTorqueLimb4.eps'

plot CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($18*E) t '1' w l ls 1,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($19*E) t '2' w l ls 2,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($20*E) t '3' w l ls 3,\
CONTROLLER_DAT.'032_jointTorque.dat' every ::(T_OFFSET*SAMPLING) u ($1-T_OFFSET):($21*E) t '4' w l ls 4

set terminal TERMINAL 4
if(VIEWMODE) replot


