#include "application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     Application application;
     application.run();
     return a.exec();
}
