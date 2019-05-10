#ifndef SBK_QTARRAYEDITFACTORYWRAPPER_H
#define SBK_QTARRAYEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtArrayEditFactoryWrapper : public QtArrayEditFactory
{
public:
    QtArrayEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtComplexArrayPropertyManager * manager) { QtArrayEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtComplexArrayPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtComplexArrayPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtArrayEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtComplexArrayPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtComplexArrayPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtArrayEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtComplexArrayPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtComplexArrayPropertyManager * manager) { QtArrayEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtComplexArrayPropertyManager * manager) override;
    ~QtArrayEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTARRAYEDITFACTORYWRAPPER_H

