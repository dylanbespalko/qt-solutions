#ifndef SBK_QTLINEEDITFACTORYWRAPPER_H
#define SBK_QTLINEEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtLineEditFactoryWrapper : public QtLineEditFactory
{
public:
    QtLineEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtStringPropertyManager * manager) { QtLineEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtStringPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtStringPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtLineEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtStringPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtStringPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtLineEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtStringPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtStringPropertyManager * manager) { QtLineEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtStringPropertyManager * manager) override;
    ~QtLineEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTLINEEDITFACTORYWRAPPER_H

