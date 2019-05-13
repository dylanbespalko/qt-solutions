#ifndef SBK_QTDATETIMEEDITFACTORYWRAPPER_H
#define SBK_QTDATETIMEEDITFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtDateTimeEditFactoryWrapper : public QtDateTimeEditFactory
{
public:
    QtDateTimeEditFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtDateTimePropertyManager * manager) { QtDateTimeEditFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtDateTimePropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtDateTimePropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtDateTimeEditFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtDateTimePropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtDateTimePropertyManager * manager, QtProperty * property, QWidget * parent) { return QtDateTimeEditFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtDateTimePropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtDateTimePropertyManager * manager) { QtDateTimeEditFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtDateTimePropertyManager * manager) override;
    ~QtDateTimeEditFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTDATETIMEEDITFACTORYWRAPPER_H
