#ifndef SBK_QTSLIDERFACTORYWRAPPER_H
#define SBK_QTSLIDERFACTORYWRAPPER_H

#include <qteditorfactory.h>

class QtSliderFactoryWrapper : public QtSliderFactory
{
public:
    QtSliderFactoryWrapper(QObject * parent = 0);
    inline void connectPropertyManager_protected(QtIntPropertyManager * manager) { QtSliderFactory::connectPropertyManager(manager); }
    void connectPropertyManager(QtIntPropertyManager * manager) override;
    inline QWidget * createAttributeEditor_protected(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) { return QtSliderFactory::createAttributeEditor(manager, property, parent, Attribute(attribute)); }
    QWidget * createAttributeEditor(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent, Attribute attribute) override;
    inline QWidget * createEditor_protected(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent) { return QtSliderFactory::createEditor(manager, property, parent); }
    QWidget * createEditor(QtIntPropertyManager * manager, QtProperty * property, QWidget * parent) override;
    inline void disconnectPropertyManager_protected(QtIntPropertyManager * manager) { QtSliderFactory::disconnectPropertyManager(manager); }
    void disconnectPropertyManager(QtIntPropertyManager * manager) override;
    ~QtSliderFactoryWrapper();
    static void pysideInitQtMetaTypes();
};

#endif // SBK_QTSLIDERFACTORYWRAPPER_H

