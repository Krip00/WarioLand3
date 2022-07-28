#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    (new WL3::MainWindow())->show();

    return app.exec();
}
