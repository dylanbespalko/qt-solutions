#ifndef SBK_QTCOMPLEXEDITFACTORYWRAPPER_H
#define SBK_QTCOMPLEXEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtComplexEditFactoryWrapper : public QtComplexEditFactory
{
public:
    QtComplexEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtComplexPropertyManager * manager) { QtComplexEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtComplexPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtComplexPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtComplexEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtComplexPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtComplexPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtComplexEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtComplexPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtComplexPropertyManager * manager) { QtComplexEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtComplexPropertyManager * manager) override;
    ~QtComplexEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTCOMPLEXEDITFACTORYWRAPPER_H

