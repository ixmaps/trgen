/****************************************************************************
** Meta object code from reading C++ file 'TrDo.h'
**
** Created: Wed Nov 17 18:32:20 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TrDo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrDo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrDo[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,
      22,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,    5,    5,    5, 0x08,
      78,   58,    5,    5, 0x08,
     124,  118,    5,    5, 0x08,
     159,    5,    5,    5, 0x08,
     175,  168,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TrDo[] = {
    "TrDo\0\0criticalError()\0tracerouteFinished()\0"
    "childStarted()\0exitCode,exitStatus\0"
    "childFinished(int,QProcess::ExitStatus)\0"
    "error\0childError(QProcess::ProcessError)\0"
    "cancel()\0result\0cancel(int)\0"
};

const QMetaObject TrDo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TrDo,
      qt_meta_data_TrDo, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrDo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrDo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrDo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrDo))
        return static_cast<void*>(const_cast< TrDo*>(this));
    return QObject::qt_metacast(_clname);
}

int TrDo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: criticalError(); break;
        case 1: tracerouteFinished(); break;
        case 2: childStarted(); break;
        case 3: childFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: childError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 5: cancel(); break;
        case 6: cancel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TrDo::criticalError()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TrDo::tracerouteFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
