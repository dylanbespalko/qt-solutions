// @snippet qtabstractpropertybrowser-setFactoryForManager
static void setFactoryForManager_glue(QtAbstractPropertyBrowser* self, PyObject* pyManager, PyObject* pyFactory )
{
    Shiboken::GilState gil;
    PythonToCppFunc pythonToCpp;
    SbkObjectType* shiboType;
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTBOOLPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtBoolPropertyManager* cppManager;
        QtAbstractEditorFactory< QtBoolPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtBoolPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtBoolPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtBoolPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtBoolPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTINTPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtIntPropertyManager* cppManager;
        QtAbstractEditorFactory< QtIntPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtIntPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtIntPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtIntPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtIntPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTDOUBLEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtDoublePropertyManager* cppManager;
        QtAbstractEditorFactory< QtDoublePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtDoublePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtDoublePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtDoublePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtDoublePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOMPLEXPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtComplexPropertyManager* cppManager;
        QtAbstractEditorFactory< QtComplexPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtComplexPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtComplexPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtComplexPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtComplexPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTTFTENSORPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtTFTensorPropertyManager* cppManager;
        QtAbstractEditorFactory< QtTFTensorPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtTFTensorPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtTFTensorPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtTFTensorPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtTFTensorPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCHARPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtCharPropertyManager* cppManager;
        QtAbstractEditorFactory< QtCharPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtCharPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtCharPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtCharPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtCharPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTSTRINGPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtStringPropertyManager* cppManager;
        QtAbstractEditorFactory< QtStringPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtStringPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtStringPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtStringPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtStringPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTFILEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtFilePropertyManager* cppManager;
        QtAbstractEditorFactory< QtFilePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtFilePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtFilePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtFilePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtFilePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTKEYSEQUENCEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtKeySequencePropertyManager* cppManager;
        QtAbstractEditorFactory< QtKeySequencePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtKeySequencePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtKeySequencePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtKeySequencePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtKeySequencePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTENUMPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtEnumPropertyManager* cppManager;
        QtAbstractEditorFactory< QtEnumPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
        cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
        cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtEnumPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtEnumPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtEnumPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtEnumPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTFLAGPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtFlagPropertyManager* cppManager;
        QtAbstractEditorFactory< QtFlagPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtFlagPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtFlagPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtFlagPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtFlagPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTFONTPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtFontPropertyManager* cppManager;
        QtAbstractEditorFactory< QtFontPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtFontPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtFontPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtFontPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtFontPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCURSORPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtCursorPropertyManager* cppManager;
        QtAbstractEditorFactory< QtCursorPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
        cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
        cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtCursorPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtCursorPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtCursorPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtCursorPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTCOLORPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtColorPropertyManager* cppManager;
        QtAbstractEditorFactory< QtColorPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtColorPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtColorPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtColorPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtColorPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPOINTPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtPointPropertyManager* cppManager;
        QtAbstractEditorFactory< QtPointPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtPointPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtPointPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtPointPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtPointPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTPOINTFPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtPointFPropertyManager* cppManager;
        QtAbstractEditorFactory< QtPointFPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtPointFPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtPointFPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtPointFPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtPointFPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTRECTPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtRectPropertyManager* cppManager;
        QtAbstractEditorFactory< QtRectPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtRectPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtRectPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtRectPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtRectPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTRECTFPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtRectFPropertyManager* cppManager;
        QtAbstractEditorFactory< QtRectFPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtRectFPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtRectFPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtRectFPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtRectFPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTSIZEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtSizePropertyManager* cppManager;
        QtAbstractEditorFactory< QtSizePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtSizePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtSizePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtSizePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtSizePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTSIZEFPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtSizeFPropertyManager* cppManager;
        QtAbstractEditorFactory< QtSizeFPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtSizeFPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtSizeFPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtSizeFPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtSizeFPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTSIZEPOLICYPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtSizePolicyPropertyManager* cppManager;
        QtAbstractEditorFactory< QtSizePolicyPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtSizePolicyPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtSizePolicyPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtSizePolicyPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtSizePolicyPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTDATEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtDatePropertyManager* cppManager;
        QtAbstractEditorFactory< QtDatePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
        cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
        cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtDatePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtDatePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtDatePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtDatePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTDATETIMEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtDateTimePropertyManager* cppManager;
        QtAbstractEditorFactory< QtDateTimePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
        cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
        cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtDateTimePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtDateTimePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtDateTimePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtDateTimePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTTIMEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtTimePropertyManager* cppManager;
        QtAbstractEditorFactory< QtTimePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
        cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
        cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtTimePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtTimePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtTimePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtTimePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTLOCALEPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtLocalePropertyManager* cppManager;
        QtAbstractEditorFactory< QtLocalePropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtLocalePropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtLocalePropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtLocalePropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtLocalePropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTVARIANTPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtVariantPropertyManager* cppManager;
        QtAbstractEditorFactory< QtVariantPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtVariantPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtVariantPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtVariantPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtVariantPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
    pythonToCpp = Shiboken::Conversions::isPythonToCppPointerConvertible(reinterpret_cast<SbkObjectType *>(SbkqtpropertybrowserTypes[SBK_QTGROUPPROPERTYMANAGER_IDX]), pyManager);
    if (pythonToCpp) {
        QtGroupPropertyManager* cppManager;
        QtAbstractEditorFactory< QtGroupPropertyManager >* cppFactory;
        pythonToCpp( pyManager, &cppManager);
        if (pyFactory == Py_None)
            cppFactory = 0;
        shiboType = reinterpret_cast<SbkObjectType*>(pyFactory->ob_type);
        if (Shiboken::ObjectType::hasCast(shiboType))
            cppFactory = reinterpret_cast<QtAbstractEditorFactory< QtGroupPropertyManager >*>(Shiboken::ObjectType::cast(shiboType, reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtGroupPropertyManager >>()));
        cppFactory = (QtAbstractEditorFactory< QtGroupPropertyManager >*) Shiboken::Object::cppPointer(reinterpret_cast<SbkObject*>(pyFactory), Shiboken::SbkType<QtAbstractEditorFactory< QtGroupPropertyManager >>());
        gil.release();
        self->setFactoryForManager(cppManager, cppFactory);
        return;
    }
}
// @snippet qtabstractpropertybrowser-setFactoryForManager
