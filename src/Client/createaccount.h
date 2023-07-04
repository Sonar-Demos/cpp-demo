#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include "mainwindow.h"

/**
 * @brief Create Account object Class
 */
class CreateAccount : public QWindow
{
    Q_OBJECT
private:

    //socket descriptor, used for communication with the server
    int sockDesc;

    //address to the parent object, mainwindow
    MainWindow* parent;

    //address to the current window main object, widget
    QWidget *window;

    //label of the title of the window
    QLabel *labelTitle;
    //label of the name field
    QLabel *labelName;
    //label of the pass field
    QLabel *labelPass;
    //label of the confirm password field
    QLabel *labelPassConfirm;

    //label to the warning name field
    QLabel *labelWarningName;
    //label to the warning pass field
    QLabel *labelWarningPass;
    //label to the warning pass confirm field
    QLabel *labelWarningConfirmPass;

    //layout of the warning labels
    QLayout *warningsLayout;
    //layout of the app title
    QLayout * titleLayout;
    //layout of the line edits
    QLayout *lineEditLayout;
    //layout of the labels
    QLayout *labelLayout;
    //layout of the credentials (linedit + labels + warning labels)
    QLayout* credentialsLayout;
    //layout of the buttons
    QLayout* buttonsLayout;
    //general layout ( credentials + buttons );
    QLayout* generalLayout;

    //line edit for the name field
    QLineEdit* lineEditName;
    //line edit for the password field
    QLineEdit* lineEditPass;
    //line edit for the confirm password field
    QLineEdit* lineEditConfirmPass;

    //button for confirming the creation of the account
    QPushButton *confirmButton;
    //button for canceling the creation of the account
    QPushButton *cancelButton;

private slots:
    /**
     * @brief callOnDestroy
     *
     * Function called whenever the user closes the window from the close window button (upper right)
     */
    void callOnDestroy();

    /**
     * @brief onConfirmClick
     *
     * Function called whenever the user clicks the confirm button
     *
     * Sends the server the account information of the newly created account
     */
    void onConfirmClick();

    /**
     * @brief onCancelClick
     *
     * Function called whenever the user clicks the cancel button
     */
    void onCancelClick();

    /**
     * @brief onNameModify
     *
     * Function called whenever the user modifies the name line edit
     *
     * Used to generate warnings
     *
     * @param newString string of the new information in the name field
     */
    void onNameModify(const QString&);

    /**
     * @brief onPassModify
     *
     * Function called whenever the user modifies the pass line edit
     *
     * Used to generate warnings
     *
     * @param newString string of the new information in the pass field
     */
    void onPassModify(const QString&);

    /**
     * @brief onConfirmPassModify
     *
     * Function called whenever the user modifies the confirm pass line edit
     *
     * Used to generate warnings
     *
     * @param newString string of the new information in the pass field field
     */
    void onConfirmPassModify(const QString&);
public:

    /**
     * @brief CreateAccount
     *
     * Constructor of the Create Account window
     *
     * @param parentWindow address to the creator object
     * @param commSock socket descriptor
     */
    CreateAccount(MainWindow*, int commSock);

    /**
      * @brief ~CreateAccount
      *
      * Destructor of the Create Account window
      */
    ~CreateAccount();
};

#endif // CREATEACCOUNT_H
