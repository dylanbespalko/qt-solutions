#ifndef SBK_QTCURSOREDITORFACTORYWRAPPER_H
#define SBK_QTCURSOREDITORFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtCursorEditorFactoryWrapper : public QtCursorEditorFactory
{
public:
    QtCursorEditorFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtCursorPropertyManager * manager) { QtCursorEditorFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtCursorPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtCursorPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtCursorEditorFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtCursorPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtCursorPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtCursorEditorFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtCursorPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtCursorPropertyManager * manager) { QtCursorEditorFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtCursorPropertyManager * manager) override;
    ~QtCursorEditorFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTCURSOREDITORFACTORYWRAPPER_H
