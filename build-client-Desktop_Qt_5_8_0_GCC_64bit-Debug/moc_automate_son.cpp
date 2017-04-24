/****************************************************************************
** Meta object code from reading C++ file 'automate_son.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../client/automate_son.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'automate_son.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Automate_son_t {
    QByteArrayData data[11];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Automate_son_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Automate_son_t qt_meta_stringdata_Automate_son = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Automate_son"
QT_MOC_LITERAL(1, 13, 13), // "signalMachine"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "signalType"
QT_MOC_LITERAL(4, 39, 2), // "on"
QT_MOC_LITERAL(5, 42, 6), // "param1"
QT_MOC_LITERAL(6, 49, 6), // "param2"
QT_MOC_LITERAL(7, 56, 11), // "signalSound"
QT_MOC_LITERAL(8, 68, 10), // "signalMute"
QT_MOC_LITERAL(9, 79, 7), // "setMute"
QT_MOC_LITERAL(10, 87, 4) // "mute"

    },
    "Automate_son\0signalMachine\0\0signalType\0"
    "on\0param1\0param2\0signalSound\0signalMute\0"
    "setMute\0mute"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Automate_son[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   49,    2, 0x06 /* Public */,
       1,    3,   58,    2, 0x26 /* Public | MethodCloned */,
       1,    2,   65,    2, 0x26 /* Public | MethodCloned */,
       1,    1,   70,    2, 0x26 /* Public | MethodCloned */,
       7,    0,   73,    2, 0x06 /* Public */,
       8,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Int, QMetaType::Int,    2,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool, QMetaType::Int,    2,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    4,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   10,

       0        // eod
};

void Automate_son::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Automate_son *_t = static_cast<Automate_son *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMachine((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->signalMachine((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->signalMachine((*reinterpret_cast< signalType(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->signalMachine((*reinterpret_cast< signalType(*)>(_a[1]))); break;
        case 4: _t->signalSound(); break;
        case 5: _t->signalMute(); break;
        case 6: _t->setMute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Automate_son::*_t)(signalType , bool , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Automate_son::signalMachine)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Automate_son::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Automate_son::signalSound)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Automate_son::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Automate_son::signalMute)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Automate_son::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Automate_son.data,
      qt_meta_data_Automate_son,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Automate_son::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Automate_son::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Automate_son.stringdata0))
        return static_cast<void*>(const_cast< Automate_son*>(this));
    return QObject::qt_metacast(_clname);
}

int Automate_son::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Automate_son::signalMachine(signalType _t1, bool _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 4
void Automate_son::signalSound()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Automate_son::signalMute()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
