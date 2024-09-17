#include "application.h"

#include <cstdio>
#include <cstring>
#include <iostream>

#include <QDebug>
#include <QSocketNotifier>

#include "ui_application.h"


Application::Application( QWidget *parent )
     : QMainWindow{ parent }
     , ui_{ new Ui::Application }
     , notifier_{ new QSocketNotifier{ fileno( stdin ), QSocketNotifier::Read, this } }
{
     qInfo() << "Application created, set up UI class";
     ui_->setupUi( this );

     show();
}


Application::~Application()
{
     delete notifier_;
     delete ui_;
     qInfo() << "Application destroyed, UI deleted";
}


void Application::run()
{
     qInfo() << "Starting working thread";
     connect(
          notifier_
          , SIGNAL(activated(int))
          , this
          , SLOT(readData())
          );
     connect(
          this
          , SIGNAL(dataReceived(const QString&))
          , ui_->textFromInput
          , SLOT(appendPlainText(const QString&))
          );
     connect(
          this
          , SIGNAL(inputStreamClosed())
          , this
          , SLOT(close())
          );
     connect(
          this
          , SIGNAL(inputStreamError(const QString&))
          , ui_->textForOutput
          , SLOT(setPlainText(const QString&))
          );
}


void Application::readData()
{
     qInfo() << "Reading data";
     char buffer[ 1024 ] = {};
     const auto ret = fread( buffer, 1, sizeof( buffer ), stdin );
     qInfo() << "Reading data: ret: " << ret;
     if( ret > 0 )
     {
          const std::string data{ buffer, ret };
          qInfo() << "Emit [dataReceived]: " << QString::fromStdString( data );
          emit dataReceived( QString::fromStdString( data ) );
     }
     else if( feof( stdin ) )
     {
          qInfo() << "Emit [inputStreamClosed]";
          emit inputStreamClosed();
     }
     else
     {
          qInfo() << "Emit [inputStreamError]";
          emit inputStreamError( QString{ strerror( errno ) } );
     }
}
