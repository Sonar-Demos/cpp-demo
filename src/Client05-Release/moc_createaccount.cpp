/****************************************************************************
** Meta object code from reading C++ file 'createaccount.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Client05/createaccount.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createaccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateAccount_t {
    QByteArrayData data[8];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateAccount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateAccount_t qt_meta_stringdata_CreateAccount = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CreateAccount"
QT_MOC_LITERAL(1, 14, 13), // "callOnDestroy"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "onConfirmClick"
QT_MOC_LITERAL(4, 44, 13), // "onCancelClick"
QT_MOC_LITERAL(5, 58, 12), // "onNameModify"
QT_MOC_LITERAL(6, 71, 12), // "onPassModify"
QT_MOC_LITERAL(7, 84, 19) // "onConfirmPassModify"

    },
    "CreateAccount\0callOnDestroy\0\0"
    "onConfirmClick\0onCancelClick\0onNameModify\0"
    "onPassModify\0onConfirmPassModify"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateAccount[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       6,    1,   50,    2, 0x08 /* Private */,
       7,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void CreateAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateAccount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->callOnDestroy(); break;
        case 1: _t->onConfirmClick(); break;
        case 2: _t->onCancelClick(); break;
        case 3: _t->onNameModify((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onPassModify((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->onConfirmPassModify((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CreateAccount::staticMetaObject = { {
    &QWindow::staticMetaObject,
    qt_meta_stringdata_CreateAccount.data,
    qt_meta_data_CreateAccount,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CreateAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreateAccount.stringdata0))
        return static_cast<void*>(this);
    return QWindow::qt_metacast(_clname);
}

int CreateAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
