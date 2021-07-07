#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>
#include <iostream>
#include <QTextStream>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

    static bool isEnabled;
    static QString logFile;
    static void enableLogger(bool enable);
    static void handler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

signals:

};

#endif // LOGGER_H
