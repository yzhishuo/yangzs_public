/****************************************************************************
** Meta object code from reading C++ file 'upfile_obs_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../upfile_obs_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upfile_obs_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UpFile_OBS_Thread_t {
    QByteArrayData data[8];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpFile_OBS_Thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpFile_OBS_Thread_t qt_meta_stringdata_UpFile_OBS_Thread = {
    {
QT_MOC_LITERAL(0, 0, 17), // "UpFile_OBS_Thread"
QT_MOC_LITERAL(1, 18, 16), // "send_obs_up_eror"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "errlist"
QT_MOC_LITERAL(4, 44, 14), // "send_obs_up_ok"
QT_MOC_LITERAL(5, 59, 8), // "upoklist"
QT_MOC_LITERAL(6, 68, 10), // "upfile_OBS"
QT_MOC_LITERAL(7, 79, 8) // "filepath"

    },
    "UpFile_OBS_Thread\0send_obs_up_eror\0\0"
    "errlist\0send_obs_up_ok\0upoklist\0"
    "upfile_OBS\0filepath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpFile_OBS_Thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QStringList,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList,    7,

       0        // eod
};

void UpFile_OBS_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UpFile_OBS_Thread *_t = static_cast<UpFile_OBS_Thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_obs_up_eror((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->send_obs_up_ok((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->upfile_OBS((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (UpFile_OBS_Thread::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpFile_OBS_Thread::send_obs_up_eror)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UpFile_OBS_Thread::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpFile_OBS_Thread::send_obs_up_ok)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject UpFile_OBS_Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UpFile_OBS_Thread.data,
      qt_meta_data_UpFile_OBS_Thread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UpFile_OBS_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpFile_OBS_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UpFile_OBS_Thread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int UpFile_OBS_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void UpFile_OBS_Thread::send_obs_up_eror(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpFile_OBS_Thread::send_obs_up_ok(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
