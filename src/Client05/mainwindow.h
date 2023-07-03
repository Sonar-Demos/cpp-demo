#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#include <QMainWindow>
#include <QSignalMapper>

#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The DBResult struct.
 *
 * Same as in the database header.

 * Structure which describes/contains an entry in a query result
 */
struct DBResult
{
    /**
     * @brief the title of the book
     */
    char bookName[128];
    /**
     * @brief the name of the author of the book
     */
    char authorName[128];
    /**
     * @brief the year in which the book was published
     */
    int year;
    /**
     * @brief the name of the genre of the book
     */
    char genre[64];
    /**
     * @brief the rating of the book (i out of 5)
     */
    int rating;
    /**
     * @brief the ISBN of the book (international standard book number)
     */
    int ISBN;
    /**
     * @brief the absolute path of the file containing the book contents on the disk
     */
    char diskPath[256];
};

/**
 * @brief The logs enum.
 *
 * Used to give an error code to each reported error. Improves readability.
 */
enum logs
{
    socketError, connectError, writeError, readError, connectionLost
};

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief ReportLog
     *
     * [Optional]
     * [Requires CreateLog()]
     * Function writes a log to the created log file, log id will be passed down through the parameter
     *
     * @param idLog contains an item from enum reports (refer reports), descibing the event which is to be logged
     */
    void ReportLog(const int = -1);

    /**
     * @brief SetIpString
     * @param givenIp string containing the IP that is to be set
     */
    inline void SetIpString(const QString& givenIp) { this->serverIP = givenIp; }

    /**
     * @brief SetPortString
     * @param givenPort string containing the PORT that is to be set
     */
    inline void SetPortString(const QString& givenPort) { this->serverPort = givenPort; }

    /**
     * @brief GetConnectedStatus
     * @return Returns whether the client app is connected or not
     */
    inline bool& GetConnectedStatus() {return this->isConnected;}

    /**
     * @brief GetSocketDescriptor
     * @return Returns a refference to the socket descriptor
     */
    inline int& GetSocketDescriptor() {return this->socketDescriptor;}

    /**
     * @brief GetIpString
     * @return Returns a refference to the string containing the IP
     */
    inline QString& GetIpString() { return this->serverIP; }

    /**
     * @brief GetPortString
     * @return returns a refference to the string containing the PORT
     */
    inline QString& GetPortString() { return this->serverPort; }

    /**
     * @brief GetServerInfo
     * @return Returns a refference to the structure containing the server connection information
     */
    inline sockaddr_in& GetServerInfo() {return this->serverInfo;}

    /**
     * @brief GetReconnect
     * @return Returns a refference to the variable controlling the status regaring a pending reconnection
     */
    inline int& GetReconnect() { return this->reconnect; }

    /**
     * @brief MainWindow Constructor
     * @param parent main application
     */
    MainWindow(QWidget *parent = nullptr);

    /**
      * @brief MainWindow Destructor
    */
    ~MainWindow();

    /**
     * @brief Client initialisation function
     */
    void Init();

    /**
     * @brief LoginRequest function
     *
     * Discontinued
     */
    void LoginRequest();

    /**
     * @brief Library interface initialisation function.
     *
     * Sets the filter interface objects to defaults.
     * Sends a message to the server containing a filter configured to show all entries
     */
    void InitLibrary();

    /**
     * @brief closeEvent
     *
     * Used to treat the event caused by the user exiting the program forcefully
     *
     * Sends the Server an exit message.
     *
     * @param event unused
     */
    void closeEvent(QCloseEvent*);

    /**
     * @brief Runtime function
     *
     * Discontinued
     */
    void Runtime();

    /**
     * @brief PrintResults function
     *
     * [Optional]
     * [Debug function]
     * Prints the query results received from the server on the debug console
     *
     * @param array address to the start of the DBResult array
     * @param length length of the array
     */
    void PrintResults(DBResult*, const int&);

    /**
     * @brief GetLocalTime function
     *
     * Returns the local time and date of the client.
     *
     * Used in CreateLog(), ReportLog()...
     *
     * Time and date is stored in a static string in the following format:
     * [hour]-[minute][second]<->[day]:[month]:[year]
     *
     * @return Returns an address to the static string containing the time and date in string format
     */
    char *GetLocalTime();

protected:
    /**
     * @brief keyPressEvent
     *
     * [Overridden event]
     *
     * Treats a key press event
     *
     * @param keyEvent address to the event that caused the function's call (key press)
     */
    void keyPressEvent(QKeyEvent*);

    /**
     * @brief keyReleaseEvent
     *
     * [Overridden event]
     *
     * Treats a key press event
     *
     * @param keyEvent address to the event that caused the function's call (key press)
     */
    void keyReleaseEvent(QKeyEvent*);

private slots:


    /**
     * @brief on_pushButtonLogin_clicked
     *
     * Function is triggered when the user clicks on the Login button
     *
     * The function converts the text from the editText objects that handle the username and the password
     * into a char*;char* format to send it to the server.
     * Upon function finish, the groupBoxLogin is hidden, and the main library interface group is shown
     */
    void on_pushButtonLogin_clicked();

    /**
     * @brief on_pushButtonApplyFilter_clicked
     *
     * Function is triggered when the user clicks on the Filter Results button
     *
     * The function converts the information from the filter group objects into a char* and passes
     * it on to the server through the communication channel. Afterwards, it prints the results through
     * the AddToList() function.
     */
    void on_pushButtonApplyFilter_clicked();

    /**
     * @brief on_dateEditMin_userDateChanged
     *
     * Function is triggered whenever the user changes the minimum date on the dateEdit dial
     *
     * Also resets the dateEdit dial if the user goes over the dateMax dial or slider.
     * @param date date assigned to the dateEditMin dial
     */
    void on_dateEditMin_userDateChanged(const QDate &date);

    /**
     * @brief on_sliderMinYear_sliderMoved
     *
     * Function is triggered whenever the user changes the minimum date on the dateSlider slider
     *
     * Also resets the slider if the user goes over the Max slider or dial
     * @param position assigned to the slider
     */
    void on_sliderMinYear_sliderMoved(int position);

    /**
     * @brief buttonRead_clicked
     *
     * Function is triggered whenever the user clicks a read button
     *
     * @param indexButton index of the button clicked
     */
    void buttonRead_clicked(int indexButton);

    /**
     * @brief buttonDownload_clicked
     *
     * Function is triggered whenever the user clicks a download button
     *
     * @param index index of the button clicked
     */
    void buttonDownload_clicked(int index);

    /**
     * @brief on_sliderMaxYear_sliderMoved
     *
     * Function is triggered whenever the user changes the maximum date on the dateSlider slider
     *
     * Also resets the slider if the user goes below the Min slider or dial
     *
     * @param position assigned to the slider
     */
    void on_sliderMaxYear_sliderMoved(int position);

    /**
     * @brief on_dateEditMax_dateChanged
     *
     * Function is triggered whenever the user changes the maximum date on the dateEdit dial
     *
     * Also resets the dial if the user goes below the Min slider or dial
     * @param date
     */
    void on_dateEditMax_dateChanged(const QDate &date);

    /**
     * @brief on_actionDisconnect_triggered
     *
     * Function is triggered whenever the user presses the disconnect action from the upper action menu
     */
    void on_actionDisconnect_triggered();

    /**
     * @brief on_actionSettings_triggered
     *
     * Function is triggered whenever the user presses the settings action from the upper action menu
     *
     * Causes the settings window to open
     */
    void on_actionSettings_triggered();

    /**
     * @brief on_actionHide_Show_triggered
     *
     * Function is triggered whenever the user presses the show/hide filter action from the upper action menu
     *
     * Shows/Hides the filter menu
     */
    void on_actionHide_Show_triggered();

    /**
     * @brief on_pushButtonCreateAccount_clicked
     *
     * Function is triggered whenever the user presses the create account button in the login screen
     *
     * Causes the create account window to open
     */
    void on_pushButtonCreateAccount_clicked();

    /**
     * @brief on_actionQuit_triggered
     *
     * Function is triggered whenever the user presses the quit action button in the upper action menu
     *
     * Closes the program
     */
    void on_actionQuit_triggered();

    /**
     * @brief on_getRecommendedBooks_clicked
     *
     * Function is triggered whenever the user presses the Recommend Books button
     *
     * Gets the recommended books from the server
     */
    void on_getRecommendedBooks_clicked();

private:
    /**
     * @brief ui
     *
     * The ui that is linked to the Client object
     */
    Ui::MainWindow *ui;

    /**
     * @brief entries
     *
     * The array containing the book entries' information recieved from the server
     */
    DBResult* entries;

    /**
     * @brief actualNumberEntries
     *
     * Contains the actual number of entries received, compared to the number requested per page
     */
    int actualNumberEntries;

    /**
     * @brief readButtonSignalMapper
     *
     * The signal mapper of the read buttons. Connects the indexed buttons to the read functions
     */
    QSignalMapper *readButtonSignalMapper;

    /**
     * @brief signalMapper
     *
     * The signal mapper of the download buttons. Connects the indexed buttons to the download functions
     */
    QSignalMapper *signalMapper;

    /**
     * @brief reconnect
     *
     * Variable containing the status of a pending reconnect
     */
    int reconnect = 0;

    /**
     * @brief pressedButton
     *
     * Variable containing the index of a pressed button. Used in download/read buttons
     */
    int pressedButton;

    /**
      @brief isConnected

      Variable containing the status of the current connection
      */
    bool isConnected{false};

    // variable determining whether the user has logged on or not.
    bool isLoggedOn{false};

    //counter of attempts, locally stored. 
    int loginAttempts;

    //descriptor of the communication channel between the client and the server.
    int socketDescriptor;

    //buffer containing the filter information that is sent to the server.
    char *filterBuffer;

    /**
      @brief tempPdfAbsPath

      Container of the string pointing to the path of an opened pdf file.

      Used to delete the file once the user has finished reading it
      */
    char *tempPdfAbsPath{nullptr};

    //address to the log file created by the client.
    FILE* logFile{nullptr};

    //string containing the path of the download directory
    char *downloadDirPath;

    //address to the directory in which downloads will be saved
    DIR* downloadDir;

    //externally declared structure containing the information required to connect to the server. Contains IP, port and protocol family of the server
    sockaddr_in serverInfo;

    //string containing server IP address
    QString serverIP;

    //string containing server PORT
    QString serverPort;

    /**
     * @brief GetCurrentGenreFlag
     *
     * Function returns the coded flag (base 2) associated with the genres selected from the available gernes in the filter group
     *
     * From Server/Database.h :
     *
     *      genres are stored in a flag which is in base 2, i.e.
     *      - user is looking for both thriller and horror books, thriller flag is 4 (100), horror flag is 8 (1000), therefore
     *      - what he is looking for can be described as 12 (1100)
     *
     * @return Returns the flag that contains the requested genres
     */
    int GetCurrentGenreFlag();

    /**
     * @brief AddToList
     *
     * Function updates the table in which the query result will be shown.
     *
     * Converts from DBResult* array items to QTableViewItems
     *
     * @param array array through which the query results are received.
     * @param length the length of the array
     */
    void AddToList(DBResult*, const int&);


    /**
     * @brief CreateLog
     *
     * [Optional]
     *
     * Creates a log at the specified path (inside the function definition) TODO : get path from outside the function
     * Log is created with the following name
     * log:[hour]-[minute]-[second]<->[day]:[month]:[year].txt
     *
     * @return address of the file
     */
    FILE* CreateLog();
};
#endif // MAINWINDOW_H
