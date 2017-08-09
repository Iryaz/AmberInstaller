#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QTime>
#include <QDir>
#include <QThread>
#include <QProcess>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);
    setFixedSize(QSize(500, 450));
    ui->bannerLabel->setVisible(true);
    ui->logWidget->setVisible(false);
    ui->dirLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
    connect(ui->extractButton, SIGNAL(clicked()), this, SLOT(extractArchive()));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::extractArchive()
{
    ui->bannerLabel->setVisible(false);
    ui->logWidget->setVisible(true);
    ui->extractButton->setEnabled(false);

    TMP_DIR = createTempDir();
    if (!TMP_DIR.isEmpty())
        qDebug() << "Create directory: " + TMP_DIR;
    else
        qDebug() << "Error create TMP directory!!!";

    QFile archiveFile(":/" + QString(GAME_ARCHIVE));
    QString TARGET_FILE = TMP_DIR + QDir::separator() + QString(GAME_ARCHIVE);
    if (archiveFile.copy(TARGET_FILE))
        qDebug() << "Create game archive success!!!: " + TARGET_FILE;
    else
        qDebug() << "Error create game archive!!!: " + TARGET_FILE;

    ZipFile zip;
    connect(&zip, SIGNAL(beginExtractFile(QString*)), this, SLOT(addExtractFileInLog(QString*)));
    connect(&zip, SIGNAL(fileExtract(QString*, ZipFile::EXTRACTING_STATUS)),
            this, SLOT(extractFileFinish(QString*, ZipFile::EXTRACTING_STATUS)));

    ui->dirLabel->setText(TMP_DIR);
    zip.extracting(TARGET_FILE, TMP_DIR, ARCHIVE_PASSWORD);

    // Запустить как независимыйпроцесс процесс
    QDir::setCurrent(TMP_DIR);
    QProcess::startDetached(TMP_DIR + QDir::separator() + EXE_FILE);
}

void MainWidget::addExtractFileInLog(QString *fName)
{
    ui->logWidget->addItem(*fName);
    ui->logWidget->setCurrentRow(ui->logWidget->count()-1);
}

void MainWidget::extractFileFinish(QString *fName, ZipFile::EXTRACTING_STATUS status)
{
    Q_UNUSED(fName);
    QString itemText = ui->logWidget->currentItem()->text();
    itemText.remove(QChar(0x20));
    ui->logWidget->currentItem()->setText(itemText + " ------> " +
                                          ZipFile::Status2String(status));
    ui->logWidget->currentItem()->setToolTip(TMP_DIR + "/" + itemText);

    switch (status) {
    case ZipFile::EXTRACT_OK:
        ui->logWidget->currentItem()->setForeground(Qt::darkGreen);
        break;
    case ZipFile::EXTRACT_FAILED:
        ui->logWidget->currentItem()->setForeground(Qt::red);
        break;
    }
}

QString MainWidget::getRandomString() const
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = DIR_NAME_LENGTH;

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

QString MainWidget::createTempDir()
{
    QString dirName = QDir::tempPath() + "/{" + getRandomString() + "}";
    QDir d(dirName);
    if (d.exists())
        d.rmdir(dirName);
    if (d.mkdir(dirName))
        return dirName;
    return QString();
}
