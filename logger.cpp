#include "logger.h"

QDir Logger::logDir;
QFile Logger::log;
QString Logger::logDirPath = QDir::currentPath() + QDir::separator() + "logs";
QString Logger::logFile = Logger::logDirPath + QDir::separator() + "log.txt";
bool Logger::isEnabled = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

Logger::Logger(QObject *parent) : QObject(parent)
{

}

Logger::~Logger()
{
    qDebug() << "Deconstructing Logger class";
    log.close();
}

void Logger::intializeLogFile()
{
    qDebug() << "Initialize log file";

    if(!logDir.path().isEmpty())
    {
        logDir.mkdir(Logger::logDirPath);
    }

    if(!log.isOpen())
    {
        log.setFileName(Logger::logFile);
        if(log.open(QIODevice::Append))
        {
            qDebug() << "Log file opened";
        }
        else
        {
            qCritical() << "Log file could not be opened";
        }
    }
}

void Logger::enableLogger(bool enable)
{
    Logger::isEnabled = enable;
    if(Logger::isEnabled)
    {
        qInstallMessageHandler(Logger::handler);
        intializeLogFile();
    }
    else
    {
        qInstallMessageHandler(nullptr);
    }
}

void Logger::handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if(Logger::isEnabled)
    {
        QString logType;
        switch (type) {
        case QtDebugMsg:
            logType = QString("DEBUG");
            break;
        case QtInfoMsg:
            logType = QString("INFO");
            break;
        case QtWarningMsg:
            logType = QString("WARN");
            break;
        case QtCriticalMsg:
            logType = QString("CRITICAL");
            break;
        case QtFatalMsg:
            logType = QString("FATAL");
            break;
        }


        QTextStream ts(&log);

        ts << QDateTime::currentDateTime().toString() << " " << logType << " --- [" << context.file << " in - " << context.function << " - at line " << context.line << "] " << msg << "\r\n";
        ts.flush();
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}
