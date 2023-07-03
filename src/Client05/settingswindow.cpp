#include "settingswindow.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QObject>
SettingsWindow::SettingsWindow(MainWindow* parentClass) : parent(parentClass)
{
    settingsWindow = new QWidget();
    settingsWindow->setAttribute(Qt::WA_DeleteOnClose);
    settingsWindow->resize(200,200);
    cancelButton = new QPushButton();
    saveButton = new QPushButton();
    acceptButton = new QPushButton();
    generalLayout = new QVBoxLayout(settingsWindow);
    buttonsLayout = new QHBoxLayout();
    optionsLayout = new QHBoxLayout();

    serverInformationLabel = new QLabel();
    serverInformationLabel->setText("Server Connection Information:");
    generalLayout->addWidget(serverInformationLabel);

    generalLayout->addItem(optionsLayout);
    generalLayout->addItem(buttonsLayout);
    optionsLayout->setParent(generalLayout);
    buttonsLayout->setParent(generalLayout);

    cancelButton->setText("Cancel");
    saveButton->setText("Save");
    acceptButton->setText("Accept");

    buttonsLayout->setAlignment(Qt::AlignBottom);
    buttonsLayout->setContentsMargins(0,0,0,0);
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(acceptButton);

    labelLayout = new QVBoxLayout();
    lineEditLayout = new QVBoxLayout();
    optionsLayout->addItem(labelLayout);
    optionsLayout->addItem(lineEditLayout);

    labelLayout->setParent(optionsLayout);
    lineEditLayout->setParent(optionsLayout);

    serverIPLabel = new QLabel();
    serverIPLineEdit = new QLineEdit();

    serverIPLineEdit->setText(this->parent->GetIpString());

    serverIPLabel->setText("Server IP address");

    labelLayout->addWidget(serverIPLabel);
    lineEditLayout->addWidget(serverIPLineEdit);

    serverPortLabel = new QLabel();
    serverPortLineEdit = new QLineEdit();

    serverPortLineEdit->setText(this->parent->GetPortString());

    serverPortLabel->setText("Server Port");

    labelLayout->addWidget(serverPortLabel);
    lineEditLayout->addWidget(serverPortLineEdit);

    connect(this->settingsWindow, SIGNAL(destroyed()), this, SLOT(on_settingsClosed()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_settingsPushButtonCancel_clicked()));
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(on_settingsPushButtonAccept_clicked()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_settingsPushButtonSave_clicked()));

    settingsWindow->show();
    this->parent->setEnabled(false);
}

void SettingsWindow::on_settingsPushButtonSave_clicked()
{
    this->parent->GetIpString() = this->serverIPLineEdit->text();
    this->parent->GetPortString() = this->serverPortLineEdit->text();
    this->parent->GetServerInfo().sin_addr.s_addr = inet_addr(this->parent->GetIpString().toStdString().c_str());
    this->parent->GetServerInfo().sin_port = htons(atoi(this->parent->GetPortString().toStdString().c_str()));
    this->parent->GetReconnect() = 1;
}

void SettingsWindow::on_settingsPushButtonAccept_clicked()
{
    this->parent->GetIpString() = this->serverIPLineEdit->text();
    this->parent->GetPortString() = this->serverPortLineEdit->text();
    this->parent->GetServerInfo().sin_addr.s_addr = inet_addr(this->parent->GetIpString().toStdString().c_str());
    this->parent->GetServerInfo().sin_port = htons(atoi(this->parent->GetPortString().toStdString().c_str()));
    this->parent->GetReconnect() = 1;

    this->settingsWindow->close();
    this->parent->setEnabled(true);
    delete this;
}

void SettingsWindow::on_settingsPushButtonCancel_clicked()
{
    this->settingsWindow->close();
    this->parent->setEnabled(true);
    delete this;
}

SettingsWindow::~SettingsWindow()
{
    this->parent->setEnabled(true);
    delete serverIPLabel;
    delete serverPortLabel;
    delete serverPortLineEdit;
    delete serverInformationLabel;
    delete serverIPLineEdit;

    delete cancelButton;
    delete acceptButton;
    delete saveButton;

    delete labelLayout;
    delete lineEditLayout;

    delete buttonsLayout;
    delete optionsLayout;
    delete generalLayout;

    delete settingsWindow;
}

void SettingsWindow::on_settingsClosed()
{
    this->parent->setEnabled(true);
}
