#include "help.h"
#include "ui_help.h"


help::help(int t, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    QFile f;
    switch (t) {
    case 0:
        f.setFileName(":/res/about.txt");
        break;
    case 1:
        f.setFileName(":/res/inst.txt");
        break;
    case 2:
        f.setFileName(":/res/help.txt");
        break;
    }
    f.open(QFile::ReadOnly);
    ui->label->setText(f.readAll());
    show();
}

help::~help()
{
    delete this->ui;
}

void help::on_pushButton_clicked()
{
    close();
}
