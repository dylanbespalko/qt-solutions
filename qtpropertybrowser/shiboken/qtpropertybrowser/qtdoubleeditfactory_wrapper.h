#ifndef SBK_QTDOUBLEEDITFACTORYWRAPPER_H
#define SBK_QTDOUBLEEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtDoubleEditFactoryWrapper : public QtDoubleEditFactory
{
public:
    QtDoubleEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtDoublePropertyManager * manager) { QtDoubleEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtDoublePropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtDoublePropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtDoubleEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtDoublePropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtDoublePropertyManager * manager, QtProperty * property, QWidget * parent) { return QtDoubleEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtDoublePropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtDoublePropertyManager * manager) { QtDoubleEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtDoublePropertyManager * manager) override;
    ~QtDoubleEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTDOUBLEEDITFACTORYWRAPPER_H

