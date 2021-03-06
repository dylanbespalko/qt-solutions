#ifndef SBK_QTDATEEDITFACTORYWRAPPER_H
#define SBK_QTDATEEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtDateEditFactoryWrapper : public QtDateEditFactory
{
public:
    QtDateEditFactoryWrapper(QObject * parent = nullptr);
    inline void connectPropertyManager_protected(QtDatePropertyManager * manager) { QtDateEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtDatePropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtDatePropertyManager * manager, QtProperty * property, QWidget * parent, BrowserCol attribute) { return QtDateEditFactory::createAttributeEditor(manager, property, parent, BrowserCol(attribute)); }
    QWidget * createAttributeEditor(QtDatePropertyManager * manager, QtProperty * property, QWidget * parent, BrowserCol attribute) override;
    inline QWidget * createEditor_protected(QtDatePropertyManager * manager, QtProperty * property, QWidget * parent) { return QtDateEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtDatePropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtDatePropertyManager * manager) { QtDateEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtDatePropertyManager * manager) override;
    ~QtDateEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTDATEEDITFACTORYWRAPPER_H

