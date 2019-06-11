#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    std::chrono::high_resolution_clock t;
    auto s = t.now();

    ui->setupUi(this);
    setWindowState(Qt::WindowState::WindowMaximized);
    lab = new laboratory;
    ui->layout->insertWidget(0, createWindowContainer(lab->get_window(), ui->centralWidget));
    ui->inf->setLayout(lab->get_inf());
    ui->opt->setLayout(lab->get_opt());

    auto e = t.now();
    auto d = std::chrono::duration<double, std::milli>(e - s).count();
    if (d < 2e3) {
        QThread::msleep(uint(2e3 - d));
    }
    show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_stop_clicked()
{
    if (lab->start_or_stop()) {
        ui->start_stop->setText("Остановить эксперимент");
    }
    else {
        ui->start_stop->setText("Начать эксперимент");
    }
}

void MainWindow::on_bullet_speed_action_triggered()
{
    lab->make_velocity_mass_plot(this);
}

void MainWindow::on_kinetic_energy_triggered()
{
    lab->make_kinetic_energy_plot(this);
}

void MainWindow::on_potential_energy_triggered()
{
    lab->make_potential_energy_plot(this);
}

void MainWindow::on_pos_triggered()
{
    lab->make_position_plot(this);
}

void MainWindow::on_vel_triggered()
{
    lab->make_velocity_plot(this);
}

void MainWindow::on_about_triggered()
{
    new help(0, this);
}

void MainWindow::on_instruction_triggered()
{
    new help(1, this);
}

void MainWindow::on_help_button_clicked()
{
    new help(2, this);
}

void MainWindow::on_exit_triggered()
{
    close();
}
