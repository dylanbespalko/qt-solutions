/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Solutions component.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qteditorfactory.h"

#include <QSpinBox>
#include <QScrollBar>
#include <QComboBox>
#include <QAbstractItemView>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QMenu>
#include <QKeyEvent>
#include <QApplication>
#include <QLabel>
#include <QToolButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QSpacerItem>
#include <QStyleOption>
#include <QPainter>
#include <QMap>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif

#if QT_VERSION >= 0x040400
QT_BEGIN_NAMESPACE
#endif

// Set a hard coded left margin to account for the indentation
// of the tree view icon when switching to an editor

static inline void setupTreeViewEditorMargin(QLayout *lt)
{
    enum { DecorationMargin = 4 };
    if (QApplication::layoutDirection() == Qt::LeftToRight)
        lt->setContentsMargins(DecorationMargin, 0, 0, 0);
    else
        lt->setContentsMargins(0, 0, DecorationMargin, 0);
}

// ---------- EditorFactoryPrivate :
// Base class for editor factory private classes. Manages mapping of properties to editors and vice versa.

template <class Editor>
class EditorFactoryPrivate
{
public:

    typedef QList<Editor *> EditorList;
    typedef QMap<QtProperty *, EditorList> PropertyToEditorListMap;
    typedef QMap<Editor *, QtProperty *> EditorToPropertyMap;
    typedef QList<QComboBox *> UnitAttributeEditorList;
    typedef QList<QComboBox *> PkAvgAttributeEditorList;
    typedef QList<QComboBox *> FormatAttributeEditorList;
    typedef QList<QDoubleEdit *> MinimumAttributeEditorList;
    typedef QList<QDoubleEdit *> MaximumAttributeEditorList;
    typedef QList<QtBoolEdit *> CheckAttributeEditorList;
    typedef QMap<QtProperty *, UnitAttributeEditorList> PropertyToUnitAttributeEditorListMap;
    typedef QMap<QtProperty *, PkAvgAttributeEditorList> PropertyToPkAvgAttributeEditorListMap;
    typedef QMap<QtProperty *, FormatAttributeEditorList> PropertyToFormatAttributeEditorListMap;
    typedef QMap<QtProperty *, MinimumAttributeEditorList> PropertyToMinimumAttributeEditorListMap;
    typedef QMap<QtProperty *, MaximumAttributeEditorList> PropertyToMaximumAttributeEditorListMap;
    typedef QMap<QtProperty *, CheckAttributeEditorList> PropertyToCheckAttributeEditorListMap;
    typedef QMap<QComboBox *, QtProperty *> UnitAttributeEditorToPropertyMap;
    typedef QMap<QComboBox *, QtProperty *> PkAvgAttributeEditorToPropertyMap;
    typedef QMap<QComboBox *, QtProperty *> FormatAttributeEditorToPropertyMap;
    typedef QMap<QDoubleEdit *, QtProperty *> MinimumAttributeEditorToPropertyMap;
    typedef QMap<QDoubleEdit *, QtProperty *> MaximumAttributeEditorToPropertyMap;
    typedef QMap<QtBoolEdit *, QtProperty *> CheckAttributeEditorToPropertyMap;

    Editor *createEditor(QtProperty *property, QWidget *parent);
    QComboBox *createUnitAttributeEditor(QtProperty *property, QWidget *parent);
    QComboBox *createPkAvgAttributeEditor(QtProperty *property, QWidget *parent);
    QComboBox *createFormatAttributeEditor(QtProperty *property, QWidget *parent);
    QDoubleEdit *createMinimumAttributeEditor(QtProperty *property, QWidget *parent);
    QDoubleEdit *createMaximumAttributeEditor(QtProperty *property, QWidget *parent);
    QtBoolEdit *createCheckAttributeEditor(QtProperty *property, QWidget *parent);
    void initializeEditor(QtProperty *property, Editor *e);
    void initializeUnitAttributeEditor(QtProperty *property, QComboBox *e);
    void initializePkAvgAttributeEditor(QtProperty *property, QComboBox *e);
    void initializeFormatAttributeEditor(QtProperty *property, QComboBox *e);
    void initializeMinimumAttributeEditor(QtProperty *property, QDoubleEdit *e);
    void initializeMaximumAttributeEditor(QtProperty *property, QDoubleEdit *e);
    void initializeCheckAttributeEditor(QtProperty *property, QtBoolEdit *e);
    void slotEditorDestroyed(QObject *object);
    void slotUnitAttributeEditorDestroyed(QObject *object);
    void slotPkAvgAttributeEditorDestroyed(QObject *object);
    void slotFormatAttributeEditorDestroyed(QObject *object);
    void slotMinimumAttributeEditorDestroyed(QObject *object);
    void slotMaximumAttributeEditorDestroyed(QObject *object);
    void slotCheckAttributeEditorDestroyed(QObject *object);

    PropertyToEditorListMap  m_createdEditors;
    EditorToPropertyMap m_editorToProperty;
    PropertyToUnitAttributeEditorListMap m_createdUnitAttributeEditors;
    PropertyToPkAvgAttributeEditorListMap m_createdPkAvgAttributeEditors;
    PropertyToFormatAttributeEditorListMap m_createdFormatAttributeEditors;
    PropertyToMinimumAttributeEditorListMap m_createdMinimumAttributeEditors;
    PropertyToMaximumAttributeEditorListMap m_createdMaximumAttributeEditors;
    PropertyToCheckAttributeEditorListMap m_createdCheckAttributeEditors;
    UnitAttributeEditorToPropertyMap m_unitAttributeEditorToProperty;
    PkAvgAttributeEditorToPropertyMap m_pkAvgAttributeEditorToProperty;
    FormatAttributeEditorToPropertyMap m_formatAttributeEditorToProperty;
    MinimumAttributeEditorToPropertyMap m_minimumAttributeEditorToProperty;
    MaximumAttributeEditorToPropertyMap m_maximumAttributeEditorToProperty;
    CheckAttributeEditorToPropertyMap m_checkAttributeEditorToProperty;
};

template <class Editor>
Editor *EditorFactoryPrivate<Editor>::createEditor(QtProperty *property, QWidget *parent)
{
    Editor *editor = new Editor(parent);
    initializeEditor(property, editor);
    return editor;
}

template <class Editor>
QComboBox *EditorFactoryPrivate<Editor>::createUnitAttributeEditor(QtProperty *property, QWidget *parent)
{
    QComboBox *editor = new QComboBox(parent);
    initializeUnitAttributeEditor(property, editor);
    return editor;
}

template <class Editor>
QComboBox *EditorFactoryPrivate<Editor>::createPkAvgAttributeEditor(QtProperty *property, QWidget *parent)
{
    QComboBox *editor = new QComboBox(parent);
    initializePkAvgAttributeEditor(property, editor);
    return editor;
}

template <class Editor>
QComboBox *EditorFactoryPrivate<Editor>::createFormatAttributeEditor(QtProperty *property, QWidget *parent)
{
    QComboBox *editor = new QComboBox(parent);
    initializeFormatAttributeEditor(property, editor);
    return editor;
}

template <class Editor>
QDoubleEdit *EditorFactoryPrivate<Editor>::createMinimumAttributeEditor(QtProperty *property, QWidget *parent)
{
    QDoubleEdit *editor = new QDoubleEdit(parent);
    initializeMinimumAttributeEditor(property, editor);
    return editor;
}

template <class Editor>
QDoubleEdit *EditorFactoryPrivate<Editor>::createMaximumAttributeEditor(QtProperty *property, QWidget *parent)
{
    QDoubleEdit *editor = new QDoubleEdit(parent);
    initializeMaximumAttributeEditor(property, editor);
    return editor;
}

template <class Editor>
QtBoolEdit *EditorFactoryPrivate<Editor>::createCheckAttributeEditor(QtProperty *property, QWidget *parent)
{
    QtBoolEdit *editor = new QtBoolEdit(parent);
    initializeCheckAttributeEditor(property, editor);
    return editor;
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeEditor(QtProperty *property, Editor *editor)
{
    typename PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        it = m_createdEditors.insert(property, EditorList());
    it.value().append(editor);
    m_editorToProperty.insert(editor, property);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeUnitAttributeEditor(QtProperty *property, QComboBox *editor)
{
    typename PropertyToUnitAttributeEditorListMap::iterator it = m_createdUnitAttributeEditors.find(property);
    if (it == m_createdUnitAttributeEditors.end())
        it = m_createdUnitAttributeEditors.insert(property, UnitAttributeEditorList());
    it.value().append(editor);
    m_unitAttributeEditorToProperty.insert(editor, property);

    editor->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    editor->setMinimumContentsLength(1);
    editor->view()->setTextElideMode(Qt::ElideRight);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializePkAvgAttributeEditor(QtProperty *property, QComboBox *editor)
{
    typename PropertyToPkAvgAttributeEditorListMap::iterator it = m_createdPkAvgAttributeEditors.find(property);
    if (it == m_createdPkAvgAttributeEditors.end())
        it = m_createdPkAvgAttributeEditors.insert(property, PkAvgAttributeEditorList());
    it.value().append(editor);
    m_pkAvgAttributeEditorToProperty.insert(editor, property);

    editor->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    editor->setMinimumContentsLength(1);
    editor->view()->setTextElideMode(Qt::ElideRight);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeFormatAttributeEditor(QtProperty *property, QComboBox *editor)
{
    typename PropertyToFormatAttributeEditorListMap::iterator it = m_createdFormatAttributeEditors.find(property);
    if (it == m_createdFormatAttributeEditors.end())
        it = m_createdFormatAttributeEditors.insert(property, FormatAttributeEditorList());
    it.value().append(editor);
    m_formatAttributeEditorToProperty.insert(editor, property);

    editor->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    editor->setMinimumContentsLength(1);
    editor->view()->setTextElideMode(Qt::ElideRight);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeMinimumAttributeEditor(QtProperty *property, QDoubleEdit *editor)
{
    typename PropertyToMinimumAttributeEditorListMap::iterator it = m_createdMinimumAttributeEditors.find(property);
    if (it == m_createdMinimumAttributeEditors.end())
        it = m_createdMinimumAttributeEditors.insert(property, MinimumAttributeEditorList());
    it.value().append(editor);
    m_minimumAttributeEditorToProperty.insert(editor, property);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeMaximumAttributeEditor(QtProperty *property, QDoubleEdit *editor)
{
    typename PropertyToMaximumAttributeEditorListMap::iterator it = m_createdMaximumAttributeEditors.find(property);
    if (it == m_createdMaximumAttributeEditors.end())
        it = m_createdMaximumAttributeEditors.insert(property, MaximumAttributeEditorList());
    it.value().append(editor);
    m_maximumAttributeEditorToProperty.insert(editor, property);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::initializeCheckAttributeEditor(QtProperty *property, QtBoolEdit *editor)
{
    typename PropertyToCheckAttributeEditorListMap::iterator it = m_createdCheckAttributeEditors.find(property);
    if (it == m_createdCheckAttributeEditors.end())
        it = m_createdCheckAttributeEditors.insert(property, CheckAttributeEditorList());
    it.value().append(editor);
    m_checkAttributeEditorToProperty.insert(editor, property);
    editor->setTextVisible(false);
}

template <class Manager>
void updateUnit(Manager *manager, QtProperty *property, QComboBox * editor)
{
    QString prefix;
    QString unit = manager->unit(property);
    QStringList enumNames;
    manager->format(property) == LOG_DEG? prefix = "dB" : "";
    QMap<Scale, QString>::iterator i;
    for (i = ScaleNameMap.begin(); i != ScaleNameMap.end(); ++i) {
        enumNames << prefix + i.value() + unit;
    }

    editor->blockSignals(true);
    editor->clear();
    editor->addItems(enumNames);
    editor->setCurrentIndex(static_cast<int>(manager->scale(property)));
    editor->blockSignals(false);
}

template <class Manager>
void updatePkAvg(Manager *manager, QtProperty *property, QComboBox * editor)
{
    QStringList enumNames = PkAvgNameMap.values();

    editor->blockSignals(true);
    editor->clear();
    editor->addItems(enumNames);
    editor->setCurrentIndex(static_cast<int>(manager->pkAvg(property)));
    editor->blockSignals(false);
}

template <class Manager>
void updateFormat(Manager *manager, QtProperty *property, QComboBox * editor)
{
    QStringList enumNames = FormatNameMap.values();

    editor->blockSignals(true);
    editor->clear();
    editor->addItems(enumNames);
    editor->setCurrentIndex(static_cast<int>(manager->format(property)));
    editor->blockSignals(false);
}

template <class Manager>
void updateMinimum(Manager *manager, QtProperty *property, QDoubleEdit *editor)
{
    editor->blockSignals(true);
    editor->setScale(manager->scale(property));
    editor->setFormat(manager->format(property));
    editor->setPrecision(manager->precision(property));
    editor->setRange(lowest, highest);
    editor->setValue(manager->minimum(property));
    editor->blockSignals(false);
}

void updateMinimum(QtIntPropertyManager *manager, QtProperty *property, QDoubleEdit *editor)
{
    editor->blockSignals(true);
    editor->setPrecision(manager->precision(property));
    editor->setRange(lowest, highest);
    editor->setValue(manager->minimum(property));
    editor->blockSignals(false);
}

template <class Manager>
void updateMaximum(Manager *manager, QtProperty *property, QDoubleEdit *editor)
{
    editor->blockSignals(true);
    editor->setScale(manager->scale(property));
    editor->setFormat(manager->format(property));
    editor->setPrecision(manager->precision(property));
    editor->setRange(lowest, highest);
    editor->setValue(manager->maximum(property));
    editor->blockSignals(false);
}

void updateMaximum(QtIntPropertyManager *manager, QtProperty *property, QDoubleEdit *editor)
{
    editor->blockSignals(true);
    editor->setPrecision(manager->precision(property));
    editor->setRange(lowest, highest);
    editor->setValue(manager->maximum(property));
    editor->blockSignals(false);
}

template <class Manager>
void updateCheck(Manager *manager, QtProperty *property, QtBoolEdit *editor)
{
    Q_UNUSED(manager);
    editor->blockSignals(true);
    editor->setChecked(manager->check(property));
    editor->blockSignals(false);
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotEditorDestroyed(QObject *object)
{
    const typename EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
    for (typename EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            Editor *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
            if (pit != m_createdEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdEditors.erase(pit);
            }
            m_editorToProperty.erase(itEditor);
            return;
        }
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotUnitAttributeEditorDestroyed(QObject *object)
{
    const typename UnitAttributeEditorToPropertyMap::iterator ecend = m_unitAttributeEditorToProperty.end();
    for (typename UnitAttributeEditorToPropertyMap::iterator itEditor = m_unitAttributeEditorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QComboBox *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToUnitAttributeEditorListMap::iterator pit = m_createdUnitAttributeEditors.find(property);
            if (pit != m_createdUnitAttributeEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdUnitAttributeEditors.erase(pit);
            }
            m_unitAttributeEditorToProperty.erase(itEditor);
            return;
        }
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotPkAvgAttributeEditorDestroyed(QObject *object)
{
    const typename PkAvgAttributeEditorToPropertyMap::iterator ecend = m_pkAvgAttributeEditorToProperty.end();
    for (typename PkAvgAttributeEditorToPropertyMap::iterator itEditor = m_pkAvgAttributeEditorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QComboBox *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToPkAvgAttributeEditorListMap::iterator pit = m_createdPkAvgAttributeEditors.find(property);
            if (pit != m_createdPkAvgAttributeEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdPkAvgAttributeEditors.erase(pit);
            }
            m_pkAvgAttributeEditorToProperty.erase(itEditor);
            return;
        }
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotFormatAttributeEditorDestroyed(QObject *object)
{
    const typename FormatAttributeEditorToPropertyMap::iterator ecend = m_formatAttributeEditorToProperty.end();
    for (typename FormatAttributeEditorToPropertyMap::iterator itEditor = m_formatAttributeEditorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QComboBox *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToFormatAttributeEditorListMap::iterator pit = m_createdFormatAttributeEditors.find(property);
            if (pit != m_createdFormatAttributeEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdFormatAttributeEditors.erase(pit);
            }
            m_formatAttributeEditorToProperty.erase(itEditor);
            return;
        }
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotMinimumAttributeEditorDestroyed(QObject *object)
{
    const typename MinimumAttributeEditorToPropertyMap::iterator ecend = m_minimumAttributeEditorToProperty.end();
    for (typename MinimumAttributeEditorToPropertyMap::iterator itEditor = m_minimumAttributeEditorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QDoubleEdit *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToMinimumAttributeEditorListMap::iterator pit = m_createdMinimumAttributeEditors.find(property);
            if (pit != m_createdMinimumAttributeEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdMinimumAttributeEditors.erase(pit);
            }
            m_minimumAttributeEditorToProperty.erase(itEditor);
            return;
        }
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotMaximumAttributeEditorDestroyed(QObject *object)
{
    const typename MaximumAttributeEditorToPropertyMap::iterator ecend = m_maximumAttributeEditorToProperty.end();
    for (typename MaximumAttributeEditorToPropertyMap::iterator itEditor = m_maximumAttributeEditorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QDoubleEdit *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToMaximumAttributeEditorListMap::iterator pit = m_createdMaximumAttributeEditors.find(property);
            if (pit != m_createdMaximumAttributeEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdMaximumAttributeEditors.erase(pit);
            }
            m_maximumAttributeEditorToProperty.erase(itEditor);
            return;
        }
    }
}

template <class Editor>
void EditorFactoryPrivate<Editor>::slotCheckAttributeEditorDestroyed(QObject *object)
{
    const typename CheckAttributeEditorToPropertyMap::iterator ecend = m_checkAttributeEditorToProperty.end();
    for (typename CheckAttributeEditorToPropertyMap::iterator itEditor = m_checkAttributeEditorToProperty.begin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QtBoolEdit *editor = itEditor.key();
            QtProperty *property = itEditor.value();
            const typename PropertyToCheckAttributeEditorListMap::iterator pit = m_createdCheckAttributeEditors.find(property);
            if (pit != m_createdCheckAttributeEditors.end()) {
                pit.value().removeAll(editor);
                if (pit.value().empty())
                    m_createdCheckAttributeEditors.erase(pit);
            }
            m_checkAttributeEditorToProperty.erase(itEditor);
            return;
        }
    }
}

// QtGroupEditorFactory

class QtGroupEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtGroupEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtGroupEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtGroupEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtGroupPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtGroupEditorFactory

 \brief The QtGroupEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtGroupEditorFactory::QtGroupEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtGroupPropertyManager>(parent)
{
    d_ptr = new QtGroupEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtGroupEditorFactory::~QtGroupEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtGroupEditorFactory::connectPropertyManager(QtGroupPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtGroupEditorFactory::createEditor(QtGroupPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtGroupEditorFactory::createAttributeEditor(QtGroupPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtGroupEditorFactory::disconnectPropertyManager(QtGroupPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// ------------ QtSpinBoxFactory

class QtSpinBoxFactoryPrivate : public EditorFactoryPrivate<QSpinBox>
{
    QtSpinBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtSpinBoxFactory)
public:

    void slotPropertyChanged(QtProperty *property, int value);
    void slotRangeChanged(QtProperty *property, int min, int max);
    void slotSingleStepChanged(QtProperty *property, int step);
    void slotReadOnlyChanged(QtProperty *property, bool readOnly);
    void slotSetValue(int value);
    void slotSetMinimum(int minVal);
    void slotSetMaximum(int maxVal);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtSpinBoxFactoryPrivate::slotPropertyChanged(QtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;
    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        if (editor->value() != value) {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtSpinBoxFactoryPrivate::slotRangeChanged(QtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtSpinBoxFactoryPrivate::slotSingleStepChanged(QtProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QtSpinBoxFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtSpinBoxFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QSpinBox *, QtProperty *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (QMap<QSpinBox *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor !=  ecend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

void QtSpinBoxFactoryPrivate::slotSetMinimum(double minVal)
{
    slotSetMinimum(int(minVal));
}

void QtSpinBoxFactoryPrivate::slotSetMinimum(int minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtSpinBoxFactoryPrivate::slotSetMaximum(double maxVal)
{
    slotSetMaximum(int(maxVal));
}

void QtSpinBoxFactoryPrivate::slotSetMaximum(int maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtSpinBoxFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtSpinBoxFactory

    \brief The QtSpinBoxFactory class provides QSpinBox widgets for
    properties created by QtIntPropertyManager objects.

    \sa QtAbstractEditorFactory, QtIntPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtSpinBoxFactory::QtSpinBoxFactory(QObject *parent)
    : QtAbstractEditorFactory<QtIntPropertyManager>(parent)
{
    d_ptr = new QtSpinBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtSpinBoxFactory::~QtSpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtSpinBoxFactory::connectPropertyManager(QtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
                this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QtProperty *, int)),
                this, SLOT(slotSingleStepChanged(QtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
                this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtSpinBoxFactory::createEditor(QtIntPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QSpinBox *editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSpinBoxFactory::createAttributeEditor(QtIntPropertyManager *manager, QtProperty *property,
                                                 QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}
/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtSpinBoxFactory::disconnectPropertyManager(QtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
                this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QtProperty *, int)),
                this, SLOT(slotSingleStepChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
                this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}


// QtIntEditFactory

class QtIntEditFactoryPrivate : public EditorFactoryPrivate<QIntEdit>{
    QtIntEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtIntEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, int value);
    void slotRangeChanged(QtProperty *property, int min, int max);
    void slotRangeChanged(QtProperty *property, double min, double max);
    void slotPrecisionChanged(QtProperty *property, int prec);
    void slotReadOnlyChanged(QtProperty *property, bool readOnly);
    void slotSetValue(int value);
    void slotSetMinimum(int minVal);
    void slotSetMaximum(int maxVal);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtIntEditFactoryPrivate::slotPropertyChanged(QtProperty *property, int value)
{
    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    QList<QIntEdit *> editors = m_createdEditors[property];
    QListIterator<QIntEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QIntEdit *editor = itEditor.next();
        if (editor->value() != value) {
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtIntEditFactoryPrivate::slotRangeChanged(QtProperty *property, double min, double max)
{
    slotRangeChanged(property, int(min), int(max));
}

void QtIntEditFactoryPrivate::slotRangeChanged(QtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QIntEdit *> editors = m_createdEditors[property];
    QListIterator<QIntEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        QIntEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtIntEditFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QIntEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QIntEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtIntEditFactoryPrivate::slotPrecisionChanged(QtProperty *property, int prec)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QIntEdit *> editors = m_createdEditors[property];
    QListIterator<QIntEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        QIntEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setPrecision(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtIntEditFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QIntEdit *, QtProperty *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (QMap<QIntEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

void QtIntEditFactoryPrivate::slotSetMinimum(double minVal)
{
    slotSetMinimum(int(minVal));
}

void QtIntEditFactoryPrivate::slotSetMinimum(int minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtIntEditFactoryPrivate::slotSetMaximum(double maxVal)
{
    slotSetMaximum(int(maxVal));
}

void QtIntEditFactoryPrivate::slotSetMaximum(int maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtIntEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}
/*! \class QtIntEditFactory

 \brief The QtIntEditFactory class provides QComplexEdit
 widgets for properties created by QtDoublePropertyManager objects.

 \sa QtAbstractEditorFactory, QtDoublePropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtIntEditFactory::QtIntEditFactory(QObject *parent)
: QtAbstractEditorFactory<QtIntPropertyManager>(parent)
{
    d_ptr = new QtIntEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtIntEditFactory::~QtIntEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtIntEditFactory::connectPropertyManager(QtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, int)),
            this, SLOT(slotPropertyChanged(QtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
            this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    connect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtIntEditFactory::createEditor(QtIntPropertyManager *manager, QtProperty *property, QWidget *parent)
{
    QIntEdit *editor = d_ptr->createEditor(property, parent);
    //editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    //editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtIntEditFactory::createAttributeEditor(QtIntPropertyManager *manager, QtProperty *property,
                                                 QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtIntEditFactory::disconnectPropertyManager(QtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, int)),
               this, SLOT(slotPropertyChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
               this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

// QtSliderFactory

class QtSliderFactoryPrivate : public EditorFactoryPrivate<QSlider>
{
    QtSliderFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtSliderFactory)
public:
    void slotPropertyChanged(QtProperty *property, int value);
    void slotRangeChanged(QtProperty *property, int min, int max);
    void slotSingleStepChanged(QtProperty *property, int step);
    void slotSetValue(int value);
    void slotSetMinimum(int minVal);
    void slotSetMaximum(int maxVal);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtSliderFactoryPrivate::slotPropertyChanged(QtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;
    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtSliderFactoryPrivate::slotRangeChanged(QtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtSliderFactoryPrivate::slotSingleStepChanged(QtProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QSlider *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QSlider *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QtSliderFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QSlider *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QSlider *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor ) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

void QtSliderFactoryPrivate::slotSetMinimum(double minVal)
{
    slotSetMinimum(int(minVal));
}

void QtSliderFactoryPrivate::slotSetMinimum(int minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtSliderFactoryPrivate::slotSetMaximum(double maxVal)
{
    slotSetMaximum(int(maxVal));
}

void QtSliderFactoryPrivate::slotSetMaximum(int maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtSliderFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtSliderFactory

    \brief The QtSliderFactory class provides QSlider widgets for
    properties created by QtIntPropertyManager objects.

    \sa QtAbstractEditorFactory, QtIntPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtSliderFactory::QtSliderFactory(QObject *parent)
    : QtAbstractEditorFactory<QtIntPropertyManager>(parent)
{
    d_ptr = new QtSliderFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtSliderFactory::~QtSliderFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtSliderFactory::connectPropertyManager(QtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
                this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QtProperty *, int)),
                this, SLOT(slotSingleStepChanged(QtProperty *, int)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtSliderFactory::createEditor(QtIntPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QSlider *editor = new QSlider(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSliderFactory::createAttributeEditor(QtIntPropertyManager *manager, QtProperty *property,
                                                QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtSliderFactory::disconnectPropertyManager(QtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
                this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QtProperty *, int)),
                this, SLOT(slotSingleStepChanged(QtProperty *, int)));
}

// QtSliderFactory

class QtScrollBarFactoryPrivate : public  EditorFactoryPrivate<QScrollBar>
{
    QtScrollBarFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtScrollBarFactory)
public:
    void slotPropertyChanged(QtProperty *property, int value);
    void slotRangeChanged(QtProperty *property, int min, int max);
    void slotSingleStepChanged(QtProperty *property, int step);
    void slotSetValue(int value);
    void slotSetMinimum(int minVal);
    void slotSetMaximum(int maxVal);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtScrollBarFactoryPrivate::slotPropertyChanged(QtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QScrollBar *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtScrollBarFactoryPrivate::slotRangeChanged(QtProperty *property, int min, int max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtIntPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QScrollBar *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtScrollBarFactoryPrivate::slotSingleStepChanged(QtProperty *property, int step)
{
    if (!m_createdEditors.contains(property))
        return;
    QListIterator<QScrollBar *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QScrollBar *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QtScrollBarFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const QMap<QScrollBar *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QScrollBar *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtScrollBarFactoryPrivate::slotSetMinimum(double minVal)
{
    slotSetMinimum(int(minVal));
}

void QtScrollBarFactoryPrivate::slotSetMinimum(int minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtScrollBarFactoryPrivate::slotSetMaximum(double maxVal)
{
    slotSetMaximum(int(maxVal));
}

void QtScrollBarFactoryPrivate::slotSetMaximum(int maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtScrollBarFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtIntPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtScrollBarFactory

    \brief The QtScrollBarFactory class provides QScrollBar widgets for
    properties created by QtIntPropertyManager objects.

    \sa QtAbstractEditorFactory, QtIntPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtScrollBarFactory::QtScrollBarFactory(QObject *parent)
    : QtAbstractEditorFactory<QtIntPropertyManager>(parent)
{
    d_ptr = new QtScrollBarFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtScrollBarFactory::~QtScrollBarFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtScrollBarFactory::connectPropertyManager(QtIntPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
                this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    connect(manager, SIGNAL(singleStepChanged(QtProperty *, int)),
                this, SLOT(slotSingleStepChanged(QtProperty *, int)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtScrollBarFactory::createEditor(QtIntPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QScrollBar *editor = new QScrollBar(Qt::Horizontal, parent);
    d_ptr->initializeEditor(property, editor);
    editor->setSingleStep(manager->singleStep(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtScrollBarFactory::createAttributeEditor(QtIntPropertyManager *manager, QtProperty *property,
                                                   QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtScrollBarFactory::disconnectPropertyManager(QtIntPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, int, int)),
                this, SLOT(slotRangeChanged(QtProperty *, int, int)));
    disconnect(manager, SIGNAL(singleStepChanged(QtProperty *, int)),
                this, SLOT(slotSingleStepChanged(QtProperty *, int)));
}

// QtCheckBoxFactory

class QtCheckBoxFactoryPrivate : public EditorFactoryPrivate<QtBoolEdit>
{
    QtCheckBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtCheckBoxFactory)
public:
    void slotPropertyChanged(QtProperty *property, bool value);
    void slotTextVisibleChanged(QtProperty *property, bool textVisible);
    void slotSetValue(bool value);
    void slotSetCheck(bool check);
};

void QtCheckBoxFactoryPrivate::slotPropertyChanged(QtProperty *property, bool value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtBoolPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QtBoolEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QtBoolEdit *editor = itEditor.next();
        editor->blockCheckBoxSignals(true);
        editor->setChecked(value);
        editor->blockCheckBoxSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtCheckBoxFactoryPrivate::slotTextVisibleChanged(QtProperty *property, bool textVisible)
{
    if (!m_createdEditors.contains(property))
        return;

    QtBoolPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QtBoolEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QtBoolEdit *editor = itEditor.next();
        editor->setTextVisible(textVisible);
    }
}

void QtCheckBoxFactoryPrivate::slotSetValue(bool value)
{
    QObject *object = q_ptr->sender();

    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtBoolPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtCheckBoxFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtBoolPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtCheckBoxFactory

    \brief The QtCheckBoxFactory class provides QCheckBox widgets for
    properties created by QtBoolPropertyManager objects.

    \sa QtAbstractEditorFactory, QtBoolPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtCheckBoxFactory::QtCheckBoxFactory(QObject *parent)
    : QtAbstractEditorFactory<QtBoolPropertyManager>(parent)
{
    d_ptr = new QtCheckBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtCheckBoxFactory::~QtCheckBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtCheckBoxFactory::connectPropertyManager(QtBoolPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, bool)),
                this, SLOT(slotPropertyChanged(QtProperty *, bool)));
    connect(manager, SIGNAL(textVisibleChanged(QtProperty *, bool)),
                this, SLOT(slotTextVisibleChanged(QtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtCheckBoxFactory::createEditor(QtBoolPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QtBoolEdit *editor = d_ptr->createEditor(property, parent);
    editor->setChecked(manager->value(property));
    editor->setTextVisible(manager->textVisible(property));

    connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetValue(bool)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtCheckBoxFactory::createAttributeEditor(QtBoolPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtCheckBoxFactory::disconnectPropertyManager(QtBoolPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, bool)),
                this, SLOT(slotPropertyChanged(QtProperty *, bool)));
    disconnect(manager, SIGNAL(textVisibleChanged(QtProperty *, bool)),
                this, SLOT(slotTextVisibleChanged(QtProperty *, bool)));
}

// QtDoubleSpinBoxFactory

class QtDoubleSpinBoxFactoryPrivate : public EditorFactoryPrivate<QDoubleSpinBox>
{
    QtDoubleSpinBoxFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtDoubleSpinBoxFactory)
public:

    void slotPropertyChanged(QtProperty *property, double value);
    void slotRangeChanged(QtProperty *property, double min, double max);
    void slotSingleStepChanged(QtProperty *property, double step);
    void slotPrecisionChanged(QtProperty *property, int prec);
    void slotReadOnlyChanged(QtProperty *property, bool readOnly);
    void slotSetValue(double value);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtDoubleSpinBoxFactoryPrivate::slotPropertyChanged(QtProperty *property, double value)
{
    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        if (!isclose(value, editor->value(), epsilon, epsilon)){
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotRangeChanged(QtProperty *property,
            double min, double max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotSingleStepChanged(QtProperty *property, double step)
{
    if (!m_createdEditors.contains(property))
        return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setSingleStep(step);
        editor->blockSignals(false);
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QDoubleSpinBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotPrecisionChanged(QtProperty *property, int prec)
{
    if (!m_createdEditors.contains(property))
        return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QDoubleSpinBox *> editors = m_createdEditors[property];
    QListIterator<QDoubleSpinBox *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleSpinBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDecimals(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotSetValue(double value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleSpinBox *, QtProperty *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (QMap<QDoubleSpinBox *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotSetMinimum(double minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotSetMaximum(double maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtDoubleSpinBoxFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*! \class QtDoubleSpinBoxFactory

    \brief The QtDoubleSpinBoxFactory class provides QDoubleSpinBox
    widgets for properties created by QtDoublePropertyManager objects.

    \sa QtAbstractEditorFactory, QtDoublePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtDoubleSpinBoxFactory::QtDoubleSpinBoxFactory(QObject *parent)
    : QtAbstractEditorFactory<QtDoublePropertyManager>(parent)
{
    d_ptr = new QtDoubleSpinBoxFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtDoubleSpinBoxFactory::~QtDoubleSpinBoxFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtDoubleSpinBoxFactory::connectPropertyManager(QtDoublePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, double)),
                this, SLOT(slotPropertyChanged(QtProperty *, double)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, double, double)),
                this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    connect(manager, SIGNAL(singleStepChanged(QtProperty *, double)),
                this, SLOT(slotSingleStepChanged(QtProperty *, double)));
    connect(manager, SIGNAL(precisionChanged(QtProperty *, int)),
                this, SLOT(slotPrecisionChanged(QtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
                this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtDoubleSpinBoxFactory::createEditor(QtDoublePropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    QDoubleSpinBox *editor = d_ptr->createEditor(property, parent);
    editor->setSingleStep(manager->singleStep(property));
    editor->setDecimals(manager->precision(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetValue(double)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtDoubleSpinBoxFactory::createAttributeEditor(QtDoublePropertyManager *manager, QtProperty *property,
                                                       QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtDoubleSpinBoxFactory::disconnectPropertyManager(QtDoublePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, double)),
                this, SLOT(slotPropertyChanged(QtProperty *, double)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, double, double)),
                this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    disconnect(manager, SIGNAL(singleStepChanged(QtProperty *, double)),
                this, SLOT(slotSingleStepChanged(QtProperty *, double)));
    disconnect(manager, SIGNAL(precisionChanged(QtProperty *, int)),
                this, SLOT(slotPrecisionChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
                this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

// QtDoubleEditFactory

class QtDoubleEditFactoryPrivate : public EditorFactoryPrivate<QDoubleEdit>
{
    QtDoubleEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtDoubleEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, double value);
    void slotRangeChanged(QtProperty *property, double min, double max);
    void slotPrecisionChanged(QtProperty *property, int prec);
    void slotReadOnlyChanged(QtProperty *property, bool readOnly);
    void slotSetValue(double value);
    void slotSetScale(int scaleSelection);
    void slotSetFormat(int formatSelection);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtDoubleEditFactoryPrivate::slotPropertyChanged(QtProperty *property, double value)
{
    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    QList<QDoubleEdit *> editors = m_createdEditors[property];
    QListIterator<QDoubleEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDoubleEdit *editor = itEditor.next();
        editor->setFormat(manager->format(property));
        editor->setScale(manager->scale(property));
        if (!isclose(value, editor->value(), epsilon, epsilon)){
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
    QList<QComboBox *> unitEditors = m_createdUnitAttributeEditors[property];
    for (unsigned short index = 0; index < unitEditors.size(); ++index ){
        updateUnit(manager, property, unitEditors[index]);
    }
    QList<QComboBox *> formatEditors = m_createdFormatAttributeEditors[property];
    for (unsigned short index = 0; index < formatEditors.size(); ++index ){
        updateFormat(manager, property, formatEditors[index]);
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtDoubleEditFactoryPrivate::slotRangeChanged(QtProperty *property, double min, double max)
{
    if (!m_createdEditors.contains(property))
    return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    return;

    QList<QDoubleEdit *> editors = m_createdEditors[property];
    QListIterator<QDoubleEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtDoubleEditFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
    return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    return;

    QListIterator<QDoubleEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDoubleEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtDoubleEditFactoryPrivate::slotPrecisionChanged(QtProperty *property, int prec)
{
    if (!m_createdEditors.contains(property))
    return;

    QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
    return;

    QList<QDoubleEdit *> editors = m_createdEditors[property];
    QListIterator<QDoubleEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        QDoubleEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setPrecision(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtDoubleEditFactoryPrivate::slotSetValue(double value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

void QtDoubleEditFactoryPrivate::slotSetScale(int scaleSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_unitAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_unitAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setScale(property, Scale(scaleSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtDoubleEditFactoryPrivate::slotSetFormat(int formatSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_formatAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_formatAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setFormat(property, Format(formatSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtDoubleEditFactoryPrivate::slotSetMinimum(double minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtDoubleEditFactoryPrivate::slotSetMaximum(double maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtDoubleEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDoublePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}
/*! \class QtDoubleEditFactory

 \brief The QtDoubleEditFactory class provides QComplexEdit
 widgets for properties created by QtDoublePropertyManager objects.

 \sa QtAbstractEditorFactory, QtDoublePropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtDoubleEditFactory::QtDoubleEditFactory(QObject *parent)
: QtAbstractEditorFactory<QtDoublePropertyManager>(parent)
{
    d_ptr = new QtDoubleEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtDoubleEditFactory::~QtDoubleEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtDoubleEditFactory::connectPropertyManager(QtDoublePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, double)),
            this, SLOT(slotPropertyChanged(QtProperty *, double)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    connect(manager, SIGNAL(precisionChanged(QtProperty *, int)),
            this, SLOT(slotPrecisionChanged(QtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtDoubleEditFactory::createEditor(QtDoublePropertyManager *manager,
                                        QtProperty *property, QWidget *parent)
{
    QDoubleEdit *editor = d_ptr->createEditor(property, parent);
    //editor->setSingleStep(manager->singleStep(property));
    editor->setPrecision(manager->precision(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setFormat(manager->format(property));
    editor->setScale(manager->scale(property));
    //editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetValue(double)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtDoubleEditFactory::createAttributeEditor(QtDoublePropertyManager *manager, QtProperty *property,
                                                    QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::UNIT)
    {
        if (!manager->attributesEditable(BrowserCol::UNIT))
            return nullptr;
        QComboBox *editor = d_ptr->createUnitAttributeEditor(property, parent);
        updateUnit(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetScale(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotUnitAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::FORMAT)
    {
        if (!manager->attributesEditable(BrowserCol::FORMAT))
            return nullptr;
        QComboBox *editor = d_ptr->createFormatAttributeEditor(property, parent);
        updateFormat(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetFormat(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotFormatAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtDoubleEditFactory::disconnectPropertyManager(QtDoublePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, double)),
               this, SLOT(slotPropertyChanged(QtProperty *, double)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, double, double)),
               this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    disconnect(manager, SIGNAL(precisionChanged(QtProperty *, int)),
               this, SLOT(slotPrecisionChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

// QtComplexEditFactory

class QtComplexEditFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtComplexEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtComplexEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QComplex& value);
    void slotRangeChanged(QtProperty *property, double min, double max);
    void slotPrecisionChanged(QtProperty *property, int prec);
    void slotReadOnlyChanged(QtProperty *property, bool readOnly);
    void slotSetValue(const QComplex& value);
    void slotSetScale(int scaleSelection);
    void slotSetPkAvg(int slotSetPkAvg);
    void slotSetFormat(int formatSelection);
    void slotSetMinimum(double minVal);
    void slotSetMaximum(double maxVal);
    void slotSetCheck(bool check);
};

void QtComplexEditFactoryPrivate::slotPropertyChanged(QtProperty *property, const QComplex& value)
{
    QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
    QList<QComplexEdit *> editors = m_createdEditors[property];
    QListIterator<QComplexEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComplexEdit *editor = itEditor.next();
        editor->setScale(manager->scale(property));
        editor->setFormat(manager->format(property));
        if (!isclose(value, editor->value(), epsilon, epsilon)){
            editor->blockSignals(true);
            editor->setValue(value);
            editor->blockSignals(false);
        }
    }
    QList<QComboBox *> unitEditors = m_createdUnitAttributeEditors[property];
    for (unsigned short index = 0; index < unitEditors.size(); ++index ){
        updateUnit(manager, property, unitEditors[index]);
    }
    QList<QComboBox *> formatEditors = m_createdFormatAttributeEditors[property];
    for (unsigned short index = 0; index < formatEditors.size(); ++index ){
        updateFormat(manager, property, formatEditors[index]);
    }
    QList<QDoubleEdit *> minimumEditors = m_createdMinimumAttributeEditors[property];
    for (unsigned short index = 0; index < minimumEditors.size(); ++index ){
        updateMinimum(manager, property, minimumEditors[index]);
    }
    QList<QDoubleEdit *> maximumEditors = m_createdMaximumAttributeEditors[property];
    for (unsigned short index = 0; index < maximumEditors.size(); ++index ){
        updateMaximum(manager, property, maximumEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtComplexEditFactoryPrivate::slotRangeChanged(QtProperty *property,
                                                     double min, double max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QComplexEdit *> editors = m_createdEditors[property];
    QListIterator<QComplexEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        QComplexEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setRange(min, max);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtComplexEditFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QComplexEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComplexEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtComplexEditFactoryPrivate::slotPrecisionChanged(QtProperty *property, int prec)
{
    if (!m_createdEditors.contains(property))
        return;

    QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QList<QComplexEdit *> editors = m_createdEditors[property];
    QListIterator<QComplexEdit *> itEditor(editors);
    while (itEditor.hasNext()) {
        QComplexEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setPrecision(prec);
        editor->setValue(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtComplexEditFactoryPrivate::slotSetValue(const QComplex& value)
{
    QObject *object = q_ptr->sender();
    const QMap<QComplexEdit *, QtProperty *>::ConstIterator itcend = m_editorToProperty.constEnd();
    for (QMap<QComplexEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
    }
}

void QtComplexEditFactoryPrivate::slotSetScale(int scaleSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_unitAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_unitAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setScale(property, Scale(scaleSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtComplexEditFactoryPrivate::slotSetPkAvg(int pkAvgSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_pkAvgAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_pkAvgAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setPkAvg(property, PkAvg(pkAvgSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtComplexEditFactoryPrivate::slotSetFormat(int formatSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_formatAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_formatAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setFormat(property, Format(formatSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtComplexEditFactoryPrivate::slotSetMinimum(double minVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_minimumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_minimumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMinimum(property, minVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtComplexEditFactoryPrivate::slotSetMaximum(double maxVal)
{
    QObject *object = q_ptr->sender();
    const QMap<QDoubleEdit *, QtProperty *>::ConstIterator itcend = m_maximumAttributeEditorToProperty.constEnd();
    for (QMap<QDoubleEdit *, QtProperty *>::ConstIterator itEditor = m_maximumAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setMaximum(property, maxVal);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtComplexEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtComplexPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}
/*! \class QtComplexEditFactory

 \brief The QtComplexEditFactory class provides QComplexEdit
 widgets for properties created by QtDoublePropertyManager objects.

 \sa QtAbstractEditorFactory, QtDoublePropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtComplexEditFactory::QtComplexEditFactory(QObject *parent)
: QtAbstractEditorFactory<QtComplexPropertyManager>(parent)
{
    d_ptr = new QtComplexEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtComplexEditFactory::~QtComplexEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtComplexEditFactory::connectPropertyManager(QtComplexPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QComplex&)),
            this, SLOT(slotPropertyChanged(QtProperty *, const QComplex&)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    connect(manager, SIGNAL(precisionChanged(QtProperty *, int)),
            this, SLOT(slotPrecisionChanged(QtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
            this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtComplexEditFactory::createEditor(QtComplexPropertyManager *manager,
                                              QtProperty *property, QWidget *parent)
{
    QComplexEdit *editor = d_ptr->createEditor(property, parent);
    //editor->setSingleStep(manager->singleStep(property));
    editor->setPrecision(manager->precision(property));
    editor->setRange(manager->minimum(property), manager->maximum(property));
    editor->setValue(manager->value(property));
    editor->setFormat(manager->format(property));
    editor->setScale(manager->scale(property));
    //editor->setKeyboardTracking(false);
    editor->setReadOnly(manager->isReadOnly(property));

    connect(editor, SIGNAL(valueChanged(const QComplex&)), this, SLOT(slotSetValue(const QComplex&)));
    connect(editor, SIGNAL(destroyed(QObject *)),
            this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtComplexEditFactory::createAttributeEditor(QtComplexPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::UNIT)
    {
        if (!manager->attributesEditable(BrowserCol::UNIT))
            return nullptr;
        QComboBox *editor = d_ptr->createUnitAttributeEditor(property, parent);
        updateUnit(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetScale(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotUnitAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::FORMAT)
    {
        if (!manager->attributesEditable(BrowserCol::FORMAT))
            return nullptr;
        QComboBox *editor = d_ptr->createFormatAttributeEditor(property, parent);
        updateFormat(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetFormat(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotFormatAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MINIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MINIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMinimumAttributeEditor(property, parent);
        updateMinimum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMinimum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMinimumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::MAXIMUM)
    {
        if (!manager->attributesEditable(BrowserCol::MAXIMUM))
            return nullptr;
        QDoubleEdit *editor = d_ptr->createMaximumAttributeEditor(property, parent);
        updateMaximum(manager, property, editor);

        connect(editor, SIGNAL(valueChanged(double)), this, SLOT(slotSetMaximum(double)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotMaximumAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtComplexEditFactory::disconnectPropertyManager(QtComplexPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QComplex&)),
               this, SLOT(slotPropertyChanged(QtProperty *, const QComplex&)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, double, double)),
               this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    disconnect(manager, SIGNAL(precisionChanged(QtProperty *, int)),
               this, SLOT(slotPrecisionChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QtProperty *, bool)),
               this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

// QtArrayEditFactory

class QtTFTensorEditFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtTFTensorEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtTFTensorEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QVector<QComplex>& value);
    void slotSetScale(int scaleSelection);
    void slotSetPkAvg(int formatSelection);
    void slotSetFormat(int formatSelection);
    void slotSetCheck(bool check);
    QtComplexEditFactory* m_subFactory;
};

void QtTFTensorEditFactoryPrivate::slotPropertyChanged(QtProperty *property, const QVector<QComplex>& value)
{
    QtTFTensorPropertyManager* manager = q_ptr->propertyManager(property);
    for(int index=0; index < property->subProperties().size(); ++index){
        QtProperty* subProperty = property->subProperties()[index];
        m_subFactory->d_ptr->slotPropertyChanged(subProperty, value[index]);
    }
    QList<QComboBox *> unitEditors = m_createdUnitAttributeEditors[property];
    for (unsigned short index = 0; index < unitEditors.size(); ++index ){
        updateUnit(manager, property, unitEditors[index]);
    }
    QList<QComboBox *> formatEditors = m_createdFormatAttributeEditors[property];
    for (unsigned short index = 0; index < formatEditors.size(); ++index ){
        updateFormat(manager, property, formatEditors[index]);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtTFTensorEditFactoryPrivate::slotSetScale(int scaleSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_unitAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_unitAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtTFTensorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setScale(property, Scale(scaleSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtTFTensorEditFactoryPrivate::slotSetPkAvg(int pkAvgSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_pkAvgAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_pkAvgAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtTFTensorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setPkAvg(property, PkAvg(pkAvgSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtTFTensorEditFactoryPrivate::slotSetFormat(int formatSelection)
{
    QObject *object = q_ptr->sender();
    const QMap<QComboBox *, QtProperty *>::ConstIterator itcend = m_formatAttributeEditorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_formatAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtTFTensorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setFormat(property, Format(formatSelection));
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

void QtTFTensorEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtTFTensorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*! \class QtArrayEditFactory

 \brief The QtArrayEditFactory class provides QComplexEdit
 widgets for properties created by QtDoublePropertyManager objects.

 \sa QtAbstractEditorFactory, QtDoublePropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtTFTensorEditFactory::QtTFTensorEditFactory(QObject *parent)
: QtAbstractEditorFactory<QtTFTensorPropertyManager>(parent)
{
    d_ptr = new QtTFTensorEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtTFTensorEditFactory::~QtTFTensorEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

QtComplexEditFactory* QtTFTensorEditFactory::subFactory() const
{
    return d_ptr->m_subFactory;
}

void QtTFTensorEditFactory::setSubFactory(QtComplexEditFactory* subFactory)
{
    d_ptr->m_subFactory = subFactory;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtTFTensorEditFactory::connectPropertyManager(QtTFTensorPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtTFTensorEditFactory::createEditor(QtTFTensorPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtTFTensorEditFactory::createAttributeEditor(QtTFTensorPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::UNIT)
    {
        if (!manager->attributesEditable(BrowserCol::UNIT))
            return nullptr;
        QComboBox *editor = d_ptr->createUnitAttributeEditor(property, parent);
        updateUnit(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetScale(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotUnitAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::PKAVG)
    {
        if (!manager->attributesEditable(BrowserCol::PKAVG))
            return nullptr;
        QComboBox *editor = d_ptr->createPkAvgAttributeEditor(property, parent);
        updatePkAvg(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetPkAvg(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotPkAvgAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::FORMAT)
    {
        if (!manager->attributesEditable(BrowserCol::FORMAT))
            return nullptr;
        QComboBox *editor = d_ptr->createFormatAttributeEditor(property, parent);
        updateFormat(manager, property, editor);

        connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetFormat(int)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotFormatAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    else if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtTFTensorEditFactory::disconnectPropertyManager(QtTFTensorPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtLineEditFactory

class QtLineEditFactoryPrivate : public EditorFactoryPrivate<QLineEdit>
{
    QtLineEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtLineEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QString &value);
    void slotRegExpChanged(QtProperty *property, const QRegExp &regExp);
    void slotSetValue(const QString &value);
    void slotEchoModeChanged(QtProperty *, int);
    void slotReadOnlyChanged(QtProperty *, bool);
    void slotSetCheck(bool check);
};

void QtLineEditFactoryPrivate::slotPropertyChanged(QtProperty *property,
                const QString &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtStringPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QLineEdit *> itEditor( m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        if (editor->text() != value) {
            editor->blockSignals(true);
            editor->setText(value);
            editor->blockSignals(false);
        }
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtLineEditFactoryPrivate::slotRegExpChanged(QtProperty *property,
            const QRegExp &regExp)
{
    if (!m_createdEditors.contains(property))
        return;

    QtStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        const QValidator *oldValidator = editor->validator();
        QValidator *newValidator = nullptr;
        if (regExp.isValid()) {
            newValidator = new QRegExpValidator(regExp, editor);
        }
        editor->setValidator(newValidator);
        if (oldValidator)
            delete oldValidator;
        editor->blockSignals(false);
    }
}

void QtLineEditFactoryPrivate::slotEchoModeChanged(QtProperty *property, int echoMode)
{
    if (!m_createdEditors.contains(property))
        return;

    QtStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setEchoMode(static_cast<EchoMode>(echoMode));
        editor->blockSignals(false);
    }
}

void QtLineEditFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QtStringPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QLineEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QLineEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtLineEditFactoryPrivate::slotSetValue(const QString &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QLineEdit *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QLineEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtStringPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtLineEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtStringPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtLineEditFactory

    \brief The QtLineEditFactory class provides QLineEdit widgets for
    properties created by QtStringPropertyManager objects.

    \sa QtAbstractEditorFactory, QtStringPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtLineEditFactory::QtLineEditFactory(QObject *parent)
    : QtAbstractEditorFactory<QtStringPropertyManager>(parent)
{
    d_ptr = new QtLineEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtLineEditFactory::~QtLineEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtLineEditFactory::connectPropertyManager(QtStringPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)),
            this, SLOT(slotPropertyChanged(QtProperty *, const QString &)));
    connect(manager, SIGNAL(regExpChanged(QtProperty *, const QRegExp &)),
            this, SLOT(slotRegExpChanged(QtProperty *, const QRegExp &)));
    connect(manager, SIGNAL(echoModeChanged(QtProperty*, int)),
            this, SLOT(slotEchoModeChanged(QtProperty *, int)));
    connect(manager, SIGNAL(readOnlyChanged(QtProperty*, bool)),
        this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtLineEditFactory::createEditor(QtStringPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{

    QLineEdit *editor = d_ptr->createEditor(property, parent);
    editor->setEchoMode(static_cast<EchoMode>(manager->echoMode(property)));
    editor->setReadOnly(manager->isReadOnly(property));
    QRegExp regExp = manager->regExp(property);
    if (regExp.isValid()) {
        QValidator *validator = new QRegExpValidator(regExp, editor);
        editor->setValidator(validator);
    }
    editor->setText(manager->value(property));

    connect(editor, SIGNAL(textChanged(const QString &)),
                this, SLOT(slotSetValue(const QString &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtLineEditFactory::createAttributeEditor(QtStringPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtLineEditFactory::disconnectPropertyManager(QtStringPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QString &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QString &)));
    disconnect(manager, SIGNAL(regExpChanged(QtProperty *, const QRegExp &)),
                this, SLOT(slotRegExpChanged(QtProperty *, const QRegExp &)));
    disconnect(manager, SIGNAL(echoModeChanged(QtProperty*,int)),
                this, SLOT(slotEchoModeChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(readOnlyChanged(QtProperty*, bool)),
        this, SLOT(slotReadOnlyChanged(QtProperty *, bool)));

}

// QtDateEditFactory

class QtDateEditFactoryPrivate : public EditorFactoryPrivate<QDateEdit>
{
    QtDateEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtDateEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QDate &value);
    void slotRangeChanged(QtProperty *property, const QDate &min, const QDate &max);
    void slotSetValue(const QDate &value);
    void slotSetCheck(bool check);
};

void QtDateEditFactoryPrivate::slotPropertyChanged(QtProperty *property, const QDate &value)
{
    if (!m_createdEditors.contains(property))
        return;
    QtDatePropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QDateEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDateEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDate(value);
        editor->blockSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtDateEditFactoryPrivate::slotRangeChanged(QtProperty *property,
                const QDate &min, const QDate &max)
{
    if (!m_createdEditors.contains(property))
        return;

    QtDatePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QDateEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDateEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDateRange(min, max);
        editor->setDate(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtDateEditFactoryPrivate::slotSetValue(const QDate &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QDateEdit *, QtProperty *>::ConstIterator  ecend = m_editorToProperty.constEnd();
    for (QMap<QDateEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDatePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtDateEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDatePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtDateEditFactory

    \brief The QtDateEditFactory class provides QDateEdit widgets for
    properties created by QtDatePropertyManager objects.

    \sa QtAbstractEditorFactory, QtDatePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtDateEditFactory::QtDateEditFactory(QObject *parent)
    : QtAbstractEditorFactory<QtDatePropertyManager>(parent)
{
    d_ptr = new QtDateEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtDateEditFactory::~QtDateEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtDateEditFactory::connectPropertyManager(QtDatePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QDate &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QDate &)));
    connect(manager, SIGNAL(rangeChanged(QtProperty *, const QDate &, const QDate &)),
                this, SLOT(slotRangeChanged(QtProperty *, const QDate &, const QDate &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtDateEditFactory::createEditor(QtDatePropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QDateEdit *editor = d_ptr->createEditor(property, parent);
    editor->setCalendarPopup(true);
    editor->setDateRange(manager->minimum(property), manager->maximum(property));
    editor->setDate(manager->value(property));

    connect(editor, SIGNAL(dateChanged(const QDate &)),
                this, SLOT(slotSetValue(const QDate &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtDateEditFactory::createAttributeEditor(QtDatePropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtDateEditFactory::disconnectPropertyManager(QtDatePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QDate &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QDate &)));
    disconnect(manager, SIGNAL(rangeChanged(QtProperty *, const QDate &, const QDate &)),
                this, SLOT(slotRangeChanged(QtProperty *, const QDate &, const QDate &)));
}

// QtTimeEditFactory

class QtTimeEditFactoryPrivate : public EditorFactoryPrivate<QTimeEdit>
{
    QtTimeEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtTimeEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QTime &value);
    void slotSetValue(const QTime &value);
    void slotSetCheck(bool check);
};

void QtTimeEditFactoryPrivate::slotPropertyChanged(QtProperty *property, const QTime &value)
{
    if (!m_createdEditors.contains(property))
        return;
    QtTimePropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QTimeEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QTimeEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setTime(value);
        editor->blockSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtTimeEditFactoryPrivate::slotSetValue(const QTime &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QTimeEdit *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QTimeEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtTimeEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtTimeEditFactory

    \brief The QtTimeEditFactory class provides QTimeEdit widgets for
    properties created by QtTimePropertyManager objects.

    \sa QtAbstractEditorFactory, QtTimePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtTimeEditFactory::QtTimeEditFactory(QObject *parent)
    : QtAbstractEditorFactory<QtTimePropertyManager>(parent)
{
    d_ptr = new QtTimeEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtTimeEditFactory::~QtTimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtTimeEditFactory::connectPropertyManager(QtTimePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QTime &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QTime &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtTimeEditFactory::createEditor(QtTimePropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QTimeEdit *editor = d_ptr->createEditor(property, parent);
    editor->setTime(manager->value(property));

    connect(editor, SIGNAL(timeChanged(const QTime &)),
                this, SLOT(slotSetValue(const QTime &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtTimeEditFactory::createAttributeEditor(QtTimePropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtTimeEditFactory::disconnectPropertyManager(QtTimePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QTime &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QTime &)));
}

// QtDateTimeEditFactory

class QtDateTimeEditFactoryPrivate : public EditorFactoryPrivate<QDateTimeEdit>
{
    QtDateTimeEditFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtDateTimeEditFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QDateTime &value);
    void slotSetValue(const QDateTime &value);
    void slotSetCheck(bool check);

};

void QtDateTimeEditFactoryPrivate::slotPropertyChanged(QtProperty *property,
            const QDateTime &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtDateTimePropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QDateTimeEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QDateTimeEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setDateTime(value);
        editor->blockSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtDateTimeEditFactoryPrivate::slotSetValue(const QDateTime &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QDateTimeEdit *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QDateTimeEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDateTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtDateTimeEditFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtDateTimePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtDateTimeEditFactory

    \brief The QtDateTimeEditFactory class provides QDateTimeEdit
    widgets for properties created by QtDateTimePropertyManager objects.

    \sa QtAbstractEditorFactory, QtDateTimePropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtDateTimeEditFactory::QtDateTimeEditFactory(QObject *parent)
    : QtAbstractEditorFactory<QtDateTimePropertyManager>(parent)
{
    d_ptr = new QtDateTimeEditFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtDateTimeEditFactory::~QtDateTimeEditFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtDateTimeEditFactory::connectPropertyManager(QtDateTimePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QDateTime &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QDateTime &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtDateTimeEditFactory::createEditor(QtDateTimePropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    QDateTimeEdit *editor =  d_ptr->createEditor(property, parent);
    editor->setDateTime(manager->value(property));

    connect(editor, SIGNAL(dateTimeChanged(const QDateTime &)),
                this, SLOT(slotSetValue(const QDateTime &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtDateTimeEditFactory::createAttributeEditor(QtDateTimePropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtDateTimeEditFactory::disconnectPropertyManager(QtDateTimePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QDateTime &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QDateTime &)));
}

// QtKeySequenceEditorFactory

class QtKeySequenceEditorFactoryPrivate : public EditorFactoryPrivate<QtKeySequenceEdit>
{
    QtKeySequenceEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtKeySequenceEditorFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QKeySequence &value);
    void slotSetValue(const QKeySequence &value);
    void slotSetCheck(bool check);
};

void QtKeySequenceEditorFactoryPrivate::slotPropertyChanged(QtProperty *property,
            const QKeySequence &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtKeySequencePropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QtKeySequenceEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QtKeySequenceEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setKeySequence(value);
        editor->blockSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtKeySequenceEditorFactoryPrivate::slotSetValue(const QKeySequence &value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QtKeySequenceEdit *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QtKeySequenceEdit *, QtProperty *>::ConstIterator itEditor =  m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtKeySequencePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtKeySequenceEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtKeySequencePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtKeySequenceEditorFactory

    \brief The QtKeySequenceEditorFactory class provides editor
    widgets for properties created by QtKeySequencePropertyManager objects.

    \sa QtAbstractEditorFactory
*/

/*!
    Creates a factory with the given \a parent.
*/
QtKeySequenceEditorFactory::QtKeySequenceEditorFactory(QObject *parent)
    : QtAbstractEditorFactory<QtKeySequencePropertyManager>(parent)
{
    d_ptr = new QtKeySequenceEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtKeySequenceEditorFactory::~QtKeySequenceEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtKeySequenceEditorFactory::connectPropertyManager(QtKeySequencePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QKeySequence &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QKeySequence &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtKeySequenceEditorFactory::createEditor(QtKeySequencePropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    QtKeySequenceEdit *editor = d_ptr->createEditor(property, parent);
    editor->setKeySequence(manager->value(property));

    connect(editor, SIGNAL(keySequenceChanged(const QKeySequence &)),
                this, SLOT(slotSetValue(const QKeySequence &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtKeySequenceEditorFactory::createAttributeEditor(QtKeySequencePropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtKeySequenceEditorFactory::disconnectPropertyManager(QtKeySequencePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QKeySequence &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QKeySequence &)));
}

// QtCharEdit

class QtCharEdit : public QWidget
{
    Q_OBJECT
public:
    QtCharEdit(QWidget *parent = nullptr);

    QChar value() const;
    bool eventFilter(QObject *o, QEvent *e);
public Q_SLOTS:
    void setValue(const QChar &value);
Q_SIGNALS:
    void valueChanged(const QChar &value);
protected:
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *);
    bool event(QEvent *e);
private slots:
    void slotClearChar();
private:
    void handleKeyEvent(QKeyEvent *e);

    QChar m_value;
    QLineEdit *m_lineEdit;
};

QtCharEdit::QtCharEdit(QWidget *parent)
    : QWidget(parent),  m_lineEdit(new QLineEdit(this))
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_lineEdit);
    layout->setMargin(0);
    m_lineEdit->installEventFilter(this);
    m_lineEdit->setReadOnly(true);
    m_lineEdit->setFocusProxy(this);
    setFocusPolicy(m_lineEdit->focusPolicy());
    setAttribute(Qt::WA_InputMethodEnabled);
}

bool QtCharEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_lineEdit && e->type() == QEvent::ContextMenu) {
        QContextMenuEvent *c = static_cast<QContextMenuEvent *>(e);
        QMenu *menu = m_lineEdit->createStandardContextMenu();
        QList<QAction *> actions = menu->actions();
        QListIterator<QAction *> itAction(actions);
        while (itAction.hasNext()) {
            QAction *action = itAction.next();
            action->setShortcut(QKeySequence());
            QString actionString = action->text();
            const int pos = actionString.lastIndexOf(QLatin1Char('\t'));
            if (pos > 0)
                actionString = actionString.remove(pos, actionString.length() - pos);
            action->setText(actionString);
        }
        QAction *actionBefore = nullptr;
        if (actions.count() > 0)
            actionBefore = actions[0];
        QAction *clearAction = new QAction(tr("Clear Char"), menu);
        menu->insertAction(actionBefore, clearAction);
        menu->insertSeparator(actionBefore);
        clearAction->setEnabled(!m_value.isNull());
        connect(clearAction, SIGNAL(triggered()), this, SLOT(slotClearChar()));
        menu->exec(c->globalPos());
        delete menu;
        e->accept();
        return true;
    }

    return QWidget::eventFilter(o, e);
}

void QtCharEdit::slotClearChar()
{
    if (m_value.isNull())
        return;
    setValue(QChar());
    emit valueChanged(m_value);
}

void QtCharEdit::handleKeyEvent(QKeyEvent *e)
{
    const int key = e->key();
    switch (key) {
    case Qt::Key_Control:
    case Qt::Key_Shift:
    case Qt::Key_Meta:
    case Qt::Key_Alt:
    case Qt::Key_Super_L:
    case Qt::Key_Return:
        return;
    default:
        break;
    }

    const QString text = e->text();
    if (text.count() != 1)
        return;

    const QChar c = text.at(0);
    if (!c.isPrint())
        return;

    if (m_value == c)
        return;

    m_value = c;
    const QString str = m_value.isNull() ? QString() : QString(m_value);
    m_lineEdit->setText(str);
    e->accept();
    emit valueChanged(m_value);
}

void QtCharEdit::setValue(const QChar &value)
{
    if (value == m_value)
        return;

    m_value = value;
    QString str = value.isNull() ? QString() : QString(value);
    m_lineEdit->setText(str);
}

QChar QtCharEdit::value() const
{
    return m_value;
}

void QtCharEdit::focusInEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    m_lineEdit->selectAll();
    QWidget::focusInEvent(e);
}

void QtCharEdit::focusOutEvent(QFocusEvent *e)
{
    m_lineEdit->event(e);
    QWidget::focusOutEvent(e);
}

void QtCharEdit::keyPressEvent(QKeyEvent *e)
{
    handleKeyEvent(e);
    e->accept();
}

void QtCharEdit::keyReleaseEvent(QKeyEvent *e)
{
    m_lineEdit->event(e);
}

void QtCharEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool QtCharEdit::event(QEvent *e)
{
    switch(e->type()) {
    case QEvent::Shortcut:
    case QEvent::ShortcutOverride:
    case QEvent::KeyRelease:
        e->accept();
        return true;
    default:
        break;
    }
    return QWidget::event(e);
}

// QtCharEditorFactory

class QtCharEditorFactoryPrivate : public EditorFactoryPrivate<QtCharEdit>
{
    QtCharEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtCharEditorFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QChar &value);
    void slotSetValue(const QChar &value);
    void slotSetCheck(bool check);

};

void QtCharEditorFactoryPrivate::slotPropertyChanged(QtProperty *property,
            const QChar &value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtCharPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QtCharEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QtCharEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setValue(value);
        editor->blockSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtCharEditorFactoryPrivate::slotSetValue(const QChar &value)
{
    QObject *object = q_ptr->sender();
    const QMap<QtCharEdit *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QtCharEdit *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend;  ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtCharPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtCharEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtCharPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtCharEditorFactory

    \brief The QtCharEditorFactory class provides editor
    widgets for properties created by QtCharPropertyManager objects.

    \sa QtAbstractEditorFactory
*/

/*!
    Creates a factory with the given \a parent.
*/
QtCharEditorFactory::QtCharEditorFactory(QObject *parent)
    : QtAbstractEditorFactory<QtCharPropertyManager>(parent)
{
    d_ptr = new QtCharEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtCharEditorFactory::~QtCharEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtCharEditorFactory::connectPropertyManager(QtCharPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QChar &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QChar &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtCharEditorFactory::createEditor(QtCharPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    QtCharEdit *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));

    connect(editor, SIGNAL(valueChanged(const QChar &)),
                this, SLOT(slotSetValue(const QChar &)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtCharEditorFactory::createAttributeEditor(QtCharPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtCharEditorFactory::disconnectPropertyManager(QtCharPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QChar &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QChar &)));
}

// QtLocaleEditorFactory

class QtLocaleEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtLocaleEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtLocaleEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtLocaleEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtLocalePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtLocaleEditorFactory

 \brief The QtLocaleEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtLocaleEditorFactory::QtLocaleEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtLocalePropertyManager>(parent)
{
    d_ptr = new QtLocaleEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtLocaleEditorFactory::~QtLocaleEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtLocaleEditorFactory::connectPropertyManager(QtLocalePropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtLocaleEditorFactory::createEditor(QtLocalePropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtLocaleEditorFactory::createAttributeEditor(QtLocalePropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtLocaleEditorFactory::disconnectPropertyManager(QtLocalePropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtPointEditorFactory

class QtPointEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtPointEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtPointEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtPointEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtPointPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtPointEditorFactory

 \brief The QtPointEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtPointEditorFactory::QtPointEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtPointPropertyManager>(parent)
{
    d_ptr = new QtPointEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtPointEditorFactory::~QtPointEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtPointEditorFactory::connectPropertyManager(QtPointPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtPointEditorFactory::createEditor(QtPointPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtPointEditorFactory::createAttributeEditor(QtPointPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtPointEditorFactory::disconnectPropertyManager(QtPointPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtPointFEditorFactory

class QtPointFEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtPointFEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtPointFEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtPointFEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtPointFPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtPointFEditorFactory

 \brief The QtPointFEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtPointFEditorFactory::QtPointFEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtPointFPropertyManager>(parent)
{
    d_ptr = new QtPointFEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtPointFEditorFactory::~QtPointFEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtPointFEditorFactory::connectPropertyManager(QtPointFPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtPointFEditorFactory::createEditor(QtPointFPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtPointFEditorFactory::createAttributeEditor(QtPointFPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtPointFEditorFactory::disconnectPropertyManager(QtPointFPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtSizeEditorFactory

class QtSizeEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtSizeEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtSizeEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtSizeEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtSizePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtSizeEditorFactory

 \brief The QtSizeEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtSizeEditorFactory::QtSizeEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtSizePropertyManager>(parent)
{
    d_ptr = new QtSizeEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtSizeEditorFactory::~QtSizeEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtSizeEditorFactory::connectPropertyManager(QtSizePropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSizeEditorFactory::createEditor(QtSizePropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSizeEditorFactory::createAttributeEditor(QtSizePropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtSizeEditorFactory::disconnectPropertyManager(QtSizePropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtSizeFEditorFactory

class QtSizeFEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtSizeFEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtSizeFEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtSizeFEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtSizeFPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtSizeFEditorFactory

 \brief The QtSizeFEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtSizeFEditorFactory::QtSizeFEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtSizeFPropertyManager>(parent)
{
    d_ptr = new QtSizeFEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtSizeFEditorFactory::~QtSizeFEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtSizeFEditorFactory::connectPropertyManager(QtSizeFPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSizeFEditorFactory::createEditor(QtSizeFPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSizeFEditorFactory::createAttributeEditor(QtSizeFPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtSizeFEditorFactory::disconnectPropertyManager(QtSizeFPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtRectEditorFactory

class QtRectEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtRectEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtRectEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtRectEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtRectPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtRectEditorFactory

 \brief The QtRectEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtRectEditorFactory::QtRectEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtRectPropertyManager>(parent)
{
    d_ptr = new QtRectEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtRectEditorFactory::~QtRectEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtRectEditorFactory::connectPropertyManager(QtRectPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtRectEditorFactory::createEditor(QtRectPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtRectEditorFactory::createAttributeEditor(QtRectPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtRectEditorFactory::disconnectPropertyManager(QtRectPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtRectFEditorFactory

class QtRectFEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtRectFEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtRectFEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtRectFEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtRectFPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtRectFEditorFactory

 \brief The QtRectFEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtRectFEditorFactory::QtRectFEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtRectFPropertyManager>(parent)
{
    d_ptr = new QtRectFEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtRectFEditorFactory::~QtRectFEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtRectFEditorFactory::connectPropertyManager(QtRectFPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtRectFEditorFactory::createEditor(QtRectFPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtRectFEditorFactory::createAttributeEditor(QtRectFPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtRectFEditorFactory::disconnectPropertyManager(QtRectFPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtEnumEditorFactory

class QtEnumEditorFactoryPrivate : public EditorFactoryPrivate<QComboBox>
{
    QtEnumEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtEnumEditorFactory)
public:

    void slotPropertyChanged(QtProperty *property, int value);
    void slotEnumNamesChanged(QtProperty *property, const QStringList &);
    void slotEnumIconsChanged(QtProperty *property, const QMap<int, QIcon> &);
    void slotSetValue(int value);
    void slotSetCheck(bool check);
};

void QtEnumEditorFactoryPrivate::slotPropertyChanged(QtProperty *property, int value)
{
    if (!m_createdEditors.contains(property))
        return;

    QtEnumPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setCurrentIndex(value);
        editor->blockSignals(false);
    }
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtEnumEditorFactoryPrivate::slotEnumNamesChanged(QtProperty *property,
                const QStringList &enumNames)
{
    if (!m_createdEditors.contains(property))
        return;

    QtEnumPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QMap<int, QIcon> enumIcons = manager->enumIcons(property);

    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        editor->clear();
        editor->addItems(enumNames);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
            editor->setItemIcon(i, enumIcons.value(i));
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtEnumEditorFactoryPrivate::slotEnumIconsChanged(QtProperty *property,
                const QMap<int, QIcon> &enumIcons)
{
    if (!m_createdEditors.contains(property))
        return;

    QtEnumPropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    const QStringList enumNames = manager->enumNames(property);
    QListIterator<QComboBox *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QComboBox *editor = itEditor.next();
        editor->blockSignals(true);
        const int nameCount = enumNames.count();
        for (int i = 0; i < nameCount; i++)
            editor->setItemIcon(i, enumIcons.value(i));
        editor->setCurrentIndex(manager->value(property));
        editor->blockSignals(false);
    }
}

void QtEnumEditorFactoryPrivate::slotSetValue(int value)
{
    QObject *object = q_ptr->sender();
    const  QMap<QComboBox *, QtProperty *>::ConstIterator ecend = m_editorToProperty.constEnd();
    for (QMap<QComboBox *, QtProperty *>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtEnumPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtEnumEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtEnumPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtEnumEditorFactory

    \brief The QtEnumEditorFactory class provides QComboBox widgets for
    properties created by QtEnumPropertyManager objects.

    \sa QtAbstractEditorFactory, QtEnumPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtEnumEditorFactory::QtEnumEditorFactory(QObject *parent)
    : QtAbstractEditorFactory<QtEnumPropertyManager>(parent)
{
    d_ptr = new QtEnumEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtEnumEditorFactory::~QtEnumEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtEnumEditorFactory::connectPropertyManager(QtEnumPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    connect(manager, SIGNAL(enumNamesChanged(QtProperty *, const QStringList &)),
                this, SLOT(slotEnumNamesChanged(QtProperty *, const QStringList &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtEnumEditorFactory::createEditor(QtEnumPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QComboBox *editor = d_ptr->createEditor(property, parent);
    editor->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    editor->setMinimumContentsLength(1);
    editor->view()->setTextElideMode(Qt::ElideRight);
    QStringList enumNames = manager->enumNames(property);
    editor->addItems(enumNames);
    QMap<int, QIcon> enumIcons = manager->enumIcons(property);
    const int enumNamesCount = enumNames.count();
    for (int i = 0; i < enumNamesCount; i++)
        editor->setItemIcon(i, enumIcons.value(i));
    editor->setCurrentIndex(manager->value(property));

    connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetValue(int)));
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtEnumEditorFactory::createAttributeEditor(QtEnumPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtEnumEditorFactory::disconnectPropertyManager(QtEnumPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotPropertyChanged(QtProperty *, int)));
    disconnect(manager, SIGNAL(enumNamesChanged(QtProperty *, const QStringList &)),
                this, SLOT(slotEnumNamesChanged(QtProperty *, const QStringList &)));
}

// QtFlagEditorFactory

class QtFlagEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtFlagEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtFlagEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtFlagEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtFlagPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtFlagEditorFactory

 \brief The QtFlagEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtFlagEditorFactory::QtFlagEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtFlagPropertyManager>(parent)
{
    d_ptr = new QtFlagEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtFlagEditorFactory::~QtFlagEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtFlagEditorFactory::connectPropertyManager(QtFlagPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtFlagEditorFactory::createEditor(QtFlagPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtFlagEditorFactory::createAttributeEditor(QtFlagPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtFlagEditorFactory::disconnectPropertyManager(QtFlagPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtSizePolicyEditorFactory

class QtSizePolicyEditorFactoryPrivate : public EditorFactoryPrivate<QComplexEdit>
{
    QtSizePolicyEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtSizePolicyEditorFactory)
public:
    void slotSetCheck(bool check);
};

void QtSizePolicyEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtSizePolicyPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            return;
        }
    }
}

/*! \class QtSizePolicyEditorFactory

 \brief The QtSizePolicyEditorFactory class provides QComplexEdit
 widgets for properties created by QtAbstractPropertyManager objects.

 \sa QtAbstractEditorFactory, QtAbstractPropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtSizePolicyEditorFactory::QtSizePolicyEditorFactory(QObject *parent)
: QtAbstractEditorFactory<QtSizePolicyPropertyManager>(parent)
{
    d_ptr = new QtSizePolicyEditorFactoryPrivate();
    d_ptr->q_ptr = this;

}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtSizePolicyEditorFactory::~QtSizePolicyEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_unitAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_pkAvgAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_formatAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_minimumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_maximumAttributeEditorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtSizePolicyEditorFactory::connectPropertyManager(QtSizePolicyPropertyManager *manager)
{

    Q_UNUSED(manager);
    return;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSizePolicyEditorFactory::createEditor(QtSizePolicyPropertyManager *manager,
                                            QtProperty *property, QWidget *parent)
{
    Q_UNUSED(manager);
    return new QLabel(property->valueText(), parent);
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtSizePolicyEditorFactory::createAttributeEditor(QtSizePolicyPropertyManager *manager,
                                                     QtProperty *property, QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtSizePolicyEditorFactory::disconnectPropertyManager(QtSizePolicyPropertyManager *manager)
{
    Q_UNUSED(manager);
    return;
}

// QtCursorEditorFactory

Q_GLOBAL_STATIC(QtCursorDatabase, cursorDatabase)

class QtCursorEditorFactoryPrivate: public EditorFactoryPrivate<QComboBox>
{
    QtCursorEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtCursorEditorFactory)
public:
    QtCursorEditorFactoryPrivate();

    void slotPropertyChanged(QtProperty *property, const QCursor &cursor);
    void slotEnumChanged(QtProperty *property, int value);
    void slotEditorDestroyed(QObject *object);
    void slotSetCheck(bool check);

    QtEnumEditorFactory *m_enumEditorFactory;
    QtEnumPropertyManager *m_enumPropertyManager;

    QMap<QtProperty *, QtProperty *> m_propertyToEnum;
    QMap<QtProperty *, QtProperty *> m_enumToProperty;
    QMap<QtProperty *, QList<QWidget *> > m_enumToEditors;
    QMap<QWidget *, QtProperty *> m_editorToEnum;
    bool m_updatingEnum;
};

QtCursorEditorFactoryPrivate::QtCursorEditorFactoryPrivate()
    : m_updatingEnum(false)
{

}

void QtCursorEditorFactoryPrivate::slotPropertyChanged(QtProperty *property, const QCursor &cursor)
{
    // update enum property
    QtProperty *enumProp = m_propertyToEnum.value(property);
    if (!enumProp)
        return;

    QtCursorPropertyManager *manager = q_ptr->propertyManager(property);
    m_updatingEnum = true;
    m_enumPropertyManager->setValue(enumProp, cursorDatabase()->cursorToValue(cursor));
    m_updatingEnum = false;

    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtCursorEditorFactoryPrivate::slotEnumChanged(QtProperty *property, int value)
{
    if (m_updatingEnum)
        return;
    // update cursor property
    QtProperty *prop = m_enumToProperty.value(property);
    if (!prop)
        return;
    QtCursorPropertyManager *cursorManager = q_ptr->propertyManager(prop);
    if (!cursorManager)
        return;
#ifndef QT_NO_CURSOR
    cursorManager->setValue(prop, QCursor(cursorDatabase()->valueToCursor(value)));
#endif
}

void QtCursorEditorFactoryPrivate::slotEditorDestroyed(QObject *object)
{
    // remove from m_editorToEnum map;
    // remove from m_enumToEditors map;
    // if m_enumToEditors doesn't contains more editors delete enum property;
    const  QMap<QWidget *, QtProperty *>::ConstIterator ecend = m_editorToEnum.constEnd();
    for (QMap<QWidget *, QtProperty *>::ConstIterator itEditor = m_editorToEnum.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QWidget *editor = itEditor.key();
            QtProperty *enumProp = itEditor.value();
            m_editorToEnum.remove(editor);
            m_enumToEditors[enumProp].removeAll(editor);
            if (m_enumToEditors[enumProp].isEmpty()) {
                m_enumToEditors.remove(enumProp);
                QtProperty *property = m_enumToProperty.value(enumProp);
                m_enumToProperty.remove(enumProp);
                m_propertyToEnum.remove(property);
                delete enumProp;
            }
            return;
        }
}

void QtCursorEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtCursorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtCursorEditorFactory

    \brief The QtCursorEditorFactory class provides QComboBox widgets for
    properties created by QtCursorPropertyManager objects.

    \sa QtAbstractEditorFactory, QtCursorPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtCursorEditorFactory::QtCursorEditorFactory(QObject *parent)
    : QtAbstractEditorFactory<QtCursorPropertyManager>(parent)
{
    d_ptr = new QtCursorEditorFactoryPrivate();
    d_ptr->q_ptr = this;

    d_ptr->m_enumEditorFactory = new QtEnumEditorFactory(this);
    d_ptr->m_enumPropertyManager = new QtEnumPropertyManager(this);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotEnumChanged(QtProperty *, int)));
    d_ptr->m_enumEditorFactory->addPropertyManager(d_ptr->m_enumPropertyManager);
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtCursorEditorFactory::~QtCursorEditorFactory()
{
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtCursorEditorFactory::connectPropertyManager(QtCursorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *, const QCursor &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QCursor &)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtCursorEditorFactory::createEditor(QtCursorPropertyManager *manager, QtProperty *property,
        QWidget *parent)
{
    QtProperty *enumProp = nullptr;
    if (d_ptr->m_propertyToEnum.contains(property)) {
        enumProp = d_ptr->m_propertyToEnum[property];
    } else {
        enumProp = d_ptr->m_enumPropertyManager->addProperty(property->propertyName());
        d_ptr->m_enumPropertyManager->setEnumNames(enumProp, cursorDatabase()->cursorShapeNames());
        d_ptr->m_enumPropertyManager->setEnumIcons(enumProp, cursorDatabase()->cursorShapeIcons());
#ifndef QT_NO_CURSOR
        d_ptr->m_enumPropertyManager->setValue(enumProp, cursorDatabase()->cursorToValue(manager->value(property)));
#endif
        d_ptr->m_propertyToEnum[property] = enumProp;
        d_ptr->m_enumToProperty[enumProp] = property;
    }
    QtAbstractEditorFactoryBase *af = d_ptr->m_enumEditorFactory;
    QWidget *editor = af->createEditor(enumProp, parent);
    d_ptr->m_enumToEditors[enumProp].append(editor);
    d_ptr->m_editorToEnum[editor] = enumProp;
    connect(editor, SIGNAL(destroyed(QObject *)),
                this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtCursorEditorFactory::createAttributeEditor(QtCursorPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtCursorEditorFactory::disconnectPropertyManager(QtCursorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *, const QCursor &)),
                this, SLOT(slotPropertyChanged(QtProperty *, const QCursor &)));
}

// QtColorEditWidget

class QtColorEditWidget : public QWidget {
    Q_OBJECT

public:
    QtColorEditWidget(QWidget *parent);

    bool eventFilter(QObject *obj, QEvent *ev);

public Q_SLOTS:
    void setValue(const QColor &value);

Q_SIGNALS:
    void valueChanged(const QColor &value);

protected:
    void paintEvent(QPaintEvent *);

private Q_SLOTS:
    void buttonClicked();

private:
    QColor m_color;
    QLabel *m_pixmapLabel;
    QLabel *m_label;
    QToolButton *m_button;
};

QtColorEditWidget::QtColorEditWidget(QWidget *parent) :
    QWidget(parent),
    m_pixmapLabel(new QLabel),
    m_label(new QLabel),
    m_button(new QToolButton)
{
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setFixedWidth(20);
    setFocusProxy(m_button);
    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(tr("..."));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::brushValuePixmap(QBrush(m_color)));
    m_label->setText(QtPropertyBrowserUtils::colorValueText(m_color));
}

void QtColorEditWidget::setValue(const QColor &c)
{
    if (m_color != c) {
        m_color = c;
        m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::brushValuePixmap(QBrush(c)));
        m_label->setText(QtPropertyBrowserUtils::colorValueText(c));
    }
}

void QtColorEditWidget::buttonClicked()
{
    bool ok = false;
    QRgb oldRgba = m_color.rgba();
    QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, this);
    if (ok && newRgba != oldRgba) {
        setValue(QColor::fromRgba(newRgba));
        emit valueChanged(m_color);
    }
}

bool QtColorEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button) {
        switch (ev->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease: { // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key()) {
            case Qt::Key_Escape:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                ev->ignore();
                return true;
            default:
                break;
            }
        }
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void QtColorEditWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// QtColorEditorFactoryPrivate

class QtColorEditorFactoryPrivate : public EditorFactoryPrivate<QtColorEditWidget>
{
    QtColorEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtColorEditorFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QColor &value);
    void slotSetValue(const QColor &value);
    void slotSetCheck(bool check);
};

void QtColorEditorFactoryPrivate::slotPropertyChanged(QtProperty *property,
                const QColor &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        return;
    QtColorPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QtColorEditWidget *> itEditor(it.value());
    while (itEditor.hasNext())
        itEditor.next()->setValue(value);
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtColorEditorFactoryPrivate::slotSetValue(const QColor &value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtColorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtColorEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtColorPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtColorEditorFactory

    \brief The QtColorEditorFactory class provides color editing  for
    properties created by QtColorPropertyManager objects.

    \sa QtAbstractEditorFactory, QtColorPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtColorEditorFactory::QtColorEditorFactory(QObject *parent) :
    QtAbstractEditorFactory<QtColorPropertyManager>(parent),
    d_ptr(new QtColorEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtColorEditorFactory::~QtColorEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtColorEditorFactory::connectPropertyManager(QtColorPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty*,QColor)),
            this, SLOT(slotPropertyChanged(QtProperty*,QColor)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtColorEditorFactory::createEditor(QtColorPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    QtColorEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QColor)), this, SLOT(slotSetValue(QColor)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtColorEditorFactory::createAttributeEditor(QtColorPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtColorEditorFactory::disconnectPropertyManager(QtColorPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty*,QColor)), this, SLOT(slotPropertyChanged(QtProperty*,QColor)));
}

// QtFontEditWidget

class QtFontEditWidget : public QWidget {
    Q_OBJECT

public:
    QtFontEditWidget(QWidget *parent);

    bool eventFilter(QObject *obj, QEvent *ev);

public Q_SLOTS:
    void setValue(const QFont &value);

Q_SIGNALS:
    void valueChanged(const QFont &value);

protected:
    void paintEvent(QPaintEvent *);

private Q_SLOTS:
    void buttonClicked();

private:
    QFont m_font;
    QLabel *m_pixmapLabel;
    QLabel *m_label;
    QToolButton *m_button;
};

QtFontEditWidget::QtFontEditWidget(QWidget *parent) :
    QWidget(parent),
    m_pixmapLabel(new QLabel),
    m_label(new QLabel),
    m_button(new QToolButton)
{
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(m_pixmapLabel);
    lt->addWidget(m_label);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));

    m_button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    m_button->setFixedWidth(20);
    setFocusProxy(m_button);
    setFocusPolicy(m_button->focusPolicy());
    m_button->setText(tr("..."));
    m_button->installEventFilter(this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    lt->addWidget(m_button);
    m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::fontValuePixmap(m_font));
    m_label->setText(QtPropertyBrowserUtils::fontValueText(m_font));
}

void QtFontEditWidget::setValue(const QFont &f)
{
    if (m_font != f) {
        m_font = f;
        m_pixmapLabel->setPixmap(QtPropertyBrowserUtils::fontValuePixmap(f));
        m_label->setText(QtPropertyBrowserUtils::fontValueText(f));
    }
}

void QtFontEditWidget::buttonClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, m_font, this, tr("Select Font"));
    if (ok && newFont != m_font) {
        QFont f = m_font;
        // prevent mask for unchanged attributes, don't change other attributes (like kerning, etc...)
        if (m_font.family() != newFont.family())
            f.setFamily(newFont.family());
        if (m_font.pointSize() != newFont.pointSize())
            f.setPointSize(newFont.pointSize());
        if (m_font.bold() != newFont.bold())
            f.setBold(newFont.bold());
        if (m_font.italic() != newFont.italic())
            f.setItalic(newFont.italic());
        if (m_font.underline() != newFont.underline())
            f.setUnderline(newFont.underline());
        if (m_font.strikeOut() != newFont.strikeOut())
            f.setStrikeOut(newFont.strikeOut());
        setValue(f);
        emit valueChanged(m_font);
    }
}

bool QtFontEditWidget::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == m_button) {
        switch (ev->type()) {
        case QEvent::KeyPress:
        case QEvent::KeyRelease: { // Prevent the QToolButton from handling Enter/Escape meant control the delegate
            switch (static_cast<const QKeyEvent*>(ev)->key()) {
            case Qt::Key_Escape:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                ev->ignore();
                return true;
            default:
                break;
            }
        }
            break;
        default:
            break;
        }
    }
    return QWidget::eventFilter(obj, ev);
}

void QtFontEditWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// QtFontEditorFactoryPrivate

class QtFontEditorFactoryPrivate : public EditorFactoryPrivate<QtFontEditWidget>
{
    QtFontEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtFontEditorFactory)
public:

    void slotPropertyChanged(QtProperty *property, const QFont &value);
    void slotSetValue(const QFont &value);
    void slotSetCheck(bool check);
};

void QtFontEditorFactoryPrivate::slotPropertyChanged(QtProperty *property,
                const QFont &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        return;
    QtFontPropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QtFontEditWidget *> itEditor(it.value());

    while (itEditor.hasNext())
        itEditor.next()->setValue(value);
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtFontEditorFactoryPrivate::slotSetValue(const QFont &value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtFontPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtFontEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtFontPropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
    \class QtFontEditorFactory

    \brief The QtFontEditorFactory class provides font editing for
    properties created by QtFontPropertyManager objects.

    \sa QtAbstractEditorFactory, QtFontPropertyManager
*/

/*!
    Creates a factory with the given \a parent.
*/
QtFontEditorFactory::QtFontEditorFactory(QObject *parent) :
    QtAbstractEditorFactory<QtFontPropertyManager>(parent),
    d_ptr(new QtFontEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

/*!
    Destroys this factory, and all the widgets it has created.
*/
QtFontEditorFactory::~QtFontEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtFontEditorFactory::connectPropertyManager(QtFontPropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty*,QFont)),
            this, SLOT(slotPropertyChanged(QtProperty*,QFont)));
}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
QWidget *QtFontEditorFactory::createEditor(QtFontPropertyManager *manager,
        QtProperty *property, QWidget *parent)
{
    QtFontEditWidget *editor = d_ptr->createEditor(property, parent);
    editor->setValue(manager->value(property));
    connect(editor, SIGNAL(valueChanged(QFont)), this, SLOT(slotSetValue(QFont)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}



/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtFontEditorFactory::createAttributeEditor(QtFontPropertyManager *manager, QtProperty *property,
                                                  QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
    \internal

    Reimplemented from the QtAbstractEditorFactory class.
*/
void QtFontEditorFactory::disconnectPropertyManager(QtFontPropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty*,QFont)), this, SLOT(slotPropertyChanged(QtProperty*,QFont)));
}

// QtFileEditorFactoryPrivate

class QtFileEditorFactoryPrivate : public EditorFactoryPrivate<QFileEdit>
{
    QtFileEditorFactory *q_ptr;
    Q_DECLARE_PUBLIC(QtFileEditorFactory)
public:
    void slotPropertyChanged(QtProperty *property, const QString &value);
    void slotSetValue(const QString &value);
    void slotFilterChanged(QtProperty *property, const QString &value);
    void slotReadOnlyChanged(QtProperty *property, const bool value);
    void slotSetCheck(bool check);
};

void QtFileEditorFactoryPrivate::slotPropertyChanged(QtProperty *property, const QString &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        return;
    QtFilePropertyManager *manager = q_ptr->propertyManager(property);
    QListIterator<QFileEdit *> itEditor(it.value());

    while (itEditor.hasNext())
        itEditor.next()->setValue(value);
    QList<QtBoolEdit *> checkEditors = m_createdCheckAttributeEditors[property];
    for (unsigned short index = 0; index < checkEditors.size(); ++index ){
        updateCheck(manager, property, checkEditors[index]);
    }
}

void QtFileEditorFactoryPrivate::slotSetValue(const QString &value)
{
    QObject *object = q_ptr->sender();
    const EditorToPropertyMap::ConstIterator ecend = m_editorToProperty.constEnd();
    for (EditorToPropertyMap::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtFilePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setValue(property, value);
            return;
        }
}

void QtFileEditorFactoryPrivate::slotFilterChanged(QtProperty *property, const QString &value)
{
    const PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
    if (it == m_createdEditors.end())
        return;
    QListIterator<QFileEdit *> itEditor(it.value());

    while (itEditor.hasNext())
        itEditor.next()->setValue(value);
}

void QtFileEditorFactoryPrivate::slotReadOnlyChanged( QtProperty *property, bool readOnly)
{
    if (!m_createdEditors.contains(property))
        return;

    QtFilePropertyManager *manager = q_ptr->propertyManager(property);
    if (!manager)
        return;

    QListIterator<QFileEdit *> itEditor(m_createdEditors[property]);
    while (itEditor.hasNext()) {
        QFileEdit *editor = itEditor.next();
        editor->blockSignals(true);
        editor->setReadOnly(readOnly);
        editor->blockSignals(false);
    }
}

void QtFileEditorFactoryPrivate::slotSetCheck(bool check)
{
    QObject *object = q_ptr->sender();
    const QMap<QtBoolEdit *, QtProperty *>::ConstIterator itcend = m_checkAttributeEditorToProperty.constEnd();
    for (QMap<QtBoolEdit *, QtProperty *>::ConstIterator itEditor = m_checkAttributeEditorToProperty.constBegin(); itEditor != itcend; ++itEditor) {
        if (itEditor.key() == object) {
            QtProperty *property = itEditor.value();
            QtFilePropertyManager *manager = q_ptr->propertyManager(property);
            if (!manager)
                return;
            manager->setCheck(property, check);
            slotPropertyChanged(property, manager->value(property));
            return;
        }
    }
}

/*!
 \class QtFileEditorFactory

 \brief The QtFileEditorFactory class provides file editor selection for
 properties created by QtFilePropertyManager objects.

 \sa QtAbstractEditorFactory, QtFilePropertyManager
 */

/*!
 Creates a factory with the given \a parent.
 */
QtFileEditorFactory::QtFileEditorFactory(QObject *parent) :
QtAbstractEditorFactory<QtFilePropertyManager>(parent),
d_ptr(new QtFileEditorFactoryPrivate())
{
    d_ptr->q_ptr = this;
}

/*!
 Destroys this factory, and all the widgets it has created.
 */
QtFileEditorFactory::~QtFileEditorFactory()
{
    qDeleteAll(d_ptr->m_editorToProperty.keys());
    qDeleteAll(d_ptr->m_checkAttributeEditorToProperty.keys());
    delete d_ptr;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtFileEditorFactory::connectPropertyManager(QtFilePropertyManager *manager)
{
    connect(manager, SIGNAL(valueChanged(QtProperty *,const QString &)),
            this, SLOT(slotPropertyChanged(QtProperty *,const QString &)));
    connect(manager, SIGNAL(filterChanged(QtProperty *,const QString &)),
            this, SLOT(slotFilterChanged(QtProperty *,const QString &)));
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtFileEditorFactory::createEditor(QtFilePropertyManager *manager, QtProperty *property, QWidget *parent)
{
    QFileEdit *editor = d_ptr->createEditor(property, parent);
    editor->setFilter(manager->filter(property));
    editor->setFileMode(manager->fileMode(property));
    editor->setValue(manager->value(property));
    editor->setReadOnly(manager->isReadOnly(property));
    connect(editor, SIGNAL(valueChanged(QString)), this, SLOT(slotSetValue(QString)));
    connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotEditorDestroyed(QObject *)));
    return editor;
}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
QWidget *QtFileEditorFactory::createAttributeEditor(QtFilePropertyManager *manager, QtProperty *property,
                                                    QWidget *parent, BrowserCol attribute)
{
    if (attribute == BrowserCol::CHECK)
    {
        if (!manager->attributesEditable(BrowserCol::CHECK))
            return nullptr;
        QtBoolEdit *editor = d_ptr->createCheckAttributeEditor(property, parent);
        updateCheck(manager, property, editor);

        connect(editor, SIGNAL(toggled(bool)), this, SLOT(slotSetCheck(bool)));
        connect(editor, SIGNAL(destroyed(QObject *)), this, SLOT(slotCheckAttributeEditorDestroyed(QObject *)));
        return editor;
    }
    return nullptr;

}

/*!
 \internal

 Reimplemented from the QtAbstractEditorFactory class.
 */
void QtFileEditorFactory::disconnectPropertyManager(QtFilePropertyManager *manager)
{
    disconnect(manager, SIGNAL(valueChanged(QtProperty *,const QString &)),
            this, SLOT(slotPropertyChanged(QtProperty *,const QString &)));
    disconnect(manager, SIGNAL(filterChanged(QtProperty *,const QString &)),
            this, SLOT(slotFilterChanged(QtProperty *,const QString &)));
}

#if QT_VERSION >= 0x040400
QT_END_NAMESPACE
#endif

#include "moc_qteditorfactory.cpp"
#include "qteditorfactory.moc"
