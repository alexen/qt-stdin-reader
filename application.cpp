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
     emit finish();
     delete ui_;
     qInfo() << "Application destroyed, UI deleted";
}


void Application::run()
{
     qInfo() << "Starting working thread";

     StdinReader* stdinReader = new StdinReader;
     QThread* thread = new QThread;

     stdinReader->moveToThread( thread );

     connect( thread, SIGNAL(started()), stdinReader, SLOT(start()) );
     connect( stdinReader, SIGNAL(finished()), thread, SLOT(quit()));
     connect( this, SIGNAL(finish()), stdinReader, SLOT(stop()) );
     connect( stdinReader, SIGNAL(finished()), stdinReader, SLOT(deleteLater()) );
     connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

     connect( stdinReader, SIGNAL(dataReceived(const QString&)), ui_->textFromInput, SLOT(appendPlainText(const QString&)) );

     thread->start();
}
