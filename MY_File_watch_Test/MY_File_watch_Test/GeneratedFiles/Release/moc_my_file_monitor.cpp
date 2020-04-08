/****************************************************************************
** Meta object code from reading C++ file 'my_file_monitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../my_file_monitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_file_monitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_My_File_Monitor_t {
    QByteArrayData data[17];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_My_File_Monitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_My_File_Monitor_t qt_meta_stringdata_My_File_Monitor = {
    {
QT_MOC_LITERAL(0, 0, 15), // "My_File_Monitor"
QT_MOC_LITERAL(1, 16, 10), // "sen_mondir"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "dir"
QT_MOC_LITERAL(4, 32, 14), // "sen_upfilepath"
QT_MOC_LITERAL(5, 47, 8), // "filepath"
QT_MOC_LITERAL(6, 56, 12), // "slot_addfile"
QT_MOC_LITERAL(7, 69, 4), // "path"
QT_MOC_LITERAL(8, 74, 15), // "slot_deletefile"
QT_MOC_LITERAL(9, 90, 16), // "slot_moniforfile"
QT_MOC_LITERAL(10, 107, 16), // "slot_oldnamefile"
QT_MOC_LITERAL(11, 124, 7), // "oldpath"
QT_MOC_LITERAL(12, 132, 7), // "newpath"
QT_MOC_LITERAL(13, 140, 20), // "slot_obs_sql_fileflg"
QT_MOC_LITERAL(14, 161, 8), // "upoklist"
QT_MOC_LITERAL(15, 170, 14), // "time_out_upobs"
QT_MOC_LITERAL(16, 185, 20) // "time_out_upfileinfor"

    },
    "My_File_Monitor\0sen_mondir\0\0dir\0"
    "sen_upfilepath\0filepath\0slot_addfile\0"
    "path\0slot_deletefile\0slot_moniforfile\0"
    "slot_oldnamefile\0oldpath\0newpath\0"
    "slot_obs_sql_fileflg\0upoklist\0"
    "time_out_upobs\0time_out_upfileinfor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_My_File_Monitor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   65,    2, 0x08 /* Private */,
       8,    1,   68,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      10,    2,   74,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      15,    0,   82,    2, 0x08 /* Private */,
      16,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QStringList,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QStringList,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void My_File_Monitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        My_File_Monitor *_t = static_cast<My_File_Monitor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sen_mondir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sen_upfilepath((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->slot_addfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slot_deletefile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->slot_moniforfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slot_oldnamefile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->slot_obs_sql_fileflg((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->time_out_upobs(); break;
        case 8: _t->time_out_upfileinfor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (My_File_Monitor::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&My_File_Monitor::sen_mondir)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (My_File_Monitor::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&My_File_Monitor::sen_upfilepath)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject My_File_Monitor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_My_File_Monitor.data,
      qt_meta_data_My_File_Monitor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *My_File_Monitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *My_File_Monitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_My_File_Monitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int My_File_Monitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void My_File_Monitor::sen_mondir(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void My_File_Monitor::sen_upfilepath(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
