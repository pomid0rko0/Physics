#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "laboratory.h"
#include "plot.h"
#include "help.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QList<Plot*> plots;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_stop_clicked();
    void on_bullet_speed_action_triggered();
    void on_kinetic_energy_triggered();
    void on_potential_energy_triggered();
    void on_pos_triggered();
    void on_vel_triggered();
    void on_help_button_clicked();
    void on_instruction_triggered();
    void on_about_triggered();

    void on_exit_triggered();

private:
    Ui::MainWindow *ui;
    laboratory *lab = nullptr;
};

#endif // MAINWINDOW_H
