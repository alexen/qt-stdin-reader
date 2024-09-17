#include "application.h"
#include "./ui_application.h"

#include <memory>

#include <QDebug>
#include <QThread>

#include "stdin_reader.h"


Application::Application(QWidget *parent)
     : QMainWindow(parent)
     , ui_(new Ui::Application)
{
     qInfo() << "Application created, set up UI class";
     ui_->setupUi(this);

     show();
}


Application::~Application()
{
     delete ui_;
     qInfo() << "Application destroyed, UI deleted";
}


void Application::run()
{
     qInfo() << "Starting working thread";

     StdinReader* stdinReader = new StdinReader;
     QThreadDebug* thread = new QThreadDebug;

     stdinReader->moveToThread( thread );

     /// Вызов необходим для старта потокового воркера
     connect( thread, SIGNAL(started()), stdinReader, SLOT(start()) );
     /// Вызов необходим для корректного выключения? потока
     connect( stdinReader, SIGNAL(finished()), thread, SLOT(quit()) );
     /// Необходим для корректного удаления объекта класса StdinReader
     connect( stdinReader, SIGNAL(finished()), stdinReader, SLOT(deleteLater()) );
     /// Необходим для корректного удаления объекта класса QThread
     connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );

     connect(
          stdinReader
          , SIGNAL(dataReceived(const QString&))
          , ui_->textFromInput
          , SLOT(appendPlainText(const QString&))
          );

     thread->start();
}
