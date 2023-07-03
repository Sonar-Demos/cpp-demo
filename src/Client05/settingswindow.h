#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include "mainwindow.h"

/**
 * @brief SettingsWindow Class Window
 * 
 */
class SettingsWindow : public QWindow
{
  Q_OBJECT
private:

    //address to the parent class
    MainWindow *parent;
    //address to the central widget
    QWidget *settingsWindow;
    //address to the cancel button
    QPushButton *cancelButton;
    //address to the save button
    QPushButton *saveButton;
    //address to the accept button
    QPushButton *acceptButton;
    //address to the general window layout
    QLayout *generalLayout;
    //address to the buttons layout
    QLayout *buttonsLayout;
    //address to the options layout (ip, port...)
    QLayout *optionsLayout;
    //adress to the information label
    QLabel *serverInformationLabel;
    //address to the label layout
    QLayout *labelLayout;
    //address to the line edits layout
    QLayout *lineEditLayout;
    //address to the label of the IP
    QLabel *serverIPLabel;
    //address to the line edit for the IP
    QLineEdit *serverIPLineEdit;
    //address to the label of the PORT
    QLabel *serverPortLabel;
    //address to the line edit for the PORT
    QLineEdit *serverPortLineEdit;
private slots:

    /**
     * @brief on_settingsPushButtonCancel_clicked
     *
     * Function is called whenever the user clicks the cancel button
     */
    void on_settingsPushButtonCancel_clicked();

    /**
     * @brief on_settingsPushButtonSave_clicked
     *
     * Function is called whenever the user clicks the save button
     */
    void on_settingsPushButtonSave_clicked();

    /**
     * @brief on_settingsPushButtonAccept_clicked
     *
     * Function is called whenever the user clicks the accept button
     */
    void on_settingsPushButtonAccept_clicked();

    /**
     * @brief on_settingsClosed
     *
     * Function is called whenever the user clicks the close button
     */
    void on_settingsClosed();

public:

    /**
     * @brief SettingsWindow
     *
     * The Settings Window object Constructor
     *
     * @param parentClass address to the parentClass
     */
    SettingsWindow(MainWindow* parentClass);

    /**
     * @brief ~SettingsWindow
     *
     * The Settings Window object Destructor
     */
    ~SettingsWindow();
};

#endif // SETTINGSWINDOW_H
