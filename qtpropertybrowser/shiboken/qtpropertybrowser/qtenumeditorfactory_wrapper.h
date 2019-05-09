#ifndef SBK_QTENUMEDITORFACTORYWRAPPER_H
#define SBK_QTENUMEDITORFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtEnumEditorFactoryWrapper : public QtEnumEditorFactory
{
public:
    QtEnumEditorFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtEnumPropertyManager * manager) { QtEnumEditorFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtEnumPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtEnumPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtEnumEditorFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtEnumPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtEnumPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtEnumEditorFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtEnumPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtEnumPropertyManager * manager) { QtEnumEditorFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtEnumPropertyManager * manager) override;
    ~QtEnumEditorFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTENUMEDITORFACTORYWRAPPER_H

