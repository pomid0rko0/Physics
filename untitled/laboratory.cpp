#include "laboratory.h"

laboratory::laboratory()
{
    root = new Qt3DCore::QEntity;

    light = new Qt3DRender::QPointLight;
    light->setColor(Qt::white);
    light->setIntensity(0.25f);

    world    = new physics::object(root);
    lamp1    = new physics::object(root);
    lamp2    = new physics::object(root);
    lamp3    = new physics::object(root);
    lamp4    = new physics::object(root);
    lab      = new physics::object(root);
    desk     = new physics::object(root);
    room     = new physics::object(root);
    items    = new physics::object(root);
    table    = new physics::object(root);
    cabinet1 = new physics::object(root);
    cabinet2 = new physics::object(root);
    curtain  = new physics::object(root);


    bullet      = new physics::bullet   (0.01f, root);
    pendulum    = new physics::pendulum (0.20f, bullet  , root);
    measurer    = new physics::measurer (0.01f, pendulum, root);
    B           = new QPropertyAnimation(bullet  , "time");
    P           = new QPropertyAnimation(pendulum, "time");
    M           = new QPropertyAnimation(measurer, "time");
    swing       = new QParallelAnimationGroup(root);
    shoot       = new QSequentialAnimationGroup(root);
    cam         = new Camera(root);
    //cam = new Qt3DExtras::QOrbitCameraController(root);
    w           = new Qt3DExtras::Qt3DWindow();
    opt         = new QVBoxLayout;
    inf         = new QVBoxLayout;


    // init laboratry
    QVector3D retranslation = { 0, -2.19f, 0 };

    world->setMesh(":/res/world.obj");
    world->setTexture(":/res/world.jpg");
    world->setPosition(retranslation);

    lamp1->setPosition(retranslation + QVector3D(-3.0f, 6, -3.0f));
    lamp1->entity()->addComponent(light);
    lamp2->setPosition(retranslation + QVector3D(-3.0f, 6,  3.0f));
    lamp2->entity()->addComponent(light);
    lamp3->setPosition(retranslation + QVector3D( 3.0f, 6, -3.0f));
    lamp3->entity()->addComponent(light);
    lamp4->setPosition(retranslation + QVector3D( 3.0f, 6,  3.0f));
    lamp4->entity()->addComponent(light);

    lab->setMesh(":/res/lab.obj");
    lab->setTexture(":/res/lab.png");
    lab->setPosition({ -0.13f, 0, 0 });

    desk->setMesh(":/res/desk.obj");
    desk->setTexture(":/res/desk.png");
    desk->setPosition(retranslation);

    room->setMesh(":/res/room.obj");
    room->setTexture(":/res/room.png");
    room->setPosition(retranslation);
    room->texture()->setAmbient(QColor(148, 148, 148));

    items->setMesh(":/res/items.obj");
    items->setTexture(":/res/items.png");
    items->setPosition(retranslation);

    table->setMesh(":/res/table.obj");
    table->setTexture(":/res/table.png");
    table->transform()->setRotationY(180);
    table->setPosition(retranslation + QVector3D(-2.4f, 0, 8));

    cabinet1->setMesh(":/res/cabinet1.obj");
    cabinet1->setTexture(":/res/cabinet1.png");
    cabinet1->setPosition(retranslation);

    cabinet2->setMesh(":/res/cabinet2.obj");
    cabinet2->setTexture(":/res/cabinet2.png");
    cabinet2->setPosition(retranslation);

    curtain->setMesh(":/res/curtain.obj");
    curtain->setTexture(":/res/curtain.png");
    curtain->setPosition(retranslation);
    curtain->texture()->setAlphaBlendingEnabled(true);


    bullet->setMesh(":/res/bullet.obj");
    bullet->setTexture(":/res/bullet.png");
    bullet->setPosition({ -2.6f, 0.33f, 1.13f });
    bullet->setScale(0.1f);
    bullet->set_r(bullet->transform()->translation());

    pendulum->setMesh(":/res/pendulum_bullet.obj");    // загрузить в память, чтобы не мигало при столкновении
    pendulum->setTexture(":/res/pendulum_bullet.png"); // загрузить в память, чтобы не мигало при столкновении
    pendulum->setMesh(":/res/pendulum.obj");
    pendulum->setTexture(":/res/pendulum.png");
    pendulum->setPosition({ -0.22f, 3.2f, 1.14f });
    pendulum->set_r(pendulum->transform()->translation());

    measurer->setMesh(":/res/measurer.obj");
    measurer->setTexture(":/res/measurer.png");
    measurer->setPosition({ 0.07f, 0.395f, 0.96f });
    measurer->set_r(measurer->transform()->translation());

    B->setStartValue(0);
    B->setLoopCount(1);

    P->setDuration(physics::duration * 1000); // измеряется в милисекундах
    P->setLoopCount(-1);
    P->setStartValue(0);
    P->setEndValue(physics::duration);

    M->setDuration(physics::duration * 1000);
    M->setLoopCount(-1);
    M->setStartValue(0);
    M->setEndValue(physics::duration);

    shoot->addAnimation(B);
    swing->addAnimation(P);
    swing->addAnimation(M);
    shoot->addAnimation(swing);

    w->setWindowState(Qt::WindowMaximized);
    w->setRootEntity(root);


    cam->setCamera(w->camera()); // прикрепить камеру к контроллеру
    cam->camera()->setPosition({ 0.5f, 1, 4.5f }); // начальное положение камеры
    cam->camera()->setViewCenter({ 0.5f, 1, 0.96f }); // точка, вокруг которой камера будет вращаться
    cam->setLookSpeed(100); // скорость вращения
    cam->setLinearSpeed(10); // скорость зума


    // init options
    move_plot_checkbox  = new QCheckBox("Фиксировать координатную сетку");
    bullet_mass_label   = new QLabel("");
    pendulum_mass_label = new QLabel("");
    k_label             = new QLabel("");
    b_label             = new QLabel("");
    move_label          = new QLabel("Смещение маятника: 0.000 м");
    speed_label         = new QLabel("Скорость пули: 00.000 м/с");
    time_label          = new QLabel("Время: 00:00:00.000");
    move_plot_checkbox  = new QCheckBox("Фиксировать координатну сетку на графиках");

    QObject::connect(pendulum, &physics::MaterialPoint::timeChanged, [&]() {
        QString text;
        float x = (measurer->transform()->translation() - measurer->r()).x() / 4;
        text.sprintf("Смещение маятника: %0.3f м", double(x));
        move_label->setText(text);
        text.sprintf("Скорость пули: %02.3f м/с", double(bullet->v(0).x()));
        speed_label->setText(text);
        int s = int(pendulum->getTime());
        int ms = int(1e3f * pendulum->getTime()) % 1000;
        text.sprintf("Время: %02d:%02d:%02d.%03d", s / 3600, s / 60 % 60, s % 60, ms);
        time_label->setText(text);
    });

    bullet_mass_slider = new QSlider(Qt::Horizontal);
    bullet_mass_slider->setRange(5, 20);
    bullet_mass_slider->setSingleStep(1);
    QObject::connect(bullet_mass_slider, &QSlider::valueChanged, [&](int v) {
        bullet->set_m(float(v) / 1e3f);
        QString text;
        text.sprintf("Масса пули: %0.3f кг", double(bullet->m()));
        bullet_mass_label->setText(text);
    });
    bullet_mass_slider->setValue(12);
    bullet_mass_slider->setObjectName("bullet_mass_slider");
    pendulum_mass_slider = new QSlider(Qt::Horizontal);
    pendulum_mass_slider->setRange(250, 500);
    pendulum_mass_slider->setSingleStep(1);
    QObject::connect(pendulum_mass_slider, &QSlider::valueChanged, [&](int v) {
        pendulum->set_m(float(v) / 1e3f);
        QString text;
        text.sprintf("Масса подвеса маятника: %0.3f кг", double(pendulum->m()));
        pendulum_mass_label->setText(text);
    });
    pendulum_mass_slider->setValue(375);
    k_slider = new QSlider(Qt::Horizontal);
    k_slider->setRange(12000, 13000);
    k_slider->setSingleStep(1);
    QObject::connect(k_slider, &QSlider::valueChanged, [&](int v) {
        bullet->set_k(float(v));
        QString text;
        text.sprintf("Жёсткость пружины: %05.0f Н/м", double(bullet->k()));
        k_label->setText(text);
    });
    k_slider->setValue(12500);
    k_slider->setObjectName("k_slider");
    b_slider = new QSlider(Qt::Horizontal);
    b_slider->setRange(15, 25);
    b_slider->setSingleStep(1);
    QObject::connect(b_slider, &QSlider::valueChanged, [&](int v) {
        bullet->set_b(float(v) / 1e3f);
        QString text;
        text.sprintf("Деформация пружины: %01.3f м", double(bullet->b()));
        b_label->setText(text);
    });
    b_slider->setValue(20);
    b_slider->setObjectName("b_slider");

    move_plot_checkbox->setCheckState(Qt::CheckState::Checked);

    inf->addWidget(new QLabel("<center><h3>Информационная панель</h3></center>"));
    inf->addWidget(move_label);
    inf->addWidget(speed_label);
    inf->addWidget(time_label);

    opt->addWidget(new QLabel("<center><h3>Панель управления</h3></center>"));
    opt->addWidget(bullet_mass_label);
    opt->addWidget(bullet_mass_slider);
    opt->addWidget(pendulum_mass_label);
    opt->addWidget(pendulum_mass_slider);
    opt->addWidget(k_label);
    opt->addWidget(k_slider);
    opt->addWidget(b_label);
    opt->addWidget(b_slider);
    opt->addWidget(move_plot_checkbox);
}

bool laboratory::start_or_stop() const
{
    if (shoot->state() == QParallelAnimationGroup::State::Running) {
        shoot->stop();
        pendulum->setTime(0);
        pendulum->move(0);
        pendulum->setMesh(":/res/pendulum.obj");
        pendulum->setTexture(":/res/pendulum.png");
        measurer->move(0);
        bullet->move(0);
        return false;
    }
    else {
        float t = physics::d / bullet->v(0).x();
        B->setDuration(int(t * 1e3f));
        B->setEndValue(t);
        shoot->start();
        return true;
    }
}

float laboratory::get_time() const
{
    return pendulum->getTime();
}

QVBoxLayout *laboratory::get_opt() const
{
    return opt;
}

QVBoxLayout *laboratory::get_inf() const
{
    return inf;
}

Qt3DExtras::Qt3DWindow *laboratory::get_window() const
{
    return w;
}

Plot *laboratory::make_kinetic_energy_plot(QWidget *parent) const
{
    Plot *plot = new Plot(
                [this]()->double{ return double(get_time()); },
                [this]()->double{ return double(pendulum->Ek(get_time())); },
                "Время, с", "Кинетическая энергия, Дж",
                double(get_time()), double(get_time() + 2.f * physics::T),
                0, double(pendulum->Ek(0)), parent
                );
    plot->setWindowTitle("График кинетической энергии маятника");
    QObject::connect(pendulum, &physics::MaterialPoint::timeChanged, plot, &Plot::Update);
    plot->isFixed(move_plot_checkbox->isChecked());
    QObject::connect(move_plot_checkbox, &QCheckBox::toggled, plot, &Plot::isFixed);

    return plot;
}

Plot *laboratory::make_potential_energy_plot(QWidget *parent) const
{
    Plot *plot = new Plot(
                [this]()->double{ return double(get_time()); },
                [this]()->double{ return double(pendulum->Ep(get_time())); },
                "Время, с", "Потенциальная энергия, Дж",
                double(get_time()), double(get_time() + 2.f * physics::T),
                0, double(pendulum->Ek(0)), parent
                );
    plot->setWindowTitle("График потенциальной энергии маятника");
    QObject::connect(pendulum, &physics::MaterialPoint::timeChanged, plot, &Plot::Update);
    plot->isFixed(move_plot_checkbox->isChecked());
    QObject::connect(move_plot_checkbox, &QCheckBox::toggled, plot, &Plot::isFixed);

    return plot;
}

Plot *laboratory::make_position_plot(QWidget *parent) const
{
    Plot *plot = new Plot(
                [this]()->double{ return double(get_time()); },
                [this]()->double{ return double(asinf(pendulum->pos(get_time()).x() / physics::l)); },
                "Время, с", "Отклонение маятника, рад",
                double(get_time()), double(get_time() + 2.f * physics::T),
                -M_PI_2, M_PI_2, parent
                );
    plot->setWindowTitle("График отклонения маятника от положения равновесия");
    QObject::connect(pendulum, &physics::MaterialPoint::timeChanged, plot, &Plot::Update);
    plot->isFixed(move_plot_checkbox->isChecked());
    QObject::connect(move_plot_checkbox, &QCheckBox::toggled, plot, &Plot::isFixed);

    return plot;
}

Plot *laboratory::make_velocity_plot(QWidget *parent) const
{
    Plot *plot = new Plot(
                [this]()->double{ return double(get_time()); },
                [this]()->double{
                    float t = get_time();
                    return double(pendulum->v(t).length() / physics::l *
                                      pendulum->v(t).x() /
                                  abs(pendulum->v(t).x())); },
                "Время, с", "Угловая скорость, рад/с",
                double(get_time()), double(get_time() + 2.f * physics::T),
                -M_PI_2, M_PI_2, parent
                );
    plot->setWindowTitle("График угловой скорости маятника");
    QObject::connect(pendulum, &physics::MaterialPoint::timeChanged, plot, &Plot::Update);
    plot->isFixed(move_plot_checkbox->isChecked());
    QObject::connect(move_plot_checkbox, &QCheckBox::toggled, plot, &Plot::isFixed);

    return plot;
}

Plot *laboratory::make_velocity_mass_plot(QWidget *parent) const
{
    Plot *plot = new Plot(
                []()->double{ return 0.; },
                [this]()->double{ return double(bullet->b() * sqrtf(bullet->k())); },
                "Обратный корень из массы пули, кг^(-1/2)", "Скорость пули, м/с",
                0, 20,
                0, 45, parent
                );
    plot->setWindowTitle("График скорости пули от обратного квадратного корная массы пули");
    plot->BuildMySpecificPlot();
    QObject::connect(b_slider, &QSlider::valueChanged, plot, &Plot::BuildMySpecificPlot);
    QObject::connect(k_slider, &QSlider::valueChanged, plot, &Plot::BuildMySpecificPlot);

    return plot;
}
