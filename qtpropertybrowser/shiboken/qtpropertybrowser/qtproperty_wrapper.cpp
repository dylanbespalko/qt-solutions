
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

// module include
#include "qtpropertybrowser_python.h"

// main header
#include "qtproperty_wrapper.h"

// inner classes

// Extra includes
#include <QList>
#include <qbrush.h>
#include <qicon.h>
#include <qtpropertybrowser.h>


// Native ---------------------------------------------------------

void QtPropertyWrapper::pysideInitQtMetaTypes()
{
}

QtPropertyWrapper::QtPropertyWrapper(QtAbstractPropertyManager * manager) : QtProperty(manager) {
    // ... middle
}

QtPropertyWrapper::~QtPropertyWrapper()
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(this);
    Shiboken::Object::destroy(wrapper, this);
}

// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_QtProperty_Init(PyObject* self, PyObject* args, PyObject* kwds)
{
    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::QtProperty >()))
        return -1;

    ::QtPropertyWrapper* cptr = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "QtProperty", 1, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: QtProperty(QtAbstractPropertyManager*)
    if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTABSTRACTPROPERTYMANAGER_IDX]), (pyArgs[0])))) {
        overloadId = 0; // QtProperty(QtAbstractPropertyManager*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtProperty_Init_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return -1;
        ::QtAbstractPropertyManager* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);

        if (!PyErr_Occurred()) {
            // QtProperty(QtAbstractPropertyManager*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cptr = new ::QtPropertyWrapper(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::QtProperty >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_QtProperty_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    Shiboken::Object::setHasCppWrapper(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_QtProperty_Init_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtAbstractPropertyManager", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtProperty", overloads);
        return -1;
}

static PyObject* Sbk_QtPropertyFunc_addSubProperty(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: addSubProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // addSubProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_addSubProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // addSubProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->addSubProperty(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_addSubProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.addSubProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_check(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // check()const
            bool cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->check();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_checkIcon(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // checkIcon()const
            QIcon cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->checkIcon();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QICON_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_displayText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // displayText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->displayText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_foreground(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // foreground()const
            QBrush cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->foreground();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QBRUSH_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_formatText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // formatText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->formatText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_hasValue(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // hasValue()const
            bool cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->hasValue();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_insertSubProperty(PyObject* self, PyObject* args)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "insertSubProperty", 2, 2, &(pyArgs[0]), &(pyArgs[1])))
        return 0;


    // Overloaded function decisor
    // 0: insertSubProperty(QtProperty*,QtProperty*)
    if (numArgs == 2
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[1])))) {
        overloadId = 0; // insertSubProperty(QtProperty*,QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_insertSubProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        if (!Shiboken::Object::isValid(pyArgs[1]))
            return 0;
        ::QtProperty* cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);

        if (!PyErr_Occurred()) {
            // insertSubProperty(QtProperty*,QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->insertSubProperty(cppArg0, cppArg1);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_insertSubProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty, qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtProperty.insertSubProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_isEnabled(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // isEnabled()const
            bool cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->isEnabled();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_isModified(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // isModified()const
            bool cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->isModified();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_label(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // label()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->label();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_maximumText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // maximumText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->maximumText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_minimumText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // minimumText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->minimumText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_pkAvgText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // pkAvgText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->pkAvgText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_propertyChanged(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // propertyChanged()
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtPropertyWrapper*) cppSelf)->QtPropertyWrapper::propertyChanged_protected();
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;
}

static PyObject* Sbk_QtPropertyFunc_propertyManager(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // propertyManager()const
            QtAbstractPropertyManager * cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->propertyManager();
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTABSTRACTPROPERTYMANAGER_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_propertyName(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // propertyName()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->propertyName();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_removeSubProperty(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: removeSubProperty(QtProperty*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArg)))) {
        overloadId = 0; // removeSubProperty(QtProperty*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_removeSubProperty_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtProperty* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // removeSubProperty(QtProperty*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->removeSubProperty(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_removeSubProperty_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtProperty", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.removeSubProperty", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setEnabled(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setEnabled(bool)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArg)))) {
        overloadId = 0; // setEnabled(bool)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setEnabled_TypeError;

    // Call function/method
    {
        bool cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setEnabled(bool)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setEnabled(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setEnabled_TypeError:
        const char* overloads[] = {"bool", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setEnabled", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setLabel(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setLabel(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setLabel(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setLabel_TypeError;

    // Call function/method
    {
        ::QString cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setLabel(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setLabel(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setLabel_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setLabel", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setModified(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setModified(bool)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), (pyArg)))) {
        overloadId = 0; // setModified(bool)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setModified_TypeError;

    // Call function/method
    {
        bool cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setModified(bool)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setModified(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setModified_TypeError:
        const char* overloads[] = {"bool", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setModified", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setPropertyName(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setPropertyName(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setPropertyName(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setPropertyName_TypeError;

    // Call function/method
    {
        ::QString cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setPropertyName(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setPropertyName(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setPropertyName_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setPropertyName", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setStatusTip(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setStatusTip(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setStatusTip(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setStatusTip_TypeError;

    // Call function/method
    {
        ::QString cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setStatusTip(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setStatusTip(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setStatusTip_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setStatusTip", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setToolTip(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setToolTip(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setToolTip(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setToolTip_TypeError;

    // Call function/method
    {
        ::QString cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setToolTip(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setToolTip(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setToolTip_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setToolTip", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_setWhatsThis(PyObject* self, PyObject* pyArg)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: setWhatsThis(QString)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], (pyArg)))) {
        overloadId = 0; // setWhatsThis(QString)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtPropertyFunc_setWhatsThis_TypeError;

    // Call function/method
    {
        ::QString cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setWhatsThis(QString)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cppSelf->setWhatsThis(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtPropertyFunc_setWhatsThis_TypeError:
        const char* overloads[] = {"unicode", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtProperty.setWhatsThis", overloads);
        return 0;
}

static PyObject* Sbk_QtPropertyFunc_statusTip(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // statusTip()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->statusTip();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_subProperties(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // subProperties()const
            QList<QtProperty* > cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->subProperties();
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QLIST_QTPROPERTYPTR_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_toolTip(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // toolTip()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->toolTip();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_unitText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // unitText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->unitText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_valueIcon(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // valueIcon()const
            QIcon cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->valueIcon();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtGuiTypes[SBK_QICON_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_valueText(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // valueText()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->valueText();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtPropertyFunc_whatsThis(PyObject* self)
{
    QtPropertyWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtPropertyWrapper*)reinterpret_cast< ::QtProperty *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // whatsThis()const
            QString cppResult = const_cast<const ::QtPropertyWrapper*>(cppSelf)->whatsThis();
            pyResult = Shiboken::Conversions::copyToPython(SbkPySide2_QtCoreTypeConverters[SBK_QSTRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;
}

static PyMethodDef Sbk_QtProperty_methods[] = {
    {"addSubProperty", (PyCFunction)Sbk_QtPropertyFunc_addSubProperty, METH_O},
    {"check", (PyCFunction)Sbk_QtPropertyFunc_check, METH_NOARGS},
    {"checkIcon", (PyCFunction)Sbk_QtPropertyFunc_checkIcon, METH_NOARGS},
    {"displayText", (PyCFunction)Sbk_QtPropertyFunc_displayText, METH_NOARGS},
    {"foreground", (PyCFunction)Sbk_QtPropertyFunc_foreground, METH_NOARGS},
    {"formatText", (PyCFunction)Sbk_QtPropertyFunc_formatText, METH_NOARGS},
    {"hasValue", (PyCFunction)Sbk_QtPropertyFunc_hasValue, METH_NOARGS},
    {"insertSubProperty", (PyCFunction)Sbk_QtPropertyFunc_insertSubProperty, METH_VARARGS},
    {"isEnabled", (PyCFunction)Sbk_QtPropertyFunc_isEnabled, METH_NOARGS},
    {"isModified", (PyCFunction)Sbk_QtPropertyFunc_isModified, METH_NOARGS},
    {"label", (PyCFunction)Sbk_QtPropertyFunc_label, METH_NOARGS},
    {"maximumText", (PyCFunction)Sbk_QtPropertyFunc_maximumText, METH_NOARGS},
    {"minimumText", (PyCFunction)Sbk_QtPropertyFunc_minimumText, METH_NOARGS},
    {"pkAvgText", (PyCFunction)Sbk_QtPropertyFunc_pkAvgText, METH_NOARGS},
    {"propertyChanged", (PyCFunction)Sbk_QtPropertyFunc_propertyChanged, METH_NOARGS},
    {"propertyManager", (PyCFunction)Sbk_QtPropertyFunc_propertyManager, METH_NOARGS},
    {"propertyName", (PyCFunction)Sbk_QtPropertyFunc_propertyName, METH_NOARGS},
    {"removeSubProperty", (PyCFunction)Sbk_QtPropertyFunc_removeSubProperty, METH_O},
    {"setEnabled", (PyCFunction)Sbk_QtPropertyFunc_setEnabled, METH_O},
    {"setLabel", (PyCFunction)Sbk_QtPropertyFunc_setLabel, METH_O},
    {"setModified", (PyCFunction)Sbk_QtPropertyFunc_setModified, METH_O},
    {"setPropertyName", (PyCFunction)Sbk_QtPropertyFunc_setPropertyName, METH_O},
    {"setStatusTip", (PyCFunction)Sbk_QtPropertyFunc_setStatusTip, METH_O},
    {"setToolTip", (PyCFunction)Sbk_QtPropertyFunc_setToolTip, METH_O},
    {"setWhatsThis", (PyCFunction)Sbk_QtPropertyFunc_setWhatsThis, METH_O},
    {"statusTip", (PyCFunction)Sbk_QtPropertyFunc_statusTip, METH_NOARGS},
    {"subProperties", (PyCFunction)Sbk_QtPropertyFunc_subProperties, METH_NOARGS},
    {"toolTip", (PyCFunction)Sbk_QtPropertyFunc_toolTip, METH_NOARGS},
    {"unitText", (PyCFunction)Sbk_QtPropertyFunc_unitText, METH_NOARGS},
    {"valueIcon", (PyCFunction)Sbk_QtPropertyFunc_valueIcon, METH_NOARGS},
    {"valueText", (PyCFunction)Sbk_QtPropertyFunc_valueText, METH_NOARGS},
    {"whatsThis", (PyCFunction)Sbk_QtPropertyFunc_whatsThis, METH_NOARGS},

    {0} // Sentinel
};

} // extern "C"

static int Sbk_QtProperty_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_QtProperty_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_QtProperty_Type = nullptr;
static SbkObjectType *Sbk_QtProperty_TypeF(void)
{
    return _Sbk_QtProperty_Type;
}

static PyType_Slot Sbk_QtProperty_slots[] = {
    {Py_tp_base,        (void *)0}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     (void *)&SbkDeallocWrapper},
    {Py_tp_repr,        (void *)0},
    {Py_tp_hash,        (void *)0},
    {Py_tp_call,        (void *)0},
    {Py_tp_str,         (void *)0},
    {Py_tp_getattro,    (void *)0},
    {Py_tp_setattro,    (void *)0},
    {Py_tp_traverse,    (void *)Sbk_QtProperty_traverse},
    {Py_tp_clear,       (void *)Sbk_QtProperty_clear},
    {Py_tp_richcompare, (void *)0},
    {Py_tp_iter,        (void *)0},
    {Py_tp_iternext,    (void *)0},
    {Py_tp_methods,     (void *)Sbk_QtProperty_methods},
    {Py_tp_getset,      (void *)0},
    {Py_tp_init,        (void *)Sbk_QtProperty_Init},
    {Py_tp_new,         (void *)SbkObjectTpNew},
    {0, 0}
};
static PyType_Spec Sbk_QtProperty_spec = {
    "qtpropertybrowser.QtProperty",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_QtProperty_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void QtProperty_PythonToCpp_QtProperty_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_QtProperty_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_QtProperty_PythonToCpp_QtProperty_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)Sbk_QtProperty_TypeF()))
        return QtProperty_PythonToCpp_QtProperty_PTR;
    return 0;
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtProperty_PTR_CppToPython_QtProperty(const void* cppIn) {
    PyObject* pyOut = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(cppIn);
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    const char* typeName = typeid(*((::QtProperty*)cppIn)).name();
    return Shiboken::Object::newObject(Sbk_QtProperty_TypeF(), const_cast<void*>(cppIn), false, false, typeName);
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
const char QtProperty_SignaturesString[] = ""
    "qtpropertybrowser.QtProperty(manager:qtpropertybrowser.QtAbstractPropertyManager)\n"
    "qtpropertybrowser.QtProperty.addSubProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtProperty.check()->bool\n"
    "qtpropertybrowser.QtProperty.checkIcon()->PySide2.QtGui.QIcon\n"
    "qtpropertybrowser.QtProperty.displayText()->QString\n"
    "qtpropertybrowser.QtProperty.foreground()->PySide2.QtGui.QBrush\n"
    "qtpropertybrowser.QtProperty.formatText()->QString\n"
    "qtpropertybrowser.QtProperty.hasValue()->bool\n"
    "qtpropertybrowser.QtProperty.insertSubProperty(property:qtpropertybrowser.QtProperty,afterProperty:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtProperty.isEnabled()->bool\n"
    "qtpropertybrowser.QtProperty.isModified()->bool\n"
    "qtpropertybrowser.QtProperty.label()->QString\n"
    "qtpropertybrowser.QtProperty.maximumText()->QString\n"
    "qtpropertybrowser.QtProperty.minimumText()->QString\n"
    "qtpropertybrowser.QtProperty.pkAvgText()->QString\n"
    "qtpropertybrowser.QtProperty.propertyChanged()\n"
    "qtpropertybrowser.QtProperty.propertyManager()->qtpropertybrowser.QtAbstractPropertyManager\n"
    "qtpropertybrowser.QtProperty.propertyName()->QString\n"
    "qtpropertybrowser.QtProperty.removeSubProperty(property:qtpropertybrowser.QtProperty)\n"
    "qtpropertybrowser.QtProperty.setEnabled(enable:bool)\n"
    "qtpropertybrowser.QtProperty.setLabel(text:QString)\n"
    "qtpropertybrowser.QtProperty.setModified(modified:bool)\n"
    "qtpropertybrowser.QtProperty.setPropertyName(text:QString)\n"
    "qtpropertybrowser.QtProperty.setStatusTip(text:QString)\n"
    "qtpropertybrowser.QtProperty.setToolTip(text:QString)\n"
    "qtpropertybrowser.QtProperty.setWhatsThis(text:QString)\n"
    "qtpropertybrowser.QtProperty.statusTip()->QString\n"
    "qtpropertybrowser.QtProperty.subProperties()->qtpropertybrowser.QtProperty\n"
    "qtpropertybrowser.QtProperty.toolTip()->QString\n"
    "qtpropertybrowser.QtProperty.unitText()->QString\n"
    "qtpropertybrowser.QtProperty.valueIcon()->PySide2.QtGui.QIcon\n"
    "qtpropertybrowser.QtProperty.valueText()->QString\n"
    "qtpropertybrowser.QtProperty.whatsThis()->QString\n"
;

void init_QtProperty(PyObject* module)
{
    _Sbk_QtProperty_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtProperty",
        "QtProperty*",
        &Sbk_QtProperty_spec,
        QtProperty_SignaturesString,
        &Shiboken::callCppDestructor< ::QtProperty >,
        0,
        0,
        0    );
    
    SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]
        = reinterpret_cast<PyTypeObject*>(Sbk_QtProperty_TypeF());

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(Sbk_QtProperty_TypeF(),
        QtProperty_PythonToCpp_QtProperty_PTR,
        is_QtProperty_PythonToCpp_QtProperty_PTR_Convertible,
        QtProperty_PTR_CppToPython_QtProperty);

    Shiboken::Conversions::registerConverterName(converter, "QtProperty");
    Shiboken::Conversions::registerConverterName(converter, "QtProperty*");
    Shiboken::Conversions::registerConverterName(converter, "QtProperty&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtProperty).name());
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtPropertyWrapper).name());



    QtPropertyWrapper::pysideInitQtMetaTypes();
}
