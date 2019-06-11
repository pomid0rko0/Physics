#ifndef PLOT_H
#define PLOT_H

#include <QMainWindow>
#include <qcustomplot.h>

namespace Ui {
class Plot;
}

class Plot : public QMainWindow
{
    Q_OBJECT

public:

    explicit Plot(std::function<double()> getarg, std::function<double()> getvalue,
                  QString args, QString values,
                  double args_start, double args_end,
                  double values_start, double values_end, QWidget *parent = nullptr);

    void Update();
    void BuildMySpecificPlot();
    void isFixed(bool fixed);

private:
    Ui::Plot *ui;

    std::function<double()> getarg;
    std::function<double()> getvalue;
    void Draw();

    double args_start, args_end, values_start, values_end;
    QCustomPlot *plot;
    QList<double> args;
    QList<double> values;
    bool _isFixed = true;

};

#endif
