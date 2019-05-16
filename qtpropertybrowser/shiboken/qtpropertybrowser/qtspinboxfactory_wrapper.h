#ifndef SBK_QTSPINBOXFACTORYWRAPPER_H
#define SBK_QTSPINBOXFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtSpinBoxFactoryWrapper : public QtSpinBoxFactory
{
public:
    QtSpinBoxFactoryWrapper(QObject * parent = nullptr);
    inline void connectPropertyManager_protected(QtIntPropertyManager * manager) { QtSpinBoxFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtIntPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtSpinBoxFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtSpinBoxFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtIntPropertyManager * manager) { QtSpinBoxFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtIntPropertyManager * manager) override;
    ~QtSpinBoxFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTSPINBOXFACTORYWRAPPER_H

