/****************************************************************************
** Meta object code from reading C++ file 'WirelessCon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WirelessCon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WirelessCon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WirelessCon_t {
    QByteArrayData data[8];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WirelessCon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WirelessCon_t qt_meta_stringdata_WirelessCon = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WirelessCon"
QT_MOC_LITERAL(1, 12, 11), // "BtnNextWifi"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "BtnNextWired"
QT_MOC_LITERAL(4, 38, 18), // "StackedWidgetClose"
QT_MOC_LITERAL(5, 57, 15), // "clickedWifiItem"
QT_MOC_LITERAL(6, 73, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 90, 7) // "curItem"

    },
    "WirelessCon\0BtnNextWifi\0\0BtnNextWired\0"
    "StackedWidgetClose\0clickedWifiItem\0"
    "QListWidgetItem*\0curItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WirelessCon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void WirelessCon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WirelessCon *_t = static_cast<WirelessCon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BtnNextWifi(); break;
        case 1: _t->BtnNextWired(); break;
        case 2: _t->StackedWidgetClose(); break;
        case 3: _t->clickedWifiItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WirelessCon::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WirelessCon::BtnNextWifi)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WirelessCon::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WirelessCon::BtnNextWired)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WirelessCon::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WirelessCon::StackedWidgetClose)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WirelessCon::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_WirelessCon.data,
      qt_meta_data_WirelessCon,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WirelessCon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WirelessCon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WirelessCon.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WirelessCon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WirelessCon::BtnNextWifi()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WirelessCon::BtnNextWired()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WirelessCon::StackedWidgetClose()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
