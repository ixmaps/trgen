/****************************************************************************
** Meta object code from reading C++ file 'SingleRunDialog.h'
**
** Created: Wed Nov 17 18:32:15 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SingleRunDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SingleRunDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SingleRunDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   16,   16,   16, 0x08,
      74,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SingleRunDialog[] = {
    "SingleRunDialog\0\0hostname\0"
    "tracerouteHost(QString)\0on_buttonBox_accepted()\0"
    "on_buttonBox_rejected()\0"
};

const QMetaObject SingleRunDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SingleRunDialog,
      qt_meta_data_SingleRunDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SingleRunDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SingleRunDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SingleRunDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SingleRunDialog))
        return static_cast<void*>(const_cast< SingleRunDialog*>(this));
    if (!strcmp(_clname, "Ui_SingleRunDialog"))
        return static_cast< Ui_SingleRunDialog*>(const_cast< SingleRunDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SingleRunDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tracerouteHost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: on_buttonBox_accepted(); break;
        case 2: on_buttonBox_rejected(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SingleRunDialog::tracerouteHost(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
