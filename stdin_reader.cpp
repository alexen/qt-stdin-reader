#include "stdin_reader.h"

#include <iostream>
#include <QDebug>


StdinReader::StdinReader()
{
     qInfo() << "StdinReader created";
}


StdinReader::~StdinReader()
{
     qInfo() << "StdinReader destroyed";
}


void StdinReader::start()
{
     qInfo() << "StdinReader start working...";
     std::string input;
     while( std::getline( std::cin, input ) )
     {
          emit dataReceived( QString::fromStdString( input ) );
     }
     if( std::cin.eof() )
     {
          qInfo() << "Input stream has been closed";
     }
     emit finished();
}
