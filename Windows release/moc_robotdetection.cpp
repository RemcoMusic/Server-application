/****************************************************************************
** Meta object code from reading C++ file 'robotdetection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Server-application/robot_detection/robotdetection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotdetection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_robotDetection_t {
    QByteArrayData data[9];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_robotDetection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_robotDetection_t qt_meta_stringdata_robotDetection = {
    {
QT_MOC_LITERAL(0, 0, 14), // "robotDetection"
QT_MOC_LITERAL(1, 15, 16), // "newFrameFinished"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 13), // "makeANewRobot"
QT_MOC_LITERAL(4, 47, 1), // "x"
QT_MOC_LITERAL(5, 49, 1), // "y"
QT_MOC_LITERAL(6, 51, 10), // "makeObject"
QT_MOC_LITERAL(7, 62, 1), // "i"
QT_MOC_LITERAL(8, 64, 14) // "startDetecting"

    },
    "robotDetection\0newFrameFinished\0\0"
    "makeANewRobot\0x\0y\0makeObject\0i\0"
    "startDetecting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_robotDetection[] = {

 // content:
       8,       // revision
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
       3,    2,   35,    2, 0x06 /* Public */,
       6,    3,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long,    4,    5,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void robotDetection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<robotDetection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFrameFinished(); break;
        case 1: _t->makeANewRobot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->makeObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 3: _t->startDetecting(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (robotDetection::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&robotDetection::newFrameFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (robotDetection::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&robotDetection::makeANewRobot)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (robotDetection::*)(int , int , long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&robotDetection::makeObject)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject robotDetection::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_robotDetection.data,
    qt_meta_data_robotDetection,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *robotDetection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *robotDetection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_robotDetection.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int robotDetection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void robotDetection::newFrameFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void robotDetection::makeANewRobot(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void robotDetection::makeObject(int _t1, int _t2, long _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
