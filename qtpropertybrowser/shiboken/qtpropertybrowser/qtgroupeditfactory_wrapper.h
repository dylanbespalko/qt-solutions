#ifndef SBK_QTGROUPEDITFACTORYWRAPPER_H
#define SBK_QTGROUPEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtGroupEditFactoryWrapper : public QtGroupEditFactory
{
public:
    QtGroupEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtAbstractPropertyManager * manager) { QtGroupEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtAbstractPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtGroupEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtGroupEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtAbstractPropertyManager * manager) { QtGroupEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtAbstractPropertyManager * manager) override;
    ~QtGroupEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTGROUPEDITFACTORYWRAPPER_H

