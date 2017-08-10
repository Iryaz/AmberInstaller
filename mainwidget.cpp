#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QTime>
#include <QThread>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    ui->bannerLabel->setVisible(true);
    ui->logWidget->setVisible(false);
    ui->dirLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    zipThread = new ZipFile(this);
    copyFileThread = new FileClonerThread(this);

    connect(ui->extractButton, SIGNAL(clicked()), this, SLOT(begin()));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    if (zipThread->isRunning() || copyFileThread->isRunning()) {
        if (QMessageBox::question(this, "Exit?",
                                  "Do you want to terminate the decompression?") == QMessageBox::Yes)
            event->accept();
        else
            event->ignore();
    }
}

void MainWidget::begin()
{
    ui->bannerLabel->setVisible(false);
    ui->logWidget->setVisible(true);
    ui->extractButton->setEnabled(false);

    TMP_DIR = createTempDir();
    if (!TMP_DIR.isEmpty())
        qDebug() << "Create directory: " + TMP_DIR;
    else
        qDebug() << "Error create TMP directory!!!";

    QString archiveFile(":/" + QString(GAME_ARCHIVE));
    //QString archiveFile("./" + QString("Video.zip"));
    QString TARGET_FILE = TMP_DIR + QDir::separator() + QString(GAME_ARCHIVE);
    ui->logWidget->addItem(tr("Copying an archive"));

    // После копирования архива, распаковать его в этой же директории
    connect(copyFileThread, SIGNAL(finished()), this, SLOT(extractArchive()));

    setStatusText("Copy zip archive to TMP_DIR");

    // Скопировать архив во временную директорию в отдельном потоке
    copyFileThread->copyFile(archiveFile, TARGET_FILE);
}

void MainWidget::setStatusText(const QString& statusText)
{
    setWindowTitle(QString(PROGRAM_TITLE) + " " + statusText);
}

void MainWidget::extractArchive()
{
    if (copyFileThread->getStatus() == FILE_COPY_OK)
        qDebug() << "Create game archive success!!!: " + copyFileThread->getDstFileName();
    else
        qDebug() << "Error create game archive!!!: " + copyFileThread->getDstFileName();

    QString itemText = ui->logWidget->item(ui->logWidget->count()-1)->text();
    ui->logWidget->item(ui->logWidget->count()-1)->setText(itemText + " ------> " +
                                          FileClonerThread::Status2String(copyFileThread->getStatus()));
    ui->logWidget->item(ui->logWidget->count()-1)->setToolTip(TMP_DIR + QDir::separator() + GAME_ARCHIVE);

    switch (copyFileThread->getStatus()) {
    case FILE_COPY_OK:
        ui->logWidget->item(ui->logWidget->count()-1)->setForeground(Qt::darkGreen);
        break;
    case FILE_COPY_FAILED:
        ui->logWidget->item(ui->logWidget->count()-1)->setForeground(Qt::red);
        break;
    }

    // После распаковки всех файлов запустить exe файл игры
    connect(zipThread, SIGNAL(finished()), this, SLOT(startGame()));
    // Перед распаковкой файла в архиве, занести его имя в список
    connect(zipThread, SIGNAL(beginExtractFile(QString*)), this, SLOT(addExtractFileInLog(QString*)));
    // После того как файл распакован, получить его статус (Успешно или Не Успешно)
    connect(zipThread, SIGNAL(fileExtract(QString*, int)), this, SLOT(extractFileFinish(QString*, int)));

    ui->dirLabel->setText(TMP_DIR);

    setStatusText(QString("Extract: ") + GAME_ARCHIVE);

    // Распаковать файлы в отдельном потоке
    zipThread->extracting(copyFileThread->getDstFileName(), TMP_DIR, ARCHIVE_PASSWORD);
}

void MainWidget::startGame()
{
    setStatusText("Mission complete");

    // Запустить, как независимый процесс
    QDir::setCurrent(TMP_DIR);
    QProcess::startDetached(TMP_DIR + QDir::separator() + EXE_FILE);
}

void MainWidget::addExtractFileInLog(QString *fName)
{
    ui->logWidget->addItem(*fName);
}

void MainWidget::extractFileFinish(QString *fName, int status)
{
    Q_UNUSED(fName);
    QString itemText = ui->logWidget->item(ui->logWidget->count()-1)->text();
    itemText.remove(QChar(0x20));
    ui->logWidget->item(ui->logWidget->count()-1)->setText(itemText + " ------> " +
                                          ZipFile::Status2String(status));
    ui->logWidget->item(ui->logWidget->count()-1)->setToolTip(TMP_DIR + QDir::separator() + itemText);

    switch (status) {
    case EXTRACT_OK:
        ui->logWidget->item(ui->logWidget->count()-1)->setForeground(Qt::darkGreen);
        break;
    case EXTRACT_FAILED:
        ui->logWidget->item(ui->logWidget->count()-1)->setForeground(Qt::red);
        break;
    }
}

QString MainWidget::getRandomString() const
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = DIR_NAME_LENGTH;

   QString randomString;
   for(int i = 0; i < randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }

   return randomString;
}

QString MainWidget::createTempDir()
{
    QString dirName = QDir::tempPath() + QDir::separator() + "{" + getRandomString() + "}";
    QDir d(dirName);
    if (d.exists())
        d.rmdir(dirName);
    if (d.mkdir(dirName))
        return dirName;
    return QString();
}
