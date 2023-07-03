#include "readwindow.h"
#include <poppler-qt5.h>
#include <QMessageBox>
#include "pdfviewer.h"
ReadWindow::ReadWindow(MainWindow *parentWindow, const char* tempFilePath)
{
    this->pdfPath = (char*)malloc(256);
    strcpy(this->pdfPath, tempFilePath);

    this->parent = parentWindow;

    this->window = new QWidget();
    this->window->setAttribute(Qt::WA_DeleteOnClose);

    connect(this->window, SIGNAL(destroyed()), this, SLOT(on_readWindowClosed()));

    this->window->setGeometry(this->parent->x() + 200, this->parent->y() + 100, this->parent->width() - 400, this->parent->height() - 150);

    this->generalLayout = new QVBoxLayout(this->window);

    this->window->setLayout(generalLayout);

    this->browserLayout = new QHBoxLayout();
    this->buttonsLayout = new QHBoxLayout();

    browserLayout->setParent(this->generalLayout);
    buttonsLayout->setParent(this->generalLayout);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    this->generalLayout->addItem(this->browserLayout);
    this->generalLayout->addItem(this->buttonsLayout);


    this->closeButton = new QPushButton(this->window);
    this->closeButton->setText(QString("Close"));
    this->closeButton->setMinimumWidth(100);
    this->closeButton->setMaximumWidth(100);
    connect(this->closeButton, SIGNAL(clicked()), this, SLOT(closeButton_onClicked()));

    this->buttonsLayout->addWidget(closeButton);

    this->window->show();
    this->parent->setEnabled(false);

    this->window->update();
    this->parent->update();

    this->addToReadWindow(tempFilePath);
}

void ReadWindow::addToReadWindow(const char *fileAbsPath)
{

    int bytesRead = 0;
    char *absPathCopy = (char*)malloc(256);
    strcpy(absPathCopy, fileAbsPath);

    char *extension = absPathCopy;
    while(strchr(extension, '.')) extension = strchr(extension, '.') + 1;

    if(implementationStatus(extension) == false)
    {
        free(absPathCopy);
        return;
    }

    free(absPathCopy);

    if(!strcmp(extension, "txt"))
    {
        int fileDescriptor = open(fileAbsPath, O_RDONLY, 0666);
        this->bookTextBrowser = new QTextBrowser();
        this->browserLayout->addWidget(this->bookTextBrowser);

        this->bookTextBrowser->setReadOnly(true);
        this->bookTextBrowser->clear();
        char * readBuffer = (char*)malloc(1024);

        do
        {
            memset(readBuffer, 0, 1024);
            bytesRead = read(fileDescriptor, readBuffer, 1024);

            this->bookTextBrowser->append(QString(readBuffer));

        }while( bytesRead > 0 );

        ::close(fileDescriptor);

        free(readBuffer);

    }
    if(!strcmp(extension, "pdf"))
    {
        PdfViewer *pdfWidget = new PdfViewer(this->window);
        browserLayout->addWidget(pdfWidget);

        pdfWidget->documentLoad( fileAbsPath );
        pdfWidget->setViewMode(PdfViewer::ViewMode::singlePageView);
        pdfWidget->setLayoutMode(PdfViewer::LayoutMode::continuous);
        pdfWidget->setZoom(1.0);
    }
}

void ReadWindow::errorBox(const char *errName)
{
    QMessageBox* errorPopup = new QMessageBox();
    errorPopup->setText(QString(errName));
    errorPopup->setInformativeText("Press OK to return");
    errorPopup->setStandardButtons(QMessageBox::Ok);
    errorPopup->setDefaultButton(QMessageBox::Ok);
    errorPopup->exec();
    delete errorPopup;
}

bool ReadWindow::implementationStatus(const char *extension)
{
    if(!strcmp(extension, "txt"))
        return true;
    if(!strcmp(extension, "pdf"))
        return true;
    return false;
}

void ReadWindow::closeButton_onClicked()
{
    system(QString( QString("rm ") + QString(this->pdfPath) ).toStdString().c_str());

    free(this->pdfPath);
    this->window->close();
    this->close();
    this->on_readWindowClosed();

}


ReadWindow::~ReadWindow()
{
    delete bookTextBrowser;
    delete closeButton;
    delete browserLayout;
    delete buttonsLayout;
    delete window;
}

void ReadWindow::on_readWindowClosed()
{
    system(QString( QString("rm ") + QString(this->pdfPath) ).toStdString().c_str());
    this->parent->setEnabled(true);
}
