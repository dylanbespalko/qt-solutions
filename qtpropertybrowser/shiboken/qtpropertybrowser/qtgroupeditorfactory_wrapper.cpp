
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
#include "qtgroupeditorfactory_wrapper.h"

// inner classes

// Extra includes
#include <qobject.h>
#include <qtpropertybrowser.h>
#include <qtpropertymanager.h>
#include <qwidget.h>


// Native ---------------------------------------------------------

void QtGroupEditorFactoryWrapper::pysideInitQtMetaTypes()
{
}

QtGroupEditorFactoryWrapper::QtGroupEditorFactoryWrapper(QObject * parent) : QtGroupEditorFactory(parent) {
    // ... middle
}

void QtGroupEditorFactoryWrapper::connectPropertyManager(QtGroupPropertyManager * manager)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "connectPropertyManager"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtGroupEditorFactory::connectPropertyManager(manager);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), manager)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QWidget * QtGroupEditorFactoryWrapper::createAttributeEditor(QtGroupPropertyManager * manager, QtProperty * property, QWidget * parent, BrowserCol attribute)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return nullptr;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "createAttributeEditor"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtGroupEditorFactory::createAttributeEditor(manager, property, parent, attribute);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(NNNN)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), manager),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), parent),
        Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_BROWSERCOL_IDX])->converter, &attribute)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return nullptr;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtGroupEditorFactory.createAttributeEditor", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QWidget >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return nullptr;
    }
    ::QWidget* cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

QWidget * QtGroupEditorFactoryWrapper::createEditor(QtGroupPropertyManager * manager, QtProperty * property, QWidget * parent)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return nullptr;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "createEditor"));
    if (pyOverride.isNull()) {
        gil.release();
        return this->::QtGroupEditorFactory::createEditor(manager, property, parent);
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(NNN)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), manager),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), property),
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), parent)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return nullptr;
    }
    // Check return type
    PythonToCppFunc pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), pyResult);
    if (!pythonToCpp) {
        Shiboken::warning(PyExc_RuntimeWarning, 2, "Invalid return value in function %s, expected %s, got %s.", "QtGroupEditorFactory.createEditor", reinterpret_cast<PyTypeObject *>(Shiboken::SbkType< QWidget >())->tp_name, Py_TYPE(pyResult)->tp_name);
        return nullptr;
    }
    ::QWidget* cppResult;
    pythonToCpp(pyResult, &cppResult);
    return cppResult;
}

void QtGroupEditorFactoryWrapper::disconnectPropertyManager(QtGroupPropertyManager * manager)
{
    Shiboken::GilState gil;
    if (PyErr_Occurred())
        return;
    Shiboken::AutoDecRef pyOverride(Shiboken::BindingManager::instance().getOverride(this, "disconnectPropertyManager"));
    if (pyOverride.isNull()) {
        gil.release();
        this->::QtGroupEditorFactory::disconnectPropertyManager(manager);
        return;
    }

    Shiboken::AutoDecRef pyArgs(Py_BuildValue("(N)",
        Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), manager)
    ));

    Shiboken::AutoDecRef pyResult(PyObject_Call(pyOverride, pyArgs, NULL));
    // An error happened in python code!
    if (pyResult.isNull()) {
        PyErr_Print();
        return;
    }
}

QtGroupEditorFactoryWrapper::~QtGroupEditorFactoryWrapper()
{
    SbkObject* wrapper = Shiboken::BindingManager::instance().retrieveWrapper(this);
    Shiboken::Object::destroy(wrapper, this);
}

// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_QtGroupEditorFactory_Init(PyObject* self, PyObject* args, PyObject* kwds)
{
    SbkObject* sbkSelf = reinterpret_cast<SbkObject*>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::QtGroupEditorFactory >()))
        return -1;

    ::QtGroupEditorFactoryWrapper* cptr = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0 };
    SBK_UNUSED(pythonToCpp)
    int numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 1) {
        PyErr_SetString(PyExc_TypeError, "qtpropertybrowser.QtGroupEditorFactory(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|O:QtGroupEditorFactory", &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: QtGroupEditorFactory(QObject*)
    if (numArgs == 0) {
        overloadId = 0; // QtGroupEditorFactory(QObject*)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0])))) {
        overloadId = 0; // QtGroupEditorFactory(QObject*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtGroupEditorFactory_Init_TypeError;

    // Call function/method
    {
        if (kwds) {
            PyObject* value = PyDict_GetItemString(kwds, "parent");
            if (value && pyArgs[0]) {
                PyErr_SetString(PyExc_TypeError, "qtpropertybrowser.QtGroupEditorFactory(): got multiple values for keyword argument 'parent'.");
                return -1;
            } else if (value) {
                pyArgs[0] = value;
                if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtCoreTypes[SBK_QOBJECT_IDX]), (pyArgs[0]))))
                    goto Sbk_QtGroupEditorFactory_Init_TypeError;
            }
        }
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return -1;
        ::QObject* cppArg0 = nullptr;
        if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

        if (!PyErr_Occurred()) {
            // QtGroupEditorFactory(QObject*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            cptr = new ::QtGroupEditorFactoryWrapper(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            Shiboken::Object::setParent(pyArgs[0], self);
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::QtGroupEditorFactory >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_QtGroupEditorFactory_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    Shiboken::Object::setHasCppWrapper(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_QtGroupEditorFactory_Init_TypeError:
        const char* overloads[] = {"PySide2.QtCore.QObject = nullptr", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtGroupEditorFactory", overloads);
        return -1;
}

static PyObject* Sbk_QtGroupEditorFactoryFunc_connectPropertyManager(PyObject* self, PyObject* pyArg)
{
    QtGroupEditorFactoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtGroupEditorFactoryWrapper*)reinterpret_cast< ::QtGroupEditorFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTGROUPEDITORFACTORY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: connectPropertyManager(QtGroupPropertyManager*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), (pyArg)))) {
        overloadId = 0; // connectPropertyManager(QtGroupPropertyManager*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtGroupEditorFactoryFunc_connectPropertyManager_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtGroupPropertyManager* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // connectPropertyManager(QtGroupPropertyManager*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtGroupEditorFactoryWrapper*) cppSelf)->QtGroupEditorFactoryWrapper::connectPropertyManager_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtGroupEditorFactoryFunc_connectPropertyManager_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtGroupPropertyManager", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtGroupEditorFactory.connectPropertyManager", overloads);
        return 0;
}

static PyObject* Sbk_QtGroupEditorFactoryFunc_createAttributeEditor(PyObject* self, PyObject* args)
{
    QtGroupEditorFactoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtGroupEditorFactoryWrapper*)reinterpret_cast< ::QtGroupEditorFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTGROUPEDITORFACTORY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0, 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0, 0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "createAttributeEditor", 4, 4, &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2]), &(pyArgs[3])))
        return 0;


    // Overloaded function decisor
    // 0: createAttributeEditor(QtGroupPropertyManager*,QtProperty*,QWidget*,BrowserCol)
    if (numArgs == 4
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[1])))
        && (pythonToCpp[2] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), (pyArgs[2])))
        && (pythonToCpp[3] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkqtpropertybrowserTypes[SBK_BROWSERCOL_IDX])->converter, (pyArgs[3])))) {
        overloadId = 0; // createAttributeEditor(QtGroupPropertyManager*,QtProperty*,QWidget*,BrowserCol)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtGroupEditorFactoryFunc_createAttributeEditor_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtGroupPropertyManager* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        if (!Shiboken::Object::isValid(pyArgs[1]))
            return 0;
        ::QtProperty* cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);
        if (!Shiboken::Object::isValid(pyArgs[2]))
            return 0;
        ::QWidget* cppArg2;
        pythonToCpp[2](pyArgs[2], &cppArg2);
        ::BrowserCol cppArg3{NONE};
        pythonToCpp[3](pyArgs[3], &cppArg3);

        if (!PyErr_Occurred()) {
            // createAttributeEditor(QtGroupPropertyManager*,QtProperty*,QWidget*,BrowserCol)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QWidget * cppResult = ((::QtGroupEditorFactoryWrapper*) cppSelf)->QtGroupEditorFactoryWrapper::createAttributeEditor_protected(cppArg0, cppArg1, cppArg2, cppArg3);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtGroupEditorFactoryFunc_createAttributeEditor_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtGroupPropertyManager, qtpropertybrowser.QtProperty, PySide2.QtWidgets.QWidget, qtpropertybrowser.BrowserCol", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtGroupEditorFactory.createAttributeEditor", overloads);
        return 0;
}

static PyObject* Sbk_QtGroupEditorFactoryFunc_createEditor(PyObject* self, PyObject* args)
{
    QtGroupEditorFactoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtGroupEditorFactoryWrapper*)reinterpret_cast< ::QtGroupEditorFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTGROUPEDITORFACTORY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { 0, 0, 0 };
    SBK_UNUSED(pythonToCpp)
    int numArgs = PyTuple_GET_SIZE(args);
    PyObject* pyArgs[] = {0, 0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "createEditor", 3, 3, &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2])))
        return 0;


    // Overloaded function decisor
    // 0: createEditor(QtGroupPropertyManager*,QtProperty*,QWidget*)
    if (numArgs == 3
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), (pyArgs[0])))
        && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), (pyArgs[1])))
        && (pythonToCpp[2] = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), (pyArgs[2])))) {
        overloadId = 0; // createEditor(QtGroupPropertyManager*,QtProperty*,QWidget*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtGroupEditorFactoryFunc_createEditor_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArgs[0]))
            return 0;
        ::QtGroupPropertyManager* cppArg0;
        pythonToCpp[0](pyArgs[0], &cppArg0);
        if (!Shiboken::Object::isValid(pyArgs[1]))
            return 0;
        ::QtProperty* cppArg1;
        pythonToCpp[1](pyArgs[1], &cppArg1);
        if (!Shiboken::Object::isValid(pyArgs[2]))
            return 0;
        ::QWidget* cppArg2;
        pythonToCpp[2](pyArgs[2], &cppArg2);

        if (!PyErr_Occurred()) {
            // createEditor(QtGroupPropertyManager*,QtProperty*,QWidget*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            QWidget * cppResult = ((::QtGroupEditorFactoryWrapper*) cppSelf)->QtGroupEditorFactoryWrapper::createEditor_protected(cppArg0, cppArg1, cppArg2);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkPySide2_QtWidgetsTypes[SBK_QWIDGET_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return 0;
    }
    return pyResult;

    Sbk_QtGroupEditorFactoryFunc_createEditor_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtGroupPropertyManager, qtpropertybrowser.QtProperty, PySide2.QtWidgets.QWidget", 0};
        Shiboken::setErrorAboutWrongArguments(args, "qtpropertybrowser.QtGroupEditorFactory.createEditor", overloads);
        return 0;
}

static PyObject* Sbk_QtGroupEditorFactoryFunc_disconnectPropertyManager(PyObject* self, PyObject* pyArg)
{
    QtGroupEditorFactoryWrapper* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = (QtGroupEditorFactoryWrapper*)reinterpret_cast< ::QtGroupEditorFactory *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTGROUPEDITORFACTORY_IDX], reinterpret_cast<SbkObject *>(self)));
    int overloadId = -1;
    PythonToCppFunc pythonToCpp;
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: disconnectPropertyManager(QtGroupPropertyManager*)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), (pyArg)))) {
        overloadId = 0; // disconnectPropertyManager(QtGroupPropertyManager*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_QtGroupEditorFactoryFunc_disconnectPropertyManager_TypeError;

    // Call function/method
    {
        if (!Shiboken::Object::isValid(pyArg))
            return 0;
        ::QtGroupPropertyManager* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // disconnectPropertyManager(QtGroupPropertyManager*)
            PyThreadState* _save = PyEval_SaveThread(); // Py_BEGIN_ALLOW_THREADS
            ((::QtGroupEditorFactoryWrapper*) cppSelf)->QtGroupEditorFactoryWrapper::disconnectPropertyManager_protected(cppArg0);
            PyEval_RestoreThread(_save); // Py_END_ALLOW_THREADS
        }
    }

    if (PyErr_Occurred()) {
        return 0;
    }
    Py_RETURN_NONE;

    Sbk_QtGroupEditorFactoryFunc_disconnectPropertyManager_TypeError:
        const char* overloads[] = {"qtpropertybrowser.QtGroupPropertyManager", 0};
        Shiboken::setErrorAboutWrongArguments(pyArg, "qtpropertybrowser.QtGroupEditorFactory.disconnectPropertyManager", overloads);
        return 0;
}

static PyMethodDef Sbk_QtGroupEditorFactory_methods[] = {
    {"connectPropertyManager", (PyCFunction)Sbk_QtGroupEditorFactoryFunc_connectPropertyManager, METH_O},
    {"createAttributeEditor", (PyCFunction)Sbk_QtGroupEditorFactoryFunc_createAttributeEditor, METH_VARARGS},
    {"createEditor", (PyCFunction)Sbk_QtGroupEditorFactoryFunc_createEditor, METH_VARARGS},
    {"disconnectPropertyManager", (PyCFunction)Sbk_QtGroupEditorFactoryFunc_disconnectPropertyManager, METH_O},

    {0} // Sentinel
};

} // extern "C"

static int Sbk_QtGroupEditorFactory_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_QtGroupEditorFactory_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_QtGroupEditorFactory_Type = nullptr;
static SbkObjectType *Sbk_QtGroupEditorFactory_TypeF(void)
{
    return _Sbk_QtGroupEditorFactory_Type;
}

static PyType_Slot Sbk_QtGroupEditorFactory_slots[] = {
    {Py_tp_base,        (void *)0}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     (void *)&SbkDeallocWrapper},
    {Py_tp_repr,        (void *)0},
    {Py_tp_hash,        (void *)0},
    {Py_tp_call,        (void *)0},
    {Py_tp_str,         (void *)0},
    {Py_tp_getattro,    (void *)0},
    {Py_tp_setattro,    (void *)0},
    {Py_tp_traverse,    (void *)Sbk_QtGroupEditorFactory_traverse},
    {Py_tp_clear,       (void *)Sbk_QtGroupEditorFactory_clear},
    {Py_tp_richcompare, (void *)0},
    {Py_tp_iter,        (void *)0},
    {Py_tp_iternext,    (void *)0},
    {Py_tp_methods,     (void *)Sbk_QtGroupEditorFactory_methods},
    {Py_tp_getset,      (void *)0},
    {Py_tp_init,        (void *)Sbk_QtGroupEditorFactory_Init},
    {Py_tp_new,         (void *)SbkObjectTpNew},
    {0, 0}
};
static PyType_Spec Sbk_QtGroupEditorFactory_spec = {
    "qtpropertybrowser.QtGroupEditorFactory",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_QtGroupEditorFactory_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void QtGroupEditorFactory_PythonToCpp_QtGroupEditorFactory_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_QtGroupEditorFactory_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_QtGroupEditorFactory_PythonToCpp_QtGroupEditorFactory_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)Sbk_QtGroupEditorFactory_TypeF()))
        return QtGroupEditorFactory_PythonToCpp_QtGroupEditorFactory_PTR;
    return 0;
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtGroupEditorFactory_PTR_CppToPython_QtGroupEditorFactory(const void* cppIn) {
    PyObject* pyOut = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(cppIn);
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    const char* typeName = typeid(*((::QtGroupEditorFactory*)cppIn)).name();
    return Shiboken::Object::newObject(Sbk_QtGroupEditorFactory_TypeF(), const_cast<void*>(cppIn), false, false, typeName);
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
const char QtGroupEditorFactory_SignaturesString[] = ""
    "qtpropertybrowser.QtGroupEditorFactory(parent:PySide2.QtCore.QObject=nullptr)\n"
    "qtpropertybrowser.QtGroupEditorFactory.connectPropertyManager(manager:qtpropertybrowser.QtGroupPropertyManager)\n"
    "qtpropertybrowser.QtGroupEditorFactory.createAttributeEditor(manager:qtpropertybrowser.QtGroupPropertyManager,property:qtpropertybrowser.QtProperty,parent:PySide2.QtWidgets.QWidget,attribute:qtpropertybrowser.BrowserCol)->PySide2.QtWidgets.QWidget\n"
    "qtpropertybrowser.QtGroupEditorFactory.createEditor(manager:qtpropertybrowser.QtGroupPropertyManager,property:qtpropertybrowser.QtProperty,parent:PySide2.QtWidgets.QWidget)->PySide2.QtWidgets.QWidget\n"
    "qtpropertybrowser.QtGroupEditorFactory.disconnectPropertyManager(manager:qtpropertybrowser.QtGroupPropertyManager)\n"
;

void init_QtGroupEditorFactory(PyObject* module)
{
    _Sbk_QtGroupEditorFactory_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtGroupEditorFactory",
        "QtGroupEditorFactory*",
        &Sbk_QtGroupEditorFactory_spec,
        QtGroupEditorFactory_SignaturesString,
        &Shiboken::callCppDestructor< ::QtGroupEditorFactory >,
        0,
        0,
        0    );
    
    SbkqtpropertybrowserTypes[SBK_QTGROUPEDITORFACTORY_IDX]
        = reinterpret_cast<PyTypeObject*>(Sbk_QtGroupEditorFactory_TypeF());

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(Sbk_QtGroupEditorFactory_TypeF(),
        QtGroupEditorFactory_PythonToCpp_QtGroupEditorFactory_PTR,
        is_QtGroupEditorFactory_PythonToCpp_QtGroupEditorFactory_PTR_Convertible,
        QtGroupEditorFactory_PTR_CppToPython_QtGroupEditorFactory);

    Shiboken::Conversions::registerConverterName(converter, "QtGroupEditorFactory");
    Shiboken::Conversions::registerConverterName(converter, "QtGroupEditorFactory*");
    Shiboken::Conversions::registerConverterName(converter, "QtGroupEditorFactory&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtGroupEditorFactory).name());
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtGroupEditorFactoryWrapper).name());



    QtGroupEditorFactoryWrapper::pysideInitQtMetaTypes();
}
