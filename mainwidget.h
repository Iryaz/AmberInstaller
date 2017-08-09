#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QFile>
#include <QWidget>
#include <QProcess>
#include <QDir>
#include <QThread>

#include "zipfile.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:

    const char* GAME_ARCHIVE = "pacman.zip";  // Имя архива
    const char* ARCHIVE_PASSWORD = "pacman";    // Пароль ко всем файлам архива
    const char* EXE_FILE = "\"Pacman 4000.exe\"";  // Имя запускаемого после распаковки файла
    const int DIR_NAME_LENGTH = 8;  // Количество символов в имени директории за исключением скобок

    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void extractArchive();
    void addExtractFileInLog(QString*);
    void extractFileFinish(QString*, ZipFile::EXTRACTING_STATUS);

private:
    Ui::MainWidget *ui;
    QString TMP_DIR;    // Полный путь к директории распаковки

    QString getRandomString() const ;
    QString createTempDir();
};

#endif // MAINWIDGET_H
