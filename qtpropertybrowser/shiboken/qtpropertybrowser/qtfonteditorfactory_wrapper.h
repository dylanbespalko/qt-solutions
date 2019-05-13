#ifndef SBK_QTFONTEDITORFACTORYWRAPPER_H
#define SBK_QTFONTEDITORFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtFontEditorFactoryWrapper : public QtFontEditorFactory
{
public:
    QtFontEditorFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtFontPropertyManager * manager) { QtFontEditorFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtFontPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtFontPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtFontEditorFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtFontPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtFontPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtFontEditorFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtFontPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtFontPropertyManager * manager) { QtFontEditorFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtFontPropertyManager * manager) override;
    ~QtFontEditorFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTFONTEDITORFACTORYWRAPPER_H
