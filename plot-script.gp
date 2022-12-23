set datafile separator data_separator
set title chart_title


set xlabel x_label
set ylabel y_label
set format y '%.2f'    
set grid
plot for [i=1:num_curves] file1 using 1:(column(2*i)) w lines lw line_w lc 3*i
# plot file1 using 1:2:4 w lines lw line_w lc line_c
pause mouse keypress