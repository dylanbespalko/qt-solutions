#ifndef SBK_QTGROUPEDITORFACTORYWRAPPER_H
#define SBK_QTGROUPEDITORFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtGroupEditorFactoryWrapper : public QtGroupEditorFactory
{
public:
    QtGroupEditorFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtAbstractPropertyManager * manager) { QtGroupEditorFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtAbstractPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtGroupEditorFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtGroupEditorFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtAbstractPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtAbstractPropertyManager * manager) { QtGroupEditorFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtAbstractPropertyManager * manager) override;
    ~QtGroupEditorFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTGROUPEDITORFACTORYWRAPPER_H

