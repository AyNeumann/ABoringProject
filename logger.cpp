#include "logger.h"

QString Logger::logFile = QDir::currentPath() + QDir::separator() + "log.txt";
bool Logger::isEnabled = false;
static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr);

Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::enableLogger(bool enable)
{
    Logger::isEnabled = enable;
    qInstallMessageHandler(Logger::handler);
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

        QFile file(Logger::logFile);
        if(file.open(QIODevice::Append))
        {
            QTextStream ts(&file);

            ts << QDateTime::currentDateTime().toString() << " " << logType << " --- [" << context.file << " in - " << context.function << " - at line " << context.line << "] " << msg << "\r\n";
            ts.flush();
            file.close();
        }
    }

    (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}
