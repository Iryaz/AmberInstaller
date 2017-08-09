#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <QObject>
#include <QString>

#define ZIP_STATIC
#include "zip.h"

class ZipFile : public QObject
{
    Q_OBJECT

public:
    enum EXTRACTING_STATUS {
        EXTRACT_OK = 0,
        EXTRACT_FAILED = -1
    };

    const char* CLASS = "<ZipFile>";

    static QString Status2String(EXTRACTING_STATUS s);

    ZipFile();
    ~ZipFile();
    bool open(const char* fileName);
    bool open(QString fileName);

public slots:
    void extracting(QString zipFile, QString targetDir = "./", QString password = "");

signals:
    void beginExtractFile(QString* fileName);   // Файл готов к распаковки
    void fileExtract(QString* fileName, ZipFile::EXTRACTING_STATUS status); // Файл распакован

protected:
    zip_t *za;
    int error;

private:
    uint64_t saveFile(QString targetDir, zip_file* file, struct zip_stat *stat);
};

#endif // ZIPFILE_H
