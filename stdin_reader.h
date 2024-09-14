#pragma once

#include <QObject>

class StdinReader : public QObject {
     Q_OBJECT

public:
     StdinReader();

signals:
     void dataReceived( const QByteArray& );
     void stdinClosed();
};

