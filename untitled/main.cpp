#include <QApplication>
#include "mainwindow.h"
#include <QOpenGLContext>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSplashScreen splashScreen(QPixmap( ":/res/title.png" ));
    splashScreen.show();
    MainWindow w;
    splashScreen.finish(&w);
    return a.exec();

}
