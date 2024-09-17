#pragma once

#include <QMainWindow>
#include <QThread>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE


class QThreadDebug : public QThread {
     Q_OBJECT
public:
     QThreadDebug() : QThread{} {
          qInfo() << "Thread (debug) created";
     }
     ~QThreadDebug() {
          qInfo() << "Thread (debug) destroyed";
     }
};


class Application : public QMainWindow
{
     Q_OBJECT
public:
     Application(QWidget *parent = nullptr);
     ~Application();

     void run();

signals:
     void finish();

private:
     Ui::Application *ui_;
};
