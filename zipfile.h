#ifndef ZIPFILE_H
#define ZIPFILE_H

#include <QObject>
#include <QString>
#include <QThread>

#define ZIP_STATIC
#include "zip.h"

#define EXTRACT_OK 0
#define EXTRACT_FAILED -1

/*
 * Сам класс который распаковывает архив в отдельном потоке
 * Для распаковки архива используются функции библиотеки libzip
 * Перед началом распаковки класс отправляет сигнал beginExtractFile
 * После того как файл рапакован, отправляется сигнал fileExtract, с которого
 * можно считать как прошла распаковка файла (Успешно или Нет).
 * При распаковки архива пароль вводится один для всех файлов архива,
 * если какой либо файл имеет другой пароль, то он не распаковывается.
*/

class ZipFile : public QThread
{
    Q_OBJECT

public:
    const char* CLASS = "<ZipFile>";

    static QString Status2String(int s);

    ZipFile(QObject *parent);
    ~ZipFile();
    bool open(const char* fileName);
    bool open(const QString &fileName);

    void setTargetDir(const QString& targetDir) { targetDir_ = targetDir; }
    void setPassword(const QString& password) { password_ = password; }
    void setFileName(const QString& name) { zipFile_ = name; }

public slots:
    void extracting(const QString& zipFile, const QString& targetDir = "./", const QString& password = "");

signals:
    void beginExtractFile(QString* fileName);            // Файл готов к распаковки
    void fileExtract(QString* fileName, int statusCode); // Файл распакован

protected:
    zip_t *za;
    int error;

    void extracting_(const QString& zipFile, const QString& targetDir = "./", const QString& password = "");

private:
    QString targetDir_;
    QString password_;
    QString zipFile_;
    void run() Q_DECL_OVERRIDE;

    // Записать считанный файл из архива на диск
    // Функция не сохраняет на диск файлы слишком большого размера !!!!!!!
    // Этот момент не реализован, так как функция выделяет один буфер под размер файла.
    // Ограничение на размер файла зависят от размера ОЗУ !!!!!!!
    uint64_t saveFile(const QString& targetDir, zip_file* file, struct zip_stat *stat);
};

#endif // ZIPFILE_H
