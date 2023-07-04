#ifndef READWINDOW_H
#define READWINDOW_H

#include "mainwindow.h"
#include <QWindow>
#include <QTextBrowser>
#include <QLayout>
#include <QTableWidget>

#include <QTextDocument>


/**
 * @brief ReadWindow Class Window
 * 
 */
class ReadWindow : public QWindow
{

   Q_OBJECT

private:
    //address to the text browser object, used in reading plain text books
    QTextBrowser *bookTextBrowser;

    //window = address to the central widget
    QWidget* window;
    //address to the layout of the window
    QLayout* generalLayout;
    //address to the browser layout (text browser / pdf viewer)
    QLayout* browserLayout;
    //address to the layout of the buttons
    QLayout* buttonsLayout;

    //address to the close button
    QPushButton* closeButton;

    //address to the parent class
    MainWindow *parent;

    /**
     * @brief addToReadWindow
     *
     * @param fileAbsPath string containing the path to the file to be loaded
     *
     * Function sets a widget based on the file in the browser layout
     *
     * If file is .txt, it will load a text browser, otherwise it will load a pdf viewer
     */
    void addToReadWindow(const char*);

    /**
     * @brief implementationStatus
     *
     * @param extension string containing the extension of the file to be loaded
     *
     * @return Returns whether the client application can load the downloaded file or not
     */
    bool implementationStatus(const char*);

    /**
     * @brief errorBox
     *
     * @param errName string containing error name to be loaded on a message box
     *
     * Function loads a message box contaning given error
     */
    void errorBox(const char *);

    // string containing pdf path
    char* pdfPath;

private slots:

    /**
     * @brief on_readWindowClosed
     *
     * Function is called whenever the user clicks the close button
     */
    void on_readWindowClosed();

    /**
     * @brief closeButton_onClicked
     *
     * Function is called whenever the user forcefully closes the window
     */
    void closeButton_onClicked();

public:

    /**
     * @brief GetWindow
     *
     * @return Returns the address to the current central widget
     */
    inline QWidget* GetWindow() { return this->window; }

    /**
     * @brief ReadWindow
     *
     * Constructor of the Read Window object
     *
     * @param parentWindow address to the creator (parent) class
     * @param tempFilePath path to the file that is to be loaded
     */
    ReadWindow(MainWindow*, const char*);

    /**
      * @brief ~ReadWindow
      *
      * Destructor of the Read Window object
      */
    ~ReadWindow();
};

#endif // READWINDOW_H
