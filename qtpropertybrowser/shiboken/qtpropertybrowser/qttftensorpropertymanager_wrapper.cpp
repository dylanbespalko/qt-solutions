
// default includes
#include <shiboken.h>
#ifndef QT_NO_VERSION_TAGGING
#  define QT_NO_VERSION_TAGGING
#endif
#include <QDebug>
#include <pysidesignal.h>
#include <pysideproperty.h>
#include <pyside.h>
#include <destroylistener.h>
#include <qapp_macro.h>
#include <typeinfo>
#include <signalmanager.h>
#include <pysidemetafunction.h>

// module include
#include "qtpropertybrowser_python.h"

// main header
#include "qttftensorpropertymanager_wrapper.h"

// inner classes

// Extra includes
#include <QList>
#include <QSet>
#include <QVector>
#include <qbrush.h>
#include <qbytearray.h>
#include <qicon.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qtpropertybrowser.h>
#include <qtpropertymanager.h>


// Native ---------------------------------------------------------

void QtTFTensorPropertyManagerWrapper::pysideInitQtMetaTypes()
{
}

QtTFTensorPropertyManagerWrapper::QtTFTensorPropertyManagerWrapper(QObject * parent) : QtTFTensorPropertyManager(parent) {
    // ... middle
}

bool QtTFTensorPropertyManagerWrapper::check(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "check"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::check(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return false;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.check", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QIcon QtTFTensorPropertyManagerWrapper::checkIcon(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return {};
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "checkIcon"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::checkIcon(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return {};
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QICON_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.checkIcon", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QIcon >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return {};
    }
    ::QIcon cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtTFTensorPropertyManagerWrapper::childEvent(QChildEvent * event)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "childEvent"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QObject::childEvent(event);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QCHILDEVENT_IDX]), event)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
}

void QtTFTensorPropertyManagerWrapper::connectNotify(const QMetaMethod & signal)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "connectNotify"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QObject::connectNotify(signal);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QMETAMETHOD_IDX]), &signal)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QtProperty * QtTFTensorPropertyManagerWrapper::createProperty()
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return nullptr;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "createProperty"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::createProperty();
    }

    Shiboken::AutoDecRef pyArgs(PyTuple_New(0));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return nullptr;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.createProperty", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QtProperty >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return nullptr;
    }
    ::QtProperty* cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtTFTensorPropertyManagerWrapper::customEvent(QEvent * event)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "customEvent"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QObject::customEvent(event);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QEVENT_IDX]), event)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
}

void QtTFTensorPropertyManagerWrapper::disconnectNotify(const QMetaMethod & signal)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "disconnectNotify"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QObject::disconnectNotify(signal);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QMETAMETHOD_IDX]), &signal)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QString QtTFTensorPropertyManagerWrapper::displayText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "displayText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::displayText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.displayText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QLineEdit::EchoMode QtTFTensorPropertyManagerWrapper::echoMode(const QtProperty * arg__1) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return QLineEdit::Normal;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "echoMode"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::echoMode(arg__1);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), arg__1)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return QLineEdit::Normal;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkPySide2_QtWidgetsTypes[SBK_QLINEEDIT_ECHOMODE_IDX])->converter, pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.echoMode", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QLineEdit::EchoMode >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return QLineEdit::Normal;
    }
    ::QLineEdit::EchoMode cppResult{QLineEdit::Normal};
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

bool QtTFTensorPropertyManagerWrapper::event(QEvent * event)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "event"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::event(event);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QEVENT_IDX]), event)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return false;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.event", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
    return cppResult;
}

bool QtTFTensorPropertyManagerWrapper::eventFilter(QObject * watched, QEvent * event)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "eventFilter"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QObject::eventFilter(watched, event);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(NN)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), watched),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QEVENT_IDX]), event)
    ));
    bool invalidateArg2 = PyTuple_GET_ITEM(pyArgs, 1)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return false;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.eventFilter", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    if (invalidateArg2)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 1));
    return cppResult;
}

QBrush QtTFTensorPropertyManagerWrapper::foreground(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return {};
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "foreground"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::foreground(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return {};
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QBRUSH_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.foreground", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QBrush >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return {};
    }
    ::QBrush cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtTFTensorPropertyManagerWrapper::formatText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "formatText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::formatText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.formatText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

bool QtTFTensorPropertyManagerWrapper::hasValue(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "hasValue"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::hasValue(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return false;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.hasValue", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtTFTensorPropertyManagerWrapper::initializeProperty(QtProperty * property)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "initializeProperty"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtTFTensorPropertyManager::initializeProperty(property);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

bool QtTFTensorPropertyManagerWrapper::isReadOnly(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "isReadOnly"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::isReadOnly(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return false;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.isReadOnly", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtTFTensorPropertyManagerWrapper::maximumText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "maximumText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::maximumText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.maximumText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtTFTensorPropertyManagerWrapper::minimumText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "minimumText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::minimumText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.minimumText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtTFTensorPropertyManagerWrapper::pkAvgText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "pkAvgText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::pkAvgText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.pkAvgText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtTFTensorPropertyManagerWrapper::reinitializeProperty(QtProperty * property)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "reinitializeProperty"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtTFTensorPropertyManager::reinitializeProperty(property);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

void QtTFTensorPropertyManagerWrapper::timerEvent(QTimerEvent * event)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "timerEvent"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QObject::timerEvent(event);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QTIMEREVENT_IDX]), event)
    ));
    bool invalidateArg1 = PyTuple_GET_ITEM(pyArgs, 0)->ob_refcnt == 1;

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
}

void QtTFTensorPropertyManagerWrapper::uninitializeProperty(QtProperty * property)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "uninitializeProperty"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtTFTensorPropertyManager::uninitializeProperty(property);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QString QtTFTensorPropertyManagerWrapper::unitText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "unitText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::unitText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.unitText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QIcon QtTFTensorPropertyManagerWrapper::valueIcon(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return {};
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "valueIcon"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::valueIcon(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return {};
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QICON_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.valueIcon", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QIcon >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return {};
    }
    ::QIcon cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtTFTensorPropertyManagerWrapper::valueText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "valueText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtTFTensorPropertyManager::valueText(property);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return ::QString();
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtTFTensorPropertyManager.valueText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

const QMetaObject* QtTFTensorPropertyManagerWrapper::metaObject() const
{
    if (QObject::d_ptr->metaObject)
        return QObject::d_ptr->dynamicMetaObject();
    SbkObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(this);
    if (pySelf == NULL)
        return QtTFTensorPropertyManager::metaObject();
    return PySide::SignalManager::retrieveMetaObject(reinterpret_cast<PyObject*>(pySelf));
}

int QtTFTensorPropertyManagerWrapper::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    int result = QtTFTensorPropertyManager::qt_metacall(call, id, args);
    return result < 0 ? result : PySide::SignalManager::qt_metacall(this, call, id, args);
}

void* QtTFTensorPropertyManagerWrapper::qt_metacast(const char* _clname)
{
        if (!_clname) return 0;
        SbkObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(this);
        if (pySelf && PySide::inherits(Py_TYPE(pySelf), _clname))
                return static_cast<void*>(const_cast< QtTFTensorPropertyManagerWrapper* >(this));
        return QtTFTensorPropertyManager::qt_metacast(_clname);
}

QtTFTensorPropertyManagerWrapper::~QtTFTensorPropertyManagerWrapper()
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(this);
    Shiboken::Object::destroy(wrapper, this);
}

// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_QtTFTensorPropertyManager_Init(PyObject* self, PyObject* args, PyObject* kwds)
{
    const char* argNames[] = {"parent"};
    const QMetaObject* metaObject;
    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::QtTFTensorPropertyManager >()))
        return -1;

    ::QtTFTensorPropertyManagerWrapper* cptr = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_ParseTuple(args, "|O:QtTFTensorPropertyManager", &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: QtTFTensorPropertyManager(QObject*)
    if (numArgs == 0) {
        overloadId = 0; // QtTFTensorPropertyManager(QObject*)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0])))) {
        overloadId = 0; // QtTFTensorPropertyManager(QObject*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManager_Init_TypeError;

    // Call function/method
    {
        if (kwds) {
            PyObject* value = PyDict_GetItemString(kwds, "parent");
            if (value && pyArgs[0]) {
                PyErr_SetString(PyExc_TypeError, "qtpropertybrowser.QtTFTensorPropertyManager(): got multiple values for keyword argument 'parent'.");
                return -1;
            } else if (value) {
                pyArgs[0] = value;
                if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0]))))
                    goto Sbk_QtTFTensorPropertyManager_Init_TypeError;
            }
        }
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return -1;
        ::QObject* cppArg0 = nullptr;
        if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

        if (!PyErr_Occurred()) {
            // QtTFTensorPropertyManager(QObject*)
            void* addr = PySide::nextQObjectMemoryAddr();
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            if (addr) {
                cptr = new (addr) ::QtTFTensorPropertyManagerWrapper(cppArg0);
                PySide::setNextQObjectMemoryAddr(0);
            } else {
                cptr = new ::QtTFTensorPropertyManagerWrapper(cppArg0);
            }

            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            Shiboken::Object::setParent(pyArgs[0], self);
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::QtTFTensorPropertyManager >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_QtTFTensorPropertyManager_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    Shiboken::Object::setHasCppWrapper(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);

    // QObject setup
    PySide::Signal::updateSourceObject(self);
    metaObject = cptr->metaObject(); // <- init python qt properties
    if (kwds && !PySide::fillQtProperties(self, metaObject, kwds, argNames, 1))
        return -1;


    return 1;

    Sbk_QtTFTensorPropertyManager_Init_TypeError:
        const char* overloads[] = {"PySide2.QtCore.QObject = nullptr", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager", overloads);
        return -1;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_absTol(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: absTol(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // absTol(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_absTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // absTol(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QVector<double > cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->absTol(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_absTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.absTol", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_check(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: check(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // check(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_check_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // check(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = Shiboken::Object::hasCppWrapper(reinterpret_cast<SbkObject*>(self)) ? const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->::QtTFTensorPropertyManager::check(cppArg0) : const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->check(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_check_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.check", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_checkIcon(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: checkIcon(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // checkIcon(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_checkIcon_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // checkIcon(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QIcon cppResult = ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::checkIcon_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QICON_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_checkIcon_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.checkIcon", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_connect_signals(PyObject* self)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // connect_signals()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->connect_signals();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_disconnect_signals(PyObject* self)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // disconnect_signals()const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->disconnect_signals();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_foreground(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: foreground(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // foreground(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_foreground_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // foreground(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QBrush cppResult = Shiboken::Object::hasCppWrapper(reinterpret_cast<SbkObject*>(self)) ? const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->::QtTFTensorPropertyManager::foreground(cppArg0) : const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->foreground(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QBRUSH_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_foreground_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.foreground", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_format(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: format(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // format(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_format_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // format(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            Format cppResult = Format(const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->format(cppArg0));
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_FORMAT_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_format_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.format", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_formatText(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: formatText(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // formatText(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_formatText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // formatText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::formatText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_formatText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.formatText", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_initializeProperty(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: initializeProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // initializeProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_initializeProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // initializeProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::initializeProperty_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_initializeProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.initializeProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_isReadOnly(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: isReadOnly(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // isReadOnly(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_isReadOnly_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // isReadOnly(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = Shiboken::Object::hasCppWrapper(reinterpret_cast<SbkObject*>(self)) ? const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->::QtTFTensorPropertyManager::isReadOnly(cppArg0) : const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->isReadOnly(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_isReadOnly_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.isReadOnly", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_maximum(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: maximum(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // maximum(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_maximum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // maximum(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QVector<double > cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->maximum(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_maximum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.maximum", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_minimum(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: minimum(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // minimum(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_minimum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // minimum(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QVector<double > cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->minimum(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_minimum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.minimum", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_pkAvg(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: pkAvg(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // pkAvg(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_pkAvg_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // pkAvg(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            PkAvg cppResult = PkAvg(const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->pkAvg(cppArg0));
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_PKAVG_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_pkAvg_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.pkAvg", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_pkAvgText(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: pkAvgText(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // pkAvgText(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_pkAvgText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // pkAvgText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::pkAvgText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_pkAvgText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.pkAvgText", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_precision(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: precision(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // precision(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_precision_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // precision(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            int cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->precision(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_precision_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.precision", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_reinitializeProperty(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: reinitializeProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // reinitializeProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_reinitializeProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // reinitializeProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::reinitializeProperty_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_reinitializeProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.reinitializeProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_relTol(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: relTol(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // relTol(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_relTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // relTol(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QVector<double > cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->relTol(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_relTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.relTol", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_scale(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: scale(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // scale(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_scale_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // scale(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            Scale cppResult = Scale(const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->scale(cppArg0));
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_SCALE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_scale_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.scale", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setAbsTol(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setAbsTol", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setAbsTol(QtProperty*,QVector<double>)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], (pyArgs[1])))) {
        overloadId = 0; // setAbsTol(QtProperty*,QVector<double>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setAbsTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<double > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setAbsTol(QtProperty*,QVector<double>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setAbsTol(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setAbsTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setAbsTol", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setCheck(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setCheck", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setCheck(QtProperty*,bool)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArgs[1])))) {
        overloadId = 0; // setCheck(QtProperty*,bool)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setCheck_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        bool cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setCheck(QtProperty*,bool)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setCheck(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setCheck_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, bool", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setCheck", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setFormat(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setFormat", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setFormat(QtProperty*,Format)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_FORMAT_IDX])->converter, (pyArgs[1])))) {
        overloadId = 0; // setFormat(QtProperty*,Format)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setFormat_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::Format cppArg1{RE};
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setFormat(QtProperty*,Format)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setFormat(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setFormat_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, qtpropertybrowser.Format", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setFormat", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setMaximum(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setMaximum", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setMaximum(QtProperty*,QVector<double>)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], (pyArgs[1])))) {
        overloadId = 0; // setMaximum(QtProperty*,QVector<double>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setMaximum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<double > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setMaximum(QtProperty*,QVector<double>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setMaximum(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setMaximum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setMaximum", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setMinimum(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setMinimum", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setMinimum(QtProperty*,QVector<double>)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], (pyArgs[1])))) {
        overloadId = 0; // setMinimum(QtProperty*,QVector<double>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setMinimum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<double > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setMinimum(QtProperty*,QVector<double>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setMinimum(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setMinimum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setMinimum", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setPkAvg(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setPkAvg", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setPkAvg(QtProperty*,PkAvg)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_PKAVG_IDX])->converter, (pyArgs[1])))) {
        overloadId = 0; // setPkAvg(QtProperty*,PkAvg)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setPkAvg_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::PkAvg cppArg1{PK};
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setPkAvg(QtProperty*,PkAvg)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setPkAvg(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setPkAvg_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, qtpropertybrowser.PkAvg", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setPkAvg", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setPrecision(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setPrecision", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setPrecision(QtProperty*,int)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<int>(), (pyArgs[1])))) {
        overloadId = 0; // setPrecision(QtProperty*,int)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setPrecision_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        int cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setPrecision(QtProperty*,int)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setPrecision(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setPrecision_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, int", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setPrecision", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setRange(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setRange", 3, 3, &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2])))
        return 0;


    // Overloaded function decisor
    // 0: setRange(QtProperty*,QVector<double>,QVector<double>)
    if (numArgs == 3
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], (pyArgs[1])))
        && (pythonToCpp[2] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], (pyArgs[2])))) {
        overloadId = 0; // setRange(QtProperty*,QVector<double>,QVector<double>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setRange_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<double > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);
        ::QVector<double > cppArg2;
        pythonToCpp[2](pyArgs[2], &cppArg2);

        if (!PyErr_Occurred()) {
            // setRange(QtProperty*,QVector<double>,QVector<double>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setRange(cppArg0, cppArg1, cppArg2);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setRange_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setRange", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setReadOnly(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setReadOnly", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setReadOnly(QtProperty*,bool)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArgs[1])))) {
        overloadId = 0; // setReadOnly(QtProperty*,bool)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setReadOnly_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        bool cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setReadOnly(QtProperty*,bool)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setReadOnly(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setReadOnly_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, bool", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setReadOnly", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setRelTol(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setRelTol", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setRelTol(QtProperty*,QVector<double>)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_DOUBLE_IDX], (pyArgs[1])))) {
        overloadId = 0; // setRelTol(QtProperty*,QVector<double>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setRelTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<double > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setRelTol(QtProperty*,QVector<double>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setRelTol(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setRelTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setRelTol", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setScale(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setScale", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setScale(QtProperty*,Scale)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_SCALE_IDX])->converter, (pyArgs[1])))) {
        overloadId = 0; // setScale(QtProperty*,Scale)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setScale_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::Scale cppArg1{T};
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setScale(QtProperty*,Scale)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setScale(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setScale_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, qtpropertybrowser.Scale", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setScale", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setSingleStep(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setSingleStep", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setSingleStep(QtProperty*,QVector<QComplex>)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_QCOMPLEX_IDX], (pyArgs[1])))) {
        overloadId = 0; // setSingleStep(QtProperty*,QVector<QComplex>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setSingleStep_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<QComplex > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setSingleStep(QtProperty*,QVector<QComplex>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setSingleStep(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setSingleStep_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setSingleStep", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setSize(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setSize", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setSize(QtProperty*,int)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<int>(), (pyArgs[1])))) {
        overloadId = 0; // setSize(QtProperty*,int)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setSize_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        int cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setSize(QtProperty*,int)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setSize(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setSize_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, int", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setSize", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setUnit(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setUnit", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setUnit(QtProperty*,QString)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArgs[1])))) {
        overloadId = 0; // setUnit(QtProperty*,QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setUnit_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QString cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setUnit(QtProperty*,QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setUnit(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setUnit_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, unicode", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setUnit", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_setValue(PyObject* self, PyObject* args)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setValue", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setValue(QtProperty*,QVector<QComplex>)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_QCOMPLEX_IDX], (pyArgs[1])))) {
        overloadId = 0; // setValue(QtProperty*,QVector<QComplex>)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_setValue_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        ::QVector<QComplex > cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setValue(QtProperty*,QVector<QComplex>)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setValue(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_setValue_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, list", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtTFTensorPropertyManager.setValue", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_singleStep(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: singleStep(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // singleStep(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_singleStep_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // singleStep(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QVector<QComplex > cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->singleStep(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_QCOMPLEX_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_singleStep_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.singleStep", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_size(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: size(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // size(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_size_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // size(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            int cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->size(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_size_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.size", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_subComplexPropertyManager(PyObject* self)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // subComplexPropertyManager()const
            QtComplexPropertyManager * cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->subComplexPropertyManager();
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXPROPERTYMANAGER_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_uninitializeProperty(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: uninitializeProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // uninitializeProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_uninitializeProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // uninitializeProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::uninitializeProperty_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtTFTensorPropertyManagerFunc_uninitializeProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.uninitializeProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_unit(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: unit(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // unit(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_unit_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // unit(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->unit(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_unit_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.unit", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_unitText(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: unitText(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // unitText(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_unitText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // unitText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::unitText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_unitText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.unitText", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_value(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: value(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // value(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_value_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // value(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QVector<QComplex > cppResult = const_cast<const ::QtTFTensorPropertyManagerWrapper*>(cppSelf)->value(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QVECTOR_QCOMPLEX_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_value_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.value", overloads);
        return 0;
}

static PyObject* Sbk_QtTFTensorPropertyManagerFunc_valueText(PyObject* self, PyObject* pyArg)
{
    QtTFTensorPropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtTFTensorPropertyManagerWrapper*)reinterpret_cast< ::QtTFTensorPropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: valueText(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // valueText(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtTFTensorPropertyManagerFunc_valueText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // valueText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtTFTensorPropertyManagerWrapper*) cppSelf)->QtTFTensorPropertyManagerWrapper::valueText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtTFTensorPropertyManagerFunc_valueText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtTFTensorPropertyManager.valueText", overloads);
        return 0;
}

static PyMethodDef Sbk_QtTFTensorPropertyManager_methods[] = {
    {"absTol", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_absTol, METH_O},
    {"check", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_check, METH_O},
    {"checkIcon", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_checkIcon, METH_O},
    {"connect_signals", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_connect_signals, METH_NOARGS},
    {"disconnect_signals", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_disconnect_signals, METH_NOARGS},
    {"foreground", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_foreground, METH_O},
    {"format", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_format, METH_O},
    {"formatText", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_formatText, METH_O},
    {"initializeProperty", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_initializeProperty, METH_O},
    {"isReadOnly", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_isReadOnly, METH_O},
    {"maximum", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_maximum, METH_O},
    {"minimum", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_minimum, METH_O},
    {"pkAvg", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_pkAvg, METH_O},
    {"pkAvgText", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_pkAvgText, METH_O},
    {"precision", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_precision, METH_O},
    {"reinitializeProperty", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_reinitializeProperty, METH_O},
    {"relTol", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_relTol, METH_O},
    {"scale", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_scale, METH_O},
    {"setAbsTol", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setAbsTol, METH_VARARGS},
    {"setCheck", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setCheck, METH_VARARGS},
    {"setFormat", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setFormat, METH_VARARGS},
    {"setMaximum", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setMaximum, METH_VARARGS},
    {"setMinimum", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setMinimum, METH_VARARGS},
    {"setPkAvg", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setPkAvg, METH_VARARGS},
    {"setPrecision", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setPrecision, METH_VARARGS},
    {"setRange", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setRange, METH_VARARGS},
    {"setReadOnly", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setReadOnly, METH_VARARGS},
    {"setRelTol", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setRelTol, METH_VARARGS},
    {"setScale", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setScale, METH_VARARGS},
    {"setSingleStep", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setSingleStep, METH_VARARGS},
    {"setSize", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setSize, METH_VARARGS},
    {"setUnit", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setUnit, METH_VARARGS},
    {"setValue", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_setValue, METH_VARARGS},
    {"singleStep", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_singleStep, METH_O},
    {"size", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_size, METH_O},
    {"subComplexPropertyManager", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_subComplexPropertyManager, METH_NOARGS},
    {"uninitializeProperty", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_uninitializeProperty, METH_O},
    {"unit", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_unit, METH_O},
    {"unitText", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_unitText, METH_O},
    {"value", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_value, METH_O},
    {"valueText", (PyCFunction)Sbk_QtTFTensorPropertyManagerFunc_valueText, METH_O},

    {0} // Sentinel
};

} // extern "C"

static int Sbk_QtTFTensorPropertyManager_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_QtTFTensorPropertyManager_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_QtTFTensorPropertyManager_Type = nullptr;
static SbkObjectType *Sbk_QtTFTensorPropertyManager_TypeF(void)
{
    return _Sbk_QtTFTensorPropertyManager_Type;
}

static PyType_Slot Sbk_QtTFTensorPropertyManager_slots[] = {
    {Py_tp_base,        (void *)0}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     (void *)&SbkDeallocWrapper},
    {Py_tp_repr,        (void *)0},
    {Py_tp_hash,        (void *)0},
    {Py_tp_call,        (void *)0},
    {Py_tp_str,         (void *)0},
    {Py_tp_getattro,    (void *)0},
    {Py_tp_setattro,    (void *)0},
    {Py_tp_traverse,    (void *)Sbk_QtTFTensorPropertyManager_traverse},
    {Py_tp_clear,       (void *)Sbk_QtTFTensorPropertyManager_clear},
    {Py_tp_richcompare, (void *)0},
    {Py_tp_iter,        (void *)0},
    {Py_tp_iternext,    (void *)0},
    {Py_tp_methods,     (void *)Sbk_QtTFTensorPropertyManager_methods},
    {Py_tp_getset,      (void *)0},
    {Py_tp_init,        (void *)Sbk_QtTFTensorPropertyManager_Init},
    {Py_tp_new,         (void *)SbkObjectTpNew},
    {0, 0}
};
static PyType_Spec Sbk_QtTFTensorPropertyManager_spec = {
    "qtpropertybrowser.QtTFTensorPropertyManager",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_QtTFTensorPropertyManager_slots
};

} //extern "C"

static void* Sbk_QtTFTensorPropertyManager_typeDiscovery(void* cptr, SbkObjectType* instanceType)
{
    if (instanceType == reinterpret_cast<SbkObjectType*>(Shiboken::SbkType< ::QObject >()))
        return dynamic_cast< ::QtTFTensorPropertyManager*>(reinterpret_cast< ::QObject*>(cptr));
    return 0;
}


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void QtTFTensorPropertyManager_PythonToCpp_QtTFTensorPropertyManager_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_QtTFTensorPropertyManager_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_QtTFTensorPropertyManager_PythonToCpp_QtTFTensorPropertyManager_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)Sbk_QtTFTensorPropertyManager_TypeF()))
        return QtTFTensorPropertyManager_PythonToCpp_QtTFTensorPropertyManager_PTR;
    return 0;
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtTFTensorPropertyManager_PTR_CppToPython_QtTFTensorPropertyManager(const void* cppIn) {
    return PySide::getWrapperForQObject((::QtTFTensorPropertyManager*)cppIn, Sbk_QtTFTensorPropertyManager_TypeF());

}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
const char QtTFTensorPropertyManager_SignaturesString[] = ""
    "qtpropertybrowser.QtTFTensorPropertyManager(parent:PySide2.QtCore.QObject=nullptr)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.absTol(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.check(property:qtpropertybrowser.QtProperty)->bool\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.checkIcon(property:qtpropertybrowser.QtProperty)->PySide2.QtGui.QIcon\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.connect_signals()\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.disconnect_signals()\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.foreground(property:qtpropertybrowser.QtProperty)->PySide2.QtGui.QBrush\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.format(property:qtpropertybrowser.QtProperty)->qtpropertybrowser.Format\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.formatText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.initializeProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.isReadOnly(property:qtpropertybrowser.QtProperty)->bool\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.maximum(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.minimum(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.pkAvg(property:qtpropertybrowser.QtProperty)->qtpropertybrowser.PkAvg\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.pkAvgText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.precision(property:qtpropertybrowser.QtProperty)->int\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.reinitializeProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.relTol(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.scale(property:qtpropertybrowser.QtProperty)->qtpropertybrowser.Scale\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setAbsTol(property:qtpropertybrowser.QtProperty,absTol:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setCheck(property:qtpropertybrowser.QtProperty,check:bool)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setFormat(property:qtpropertybrowser.QtProperty,format_:qtpropertybrowser.Format)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setMaximum(property:qtpropertybrowser.QtProperty,maxVal:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setMinimum(property:qtpropertybrowser.QtProperty,minVal:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setPkAvg(property:qtpropertybrowser.QtProperty,pkAvg:qtpropertybrowser.PkAvg)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setPrecision(property:qtpropertybrowser.QtProperty,prec:int)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setRange(property:qtpropertybrowser.QtProperty,minVal:QVector,maxVal:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setReadOnly(property:qtpropertybrowser.QtProperty,readOnly:bool)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setRelTol(property:qtpropertybrowser.QtProperty,relTol:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setScale(property:qtpropertybrowser.QtProperty,scale_:qtpropertybrowser.Scale)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setSingleStep(property:qtpropertybrowser.QtProperty,step:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setSize(property:qtpropertybrowser.QtProperty,size:int)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setUnit(property:qtpropertybrowser.QtProperty,unit:QString)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.setValue(property:qtpropertybrowser.QtProperty,val:QVector)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.singleStep(property:qtpropertybrowser.QtProperty)->QComplex\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.size(property:qtpropertybrowser.QtProperty)->int\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.subComplexPropertyManager()->qtpropertybrowser.QtComplexPropertyManager\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.uninitializeProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.unit(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.unitText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.value(property:qtpropertybrowser.QtProperty)->QComplex\n"
    "qtpropertybrowser.QtTFTensorPropertyManager.valueText(property:qtpropertybrowser.QtProperty)->QString\n"
;

void init_QtTFTensorPropertyManager(PyObject* module)
{
    _Sbk_QtTFTensorPropertyManager_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtTFTensorPropertyManager",
        "QtTFTensorPropertyManager*",
        &Sbk_QtTFTensorPropertyManager_spec,
        QtTFTensorPropertyManager_SignaturesString,
        &Shiboken::callCppDestructor< ::QtTFTensorPropertyManager >,
        reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTABSTRACTPROPERTYMANAGER_IDX]),
        0,
        0    );
    
    SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX]
        = reinterpret_cast<PyTypeObject*>(Sbk_QtTFTensorPropertyManager_TypeF());

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(Sbk_QtTFTensorPropertyManager_TypeF(),
        QtTFTensorPropertyManager_PythonToCpp_QtTFTensorPropertyManager_PTR,
        is_QtTFTensorPropertyManager_PythonToCpp_QtTFTensorPropertyManager_PTR_Convertible,
        QtTFTensorPropertyManager_PTR_CppToPython_QtTFTensorPropertyManager);

    Shiboken::Conversions::registerConverterName(converter, "QtTFTensorPropertyManager");
    Shiboken::Conversions::registerConverterName(converter, "QtTFTensorPropertyManager*");
    Shiboken::Conversions::registerConverterName(converter, "QtTFTensorPropertyManager&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtTFTensorPropertyManager).name());
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtTFTensorPropertyManagerWrapper).name());


    Shiboken::ObjectType::setTypeDiscoveryFunctionV2(Sbk_QtTFTensorPropertyManager_TypeF(), &Sbk_QtTFTensorPropertyManager_typeDiscovery);

    PySide::Signal::registerSignals(Sbk_QtTFTensorPropertyManager_TypeF(), &::QtTFTensorPropertyManager::staticMetaObject);

    QtTFTensorPropertyManagerWrapper::pysideInitQtMetaTypes();
    Shiboken::ObjectType::setSubTypeInitHook(Sbk_QtTFTensorPropertyManager_TypeF(), &PySide::initQObjectSubType);
    PySide::initDynamicMetaObject(Sbk_QtTFTensorPropertyManager_TypeF(), &::QtTFTensorPropertyManager::staticMetaObject, sizeof(::QtTFTensorPropertyManager));
}
