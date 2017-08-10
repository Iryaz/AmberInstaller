#ifndef FILECLONERTHREAD_H
#define FILECLONERTHREAD_H

#include <QFile>
#include <QThread>

#define FILE_COPY_OK 0
#define FILE_COPY_FAILED -1

class FileClonerThread : public QThread
{
    Q_OBJECT

public:

    const char* CLASS = "<FileClonerThread>";

    static QString Status2String(int s);

    FileClonerThread(QObject* parent = 0);
    void copyFile(const QString& srcFile, const QString& dstFile);
    int getStatus() { return lastStatus_; }
    QString getSrcFileName() { return srcFile_; }
    QString getDstFileName() { return dstFile_; }

signals:
    void finishFileCopy(int status);

private:
    void run() Q_DECL_OVERRIDE;

    QString srcFile_;
    QString dstFile_;
    int lastStatus_;
};

#endif // FILECLONERTHREAD_H
