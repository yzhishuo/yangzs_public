/****************************************************************************
** Meta object code from reading C++ file 'file_monitoring_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../file_monitoring_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'file_monitoring_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_File_Monitoring_Thread_t {
    QByteArrayData data[11];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_File_Monitoring_Thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_File_Monitoring_Thread_t qt_meta_stringdata_File_Monitoring_Thread = {
    {
QT_MOC_LITERAL(0, 0, 22), // "File_Monitoring_Thread"
QT_MOC_LITERAL(1, 23, 12), // "send_addfile"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "dirfile"
QT_MOC_LITERAL(4, 45, 15), // "send_deletefile"
QT_MOC_LITERAL(5, 61, 16), // "send_moniforfile"
QT_MOC_LITERAL(6, 78, 16), // "send_oldnamefile"
QT_MOC_LITERAL(7, 95, 10), // "olddirfile"
QT_MOC_LITERAL(8, 106, 10), // "newdirfile"
QT_MOC_LITERAL(9, 117, 20), // "start_FileMoniforing"
QT_MOC_LITERAL(10, 138, 3) // "dir"

    },
    "File_Monitoring_Thread\0send_addfile\0"
    "\0dirfile\0send_deletefile\0send_moniforfile\0"
    "send_oldnamefile\0olddirfile\0newdirfile\0"
    "start_FileMoniforing\0dir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_File_Monitoring_Thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       5,    1,   45,    2, 0x06 /* Public */,
       6,    2,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,

 // slots: parameters
    QMetaType::Int, QMetaType::QString,   10,

       0        // eod
};

void File_Monitoring_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        File_Monitoring_Thread *_t = static_cast<File_Monitoring_Thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_addfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_deletefile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->send_moniforfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->send_oldnamefile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: { int _r = _t->start_FileMoniforing((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (File_Monitoring_Thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&File_Monitoring_Thread::send_addfile)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (File_Monitoring_Thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&File_Monitoring_Thread::send_deletefile)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (File_Monitoring_Thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&File_Monitoring_Thread::send_moniforfile)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (File_Monitoring_Thread::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&File_Monitoring_Thread::send_oldnamefile)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject File_Monitoring_Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_File_Monitoring_Thread.data,
      qt_meta_data_File_Monitoring_Thread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *File_Monitoring_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *File_Monitoring_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_File_Monitoring_Thread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int File_Monitoring_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void File_Monitoring_Thread::send_addfile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void File_Monitoring_Thread::send_deletefile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void File_Monitoring_Thread::send_moniforfile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void File_Monitoring_Thread::send_oldnamefile(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
