/****************************************************************************
** Meta object code from reading C++ file 'BindHost.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BindHost.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BindHost.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BindHost_t {
    QByteArrayData data[9];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BindHost_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BindHost_t qt_meta_stringdata_BindHost = {
    {
QT_MOC_LITERAL(0, 0, 8), // "BindHost"
QT_MOC_LITERAL(1, 9, 16), // "BtnReturnClicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "BtnSaveClicked"
QT_MOC_LITERAL(4, 42, 9), // "CloseSlot"
QT_MOC_LITERAL(5, 52, 10), // "ReturnSlot"
QT_MOC_LITERAL(6, 63, 8), // "SaveSlot"
QT_MOC_LITERAL(7, 72, 7), // "UseSlot"
QT_MOC_LITERAL(8, 80, 11) // "timeoutSlot"

    },
    "BindHost\0BtnReturnClicked\0\0BtnSaveClicked\0"
    "CloseSlot\0ReturnSlot\0SaveSlot\0UseSlot\0"
    "timeoutSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BindHost[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BindHost::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BindHost *_t = static_cast<BindHost *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BtnReturnClicked(); break;
        case 1: _t->BtnSaveClicked(); break;
        case 2: _t->CloseSlot(); break;
        case 3: _t->ReturnSlot(); break;
        case 4: _t->SaveSlot(); break;
        case 5: _t->UseSlot(); break;
        case 6: _t->timeoutSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BindHost::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BindHost::BtnReturnClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BindHost::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BindHost::BtnSaveClicked)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject BindHost::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BindHost.data,
      qt_meta_data_BindHost,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BindHost::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BindHost::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BindHost.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int BindHost::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void BindHost::BtnReturnClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BindHost::BtnSaveClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
