
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
#include "qtbrowseritem_wrapper.h"

// inner classes

// Extra includes
#include <QList>
#include <qtpropertybrowser.h>


#include <cctype>
#include <cstring>

QT_WARNING_DISABLE_DEPRECATED



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
    if (size > 2 && typeName[0] == 'P' && std::isdigit(typeName[1])) {
        ++typeName;
        --size;
    }
#endif
    char *result = new char[size + 1];
    result[size] = '\0';
    memcpy(result, typeName, size);
    return result;
}


// Target ---------------------------------------------------------

extern "C" {
static PyObject* Sbk_QtBrowserItemFunc_browser(PyObject* self)
{
    ::QtBrowserItem* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // browser()const
            QtAbstractPropertyBrowser * cppResult = const_cast<const ::QtBrowserItem*>(cppSelf)->browser();
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTABSTRACTPROPERTYBROWSER_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject* Sbk_QtBrowserItemFunc_children(PyObject* self)
{
    ::QtBrowserItem* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // children()const
            QList<QtBrowserItem* > cppResult = const_cast<const ::QtBrowserItem*>(cppSelf)->children();
            pyResult = Shiboken::Conversions::copyToPython(SbkqtpropertybrowserTypeConverters[SBK_QTPROPERTYBROWSER_QLIST_QTBROWSERITEMPTR_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject* Sbk_QtBrowserItemFunc_parent(PyObject* self)
{
    ::QtBrowserItem* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // parent()const
            QtBrowserItem * cppResult = const_cast<const ::QtBrowserItem*>(cppSelf)->parent();
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject* Sbk_QtBrowserItemFunc_property(PyObject* self)
{
    ::QtBrowserItem* cppSelf = nullptr;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return {};
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // property()const
            QtProperty * cppResult = const_cast<const ::QtBrowserItem*>(cppSelf)->property();
            pyResult = Shiboken::Conversions::pointerToPython(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPROPERTY_IDX]), cppResult);
            Shiboken::Object::setParent(self, pyResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_QtBrowserItem_methods[] = {
    {"browser", reinterpret_cast<PyCFunction>(Sbk_QtBrowserItemFunc_browser), METH_NOARGS},
    {"children", reinterpret_cast<PyCFunction>(Sbk_QtBrowserItemFunc_children), METH_NOARGS},
    {"parent", reinterpret_cast<PyCFunction>(Sbk_QtBrowserItemFunc_parent), METH_NOARGS},
    {"property", reinterpret_cast<PyCFunction>(Sbk_QtBrowserItemFunc_property), METH_NOARGS},

    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_QtBrowserItem_traverse(PyObject* self, visitproc visit, void* arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_QtBrowserItem_clear(PyObject* self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_QtBrowserItem_Type = nullptr;
static SbkObjectType *Sbk_QtBrowserItem_TypeF(void)
{
    return _Sbk_QtBrowserItem_Type;
}

static PyType_Slot Sbk_QtBrowserItem_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void*>(SbkDeallocWrapperWithPrivateDtor)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void*>(Sbk_QtBrowserItem_traverse)},
    {Py_tp_clear,       reinterpret_cast<void*>(Sbk_QtBrowserItem_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void*>(Sbk_QtBrowserItem_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        nullptr},
    {Py_tp_new,         reinterpret_cast<void*>(SbkDummyNew /* PYSIDE-595: Prevent replacement of "0" with base->tp_new. */)},
    {0, nullptr}
};
static PyType_Spec Sbk_QtBrowserItem_spec = {
    "qtpropertybrowser.QtBrowserItem",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_QtBrowserItem_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void QtBrowserItem_PythonToCpp_QtBrowserItem_PTR(PyObject* pyIn, void* cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_QtBrowserItem_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_QtBrowserItem_PythonToCpp_QtBrowserItem_PTR_Convertible(PyObject* pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject*>(Sbk_QtBrowserItem_TypeF())))
        return QtBrowserItem_PythonToCpp_QtBrowserItem_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtBrowserItem_PTR_CppToPython_QtBrowserItem(const void* cppIn) {
    auto pyOut = reinterpret_cast<PyObject*>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::QtBrowserItem *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
     }
    PyObject *result = Shiboken::Object::newObject(Sbk_QtBrowserItem_TypeF(), const_cast<void*>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *QtBrowserItem_SignatureStrings[] = {
    "qtpropertybrowser.QtBrowserItem.browser()->qtpropertybrowser.QtAbstractPropertyBrowser",
    "qtpropertybrowser.QtBrowserItem.children()->QList[qtpropertybrowser.QtBrowserItem]",
    "qtpropertybrowser.QtBrowserItem.parent()->qtpropertybrowser.QtBrowserItem",
    "qtpropertybrowser.QtBrowserItem.property()->qtpropertybrowser.QtProperty",
    nullptr}; // Sentinel

void init_QtBrowserItem(PyObject* module)
{
    _Sbk_QtBrowserItem_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtBrowserItem",
        "QtBrowserItem*",
        &Sbk_QtBrowserItem_spec,
        QtBrowserItem_SignatureStrings,
        0,
        0,
        0,
        0    );
    
    SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX]
        = reinterpret_cast<PyTypeObject*>(Sbk_QtBrowserItem_TypeF());

    // Register Converter
    SbkConverter* converter = Shiboken::Conversions::createConverter(Sbk_QtBrowserItem_TypeF(),
        QtBrowserItem_PythonToCpp_QtBrowserItem_PTR,
        is_QtBrowserItem_PythonToCpp_QtBrowserItem_PTR_Convertible,
        QtBrowserItem_PTR_CppToPython_QtBrowserItem);

    Shiboken::Conversions::registerConverterName(converter, "QtBrowserItem");
    Shiboken::Conversions::registerConverterName(converter, "QtBrowserItem*");
    Shiboken::Conversions::registerConverterName(converter, "QtBrowserItem&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::QtBrowserItem).name());



}
