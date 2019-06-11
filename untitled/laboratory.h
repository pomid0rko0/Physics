#ifndef laboratory_H
#define laboratory_H

#include <Qt3DExtras>
#include <QObject>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include "measurer.h"
#include "Camera.h"
#include "plot.h"

class laboratory
{
private:
    Qt3DExtras::Qt3DWindow *w = nullptr;
    // камера (а точнее, контроллер камеры)
    Camera *cam = nullptr;
    //Qt3DExtras::QOrbitCameraController *cam = nullptr;

    Qt3DCore::QEntity       *root   = nullptr;

    // лаборатория
    Qt3DRender::QPointLight *light = nullptr;
    physics::object *lamp1    = nullptr;
    physics::object *lamp2    = nullptr;
    physics::object *lamp3    = nullptr;
    physics::object *lamp4    = nullptr;
    physics::object *world    = nullptr;
    physics::object *lab      = nullptr;
    physics::object *desk     = nullptr;
    physics::object *room     = nullptr;
    physics::object *items    = nullptr;
    physics::object *table    = nullptr;
    physics::object *cabinet1 = nullptr;
    physics::object *cabinet2 = nullptr;
    physics::object *curtain  = nullptr;


    physics ::bullet          *bullet   = nullptr;
    physics ::pendulum        *pendulum = nullptr;
    physics ::measurer        *measurer = nullptr;
    QPropertyAnimation        *B        = nullptr;
    QPropertyAnimation        *P        = nullptr;
    QPropertyAnimation        *M        = nullptr;
    QParallelAnimationGroup   *swing    = nullptr;
    QSequentialAnimationGroup *shoot    = nullptr;

    QCheckBox   *move_plot_checkbox   = nullptr;
    QVBoxLayout *opt                  = nullptr;
    QVBoxLayout *inf                  = nullptr;
    QSlider     *bullet_mass_slider   = nullptr;
    QSlider     *pendulum_mass_slider = nullptr;
    QSlider     *k_slider             = nullptr;
    QSlider     *b_slider             = nullptr;
    QLabel      *bullet_mass_label    = nullptr;
    QLabel      *pendulum_mass_label  = nullptr;
    QLabel      *k_label              = nullptr;
    QLabel      *b_label              = nullptr;
    QLabel      *move_label           = nullptr;
    QLabel      *speed_label          = nullptr;
    QLabel      *time_label           = nullptr;
    QPushButton *start_button         = nullptr;


public:
    laboratory();
    bool start_or_stop() const; // return true if started and return false if stopped

    float get_time()  const;
    QVBoxLayout *get_opt() const;
    QVBoxLayout *get_inf() const;
    Qt3DExtras::Qt3DWindow *get_window () const;

    Plot *make_kinetic_energy_plot(QWidget *parent) const;
    Plot *make_potential_energy_plot(QWidget *parent) const;
    Plot *make_position_plot(QWidget *parent) const;
    Plot *make_velocity_plot(QWidget *parent) const;
    Plot *make_velocity_mass_plot(QWidget *parent) const;
};

#endif // laboratory_H
