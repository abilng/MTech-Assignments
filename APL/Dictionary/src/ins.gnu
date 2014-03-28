#! /usr/bin/env gnuplot

set term x11 persist
set title "Insert Timing";
RBT='< cat insRBT | sort -n ';
BST='< cat insBST | sort -n';

set xlabel "No of Elements"
set ylabel "Time (in s)"
#set key off

set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5   # --- blue
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5   # --- red

plot RBT using 1:2  with linespoints ls 2 title 'RBTree', \
	BST using 1:2  with linespoints ls 1 title 'BSTree'
