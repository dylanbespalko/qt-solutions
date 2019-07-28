
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
#include "qtdoublepropertymanager_wrapper.h"

// inner classes

// Extra includes
#include <QList>
#include <QSet>
#include <qbrush.h>
#include <qbytearray.h>
#include <qicon.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qtpropertybrowser.h>


// Native ---------------------------------------------------------

void QtDoublePropertyManagerWrapper::pysideInitQtMetaTypes()
{
}

QtDoublePropertyManagerWrapper::QtDoublePropertyManagerWrapper(QObject * parent) : QtDoublePropertyManager(parent) {
    // ... middle
}

bool QtDoublePropertyManagerWrapper::check(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "check"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::check(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.check", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QIcon QtDoublePropertyManagerWrapper::checkIcon(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return {};
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "checkIcon"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::checkIcon(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.checkIcon", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QIcon >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return {};
    }
    ::QIcon cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtDoublePropertyManagerWrapper::childEvent(QChildEvent * event)
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

void QtDoublePropertyManagerWrapper::connectNotify(const QMetaMethod & signal)
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

QtProperty * QtDoublePropertyManagerWrapper::createProperty()
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.createProperty", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QtProperty >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return nullptr;
    }
    ::QtProperty* cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtDoublePropertyManagerWrapper::customEvent(QEvent * event)
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

void QtDoublePropertyManagerWrapper::disconnectNotify(const QMetaMethod & signal)
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

QString QtDoublePropertyManagerWrapper::displayText(const QtProperty * property) const
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.displayText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QLineEdit::EchoMode QtDoublePropertyManagerWrapper::echoMode(const QtProperty * arg__1) const
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.echoMode", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QLineEdit::EchoMode >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return QLineEdit::Normal;
    }
    ::QLineEdit::EchoMode cppResult{QLineEdit::Normal};
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

bool QtDoublePropertyManagerWrapper::event(QEvent * event)
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.event", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    if (invalidateArg1)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 0));
    return cppResult;
}

bool QtDoublePropertyManagerWrapper::eventFilter(QObject * watched, QEvent * event)
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.eventFilter", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    if (invalidateArg2)
        Shiboken::Object::invalidate(PyTuple_GET_ITEM(pyArgs, 1));
    return cppResult;
}

QBrush QtDoublePropertyManagerWrapper::foreground(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return {};
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "foreground"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::foreground(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.foreground", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QBrush >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return {};
    }
    ::QBrush cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtDoublePropertyManagerWrapper::formatText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "formatText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::formatText(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.formatText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

bool QtDoublePropertyManagerWrapper::hasValue(const QtProperty * property) const
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.hasValue", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtDoublePropertyManagerWrapper::initializeProperty(QtProperty * property)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "initializeProperty"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtDoublePropertyManager::initializeProperty(property);
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

bool QtDoublePropertyManagerWrapper::isReadOnly(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return false;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "isReadOnly"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::isReadOnly(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.isReadOnly", "bool", Py_TYPE(pyResult)->tp_name);
        return false;
    }
    bool cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtDoublePropertyManagerWrapper::maximumText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "maximumText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::maximumText(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.maximumText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtDoublePropertyManagerWrapper::minimumText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "minimumText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::minimumText(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.minimumText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtDoublePropertyManagerWrapper::pkAvgText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "pkAvgText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtAbstractPropertyManager::pkAvgText(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.pkAvgText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtDoublePropertyManagerWrapper::timerEvent(QTimerEvent * event)
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

void QtDoublePropertyManagerWrapper::uninitializeProperty(QtProperty * property)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "uninitializeProperty"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtDoublePropertyManager::uninitializeProperty(property);
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

QString QtDoublePropertyManagerWrapper::unitText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "unitText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::unitText(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.unitText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QIcon QtDoublePropertyManagerWrapper::valueIcon(const QtProperty * property) const
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.valueIcon", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QIcon >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return {};
    }
    ::QIcon cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QString QtDoublePropertyManagerWrapper::valueText(const QtProperty * property) const
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return ::QString();
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "valueText"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtDoublePropertyManager::valueText(property);
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
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtDoublePropertyManager.valueText", "QString", Py_TYPE(pyResult)->tp_name);
        return ::QString();
    }
    ::QString cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

const QMetaObject* QtDoublePropertyManagerWrapper::metaObject() const
{
    if (QObject::d_ptr->metaObject)
        return QObject::d_ptr->dynamicMetaObject();
    SbkObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(this);
    if (pySelf == NULL)
        return QtDoublePropertyManager::metaObject();
    return PySide::SignalManager::retrieveMetaObject(reinterpret_cast<PyObject*>(pySelf));
}

int QtDoublePropertyManagerWrapper::qt_metacall(QMetaObject::Call call, int id, void** args)
{
    int result = QtDoublePropertyManager::qt_metacall(call, id, args);
    return result < 0 ? result : PySide::SignalManager::qt_metacall(this, call, id, args);
}

void* QtDoublePropertyManagerWrapper::qt_metacast(const char* _clname)
{
        if (!_clname) return 0;
        SbkObject* pySelf = Shiboken::BindingManager::instance().retrieveWrapper(this);
        if (pySelf && PySide::inherits(Py_TYPE(pySelf), _clname))
                return static_cast<void*>(const_cast< QtDoublePropertyManagerWrapper* >(this));
        return QtDoublePropertyManager::qt_metacast(_clname);
}

QtDoublePropertyManagerWrapper::~QtDoublePropertyManagerWrapper()
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(this);
    Shiboken::Object::destroy(wrapper, this);
}

// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_QtDoublePropertyManager_Init(PyObject* self, PyObject* args, PyObject* kwds)
{
    const char* argNames[] = {"parent"};
    const QMetaObject* metaObject;
    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::QtDoublePropertyManager >()))
        return -1;

    ::QtDoublePropertyManagerWrapper* cptr = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_ParseTuple(args, "|O:QtDoublePropertyManager", &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: QtDoublePropertyManager(QObject*)
    if (numArgs == 0) {
        overloadId = 0; // QtDoublePropertyManager(QObject*)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0])))) {
        overloadId = 0; // QtDoublePropertyManager(QObject*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManager_Init_TypeError;

    // Call function/method
    {
        if (kwds) {
            PyObject* value = PyDict_GetItemString(kwds, "parent");
            if (value && pyArgs[0]) {
                PyErr_SetString(PyExc_TypeError, "qtpropertybrowser.QtDoublePropertyManager(): got multiple values for keyword argument 'parent'.");
                return -1;
            } else if (value) {
                pyArgs[0] = value;
                if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0]))))
                    goto Sbk_QtDoublePropertyManager_Init_TypeError;
            }
        }
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return -1;
        ::QObject* cppArg0 = nullptr;
        if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

        if (!PyErr_Occurred()) {
            // QtDoublePropertyManager(QObject*)
            void* addr = PySide::nextQObjectMemoryAddr();
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            if (addr) {
                cptr = new (addr) ::QtDoublePropertyManagerWrapper(cppArg0);
                PySide::setNextQObjectMemoryAddr(0);
            } else {
                cptr = new ::QtDoublePropertyManagerWrapper(cppArg0);
            }

            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            Shiboken::Object::setParent(pyArgs[0], self);
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::QtDoublePropertyManager >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_QtDoublePropertyManager_Init_TypeError;

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

    Sbk_QtDoublePropertyManager_Init_TypeError:
        const char* overloads[] = {"PySide2.QtCore.QObject = nullptr", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager", overloads);
        return -1;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_absTol(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_absTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // absTol(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            double cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->absTol(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_absTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.absTol", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_check(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_check_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // check(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = Shiboken::Object::hasCppWrapper(reinterpret_cast<SbkObject*>(self)) ? const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->::QtDoublePropertyManager::check(cppArg0) : const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->check(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_check_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.check", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_checkIcon(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_checkIcon_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // checkIcon(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QIcon cppResult = ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::checkIcon_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QICON_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_checkIcon_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.checkIcon", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_foreground(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_foreground_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // foreground(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QBrush cppResult = Shiboken::Object::hasCppWrapper(reinterpret_cast<SbkObject*>(self)) ? const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->::QtDoublePropertyManager::foreground(cppArg0) : const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->foreground(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QBRUSH_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_foreground_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.foreground", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_format(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_format_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // format(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            Format cppResult = Format(const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->format(cppArg0));
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_FORMAT_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_format_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.format", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_formatText(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_formatText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // formatText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::formatText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_formatText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.formatText", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_initializeProperty(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: initializeProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // initializeProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_initializeProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // initializeProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::initializeProperty_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_initializeProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.initializeProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_isReadOnly(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_isReadOnly_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // isReadOnly(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            bool cppResult = Shiboken::Object::hasCppWrapper(reinterpret_cast<SbkObject*>(self)) ? const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->::QtDoublePropertyManager::isReadOnly(cppArg0) : const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->isReadOnly(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_isReadOnly_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.isReadOnly", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_maximum(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_maximum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // maximum(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            double cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->maximum(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_maximum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.maximum", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_maximumText(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: maximumText(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // maximumText(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_maximumText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // maximumText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::maximumText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_maximumText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.maximumText", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_minimum(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_minimum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // minimum(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            double cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->minimum(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_minimum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.minimum", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_minimumText(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: minimumText(const QtProperty*)const
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // minimumText(const QtProperty*)const
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_minimumText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // minimumText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::minimumText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_minimumText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.minimumText", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_precision(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_precision_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // precision(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            int cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->precision(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_precision_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.precision", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_relTol(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_relTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // relTol(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            double cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->relTol(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_relTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.relTol", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_scale(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_scale_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // scale(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            Scale cppResult = Scale(const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->scale(cppArg0));
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_SCALE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_scale_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.scale", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setAbsTol(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setAbsTol", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setAbsTol(QtProperty*,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 0; // setAbsTol(QtProperty*,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setAbsTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setAbsTol(QtProperty*,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setAbsTol(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setAbsTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setAbsTol", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setCheck(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setCheck_TypeError;

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

    Sbk_QtDoublePropertyManagerFunc_setCheck_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, bool", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setCheck", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setFormat(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setFormat_TypeError;

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

    Sbk_QtDoublePropertyManagerFunc_setFormat_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, qtpropertybrowser.Format", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setFormat", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setMaximum(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setMaximum", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setMaximum(QtProperty*,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 0; // setMaximum(QtProperty*,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setMaximum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setMaximum(QtProperty*,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setMaximum(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setMaximum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setMaximum", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setMinimum(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setMinimum", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setMinimum(QtProperty*,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 0; // setMinimum(QtProperty*,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setMinimum_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setMinimum(QtProperty*,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setMinimum(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setMinimum_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setMinimum", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setPrecision(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setPrecision_TypeError;

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

    Sbk_QtDoublePropertyManagerFunc_setPrecision_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, int", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setPrecision", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setRange(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setRange", 3, 3, &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2])))
        return 0;


    // Overloaded function decisor
    // 0: setRange(QtProperty*,double,double)
    if (numArgs == 3
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))
        && (pythonToCpp[2] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[2])))) {
        overloadId = 0; // setRange(QtProperty*,double,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setRange_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);
        double cppArg2;
        pythonToCpp[2](pyArgs[2], &cppArg2);

        if (!PyErr_Occurred()) {
            // setRange(QtProperty*,double,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setRange(cppArg0, cppArg1, cppArg2);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setRange_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setRange", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setReadOnly(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setReadOnly_TypeError;

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

    Sbk_QtDoublePropertyManagerFunc_setReadOnly_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, bool", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setReadOnly", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setRelTol(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setRelTol", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setRelTol(QtProperty*,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 0; // setRelTol(QtProperty*,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setRelTol_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setRelTol(QtProperty*,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setRelTol(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setRelTol_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setRelTol", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setScale(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setScale_TypeError;

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

    Sbk_QtDoublePropertyManagerFunc_setScale_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, qtpropertybrowser.Scale", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setScale", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setSingleStep(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setSingleStep", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setSingleStep(QtProperty*,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 0; // setSingleStep(QtProperty*,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setSingleStep_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setSingleStep(QtProperty*,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setSingleStep(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setSingleStep_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setSingleStep", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setUnit(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setUnit_TypeError;

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

    Sbk_QtDoublePropertyManagerFunc_setUnit_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, unicode", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setUnit", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_setValue(PyObject* self, PyObject* args)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "setValue", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: setValue(QtProperty*,double)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<double>(), (pyArgs[1])))) {
        overloadId = 0; // setValue(QtProperty*,double)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_setValue_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        double cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // setValue(QtProperty*,double)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setValue(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_setValue_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, float", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtDoublePropertyManager.setValue", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_singleStep(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_singleStep_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // singleStep(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            double cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->singleStep(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_singleStep_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.singleStep", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_uninitializeProperty(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: uninitializeProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // uninitializeProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_uninitializeProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // uninitializeProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::uninitializeProperty_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtDoublePropertyManagerFunc_uninitializeProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.uninitializeProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_unit(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_unit_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // unit(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->unit(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_unit_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.unit", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_unitText(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_unitText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // unitText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::unitText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_unitText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.unitText", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_value(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_value_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // value(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            double cppResult = const_cast<const ::QtDoublePropertyManagerWrapper*>(cppSelf)->value(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<double>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_value_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.value", overloads);
        return 0;
}

static PyObject* Sbk_QtDoublePropertyManagerFunc_valueText(PyObject* self, PyObject* pyArg)
{
    QtDoublePropertyManagerWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtDoublePropertyManagerWrapper*)reinterpret_cast< ::QtDoublePropertyManager *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX], reinterpret_cast<SbkObject *>(self)));
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
    if (overloadId == -1) goto Sbk_QtDoublePropertyManagerFunc_valueText_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // valueText(const QtProperty*)const
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QString cppResult = ((::QtDoublePropertyManagerWrapper*) cppSelf)->QtDoublePropertyManagerWrapper::valueText_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtDoublePropertyManagerFunc_valueText_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtDoublePropertyManager.valueText", overloads);
        return 0;
}

static PyMethodDef Sbk_QtDoublePropertyManager_methods[] = {
    {"absTol", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_absTol, METH_O},
    {"check", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_check, METH_O},
    {"checkIcon", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_checkIcon, METH_O},
    {"foreground", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_foreground, METH_O},
    {"format", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_format, METH_O},
    {"formatText", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_formatText, METH_O},
    {"initializeProperty", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_initializeProperty, METH_O},
    {"isReadOnly", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_isReadOnly, METH_O},
    {"maximum", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_maximum, METH_O},
    {"maximumText", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_maximumText, METH_O},
    {"minimum", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_minimum, METH_O},
    {"minimumText", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_minimumText, METH_O},
    {"precision", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_precision, METH_O},
    {"relTol", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_relTol, METH_O},
    {"scale", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_scale, METH_O},
    {"setAbsTol", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setAbsTol, METH_VARARGS},
    {"setCheck", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setCheck, METH_VARARGS},
    {"setFormat", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setFormat, METH_VARARGS},
    {"setMaximum", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setMaximum, METH_VARARGS},
    {"setMinimum", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setMinimum, METH_VARARGS},
    {"setPrecision", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setPrecision, METH_VARARGS},
    {"setRange", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setRange, METH_VARARGS},
    {"setReadOnly", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setReadOnly, METH_VARARGS},
    {"setRelTol", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setRelTol, METH_VARARGS},
    {"setScale", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setScale, METH_VARARGS},
    {"setSingleStep", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setSingleStep, METH_VARARGS},
    {"setUnit", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setUnit, METH_VARARGS},
    {"setValue", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_setValue, METH_VARARGS},
    {"singleStep", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_singleStep, METH_O},
    {"uninitializeProperty", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_uninitializeProperty, METH_O},
    {"unit", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_unit, METH_O},
    {"unitText", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_unitText, METH_O},
    {"value", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_value, METH_O},
    {"valueText", (PyCFunction)Sbk_QtDoublePropertyManagerFunc_valueText, METH_O},

    {0} // Sentinel
};

} // extern "C"

static int Sbk_QtDoublePropertyManager_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_QtDoublePropertyManager_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_QtDoublePropertyManager_Type = nullptr;
static SbkObjectType *Sbk_QtDoublePropertyManager_TypeF(void)
{
    return _Sbk_QtDoublePropertyManager_Type;
}

static PyType_Slot Sbk_QtDoublePropertyManager_slots[] = {
    {Py_tp_base,        (void *)0}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     (void *)&SbkDeallocWrapper},
    {Py_tp_repr,        (void *)0},
    {Py_tp_hash,        (void *)0},
    {Py_tp_call,        (void *)0},
    {Py_tp_str,         (void *)0},
    {Py_tp_getattro,    (void *)0},
    {Py_tp_setattro,    (void *)0},
    {Py_tp_traverse,    (void *)Sbk_QtDoublePropertyManager_traverse},
    {Py_tp_clear,       (void *)Sbk_QtDoublePropertyManager_clear},
    {Py_tp_richcompare, (void *)0},
    {Py_tp_iter,        (void *)0},
    {Py_tp_iternext,    (void *)0},
    {Py_tp_methods,     (void *)Sbk_QtDoublePropertyManager_methods},
    {Py_tp_getset,      (void *)0},
    {Py_tp_init,        (void *)Sbk_QtDoublePropertyManager_Init},
    {Py_tp_new,         (void *)SbkObjectTpNew},
    {0, 0}
};
static PyType_Spec Sbk_QtDoublePropertyManager_spec = {
    "qtpropertybrowser.QtDoublePropertyManager",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_QtDoublePropertyManager_slots
};

} //extern "C"

static void* Sbk_QtDoublePropertyManager_typeDiscovery(void* cptr, SbkObjectType* instanceType)
{
    if (instanceType == reinterpret_cast<SbkObjectType*>(Shiboken::SbkType< ::QObject >()))
        return dynamic_cast< ::QtDoublePropertyManager*>(reinterpret_cast< ::QObject*>(cptr));
    return 0;
}


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void QtDoublePropertyManager_PythonToCpp_QtDoublePropertyManager_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_QtDoublePropertyManager_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_QtDoublePropertyManager_PythonToCpp_QtDoublePropertyManager_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)Sbk_QtDoublePropertyManager_TypeF()))
        return QtDoublePropertyManager_PythonToCpp_QtDoublePropertyManager_PTR;
    return 0;
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtDoublePropertyManager_PTR_CppToPython_QtDoublePropertyManager(const void* cppIn) {
    return PySide::getWrapperForQObject((::QtDoublePropertyManager*)cppIn, Sbk_QtDoublePropertyManager_TypeF());

}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
const char QtDoublePropertyManager_SignaturesString[] = ""
    "qtpropertybrowser.QtDoublePropertyManager(parent:PySide2.QtCore.QObject=nullptr)\n"
    "qtpropertybrowser.QtDoublePropertyManager.absTol(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtDoublePropertyManager.check(property:qtpropertybrowser.QtProperty)->bool\n"
    "qtpropertybrowser.QtDoublePropertyManager.checkIcon(property:qtpropertybrowser.QtProperty)->PySide2.QtGui.QIcon\n"
    "qtpropertybrowser.QtDoublePropertyManager.foreground(property:qtpropertybrowser.QtProperty)->PySide2.QtGui.QBrush\n"
    "qtpropertybrowser.QtDoublePropertyManager.format(property:qtpropertybrowser.QtProperty)->qtpropertybrowser.Format\n"
    "qtpropertybrowser.QtDoublePropertyManager.formatText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtDoublePropertyManager.initializeProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtDoublePropertyManager.isReadOnly(property:qtpropertybrowser.QtProperty)->bool\n"
    "qtpropertybrowser.QtDoublePropertyManager.maximum(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtDoublePropertyManager.maximumText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtDoublePropertyManager.minimum(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtDoublePropertyManager.minimumText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtDoublePropertyManager.precision(property:qtpropertybrowser.QtProperty)->int\n"
    "qtpropertybrowser.QtDoublePropertyManager.relTol(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtDoublePropertyManager.scale(property:qtpropertybrowser.QtProperty)->qtpropertybrowser.Scale\n"
    "qtpropertybrowser.QtDoublePropertyManager.setAbsTol(property:qtpropertybrowser.QtProperty,absTol:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setCheck(property:qtpropertybrowser.QtProperty,check:bool)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setFormat(property:qtpropertybrowser.QtProperty,format_:qtpropertybrowser.Format)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setMaximum(property:qtpropertybrowser.QtProperty,maxVal:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setMinimum(property:qtpropertybrowser.QtProperty,minVal:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setPrecision(property:qtpropertybrowser.QtProperty,prec:int)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setRange(property:qtpropertybrowser.QtProperty,minVal:double,maxVal:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setReadOnly(property:qtpropertybrowser.QtProperty,readOnly:bool)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setRelTol(property:qtpropertybrowser.QtProperty,relTol:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setScale(property:qtpropertybrowser.QtProperty,scale_:qtpropertybrowser.Scale)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setSingleStep(property:qtpropertybrowser.QtProperty,step:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setUnit(property:qtpropertybrowser.QtProperty,unit:QString)\n"
    "qtpropertybrowser.QtDoublePropertyManager.setValue(property:qtpropertybrowser.QtProperty,val:double)\n"
    "qtpropertybrowser.QtDoublePropertyManager.singleStep(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtDoublePropertyManager.uninitializeProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtDoublePropertyManager.unit(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtDoublePropertyManager.unitText(property:qtpropertybrowser.QtProperty)->QString\n"
    "qtpropertybrowser.QtDoublePropertyManager.value(property:qtpropertybrowser.QtProperty)->double\n"
    "qtpropertybrowser.QtDoublePropertyManager.valueText(property:qtpropertybrowser.QtProperty)->QString\n"
;

void init_QtDoublePropertyManager(PyObject* module)
{
    _Sbk_QtDoublePropertyManager_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtDoublePropertyManager",
        "QtDoublePropertyManager*",
        &Sbk_QtDoublePropertyManager_spec,
        QtDoublePropertyManager_SignaturesString,
        &Shiboken::callCppDestructor< ::QtDoublePropertyManager >,
        reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTABSTRACTPROPERTYMANAGER_IDX]),
        0,
        0    );
    
    SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX]
        = reinterpret_cast<PyTypeObject*>(Sbk_QtDoublePropertyManager_TypeF());

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(Sbk_QtDoublePropertyManager_TypeF(),
        QtDoublePropertyManager_PythonToCpp_QtDoublePropertyManager_PTR,
        is_QtDoublePropertyManager_PythonToCpp_QtDoublePropertyManager_PTR_Convertible,
        QtDoublePropertyManager_PTR_CppToPython_QtDoublePropertyManager);

    Shiboken::Conversions::registerConverterName(converter, "QtDoublePropertyManager");
    Shiboken::Conversions::registerConverterName(converter, "QtDoublePropertyManager*");
    Shiboken::Conversions::registerConverterName(converter, "QtDoublePropertyManager&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtDoublePropertyManager).name());
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtDoublePropertyManagerWrapper).name());


    Shiboken::ObjectType::setTypeDiscoveryFunctionV2(Sbk_QtDoublePropertyManager_TypeF(), &Sbk_QtDoublePropertyManager_typeDiscovery);

    PySide::Signal::registerSignals(Sbk_QtDoublePropertyManager_TypeF(), &::QtDoublePropertyManager::staticMetaObject);

    QtDoublePropertyManagerWrapper::pysideInitQtMetaTypes();
    Shiboken::ObjectType::setSubTypeInitHook(Sbk_QtDoublePropertyManager_TypeF(), &PySide::initQObjectSubType);
    PySide::initDynamicMetaObject(Sbk_QtDoublePropertyManager_TypeF(), &::QtDoublePropertyManager::staticMetaObject, sizeof(::QtDoublePropertyManager));
}
