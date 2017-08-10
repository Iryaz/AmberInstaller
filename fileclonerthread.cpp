#include "fileclonerthread.h"

FileClonerThread::FileClonerThread(QObject* parent) : QThread(parent)
{
    lastStatus_ = FILE_COPY_FAILED;
}

void FileClonerThread::copyFile(const QString& srcFile, const QString& dstFile)
{
    srcFile_ = srcFile;
    dstFile_ = dstFile;
    this->start();
}

void FileClonerThread::run()
{
    QFile f(srcFile_);

    if (f.copy(dstFile_)) {
        emit finishFileCopy(FILE_COPY_OK);
        lastStatus_ = FILE_COPY_OK;
    }
    else {
        emit finishFileCopy(FILE_COPY_FAILED);
        lastStatus_ = FILE_COPY_FAILED;
    }
}

QString FileClonerThread::Status2String(int s)
{
    QString ret = tr("OK");
    switch (s) {
    case FILE_COPY_OK: tr("OK"); break;
    case FILE_COPY_FAILED: ret = tr("FAILED"); break;
    }

    return ret;
}
