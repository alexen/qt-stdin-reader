#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class QSocketNotifier;

class Application : public QMainWindow {
     Q_OBJECT
public:
     Application( QWidget *parent = nullptr );
     ~Application();

     void run();

signals:
     void dataReceived( const QString& );
     void inputStreamClosed();
     void inputStreamError( const QString& );

private slots:
     void readData();

private:
     Ui::Application *ui_ = {};
     QSocketNotifier* notifier_ = {};
};
