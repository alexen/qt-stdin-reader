#pragma once

#include <QObject>

class StdinReader : public QObject {
     Q_OBJECT

public:
     StdinReader();
     ~StdinReader();

public slots:
     void start();
     void stop();

signals:
     void dataReceived( const QString& );
     void finished();
};
