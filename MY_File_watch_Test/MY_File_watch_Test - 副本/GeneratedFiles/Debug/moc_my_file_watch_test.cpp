/****************************************************************************
** Meta object code from reading C++ file 'my_file_watch_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../my_file_watch_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_file_watch_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MY_File_watch_Test_t {
    QByteArrayData data[22];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MY_File_watch_Test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MY_File_watch_Test_t qt_meta_stringdata_MY_File_watch_Test = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MY_File_watch_Test"
QT_MOC_LITERAL(1, 19, 10), // "sen_mondir"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "dir"
QT_MOC_LITERAL(4, 35, 14), // "sen_upfilepath"
QT_MOC_LITERAL(5, 50, 8), // "filepath"
QT_MOC_LITERAL(6, 59, 12), // "slot_addfile"
QT_MOC_LITERAL(7, 72, 4), // "path"
QT_MOC_LITERAL(8, 77, 15), // "slot_deletefile"
QT_MOC_LITERAL(9, 93, 16), // "slot_moniforfile"
QT_MOC_LITERAL(10, 110, 16), // "slot_oldnamefile"
QT_MOC_LITERAL(11, 127, 7), // "oldpath"
QT_MOC_LITERAL(12, 135, 7), // "newpath"
QT_MOC_LITERAL(13, 143, 20), // "slot_obs_sql_fileflg"
QT_MOC_LITERAL(14, 164, 8), // "upoklist"
QT_MOC_LITERAL(15, 173, 27), // "on_btn_open_filedir_clicked"
QT_MOC_LITERAL(16, 201, 22), // "on_btn_monitor_clicked"
QT_MOC_LITERAL(17, 224, 21), // "on_btn_insert_clicked"
QT_MOC_LITERAL(18, 246, 19), // "on_btn_find_clicked"
QT_MOC_LITERAL(19, 266, 21), // "on_btn_update_clicked"
QT_MOC_LITERAL(20, 288, 21), // "on_btn_delete_clicked"
QT_MOC_LITERAL(21, 310, 14) // "time_out_upobs"

    },
    "MY_File_watch_Test\0sen_mondir\0\0dir\0"
    "sen_upfilepath\0filepath\0slot_addfile\0"
    "path\0slot_deletefile\0slot_moniforfile\0"
    "slot_oldnamefile\0oldpath\0newpath\0"
    "slot_obs_sql_fileflg\0upoklist\0"
    "on_btn_open_filedir_clicked\0"
    "on_btn_monitor_clicked\0on_btn_insert_clicked\0"
    "on_btn_find_clicked\0on_btn_update_clicked\0"
    "on_btn_delete_clicked\0time_out_upobs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MY_File_watch_Test[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   90,    2, 0x0a /* Public */,
       8,    1,   93,    2, 0x0a /* Public */,
       9,    1,   96,    2, 0x0a /* Public */,
      10,    2,   99,    2, 0x0a /* Public */,
      13,    1,  104,    2, 0x0a /* Public */,
      15,    0,  107,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    0,  109,    2, 0x0a /* Public */,
      18,    0,  110,    2, 0x0a /* Public */,
      19,    0,  111,    2, 0x0a /* Public */,
      20,    0,  112,    2, 0x0a /* Public */,
      21,    0,  113,    2, 0x0a /* Public */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MY_File_watch_Test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MY_File_watch_Test *_t = static_cast<MY_File_watch_Test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sen_mondir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sen_upfilepath((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->slot_addfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->slot_deletefile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->slot_moniforfile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slot_oldnamefile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->slot_obs_sql_fileflg((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->on_btn_open_filedir_clicked(); break;
        case 8: _t->on_btn_monitor_clicked(); break;
        case 9: _t->on_btn_insert_clicked(); break;
        case 10: _t->on_btn_find_clicked(); break;
        case 11: _t->on_btn_update_clicked(); break;
        case 12: _t->on_btn_delete_clicked(); break;
        case 13: _t->time_out_upobs(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MY_File_watch_Test::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MY_File_watch_Test::sen_mondir)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MY_File_watch_Test::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MY_File_watch_Test::sen_upfilepath)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MY_File_watch_Test::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MY_File_watch_Test.data,
      qt_meta_data_MY_File_watch_Test,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MY_File_watch_Test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MY_File_watch_Test::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MY_File_watch_Test.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MY_File_watch_Test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MY_File_watch_Test::sen_mondir(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MY_File_watch_Test::sen_upfilepath(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
