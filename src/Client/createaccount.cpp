#include "createaccount.h"
#include <QMessageBox>

CreateAccount::CreateAccount(MainWindow* parentWindow, int commSock) : parent(parentWindow), sockDesc(commSock)
{
    window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->setMinimumWidth(600);
    connect(window, SIGNAL(destroyed()), this, SLOT(callOnDestroy()));

    labelTitle = new QLabel();
    labelTitle->setText("Enter your account details below : ");

    labelName = new QLabel();
    labelName->setText("Enter your desired username");

    labelPass = new QLabel();
    labelPass->setText("Enter your desired password");

    labelPassConfirm = new QLabel();
    labelPassConfirm->setText("Re-enter your password to confirm");

    labelWarningName = new QLabel();
    labelWarningPass = new QLabel();
    labelWarningConfirmPass = new QLabel();

    labelWarningName->setText("Name field cannot be empty!");
    labelWarningPass->setText("Pass field cannot be empty!");
    labelWarningConfirmPass->setText("Confirm field cannot be empty!");

    labelLayout = new QVBoxLayout();

    labelLayout->setContentsMargins(0,0,0,0);

    labelLayout->addWidget(labelName);
    labelLayout->addWidget(labelPass);
    labelLayout->addWidget(labelPassConfirm);

    lineEditName = new QLineEdit();

    connect(lineEditName, SIGNAL(textChanged(const QString&)), this, SLOT(onNameModify(const QString &)));

    lineEditPass = new QLineEdit();

    lineEditPass->setEchoMode(QLineEdit::Password);
    connect(lineEditPass, SIGNAL(textChanged(const QString&)), this, SLOT(onPassModify(const QString&)));

    lineEditConfirmPass = new QLineEdit();

    lineEditConfirmPass->setEchoMode(QLineEdit::Password);
    connect(lineEditConfirmPass, SIGNAL(textChanged(const QString&)), this, SLOT(onConfirmPassModify(const QString&)));

    lineEditLayout = new QVBoxLayout();

    lineEditLayout->setContentsMargins(0,0,0,0);

    lineEditLayout->addWidget(lineEditName);
    lineEditLayout->addWidget(lineEditPass);
    lineEditLayout->addWidget(lineEditConfirmPass);

    warningsLayout = new QVBoxLayout();

    warningsLayout->addWidget(labelWarningName);
    warningsLayout->addWidget(labelWarningPass);
    warningsLayout->addWidget(labelWarningConfirmPass);

    warningsLayout->setSizeConstraint(QLayout::SetFixedSize);


    credentialsLayout = new QHBoxLayout();

    credentialsLayout->setContentsMargins(0,0,0,50);

    credentialsLayout->addItem(labelLayout);
    credentialsLayout->addItem(lineEditLayout);
    credentialsLayout->addItem(warningsLayout);

    warningsLayout->setParent(credentialsLayout);
    labelLayout->setParent(credentialsLayout);
    lineEditLayout->setParent(credentialsLayout);

    cancelButton = new QPushButton();
    confirmButton = new QPushButton();

    cancelButton->setText("Cancel");
    confirmButton->setText("Confirm");

    connect(confirmButton, SIGNAL(clicked()), this, SLOT(onConfirmClick()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClick()));

    buttonsLayout = new QHBoxLayout();

    buttonsLayout->setContentsMargins(0,0,0,0);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(confirmButton);

    titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(0,0,0,20);
    titleLayout->setAlignment(Qt::AlignCenter);

    titleLayout->addWidget(labelTitle);

    generalLayout = new QVBoxLayout();

    generalLayout->setContentsMargins(30, 30, 30, 10);
    generalLayout->setAlignment(Qt::AlignCenter);

    generalLayout->addItem(titleLayout);
    generalLayout->addItem(credentialsLayout);
    generalLayout->addItem(buttonsLayout);

    credentialsLayout->setParent(generalLayout);
    buttonsLayout->setParent(generalLayout);

    window->setLayout(generalLayout);

    this->parent->setEnabled(false);
    this->window->show();
}

void CreateAccount::onConfirmClick()
{
    if(this->parent->GetReconnect() == 1)
    {
        this->parent->GetReconnect() = 0;
        ::close(this->parent->GetSocketDescriptor());
        this->parent->GetSocketDescriptor() = socket(AF_INET, SOCK_STREAM, 0);
        this->parent->GetConnectedStatus() = false;
    }

    if(this->parent->GetConnectedStatus() == false)
    {
        if( -1 == ::connect(this->parent->GetSocketDescriptor(), (sockaddr*)&this->parent->GetServerInfo(), sizeof(sockaddr)))
        {
            this->parent->ReportLog(logs::connectError);
            QMessageBox *connectFailedBox = new QMessageBox();
            connectFailedBox->setText("Connect failed!");
            connectFailedBox->setInformativeText("Server might be down.");
            connectFailedBox->setStandardButtons(QMessageBox::Ok);
            connectFailedBox->setDefaultButton(QMessageBox::Ok);
            connectFailedBox->exec();
            delete connectFailedBox;
            return;
        }
    }

    this->parent->GetConnectedStatus() = true;

    if(this->labelWarningName->text() == QString("Name is Valid!") &&
      (this->labelWarningPass->text() == QString("Fair Password") ||
       this->labelWarningPass->text() == QString("Strong Password")) &&
       this->labelWarningConfirmPass->text() == QString("Passwords match!") )
    {
        char* messageBuffer = (char*)calloc(1, 256);
        strcat(messageBuffer, "CLIENTACCCREATE");
        write(this->parent->GetSocketDescriptor(), messageBuffer, 256);
        memset(messageBuffer, 0, 256);
        sprintf(messageBuffer, "%s;%s", this->lineEditName->text().toStdString().c_str(), this->lineEditPass->text().toStdString().c_str());

        fflush(stdout);
        write(this->parent->GetSocketDescriptor(), messageBuffer, 256);

        memset(messageBuffer, 0 , 256);
        read(this->parent->GetSocketDescriptor(), messageBuffer, 12);

        if(!strcmp("ACCOUEXISTS", messageBuffer))
        {
            QMessageBox *serverResponse = new QMessageBox(this->window);
            serverResponse->setText(QString("Account ") + this->lineEditName->text() + QString(" already exists!"));
            serverResponse->setInformativeText(QString("Try another username"));
            serverResponse->setStandardButtons(QMessageBox::Ok);
            serverResponse->setDefaultButton(QMessageBox::Ok);
            serverResponse->exec();
        }

        if(!strcmp("ACCONEXISTS", messageBuffer))
        {
            QMessageBox *serverResponse = new QMessageBox(this->window);
            serverResponse->setText(QString("Account ") + this->lineEditName->text() + QString(" has been created successfuly"));
            serverResponse->setInformativeText(QString("You can now log into the server with this account"));
            serverResponse->setStandardButtons(QMessageBox::Ok);
            serverResponse->setDefaultButton(QMessageBox::Ok);
            serverResponse->exec();

            this->onCancelClick();
        }
    }
}

void CreateAccount::onCancelClick()
{
    this->parent->setEnabled(true);
    this->window->close();
    delete this;
}

void CreateAccount::callOnDestroy()
{
    this->parent->setEnabled(true);
}

void CreateAccount::onNameModify(const QString & newString)
{
    if(newString.contains(QRegExp("[.,/]")))
    {
        this->labelWarningName->setText("Contains invalid characters!");
    }
    else
        if(newString.isEmpty())
        {
            this->labelWarningName->setText("Name field cannot be empty!");
        }
        else
            this->labelWarningName->setText("Name is Valid!");
    fflush(stdout);
}

void CreateAccount::onPassModify(const QString& newString)
{
    QString * newText;
    int passwordStrength;
    if(newString.contains(QRegExp("[,./]")))
    {
        this->labelWarningPass->setText("Contains invalid characters!");
    }
    else
        if(newString.isEmpty())
        {
            this->labelWarningPass->setText("Pass field cannot be empty!");
        }
        else
        {
            passwordStrength = 0;

            if(newString.contains(QRegExp("[a-z]")))
                passwordStrength++;
            if(newString.contains(QRegExp("[A-Z]")))
                passwordStrength++;
            if(newString.contains(QRegExp("[0-9]")))
                passwordStrength++;
            if(newString.length() < 8)
                passwordStrength = 1;

            switch (passwordStrength) {
                case 1:
                    newText = new QString("Weak Password");
                    break;
                case 2:
                    newText = new QString("Fair Password");
                    break;
                case 3:
                    newText = new QString("Strong Password");
            }

            this->labelWarningPass->setText(*newText);
            delete newText;
        }
}



void CreateAccount::onConfirmPassModify(const QString& newString)
{
    if(newString == this->lineEditPass->text())
        this->labelWarningConfirmPass->setText("Passwords match!");
    else
        this->labelWarningConfirmPass->setText("Passwords do not match!");
}

CreateAccount::~CreateAccount()
{
    delete lineEditLayout;
    delete labelLayout;
    delete credentialsLayout;
    delete buttonsLayout;
    delete generalLayout;

    delete lineEditName;
    delete lineEditPass;
    delete lineEditConfirmPass;

    delete confirmButton;
    delete cancelButton;

    delete labelTitle;
    delete labelPass;
    delete labelPassConfirm;
    delete labelName;
}


