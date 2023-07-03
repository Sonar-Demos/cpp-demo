/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client05/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[439];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 26), // "on_pushButtonLogin_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 32), // "on_pushButtonApplyFilter_clicked"
QT_MOC_LITERAL(4, 72, 30), // "on_dateEditMin_userDateChanged"
QT_MOC_LITERAL(5, 103, 4), // "date"
QT_MOC_LITERAL(6, 108, 28), // "on_sliderMinYear_sliderMoved"
QT_MOC_LITERAL(7, 137, 8), // "position"
QT_MOC_LITERAL(8, 146, 18), // "buttonRead_clicked"
QT_MOC_LITERAL(9, 165, 11), // "indexButton"
QT_MOC_LITERAL(10, 177, 22), // "buttonDownload_clicked"
QT_MOC_LITERAL(11, 200, 5), // "index"
QT_MOC_LITERAL(12, 206, 28), // "on_sliderMaxYear_sliderMoved"
QT_MOC_LITERAL(13, 235, 26), // "on_dateEditMax_dateChanged"
QT_MOC_LITERAL(14, 262, 29), // "on_actionDisconnect_triggered"
QT_MOC_LITERAL(15, 292, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(16, 320, 28), // "on_actionHide_Show_triggered"
QT_MOC_LITERAL(17, 349, 34), // "on_pushButtonCreateAccount_cl..."
QT_MOC_LITERAL(18, 384, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(19, 408, 30) // "on_getRecommendedBooks_clicked"

    },
    "MainWindow\0on_pushButtonLogin_clicked\0"
    "\0on_pushButtonApplyFilter_clicked\0"
    "on_dateEditMin_userDateChanged\0date\0"
    "on_sliderMinYear_sliderMoved\0position\0"
    "buttonRead_clicked\0indexButton\0"
    "buttonDownload_clicked\0index\0"
    "on_sliderMaxYear_sliderMoved\0"
    "on_dateEditMax_dateChanged\0"
    "on_actionDisconnect_triggered\0"
    "on_actionSettings_triggered\0"
    "on_actionHide_Show_triggered\0"
    "on_pushButtonCreateAccount_clicked\0"
    "on_actionQuit_triggered\0"
    "on_getRecommendedBooks_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       6,    1,   89,    2, 0x08 /* Private */,
       8,    1,   92,    2, 0x08 /* Private */,
      10,    1,   95,    2, 0x08 /* Private */,
      12,    1,   98,    2, 0x08 /* Private */,
      13,    1,  101,    2, 0x08 /* Private */,
      14,    0,  104,    2, 0x08 /* Private */,
      15,    0,  105,    2, 0x08 /* Private */,
      16,    0,  106,    2, 0x08 /* Private */,
      17,    0,  107,    2, 0x08 /* Private */,
      18,    0,  108,    2, 0x08 /* Private */,
      19,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonLogin_clicked(); break;
        case 1: _t->on_pushButtonApplyFilter_clicked(); break;
        case 2: _t->on_dateEditMin_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->on_sliderMinYear_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->buttonRead_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->buttonDownload_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_sliderMaxYear_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_dateEditMax_dateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 8: _t->on_actionDisconnect_triggered(); break;
        case 9: _t->on_actionSettings_triggered(); break;
        case 10: _t->on_actionHide_Show_triggered(); break;
        case 11: _t->on_pushButtonCreateAccount_clicked(); break;
        case 12: _t->on_actionQuit_triggered(); break;
        case 13: _t->on_getRecommendedBooks_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
