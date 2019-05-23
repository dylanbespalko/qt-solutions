#ifndef SBK_QTGROUPEDITORFACTORYWRAPPER_H
#define SBK_QTGROUPEDITORFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtGroupEditorFactoryWrapper : public QtGroupEditorFactory
{
public:
    QtGroupEditorFactoryWrapper(QObject * parent = nullptr);
    inline void connectPropertyManager_protected(QtGroupPropertyManager * manager) { QtGroupEditorFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtGroupPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtGroupPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtGroupEditorFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtGroupPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtGroupPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtGroupEditorFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtGroupPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtGroupPropertyManager * manager) { QtGroupEditorFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtGroupPropertyManager * manager) override;
    ~QtGroupEditorFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTGROUPEDITORFACTORYWRAPPER_H

