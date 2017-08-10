#include "zipfile.h"

#include <QDebug>
#include <QDir>

ZipFile::ZipFile(QObject *parent) : QThread(parent)
{
}

ZipFile::~ZipFile()
{
}

bool ZipFile::open(const QString& fileName)
{
    return open(fileName.toStdString().data());
}

bool ZipFile::open(const char *fileName)
{
    za = zip_open(fileName, 0, &error);
    if (za == NULL)
        return false;

    qDebug() << CLASS << " " << "Zip file open! - " << fileName;
    return true;
}

void ZipFile::run()
{
    extracting_(zipFile_, targetDir_, password_);
}

void ZipFile::extracting(const QString &zipFile, const QString &targetDir, const QString &password)
{
    setFileName(zipFile);
    setTargetDir(targetDir);
    setPassword(password);

    start();
}

void ZipFile::extracting_(const QString &zipFile, const QString &targetDir, const QString &password)
{
    if (open(zipFile)) {
        for (int i = 0; i < zip_get_num_entries(za, 0); i++) {
            struct zip_stat sb;
            zip_stat_index(za, i, 0, &sb);
            zip_file *zf;
            if (password.isEmpty())
                zf = zip_fopen_index(za, i, ZIP_FL_UNCHANGED);
            else
                zf = zip_fopen_index_encrypted(za, i, ZIP_FL_UNCHANGED, password.toStdString().data());

            if (!zf)
                qDebug() << CLASS <<"Error extracting file - " << sb.name;
            else {
                qDebug() << CLASS << "Extracting file - " << sb.name;
                if (sb.size != 0)
                    emit beginExtractFile(new QString(sb.name));
                if (sb.name[strlen(sb.name)-1] == '/') {
                    QDir dir(targetDir);
                    dir.mkdir(sb.name);
                    continue;
                }

                if (saveFile(targetDir, zf, &sb) == sb.size)
                    emit fileExtract(new QString(sb.name), EXTRACT_OK);
                else {
                    qDebug() << CLASS << "Error write file" << sb.name;
                    emit fileExtract(new QString(sb.name), EXTRACT_FAILED);
                }
            }
        }

        zip_close(za);
    }
}

uint64_t ZipFile::saveFile(const QString &targetDir, zip_file *file, struct zip_stat *stat)
{
    int writeByte = 0;
    uint_fast8_t* fileBuffer = NULL;

    try {
        fileBuffer = new uint8_t[stat->size];
    }
    catch (std::bad_alloc) {
        // Если память для файла выделить не получилось, то для него возвращается
        // статус не успешно !!! и он на диск не записывается
        qDebug () << CLASS << "Bad alloc !!!" << " " << "Size buffer: " << stat->size;
        return 0;
    }

    FILE *fd = fopen((targetDir + "/" + QString(stat->name)).toStdString().data(), "wb");
    if (!fd) {
        qDebug() << CLASS << "Error create file - " << stat->name;
        return 0;
    }

    zip_fread(file, fileBuffer, stat->size);
    writeByte = fwrite(fileBuffer, sizeof(uint_fast8_t), stat->size, fd);
    fclose(fd);

    delete[] fileBuffer;

    return writeByte;
}

QString ZipFile::Status2String(int s)
{
    QString ret = tr("OK");
    switch (s) {
    case EXTRACT_OK: tr("OK"); break;
    case EXTRACT_FAILED: ret = tr("FAILED"); break;
    }

    return ret;
}
