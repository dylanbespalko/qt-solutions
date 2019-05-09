#ifndef SBK_QTINTEDITFACTORYWRAPPER_H
#define SBK_QTINTEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtIntEditFactoryWrapper : public QtIntEditFactory
{
public:
    QtIntEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtIntPropertyManager * manager) { QtIntEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtIntPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtIntEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtIntEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtIntPropertyManager * manager) { QtIntEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtIntPropertyManager * manager) override;
    ~QtIntEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTINTEDITFACTORYWRAPPER_H

