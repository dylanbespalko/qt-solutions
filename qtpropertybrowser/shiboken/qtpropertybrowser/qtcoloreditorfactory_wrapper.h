#ifndef SBK_QTCOLOREDITORFACTORYWRAPPER_H
#define SBK_QTCOLOREDITORFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtColorEditorFactoryWrapper : public QtColorEditorFactory
{
public:
    QtColorEditorFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtColorPropertyManager * manager) { QtColorEditorFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtColorPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtColorPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtColorEditorFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtColorPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtColorPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtColorEditorFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtColorPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtColorPropertyManager * manager) { QtColorEditorFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtColorPropertyManager * manager) override;
    ~QtColorEditorFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTCOLOREDITORFACTORYWRAPPER_H

