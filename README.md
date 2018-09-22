collatz_traj_all_seeds.cpp -- lists of starting and ending numbers for all partial
Collatz trajectories up to a length given in the command line argument.

To compile with gcc:
```
gcc -std=c++11 -O3 collatz_traj_all_seeds.cpp -o collatz_traj_all_seeds
```

To run:
```
collatz_traj_all_seeds <max_trajectory_length>
```

All starting numbers for a given (partial) trajectory of length L have
the form `2^L*r - c`. Ending numbers have the form `3^N1*r - d`, where N1 is
the number of "ups" in the trajectory. The Collatz iteration is defined
by immediate division by 2 if the current iterate is odd after `3*x+1`
is applied:
```
         /
        |       x / 2, if x is even
T(x) = <
        | (3*x+1) / 2, if x is odd
         \
```
A trajectory is presented as a 0-1 sequence, where 0 means down (even iterate),
and 1 means up (odd iterate). Plug any r>0 to get a number producing the trajectory.

Example:
```
$ collatz_traj_all_seeds 4
0 2*r+0 to 1*r+0
1 2*r-1 to 3*r-1
00 4*r+0 to 1*r+0
01 4*r-2 to 3*r-1
10 4*r-3 to 3*r-2
11 4*r-1 to 9*r-1
000 8*r+0 to 1*r+0
001 8*r-4 to 3*r-1
010 8*r-6 to 3*r-2
011 8*r-2 to 9*r-1
100 8*r-3 to 3*r-1
101 8*r-7 to 9*r-7
110 8*r-5 to 9*r-5
111 8*r-1 to 27*r-1
0000 16*r+0 to 1*r+0
0001 16*r-8 to 3*r-1
0010 16*r-12 to 3*r-2
0011 16*r-4 to 9*r-1
0100 16*r-6 to 3*r-1
0101 16*r-14 to 9*r-7
0110 16*r-10 to 9*r-5
0111 16*r-2 to 27*r-1
1000 16*r-11 to 3*r-2
1001 16*r-3 to 9*r-1
1010 16*r-15 to 9*r-8
1011 16*r-7 to 27*r-10
1100 16*r-13 to 9*r-7
1101 16*r-5 to 27*r-7
1110 16*r-9 to 27*r-14
1111 16*r-1 to 81*r-1
```