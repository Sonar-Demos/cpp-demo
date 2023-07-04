#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QSlider>
#include <QDate>
#include <QDateEdit>
#include <QCheckBox>
#include <QCloseEvent>
#include <QMessageBox>
#include "settingswindow.h"
#include "createaccount.h"
#include "readwindow.h"

#define DB_DRAMA 1
#define DB_COMED 2
#define DB_THRIL 4
#define DB_HORRO 8
#define DB_MANUA 16
#define DB_BIOGR 32
#define DB_ABIOG 64
#define DB_CHILD 128
#define DB_ACTIO 256
#define DB_FANTA 512
#define DB_ROMAN 1024
#define DB_ALLGN 2047

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    memset(&this->serverInfo, 0 ,sizeof(sockaddr_in));
    this->serverIP = "127.0.0.1";
    this->serverPort = "3000";
    this->entries = nullptr;
    this->serverInfo.sin_family = AF_INET;
    this->serverInfo.sin_addr.s_addr = inet_addr(this->serverIP.toStdString().c_str());
    this->serverInfo.sin_port = htons(atoi(this->serverPort.toStdString().c_str()));
    this->ui->setupUi(this);
    this->ui->actionDisconnect->setEnabled(false);
    this->ui->libGroup->hide();
    this->pressedButton = 0;
    this->downloadDirPath = (char*)malloc(256);
    this->readButtonSignalMapper = new QSignalMapper(this);
    this->signalMapper = new QSignalMapper(this);

    connect(this->readButtonSignalMapper, SIGNAL(mapped(int)), this, SLOT(buttonRead_clicked(int)));
    connect(this->signalMapper, SIGNAL(mapped(int)), this, SLOT(buttonDownload_clicked(int)));

    memset(this->downloadDirPath, 0 ,256);
    strcpy(this->downloadDirPath, "./downloads");

    if(nullptr == (this->downloadDir = opendir(this->downloadDirPath)))
    {
        mkdir(this->downloadDirPath, 0700);
    }
    closedir(this->downloadDir);
}

void MainWindow::Init()
{
    this->loginAttempts = 3;
    this->logFile = this->CreateLog();
    if( -1 == (this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)))
        this->ReportLog(socketError);
}

MainWindow::~MainWindow()
{
    ::close(this->socketDescriptor);
    fflush(this->logFile);
    this->socketDescriptor = 0;
    memset(&this->serverInfo, 0 , sizeof(sockaddr_in));
    fclose(this->logFile);
    this->logFile = nullptr;
    delete ui;
}


void MainWindow::on_pushButtonLogin_clicked()
{
    if(this->GetReconnect() == 1)
    {
        this->GetReconnect() = 0;
        ::close(socketDescriptor);
        socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        isConnected = false;
    }

    if(isConnected == false)
    {
        if( -1 == ::connect(this->socketDescriptor, (sockaddr* )&this->serverInfo, sizeof(sockaddr))) // ::connect  (=) extern::connect
        {
            this->ReportLog(connectError);
            QMessageBox *connectFailedBox = new QMessageBox();
            connectFailedBox->setText("Connection failed!");
            connectFailedBox->setInformativeText("Sever might be down. Press Login to try again");
            connectFailedBox->setStandardButtons(QMessageBox::Ok);
            connectFailedBox->setDefaultButton(QMessageBox::Ok);
            connectFailedBox->exec();
            delete connectFailedBox;
            return;
        }
        else
        {
            isConnected = true;
        }
    }

    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    char* buffer = (char*)malloc(256);
    memset(buffer, 0 , 256);
    sprintf(buffer, "%s;%s",username.toStdString().c_str(), password.toStdString().c_str());

    write(socketDescriptor, buffer, 256);
    read(socketDescriptor, buffer, 12);

    if(!strcmp(buffer, "LOGONACCMPL"))
    {
        ui->loginGroup->hide();
        this->InitLibrary();
    }
    else
        this->loginAttempts--;

    if(!strcmp(buffer, "ERRTIMEDOUT"))
    {
        int secondsLeft = 0; char* message = (char*)malloc(128);
        read(socketDescriptor, &secondsLeft, sizeof(int));
        QMessageBox *timedoutBox = new QMessageBox();
        timedoutBox->setText("You are timed out!");
        sprintf(message, "Seconds left : %d", secondsLeft);
        timedoutBox->setInformativeText(QString(message));
        free(message);
        timedoutBox->setStandardButtons(QMessageBox::Ok);
        timedoutBox->setDefaultButton(QMessageBox::Ok);
        timedoutBox->exec();
        delete  timedoutBox;
    }

    if(!strcmp(buffer, "ERRLOGGEDIN"))
    {
        QMessageBox *alreadyLoggedInBox = new QMessageBox();
        alreadyLoggedInBox->setText(QString("User " + ui->lineEditUsername->text() + " is alreay logged in!"));
        alreadyLoggedInBox->setStandardButtons(QMessageBox::Ok);
        alreadyLoggedInBox->setDefaultButton(QMessageBox::Ok);
        alreadyLoggedInBox->exec();
        delete alreadyLoggedInBox;
    }

    if(!strcmp(buffer, "LGERRCAPHIT"))
    {
        QMessageBox *capacityHitBox = new QMessageBox();
        capacityHitBox->setText(QString("Too many users logged in!"));
        capacityHitBox->setStandardButtons(QMessageBox::Ok);
        capacityHitBox->setDefaultButton(QMessageBox::Ok);
        capacityHitBox->exec();
        delete capacityHitBox;
    }

    if(!strcmp(buffer, "LOGONFAILED"))
    {
        QMessageBox *loginFailedBox = new QMessageBox();
        loginFailedBox->setText("Username / Password incorrect");
        loginFailedBox->setInformativeText("Please try again");
        loginFailedBox->setStandardButtons(QMessageBox::Ok);
        loginFailedBox->setDefaultButton(QMessageBox::Ok);
        loginFailedBox->exec();
        delete loginFailedBox;
    }

    if(!strcmp(buffer, "LOGONACCMPL"))
    {
        QMessageBox *loginSuccessBox = new QMessageBox();
        loginSuccessBox->setText("Login successful!");
        loginSuccessBox->setInformativeText("Press Ok to continue.");
        loginSuccessBox->setStandardButtons(QMessageBox::Ok);
        loginSuccessBox->setDefaultButton(QMessageBox::Ok);
        loginSuccessBox->exec();
        delete loginSuccessBox;
    }

    ui->pushButtonLogin->update();
}

void MainWindow::PrintResults(DBResult* array, const int& length)
{
    for (size_t i = 0; i < length; i++)
    {
        printf("Title: %s\nAuthor: %s\nGenre: %s\nYear: %d\nRating: %d\nISBN: %d\n",
            array[i].bookName, array[i].authorName, array[i].genre, array[i].year, array[i].rating,
            array[i].ISBN);
    }
    fflush(stdout);
}

char *itoa(int n)
{
    int l = 0;
    static char* result = nullptr;
    if(result != nullptr)
        free(result);
    result = (char*)malloc(50);
    char* reversed = (char*)malloc(50);
    memset(result, 0, 50);
    memset(reversed, 0 ,50);
    if(n == 0)
    {
        *result = '0';
        *(result+1) = 0;
        return result;
    }
    while(n)
    {
        reversed[l++] = n%10 + '0';
        n/=10;
    }
    for(int i = 0; i < l; i++)
        result[i] = reversed[l-i-1];
    free(reversed);
    return result;
}

void MainWindow::AddToList(DBResult * array, const int & length)
{
    ui->tableWidgetQueryResult->setRowCount(length);
    for(int i = 0; i < length; i++)
    {
        ui->tableWidgetQueryResult->setItem(i, 0, new QTableWidgetItem(QString(itoa(array[i].ISBN))));
        ui->tableWidgetQueryResult->setItem(i, 1, new QTableWidgetItem(QString(array[i].bookName)));
        ui->tableWidgetQueryResult->setItem(i, 2, new QTableWidgetItem(QString(array[i].authorName)));
        ui->tableWidgetQueryResult->setItem(i, 3, new QTableWidgetItem(QString(array[i].genre)));
        ui->tableWidgetQueryResult->setItem(i, 4, new QTableWidgetItem(QString(itoa(array[i].year))));
        ui->tableWidgetQueryResult->setItem(i, 5, new QTableWidgetItem(QString(itoa(array[i].rating))));

        QWidget * pWidget = new QWidget();
        QPushButton* buttonDownload = new QPushButton();
        buttonDownload->setText("Download");
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);

        pLayout->addWidget(buttonDownload);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0,0,0,0);
        pWidget->setLayout(pLayout);

        connect(buttonDownload, SIGNAL(clicked()), this->signalMapper, SLOT(map()));
        this->signalMapper->setMapping(buttonDownload, i);

        QWidget *readParentWidget = new QWidget();
        QPushButton *readPushButton = new QPushButton();

        readPushButton->setText("Read");
        QLayout* readButtonLayout = new QHBoxLayout(readParentWidget);

        readButtonLayout->addWidget(readPushButton);
        readButtonLayout->setAlignment(Qt::AlignCenter);
        readButtonLayout->setContentsMargins(0,0,0,0);
        readParentWidget->setLayout(readButtonLayout);

        connect(readPushButton, SIGNAL(clicked()), this->readButtonSignalMapper, SLOT(map()));
        this->readButtonSignalMapper->setMapping(readPushButton, i);

        ui->tableWidgetQueryResult->setCellWidget(i,6, readParentWidget);
        ui->tableWidgetQueryResult->setCellWidget(i, 7, pWidget);
    }
}


void MainWindow::buttonRead_clicked(int indexButton)
{
    char* fileAbsPath = (char*)malloc(256);

    this->filterBuffer = (char*)malloc(1024);

    memset(this->filterBuffer, 0 ,1024);
    strcpy(this->filterBuffer, "CLIENTEVENTDOWN");
    write(socketDescriptor, this->filterBuffer, 1024);

    write(socketDescriptor, &indexButton, 4);
    read(socketDescriptor, this->filterBuffer, 1024);

    sprintf(fileAbsPath, "%s/%s%s", this->downloadDirPath, "readTemp", this->filterBuffer);

    long long fileSize = 0;
    int chunkSize = 0;
    long long bytesSum;

    if(tempPdfAbsPath != nullptr)
    {
        free(tempPdfAbsPath);
        tempPdfAbsPath = (char*)malloc(256);
        memset(tempPdfAbsPath, 0, 256);
        strcpy(tempPdfAbsPath, fileAbsPath);
    }

    int tempBookDescriptor = open(fileAbsPath, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    read(this->GetSocketDescriptor(), &fileSize, 8);

    do
    {
        read(this->GetSocketDescriptor(), &chunkSize, 4);
        read(this->GetSocketDescriptor(), filterBuffer, 1024);

        bytesSum += chunkSize;

        write(tempBookDescriptor, filterBuffer, (size_t)chunkSize);
    }while(chunkSize > 0);

    ::close(tempBookDescriptor);

    ReadWindow* bookWindow = new ReadWindow(this, fileAbsPath);

    free(fileAbsPath);
    free(this->filterBuffer);
}


void MainWindow::buttonDownload_clicked(int index)
{
    this->filterBuffer = (char*)malloc(1024);

    memset(this->filterBuffer, 0 ,1024);
    strcpy(this->filterBuffer, "CLIENTEVENTDOWN");
    write(socketDescriptor, this->filterBuffer, 1024);

    write(socketDescriptor, &index, 4);
    char *downloadFileName = (char*)malloc(256);
    memset(downloadFileName, 0 ,256);
    read(socketDescriptor, this->filterBuffer, 1024);
    strcpy(downloadFileName, this->downloadDirPath);
    strcat(downloadFileName, "/");
    strcat(downloadFileName, this->filterBuffer);

    int bookDescriptor = open(downloadFileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    long long fileSize = 0;

    read(socketDescriptor, &fileSize, 8);

    long long bytesSum = 0;
    int lbytes = 0;

    do
    {
        read(this->GetSocketDescriptor(), &lbytes, 4);
        read(this->GetSocketDescriptor(), filterBuffer, 1024);
        bytesSum += lbytes;
        write(bookDescriptor, filterBuffer, (size_t)lbytes);
    }while(lbytes > 0);

    ::close(bookDescriptor);

    free(downloadFileName);
    free(this->filterBuffer);
}

void MainWindow::InitLibrary()
{
    this->ui->filterGroup->setFixedSize(200, 680);
    this->ui->actionSettings->setEnabled(false);
    this->ui->actionDisconnect->setEnabled(true);
    this->filterBuffer = (char*)malloc(1024);

    this->ui->tableWidgetQueryResult->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList tableHeader;
    tableHeader << "ISBN" << "Title" << "Author" << "Genre" << "Publish Year" << "Rating" << "Read" << "Download" ;

    this->ui->tableWidgetQueryResult->verticalHeader()->setVisible(false);
    this->ui->tableWidgetQueryResult->setHorizontalHeaderLabels(tableHeader);
    this->ui->tableWidgetQueryResult->setColumnWidth(0, 20);
    this->ui->tableWidgetQueryResult->setColumnWidth(1,500);
    this->ui->tableWidgetQueryResult->setColumnWidth(5,20);
    this->ui->tableWidgetQueryResult->setColumnWidth(4,80);
    this->ui->tableWidgetQueryResult->setColumnWidth(3,120);
    this->ui->tableWidgetQueryResult->setColumnWidth(2,143);
    this->ui->tableWidgetQueryResult->setColumnWidth(6,97);
    this->ui->tableWidgetQueryResult->setColumnWidth(7,97);
    this->ui->tableWidgetQueryResult->verticalHeader()->setDefaultSectionSize(45);
    this->ui->tableWidgetQueryResult->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->ui->tableWidgetQueryResult->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableWidgetQueryResult->setFocusPolicy(Qt::NoFocus);
    this->ui->tableWidgetQueryResult->setSelectionMode(QAbstractItemView::NoSelection);

    memset(this->filterBuffer, 0 , 1024);
    strcpy(this->filterBuffer, "CLIENTEVENTQUER");
    write(socketDescriptor, this->filterBuffer, 1024);

    memset(this->filterBuffer, 0, 1024);
    sprintf(this->filterBuffer, "%d;%d;%s;%s;%d;%d;%d;%d",1,20,ui->lineEditAuthor->text().toStdString().c_str(),
            ui->lineEditTitle->text().toStdString().c_str(), 1970,
            2020, DB_ALLGN, 0);

    write(socketDescriptor, this->filterBuffer, 1024);
    QStringList pageIndex;
    QString buffer;
    for (int i = 1; i<= 50; i++)
    {
        if(i<10)
            buffer.insert(0, (char)i+'0');
        else
        {
            buffer.insert(0, (char)i/10+'0');
            buffer.insert(1, (char)i%10 + '0');
        }
        pageIndex.push_back(QString(buffer));
        buffer.clear();
    }
    ui->comboBoxPage->addItems(pageIndex);

    ui->comboBoxItemsPage->addItem(QString("10"));
    ui->comboBoxItemsPage->addItem(QString("20"));
    ui->comboBoxItemsPage->addItem(QString("50"));

    ui->comboBoxItemsPage->setCurrentIndex(1);

    ui->dateEditMin->setDate(QDate(1970,1,1));
    ui->dateEditMax->setDate(QDate::currentDate());

    ui->spinBoxRating->setRange(1,5);
    ui->spinBoxRating->setValue(1);


    ui->checkBoxAction->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxBio->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxAutobio->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxChildren->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxComedy->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxDrama->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxHorror->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxManual->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxThriller->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxRomance->setCheckState(Qt::CheckState::Unchecked);
    ui->checkBoxFantasy->setCheckState(Qt::CheckState::Unchecked);

    ui->libGroup->show();

    this->actualNumberEntries = 0;
    this->entries = (DBResult*)malloc(sizeof(DBResult)*20);
    memset(entries, 0 ,sizeof(DBResult)*20);
    if( 0 > read(socketDescriptor, &this->actualNumberEntries, 4))
        this->ReportLog(readError);
    for(int i = 0 ;i < this->actualNumberEntries; i++)
        if( 0 > read(socketDescriptor, &this->entries[i], sizeof(DBResult)))
            this->ReportLog(readError);

    this->AddToList(this->entries, this->actualNumberEntries);
}

int MainWindow::GetCurrentGenreFlag()
{
    int flag = 0;
    if(ui->checkBoxBio->isChecked())
        flag = flag | DB_BIOGR;
    if(ui->checkBoxDrama->isChecked())
        flag = flag | DB_DRAMA;
    if(ui->checkBoxAction->isChecked())
        flag = flag | DB_ACTIO;
    if(ui->checkBoxComedy->isChecked())
        flag = flag | DB_COMED;
    if(ui->checkBoxHorror->isChecked())
        flag = flag | DB_HORRO;
    if(ui->checkBoxManual->isChecked())
        flag = flag | DB_MANUA;
    if(ui->checkBoxAutobio->isChecked())
        flag = flag | DB_ABIOG;
    if(ui->checkBoxChildren->isChecked())
        flag = flag | DB_CHILD;
    if(ui->checkBoxThriller->isChecked())
        flag = flag | DB_THRIL;
    if(ui->checkBoxRomance->isChecked())
        flag = flag | DB_ROMAN;
    if(ui->checkBoxFantasy->isChecked())
        flag = flag | DB_FANTA;
    if(flag == 0)
        flag = DB_ALLGN;
    return flag;
}

void MainWindow::on_pushButtonApplyFilter_clicked()
{
    int flags = GetCurrentGenreFlag();
    int bytesRead = 0;

    this->filterBuffer=(char*)malloc(1024);

    memset(this->filterBuffer, 0 , 1024);
    strcpy(this->filterBuffer, "CLIENTEVENTQUER");
    write(this->socketDescriptor, this->filterBuffer, 1024);
    memset(this->filterBuffer, 0 , 1024);
    sprintf(this->filterBuffer, "%d;%d;%s;%s;%d;%d;%d;%d", atoi(ui->comboBoxPage->currentText().toStdString().c_str()), atoi(ui->comboBoxItemsPage->currentText().toStdString().c_str()),
            ui->lineEditAuthor->text().toStdString().c_str(), ui->lineEditTitle->text().toStdString().c_str(), ui->dateEditMin->date().year(), ui->dateEditMax->date().year(),
            flags, ui->spinBoxRating->value());

    write(this->socketDescriptor, this->filterBuffer, 1024);
    this->actualNumberEntries = 0;
    int maxNumberEntries = atoi(ui->comboBoxItemsPage->currentText().toStdString().c_str());
    free(this->entries);
    this->entries = (DBResult*)malloc(sizeof(DBResult)*maxNumberEntries);

    if( 0 > read(socketDescriptor, &actualNumberEntries, 4))
        this->ReportLog(readError);

    memset(this->entries, 0 ,sizeof(DBResult)*maxNumberEntries);

    for(int i = 0; i < actualNumberEntries; i++)
        if( 0 >= (bytesRead = read(socketDescriptor, &this->entries[i], sizeof(DBResult))))
            if(bytesRead < 0)
                this->ReportLog(readError);
            else
                this->ReportLog(connectionLost);

    AddToList(this->entries, actualNumberEntries);
    free(this->filterBuffer);
}


void MainWindow::on_getRecommendedBooks_clicked()
{
    int bytesRead = 0;

    this->filterBuffer = (char*)malloc(1024);

    memset(filterBuffer, 0, 1024);
    strcpy(filterBuffer, "CLIENTEVENTRECO");

    write(this->GetSocketDescriptor(), this->filterBuffer, 1024);

    read(this->GetSocketDescriptor(), this->filterBuffer, 64);

    if( !strcmp(this->filterBuffer, "FILENOTEXISTS") )
    {
        QMessageBox * msg = new QMessageBox();
        msg->setText("Cannot recommend any books.");
        msg->setInformativeText("Try downloading or reading some, then come back here.");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->setDefaultButton(QMessageBox::Ok);
        msg->exec();
        delete msg;
        return;
    }

    free(this->filterBuffer);

    this->actualNumberEntries = 0;
    free(this->entries);

    if( 0 > read(this->GetSocketDescriptor(), &this->actualNumberEntries, 4))
        this->ReportLog(readError);
    this->entries = (DBResult*)malloc(sizeof(DBResult)*5);
    memset(this->entries, 0, sizeof(DBResult)*5);

    for(int i = 0; i < this->actualNumberEntries; i++)
        if ( 0 >= (bytesRead = read(this->GetSocketDescriptor(), &this->entries[i], sizeof(DBResult))))
            if(bytesRead < 0)
                this->ReportLog(readError);
            else
                this->ReportLog(connectionLost);

    AddToList(this->entries, actualNumberEntries);
}


char* MainWindow::GetLocalTime()
{
    static char* timeString = (char*)malloc(256);
    memset(timeString,0,256);
    time_t t = time(NULL);
    tm timeStruct = *localtime(&t);
    sprintf(timeString,"%d-%d-%d<->%d:%d:%d", timeStruct.tm_hour, timeStruct.tm_min, timeStruct.tm_sec,
        timeStruct.tm_mday, timeStruct.tm_mon, timeStruct.tm_year);
    return timeString;
}

void MainWindow::ReportLog(const int logId)
{
    switch(logId)
    {
        case socketError:
            fprintf(this->logFile,"[Client][%s]socket()function error.\nApplication exited with code 2.\n",this->GetLocalTime());
            ::exit(2);
        case connectError:
            fprintf(this->logFile,"[Client][%s]connect() function error.\nProgram exited with code 3.\n", this->GetLocalTime());
            break;
        case writeError:
            fprintf(this->logFile,"[Client][%s]write() function error.\nContinuing program.\n",this->GetLocalTime());
            break;
        case readError:
            fprintf(this->logFile,"[Client][%s]read() function error.\nContinuing program.\n",this->GetLocalTime());
            break;
        case connectionLost:
            fprintf(this->logFile,"[Client][%s]Lost connection to the server.\n", this->GetLocalTime());
            break;
        default:
            fprintf(this->logFile,"[Client][%s]Unknown Log Request!!\n",this->GetLocalTime());
            return;
    }
}

FILE* MainWindow::CreateLog()
{
    static FILE* fileName;
    char* logName = (char*)malloc(256);
    memset(logName, 0, 256);
    struct stat st;

    if(stat("./logs", &st) == -1)
        mkdir("./logs", 0700);

    sprintf(logName,"./logs/log:%s", this->GetLocalTime());
    fileName = fopen(logName, "w");
    free(logName);
    return fileName;
}

void MainWindow::on_dateEditMin_userDateChanged(const QDate &date)
{
    if(date.year() > ui->dateEditMax->date().year())
        ui->dateEditMin->setDate(QDate(ui->dateEditMin->minimumDate()));
    ui->sliderMinYear->setValue(date.year());
    ui->sliderMinYear->setSliderPosition(date.year());
}

void MainWindow::on_sliderMinYear_sliderMoved(int position)
{
    if(position > ui->sliderMaxYear->value())
        ui->sliderMinYear->setValue(ui->sliderMinYear->minimum());
    ui->dateEditMin->setDate(QDate(ui->sliderMinYear->sliderPosition(),1,1));
}

void MainWindow::on_sliderMaxYear_sliderMoved(int position)
{
    if(position < ui->sliderMinYear->value())
        ui->sliderMaxYear->setValue(ui->sliderMaxYear->maximum());
    ui->dateEditMax->setDate(QDate(ui->sliderMaxYear->sliderPosition(),1,1));
}

void MainWindow::on_dateEditMax_dateChanged(const QDate &date)
{
    if(date.year() < ui->dateEditMin->date().year())
        ui->dateEditMax->setDate(QDate(ui->dateEditMax->maximumDate()));
    ui->sliderMaxYear->setValue(date.year());
    ui->sliderMaxYear->setSliderPosition(date.year());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    char *buffer = (char*)malloc(1024);
    memset(buffer,0 ,1024);
    strcpy(buffer, "CLIENTEVENTQUIT");
    write(socketDescriptor,buffer, 1024);
    free(buffer);
    ::close(socketDescriptor);
}

void MainWindow::on_actionDisconnect_triggered()
{
    char *buffer = (char*)malloc(1024);
    memset(buffer, 0, 1024);
    strcpy(buffer, "CLIENTEVENTDISC");
    write(socketDescriptor, buffer, 1024);
    free(buffer);
    ::close(socketDescriptor);

    this->ui->libGroup->hide();
    this->ui->loginGroup->show();
    this->isConnected = false;
    this->reconnect = true;
    this->ui->actionSettings->setEnabled(true);
    this->ui->actionDisconnect->setEnabled(false);
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsWindow* settings = new SettingsWindow(this);
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Enter||keyEvent->key() == Qt::Key_Return)
    {
        on_pushButtonLogin_clicked();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{

}

void MainWindow::on_actionHide_Show_triggered()
{
    if(this->ui->filterGroup->isHidden()==false)
        {this->ui->filterGroup->hide(); this->ui->tableWidgetQueryResult->setColumnWidth(1,706); return;}
    if(this->ui->filterGroup->isHidden()==true)
        {this->ui->filterGroup->show(); this->ui->tableWidgetQueryResult->setColumnWidth(1,500);return;}
}

void MainWindow::on_pushButtonCreateAccount_clicked()
{
    CreateAccount * accountWindow = new CreateAccount(this, this->socketDescriptor);
}

void MainWindow::on_actionQuit_triggered()
{
    char *buffer = (char*)malloc(1024);
    memset(buffer, 0, 1024);
    strcpy(buffer, "CLIENTEVENTDISC");
    write(socketDescriptor, buffer, 1024);
    free(buffer);
    ::close(socketDescriptor);
    qApp->exit();
}

