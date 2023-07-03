/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSettings;
    QAction *actionDisconnect;
    QAction *actionHide_Show;
    QAction *actionQuit;
    QWidget *centralwidget;
    QGroupBox *loginGroup;
    QPushButton *pushButtonLogin;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QPushButton *pushButtonCreateAccount;
    QGroupBox *libGroup;
    QWidget *layoutWidget1;
    QHBoxLayout *LibraryLayout;
    QGroupBox *filterGroup;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *layoutPage;
    QLabel *labelPage;
    QComboBox *comboBoxPage;
    QVBoxLayout *layoutItemsPage;
    QLabel *labelItemsPage;
    QComboBox *comboBoxItemsPage;
    QVBoxLayout *layoutAuthorTitle;
    QLabel *labelTitle;
    QLineEdit *lineEditTitle;
    QVBoxLayout *layoutAuthor;
    QLabel *labelAuthor;
    QLineEdit *lineEditAuthor;
    QHBoxLayout *layoutYear;
    QVBoxLayout *layoutYearLabels;
    QLabel *labelMinYear;
    QLabel *labelMaxYear;
    QVBoxLayout *layoutYearSliders;
    QSlider *sliderMinYear;
    QSlider *sliderMaxYear;
    QVBoxLayout *verticalLayout_2;
    QDateEdit *dateEditMin;
    QDateEdit *dateEditMax;
    QHBoxLayout *layoutRating;
    QLabel *labelRating;
    QSpinBox *spinBoxRating;
    QLabel *labelGenre;
    QScrollArea *scrollAreaGenre;
    QWidget *scrollAreaGenreContents;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkBoxDrama;
    QCheckBox *checkBoxComedy;
    QCheckBox *checkBoxThriller;
    QCheckBox *checkBoxHorror;
    QCheckBox *checkBoxManual;
    QCheckBox *checkBoxBio;
    QCheckBox *checkBoxAutobio;
    QCheckBox *checkBoxChildren;
    QCheckBox *checkBoxAction;
    QCheckBox *checkBoxRomance;
    QCheckBox *checkBoxFantasy;
    QPushButton *pushButtonApplyFilter;
    QPushButton *getRecommendedBooks;
    QTableWidget *tableWidgetQueryResult;
    QMenuBar *menubar;
    QMenu *menuClient;
    QMenu *menuFilter;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1366, 768);
        QFont font;
        font.setStrikeOut(false);
        MainWindow->setFont(font);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionHide_Show = new QAction(MainWindow);
        actionHide_Show->setObjectName(QString::fromUtf8("actionHide_Show"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        loginGroup = new QGroupBox(centralwidget);
        loginGroup->setObjectName(QString::fromUtf8("loginGroup"));
        loginGroup->setGeometry(QRect(500, 200, 371, 371));
        pushButtonLogin = new QPushButton(loginGroup);
        pushButtonLogin->setObjectName(QString::fromUtf8("pushButtonLogin"));
        pushButtonLogin->setGeometry(QRect(50, 230, 261, 25));
        layoutWidget = new QWidget(loginGroup);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 90, 261, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelUsername = new QLabel(layoutWidget);
        labelUsername->setObjectName(QString::fromUtf8("labelUsername"));

        horizontalLayout_2->addWidget(labelUsername);

        lineEditUsername = new QLineEdit(layoutWidget);
        lineEditUsername->setObjectName(QString::fromUtf8("lineEditUsername"));
        lineEditUsername->setEchoMode(QLineEdit::Normal);

        horizontalLayout_2->addWidget(lineEditUsername);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelPassword = new QLabel(layoutWidget);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));

        horizontalLayout->addWidget(labelPassword);

        lineEditPassword = new QLineEdit(layoutWidget);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setFont(font);
        lineEditPassword->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        lineEditPassword->setInputMask(QString::fromUtf8(""));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(lineEditPassword);


        verticalLayout->addLayout(horizontalLayout);

        pushButtonCreateAccount = new QPushButton(loginGroup);
        pushButtonCreateAccount->setObjectName(QString::fromUtf8("pushButtonCreateAccount"));
        pushButtonCreateAccount->setGeometry(QRect(50, 260, 261, 25));
        libGroup = new QGroupBox(centralwidget);
        libGroup->setObjectName(QString::fromUtf8("libGroup"));
        libGroup->setEnabled(true);
        libGroup->setGeometry(QRect(10, 0, 1341, 731));
        libGroup->setAutoFillBackground(false);
        libGroup->setInputMethodHints(Qt::ImhNone);
        layoutWidget1 = new QWidget(libGroup);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 1321, 701));
        LibraryLayout = new QHBoxLayout(layoutWidget1);
        LibraryLayout->setObjectName(QString::fromUtf8("LibraryLayout"));
        LibraryLayout->setContentsMargins(0, 0, 0, 0);
        filterGroup = new QGroupBox(layoutWidget1);
        filterGroup->setObjectName(QString::fromUtf8("filterGroup"));
        filterGroup->setSizeIncrement(QSize(0, 0));
        filterGroup->setFlat(false);
        verticalLayout_9 = new QVBoxLayout(filterGroup);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        layoutPage = new QVBoxLayout();
        layoutPage->setObjectName(QString::fromUtf8("layoutPage"));
        labelPage = new QLabel(filterGroup);
        labelPage->setObjectName(QString::fromUtf8("labelPage"));

        layoutPage->addWidget(labelPage);

        comboBoxPage = new QComboBox(filterGroup);
        comboBoxPage->setObjectName(QString::fromUtf8("comboBoxPage"));
        comboBoxPage->setEditable(true);
        comboBoxPage->setMaxCount(50);

        layoutPage->addWidget(comboBoxPage);


        verticalLayout_9->addLayout(layoutPage);

        layoutItemsPage = new QVBoxLayout();
        layoutItemsPage->setObjectName(QString::fromUtf8("layoutItemsPage"));
        labelItemsPage = new QLabel(filterGroup);
        labelItemsPage->setObjectName(QString::fromUtf8("labelItemsPage"));

        layoutItemsPage->addWidget(labelItemsPage);

        comboBoxItemsPage = new QComboBox(filterGroup);
        comboBoxItemsPage->setObjectName(QString::fromUtf8("comboBoxItemsPage"));
        comboBoxItemsPage->setEditable(false);
        comboBoxItemsPage->setMaxVisibleItems(3);
        comboBoxItemsPage->setMaxCount(3);

        layoutItemsPage->addWidget(comboBoxItemsPage);


        verticalLayout_9->addLayout(layoutItemsPage);

        layoutAuthorTitle = new QVBoxLayout();
        layoutAuthorTitle->setObjectName(QString::fromUtf8("layoutAuthorTitle"));
        labelTitle = new QLabel(filterGroup);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

        layoutAuthorTitle->addWidget(labelTitle);

        lineEditTitle = new QLineEdit(filterGroup);
        lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));

        layoutAuthorTitle->addWidget(lineEditTitle);

        layoutAuthor = new QVBoxLayout();
        layoutAuthor->setObjectName(QString::fromUtf8("layoutAuthor"));
        labelAuthor = new QLabel(filterGroup);
        labelAuthor->setObjectName(QString::fromUtf8("labelAuthor"));

        layoutAuthor->addWidget(labelAuthor);

        lineEditAuthor = new QLineEdit(filterGroup);
        lineEditAuthor->setObjectName(QString::fromUtf8("lineEditAuthor"));

        layoutAuthor->addWidget(lineEditAuthor);


        layoutAuthorTitle->addLayout(layoutAuthor);


        verticalLayout_9->addLayout(layoutAuthorTitle);

        layoutYear = new QHBoxLayout();
        layoutYear->setObjectName(QString::fromUtf8("layoutYear"));
        layoutYearLabels = new QVBoxLayout();
        layoutYearLabels->setObjectName(QString::fromUtf8("layoutYearLabels"));
        labelMinYear = new QLabel(filterGroup);
        labelMinYear->setObjectName(QString::fromUtf8("labelMinYear"));

        layoutYearLabels->addWidget(labelMinYear);

        labelMaxYear = new QLabel(filterGroup);
        labelMaxYear->setObjectName(QString::fromUtf8("labelMaxYear"));

        layoutYearLabels->addWidget(labelMaxYear);


        layoutYear->addLayout(layoutYearLabels);

        layoutYearSliders = new QVBoxLayout();
        layoutYearSliders->setObjectName(QString::fromUtf8("layoutYearSliders"));
        sliderMinYear = new QSlider(filterGroup);
        sliderMinYear->setObjectName(QString::fromUtf8("sliderMinYear"));
        sliderMinYear->setMinimum(1800);
        sliderMinYear->setMaximum(2050);
        sliderMinYear->setValue(1800);
        sliderMinYear->setOrientation(Qt::Horizontal);
        sliderMinYear->setInvertedControls(true);

        layoutYearSliders->addWidget(sliderMinYear);

        sliderMaxYear = new QSlider(filterGroup);
        sliderMaxYear->setObjectName(QString::fromUtf8("sliderMaxYear"));
        sliderMaxYear->setMinimum(1800);
        sliderMaxYear->setMaximum(2050);
        sliderMaxYear->setOrientation(Qt::Horizontal);
        sliderMaxYear->setInvertedControls(true);

        layoutYearSliders->addWidget(sliderMaxYear);


        layoutYear->addLayout(layoutYearSliders);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dateEditMin = new QDateEdit(filterGroup);
        dateEditMin->setObjectName(QString::fromUtf8("dateEditMin"));
        dateEditMin->setMaximumDate(QDate(2050, 1, 1));
        dateEditMin->setMinimumDate(QDate(1800, 1, 1));
        dateEditMin->setMaximumTime(QTime(23, 59, 59));
        dateEditMin->setCalendarPopup(false);

        verticalLayout_2->addWidget(dateEditMin);

        dateEditMax = new QDateEdit(filterGroup);
        dateEditMax->setObjectName(QString::fromUtf8("dateEditMax"));
        dateEditMax->setMaximumDateTime(QDateTime(QDate(2050, 1, 1), QTime(23, 59, 59)));
        dateEditMax->setMinimumDate(QDate(1800, 1, 1));

        verticalLayout_2->addWidget(dateEditMax);


        layoutYear->addLayout(verticalLayout_2);


        verticalLayout_9->addLayout(layoutYear);

        layoutRating = new QHBoxLayout();
        layoutRating->setObjectName(QString::fromUtf8("layoutRating"));
        labelRating = new QLabel(filterGroup);
        labelRating->setObjectName(QString::fromUtf8("labelRating"));

        layoutRating->addWidget(labelRating);

        spinBoxRating = new QSpinBox(filterGroup);
        spinBoxRating->setObjectName(QString::fromUtf8("spinBoxRating"));

        layoutRating->addWidget(spinBoxRating);


        verticalLayout_9->addLayout(layoutRating);

        labelGenre = new QLabel(filterGroup);
        labelGenre->setObjectName(QString::fromUtf8("labelGenre"));

        verticalLayout_9->addWidget(labelGenre);

        scrollAreaGenre = new QScrollArea(filterGroup);
        scrollAreaGenre->setObjectName(QString::fromUtf8("scrollAreaGenre"));
        scrollAreaGenre->setWidgetResizable(true);
        scrollAreaGenreContents = new QWidget();
        scrollAreaGenreContents->setObjectName(QString::fromUtf8("scrollAreaGenreContents"));
        scrollAreaGenreContents->setGeometry(QRect(0, 0, 617, 331));
        verticalLayout_8 = new QVBoxLayout(scrollAreaGenreContents);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        checkBoxDrama = new QCheckBox(scrollAreaGenreContents);
        checkBoxDrama->setObjectName(QString::fromUtf8("checkBoxDrama"));

        verticalLayout_8->addWidget(checkBoxDrama);

        checkBoxComedy = new QCheckBox(scrollAreaGenreContents);
        checkBoxComedy->setObjectName(QString::fromUtf8("checkBoxComedy"));

        verticalLayout_8->addWidget(checkBoxComedy);

        checkBoxThriller = new QCheckBox(scrollAreaGenreContents);
        checkBoxThriller->setObjectName(QString::fromUtf8("checkBoxThriller"));

        verticalLayout_8->addWidget(checkBoxThriller);

        checkBoxHorror = new QCheckBox(scrollAreaGenreContents);
        checkBoxHorror->setObjectName(QString::fromUtf8("checkBoxHorror"));

        verticalLayout_8->addWidget(checkBoxHorror);

        checkBoxManual = new QCheckBox(scrollAreaGenreContents);
        checkBoxManual->setObjectName(QString::fromUtf8("checkBoxManual"));

        verticalLayout_8->addWidget(checkBoxManual);

        checkBoxBio = new QCheckBox(scrollAreaGenreContents);
        checkBoxBio->setObjectName(QString::fromUtf8("checkBoxBio"));

        verticalLayout_8->addWidget(checkBoxBio);

        checkBoxAutobio = new QCheckBox(scrollAreaGenreContents);
        checkBoxAutobio->setObjectName(QString::fromUtf8("checkBoxAutobio"));

        verticalLayout_8->addWidget(checkBoxAutobio);

        checkBoxChildren = new QCheckBox(scrollAreaGenreContents);
        checkBoxChildren->setObjectName(QString::fromUtf8("checkBoxChildren"));

        verticalLayout_8->addWidget(checkBoxChildren);

        checkBoxAction = new QCheckBox(scrollAreaGenreContents);
        checkBoxAction->setObjectName(QString::fromUtf8("checkBoxAction"));

        verticalLayout_8->addWidget(checkBoxAction);

        checkBoxRomance = new QCheckBox(scrollAreaGenreContents);
        checkBoxRomance->setObjectName(QString::fromUtf8("checkBoxRomance"));

        verticalLayout_8->addWidget(checkBoxRomance);

        checkBoxFantasy = new QCheckBox(scrollAreaGenreContents);
        checkBoxFantasy->setObjectName(QString::fromUtf8("checkBoxFantasy"));

        verticalLayout_8->addWidget(checkBoxFantasy);

        scrollAreaGenre->setWidget(scrollAreaGenreContents);

        verticalLayout_9->addWidget(scrollAreaGenre);

        pushButtonApplyFilter = new QPushButton(filterGroup);
        pushButtonApplyFilter->setObjectName(QString::fromUtf8("pushButtonApplyFilter"));

        verticalLayout_9->addWidget(pushButtonApplyFilter);

        getRecommendedBooks = new QPushButton(filterGroup);
        getRecommendedBooks->setObjectName(QString::fromUtf8("getRecommendedBooks"));

        verticalLayout_9->addWidget(getRecommendedBooks);


        LibraryLayout->addWidget(filterGroup);

        tableWidgetQueryResult = new QTableWidget(layoutWidget1);
        if (tableWidgetQueryResult->columnCount() < 8)
            tableWidgetQueryResult->setColumnCount(8);
        tableWidgetQueryResult->setObjectName(QString::fromUtf8("tableWidgetQueryResult"));
        tableWidgetQueryResult->setDragEnabled(false);
        tableWidgetQueryResult->setAlternatingRowColors(false);
        tableWidgetQueryResult->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
        tableWidgetQueryResult->setShowGrid(false);
        tableWidgetQueryResult->setGridStyle(Qt::SolidLine);
        tableWidgetQueryResult->setWordWrap(true);
        tableWidgetQueryResult->setColumnCount(8);
        tableWidgetQueryResult->horizontalHeader()->setDefaultSectionSize(154);

        LibraryLayout->addWidget(tableWidgetQueryResult);

        MainWindow->setCentralWidget(centralwidget);
        libGroup->raise();
        loginGroup->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1366, 22));
        menuClient = new QMenu(menubar);
        menuClient->setObjectName(QString::fromUtf8("menuClient"));
        menuFilter = new QMenu(menubar);
        menuFilter->setObjectName(QString::fromUtf8("menuFilter"));
        menuFilter->setEnabled(true);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuClient->menuAction());
        menubar->addAction(menuFilter->menuAction());
        menuClient->addAction(actionSettings);
        menuClient->addSeparator();
        menuClient->addAction(actionDisconnect);
        menuClient->addAction(actionQuit);
        menuFilter->addAction(actionHide_Show);

        retranslateUi(MainWindow);

        comboBoxPage->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        actionHide_Show->setText(QApplication::translate("MainWindow", "Hide/Show", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        loginGroup->setTitle(QApplication::translate("MainWindow", "Sign In", nullptr));
        pushButtonLogin->setText(QApplication::translate("MainWindow", "Login", nullptr));
        labelUsername->setText(QApplication::translate("MainWindow", "Username", nullptr));
        labelPassword->setText(QApplication::translate("MainWindow", "Password", nullptr));
        pushButtonCreateAccount->setText(QApplication::translate("MainWindow", "Create Account", nullptr));
        libGroup->setTitle(QApplication::translate("MainWindow", "Online Library", nullptr));
        filterGroup->setTitle(QApplication::translate("MainWindow", "Filter", nullptr));
        labelPage->setText(QApplication::translate("MainWindow", "Page", nullptr));
        labelItemsPage->setText(QApplication::translate("MainWindow", "Entries per page", nullptr));
        comboBoxItemsPage->setCurrentText(QString());
        labelTitle->setText(QApplication::translate("MainWindow", "Book Title", nullptr));
        labelAuthor->setText(QApplication::translate("MainWindow", "Author Name", nullptr));
        labelMinYear->setText(QApplication::translate("MainWindow", "After", nullptr));
        labelMaxYear->setText(QApplication::translate("MainWindow", "Before", nullptr));
        dateEditMin->setDisplayFormat(QApplication::translate("MainWindow", "yyyy", nullptr));
        dateEditMax->setDisplayFormat(QApplication::translate("MainWindow", "yyyy", nullptr));
        labelRating->setText(QApplication::translate("MainWindow", "Rating", nullptr));
        labelGenre->setText(QApplication::translate("MainWindow", "Genre", nullptr));
        checkBoxDrama->setText(QApplication::translate("MainWindow", "Drama", nullptr));
        checkBoxComedy->setText(QApplication::translate("MainWindow", "Comedy", nullptr));
        checkBoxThriller->setText(QApplication::translate("MainWindow", "Thriller", nullptr));
        checkBoxHorror->setText(QApplication::translate("MainWindow", "Horror", nullptr));
        checkBoxManual->setText(QApplication::translate("MainWindow", "Manual", nullptr));
        checkBoxBio->setText(QApplication::translate("MainWindow", "Biography", nullptr));
        checkBoxAutobio->setText(QApplication::translate("MainWindow", "Autobiography", nullptr));
        checkBoxChildren->setText(QApplication::translate("MainWindow", "Children", nullptr));
        checkBoxAction->setText(QApplication::translate("MainWindow", "Action", nullptr));
        checkBoxRomance->setText(QApplication::translate("MainWindow", "Romance", nullptr));
        checkBoxFantasy->setText(QApplication::translate("MainWindow", "Fantasy", nullptr));
        pushButtonApplyFilter->setText(QApplication::translate("MainWindow", "Filter Results", nullptr));
        getRecommendedBooks->setText(QApplication::translate("MainWindow", "Recommend Books", nullptr));
        menuClient->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
        menuFilter->setTitle(QApplication::translate("MainWindow", "Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
