#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QCloseEvent>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QThread>
#include <QWidget>

#include "fileclonerthread.h"
#include "zipfile.h"

namespace Ui {
class MainWidget;
}

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 450

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    const char* PROGRAM_TITLE = "AmberInstaller";
    const char* GAME_ARCHIVE = "pacman.zip";  // Имя архива
    const char* ARCHIVE_PASSWORD = "pacman";    // Пароль ко всем файлам архива
    const char* EXE_FILE = "\"Pacman 4000.exe\"";  // Имя запускаемого после распаковки файла
    const int DIR_NAME_LENGTH = 8;  // Количество символов в имени директории за исключением скобок

    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    void closeEvent(QCloseEvent* event);
    void setStatusText(const QString &statusText);

private slots:
    void extractArchive();
    void begin();
    void addExtractFileInLog(QString*);
    void extractFileFinish(QString*, int);
    void startGame();

private:
    Ui::MainWidget *ui;
    QString TMP_DIR;    // Полный путь к директории распаковки

    QString getRandomString() const;    // Сгенерировать случайную строку
    QString createTempDir();    // Создать временную директорию

    // Поток в котором происходит копирование архива
    ZipFile *zipThread;
    // Поток в котором происходит распаковка архива
    FileClonerThread *copyFileThread;
};

#endif // MAINWIDGET_H
