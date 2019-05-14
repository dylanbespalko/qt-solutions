
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
#include "qtarrayeditfactory_wrapper.h"

// inner classes

// Extra includes
#include <qobject.h>
#include <qteditorfactory.h>
#include <qtpropertybrowser.h>
#include <qtpropertymanager.h>
#include <qwidget.h>


#include <cctype>
#include <cstring>



template <class T>
static const char *typeNameOf(const T &t)
{
    const char *typeName =  typeid(t).name();
    auto size = std::strlen(typeName);
#if defined(Q_CC_MSVC) // MSVC: "class QPaintDevice * __ptr64"
    if (auto lastStar = strchr(typeName, '*')) {
        // MSVC: "class QPaintDevice * __ptr64"
        while (*--lastStar == ' ') {
        }
        size = lastStar - typeName + 1;
    }
#else // g++, Clang: "QPaintDevice *" -> "P12QPaintDevice"
    if (size > 2 && typeName[0] == 'P' && std::isdigit(typeName[1]))
        ++typeName;
#endif
    char *result = new char[size + 1];
    result[size] = '\0';
    strncpy(result, typeName, size);
    return result;
}

// Native ---------------------------------------------------------

void QtArrayEditFactoryWrapper::pysideInitQtMetaTypes()
{
}

QtArrayEditFactoryWrapper::QtArrayEditFactoryWrapper(QObject * parent) : QtArrayEditFactory(parent) {
    // ... middle
}

void QtArrayEditFactoryWrapper::connectPropertyManager(QtComplexArrayPropertyManager * manager)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "connectPropertyManager"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtArrayEditFactory::connectPropertyManager(manager);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), manager)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, nullptr));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QWidget * QtArrayEditFactoryWrapper::createAttributeEditor(QtComplexArrayPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return nullptr;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "createAttributeEditor"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtArrayEditFactory::createAttributeEditor(manager, property, parent, attribute);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(NNNN)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), manager),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), parent),
        Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_ATTRIBUTE_IDX])->converter, &attribute)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, nullptr));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return nullptr;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtArrayEditFactory.createAttributeEditor", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QWidget >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return nullptr;
    }
    ::QWidget* cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QWidget * QtArrayEditFactoryWrapper::createEditor(QtComplexArrayPropertyManager * manager, QtProperty * property, QWidget * parent)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return nullptr;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "createEditor"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtArrayEditFactory::createEditor(manager, property, parent);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(NNN)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), manager),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), parent)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, nullptr));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return nullptr;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtArrayEditFactory.createEditor", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QWidget >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return nullptr;
    }
    ::QWidget* cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtArrayEditFactoryWrapper::disconnectPropertyManager(QtComplexArrayPropertyManager * manager)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "disconnectPropertyManager"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtArrayEditFactory::disconnectPropertyManager(manager);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), manager)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, nullptr));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QtArrayEditFactoryWrapper::~QtArrayEditFactoryWrapper()
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(this);
    Shiboken::Object::destroy(wrapper, this);
}

// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_QtArrayEditFactory_Init(PyObject* self, PyObject* args, PyObject* kwds)
{
    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::QtArrayEditFactory >()))
        return -1;

    ::QtArrayEditFactoryWrapper* cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    int numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 1) {
        PyErr_SetString(PyExc_TypeError, "qtpropertybrowser.QtArrayEditFactory(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|O:QtArrayEditFactory", &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: QtArrayEditFactory::QtArrayEditFactory(QObject*)
    if (numArgs == 0) {
        overloadId = 0; // QtArrayEditFactory(QObject*)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0])))) {
        overloadId = 0; // QtArrayEditFactory(QObject*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtArrayEditFactory_Init_TypeError;

    // Call function/method
    {
        if (kwds) {
            PyObject* value = PyDict_GetItemString(kwds, "parent");
            if (value && pyArgs[0]) {
                PyErr_SetString(PyExc_TypeError, "qtpropertybrowser.QtArrayEditFactory(): got multiple values for keyword argument 'parent'.");
                return -1;
            } else if (value) {
                pyArgs[0] = value;
                if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0]))))
                    goto Sbk_QtArrayEditFactory_Init_TypeError;
            }
        }
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return -1;
        ::QObject* cppArg0 = 0;
        if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

        if (!PyErr_Occurred()) {
            // QtArrayEditFactory(QObject*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cptr = new ::QtArrayEditFactoryWrapper(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            Shiboken::Object::setParent(pyArgs[0], self);
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::QtArrayEditFactory >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_QtArrayEditFactory_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    Shiboken::Object::setHasCppWrapper(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_QtArrayEditFactory_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtArrayEditFactory");
        return -1;
}

static PyObject* Sbk_QtArrayEditFactoryFunc_connectPropertyManager(PyObject* self, PyObject* pyArg)
{
    QtArrayEditFactoryWrapper* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = static_cast<QtArrayEditFactoryWrapper *>(reinterpret_cast< ::QtArrayEditFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX], reinterpret_cast<SbkObject *>(self))));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: QtArrayEditFactory::connectPropertyManager(QtComplexArrayPropertyManager*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), (pyArg)))) {
        overloadId = 0; // connectPropertyManager(QtComplexArrayPropertyManager*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtArrayEditFactoryFunc_connectPropertyManager_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return {};
        ::QtComplexArrayPropertyManager* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // connectPropertyManager(QtComplexArrayPropertyManager*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtArrayEditFactoryWrapper*) cppSelf)->QtArrayEditFactoryWrapper::connectPropertyManager_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_QtArrayEditFactoryFunc_connectPropertyManager_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtArrayEditFactory.connectPropertyManager");
        return {};
}

static PyObject* Sbk_QtArrayEditFactoryFunc_createAttributeEditor(PyObject* self, PyObject* args)
{
    QtArrayEditFactoryWrapper* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = static_cast<QtArrayEditFactoryWrapper *>(reinterpret_cast< ::QtArrayEditFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX], reinterpret_cast<SbkObject *>(self))));
    PyObject* pyResult{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr, nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0, 0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "createAttributeEditor", 4, 4, &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2]), &(pyArgs[3])))
        return {};


    // Overloaded function decisor
    // 0: QtArrayEditFactory::createAttributeEditor(QtComplexArrayPropertyManager*,QtProperty*,QWidget*,Attribute)
    if (numArgs == 4
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[1])))
        && (pythonToCpp[2] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), (pyArgs[2])))
        && (pythonToCpp[3] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_ATTRIBUTE_IDX])->converter, (pyArgs[3])))) {
        overloadId = 0; // createAttributeEditor(QtComplexArrayPropertyManager*,QtProperty*,QWidget*,Attribute)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtArrayEditFactoryFunc_createAttributeEditor_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return {};
        ::QtComplexArrayPropertyManager* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        if (!Shiboken::Object::isValid(pyArgs[1]))
            return {};
        ::QtProperty* cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);
        if (!Shiboken::Object::isValid(pyArgs[2]))
            return {};
        ::QWidget* cppArg2;
        pythonToCpp[2](pyArgs[2], &cppArg2);
        ::Attribute cppArg3{NONE};
        pythonToCpp[3](pyArgs[3], &cppArg3);

        if (!PyErr_Occurred()) {
            // createAttributeEditor(QtComplexArrayPropertyManager*,QtProperty*,QWidget*,Attribute)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QWidget * cppResult = ((::QtArrayEditFactoryWrapper*) cppSelf)->QtArrayEditFactoryWrapper::createAttributeEditor_protected(cppArg0, cppArg1, cppArg2, cppArg3);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;

    Sbk_QtArrayEditFactoryFunc_createAttributeEditor_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtArrayEditFactory.createAttributeEditor");
        return {};
}

static PyObject* Sbk_QtArrayEditFactoryFunc_createEditor(PyObject* self, PyObject* args)
{
    QtArrayEditFactoryWrapper* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = static_cast<QtArrayEditFactoryWrapper *>(reinterpret_cast< ::QtArrayEditFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX], reinterpret_cast<SbkObject *>(self))));
    PyObject* pyResult{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "createEditor", 3, 3, &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2])))
        return {};


    // Overloaded function decisor
    // 0: QtArrayEditFactory::createEditor(QtComplexArrayPropertyManager*,QtProperty*,QWidget*)
    if (numArgs == 3
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[1])))
        && (pythonToCpp[2] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), (pyArgs[2])))) {
        overloadId = 0; // createEditor(QtComplexArrayPropertyManager*,QtProperty*,QWidget*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtArrayEditFactoryFunc_createEditor_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return {};
        ::QtComplexArrayPropertyManager* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        if (!Shiboken::Object::isValid(pyArgs[1]))
            return {};
        ::QtProperty* cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);
        if (!Shiboken::Object::isValid(pyArgs[2]))
            return {};
        ::QWidget* cppArg2;
        pythonToCpp[2](pyArgs[2], &cppArg2);

        if (!PyErr_Occurred()) {
            // createEditor(QtComplexArrayPropertyManager*,QtProperty*,QWidget*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QWidget * cppResult = ((::QtArrayEditFactoryWrapper*) cppSelf)->QtArrayEditFactoryWrapper::createEditor_protected(cppArg0, cppArg1, cppArg2);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;

    Sbk_QtArrayEditFactoryFunc_createEditor_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtArrayEditFactory.createEditor");
        return {};
}

static PyObject* Sbk_QtArrayEditFactoryFunc_disconnectPropertyManager(PyObject* self, PyObject* pyArg)
{
    QtArrayEditFactoryWrapper* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = static_cast<QtArrayEditFactoryWrapper *>(reinterpret_cast< ::QtArrayEditFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX], reinterpret_cast<SbkObject *>(self))));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: QtArrayEditFactory::disconnectPropertyManager(QtComplexArrayPropertyManager*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXARRAYPROPERTYMANAGER_IDX]), (pyArg)))) {
        overloadId = 0; // disconnectPropertyManager(QtComplexArrayPropertyManager*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtArrayEditFactoryFunc_disconnectPropertyManager_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return {};
        ::QtComplexArrayPropertyManager* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // disconnectPropertyManager(QtComplexArrayPropertyManager*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtArrayEditFactoryWrapper*) cppSelf)->QtArrayEditFactoryWrapper::disconnectPropertyManager_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_QtArrayEditFactoryFunc_disconnectPropertyManager_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtArrayEditFactory.disconnectPropertyManager");
        return {};
}

static PyObject* Sbk_QtArrayEditFactoryFunc_setSubFactory(PyObject* self, PyObject* pyArg)
{
    QtArrayEditFactoryWrapper* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = static_cast<QtArrayEditFactoryWrapper *>(reinterpret_cast< ::QtArrayEditFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX], reinterpret_cast<SbkObject *>(self))));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: QtArrayEditFactory::setSubFactory(QtComplexEditFactory*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXEDITFACTORY_IDX]), (pyArg)))) {
        overloadId = 0; // setSubFactory(QtComplexEditFactory*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtArrayEditFactoryFunc_setSubFactory_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return {};
        ::QtComplexEditFactory* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setSubFactory(QtComplexEditFactory*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtArrayEditFactoryWrapper*) cppSelf)->QtArrayEditFactoryWrapper::setSubFactory_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_QtArrayEditFactoryFunc_setSubFactory_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtArrayEditFactory.setSubFactory");
        return {};
}

static PyObject* Sbk_QtArrayEditFactoryFunc_subFactory(PyObject* self)
{
    QtArrayEditFactoryWrapper* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = static_cast<QtArrayEditFactoryWrapper *>(reinterpret_cast< ::QtArrayEditFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX], reinterpret_cast<SbkObject *>(self))));
    PyObject* pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // subFactory()const
            QtComplexEditFactory * cppResult = ((::QtArrayEditFactoryWrapper*) cppSelf)->QtArrayEditFactoryWrapper::subFactory_protected();
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXEDITFACTORY_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_QtArrayEditFactory_methods[] = {
    {"connectPropertyManager", (PyCFunction)Sbk_QtArrayEditFactoryFunc_connectPropertyManager, METH_O},
    {"createAttributeEditor", (PyCFunction)Sbk_QtArrayEditFactoryFunc_createAttributeEditor, METH_VARARGS},
    {"createEditor", (PyCFunction)Sbk_QtArrayEditFactoryFunc_createEditor, METH_VARARGS},
    {"disconnectPropertyManager", (PyCFunction)Sbk_QtArrayEditFactoryFunc_disconnectPropertyManager, METH_O},
    {"setSubFactory", (PyCFunction)Sbk_QtArrayEditFactoryFunc_setSubFactory, METH_O},
    {"subFactory", (PyCFunction)Sbk_QtArrayEditFactoryFunc_subFactory, METH_NOARGS},

    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_QtArrayEditFactory_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_QtArrayEditFactory_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_QtArrayEditFactory_Type = nullptr;
static SbkObjectType *Sbk_QtArrayEditFactory_TypeF(void)
{
    return _Sbk_QtArrayEditFactory_Type;
}

static PyType_Slot Sbk_QtArrayEditFactory_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void*>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void*>(Sbk_QtArrayEditFactory_traverse)},
    {Py_tp_clear,       reinterpret_cast<void*>(Sbk_QtArrayEditFactory_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void*>(Sbk_QtArrayEditFactory_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void*>(Sbk_QtArrayEditFactory_Init)},
    {Py_tp_new,         reinterpret_cast<void*>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_QtArrayEditFactory_spec = {
    "qtpropertybrowser.QtArrayEditFactory",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_QtArrayEditFactory_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void QtArrayEditFactory_PythonToCpp_QtArrayEditFactory_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_QtArrayEditFactory_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_QtArrayEditFactory_PythonToCpp_QtArrayEditFactory_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)Sbk_QtArrayEditFactory_TypeF()))
        return QtArrayEditFactory_PythonToCpp_QtArrayEditFactory_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtArrayEditFactory_PTR_CppToPython_QtArrayEditFactory(const void* cppIn) {
    PyObject* pyOut = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(cppIn);
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::QtArrayEditFactory *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
     }
    PyObject *result = Shiboken::Object::newObject(Sbk_QtArrayEditFactory_TypeF(), const_cast<void*>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
const char QtArrayEditFactory_SignaturesString[] = ""
    "qtpropertybrowser.QtArrayEditFactory(parent:PySide2.QtCore.QObject=0)\n"
    "qtpropertybrowser.QtArrayEditFactory.connectPropertyManager(manager:qtpropertybrowser.QtComplexArrayPropertyManager)\n"
    "qtpropertybrowser.QtArrayEditFactory.createAttributeEditor(manager:qtpropertybrowser.QtComplexArrayPropertyManager,property:qtpropertybrowser.QtProperty,parent:PySide2.QtWidgets.QWidget,attribute:qtpropertybrowser.Attribute)->PySide2.QtWidgets.QWidget\n"
    "qtpropertybrowser.QtArrayEditFactory.createEditor(manager:qtpropertybrowser.QtComplexArrayPropertyManager,property:qtpropertybrowser.QtProperty,parent:PySide2.QtWidgets.QWidget)->PySide2.QtWidgets.QWidget\n"
    "qtpropertybrowser.QtArrayEditFactory.disconnectPropertyManager(manager:qtpropertybrowser.QtComplexArrayPropertyManager)\n"
    "qtpropertybrowser.QtArrayEditFactory.setSubFactory(subFactory:qtpropertybrowser.QtComplexEditFactory)\n"
    "qtpropertybrowser.QtArrayEditFactory.subFactory()->qtpropertybrowser.QtComplexEditFactory\n"
;

void init_QtArrayEditFactory(PyObject* module)
{
    _Sbk_QtArrayEditFactory_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtArrayEditFactory",
        "QtArrayEditFactory*",
        &Sbk_QtArrayEditFactory_spec,
        QtArrayEditFactory_SignaturesString,
        &Shiboken::callCppDestructor< ::QtArrayEditFactory >,
        0,
        0,
        0    );
    
    SbkqtpropertybrowserTypes[SBK_QTARRAYEDITFACTORY_IDX]
        = reinterpret_cast<PyTypeObject*>(Sbk_QtArrayEditFactory_TypeF());

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(Sbk_QtArrayEditFactory_TypeF(),
        QtArrayEditFactory_PythonToCpp_QtArrayEditFactory_PTR,
        is_QtArrayEditFactory_PythonToCpp_QtArrayEditFactory_PTR_Convertible,
        QtArrayEditFactory_PTR_CppToPython_QtArrayEditFactory);

    Shiboken::Conversions::registerConverterName(converter, "QtArrayEditFactory");
    Shiboken::Conversions::registerConverterName(converter, "QtArrayEditFactory*");
    Shiboken::Conversions::registerConverterName(converter, "QtArrayEditFactory&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtArrayEditFactory).name());
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtArrayEditFactoryWrapper).name());



    QtArrayEditFactoryWrapper::pysideInitQtMetaTypes();
}
