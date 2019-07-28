
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



// Target ---------------------------------------------------------

extern "C" {
static PyObject* Sbk_QtBrowserItemFunc_browser(PyObject* self)
{
    ::QtBrowserItem* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

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
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtBrowserItemFunc_children(PyObject* self)
{
    ::QtBrowserItem* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

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
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtBrowserItemFunc_parent(PyObject* self)
{
    ::QtBrowserItem* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

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
        return 0;
    }
    return pyResult;
}

static PyObject* Sbk_QtBrowserItemFunc_property(PyObject* self)
{
    ::QtBrowserItem* cppSelf = 0;
    SBK_UNUSED(cppSelf)
    if (!Shiboken::Object::isValid(self))
        return 0;
    cppSelf = reinterpret_cast< ::QtBrowserItem *>(Shiboken::Conversions::cppPointer(SbkqtpropertybrowserTypes[SBK_QTBROWSERITEM_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject* pyResult = 0;

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
        return 0;
    }
    return pyResult;
}

static PyMethodDef Sbk_QtBrowserItem_methods[] = {
    {"browser", (PyCFunction)Sbk_QtBrowserItemFunc_browser, METH_NOARGS},
    {"children", (PyCFunction)Sbk_QtBrowserItemFunc_children, METH_NOARGS},
    {"parent", (PyCFunction)Sbk_QtBrowserItemFunc_parent, METH_NOARGS},
    {"property", (PyCFunction)Sbk_QtBrowserItemFunc_property, METH_NOARGS},

    {0} // Sentinel
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
    {Py_tp_base,        (void *)0}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     (void *)SbkDeallocWrapperWithPrivateDtor},
    {Py_tp_repr,        (void *)0},
    {Py_tp_hash,        (void *)0},
    {Py_tp_call,        (void *)0},
    {Py_tp_str,         (void *)0},
    {Py_tp_getattro,    (void *)0},
    {Py_tp_setattro,    (void *)0},
    {Py_tp_traverse,    (void *)Sbk_QtBrowserItem_traverse},
    {Py_tp_clear,       (void *)Sbk_QtBrowserItem_clear},
    {Py_tp_richcompare, (void *)0},
    {Py_tp_iter,        (void *)0},
    {Py_tp_iternext,    (void *)0},
    {Py_tp_methods,     (void *)Sbk_QtBrowserItem_methods},
    {Py_tp_getset,      (void *)0},
    {Py_tp_init,        (void *)0},
    {Py_tp_new,         (void *)SbkDummyNew /* PYSIDE-595: Prevent replacement of "0" with base->tp_new. */},
    {0, 0}
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
    if (PyObject_TypeCheck(pyIn, (PyTypeObject*)Sbk_QtBrowserItem_TypeF()))
        return QtBrowserItem_PythonToCpp_QtBrowserItem_PTR;
    return 0;
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject* QtBrowserItem_PTR_CppToPython_QtBrowserItem(const void* cppIn) {
    PyObject* pyOut = (PyObject*)Shiboken::BindingManager::instance().retrieveWrapper(cppIn);
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    const char* typeName = typeid(*((::QtBrowserItem*)cppIn)).name();
    return Shiboken::Object::newObject(Sbk_QtBrowserItem_TypeF(), const_cast<void*>(cppIn), false, false, typeName);
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
const char QtBrowserItem_SignaturesString[] = ""
    "qtpropertybrowser.QtBrowserItem.browser()->qtpropertybrowser.QtAbstractPropertyBrowser\n"
    "qtpropertybrowser.QtBrowserItem.children()->qtpropertybrowser.QtBrowserItem\n"
    "qtpropertybrowser.QtBrowserItem.parent()->qtpropertybrowser.QtBrowserItem\n"
    "qtpropertybrowser.QtBrowserItem.property()->qtpropertybrowser.QtProperty\n"
;

void init_QtBrowserItem(PyObject* module)
{
    _Sbk_QtBrowserItem_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "QtBrowserItem",
        "QtBrowserItem*",
        &Sbk_QtBrowserItem_spec,
        QtBrowserItem_SignaturesString,
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
