#include"../lib/drawchart.h"

Chart __constChart(const char *title,
                   const char *xLabel,
                   const char *yLabel,
                   const char *type,
                   const char *color,
                   const char *lineWidth,
                   int numCurves, Data data)
{
    Chart chart;

    chart.title = title;
    chart.xLabel = xLabel;
    chart.yLabel = yLabel;
    chart.type = type;
    chart.color = color;
    chart.lineWidth = lineWidth;
    chart.numCurves = numCurves;
    chart.data = data;

    return chart;
}

void drawChart(Chart chart)
{
    char cmd[200];
    // initPlotScript(chart.type);
    sprintf(cmd, "gnuplot -e \"file1=\'%s\'; data_separator=\'%s\'; chart_title=\'%s\'; line_w=\'%s\'; line_c=\'%s\'; x_label=\'%s\'; y_label=\'%s\'; num_curves=\'%d\';\" %s",
            chart.data.src1, chart.data.separator, chart.title, chart.lineWidth, chart.color, chart.xLabel, chart.yLabel, chart.numCurves, GNUPLOT_SCRIPT_PATH);
    system(cmd);
}