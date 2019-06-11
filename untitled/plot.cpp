#include "plot.h"
#include "ui_plot.h"
#include "mainwindow.h"

Plot::Plot(std::function<double()> getarg, std::function<double()> getvalue,
           QString args, QString values,
           double args_start, double args_end,
           double values_start, double values_end, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Plot),
    getarg(getarg),
    getvalue(getvalue),
    args_start(args_start),
    args_end(args_end),
    values_start(values_start),
    values_end(values_end)
{
    ui->setupUi(this);

    plot = ui->PlotSurface;

    plot->xAxis->setLabel(args);
    plot->yAxis->setLabel(values);

    plot->addGraph();
    plot->xAxis->setRange(double(args_start), double(args_end));
    plot->yAxis->setRange(double(values_start), double(values_end));

    plot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
    show();
}

void Plot::Update()
{
    args.append(getarg());
    values.append(getvalue());
    if (args.size() >= 250000)
    {
        args.removeAt(0);
        values.removeAt(0);
    }
    Draw();
}

void Plot::BuildMySpecificPlot()
{
    args.clear();
    values.clear();
    args.append(1./sqrt(20e-3));
    args.append(1./sqrt(5e-3));
    values.append(getvalue() / sqrt(20e-3));
    values.append(getvalue() / sqrt(5e-3));
    Draw();
}

void Plot::isFixed(bool fixed)
{
    _isFixed = fixed;
}

void Plot::Draw()
{
    plot->graph(0)->setData(args.toVector(), values.toVector(), true);
    double d = (args_end - args_start) / 10.;
    if (!_isFixed && args.last() > args_end - d)
        plot->xAxis->setRange(args.last() - args_end + args_start + d, args.last() + d);
    plot->replot();
}
