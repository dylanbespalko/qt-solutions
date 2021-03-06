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
#include "qtpropertymanager.h"

#include <QDateTime>
#include <QLocale>
#include <QMap>
#include <QTimer>
#include <QIcon>
#include <QMetaEnum>
#include <QFontDatabase>
#include <QStyleOption>
#include <QStyle>
#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QFileDialog>

#include <limits.h>
#include <float.h>

#if defined(Q_CC_MSVC)
#    pragma warning(disable: 4786) /* MS VS 6: truncating debug info after 255 characters */
#endif

#if QT_VERSION >= 0x040400
QT_BEGIN_NAMESPACE
#endif

//     Return an icon containing a check box indicator
static QIcon drawCheckBox(bool value)
{
    QStyleOptionButton opt;
    opt.state |= value ? QStyle::State_On : QStyle::State_Off;
    opt.state |= QStyle::State_Enabled;
    const QStyle *style = QApplication::style();
    // Figure out size of an indicator and make sure it is not scaled down in a list view item
    // by making the pixmap as big as a list view icon and centering the indicator in it.
    // (if it is smaller, it can't be helped)
    const int indicatorWidth = style->pixelMetric(QStyle::PM_IndicatorWidth, &opt);
    const int indicatorHeight = style->pixelMetric(QStyle::PM_IndicatorHeight, &opt);
    const int listViewIconSize = indicatorWidth;
    const int pixmapWidth = indicatorWidth;
    const int pixmapHeight = qMax(indicatorHeight, listViewIconSize);

    opt.rect = QRect(0, 0, indicatorWidth, indicatorHeight);
    QPixmap pixmap = QPixmap(pixmapWidth, pixmapHeight);
    pixmap.fill(Qt::transparent);
    {
        // Center?
        const int xoff = (pixmapWidth  > indicatorWidth)  ? (pixmapWidth  - indicatorWidth)  / 2 : 0;
        const int yoff = (pixmapHeight > indicatorHeight) ? (pixmapHeight - indicatorHeight) / 2 : 0;
        QPainter painter(&pixmap);
        painter.translate(xoff, yoff);
        style->drawPrimitive(QStyle::PE_IndicatorCheckBox, &opt, &painter);
    }
    return QIcon(pixmap);
}
template <class PrivateData, class Value>
static void setSimpleMinimumData(PrivateData *data, const Value &minVal)
{
    data->minVal = minVal;
    if (data->maxVal < data->minVal)
        data->maxVal = data->minVal;

    if (data->val < data->minVal)
        data->val = data->minVal;
}

template <class PrivateData, class Value>
static void setSimpleMaximumData(PrivateData *data, const Value &maxVal)
{
    data->maxVal = maxVal;
    if (data->minVal > data->maxVal)
        data->minVal = data->maxVal;

    if (data->val > data->maxVal)
        data->val = data->maxVal;
}

template <class PrivateData, class Value>
static void setComplexMinimumData(PrivateData *data, const Value &minVal)
{
    data->minVal = minVal;
    if (data->maxVal < data->minVal)
        data->maxVal = data->minVal;

    if (std::abs(data->val) < data->minVal)
        data->val = QComplex(std::polar(data->minVal, std::arg(data->val)));
}

template <class PrivateData, class Value>
static void setComplexMaximumData(PrivateData *data, const Value &maxVal)
{
    data->maxVal = maxVal;
    if (data->minVal > data->maxVal)
        data->minVal = data->maxVal;

    if (std::abs(data->val) > data->maxVal)
        data->val = QComplex(std::polar(data->maxVal, std::arg(data->val)));
}

template <class PrivateData, class Value>
static void setSizeMinimumData(PrivateData *data, const Value &newMinVal)
{
    data->minVal = newMinVal;
    if (data->maxVal.width() < data->minVal.width())
        data->maxVal.setWidth(data->minVal.width());
    if (data->maxVal.height() < data->minVal.height())
        data->maxVal.setHeight(data->minVal.height());

    if (data->val.width() < data->minVal.width())
    {
        data->val.setWidth(data->minVal.width());
    }
    if (data->val.height() < data->minVal.height())
    {
        data->val.setHeight(data->minVal.height());
    }
}

template <class PrivateData, class Value>
static void setSizeMaximumData(PrivateData *data, const Value &newMaxVal)
{
    data->maxVal = newMaxVal;
    if (data->minVal.width() > data->maxVal.width())
        data->minVal.setWidth(data->maxVal.width());
    if (data->minVal.height() > data->maxVal.height())
        data->minVal.setHeight(data->maxVal.height());

    if (data->val.width() > data->maxVal.width())
    {
        data->val.setWidth(data->maxVal.width());
    }
    if (data->val.height() > data->maxVal.height())
    {
        data->val.setHeight(data->maxVal.height());
    }
}

QComplex qBound(double minVal, const QComplex val, double maxVal)
{
    double rho = qBound(minVal, std::abs(val), maxVal);
    double theta = std::arg(val);
    return  QComplex(std::polar(rho, theta));
}

template <class SizeValue>
static SizeValue qBoundSize(const SizeValue &minVal, const SizeValue &val, const SizeValue &maxVal)
{
    SizeValue croppedVal = val;
    if (minVal.width() > val.width())
        croppedVal.setWidth(minVal.width());
    else if (maxVal.width() < val.width())
        croppedVal.setWidth(maxVal.width());

    if (minVal.height() > val.height())
        croppedVal.setHeight(minVal.height());
    else if (maxVal.height() < val.height())
        croppedVal.setHeight(maxVal.height());

    return croppedVal;
}

QSize qBound(QSize minVal, QSize val, QSize maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

QSizeF qBound(QSizeF minVal, QSizeF val, QSizeF maxVal)
{
    return qBoundSize(minVal, val, maxVal);
}

template <class Value>
QColor qSoftBound(Value minVal, Value val, Value maxVal)
{
    QColor color = QColor(Qt::black);
    if (val <= minVal)
        color = QColor(Qt::blue);
    if (val >= maxVal)
        color = QColor(Qt::red);
    return color;
}

QColor qSoftBound(double minVal, const QComplex val, double maxVal)
{
    double rho = std::abs(val);
    QColor color = QColor(Qt::black);
    if (rho <= minVal)
        color = QColor(Qt::blue);
    if (rho >= maxVal)
        color = QColor(Qt::red);
    return color;
}

template <class SizeValue>
QColor qSoftBoundSize(SizeValue minVal, SizeValue val, SizeValue maxVal)
{
    Q_UNUSED(minVal);
    Q_UNUSED(val);
    Q_UNUSED(maxVal);
    QColor color = QColor(Qt::black);
    return color;
}

QColor qSoftBound(QSize minVal, QSize val, QSize maxVal)
{
    return qSoftBoundSize(minVal, val, maxVal);
}

QColor qSoftBound(QSizeF minVal, QSizeF val, QSizeF maxVal)
{
    return qSoftBoundSize(minVal, val, maxVal);
}

namespace {

namespace {
template <class Value>
void orderBorders(Value &minVal, Value &maxVal)
{
    if (minVal > maxVal)
        qSwap(minVal, maxVal);
}

template <class Value>
static void orderSizeBorders(Value &minVal, Value &maxVal)
{
    Value fromSize = minVal;
    Value toSize = maxVal;
    if (fromSize.width() > toSize.width()) {
        fromSize.setWidth(maxVal.width());
        toSize.setWidth(minVal.width());
    }
    if (fromSize.height() > toSize.height()) {
        fromSize.setHeight(maxVal.height());
        toSize.setHeight(minVal.height());
    }
    minVal = fromSize;
    maxVal = toSize;
}

void orderBorders(QSize &minVal, QSize &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

void orderBorders(QSizeF &minVal, QSizeF &maxVal)
{
    orderSizeBorders(minVal, maxVal);
}

}
}
////////

template <class Value, class PrivateData>
static Value getData(const QMap<const QtProperty *, PrivateData> &propertyMap,
            Value PrivateData::*data,
            const QtProperty *property, const Value &defaultValue = Value())
{
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = propertyMap.constFind(property);
    if (it == propertyMap.constEnd())
        return defaultValue;
    return it.value().*data;
}

template <class Value, class PrivateData>
static Value getValue(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMinimum(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::minVal, property, defaultValue);
}

template <class Value, class PrivateData>
static Value getMaximum(const QMap<const QtProperty *, PrivateData> &propertyMap,
            const QtProperty *property, const Value &defaultValue = Value())
{
    return getData<Value>(propertyMap, &PrivateData::maxVal, property, defaultValue);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setSimpleValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            QtProperty *property, const Value &val,
            void (PropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    PrivateData &data = it.value();

    if (data.val == val)
        return;

    data.val = val;

    if (setSubPropertyValue)
        (managerPrivate->*setSubPropertyValue)(property, data.val);

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setValueInRange(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            QtProperty *property, const Value &val,
            void (PropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    PrivateData &data = it.value();

    if (isclose(val, data.val, data.absTol, data.relTol))
        return;

    const Value oldVal = data.val;
    data.foreground = qSoftBound(data.minVal, val, data.maxVal);
    data.val = val;
    if (!manager->isReadOnly(property))
        data.val = qBound(data.minVal, val, data.maxVal);

    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;

    if (setSubPropertyValue)
        (managerPrivate->*setSubPropertyValue)(property, data.val);

    emit (manager->*propertyChangedSignal)(property);
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value>
static void setBorderValues(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property, const Value &minVal, const Value &maxVal,
            void (PropertyManagerPrivate::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef typename PropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    Value fromVal = minVal;
    Value toVal = maxVal;
    orderBorders(fromVal, toVal);

    PrivateData &data = it.value();

    if (isclose(fromVal, data.minVal, data.absTol, data.relTol) && isclose(toVal, data.maxVal, data.absTol, data.relTol))
        return;

    const Value oldVal = data.val;
    data.setMinimumValue(fromVal);
    data.setMaximumValue(toVal);
    data.foreground = qSoftBound(fromVal, data.val, toVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    emit (manager->*propertyChangedSignal)(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setBorderValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property,
            Value (PrivateData::*getRangeVal)() const,
            void (PrivateData::*setRangeVal)(ValueChangeParameter), const Value &borderVal,
            void (PropertyManagerPrivate::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter))
{
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef typename PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = managerPrivate->m_values.find(property);
    if (it == managerPrivate->m_values.end())
        return;

    PrivateData &data = it.value();
    if (isclose(borderVal, (data.*getRangeVal)(), data.absTol, data.relTol))
        return;

    const Value oldVal = data.val;

    (data.*setRangeVal)(borderVal);
    data.foreground = qSoftBound(data.minVal, data.val, data.maxVal);

    emit (manager->*rangeChangedSignal)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (managerPrivate->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    emit (manager->*propertyChangedSignal)(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit (manager->*valueChangedSignal)(property, data.val);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMinimumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property, const Value &minVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = nullptr;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>(manager, managerPrivate,
            propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
            property, &PropertyManagerPrivate::Data::minimumValue, &PropertyManagerPrivate::Data::setMinimumValue, minVal, setSubPropertyRange);
}

template <class ValueChangeParameter, class PropertyManagerPrivate, class PropertyManager, class Value, class PrivateData>
static void setMaximumValue(PropertyManager *manager, PropertyManagerPrivate *managerPrivate,
            void (PropertyManager::*propertyChangedSignal)(QtProperty *),
            void (PropertyManager::*valueChangedSignal)(QtProperty *, ValueChangeParameter),
            void (PropertyManager::*rangeChangedSignal)(QtProperty *, ValueChangeParameter, ValueChangeParameter),
            QtProperty *property, const Value &maxVal)
{
    void (PropertyManagerPrivate::*setSubPropertyRange)(QtProperty *,
                    ValueChangeParameter, ValueChangeParameter, ValueChangeParameter) = nullptr;
    setBorderValue<ValueChangeParameter, PropertyManagerPrivate, PropertyManager, Value, PrivateData>(manager, managerPrivate,
            propertyChangedSignal, valueChangedSignal, rangeChangedSignal,
            property, &PropertyManagerPrivate::Data::maximumValue, &PropertyManagerPrivate::Data::setMaximumValue, maxVal, setSubPropertyRange);
}

class QtMetaEnumWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSizePolicy::Policy policy READ policy)
public:
    QSizePolicy::Policy policy() const { return QSizePolicy::Ignored; }
private:
    QtMetaEnumWrapper(QObject *parent) : QObject(parent) {}
};

class QtMetaEnumProvider
{
public:
    QtMetaEnumProvider();

    QStringList policyEnumNames() const { return m_policyEnumNames; }
    QStringList languageEnumNames() const { return m_languageEnumNames; }
    QStringList countryEnumNames(QLocale::Language language) const { return m_countryEnumNames.value(language); }

    QSizePolicy::Policy indexToSizePolicy(int index) const;
    int sizePolicyToIndex(QSizePolicy::Policy policy) const;

    void indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const;
    void localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const;

private:
    void initLocale();

    QStringList m_policyEnumNames;
    QStringList m_languageEnumNames;
    QMap<QLocale::Language, QStringList> m_countryEnumNames;
    QMap<int, QLocale::Language> m_indexToLanguage;
    QMap<QLocale::Language, int> m_languageToIndex;
    QMap<int, QMap<int, QLocale::Country> > m_indexToCountry;
    QMap<QLocale::Language, QMap<QLocale::Country, int> > m_countryToIndex;
    QMetaEnum m_policyEnum;
};

#if QT_VERSION < 0x040300

static QList<QLocale::Country> countriesForLanguage(QLocale::Language language)
{
    QList<QLocale::Country> countries;
    QLocale::Country country = QLocale::AnyCountry;
    while (country <= QLocale::LastCountry) {
        QLocale locale(language, country);
        if (locale.language() == language && !countries.contains(locale.country()))
            countries << locale.country();
        country = (QLocale::Country)((uint)country + 1); // ++country
    }
    return countries;
}

#endif

static QList<QLocale::Country> sortCountries(const QList<QLocale::Country> &countries)
{
    QMultiMap<QString, QLocale::Country> nameToCountry;
    QListIterator<QLocale::Country> itCountry(countries);
    while (itCountry.hasNext()) {
        QLocale::Country country = itCountry.next();
        nameToCountry.insert(QLocale::countryToString(country), country);
    }
    return nameToCountry.values();
}

void QtMetaEnumProvider::initLocale()
{
    QMultiMap<QString, QLocale::Language> nameToLanguage;
    QLocale::Language language = QLocale::C;
    while (language <= QLocale::LastLanguage) {
        QLocale locale(language);
        if (locale.language() == language)
            nameToLanguage.insert(QLocale::languageToString(language), language);
        language = static_cast<QLocale::Language>(static_cast<uint>(language) + 1); // ++language
    }

    const QLocale system = QLocale::system();
    if (!nameToLanguage.contains(QLocale::languageToString(system.language())))
        nameToLanguage.insert(QLocale::languageToString(system.language()), system.language());

    QList<QLocale::Language> languages = nameToLanguage.values();
    QListIterator<QLocale::Language> itLang(languages);
    while (itLang.hasNext()) {
        QLocale::Language language = itLang.next();
        QList<QLocale::Country> countries;
#if QT_VERSION < 0x040300
        countries = countriesForLanguage(language);
#else
        countries = QLocale::countriesForLanguage(language);
#endif
        if (countries.isEmpty() && language == system.language())
            countries << system.country();

        if (!countries.isEmpty() && !m_languageToIndex.contains(language)) {
            countries = sortCountries(countries);
            int langIdx = m_languageEnumNames.count();
            m_indexToLanguage[langIdx] = language;
            m_languageToIndex[language] = langIdx;
            QStringList countryNames;
            QListIterator<QLocale::Country> it(countries);
            int countryIdx = 0;
            while (it.hasNext()) {
                QLocale::Country country = it.next();
                countryNames << QLocale::countryToString(country);
                m_indexToCountry[langIdx][countryIdx] = country;
                m_countryToIndex[language][country] = countryIdx;
                ++countryIdx;
            }
            m_languageEnumNames << QLocale::languageToString(language);
            m_countryEnumNames[language] = countryNames;
        }
    }
}

QtMetaEnumProvider::QtMetaEnumProvider()
{
    QMetaProperty p;

    p = QtMetaEnumWrapper::staticMetaObject.property(
                QtMetaEnumWrapper::staticMetaObject.propertyOffset() + 0);
    m_policyEnum = p.enumerator();
    const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
        m_policyEnumNames << QLatin1String(m_policyEnum.key(i));

    initLocale();
}

QSizePolicy::Policy QtMetaEnumProvider::indexToSizePolicy(int index) const
{
    return static_cast<QSizePolicy::Policy>(m_policyEnum.value(index));
}

int QtMetaEnumProvider::sizePolicyToIndex(QSizePolicy::Policy policy) const
{
     const int keyCount = m_policyEnum.keyCount();
    for (int i = 0; i < keyCount; i++)
        if (indexToSizePolicy(i) == policy)
            return i;
    return -1;
}

void QtMetaEnumProvider::indexToLocale(int languageIndex, int countryIndex, QLocale::Language *language, QLocale::Country *country) const
{
    QLocale::Language l = QLocale::C;
    QLocale::Country c = QLocale::AnyCountry;
    if (m_indexToLanguage.contains(languageIndex)) {
        l = m_indexToLanguage[languageIndex];
        if (m_indexToCountry.contains(languageIndex) && m_indexToCountry[languageIndex].contains(countryIndex))
            c = m_indexToCountry[languageIndex][countryIndex];
    }
    if (language)
        *language = l;
    if (country)
        *country = c;
}

void QtMetaEnumProvider::localeToIndex(QLocale::Language language, QLocale::Country country, int *languageIndex, int *countryIndex) const
{
    int l = -1;
    int c = -1;
    if (m_languageToIndex.contains(language)) {
        l = m_languageToIndex[language];
        if (m_countryToIndex.contains(language) && m_countryToIndex[language].contains(country))
            c = m_countryToIndex[language][country];
    }

    if (languageIndex)
        *languageIndex = l;
    if (countryIndex)
        *countryIndex = c;
}

Q_GLOBAL_STATIC(QtMetaEnumProvider, metaEnumProvider)


// QtGroupPropertyManager
class QtGroupPropertyManagerPrivate
{
    QtGroupPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtGroupPropertyManager)
public:

    struct Data
    {
        Data() : val(QCursor()), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QCursor val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QtGroupPropertyManager

    \brief The QtGroupPropertyManager provides and manages group properties.

    This class is intended to provide a grouping element without any value.

    \sa QtAbstractPropertyManager
*/

/*!
    Creates a manager with the given \a parent.
*/
QtGroupPropertyManager::QtGroupPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtGroupPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtGroupPropertyManager::~QtGroupPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtGroupPropertyManager::setCheck
*/
bool QtGroupPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtGroupPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
bool QtGroupPropertyManager::hasValue(const QtProperty *property) const
{
    Q_UNUSED(property)
    return false;
}

/*!
    Sets check status of the property.

    \sa QtGroupPropertyManager::setCheck
*/
void QtGroupPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtGroupPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtGroupPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtGroupPropertyManager::initializeProperty(QtProperty *property)
{
    Q_UNUSED(property)
}

/*!
    \reimp
*/
void QtGroupPropertyManager::uninitializeProperty(QtProperty *property)
{
    Q_UNUSED(property)
}

// QtIntPropertyManager

class QtIntPropertyManagerPrivate
{
    QtIntPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtIntPropertyManager)
public:

    struct Data
    {
        Data()
            : val(0), minVal(-INT_MAX), maxVal(INT_MAX),
              singleStep(1), precision(2), absTol(0), relTol(0),
              readOnly(false), check(false), unit(QString()),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        int val;
        int minVal;
        int maxVal;
        int singleStep;
        int precision;
        int absTol;
        int relTol;
        bool readOnly;
        bool check;
        QString unit;
        QBrush foreground;

        int minimumValue() const { return minVal; }
        int maximumValue() const { return maxVal; }
        void setMinimumValue(int newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(int newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QtIntPropertyManager

    \brief The QtIntPropertyManager provides and manages int properties.

    An int property has a current value, and a range specifying the
    valid values. The range is defined by a minimum and a maximum
    value.

    The property's value and range can be retrieved using the value(),
    minimum() and maximum() functions, and can be set using the
    setValue(), setMinimum() and setMaximum() slots. Alternatively,
    the range can be defined in one go using the setRange() slot.

    In addition, QtIntPropertyManager provides the valueChanged() signal which
    is emitted whenever a property created by this manager changes,
    and the rangeChanged() signal which is emitted whenever such a
    property changes its range of valid values.

    \sa QtAbstractPropertyManager, QtSpinBoxFactory, QtSliderFactory, QtScrollBarFactory
*/

/*!
    \fn void QtIntPropertyManager::valueChanged(QtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtIntPropertyManager::rangeChanged(QtProperty *property, int minimum, int maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid values, passing a pointer to the
    \a property and the new \a minimum and \a maximum values.

    \sa setRange()
*/

/*!
    \fn void QtIntPropertyManager::singleStepChanged(QtProperty *property, int step)

    This signal is emitted whenever a property created by this manager
    changes its single step property, passing a pointer to the
    \a property and the new \a step value

    \sa setSingleStep()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtIntPropertyManager::QtIntPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtIntPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtIntPropertyManager::~QtIntPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa setValue()
*/
int QtIntPropertyManager::value(const QtProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

/*!
    Returns the given \a property's minimum value.

    \sa setMinimum(), maximum(), setRange()
*/
int QtIntPropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<int>(d_ptr->m_values, property, 0);
}

/*!
    Returns the given \a property's maximum value.

    \sa setMaximum(), minimum(), setRange()
*/
int QtIntPropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<int>(d_ptr->m_values, property, 0);
}

/*!
    Returns the given \a property's step value.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa setSingleStep()
*/
int QtIntPropertyManager::singleStep(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtIntPropertyManagerPrivate::Data::singleStep, property, 0);
}

/*!
 Returns the given \a property's precision, in decimals.

 \sa setPrecision()
 */
int QtIntPropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtIntPropertyManagerPrivate::Data::precision, property, 0);
}

/*!
 Returns the given \a property's unit, as a QString.

 \sa setUnit()
 */
QString QtIntPropertyManager::unit(const QtProperty *property) const
{
    return getData<QString>(d_ptr->m_values, &QtIntPropertyManagerPrivate::Data::unit, property, "");
}

/*!
    Returns read-only status of the property.

    When property is read-only it's value can be selected and copied from editor but not modified.

    \sa QtIntPropertyManager::setReadOnly
*/
bool QtIntPropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtIntPropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtIntPropertyManager::check
*/
bool QtIntPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtIntPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
 Returns the given \a property's foreground brush.

 The foreground brush consists of the color and style of the text

 \sa setForeground()
 */
QBrush QtIntPropertyManager::foreground(const QtProperty *property) const
{
    return getData<QBrush>(d_ptr->m_values, &QtIntPropertyManagerPrivate::Data::foreground, property, QBrush(Qt::black, Qt::SolidPattern));
}

/*!
    \reimp
*/
QString QtIntPropertyManager::valueText(const QtProperty *property) const
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
//    return QString::number(it.value().val);
    QtIntPropertyManagerPrivate::Data  data = it.value();
    return QIntEdit::num2str(data.val, Scale::_, Format::RE, data.precision);
}

QString QtIntPropertyManager::minimumText(const QtProperty *property) const
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    QtIntPropertyManagerPrivate::Data  data = it.value();
    return QIntEdit::num2str(data.minVal, Scale::_, Format::RE, data.precision);
}

/*!
 \reimp
 */
QString QtIntPropertyManager::maximumText(const QtProperty *property) const
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    QtIntPropertyManagerPrivate::Data  data = it.value();
    return QIntEdit::num2str(data.maxVal, Scale::_, Format::RE, data.precision);
}

/*!
 \reimp
 */
QString QtIntPropertyManager::unitText(const QtProperty *property) const
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return ScaleNameMap[Scale::_] + it.value().unit;
}

/*!
 \reimp
 */
QIcon QtIntPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtIntPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given \a
    property's range, the \a value is adjusted to the nearest valid
    value within the range.

    \sa value(), setRange(), valueChanged()
*/
void QtIntPropertyManager::setValue(QtProperty *property, int val)
{
    void (QtIntPropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, int) = nullptr;
    setValueInRange<int, QtIntPropertyManagerPrivate, QtIntPropertyManager, int>(this, d_ptr,
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QtIntPropertyManager::setMinimum(QtProperty *property, int minVal)
{
    setMinimumValue<int, QtIntPropertyManagerPrivate, QtIntPropertyManager, int, QtIntPropertyManagerPrivate::Data>(this, d_ptr,
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                &QtIntPropertyManager::rangeChanged,
                property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting maximum value, the minimum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QtIntPropertyManager::setMaximum(QtProperty *property, int maxVal)
{
    setMaximumValue<int, QtIntPropertyManagerPrivate, QtIntPropertyManager, int, QtIntPropertyManagerPrivate::Data>(this, d_ptr,
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                &QtIntPropertyManager::rangeChanged,
                property, maxVal);
}

/*!
    \fn void QtIntPropertyManager::setRange(QtProperty *property, int minimum, int maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtIntPropertyManager::setRange(QtProperty *property, int minVal, int maxVal)
{
    void (QtIntPropertyManagerPrivate::*setSubPropertyRange)(QtProperty *, int, int, int) = nullptr;
    setBorderValues<int, QtIntPropertyManagerPrivate, QtIntPropertyManager, int>(this, d_ptr,
                &QtIntPropertyManager::propertyChanged,
                &QtIntPropertyManager::valueChanged,
                &QtIntPropertyManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

/*!
    Sets the step value for the given \a property to \a step.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa singleStep()
*/
void QtIntPropertyManager::setSingleStep(QtProperty *property, int step)
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtIntPropertyManagerPrivate::Data data = it.value();

    if (step < 0)
        step = 0;

    if (data.singleStep == step)
        return;

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

/*!
 \fn void QtIntPropertyManager::setPrecision(QtProperty *property, int prec)

 Sets the precision of the given \a property to \a prec.

 The valid decimal range is 0-13. The default is 2.

 \sa precision()
 */
void QtIntPropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtIntPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
    prec = 13;
    else if (prec < 0)
    prec = 0;

    if (data.precision == prec)
    return;

    data.precision = prec;

    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
 \fn void QtIntPropertyManager::setUnit(QtProperty *property, QString unit)

 Sets the unit of the given \a property to \a unit.

 \sa unit(), unitChanged()
 */
void QtIntPropertyManager::setUnit(QtProperty *property, const QString& unit)
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtIntPropertyManagerPrivate::Data data = it.value();

    if (data.unit == unit)
    return;

    data.unit = unit;

    it.value() = data;


    emit propertyChanged(property);
    emit unitChanged(property, data.unit);
}

/*!
    Sets read-only status of the property.

    \sa QtIntPropertyManager::setReadOnly
*/
void QtIntPropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtIntPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
    Sets check status of the property.

    \sa QtIntPropertyManager::setCheck
*/
void QtIntPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtIntPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtIntPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtIntPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtIntPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QtIntPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtDoublePropertyManager

class QtDoublePropertyManagerPrivate
{
    QtDoublePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtDoublePropertyManager)
public:

    struct Data
    {
        Data()
            : val(0), minVal(lowest), maxVal(highest),
            singleStep(1), absTol(epsilon), relTol(epsilon),
            precision(2), scale(Scale::_), unit(QString()), format(Format::LIN_DEG), readOnly(false), check(false),
            foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        double val;
        double minVal;
        double maxVal;
        double singleStep;
        double absTol;
        double relTol;
        int precision;
        Scale scale;
        QString unit;
        Format format;
        bool readOnly;
        bool check;
        QBrush foreground;
        double minimumValue() const { return minVal; }
        double maximumValue() const { return maxVal; }
        void setMinimumValue(double newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(double newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QtDoublePropertyManager

    \brief The QtDoublePropertyManager provides and manages double properties.

    A double property has a current value, and a range specifying the
    valid values. The range is defined by a minimum and a maximum
    value.

    The property's value and range can be retrieved using the value(),
    minimum() and maximum() functions, and can be set using the
    setValue(), setMinimum() and setMaximum() slots.
    Alternatively, the range can be defined in one go using the
    setRange() slot.

    In addition, QtDoublePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid values.

    \sa QtAbstractPropertyManager, QtDoubleSpinBoxFactory
*/

/*!
    \fn void QtDoublePropertyManager::valueChanged(QtProperty *property, double value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtDoublePropertyManager::rangeChanged(QtProperty *property, double minimum, double maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid values, passing a pointer to the
    \a property and the new \a minimum and \a maximum values

    \sa setRange()
*/

/*!
    \fn void QtDoublePropertyManager::precisionChanged(QtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setPrecision()
*/

/*!
    \fn void QtDoublePropertyManager::singleStepChanged(QtProperty *property, double step)

    This signal is emitted whenever a property created by this manager
    changes its single step property, passing a pointer to the
    \a property and the new \a step value

    \sa setSingleStep()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtDoublePropertyManager::QtDoublePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtDoublePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys  this manager, and all the properties it has created.
*/
QtDoublePropertyManager::~QtDoublePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa setValue()
*/
double QtDoublePropertyManager::value(const QtProperty *property) const
{
    return getValue<double>(d_ptr->m_values, property, 0.0);
}

/*!
 Returns the given \a property's absTol value.

 \sa relTol()
 */
double QtDoublePropertyManager::absTol(const QtProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::absTol, property, std::numeric_limits<double>::epsilon());
}

/*!
 Returns the given \a property's relTol value.

 \sa absTol()
 */
double QtDoublePropertyManager::relTol(const QtProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::relTol, property, std::numeric_limits<double>::epsilon());
}

/*!
    Returns the given \a property's minimum value.

    \sa maximum(), setRange()
*/
double QtDoublePropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<double>(d_ptr->m_values, property, 0.0);
}

/*!
    Returns the given \a property's maximum value.

    \sa minimum(), setRange()
*/
double QtDoublePropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<double>(d_ptr->m_values, property, 0.0);
}

/*!
    Returns the given \a property's step value.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa setSingleStep()
*/
double QtDoublePropertyManager::singleStep(const QtProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::singleStep, property, 0);
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setPrecision()
*/
int QtDoublePropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::precision, property, 2);
}

/*!
 Returns the given \a property's scale, as a char.

 \sa setScale()
 */
Scale QtDoublePropertyManager::scale(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtDoublePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return Scale::_;
    return it.value().scale;
}

/*!
 Returns the given \a property's unit, as a QString.

 \sa setUnit()
 */
QString QtDoublePropertyManager::unit(const QtProperty *property) const
{
    return getData<QString>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::unit, property, "");
}

/*!
 Returns the given \a property's format setting, as a Format.

 \sa setFormat()
 */
Format QtDoublePropertyManager::format(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtDoublePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return Format::LIN_DEG;
    return it.value().format;
}

/*!
    Returns read-only status of the property.

    When property is read-only it's value can be selected and copied from editor but not modified.

    \sa QtDoublePropertyManager::setReadOnly
*/
bool QtDoublePropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtDoublePropertyManager::setCheck
*/
bool QtDoublePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtDoublePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
 Returns the given \a property's foreground brush.

 The foreground brush consists of the color and style of the text

 \sa setForeground()
 */
QBrush QtDoublePropertyManager::foreground(const QtProperty *property) const
{
    return getData<QBrush>(d_ptr->m_values, &QtDoublePropertyManagerPrivate::Data::foreground, property, QBrush(Qt::black, Qt::SolidPattern));
}

/*!
    \reimp
*/
QString QtDoublePropertyManager::valueText(const QtProperty *property) const
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
//    return QLocale::system().toString(it.value().val, 'f', it.value().precision);
    QtDoublePropertyManagerPrivate::Data  data = it.value();
    return QDoubleEdit::num2str(data.val, data.scale, data.format, data.precision);
}

/*!
 \reimp
 */
QString QtDoublePropertyManager::minimumText(const QtProperty *property) const
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    QtDoublePropertyManagerPrivate::Data  data = it.value();
    return QDoubleEdit::num2str(data.minVal, data.scale, data.format, data.precision);
}

/*!
 \reimp
 */
QString QtDoublePropertyManager::maximumText(const QtProperty *property) const
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    QtDoublePropertyManagerPrivate::Data  data = it.value();
    return QDoubleEdit::num2str(data.maxVal, data.scale, data.format, data.precision);
}

/*!
 \reimp
 */
QString QtDoublePropertyManager::unitText(const QtProperty *property) const
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    switch (it.value().format) {
    case Format::LOG_DEG:
        return QString("dB") + ScaleNameMap[it.value().scale] + it.value().unit;
    default:
        return ScaleNameMap[it.value().scale] + it.value().unit;
    }
}

/*!
 \reimp
 */
QString QtDoublePropertyManager::formatText(const QtProperty *property) const
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return FormatNameMap[it.value().format];
}

/*!
 \reimp
 */
QIcon QtDoublePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtDoublePropertyManager::setValue(QtProperty *property, double value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given
    \a property's range, the \a value is adjusted to the nearest valid value
    within the range.

    \sa value(), setRange(), valueChanged()
*/
void QtDoublePropertyManager::setValue(QtProperty *property, double val)
{
    void (QtDoublePropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, double) = nullptr;
    setValueInRange<double, QtDoublePropertyManagerPrivate, QtDoublePropertyManager, double>(this, d_ptr,
                &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
 Sets the absolute tollerance value for the given \a property to \a absTol.

 \sa relTol(), setAbsTol(), setRelTol()
 */
void QtDoublePropertyManager::setAbsTol(QtProperty *property, double absTol)
{
    typedef QMap<const QtProperty *, QtDoublePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtDoublePropertyManagerPrivate::Data &data = it.value();

    data.absTol = absTol;

    it.value() = data;

    emit propertyChanged(property);
}

/*!
 Sets the relative tollerance value for the given \a property to \a relTol.

 \sa absTol(), setRelTol(), setAbsTol()
 */
void QtDoublePropertyManager::setRelTol(QtProperty *property, double relTol)
{
    typedef QMap<const QtProperty *, QtDoublePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtDoublePropertyManagerPrivate::Data &data = it.value();

    data.relTol = relTol;

    it.value() = data;

    emit propertyChanged(property);
}

/*!
    Sets the step value for the given \a property to \a step.

    The step is typically used to increment or decrement a property value while pressing an arrow key.

    \sa singleStep()
*/
void QtDoublePropertyManager::setSingleStep(QtProperty *property, double step)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (step < 0)
        step = 0;

    if (isclose(step, data.singleStep, data.absTol, data.relTol))
        return;

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

/*!
    Sets read-only status of the property.

    \sa QtDoublePropertyManager::setReadOnly
*/
void QtDoublePropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
    \fn void QtDoublePropertyManager::setPrecision(QtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa precision()
*/
void QtDoublePropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.precision == prec)
        return;

    data.precision = prec;

    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QtDoublePropertyManager::setMinimum(QtProperty *property, double minVal)
{
    setMinimumValue<double, QtDoublePropertyManagerPrivate, QtDoublePropertyManager, double, QtDoublePropertyManagerPrivate::Data>(this, d_ptr,
                &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                &QtDoublePropertyManager::rangeChanged,
                property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting the maximum value, the minimum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QtDoublePropertyManager::setMaximum(QtProperty *property, double maxVal)
{
    setMaximumValue<double, QtDoublePropertyManagerPrivate, QtDoublePropertyManager, double, QtDoublePropertyManagerPrivate::Data>(this, d_ptr,
                &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                &QtDoublePropertyManager::rangeChanged,
                property, maxVal);
}

/*!
    \fn void QtDoublePropertyManager::setRange(QtProperty *property, double minimum, double maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtDoublePropertyManager::setRange(QtProperty *property, double minVal, double maxVal)
{
    void (QtDoublePropertyManagerPrivate::*setSubPropertyRange)(QtProperty *, double, double, double) = nullptr;
    setBorderValues<double, QtDoublePropertyManagerPrivate, QtDoublePropertyManager, double>(this, d_ptr,
                &QtDoublePropertyManager::propertyChanged,
                &QtDoublePropertyManager::valueChanged,
                &QtDoublePropertyManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

/*!
 \fn void QtDoublePropertyManager::setScale(QtProperty *property, Scale scale)

 Sets the scale of the given \a property to \a scale.

 \sa scale(), scaleChanged()
 */
void QtDoublePropertyManager::setScale(QtProperty *property, Scale scale)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (data.scale == scale)
    return;

    data.scale = scale;

    it.value() = data;

    emit propertyChanged(property);
    emit scaleChanged(property, data.scale);
}

/*!
 \fn void QtDoublePropertyManager::setUnit(QtProperty *property, QString unit)

 Sets the unit of the given \a property to \a unit.

 \sa unit(), unitChanged()
 */
void QtDoublePropertyManager::setUnit(QtProperty *property, const QString& unit)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (data.unit == unit)
    return;

    data.unit = unit;

    it.value() = data;


    emit propertyChanged(property);
    emit unitChanged(property, data.unit);
}

/*!
 \fn void QtDoublePropertyManager::setFormat(QtProperty *property, Format format_)

 Sets the format of the given \a property to \a format_.

 \sa format(), formatChanged()
 */
void QtDoublePropertyManager::setFormat(QtProperty *property, Format format_)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (data.format == format_)
    return;

    data.format = format_;

    it.value() = data;

    emit propertyChanged(property);
    emit formatChanged(property, data.format);
}

/*!
    Sets check status of the property.

    \sa QtDoublePropertyManager::setCheck
*/
void QtDoublePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtDoublePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtDoublePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtDoublePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtDoublePropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QtDoublePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtComplexPropertyManager

class QtComplexPropertyManagerPrivate
{
    QtComplexPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtComplexPropertyManager)
public:

    struct Data
    {
        Data()
            : val(QComplex(0.0,0.0)), minVal(0), maxVal(highest),
              singleStep(1), absTol(epsilon), relTol(epsilon),
              precision(2), pkAvg(PkAvg::PK), scale(Scale::_), format(Format::RE_IM), readOnly(false), check(false), unit(QString()),
              foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QComplex val;
        double minVal;
        double maxVal;
        QComplex singleStep;
        double absTol;
        double relTol;
        int precision;
        PkAvg pkAvg;
        Scale scale;
        Format format;
        bool readOnly;
        bool check;
        QString unit;
        QBrush foreground;

        double minimumValue() const { return minVal; }
        double maximumValue() const { return maxVal; }
        void setMinimumValue(double newMinVal) { setComplexMinimumData(this, newMinVal); }
        void setMaximumValue(double newMaxVal) { setComplexMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
 \class QtComplexPropertyManager

 \brief The QtComplexPropertyManager provides and manages complex properties.

 A complex property has a current value, and a range specifying the
 valid values. The range is defined by a minimum and a maximum
 magnitude value.

 The property's value and range can be retrieved using the value(),
 minimum() and maximum() functions, and can be set using the
 setValue(), setMinimum() and setMaximum() slots.
 Alternatively, the range can be defined in one go using the
 setRange() slot.

 In addition, QtComplexPropertyManager provides the valueChanged() signal
 which is emitted whenever a property created by this manager
 changes, and the rangeChanged() signal which is emitted whenever
 such a property changes its range of valid values.

 \sa QtAbstractPropertyManager, QtComplexSpinBoxFactory
 */

/*!
 \fn void QtComplexPropertyManager::valueChanged(QtProperty *property, QComplex value)

 This signal is emitted whenever a property created by this manager
 changes its value, passing a pointer to the \a property and the new
 \a value as parameters.

 \sa setValue()
 */

/*!
 \fn void QtComplexPropertyManager::rangeChanged(QtProperty *property, double minimum, double maximum)

 This signal is emitted whenever a property created by this manager
 changes its range of valid values, passing a pointer to the
 \a property and the new \a minimum and \a maximum values

 \sa setRange()
 */

/*!
 \fn void QtComplexPropertyManager::precisionChanged(QtProperty *property, int prec)

 This signal is emitted whenever a property created by this manager
 changes its precision of value, passing a pointer to the
 \a property and the new \a prec value

 \sa setPrecision()
 */

/*!
 \fn void QtComplexPropertyManager::singleStepChanged(QtProperty *property, double step)

 This signal is emitted whenever a property created by this manager
 changes its single step property, passing a pointer to the
 \a property and the new \a step value

 \sa setSingleStep()
 */

/*!
 Creates a manager with the given \a parent.
 */
QtComplexPropertyManager::QtComplexPropertyManager(QObject *parent)
: QtAbstractPropertyManager(parent)
{
    d_ptr = new QtComplexPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
 Destroys  this manager, and all the properties it has created.
 */
QtComplexPropertyManager::~QtComplexPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
 Returns the given \a property's value.

 If the given property is not managed by this manager, this
 function returns 0.

 \sa setValue()
 */
QComplex QtComplexPropertyManager::value(const QtProperty *property) const
{
    return getValue<QComplex >(d_ptr->m_values, property,QComplex(0.0,0.0));
}

/*!
 Returns the given \a property's absTol value.

 \sa relTol()
 */
double QtComplexPropertyManager::absTol(const QtProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::absTol, property, std::numeric_limits<double>::epsilon());
}

/*!
 Returns the given \a property's relTol value.

 \sa absTol()
 */
double QtComplexPropertyManager::relTol(const QtProperty *property) const
{
    return getData<double>(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::relTol, property, std::numeric_limits<double>::epsilon());
}

/*!
 Returns the given \a property's minimum value.

 \sa maximum(), setRange()
 */
double QtComplexPropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<double>(d_ptr->m_values, property, 0.0);
}

/*!
 Returns the given \a property's maximum value.

 \sa minimum(), setRange()
 */
double QtComplexPropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<double>(d_ptr->m_values, property, 0.0);
}

/*!
 Returns the given \a property's step value.

 The step is typically used to increment or decrement a property value while pressing an arrow key.

 \sa setSingleStep()
 */
QComplex QtComplexPropertyManager::singleStep(const QtProperty *property) const
{
    return getData<QComplex >(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::singleStep, property, QComplex(0.0,0.0));
}

/*!
 Returns the given \a property's precision, in decimals.

 \sa setPrecision()
 */
int QtComplexPropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::precision, property, 0);
}

/*!
 Returns the given \a property's scale, as a Scale.

 \sa setScale()
 */
Scale QtComplexPropertyManager::scale(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return Scale::_;
    return it.value().scale;
}

/*!
 Returns the given \a property's unit, as a QString.

 \sa setUnit()
 */
QString QtComplexPropertyManager::unit(const QtProperty *property) const
{
    return getData<QString>(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::unit, property, "");
}

/*!
 Returns the given \a property's PkAvg setting, as a PkAvg.

 \sa setPkAvg()
 */
PkAvg QtComplexPropertyManager::pkAvg(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return PkAvg::PK;
    return it.value().pkAvg;
}

/*!
 Returns the given \a property's format setting, as a Format.

 \sa setFormat()
 */
Format QtComplexPropertyManager::format(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return Format::RE_IM;
    return it.value().format;
}

/*!
 Returns read-only status of the property.

 When property is read-only it's value can be selected and copied from editor but not modified.

 \sa QtComplexPropertyManager::setReadOnly
 */
bool QtComplexPropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtComplexPropertyManager::setCheck
*/
bool QtComplexPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*Returns the given \a property's foreground brush.

The foreground brush consists of the color and style of the text

\sa setForeground()
*/
QBrush QtComplexPropertyManager::foreground(const QtProperty *property) const
{
    return getData<QBrush>(d_ptr->m_values, &QtComplexPropertyManagerPrivate::Data::foreground, property, QBrush(Qt::black, Qt::SolidPattern));
}

/*!
 \reimp
 */
QString QtComplexPropertyManager::valueText(const QtProperty *property) const
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    QtComplexPropertyManagerPrivate::Data  data = it.value();
    return QComplexEdit::num2str(data.val, data.scale, data.format, data.precision);
}

/*!
 \reimp
 */
QString QtComplexPropertyManager::minimumText(const QtProperty *property) const
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    QtComplexPropertyManagerPrivate::Data  data = it.value();
    return QComplexEdit::num2str(QComplex(data.minVal, 0), data.scale, data.format, data.precision);
}

/*!
 \reimp
 */
QString QtComplexPropertyManager::maximumText(const QtProperty *property) const
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
    return QString();

    QtComplexPropertyManagerPrivate::Data  data = it.value();
    return QComplexEdit::num2str(QComplex(data.maxVal, 0), data.scale, data.format, data.precision);
}

/*!
 \reimp
 */
QString QtComplexPropertyManager::unitText(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::UNIT))
        return QString();
    const QtComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    switch (it.value().format) {
        case Format::LOG_DEG:
            return QString("dB") + ScaleNameMap[it.value().scale] + it.value().unit;
        default:
            return ScaleNameMap[it.value().scale] + it.value().unit;
    }
}

/*!
 \reimp
 */
QString QtComplexPropertyManager::pkAvgText(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::PKAVG))
        return QString();
    const QtComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    switch (it.value().pkAvg) {
        case PkAvg::PK:
            return QString("pk");
        default:
            return QString("avg");
    }
}

/*!
 \reimp
 */
QString QtComplexPropertyManager::formatText(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::FORMAT))
        return QString();
    const QtComplexPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    switch (it.value().format) {
        case Format::RE:
            return QString("Re");
        case Format::RE_IM:
            return QString("Re+Imj");
        case Format::LOG_DEG:
            return QString("Log") + QString(QChar(0x2220)) + QString("Deg");
        default:
            return QString("Lin") + QString(QChar(0x2220)) + QString("Deg");
    }
}

/*!
 \reimp
 */
QIcon QtComplexPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
 \fn void QtComplexPropertyManager::setValue(QtProperty *property, double value)

 Sets the value of the given \a property to \a value.

 If the specified \a value is not valid according to the given
 \a property's range, the \a value is adjusted to the nearest valid value
 within the range.

 \sa value(), setRange(), valueChanged()
 */
void QtComplexPropertyManager::setValue(QtProperty *property, const QComplex& val)
{
    void (QtComplexPropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, const QComplex&) = nullptr;
        setValueInRange<const QComplex&, QtComplexPropertyManagerPrivate, QtComplexPropertyManager, const QComplex>(this, d_ptr,
                    &QtComplexPropertyManager::propertyChanged,
                    &QtComplexPropertyManager::valueChanged,
                    property, val, setSubPropertyValue);
}

/*!
 Sets the step value for the given \a property to \a step.

 The step is typically used to increment or decrement a property value while pressing an arrow key.

 \sa singleStep()
 */
void QtComplexPropertyManager::setSingleStep(QtProperty *property, const QComplex& step)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (isclose<double>(std::real(data.singleStep), std::real(step), data.absTol, data.relTol) &&
        isclose<double>(std::imag(data.singleStep), std::imag(step), data.absTol, data.relTol)){
        return;
    }

    data.singleStep = step;

    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

/*!
 Sets read-only status of the property.

 \sa QtComplexPropertyManager::setReadOnly
 */
void QtComplexPropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
 \fn void QtComplexPropertyManager::setPrecision(QtProperty *property, int prec)

 Sets the precision of the given \a property to \a prec.

 The valid decimal range is 0-13. The default is 2.

 \sa precision()
 */
void QtComplexPropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();
    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.precision == prec)
        return;

    data.precision = prec;

    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
 Sets the absolute tollerance value for the given \a property to \a absTol.

 \sa relTol(), setAbsTol(), setRelTol()
 */
void QtComplexPropertyManager::setAbsTol(QtProperty *property, double absTol)
{
    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtComplexPropertyManagerPrivate::Data &data = it.value();

    data.absTol = absTol;

    it.value() = data;

    emit propertyChanged(property);
}

/*!
 Sets the relative tollerance value for the given \a property to \a relTol.

 \sa absTol(), setRelTol(), setAbsTol()
 */
void QtComplexPropertyManager::setRelTol(QtProperty *property, double relTol)
{
    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtComplexPropertyManagerPrivate::Data &data = it.value();

    data.relTol = relTol;

    it.value() = data;

    emit propertyChanged(property);
}

/*!
 Sets the minimum value for the given \a property to \a minVal.

 When setting the minimum value, the maximum and current values are
 adjusted if necessary (ensuring that the range remains valid and
 that the current value is within in the range).

 \sa minimum(), setRange(), rangeChanged()
 */
void QtComplexPropertyManager::setMinimum(QtProperty *property, double minVal)
{
    void (QtComplexPropertyManagerPrivate::*setSubPropertyRange)(QtProperty *,
                                                            double, double, QComplex) = nullptr;

    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data &data = it.value();

    if (isclose<double>(data.minVal, minVal, data.absTol, data.relTol)){
        return;
    }

    const QComplex oldVal = data.val;

    data.setMinimumValue(minVal);
    data.foreground = qSoftBound(data.minVal, data.val, data.maxVal);

    emit (this->rangeChanged)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (d_ptr->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 Sets the maximum value for the given \a property to \a maxVal.

 When setting the maximum value, the minimum and current values are
 adjusted if necessary (ensuring that the range remains valid and
 that the current value is within in the range).

 \sa maximum(), setRange(), rangeChanged()
 */
void QtComplexPropertyManager::setMaximum(QtProperty *property, double maxVal)
{
    void (QtComplexPropertyManagerPrivate::*setSubPropertyRange)(QtProperty *,
                                                                 double, double, QComplex) = nullptr;

    typedef QMap<const QtProperty *, QtComplexPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data &data = it.value();

    if (isclose<double>(data.maxVal, maxVal, data.absTol, data.relTol)){
        return;
    }

    const QComplex oldVal = data.val;

    data.setMaximumValue(maxVal);
    data.foreground = qSoftBound(data.minVal, data.val, data.maxVal);

    emit (this->rangeChanged)(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (d_ptr->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 \fn void QtComplexPropertyManager::setRange(QtProperty *property, double minimum, double maximum)

 Sets the range of valid values.

 This is a convenience function defining the range of valid values
 in one go; setting the \a minimum and \a maximum values for the
 given \a property with a single function call.

 When setting a new range, the current value is adjusted if
 necessary (ensuring that the value remains within range).

 \sa setMinimum(), setMaximum(), rangeChanged()
 */
void QtComplexPropertyManager::setRange(QtProperty *property, double minVal, double maxVal)
{
    void (QtComplexPropertyManagerPrivate::*setSubPropertyRange)(QtProperty *, double, double, QComplex) = nullptr;

    typedef QtComplexPropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    double fromVal = minVal;
    double toVal = maxVal;
    orderBorders(fromVal, toVal);

    PrivateData &data = it.value();

    if (isclose<double>(data.minVal, minVal, data.absTol, data.relTol) &&
        isclose<double>(data.maxVal, maxVal, data.absTol, data.relTol)){
        return;
    }

    const QComplex oldVal = data.val;

    data.setMinimumValue(fromVal);
    data.setMaximumValue(toVal);
    data.foreground = qSoftBound(data.minVal, data.val, data.maxVal);

    emit rangeChanged(property, data.minVal, data.maxVal);

    if (setSubPropertyRange)
        (d_ptr->*setSubPropertyRange)(property, data.minVal, data.maxVal, data.val);

    emit propertyChanged(property);
    if (isclose<double>(std::real(data.val), std::real(oldVal), data.absTol, data.relTol) &&
        isclose<double>(std::imag(data.val), std::imag(oldVal), data.absTol, data.relTol)){
        return;
    }
    emit valueChanged(property, data.val);
}

/*!
 \fn void QtComplexPropertyManager::setScale(QtProperty *property, Scale scale)

 Sets the scale of the given \a property to \a Scale.

 \sa scale(), scaleChanged()
 */
void QtComplexPropertyManager::setScale(QtProperty *property, Scale scale)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (data.scale == scale)
        return;

    data.scale = scale;

    it.value() = data;

    emit propertyChanged(property);
    emit scaleChanged(property, data.scale);
}

/*!
 \fn void QtComplexPropertyManager::setUnit(QtProperty *property, QString unit)

 Sets the unit of the given \a property to \a unit.

 \sa unit(), unitChanged()
 */
void QtComplexPropertyManager::setUnit(QtProperty *property, const QString& unit)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (data.unit == unit)
        return;

    data.unit = unit;

    it.value() = data;


    emit propertyChanged(property);
    emit unitChanged(property, data.unit);
}

/*!
 \fn void QtComplexPropertyManager::setPkAvg(QtProperty *property, PkAvg pkAvg)

 Sets the PkAvg of the given \a property to \a pkAvg.

 \sa pkAvg(), pkAvgChanged()
 */
void QtComplexPropertyManager::setPkAvg(QtProperty *property, PkAvg pkAvg)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (data.pkAvg == pkAvg)
        return;

    data.pkAvg = pkAvg;

    it.value() = data;

    emit propertyChanged(property);
    emit pkAvgChanged(property, data.pkAvg);
}

/*!
 \fn void QtComplexPropertyManager::setFormat(QtProperty *property, Format format_)

 Sets the format of the given \a property to \a format_.

 \sa format(), formatChanged()
 */
void QtComplexPropertyManager::setFormat(QtProperty *property, Format format_)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (data.format == format_)
        return;

    data.format = format_;

    it.value() = data;

    emit propertyChanged(property);
    emit formatChanged(property, data.format);
}

/*!
    Sets check status of the property.

    \sa QtComplexPropertyManager::setCheck
*/
void QtComplexPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtComplexPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtComplexPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
 \reimp
 */
void QtComplexPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtComplexPropertyManagerPrivate::Data();
}

/*!
 \reimp
 */
void QtComplexPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtComplexArrayPropertyManager

class QtTFTensorPropertyManagerPrivate
{
    QtTFTensorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtTFTensorPropertyManager)
public:
    void slotComplexChanged(QtProperty *property, const QComplex& value);
    void slotRangeChanged(QtProperty *sub_property, const double min, const double max);
    void slotPropertyDestroyed(QtProperty *property);

    struct Data
    {
        Data()
            :val(QVector<QComplex>(0)), minVal(QVector<double>(0)), maxVal(QVector<double>(0)),
             singleStep(QVector<QComplex>(0)), absTol(QVector<double>(0)), relTol(QVector<double>(0)),
             size(0), precision(2), scale(Scale::_), pkAvg(PkAvg::PK),format(Format::RE_IM), readOnly(false), check(false), unit(QString()),
             foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QVector<QComplex> val;
        QVector<double> minVal;
        QVector<double> maxVal;
        QVector<QComplex> singleStep;
        QVector<double> absTol;
        QVector<double> relTol;
        int size;
        int precision;
        Scale scale;
        PkAvg pkAvg;
        Format format;
        bool readOnly;
        bool check;
        QString unit;
        QBrush foreground;

        std::vector<QtProperty *> subProperties;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
    QtComplexPropertyManager *m_complexPropertyManager;
    QMap<const QtProperty *, QtProperty *> m_subToProperty;
};

void QtTFTensorPropertyManagerPrivate::slotComplexChanged(QtProperty *sub_property, const QComplex& value)
{
    QtProperty *property = m_subToProperty.value(sub_property);
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it =m_values.find(property);
    if (it == m_values.end())
        return;

    for (unsigned short index = 0; index < it.value().val.size(); index++) {
        if (it.value().subProperties[index] == sub_property){
            QVector<QComplex> values = it.value().val;
            values[index] = value;
            q_ptr->setValue(property, values);
            break;
        }
    }
}

void QtTFTensorPropertyManagerPrivate::slotRangeChanged(QtProperty *sub_property, const double min, const double max)
{
    QtProperty *property = m_subToProperty.value(sub_property);
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it =m_values.find(property);
    if (it == m_values.end())
        return;

    for (unsigned short index = 0; index < it.value().val.size(); index++) {
        if (it.value().subProperties[index] == sub_property){
            QVector<double> minimum = it.value().minVal;
            QVector<double> maximum = it.value().maxVal;
            minimum[index] = min;
            maximum[index] = max;
            q_ptr->setRange(property, minimum, maximum);
            break;
        }
    }
}

void QtTFTensorPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *sub_property)
{
    QtProperty *property = m_subToProperty.value(sub_property);
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it =m_values.find(property);
    if (it == m_values.end())
        return;

    for (unsigned short index = ushort(it.value().val.size()); index > 0; index--) {
        if (it.value().subProperties[index-1] == sub_property){
            it.value().subProperties[index-1] = nullptr;
            m_subToProperty.remove(sub_property);
        }
    }
}

/*!
 \class QtComplexArrayPropertyManager

 \brief The QtComplexArrayPropertyManager provides and manages QRectF properties.

 A rectangle property has nested \e x, \e y, \e width and \e height
 subproperties. The top-level property's value can be retrieved
 using the value() function, and set using the setValue() slot.

 The subproperties are created by a QtComplexPropertyManager object. This
 manager can be retrieved using the subDoublePropertyManager() function. In
 order to provide editing widgets for the subproperties in a
 property browser widget, this manager must be associated with an
 editor factory.

 A rectangle property also has a constraint rectangle which can be
 retrieved using the constraint() function, and set using the
 setConstraint() slot.

 In addition, QtComplexArrayPropertyManager provides the valueChanged() signal
 which is emitted whenever a property created by this manager
 changes, and the constraintChanged() signal which is emitted
 whenever such a property changes its constraint rectangle.

 \sa QtAbstractPropertyManager, QtComplexPropertyManager, QtRectPropertyManager
 */

/*!
 \fn void QtComplexArrayPropertyManager::valueChanged(QtProperty *property, const QRectF &value)

 This signal is emitted whenever a property created by this manager
 changes its value, passing a pointer to the \a property and the new
 \a value as parameters.

 \sa setValue()
 */

/*!
 \fn void QtComplexArrayPropertyManager::constraintChanged(QtProperty *property, const QRectF &constraint)

 This signal is emitted whenever property changes its constraint
 rectangle, passing a pointer to the \a property and the new \a
 constraint rectangle as parameters.

 \sa setConstraint()
 */

/*!
 \fn void QtComplexArrayPropertyManager::precisionChanged(QtProperty *property, int prec)

 This signal is emitted whenever a property created by this manager
 changes its precision of value, passing a pointer to the
 \a property and the new \a prec value

 \sa setPrecision()
 */

/*!
 Creates a manager with the given \a parent.
 */
QtTFTensorPropertyManager::QtTFTensorPropertyManager(QObject *parent)
: QtAbstractPropertyManager(parent)
{
    d_ptr = new QtTFTensorPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_complexPropertyManager = new QtComplexPropertyManager(this);
    d_ptr->m_complexPropertyManager->setAttributesEditable(BrowserCol::UNIT, false);
    d_ptr->m_complexPropertyManager->setAttributesEditable(BrowserCol::PKAVG, false);
    d_ptr->m_complexPropertyManager->setAttributesEditable(BrowserCol::FORMAT, false);
    d_ptr->m_complexPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect_signals();
}

/*!
 Destroys this manager, and all the properties it has created.
 */
QtTFTensorPropertyManager::~QtTFTensorPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
 Connect the signals to the slots.

 \sa connect_signals()
 */
void QtTFTensorPropertyManager::connect_signals() const
{
    connect(d_ptr->m_complexPropertyManager, SIGNAL(valueChanged(QtProperty *, QComplex)),
            this, SLOT(slotComplexChanged(QtProperty *, QComplex)));
    connect(d_ptr->m_complexPropertyManager, SIGNAL(rangeChanged(QtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    connect(d_ptr->m_complexPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
            this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
 Disconnect the signals from the slots.

 \sa disconnect_signals()
 */
void QtTFTensorPropertyManager::disconnect_signals() const
{
    disconnect(d_ptr->m_complexPropertyManager, SIGNAL(valueChanged(QtProperty *, QComplex)),
            this, SLOT(slotComplexChanged(QtProperty *, QComplex)));
    disconnect(d_ptr->m_complexPropertyManager, SIGNAL(rangeChanged(QtProperty *, double, double)),
            this, SLOT(slotRangeChanged(QtProperty *, double, double)));
    disconnect(d_ptr->m_complexPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
            this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
 Returns the manager that creates the nested \e x, \e y, \e width
 and \e height subproperties.

 In order to provide editing widgets for the mentioned
 subproperties in a property browser widget, this manager must be
 associated with an editor factory.

 \sa QtAbstractPropertyBrowser::setFactoryForManager()
 */
QtComplexPropertyManager *QtTFTensorPropertyManager::subComplexPropertyManager() const
{
    return d_ptr->m_complexPropertyManager;
}

/*!
 Returns the given \a property's value.

 If the given \a property is not managed by this manager, this
 function returns an invalid rectangle.

 \sa setValue(), constraint()
 */
QVector<QComplex> QtTFTensorPropertyManager::value(const QtProperty *property) const
{
    return getData<QVector<QComplex> >(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::val, property, QVector<QComplex>(0));
}

/*!
 Returns the given \a property's absTol value.

 \sa absTol()
 */
QVector<double> QtTFTensorPropertyManager::absTol(const QtProperty *property) const
{
    return getData<QVector<double> >(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::absTol, property, QVector<double>(0));
}

/*!
 Returns the given \a property's relTol value.

 \sa relTol()
 */
QVector<double> QtTFTensorPropertyManager::relTol(const QtProperty *property) const
{
    return getData<QVector<double> >(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::relTol, property, QVector<double>(0));
}

/*!
 Returns the given \a property's minimum value.

 \sa maximum(), setRange()
 */
QVector<double> QtTFTensorPropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<QVector<double> >(d_ptr->m_values, property, QVector<double>(0.0));
}

/*!
 Returns the given \a property's maximum value.

 \sa minimum(), setRange()
 */
QVector<double> QtTFTensorPropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<QVector<double> >(d_ptr->m_values, property, QVector<double>(0.0));
}

/*!
 Returns the given \a property's step value.

 The step is typically used to increment or decrement a property value while pressing an arrow key.

 \sa setSingleStep()
 */
QVector<QComplex> QtTFTensorPropertyManager::singleStep(const QtProperty *property) const
{
    return getData<QVector<QComplex> >(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::singleStep, property, QVector<QComplex>(0));
}

/*!
 Returns the given \a property's size.

 \sa setSize()
 */
int QtTFTensorPropertyManager::size(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::size, property, 0);
}

/*!
 Returns the given \a property's precision, in decimals.

 \sa setPrecision()
 */
int QtTFTensorPropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::precision, property, 0);
}

/*!
 Returns the given \a property's scale, as a Scale.

 \sa setScale()
 */
Scale QtTFTensorPropertyManager::scale(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return Scale::_;
    return it.value().scale;
}

/*!
 Returns the given \a property's unit, as a QString.

 \sa setUnit()
 */
QString QtTFTensorPropertyManager::unit(const QtProperty *property) const
{
    return getData<QString>(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::unit, property, "");
}

/*!
 Returns the given \a property's PkAvg setting, as a PkAvg.

 \sa setPkAvg()
 */
PkAvg QtTFTensorPropertyManager::pkAvg(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return PkAvg::PK;
    return it.value().pkAvg;
}

/*!
 Returns the given \a property's format setting, as a Format.

 \sa setFormat()
 */
Format QtTFTensorPropertyManager::format(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return Format::RE_IM;
    return it.value().format;
}

/*!
 Returns read-only status of the property.

 When property is read-only it's value can be selected and copied from editor but not modified.

 \sa QtComplexArrayPropertyManager::setReadOnly
 */
bool QtTFTensorPropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtTFTensorPropertyManager::setCheck
*/
bool QtTFTensorPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*Returns the given \a property's foreground brush.

 The foreground brush consists of the color and style of the text

 \sa setForeground()
 */
QBrush QtTFTensorPropertyManager::foreground(const QtProperty *property) const
{
    return getData<QBrush>(d_ptr->m_values, &QtTFTensorPropertyManagerPrivate::Data::foreground, property, QBrush(Qt::black, Qt::SolidPattern));
}

/*!
 \reimp
 */
QString QtTFTensorPropertyManager::valueText(const QtProperty *property) const
{
    QString text = QString("");
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    QtTFTensorPropertyManagerPrivate::Data  data = it.value();
    for (unsigned short idx=0; idx < data.val.size(); idx++) {
        text += QComplexEdit::num2str(data.val[idx],data.scale,data.format, data.precision);
        if (idx != data.val.size()-1)
            text += ", ";
    }
    text = "[" + text + "]";
    return text;
}

/*!
 \reimp
 */
QString QtTFTensorPropertyManager::pkAvgText(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::PKAVG))
        return QString();
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    switch (it.value().pkAvg) {
        case PkAvg::PK:
            return QString("pk");
        default:
            return QString("avg");
    }
}

/*!
 \reimp
 */
QString QtTFTensorPropertyManager::formatText(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::FORMAT))
        return QString();
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    switch (it.value().format) {
        case Format::RE:
            return QString("Re");
        case Format::RE_IM:
            return QString("Re+Imj");
        case Format::LOG_DEG:
            return QString("Log") + QString(QChar(0x2220)) + QString("Deg");
        default:
            return QString("Lin") + QString(QChar(0x2220)) + QString("Deg");
    }
}

/*!
 \reimp
 */
QString QtTFTensorPropertyManager::unitText(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::UNIT))
        return QString();
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    switch (it.value().format) {
        case Format::LOG_DEG:
            return QString("dB") + ScaleNameMap[it.value().scale] + it.value().unit;
        default:
            return ScaleNameMap[it.value().scale] + it.value().unit;
    }
}

/*!
 \reimp
 */
QIcon QtTFTensorPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
 \fn void QtComplexArrayPropertyManager::setValue(QtProperty *property, const QRectF &value)

 Sets the value of the given \a property to \a value. Nested
 properties are updated automatically.

 If the specified \a value is not inside the given \a property's
 constraining rectangle, the value is adjusted accordingly to fit
 within the constraint.

 \sa value(), setConstraint(), valueChanged()
 */
void QtTFTensorPropertyManager::setValue(QtProperty *property, const QVector<QComplex> &val)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.val.size() == 0){
        data.val = val;
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    disconnect_signals();
    QVector<QComplex> oldVal = data.val;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        QtProperty *subProperty = it.value().subProperties[index];
        d_ptr->m_complexPropertyManager->setValue(subProperty, val[index]);
        data.val[index] = d_ptr->m_complexPropertyManager->value(subProperty);
    }
    connect_signals();
    it.value() = data;

    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 Sets the step value for the given \a property to \a step.

 The step is typically used to increment or decrement a property value while pressing an arrow key.

 \sa singleStep()
 */
void QtTFTensorPropertyManager::setSingleStep(QtProperty *property, const QVector<QComplex>& step)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.val.size() == 0){
        data.val = QVector<QComplex>(step.size());
        for (unsigned short index=0; index < data.val.size(); index++){
            data.val[index] = 0;
        }
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    for (unsigned short index=0; index < it.value().val.size(); index++) {
        QtProperty *subProperty = it.value().subProperties[index];
        d_ptr->m_complexPropertyManager->setSingleStep(subProperty, step[index]);
        data.val[index] = d_ptr->m_complexPropertyManager->value(subProperty);
        data.singleStep[index] = d_ptr->m_complexPropertyManager->singleStep(subProperty);
    }
    it.value() = data;

    emit singleStepChanged(property, data.singleStep);
}

/*!
 Sets read-only status of the property.

 \sa QtComplexArrayPropertyManager::setReadOnly
 */
void QtTFTensorPropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setReadOnly(it.value().subProperties[index],readOnly);
    }
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
 \fn void QtComplexArrayPropertyManager::setSize(QtProperty *property, int size)

 Sets the precision of the given \a property to \a size.

 \sa size()
 */
void QtTFTensorPropertyManager::setSize(QtProperty *property, int size)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.size == size)
        return;

    const QVector<QComplex> oldVal = data.val;
    data.size = size;
    data.val = QVector<QComplex>(size);
    it.value() = data;
    reinitializeProperty(property);

    emit sizeChanged(property, data.size);
    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 \fn void QtComplexArrayPropertyManager::setPrecision(QtProperty *property, int prec)

 Sets the precision of the given \a property to \a prec.

 The valid decimal range is 0-13. The default is 2.

 \sa precision()
 */
void QtTFTensorPropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.precision == prec)
        return;

    data.precision = prec;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setPrecision(it.value().subProperties[index],prec);
    }
    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
 Sets the absolute tollerance value for the given \a property to \a absTol.

 \sa relTol(), setAbsTol(), setRelTol()
 */
void QtTFTensorPropertyManager::setAbsTol(QtProperty *property, const QVector<double>& absTol)
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtTFTensorPropertyManagerPrivate::Data &data = it.value();

    if (data.val.size() == 0){
        data.val = QVector<QComplex>(absTol.size());
        for (unsigned short index=0; index < data.val.size(); index++){
            data.val[index] = 0;
        }
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    data.absTol = absTol;
    it.value() = data;

    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setAbsTol(it.value().subProperties[index],data.absTol[index]);
    }

    emit propertyChanged(property);
}

/*!
 Sets the relative tollerance value for the given \a property to \a relTol.

 \sa absTol(), setRelTol(), setAbsTol()
 */
void QtTFTensorPropertyManager::setRelTol(QtProperty *property, const QVector<double>& relTol)
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
    return;

    QtTFTensorPropertyManagerPrivate::Data &data = it.value();

    if (data.val.size() == 0){
        data.val = QVector<QComplex>(relTol.size());
        for (unsigned short index=0; index < data.val.size(); index++){
            data.val[index] = 0;
        }
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    data.relTol = relTol;
    it.value() = data;

    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setRelTol(it.value().subProperties[index],data.relTol[index]);
    }

    emit propertyChanged(property);
}

/*!
 Sets the minimum value for the given \a property to \a minVal.

 When setting the minimum value, the maximum and current values are
 adjusted if necessary (ensuring that the range remains valid and
 that the current value is within in the range).

 \sa minimum(), setRange(), rangeChanged()
 */
void QtTFTensorPropertyManager::setMinimum(QtProperty *property, const QVector<double>& minVal)
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data &data = it.value();

    if (data.val.size() == 0){
        data.val = QVector<QComplex>(minVal.size());
        for (unsigned short index=0; index < data.val.size(); index++){
            data.val[index] = 0;
        }
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    QVector<QComplex> oldVal = data.val;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        QtProperty *subProperty = it.value().subProperties[index];
        d_ptr->m_complexPropertyManager->setMinimum(subProperty, minVal[index]);
        data.val[index] = d_ptr->m_complexPropertyManager->value(subProperty);
        data.minVal[index] = d_ptr->m_complexPropertyManager->minimum(subProperty);
    }

    emit rangeChanged(property, data.minVal, data.maxVal);
    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 Sets the maximum value for the given \a property to \a maxVal.

 When setting the maximum value, the minimum and current values are
 adjusted if necessary (ensuring that the range remains valid and
 that the current value is within in the range).

 \sa maximum(), setRange(), rangeChanged()
 */
void QtTFTensorPropertyManager::setMaximum(QtProperty *property, const QVector<double>& maxVal)
{
    typedef QMap<const QtProperty *, QtTFTensorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data &data = it.value();

    if (data.val.size() == 0){
        data.val = QVector<QComplex>(maxVal.size());
        for (unsigned short index=0; index < data.val.size(); index++){
            data.val[index] = 0;
        }
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    const QVector<QComplex> oldVal = data.val;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        QtProperty *subProperty = it.value().subProperties[index];
        d_ptr->m_complexPropertyManager->setMaximum(subProperty,maxVal[index]);
        data.val[index] = d_ptr->m_complexPropertyManager->value(subProperty);
        data.maxVal[index] = d_ptr->m_complexPropertyManager->maximum(subProperty);
    }

    emit rangeChanged(property, data.minVal, data.maxVal);
    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 \fn void QtComplexArrayPropertyManager::setRange(QtProperty *property, double minimum, double maximum)

 Sets the range of valid values.

 This is a convenience function defining the range of valid values
 in one go; setting the \a minimum and \a maximum values for the
 given \a property with a single function call.

 When setting a new range, the current value is adjusted if
 necessary (ensuring that the value remains within range).

 \sa setMinimum(), setMaximum(), rangeChanged()
 */
void QtTFTensorPropertyManager::setRange(QtProperty *property, const QVector<double>& minVal, const QVector<double>& maxVal)
{
    typedef QtTFTensorPropertyManagerPrivate::Data PrivateData;
    typedef QMap<const QtProperty *, PrivateData> PropertyToData;
    typedef PropertyToData::iterator PropertyToDataIterator;
    const PropertyToDataIterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QVector<double> fromVal = minVal;
    QVector<double> toVal = maxVal;
    orderBorders(fromVal, toVal);

    PrivateData &data = it.value();

    if (data.val.size() == 0){
        data.val = QVector<QComplex>(maxVal.size());
        for (unsigned short index=0; index < data.val.size(); index++){
            data.val[index] = 0;
        }
        it.value() = data;
        reinitializeProperty(property);
        data = it.value();
    }

    const QVector<QComplex> oldVal = data.val;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        QtProperty *subProperty = it.value().subProperties[index];
        d_ptr->m_complexPropertyManager->setRange(subProperty, minVal[index], maxVal[index]);
        data.val[index] = d_ptr->m_complexPropertyManager->value(subProperty);
        data.minVal[index] = d_ptr->m_complexPropertyManager->minimum(subProperty);
        data.maxVal[index] = d_ptr->m_complexPropertyManager->maximum(subProperty);
    }

    emit rangeChanged(property, data.minVal, data.maxVal);
    emit propertyChanged(property);
    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;
    emit valueChanged(property, data.val);
}

/*!
 \fn void QtComplexArrayPropertyManager::setScale(QtProperty *property, Scale scale)

 Sets the scale of the given \a property to \a scale.

 \sa scale(), scaleChanged()
 */
void QtTFTensorPropertyManager::setScale(QtProperty *property, Scale scale)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.scale == scale)
        return;

    data.scale = scale;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setScale(it.value().subProperties[index],scale);
    }
    it.value() = data;

    emit propertyChanged(property);
    emit scaleChanged(property, data.scale);
}

/*!
 \fn void QtComplexArrayPropertyManager::setUnit(QtProperty *property, QString unit)

 Sets the unit of the given \a property to \a unit.

 \sa unit(), unitChanged()
 */
void QtTFTensorPropertyManager::setUnit(QtProperty *property, QString unit)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.unit == unit)
        return;

    data.unit = unit;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setUnit(it.value().subProperties[index], unit);
    }
    it.value() = data;

    emit propertyChanged(property);
    emit unitChanged(property, data.unit);
}

/*!
 \fn void QtComplexArrayPropertyManager::setPkAvg(QtProperty *property, PkAvg pkAvg)

 Sets the PkAvg of the given \a property to \a pkAvg.

 \sa pkAvg(), pkAvgChanged()
 */
void QtTFTensorPropertyManager::setPkAvg(QtProperty *property, PkAvg pkAvg)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.pkAvg == pkAvg)
        return;

    data.pkAvg = pkAvg;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setPkAvg(it.value().subProperties[index], pkAvg);
    }
    it.value() = data;

    emit propertyChanged(property);
    emit pkAvgChanged(property, data.pkAvg);
}

/*!
 \fn void QtComplexArrayPropertyManager::setFormat(QtProperty *property, Format format_)

 Sets the format of the given \a property to \a format_.

 \sa format(), formatChanged()
 */
void QtTFTensorPropertyManager::setFormat(QtProperty *property, Format format_)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.format == format_)
        return;

    data.format = format_;
    for (unsigned short index=0; index < it.value().val.size(); index++) {
        d_ptr->m_complexPropertyManager->setFormat(it.value().subProperties[index], format_);
    }
    it.value() = data;

    emit propertyChanged(property);
    emit formatChanged(property, data.format);
}

/*!
    Sets check status of the property.

    \sa QtTFTensorPropertyManager::setCheck
*/
void QtTFTensorPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
 \reimp
 */
void QtTFTensorPropertyManager::reinitializeProperty(QtProperty *property)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTFTensorPropertyManagerPrivate::Data data = it.value();

    data.absTol = QVector<double>(data.val.size());
    data.relTol = QVector<double>(data.val.size());
    data.minVal = QVector<double>(data.val.size());
    data.maxVal = QVector<double>(data.val.size());
    data.singleStep = QVector<QComplex>(data.val.size());
    for (unsigned short index=0; index < data.val.size(); index++) {
        data.absTol[index] = std::numeric_limits<double>::epsilon();
        data.relTol[index] = std::numeric_limits<double>::epsilon();
        data.minVal[index] = 0;
        data.maxVal[index] = LONG_MAX;
        data.singleStep[index] = 1;
    }
    it.value() = data;
    it.value().subProperties = std::vector<QtProperty *>(ushort(data.val.size()));

    for (unsigned short index=0; index < data.val.size(); index++) {
        QtProperty *subProp = d_ptr->m_complexPropertyManager->addProperty();
        subProp->setPropertyName("[" + QString::number(index) + "]");
        d_ptr->m_complexPropertyManager->setPrecision(subProp, precision(property));
        d_ptr->m_complexPropertyManager->setValue(subProp, it.value().val[index]);
        d_ptr->m_complexPropertyManager->setReadOnly(subProp, it.value().readOnly);
        it.value().subProperties[index] = subProp;
        d_ptr->m_subToProperty[subProp] = property;
        property->addSubProperty(subProp);
    }
}

/*!
 \reimp
 */
void QtTFTensorPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtTFTensorPropertyManagerPrivate::Data();
}

/*!
 \reimp
 */
void QtTFTensorPropertyManager::uninitializeProperty(QtProperty *property)
{
    const QtTFTensorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QVector<QComplex> value = it.value().val;
    for (unsigned short index=ushort(value.size()); index >0; index--) {
        QtProperty *subProp = it.value().subProperties[index-1];
        if (subProp) {
            d_ptr->m_subToProperty.remove(subProp);
            delete subProp;
        }
        it.value().subProperties[index-1] = nullptr;
    }
    d_ptr->m_values.remove(property);
}

// QtStringPropertyManager

class QtStringPropertyManagerPrivate
{
    QtStringPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtStringPropertyManager)
public:

    struct Data
    {
        Data() : regExp(QString(QLatin1Char('*')),  Qt::CaseSensitive, QRegExp::Wildcard),
                 absTol(QString()), relTol(QString()),
                 echoMode(QLineEdit::Normal), readOnly(false), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QString val;
        QRegExp regExp;
        QString absTol;
        QString relTol;
        int echoMode;
        bool readOnly;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;
};

/*!
    \class QtStringPropertyManager

    \brief The QtStringPropertyManager provides and manages QString properties.

    A string property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The current value can be checked against a regular expression. To
    set the regular expression use the setRegExp() slot, use the
    regExp() function to retrieve the currently set expression.

    In addition, QtStringPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the regExpChanged() signal which is emitted whenever
    such a property changes its currently set regular expression.

    \sa QtAbstractPropertyManager, QtLineEditFactory
*/

/*!
    \fn void QtStringPropertyManager::valueChanged(QtProperty *property, const QString &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtStringPropertyManager::regExpChanged(QtProperty *property, const QRegExp &regExp)

    This signal is emitted whenever a property created by this manager
    changes its currenlty set regular expression, passing a pointer to
    the \a property and the new \a regExp as parameters.

    \sa setRegExp()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtStringPropertyManager::QtStringPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtStringPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtStringPropertyManager::~QtStringPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns an empty string.

    \sa setValue()
*/
QString QtStringPropertyManager::value(const QtProperty *property) const
{
    return getValue<QString>(d_ptr->m_values, property, QString());
}

/*!
    Returns the given \a property's currently set regular expression.

    If the given \a property is not managed by this manager, this
    function returns an empty expression.

    \sa setRegExp()
*/
QRegExp QtStringPropertyManager::regExp(const QtProperty *property) const
{
    return getData<QRegExp>(d_ptr->m_values, &QtStringPropertyManagerPrivate::Data::regExp, property, QRegExp());
}

/*!
    \reimp
*/
EchoMode QtStringPropertyManager::echoMode(const QtProperty *property) const
{
    return static_cast<EchoMode>(getData<int>(d_ptr->m_values, &QtStringPropertyManagerPrivate::Data::echoMode, property, 0));
}

/*!
    Returns read-only status of the property.

    When property is read-only it's value can be selected and copied from editor but not modified.

    \sa QtStringPropertyManager::setReadOnly
*/
bool QtStringPropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtStringPropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtStringPropertyManager::setCheck
*/
bool QtStringPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtStringPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtStringPropertyManager::valueText(const QtProperty *property) const
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return it.value().val;
}

/*!
    \reimp
*/
QString QtStringPropertyManager::displayText(const QtProperty *property) const
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    QLineEdit edit;
    edit.setEchoMode(static_cast<EchoMode>(it.value().echoMode));
    edit.setText(it.value().val);
    return edit.displayText();
}

/*!
 \reimp
 */
QIcon QtStringPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtStringPropertyManager::setValue(QtProperty *property, const QString &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value doesn't match the given \a property's
    regular expression, this function does nothing.

    \sa value(), setRegExp(), valueChanged()
*/
void QtStringPropertyManager::setValue(QtProperty *property, const QString &val)
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtStringPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
        return;

    if (data.regExp.isValid() && !data.regExp.exactMatch(val))
        return;

    data.val = val;

    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the regular expression of the given \a property to \a regExp.

    \sa regExp(), setValue(), regExpChanged()
*/
void QtStringPropertyManager::setRegExp(QtProperty *property, const QRegExp &regExp)
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtStringPropertyManagerPrivate::Data data = it.value() ;

    if (data.regExp == regExp)
        return;

    data.regExp = regExp;

    it.value() = data;

    emit regExpChanged(property, data.regExp);
}


void QtStringPropertyManager::setEchoMode(QtProperty *property, EchoMode echoMode)
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtStringPropertyManagerPrivate::Data data = it.value();

    if (data.echoMode == echoMode)
        return;

    data.echoMode = echoMode;
    it.value() = data;

    emit propertyChanged(property);
    emit echoModeChanged(property, data.echoMode);
}

/*!
    Sets read-only status of the property.

    \sa QtStringPropertyManager::setReadOnly
*/
void QtStringPropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtStringPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
    Sets check status of the property.

    \sa QtStringPropertyManager::setCheck
*/
void QtStringPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtStringPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtStringPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtStringPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtStringPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QtStringPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtBoolPropertyManager
//     Return an icon containing a check box indicator
class QtBoolPropertyManagerPrivate
{
    QtBoolPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtBoolPropertyManager)
public:
    QtBoolPropertyManagerPrivate();

    struct Data
    {
        Data() : val(false), textVisible(true),
                 check(false), absTol(QString()), relTol(QString()),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        bool val;
        bool textVisible;
        bool check;
        QString absTol;
        QString relTol;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    const QIcon m_checkedIcon;
    const QIcon m_uncheckedIcon;
};

QtBoolPropertyManagerPrivate::QtBoolPropertyManagerPrivate() :
    m_checkedIcon(drawCheckBox(true)),
    m_uncheckedIcon(drawCheckBox(false))
{
}

/*!
    \class QtBoolPropertyManager

    \brief The QtBoolPropertyManager class provides and manages boolean properties.

    The property's value can be retrieved using the value() function,
    and set using the setValue() slot.

    In addition, QtBoolPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtCheckBoxFactory
*/

/*!
    \fn void QtBoolPropertyManager::valueChanged(QtProperty *property, bool value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QtBoolPropertyManager::QtBoolPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtBoolPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtBoolPropertyManager::~QtBoolPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns false.

    \sa setValue()
*/
bool QtBoolPropertyManager::value(const QtProperty *property) const
{
    return getValue<bool>(d_ptr->m_values, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtBoolPropertyManager::setCheck
*/
bool QtBoolPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtBoolPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

bool QtBoolPropertyManager::textVisible(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtBoolPropertyManagerPrivate::Data::textVisible, property, false);
}

/*!
    \reimp
*/
QString QtBoolPropertyManager::valueText(const QtProperty *property) const
{
    const QtBoolPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QtBoolPropertyManagerPrivate::Data &data = it.value();
    if (!data.textVisible)
        return QString();

    static const QString trueText = tr("True");
    static const QString falseText = tr("False");
    return data.val ? trueText : falseText;
}

/*!
    \reimp
*/
QIcon QtBoolPropertyManager::valueIcon(const QtProperty *property) const
{
    const QtBoolPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return it.value().val ? d_ptr->m_checkedIcon : d_ptr->m_uncheckedIcon;
}

/*!
 \reimp
 */
QIcon QtBoolPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtBoolPropertyManager::setValue(QtProperty *property, bool value)

    Sets the value of the given \a property to \a value.

    \sa value()
*/
void QtBoolPropertyManager::setValue(QtProperty *property, bool val)
{
    const QtBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtBoolPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
        return;

    data.val = val;
    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

void QtBoolPropertyManager::setTextVisible(QtProperty *property, bool textVisible)
{
    const QtBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtBoolPropertyManagerPrivate::Data data = it.value();

    if (data.textVisible == textVisible)
        return;

    data.textVisible = textVisible;
    it.value() = data;

    emit propertyChanged(property);
    emit textVisibleChanged(property, data.textVisible);
}

/*!
    Sets check status of the property.

    \sa QtBoolPropertyManager::setCheck
*/
void QtBoolPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtBoolPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtBoolPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtBoolPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtBoolPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QtBoolPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtDatePropertyManager

class QtDatePropertyManagerPrivate
{
    QtDatePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtDatePropertyManager)
public:

    struct Data
    {
        Data() : val(QDate::currentDate()), minVal(QDate(1752, 9, 14)), maxVal(QDate(7999, 12, 31)),
                 absTol(QDate(1752, 9, 14)), relTol(QDate(1752, 9, 14)), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QDate val;
        QDate minVal;
        QDate maxVal;
        QDate absTol;
        QDate relTol;
        bool check;
        QBrush foreground;
        QDate minimumValue() const { return minVal; }
        QDate maximumValue() const { return maxVal; }
        void setMinimumValue(const QDate &newMinVal) { setSimpleMinimumData(this, newMinVal); }
        void setMaximumValue(const QDate &newMaxVal) { setSimpleMaximumData(this, newMaxVal); }
    };

    QString m_format;

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;
};

/*!
    \class QtDatePropertyManager

    \brief The QtDatePropertyManager provides and manages QDate properties.

    A date property has a current value, and a range specifying the
    valid dates. The range is defined by a minimum and a maximum
    value.

    The property's values can be retrieved using the minimum(),
    maximum() and value() functions, and can be set using the
    setMinimum(), setMaximum() and setValue() slots. Alternatively,
    the range can be defined in one go using the setRange() slot.

    In addition, QtDatePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid dates.

    \sa QtAbstractPropertyManager, QtDateEditFactory, QtDateTimePropertyManager
*/

/*!
    \fn void QtDatePropertyManager::valueChanged(QtProperty *property, const QDate &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtDatePropertyManager::rangeChanged(QtProperty *property, const QDate &minimum, const QDate &maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid dates, passing a pointer to the \a
    property and the new \a minimum and \a maximum dates.

    \sa setRange()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtDatePropertyManager::QtDatePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtDatePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.dateFormat(QLocale::ShortFormat);
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtDatePropertyManager::~QtDatePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns an invalid date.

    \sa setValue()
*/
QDate QtDatePropertyManager::value(const QtProperty *property) const
{
    return getValue<QDate>(d_ptr->m_values, property, QDate::currentDate());
}

/*!
    Returns the given \a  property's  minimum date.

    \sa maximum(), setRange()
*/
QDate QtDatePropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<QDate>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's maximum date.

    \sa minimum(), setRange()
*/
QDate QtDatePropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<QDate>(d_ptr->m_values, property);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtDatePropertyManager::setCheck
*/
bool QtDatePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtDatePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtDatePropertyManager::valueText(const QtProperty *property) const
{
    const QtDatePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return it.value().val.toString(d_ptr->m_format);
}

/*!
 \reimp
 */
QIcon QtDatePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtDatePropertyManager::setValue(QtProperty *property, const QDate &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not a valid date according to the
    given \a property's range, the value is adjusted to the nearest
    valid value within the range.

    \sa value(), setRange(), valueChanged()
*/
void QtDatePropertyManager::setValue(QtProperty *property, const QDate &val)
{
    void (QtDatePropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, const QDate &) = nullptr;
    setValueInRange<const QDate &, QtDatePropertyManagerPrivate, QtDatePropertyManager, const QDate>(this, d_ptr,
                &QtDatePropertyManager::propertyChanged,
                &QtDatePropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets the minimum value for the given \a property to \a minVal.

    When setting the minimum value, the maximum and current values are
    adjusted if necessary (ensuring that the range remains valid and
    that the current value is within in the range).

    \sa minimum(), setRange()
*/
void QtDatePropertyManager::setMinimum(QtProperty *property, const QDate &minVal)
{
    setMinimumValue<const QDate &, QtDatePropertyManagerPrivate, QtDatePropertyManager, QDate, QtDatePropertyManagerPrivate::Data>(this, d_ptr,
                &QtDatePropertyManager::propertyChanged,
                &QtDatePropertyManager::valueChanged,
                &QtDatePropertyManager::rangeChanged,
                property, minVal);
}

/*!
    Sets the maximum value for the given \a property to \a maxVal.

    When setting the maximum value, the minimum and current
    values are adjusted if necessary (ensuring that the range remains
    valid and that the current value is within in the range).

    \sa maximum(), setRange()
*/
void QtDatePropertyManager::setMaximum(QtProperty *property, const QDate &maxVal)
{
    setMaximumValue<const QDate &, QtDatePropertyManagerPrivate, QtDatePropertyManager, QDate, QtDatePropertyManagerPrivate::Data>(this, d_ptr,
                &QtDatePropertyManager::propertyChanged,
                &QtDatePropertyManager::valueChanged,
                &QtDatePropertyManager::rangeChanged,
                property, maxVal);
}

/*!
    \fn void QtDatePropertyManager::setRange(QtProperty *property, const QDate &minimum, const QDate &maximum)

    Sets the range of valid dates.

    This is a convenience function defining the range of valid dates
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new date range, the current value is adjusted if
    necessary (ensuring that the value remains in date range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtDatePropertyManager::setRange(QtProperty *property, const QDate &minVal, const QDate &maxVal)
{
    void (QtDatePropertyManagerPrivate::*setSubPropertyRange)(QtProperty *, const QDate &,
          const QDate &, const QDate &) = nullptr;
    setBorderValues<const QDate &, QtDatePropertyManagerPrivate, QtDatePropertyManager, QDate>(this, d_ptr,
                &QtDatePropertyManager::propertyChanged,
                &QtDatePropertyManager::valueChanged,
                &QtDatePropertyManager::rangeChanged,
                property, minVal, maxVal, setSubPropertyRange);
}

/*!
    Sets check status of the property.

    \sa QtDatePropertyManager::setCheck
*/
void QtDatePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtDatePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtDatePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtDatePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtDatePropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QtDatePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtTimePropertyManager

class QtTimePropertyManagerPrivate
{
    QtTimePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtTimePropertyManager)
public:

    struct Data
    {
        Data()
            : val(QTime::currentTime()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QTime val;
        bool check;
        QBrush foreground;
    };

    QString m_format;

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;
};

/*!
    \class QtTimePropertyManager

    \brief The QtTimePropertyManager provides and manages QTime properties.

    A time property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QtTimePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtTimeEditFactory
*/

/*!
    \fn void QtTimePropertyManager::valueChanged(QtProperty *property, const QTime &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtTimePropertyManager::QtTimePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtTimePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.timeFormat(QLocale::ShortFormat);
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtTimePropertyManager::~QtTimePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns an invalid time object.

    \sa setValue()
*/
QTime QtTimePropertyManager::value(const QtProperty *property) const
{
    return getValue<QTime>(d_ptr->m_values, property, QTime::currentTime());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtTimePropertyManager::setCheck
*/
bool QtTimePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtTimePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtTimePropertyManager::valueText(const QtProperty *property) const
{
   const QtTimePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return getValue<QTime>(d_ptr->m_values, property, QTime::currentTime()).toString(d_ptr->m_format);
}

/*!
 \reimp
 */
QIcon QtTimePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtTimePropertyManager::setValue(QtProperty *property, const QTime &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QtTimePropertyManager::setValue(QtProperty *property, const QTime &val)
{
    void (QtTimePropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, const QTime &) = nullptr;
    setSimpleValue<const QTime &, QtTimePropertyManagerPrivate, QtTimePropertyManager, const QTime>(this, d_ptr,
                &QtTimePropertyManager::propertyChanged,
                &QtTimePropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets check status of the property.

    \sa QtTimePropertyManager::setCheck
*/
void QtTimePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtTimePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtTimePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtTimePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property].val = QTime::currentTime();
}

/*!
    \reimp
*/
void QtTimePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtDateTimePropertyManager

class QtDateTimePropertyManagerPrivate
{
    QtDateTimePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtDateTimePropertyManager)
public:

    struct Data
    {
        Data()
            : val(QDateTime::currentDateTime()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QDateTime val;
        bool check;
        QBrush foreground;
    };

    QString m_format;

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;
};

/*! \class QtDateTimePropertyManager

    \brief The QtDateTimePropertyManager provides and manages QDateTime properties.

    A date and time property has a current value which can be
    retrieved using the value() function, and set using the setValue()
    slot. In addition, QtDateTimePropertyManager provides the
    valueChanged() signal which is emitted whenever a property created
    by this manager changes.

    \sa QtAbstractPropertyManager, QtDateTimeEditFactory, QtDatePropertyManager
*/

/*!
    \fn void QtDateTimePropertyManager::valueChanged(QtProperty *property, const QDateTime &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QtDateTimePropertyManager::QtDateTimePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtDateTimePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    QLocale loc;
    d_ptr->m_format = loc.dateFormat(QLocale::ShortFormat);
    d_ptr->m_format += QLatin1Char(' ');
    d_ptr->m_format += loc.timeFormat(QLocale::ShortFormat);
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtDateTimePropertyManager::~QtDateTimePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid QDateTime object.

    \sa setValue()
*/
QDateTime QtDateTimePropertyManager::value(const QtProperty *property) const
{
    return getValue<QDateTime>(d_ptr->m_values, property, QDateTime::currentDateTime());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtDateTimePropertyManager::setCheck
*/
bool QtDateTimePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtDateTimePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtDateTimePropertyManager::valueText(const QtProperty *property) const
{
   const QtDateTimePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return getValue<QDateTime>(d_ptr->m_values, property, QDateTime::currentDateTime()).toString(d_ptr->m_format);
}

/*!
 \reimp
 */
QIcon QtDateTimePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtDateTimePropertyManager::setValue(QtProperty *property, const QDateTime &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QtDateTimePropertyManager::setValue(QtProperty *property, const QDateTime &val)
{
    void (QtDateTimePropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, const QDateTime &) = nullptr;
    setSimpleValue<const QDateTime &, QtDateTimePropertyManagerPrivate, QtDateTimePropertyManager, const QDateTime>(this, d_ptr,
                &QtDateTimePropertyManager::propertyChanged,
                &QtDateTimePropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets check status of the property.

    \sa QtDateTimePropertyManager::setCheck
*/
void QtDateTimePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtDateTimePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtDateTimePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtDateTimePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property].val = QDateTime::currentDateTime();
}

/*!
    \reimp
*/
void QtDateTimePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtKeySequencePropertyManager

class QtKeySequencePropertyManagerPrivate
{
    QtKeySequencePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtKeySequencePropertyManager)
public:

    struct Data
    {
        Data()
            : val(QKeySequence()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QKeySequence val;
        bool check;
        QBrush foreground;
    };

    QString m_format;

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;
};

/*! \class QtKeySequencePropertyManager

    \brief The QtKeySequencePropertyManager provides and manages QKeySequence properties.

    A key sequence's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QtKeySequencePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager
*/

/*!
    \fn void QtKeySequencePropertyManager::valueChanged(QtProperty *property, const QKeySequence &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QtKeySequencePropertyManager::QtKeySequencePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtKeySequencePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtKeySequencePropertyManager::~QtKeySequencePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an empty QKeySequence object.

    \sa setValue()
*/
QKeySequence QtKeySequencePropertyManager::value(const QtProperty *property) const
{
    return getValue<QKeySequence>(d_ptr->m_values, property, QKeySequence());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtKeySequencePropertyManager::setCheck
*/
bool QtKeySequencePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtKeySequencePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtKeySequencePropertyManager::valueText(const QtProperty *property) const
{
    const QtKeySequencePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    return getValue<QKeySequence>(d_ptr->m_values, property, QKeySequence()).toString(QKeySequence::NativeText);
}

/*!
 \reimp
 */
QIcon QtKeySequencePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtKeySequencePropertyManager::setValue(QtProperty *property, const QKeySequence &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QtKeySequencePropertyManager::setValue(QtProperty *property, const QKeySequence &val)
{
    void (QtKeySequencePropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, const QKeySequence &) = nullptr;
    setSimpleValue<const QKeySequence &, QtKeySequencePropertyManagerPrivate, QtKeySequencePropertyManager, const QKeySequence>(this, d_ptr,
                &QtKeySequencePropertyManager::propertyChanged,
                &QtKeySequencePropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets check status of the property.

    \sa QtKeySequencePropertyManager::setCheck
*/
void QtKeySequencePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtKeySequencePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtKeySequencePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtKeySequencePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property].val = QKeySequence();
}

/*!
    \reimp
*/
void QtKeySequencePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtCharPropertyManager

class QtCharPropertyManagerPrivate
{
    QtCharPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtCharPropertyManager)
public:

    struct Data
    {
        Data()
            : val(QChar()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QChar val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;
};

/*! \class QtCharPropertyManager

    \brief The QtCharPropertyManager provides and manages QChar properties.

    A char's value can be retrieved using the value()
    function, and set using the setValue() slot.

    In addition, QtCharPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager
*/

/*!
    \fn void QtCharPropertyManager::valueChanged(QtProperty *property, const QChar &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.
*/

/*!
    Creates a manager with the given \a parent.
*/
QtCharPropertyManager::QtCharPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtCharPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtCharPropertyManager::~QtCharPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an null QChar object.

    \sa setValue()
*/
QChar QtCharPropertyManager::value(const QtProperty *property) const
{
    return getValue<QChar>(d_ptr->m_values, property, QChar());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtCharPropertyManager::setCheck
*/
bool QtCharPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtCharPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtCharPropertyManager::valueText(const QtProperty *property) const
{
   const QtCharPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QChar c = getValue<QChar>(d_ptr->m_values, property, QChar());
    return c.isNull() ? QString() : QString(c);
}

/*!
 \reimp
 */
QIcon QtCharPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtCharPropertyManager::setValue(QtProperty *property, const QChar &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QtCharPropertyManager::setValue(QtProperty *property, const QChar &val)
{
    void (QtCharPropertyManagerPrivate::*setSubPropertyValue)(QtProperty *, const QChar &) = nullptr;
    setSimpleValue<const QChar &, QtCharPropertyManagerPrivate, QtCharPropertyManager, const QChar>(this, d_ptr,
                &QtCharPropertyManager::propertyChanged,
                &QtCharPropertyManager::valueChanged,
                property, val, setSubPropertyValue);
}

/*!
    Sets check status of the property.

    \sa QtCharPropertyManager::setCheck
*/
void QtCharPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtCharPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtCharPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtCharPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property].val = QChar();
}

/*!
    \reimp
*/
void QtCharPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtLocalePropertyManager

class QtLocalePropertyManagerPrivate
{
    QtLocalePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtLocalePropertyManager)
public:

    struct Data
    {
        Data()
            : val(QLocale()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QLocale val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;

    QtLocalePropertyManagerPrivate();

    void slotEnumChanged(QtProperty *property, int value);
    void slotPropertyDestroyed(QtProperty *property);

    QtEnumPropertyManager *m_enumPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToLanguage;
    QMap<const QtProperty *, QtProperty *> m_propertyToCountry;

    QMap<const QtProperty *, QtProperty *> m_languageToProperty;
    QMap<const QtProperty *, QtProperty *> m_countryToProperty;
};

QtLocalePropertyManagerPrivate::QtLocalePropertyManagerPrivate()
{
}

void QtLocalePropertyManagerPrivate::slotEnumChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_languageToProperty.value(property, nullptr)) {
        const QLocale loc = m_values[prop].val;
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        metaEnumProvider()->indexToLocale(value, 0, &newLanguage, nullptr);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    } else if (QtProperty *prop = m_countryToProperty.value(property, nullptr)) {
        const QLocale loc = m_values[prop].val;
        QLocale::Language newLanguage = loc.language();
        QLocale::Country newCountry = loc.country();
        metaEnumProvider()->indexToLocale(m_enumPropertyManager->value(m_propertyToLanguage.value(prop)), value, &newLanguage, &newCountry);
        QLocale newLoc(newLanguage, newCountry);
        q_ptr->setValue(prop, newLoc);
    }
}

void QtLocalePropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *subProp = m_languageToProperty.value(property, nullptr)) {
        m_propertyToLanguage[subProp] = nullptr;
        m_languageToProperty.remove(property);
    } else if (QtProperty *subProp = m_countryToProperty.value(property, nullptr)) {
        m_propertyToCountry[subProp] = nullptr;
        m_countryToProperty.remove(property);
    }
}

/*!
    \class QtLocalePropertyManager

    \brief The QtLocalePropertyManager provides and manages QLocale properties.

    A locale property has nested \e language and \e country
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by QtEnumPropertyManager object.
    These submanager can be retrieved using the subEnumPropertyManager()
    function. In order to provide editing widgets for the subproperties
    in a property browser widget, this manager must be associated with editor factory.

    In addition, QtLocalePropertyManager provides the valueChanged()
    signal which is emitted whenever a property created by this
    manager changes.

    \sa QtAbstractPropertyManager, QtEnumPropertyManager
*/

/*!
    \fn void QtLocalePropertyManager::valueChanged(QtProperty *property, const QLocale &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtLocalePropertyManager::QtLocalePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtLocalePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_enumPropertyManager = new QtEnumPropertyManager(this);
    d_ptr->m_enumPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotEnumChanged(QtProperty *, int)));

    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtLocalePropertyManager::~QtLocalePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e language
    and \e country subproperties.

    In order to provide editing widgets for the mentioned subproperties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtEnumPropertyManager *QtLocalePropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns the default locale.

    \sa setValue()
*/
QLocale QtLocalePropertyManager::value(const QtProperty *property) const
{
    return getValue<QLocale>(d_ptr->m_values, property, QLocale());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtLocalePropertyManager::setCheck
*/
bool QtLocalePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtLocalePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtLocalePropertyManager::valueText(const QtProperty *property) const
{
    const QtLocalePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    QLocale loc = getValue<QLocale>(d_ptr->m_values, property, QLocale());

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(loc.language(), loc.country(), &langIdx, &countryIdx);
    QString str = tr("%1, %2")
            .arg(metaEnumProvider()->languageEnumNames().at(langIdx))
            .arg(metaEnumProvider()->countryEnumNames(loc.language()).at(countryIdx));
    return str;
}

/*!
 \reimp
 */
QIcon QtLocalePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtLocalePropertyManager::setValue(QtProperty *property, const QLocale &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtLocalePropertyManager::setValue(QtProperty *property, const QLocale &val)
{
    const QtLocalePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    const QLocale loc = getValue<QLocale>(d_ptr->m_values, property, QLocale());
    if (loc == val)
        return;

    it.value().val = val;

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);
    if (loc.language() != val.language()) {
        d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToLanguage.value(property), langIdx);
        d_ptr->m_enumPropertyManager->setEnumNames(d_ptr->m_propertyToCountry.value(property),
                    metaEnumProvider()->countryEnumNames(val.language()));
    }
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToCountry.value(property), countryIdx);

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    Sets check status of the property.

    \sa QtLocalePropertyManager::setCheck
*/
void QtLocalePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtLocalePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtLocalePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtLocalePropertyManager::initializeProperty(QtProperty *property)
{
    QLocale val;
    d_ptr->m_values[property].val = val;

    int langIdx = 0;
    int countryIdx = 0;
    metaEnumProvider()->localeToIndex(val.language(), val.country(), &langIdx, &countryIdx);

    QtProperty *languageProp = d_ptr->m_enumPropertyManager->addProperty();
    languageProp->setPropertyName(tr("Language"));
    d_ptr->m_enumPropertyManager->setEnumNames(languageProp, metaEnumProvider()->languageEnumNames());
    d_ptr->m_enumPropertyManager->setValue(languageProp, langIdx);
    d_ptr->m_propertyToLanguage[property] = languageProp;
    d_ptr->m_languageToProperty[languageProp] = property;
    property->addSubProperty(languageProp);

    QtProperty *countryProp = d_ptr->m_enumPropertyManager->addProperty();
    countryProp->setPropertyName(tr("Country"));
    d_ptr->m_enumPropertyManager->setEnumNames(countryProp, metaEnumProvider()->countryEnumNames(val.language()));
    d_ptr->m_enumPropertyManager->setValue(countryProp, countryIdx);
    d_ptr->m_propertyToCountry[property] = countryProp;
    d_ptr->m_countryToProperty[countryProp] = property;
    property->addSubProperty(countryProp);
}

/*!
    \reimp
*/
void QtLocalePropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *languageProp = d_ptr->m_propertyToLanguage[property];
    if (languageProp) {
        d_ptr->m_languageToProperty.remove(languageProp);
        delete languageProp;
    }
    d_ptr->m_propertyToLanguage.remove(property);

    QtProperty *countryProp = d_ptr->m_propertyToCountry[property];
    if (countryProp) {
        d_ptr->m_countryToProperty.remove(countryProp);
        delete countryProp;
    }
    d_ptr->m_propertyToCountry.remove(property);

    d_ptr->m_values.remove(property);
}

// QtPointPropertyManager

class QtPointPropertyManagerPrivate
{
    QtPointPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtPointPropertyManager)
public:

    struct Data
    {
        Data()
            : val(QPoint()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QPoint val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;

    void slotIntChanged(QtProperty *property, int value);
    void slotPropertyDestroyed(QtProperty *property);

    QtIntPropertyManager *m_intPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToX;
    QMap<const QtProperty *, QtProperty *> m_propertyToY;

    QMap<const QtProperty *, QtProperty *> m_xToProperty;
    QMap<const QtProperty *, QtProperty *> m_yToProperty;
};

void QtPointPropertyManagerPrivate::slotIntChanged(QtProperty *property, int value)
{
    if (QtProperty *xprop = m_xToProperty.value(property, nullptr)) {
        QPoint p = m_values[xprop].val;
        p.setX(value);
        q_ptr->setValue(xprop, p);
    } else if (QtProperty *yprop = m_yToProperty.value(property, nullptr)) {
        QPoint p = m_values[yprop].val;
        p.setY(value);
        q_ptr->setValue(yprop, p);
    }
}

void QtPointPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_xToProperty.value(property, nullptr)) {
        m_propertyToX[pointProp] = nullptr;
        m_xToProperty.remove(property);
    } else if (QtProperty *pointProp = m_yToProperty.value(property, nullptr)) {
        m_propertyToY[pointProp] = nullptr;
        m_yToProperty.remove(property);
    }
}

/*! \class QtPointPropertyManager

    \brief The QtPointPropertyManager provides and manages QPoint properties.

    A point property has nested \e x and \e y subproperties. The
    top-level property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The subproperties are created by a QtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QtPointPropertyManager provides the valueChanged() signal which
    is emitted whenever a property created by this manager changes.

    \sa QtAbstractPropertyManager, QtIntPropertyManager, QtPointFPropertyManager
*/

/*!
    \fn void QtPointPropertyManager::valueChanged(QtProperty *property, const QPoint &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtPointPropertyManager::QtPointPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtPointPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QtIntPropertyManager(this);
    d_ptr->m_intPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotIntChanged(QtProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtPointPropertyManager::~QtPointPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x and \e y
    subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtPointPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a point with coordinates (0, 0).

    \sa setValue()
*/
QPoint QtPointPropertyManager::value(const QtProperty *property) const
{
    return getValue<QPoint>(d_ptr->m_values, property, QPoint(0, 0));
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtPointPropertyManager::setCheck
*/
bool QtPointPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtPointPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtPointPropertyManager::valueText(const QtProperty *property) const
{
    const QtPointPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QPoint v = getValue<QPoint>(d_ptr->m_values, property, QPoint(0, 0));
    return QString(tr("(%1, %2)").arg(QString::number(v.x()))
                                 .arg(QString::number(v.y())));
}

/*!
 \reimp
 */
QIcon QtPointPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtPointPropertyManager::setValue(QtProperty *property, const QPoint &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtPointPropertyManager::setValue(QtProperty *property, const QPoint &val)
{
    const QtPointPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val == val)
        return;

    it.value().val = val;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    Sets check status of the property.

    \sa QtPointPropertyManager::setCheck
*/
void QtPointPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtPointPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtPointPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtPointPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property].val = QPoint(0, 0);

    QtProperty *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QtProperty *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

/*!
    \reimp
*/
void QtPointPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}

// QtPointFPropertyManager

class QtPointFPropertyManagerPrivate
{
    QtPointFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtPointFPropertyManager)
public:

    struct Data
    {
        Data() : val(QPointF(0.0, 0.0)),
                 absTol(QPointF(epsilon, epsilon)), relTol(QPointF(epsilon, epsilon)), precision(2), check(false) {}
        QPointF val;
        QPointF absTol;
        QPointF relTol;
        int precision;
        bool check;
        QBrush foreground;
    };

    void slotDoubleChanged(QtProperty *property, double value);
    void slotPropertyDestroyed(QtProperty *property);

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToX;
    QMap<const QtProperty *, QtProperty *> m_propertyToY;

    QMap<const QtProperty *, QtProperty *> m_xToProperty;
    QMap<const QtProperty *, QtProperty *> m_yToProperty;
};

void QtPointFPropertyManagerPrivate::slotDoubleChanged(QtProperty *property, double value)
{
    if (QtProperty *prop = m_xToProperty.value(property, nullptr)) {
        QPointF p = m_values[prop].val;
        p.setX(value);
        q_ptr->setValue(prop, p);
    } else if (QtProperty *prop = m_yToProperty.value(property, nullptr)) {
        QPointF p = m_values[prop].val;
        p.setY(value);
        q_ptr->setValue(prop, p);
    }
}

void QtPointFPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp  = m_xToProperty.value(property, nullptr)) {
        m_propertyToX[pointProp] = nullptr;
        m_xToProperty.remove(property);
    } else if (QtProperty *pointProp = m_yToProperty.value(property, nullptr)) {
        m_propertyToY[pointProp] = nullptr;
        m_yToProperty.remove(property);
    }
}

/*! \class QtPointFPropertyManager

    \brief The QtPointFPropertyManager provides and manages QPointF properties.

    A point property has nested \e x and \e y subproperties. The
    top-level property's value can be retrieved using the value()
    function, and set using the setValue() slot.

    The subproperties are created by a QtDoublePropertyManager object. This
    manager can be retrieved using the subDoublePropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QtPointFPropertyManager provides the valueChanged() signal which
    is emitted whenever a property created by this manager changes.

    \sa QtAbstractPropertyManager, QtDoublePropertyManager, QtPointPropertyManager
*/

/*!
    \fn void QtPointFPropertyManager::valueChanged(QtProperty *property, const QPointF &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtPointFPropertyManager::precisionChanged(QtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setPrecision()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtPointFPropertyManager::QtPointFPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtPointFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QtDoublePropertyManager(this);
    d_ptr->m_doublePropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QtProperty *, double)),
                this, SLOT(slotDoubleChanged(QtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtPointFPropertyManager::~QtPointFPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x and \e y
    subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtDoublePropertyManager *QtPointFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a point with coordinates (0, 0).

    \sa setValue()
*/
QPointF QtPointFPropertyManager::value(const QtProperty *property) const
{
    return getValue<QPointF>(d_ptr->m_values, property, QPointF(0, 0));
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtPointFPropertyManager::setCheck
*/
bool QtPointFPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtPointFPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setPrecision()
*/
int QtPointFPropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtPointFPropertyManagerPrivate::Data::precision, property, 0);
}

/*!
    \reimp
*/
QString QtPointFPropertyManager::valueText(const QtProperty *property) const
{
    const QtPointFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QPointF v = it.value().val;
    const int dec =  it.value().precision;
    return QString(tr("(%1, %2)").arg(QString::number(v.x(), 'f', dec))
                                 .arg(QString::number(v.y(), 'f', dec)));
}

/*!
 \reimp
 */
QIcon QtPointFPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtPointFPropertyManager::setValue(QtProperty *property, const QPointF &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtPointFPropertyManager::setValue(QtProperty *property, const QPointF &val)
{
    const QtPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtPointFPropertyManagerPrivate::Data data = it.value();
    if (isclose(val, data.val, data.absTol, data.relTol))
        return;

    it.value().val = val;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], val.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], val.y());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    \fn void QtPointFPropertyManager::setPrecision(QtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa precision()
*/
void QtPointFPropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtPointFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.precision == prec)
        return;

    data.precision = prec;
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToY[property], prec);

    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
    Sets check status of the property.

    \sa QtPointFPropertyManager::setCheck
*/
void QtPointFPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtPointFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtPointFPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtPointFPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtPointFPropertyManagerPrivate::Data();

    QtProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setPrecision(xProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QtProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setPrecision(yProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);
}

/*!
    \reimp
*/
void QtPointFPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    d_ptr->m_values.remove(property);
}

// QtSizePropertyManager

class QtSizePropertyManagerPrivate
{
    QtSizePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtSizePropertyManager)
public:

    void slotIntChanged(QtProperty *property, int value);
    void slotPropertyDestroyed(QtProperty *property);
    void setValue(QtProperty *property, const QSize &val);
    void setRange(QtProperty *property,
                const QSize &minVal, const QSize &maxVal, const QSize &val);

    struct Data
    {
        Data() : val(QSize(0, 0)), minVal(QSize(0, 0)), maxVal(QSize(INT_MAX, INT_MAX)),
                 absTol(QSize(0, 0)), relTol(QSize(0, 0)),
                 readOnly(false), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QSize val;
        QSize minVal;
        QSize maxVal;
        QSize absTol;
        QSize relTol;
        bool readOnly;
        bool check;
        QBrush foreground;
        QSize minimumValue() const { return minVal; }
        QSize maximumValue() const { return maxVal; }
        void setMinimumValue(const QSize &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSize &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtIntPropertyManager *m_intPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToW;
    QMap<const QtProperty *, QtProperty *> m_propertyToH;

    QMap<const QtProperty *, QtProperty *> m_wToProperty;
    QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

void QtSizePropertyManagerPrivate::slotIntChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_wToProperty.value(property, nullptr)) {
        QSize s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    } else if (QtProperty *prop = m_hToProperty.value(property, nullptr)) {
        QSize s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void QtSizePropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_wToProperty.value(property, nullptr)) {
        m_propertyToW[pointProp] = nullptr;
        m_wToProperty.remove(property);
    } else if (QtProperty *pointProp = m_hToProperty.value(property, nullptr)) {
        m_propertyToH[pointProp] = nullptr;
        m_hToProperty.remove(property);
    }
}

void QtSizePropertyManagerPrivate::setValue(QtProperty *property, const QSize &val)
{
    m_intPropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_intPropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void QtSizePropertyManagerPrivate::setRange(QtProperty *property,
                const QSize &minVal, const QSize &maxVal, const QSize &val)
{
    QtProperty *wProperty = m_propertyToW.value(property);
    QtProperty *hProperty = m_propertyToH.value(property);
    m_intPropertyManager->setRange(wProperty, minVal.width(), maxVal.width());
    m_intPropertyManager->setValue(wProperty, val.width());
    m_intPropertyManager->setRange(hProperty, minVal.height(), maxVal.height());
    m_intPropertyManager->setValue(hProperty, val.height());
}

/*!
    \class QtSizePropertyManager

    \brief The QtSizePropertyManager provides and manages QSize properties.

    A size property has nested \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A size property also has a range of valid values defined by a
    minimum size and a maximum size. These sizes can be retrieved
    using the minimum() and the maximum() functions, and set using the
    setMinimum() and setMaximum() slots. Alternatively, the range can
    be defined in one go using the setRange() slot.

    In addition, QtSizePropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid sizes.

    \sa QtAbstractPropertyManager, QtIntPropertyManager, QtSizeFPropertyManager
*/

/*!
    \fn void QtSizePropertyManager::valueChanged(QtProperty *property, const QSize &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtSizePropertyManager::rangeChanged(QtProperty *property, const QSize &minimum, const QSize &maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid sizes, passing a pointer to the \a
    property and the new \a minimum and \a maximum sizes.

    \sa setRange()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtSizePropertyManager::QtSizePropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtSizePropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QtIntPropertyManager(this);
    d_ptr->m_intPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotIntChanged(QtProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtSizePropertyManager::~QtSizePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e width and \e height
    subproperties.

    In order to provide editing widgets for the \e width and \e height
    properties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtSizePropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid size

    \sa setValue()
*/
QSize QtSizePropertyManager::value(const QtProperty *property) const
{
    return getValue<QSize>(d_ptr->m_values, property, QSize(0, 0));
}

/*!
    Returns the given \a property's minimum size value.

    \sa setMinimum(), maximum(), setRange()
*/
QSize QtSizePropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<QSize>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's maximum size value.

    \sa setMaximum(), minimum(), setRange()
*/
QSize QtSizePropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<QSize>(d_ptr->m_values, property);
}

/*!
    Returns read-only status of the property.

    When property is read-only it's value can be selected and copied from editor but not modified.

    \sa QtSizePropertyManager::setReadOnly
*/
bool QtSizePropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtSizePropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtSizePropertyManager::setCheck
*/
bool QtSizePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtSizePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtSizePropertyManager::valueText(const QtProperty *property) const
{
    const QtSizePropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QSize v = it.value().val;
    return QString(tr("%1 x %2").arg(QString::number(v.width()))
                                .arg(QString::number(v.height())));
}

/*!
 \reimp
 */
QIcon QtSizePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtSizePropertyManager::setValue(QtProperty *property, const QSize &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given \a
    property's size range, the \a value is adjusted to the nearest
    valid value within the size range.

    \sa value(), setRange(), valueChanged()
*/
void QtSizePropertyManager::setValue(QtProperty *property, const QSize &val)
{
    setValueInRange<const QSize &, QtSizePropertyManagerPrivate, QtSizePropertyManager, const QSize>(this, d_ptr,
                &QtSizePropertyManager::propertyChanged,
                &QtSizePropertyManager::valueChanged,
                property, val, &QtSizePropertyManagerPrivate::setValue);
}

/*!
    Sets the minimum size value for the given \a property to \a minVal.

    When setting the minimum size value, the maximum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QtSizePropertyManager::setMinimum(QtProperty *property, const QSize &minVal)
{
    setBorderValue<const QSize &, QtSizePropertyManagerPrivate, QtSizePropertyManager, QSize, QtSizePropertyManagerPrivate::Data>(this, d_ptr,
                &QtSizePropertyManager::propertyChanged,
                &QtSizePropertyManager::valueChanged,
                &QtSizePropertyManager::rangeChanged,
                property,
                &QtSizePropertyManagerPrivate::Data::minimumValue,
                &QtSizePropertyManagerPrivate::Data::setMinimumValue,
                minVal, &QtSizePropertyManagerPrivate::setRange);
}

/*!
    Sets the maximum size value for the given \a property to \a maxVal.

    When setting the maximum size value, the minimum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QtSizePropertyManager::setMaximum(QtProperty *property, const QSize &maxVal)
{
    setBorderValue<const QSize &, QtSizePropertyManagerPrivate, QtSizePropertyManager, QSize, QtSizePropertyManagerPrivate::Data>(this, d_ptr,
                &QtSizePropertyManager::propertyChanged,
                &QtSizePropertyManager::valueChanged,
                &QtSizePropertyManager::rangeChanged,
                property,
                &QtSizePropertyManagerPrivate::Data::maximumValue,
                &QtSizePropertyManagerPrivate::Data::setMaximumValue,
                maxVal, &QtSizePropertyManagerPrivate::setRange);
}

/*!
    \fn void QtSizePropertyManager::setRange(QtProperty *property, const QSize &minimum, const QSize &maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within the range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtSizePropertyManager::setRange(QtProperty *property, const QSize &minVal, const QSize &maxVal)
{
    setBorderValues<const QSize &, QtSizePropertyManagerPrivate, QtSizePropertyManager, QSize>(this, d_ptr,
                &QtSizePropertyManager::propertyChanged,
                &QtSizePropertyManager::valueChanged,
                &QtSizePropertyManager::rangeChanged,
                property, minVal, maxVal, &QtSizePropertyManagerPrivate::setRange);
}

/*!
    Sets read-only status of the property.

    \sa QtSizePropertyManager::setReadOnly
*/
void QtSizePropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtSizePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtSizePropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
    Sets check status of the property.

    \sa QtSizePropertyManager::setCheck
*/
void QtSizePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtSizePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtSizePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtSizePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtSizePropertyManagerPrivate::Data();

    QtProperty *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QtProperty *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QtSizePropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QtSizeFPropertyManager

class QtSizeFPropertyManagerPrivate
{
    QtSizeFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtSizeFPropertyManager)
public:

    void slotDoubleChanged(QtProperty *property, double value);
    void slotPropertyDestroyed(QtProperty *property);
    void setValue(QtProperty *property, const QSizeF &val);
    void setRange(QtProperty *property,
                const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val);

    struct Data
    {
        Data() : val(QSizeF(0, 0)), minVal(QSizeF(0, 0)), maxVal(QSizeF(highest, highest)),
                 absTol(QSizeF(epsilon, epsilon)), relTol(QSizeF(epsilon, epsilon)), precision(2),
                 readOnly(false), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QSizeF val;
        QSizeF minVal;
        QSizeF maxVal;
        QSizeF absTol;
        QSizeF relTol;
        int precision;
        bool readOnly;
        bool check;
        QBrush foreground;
        QSizeF minimumValue() const { return minVal; }
        QSizeF maximumValue() const { return maxVal; }
        void setMinimumValue(const QSizeF &newMinVal) { setSizeMinimumData(this, newMinVal); }
        void setMaximumValue(const QSizeF &newMaxVal) { setSizeMaximumData(this, newMaxVal); }
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToW;
    QMap<const QtProperty *, QtProperty *> m_propertyToH;

    QMap<const QtProperty *, QtProperty *> m_wToProperty;
    QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

void QtSizeFPropertyManagerPrivate::slotDoubleChanged(QtProperty *property, double value)
{
    if (QtProperty *prop = m_wToProperty.value(property, nullptr)) {
        QSizeF s = m_values[prop].val;
        s.setWidth(value);
        q_ptr->setValue(prop, s);
    } else if (QtProperty *prop = m_hToProperty.value(property, nullptr)) {
        QSizeF s = m_values[prop].val;
        s.setHeight(value);
        q_ptr->setValue(prop, s);
    }
}

void QtSizeFPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_wToProperty.value(property, nullptr)) {
        m_propertyToW[pointProp] = nullptr;
        m_wToProperty.remove(property);
    } else if (QtProperty *pointProp = m_hToProperty.value(property, nullptr)) {
        m_propertyToH[pointProp] = nullptr;
        m_hToProperty.remove(property);
    }
}

void QtSizeFPropertyManagerPrivate::setValue(QtProperty *property, const QSizeF &val)
{
    m_doublePropertyManager->setValue(m_propertyToW.value(property), val.width());
    m_doublePropertyManager->setValue(m_propertyToH.value(property), val.height());
}

void QtSizeFPropertyManagerPrivate::setRange(QtProperty *property,
                const QSizeF &minVal, const QSizeF &maxVal, const QSizeF &val)
{
    m_doublePropertyManager->setRange(m_propertyToW[property], minVal.width(), maxVal.width());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setRange(m_propertyToH[property], minVal.height(), maxVal.height());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}

/*!
    \class QtSizeFPropertyManager

    \brief The QtSizeFPropertyManager provides and manages QSizeF properties.

    A size property has nested \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QtDoublePropertyManager object. This
    manager can be retrieved using the subDoublePropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A size property also has a range of valid values defined by a
    minimum size and a maximum size. These sizes can be retrieved
    using the minimum() and the maximum() functions, and set using the
    setMinimum() and setMaximum() slots. Alternatively, the range can
    be defined in one go using the setRange() slot.

    In addition, QtSizeFPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the rangeChanged() signal which is emitted whenever
    such a property changes its range of valid sizes.

    \sa QtAbstractPropertyManager, QtDoublePropertyManager, QtSizePropertyManager
*/

/*!
    \fn void QtSizeFPropertyManager::valueChanged(QtProperty *property, const QSizeF &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtSizeFPropertyManager::rangeChanged(QtProperty *property, const QSizeF &minimum, const QSizeF &maximum)

    This signal is emitted whenever a property created by this manager
    changes its range of valid sizes, passing a pointer to the \a
    property and the new \a minimum and \a maximum sizes.

    \sa setRange()
*/

/*!
    \fn void QtSizeFPropertyManager::precisionChanged(QtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setPrecision()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtSizeFPropertyManager::QtSizeFPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtSizeFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QtDoublePropertyManager(this);
    d_ptr->m_doublePropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QtProperty *, double)),
                this, SLOT(slotDoubleChanged(QtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtSizeFPropertyManager::~QtSizeFPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e width and \e height
    subproperties.

    In order to provide editing widgets for the \e width and \e height
    properties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtDoublePropertyManager *QtSizeFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid size

    \sa setValue()
*/
QSizeF QtSizeFPropertyManager::value(const QtProperty *property) const
{
    return getValue<QSizeF>(d_ptr->m_values, property, QSizeF(0.0, 0.0));
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setPrecision()
*/
int QtSizeFPropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtSizeFPropertyManagerPrivate::Data::precision, property, 0);
}

/*!
    Returns the given \a property's minimum size value.

    \sa setMinimum(), maximum(), setRange()
*/
QSizeF QtSizeFPropertyManager::minimum(const QtProperty *property) const
{
    return getMinimum<QSizeF>(d_ptr->m_values, property);
}

/*!
    Returns the given \a property's maximum size value.

    \sa setMaximum(), minimum(), setRange()
*/
QSizeF QtSizeFPropertyManager::maximum(const QtProperty *property) const
{
    return getMaximum<QSizeF>(d_ptr->m_values, property);
}

/*!
    Returns read-only status of the property.

    When property is read-only it's value can be selected and copied from editor but not modified.

    \sa QtSizeFPropertyManager::setReadOnly
*/
bool QtSizeFPropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtSizeFPropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtSizeFPropertyManager::setCheck
*/
bool QtSizeFPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtSizeFPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtSizeFPropertyManager::valueText(const QtProperty *property) const
{
    const QtSizeFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QSizeF v = it.value().val;
    const int dec = it.value().precision;
    return QString(tr("%1 x %2").arg(QString::number(v.width(), 'f', dec))
                                .arg(QString::number(v.height(), 'f', dec)));
}

/*!
 \reimp
 */
QIcon QtSizeFPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtSizeFPropertyManager::setValue(QtProperty *property, const QSizeF &value)

    Sets the value of the given \a property to \a value.

    If the specified \a value is not valid according to the given \a
    property's size range, the \a value is adjusted to the nearest
    valid value within the size range.

    \sa value(), setRange(), valueChanged()
*/
void QtSizeFPropertyManager::setValue(QtProperty *property, const QSizeF &val)
{
    setValueInRange<const QSizeF &, QtSizeFPropertyManagerPrivate, QtSizeFPropertyManager, QSizeF>(this, d_ptr,
                &QtSizeFPropertyManager::propertyChanged,
                &QtSizeFPropertyManager::valueChanged,
                property, val, &QtSizeFPropertyManagerPrivate::setValue);
}

/*!
    \fn void QtSizeFPropertyManager::setPrecision(QtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa precision()
*/
void QtSizeFPropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtSizeFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtSizeFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.precision == prec)
        return;

    data.precision = prec;
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
    Sets the minimum size value for the given \a property to \a minVal.

    When setting the minimum size value, the maximum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa minimum(), setRange(), rangeChanged()
*/
void QtSizeFPropertyManager::setMinimum(QtProperty *property, const QSizeF &minVal)
{
    setBorderValue<const QSizeF &, QtSizeFPropertyManagerPrivate, QtSizeFPropertyManager, QSizeF, QtSizeFPropertyManagerPrivate::Data>(this, d_ptr,
                &QtSizeFPropertyManager::propertyChanged,
                &QtSizeFPropertyManager::valueChanged,
                &QtSizeFPropertyManager::rangeChanged,
                property,
                &QtSizeFPropertyManagerPrivate::Data::minimumValue,
                &QtSizeFPropertyManagerPrivate::Data::setMinimumValue,
                minVal, &QtSizeFPropertyManagerPrivate::setRange);
}

/*!
    Sets the maximum size value for the given \a property to \a maxVal.

    When setting the maximum size value, the minimum and current
    values are adjusted if necessary (ensuring that the size range
    remains valid and that the current value is within the range).

    \sa maximum(), setRange(), rangeChanged()
*/
void QtSizeFPropertyManager::setMaximum(QtProperty *property, const QSizeF &maxVal)
{
    setBorderValue<const QSizeF &, QtSizeFPropertyManagerPrivate, QtSizeFPropertyManager, QSizeF, QtSizeFPropertyManagerPrivate::Data>(this, d_ptr,
                &QtSizeFPropertyManager::propertyChanged,
                &QtSizeFPropertyManager::valueChanged,
                &QtSizeFPropertyManager::rangeChanged,
                property,
                &QtSizeFPropertyManagerPrivate::Data::maximumValue,
                &QtSizeFPropertyManagerPrivate::Data::setMaximumValue,
                maxVal, &QtSizeFPropertyManagerPrivate::setRange);
}

/*!
    \fn void QtSizeFPropertyManager::setRange(QtProperty *property, const QSizeF &minimum, const QSizeF &maximum)

    Sets the range of valid values.

    This is a convenience function defining the range of valid values
    in one go; setting the \a minimum and \a maximum values for the
    given \a property with a single function call.

    When setting a new range, the current value is adjusted if
    necessary (ensuring that the value remains within the range).

    \sa setMinimum(), setMaximum(), rangeChanged()
*/
void QtSizeFPropertyManager::setRange(QtProperty *property, const QSizeF &minVal, const QSizeF &maxVal)
{
    setBorderValues<const QSizeF &, QtSizeFPropertyManagerPrivate, QtSizeFPropertyManager, QSizeF>(this, d_ptr,
                &QtSizeFPropertyManager::propertyChanged,
                &QtSizeFPropertyManager::valueChanged,
                &QtSizeFPropertyManager::rangeChanged,
                property, minVal, maxVal, &QtSizeFPropertyManagerPrivate::setRange);
}

/*!
    Sets check status of the property.

    \sa QtSizeFPropertyManager::setCheck
*/
void QtSizeFPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtSizeFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtSizeFPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtSizeFPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtSizeFPropertyManagerPrivate::Data();

    QtProperty *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setPrecision(wProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QtProperty *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setPrecision(hProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    Sets read-only status of the property.

    \sa QtSizeFPropertyManager::setReadOnly
*/
void QtSizeFPropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtSizeFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtSizeFPropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
    \reimp
*/
void QtSizeFPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QtRectPropertyManager

class QtRectPropertyManagerPrivate
{
    QtRectPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtRectPropertyManager)
public:

    void slotIntChanged(QtProperty *property, int value);
    void slotPropertyDestroyed(QtProperty *property);
    void setConstraint(QtProperty *property, const QRect &constraint, const QRect &val);

    struct Data
    {
        Data() : val(QRect(0, 0, 0, 0)),
                 absTol(QRect(0, 0, 0, 0)), relTol(QRect(0, 0, 0, 0)), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QRect val;
        QRect absTol;
        QRect relTol;
        bool check;
        QBrush foreground;
        QRect constraint;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtIntPropertyManager *m_intPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToX;
    QMap<const QtProperty *, QtProperty *> m_propertyToY;
    QMap<const QtProperty *, QtProperty *> m_propertyToW;
    QMap<const QtProperty *, QtProperty *> m_propertyToH;

    QMap<const QtProperty *, QtProperty *> m_xToProperty;
    QMap<const QtProperty *, QtProperty *> m_yToProperty;
    QMap<const QtProperty *, QtProperty *> m_wToProperty;
    QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

void QtRectPropertyManagerPrivate::slotIntChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_xToProperty.value(property, nullptr)) {
        QRect r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    } else if (QtProperty *prop = m_yToProperty.value(property)) {
        QRect r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    } else if (QtProperty *prop = m_wToProperty.value(property, nullptr)) {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width()) {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    } else if (QtProperty *prop = m_hToProperty.value(property, nullptr)) {
        Data data = m_values[prop];
        QRect r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height()) {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void QtRectPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_xToProperty.value(property, nullptr)) {
        m_propertyToX[pointProp] = nullptr;
        m_xToProperty.remove(property);
    } else if (QtProperty *pointProp = m_yToProperty.value(property, nullptr)) {
        m_propertyToY[pointProp] = nullptr;
        m_yToProperty.remove(property);
    } else if (QtProperty *pointProp = m_wToProperty.value(property, nullptr)) {
        m_propertyToW[pointProp] = nullptr;
        m_wToProperty.remove(property);
    } else if (QtProperty *pointProp = m_hToProperty.value(property, nullptr)) {
        m_propertyToH[pointProp] = nullptr;
        m_hToProperty.remove(property);
    }
}

void QtRectPropertyManagerPrivate::setConstraint(QtProperty *property,
            const QRect &constraint, const QRect &val)
{
    const bool isNull = constraint.isNull();
    const int left   = isNull ? INT_MIN : constraint.left();
    const int right  = isNull ? INT_MAX : constraint.left() + constraint.width();
    const int top    = isNull ? INT_MIN : constraint.top();
    const int bottom = isNull ? INT_MAX : constraint.top() + constraint.height();
    const int width  = isNull ? INT_MAX : constraint.width();
    const int height = isNull ? INT_MAX : constraint.height();

    m_intPropertyManager->setRange(m_propertyToX[property], left, right);
    m_intPropertyManager->setRange(m_propertyToY[property], top, bottom);
    m_intPropertyManager->setRange(m_propertyToW[property], 0, width);
    m_intPropertyManager->setRange(m_propertyToH[property], 0, height);

    m_intPropertyManager->setValue(m_propertyToX[property], val.x());
    m_intPropertyManager->setValue(m_propertyToY[property], val.y());
    m_intPropertyManager->setValue(m_propertyToW[property], val.width());
    m_intPropertyManager->setValue(m_propertyToH[property], val.height());
}

/*!
    \class QtRectPropertyManager

    \brief The QtRectPropertyManager provides and manages QRect properties.

    A rectangle property has nested \e x, \e y, \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A rectangle property also has a constraint rectangle which can be
    retrieved using the constraint() function, and set using the
    setConstraint() slot.

    In addition, QtRectPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the constraintChanged() signal which is emitted
    whenever such a property changes its constraint rectangle.

    \sa QtAbstractPropertyManager, QtIntPropertyManager, QtRectFPropertyManager
*/

/*!
    \fn void QtRectPropertyManager::valueChanged(QtProperty *property, const QRect &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtRectPropertyManager::constraintChanged(QtProperty *property, const QRect &constraint)

    This signal is emitted whenever property changes its constraint
    rectangle, passing a pointer to the \a property and the new \a
    constraint rectangle as parameters.

    \sa setConstraint()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtRectPropertyManager::QtRectPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtRectPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QtIntPropertyManager(this);
    d_ptr->m_intPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotIntChanged(QtProperty *, int)));
    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtRectPropertyManager::~QtRectPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x, \e y, \e width
    and \e height subproperties.

    In order to provide editing widgets for the mentioned
    subproperties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtRectPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid rectangle.

    \sa setValue(), constraint()
*/
QRect QtRectPropertyManager::value(const QtProperty *property) const
{
    return getValue<QRect>(d_ptr->m_values, property, QRect(0, 0, 0, 0));
}

/*!
    Returns the given \a property's constraining rectangle. If returned value is null QRect it means there is no constraint applied.

    \sa value(), setConstraint()
*/
QRect QtRectPropertyManager::constraint(const QtProperty *property) const
{
    return getData<QRect>(d_ptr->m_values, &QtRectPropertyManagerPrivate::Data::constraint, property, QRect());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtRectPropertyManager::setCheck
*/
bool QtRectPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtRectPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtRectPropertyManager::valueText(const QtProperty *property) const
{
    const QtRectPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QRect v = it.value().val;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x()))
                                .arg(QString::number(v.y()))
                                .arg(QString::number(v.width()))
                                .arg(QString::number(v.height())));
}

/*!
 \reimp
 */
QIcon QtRectPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtRectPropertyManager::setValue(QtProperty *property, const QRect &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    If the specified \a value is not inside the given \a property's
    constraining rectangle, the value is adjusted accordingly to fit
    within the constraint.

    \sa value(), setConstraint(), valueChanged()
*/
void QtRectPropertyManager::setValue(QtProperty *property, const QRect &val)
{
    const QtRectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectPropertyManagerPrivate::Data data = it.value();

    QRect newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect)) {
        const QRect r1 = data.constraint;
        const QRect r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
            return;
    }

    if (data.val == newRect)
        return;

    data.val = newRect;

    it.value() = data;
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's constraining rectangle to \a
    constraint.

    When setting the constraint, the current value is adjusted if
    necessary (ensuring that the current rectangle value is inside the
    constraint). In order to reset the constraint pass a null QRect value.

    \sa setValue(), constraint(), constraintChanged()
*/
void QtRectPropertyManager::setConstraint(QtProperty *property, const QRect &constraint)
{
    const QtRectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectPropertyManagerPrivate::Data data = it.value();

    QRect newConstraint = constraint.normalized();
    if (data.constraint == newConstraint)
        return;

    const QRect oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal)) {
        QRect r1 = data.constraint;
        QRect r2 = data.val;

        if (r2.width() > r1.width())
            r2.setWidth(r1.width());
        if (r2.height() > r1.height())
            r2.setHeight(r1.height());
        if (r2.left() < r1.left())
            r2.moveLeft(r1.left());
        else if (r2.right() > r1.right())
            r2.moveRight(r1.right());
        if (r2.top() < r1.top())
            r2.moveTop(r1.top());
        else if (r2.bottom() > r1.bottom())
            r2.moveBottom(r1.bottom());

        data.val = r2;
    }

    it.value() = data;

    emit constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (data.val == oldVal)
        return;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets check status of the property.

    \sa QtRectPropertyManager::setCheck
*/
void QtRectPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtRectPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtRectPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtRectPropertyManagerPrivate::Data();

    QtProperty *xProp = d_ptr->m_intPropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_intPropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QtProperty *yProp = d_ptr->m_intPropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_intPropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    QtProperty *wProp = d_ptr->m_intPropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_intPropertyManager->setValue(wProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QtProperty *hProp = d_ptr->m_intPropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_intPropertyManager->setValue(hProp, 0);
    d_ptr->m_intPropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QtRectPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    QtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QtRectFPropertyManager

class QtRectFPropertyManagerPrivate
{
    QtRectFPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtRectFPropertyManager)
public:

    void slotDoubleChanged(QtProperty *property, double value);
    void slotPropertyDestroyed(QtProperty *property);
    void setConstraint(QtProperty *property, const QRectF &constraint, const QRectF &val);

    struct Data
    {
        Data() : val(QRectF(0, 0, 0, 0)),
                 absTol(QRectF(epsilon, epsilon, epsilon, epsilon)), relTol(QRectF(epsilon, epsilon, epsilon, epsilon)), precision(2),
                 check(false), foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QRectF val;
        QRectF absTol;
        QRectF relTol;
        QRectF constraint;
        int precision;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtDoublePropertyManager *m_doublePropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToX;
    QMap<const QtProperty *, QtProperty *> m_propertyToY;
    QMap<const QtProperty *, QtProperty *> m_propertyToW;
    QMap<const QtProperty *, QtProperty *> m_propertyToH;

    QMap<const QtProperty *, QtProperty *> m_xToProperty;
    QMap<const QtProperty *, QtProperty *> m_yToProperty;
    QMap<const QtProperty *, QtProperty *> m_wToProperty;
    QMap<const QtProperty *, QtProperty *> m_hToProperty;
};

void QtRectFPropertyManagerPrivate::slotDoubleChanged(QtProperty *property, double value)
{
    if (QtProperty *prop = m_xToProperty.value(property, nullptr)) {
        QRectF r = m_values[prop].val;
        r.moveLeft(value);
        q_ptr->setValue(prop, r);
    } else if (QtProperty *prop = m_yToProperty.value(property, nullptr)) {
        QRectF r = m_values[prop].val;
        r.moveTop(value);
        q_ptr->setValue(prop, r);
    } else if (QtProperty *prop = m_wToProperty.value(property, nullptr)) {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setWidth(value);
        if (!data.constraint.isNull() && data.constraint.x() + data.constraint.width() < r.x() + r.width()) {
            r.moveLeft(data.constraint.left() + data.constraint.width() - r.width());
        }
        q_ptr->setValue(prop, r);
    } else if (QtProperty *prop = m_hToProperty.value(property, nullptr)) {
        Data data = m_values[prop];
        QRectF r = data.val;
        r.setHeight(value);
        if (!data.constraint.isNull() && data.constraint.y() + data.constraint.height() < r.y() + r.height()) {
            r.moveTop(data.constraint.top() + data.constraint.height() - r.height());
        }
        q_ptr->setValue(prop, r);
    }
}

void QtRectFPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_xToProperty.value(property, nullptr)) {
        m_propertyToX[pointProp] = nullptr;
        m_xToProperty.remove(property);
    } else if (QtProperty *pointProp = m_yToProperty.value(property, nullptr)) {
        m_propertyToY[pointProp] = nullptr;
        m_yToProperty.remove(property);
    } else if (QtProperty *pointProp = m_wToProperty.value(property, nullptr)) {
        m_propertyToW[pointProp] = nullptr;
        m_wToProperty.remove(property);
    } else if (QtProperty *pointProp = m_hToProperty.value(property, nullptr)) {
        m_propertyToH[pointProp] = nullptr;
        m_hToProperty.remove(property);
    }
}

void QtRectFPropertyManagerPrivate::setConstraint(QtProperty *property,
            const QRectF &constraint, const QRectF &val)
{
    const bool isNull = constraint.isNull();
    const float left   = isNull ? FLT_MIN : float(constraint.left());
    const float right  = isNull ? FLT_MAX : float(constraint.left() + constraint.width());
    const float top    = isNull ? FLT_MIN : float(constraint.top());
    const float bottom = isNull ? FLT_MAX : float(constraint.top() + constraint.height());
    const float width  = isNull ? FLT_MAX : float(constraint.width());
    const float height = isNull ? FLT_MAX : float(constraint.height());

    m_doublePropertyManager->setRange(m_propertyToX[property], double(left), double(right));
    m_doublePropertyManager->setRange(m_propertyToY[property], double(top), double(bottom));
    m_doublePropertyManager->setRange(m_propertyToW[property], 0, double(width));
    m_doublePropertyManager->setRange(m_propertyToH[property], 0, double(height));

    m_doublePropertyManager->setValue(m_propertyToX[property], val.x());
    m_doublePropertyManager->setValue(m_propertyToY[property], val.y());
    m_doublePropertyManager->setValue(m_propertyToW[property], val.width());
    m_doublePropertyManager->setValue(m_propertyToH[property], val.height());
}

/*!
    \class QtRectFPropertyManager

    \brief The QtRectFPropertyManager provides and manages QRectF properties.

    A rectangle property has nested \e x, \e y, \e width and \e height
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QtDoublePropertyManager object. This
    manager can be retrieved using the subDoublePropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    A rectangle property also has a constraint rectangle which can be
    retrieved using the constraint() function, and set using the
    setConstraint() slot.

    In addition, QtRectFPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the constraintChanged() signal which is emitted
    whenever such a property changes its constraint rectangle.

    \sa QtAbstractPropertyManager, QtDoublePropertyManager, QtRectPropertyManager
*/

/*!
    \fn void QtRectFPropertyManager::valueChanged(QtProperty *property, const QRectF &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtRectFPropertyManager::constraintChanged(QtProperty *property, const QRectF &constraint)

    This signal is emitted whenever property changes its constraint
    rectangle, passing a pointer to the \a property and the new \a
    constraint rectangle as parameters.

    \sa setConstraint()
*/

/*!
    \fn void QtRectFPropertyManager::precisionChanged(QtProperty *property, int prec)

    This signal is emitted whenever a property created by this manager
    changes its precision of value, passing a pointer to the
    \a property and the new \a prec value

    \sa setPrecision()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtRectFPropertyManager::QtRectFPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtRectFPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_doublePropertyManager = new QtDoublePropertyManager(this);
    d_ptr->m_doublePropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_doublePropertyManager, SIGNAL(valueChanged(QtProperty *, double)),
                this, SLOT(slotDoubleChanged(QtProperty *, double)));
    connect(d_ptr->m_doublePropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtRectFPropertyManager::~QtRectFPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e x, \e y, \e width
    and \e height subproperties.

    In order to provide editing widgets for the mentioned
    subproperties in a property browser widget, this manager must be
    associated with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtDoublePropertyManager *QtRectFPropertyManager::subDoublePropertyManager() const
{
    return d_ptr->m_doublePropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns an invalid rectangle.

    \sa setValue(), constraint()
*/
QRectF QtRectFPropertyManager::value(const QtProperty *property) const
{
    return getValue<QRectF>(d_ptr->m_values, property, QRectF(0.0, 0.0, 0.0, 0.0));
}

/*!
    Returns the given \a property's precision, in decimals.

    \sa setPrecision()
*/
int QtRectFPropertyManager::precision(const QtProperty *property) const
{
    return getData<int>(d_ptr->m_values, &QtRectFPropertyManagerPrivate::Data::precision, property, 0);
}

/*!
    Returns the given \a property's constraining rectangle. If returned value is null QRectF it means there is no constraint applied.

    \sa value(), setConstraint()
*/
QRectF QtRectFPropertyManager::constraint(const QtProperty *property) const
{
    return getData<QRectF>(d_ptr->m_values, &QtRectFPropertyManagerPrivate::Data::constraint, property, QRect());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtRectFPropertyManager::setCheck
*/
bool QtRectFPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtRectFPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtRectFPropertyManager::valueText(const QtProperty *property) const
{
    const QtRectFPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();
    const QRectF v = it.value().val;
    const int dec = it.value().precision;
    return QString(tr("[(%1, %2), %3 x %4]").arg(QString::number(v.x(), 'f', dec))
                                .arg(QString::number(v.y(), 'f', dec))
                                .arg(QString::number(v.width(), 'f', dec))
                                .arg(QString::number(v.height(), 'f', dec)));
}

/*!
 \reimp
 */
QIcon QtRectFPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtRectFPropertyManager::setValue(QtProperty *property, const QRectF &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    If the specified \a value is not inside the given \a property's
    constraining rectangle, the value is adjusted accordingly to fit
    within the constraint.

    \sa value(), setConstraint(), valueChanged()
*/
void QtRectFPropertyManager::setValue(QtProperty *property, const QRectF &val)
{
    const QtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectFPropertyManagerPrivate::Data data = it.value();

    QRectF newRect = val.normalized();
    if (!data.constraint.isNull() && !data.constraint.contains(newRect)) {
        const QRectF r1 = data.constraint;
        const QRectF r2 = newRect;
        newRect.setLeft(qMax(r1.left(), r2.left()));
        newRect.setRight(qMin(r1.right(), r2.right()));
        newRect.setTop(qMax(r1.top(), r2.top()));
        newRect.setBottom(qMin(r1.bottom(), r2.bottom()));
        if (newRect.width() < 0 || newRect.height() < 0)
            return;
    }

    if (isclose(newRect, data.val, data.absTol, data.relTol))
        return;

    data.val = newRect;

    it.value() = data;
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property], newRect.x());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property], newRect.y());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToW[property], newRect.width());
    d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToH[property], newRect.height());

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's constraining rectangle to \a
    constraint.

    When setting the constraint, the current value is adjusted if
    necessary (ensuring that the current rectangle value is inside the
    constraint). In order to reset the constraint pass a null QRectF value.

    \sa setValue(), constraint(), constraintChanged()
*/
void QtRectFPropertyManager::setConstraint(QtProperty *property, const QRectF &constraint)
{
    const QtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectFPropertyManagerPrivate::Data data = it.value();

    QRectF newConstraint = constraint.normalized();
    if (isclose(newConstraint, data.constraint, data.absTol, data.relTol))
        return;

    const QRectF oldVal = data.val;

    data.constraint = newConstraint;

    if (!data.constraint.isNull() && !data.constraint.contains(oldVal)) {
        QRectF r1 = data.constraint;
        QRectF r2 = data.val;

        if (r2.width() > r1.width())
            r2.setWidth(r1.width());
        if (r2.height() > r1.height())
            r2.setHeight(r1.height());
        if (r2.left() < r1.left())
            r2.moveLeft(r1.left());
        else if (r2.right() > r1.right())
            r2.moveRight(r1.right());
        if (r2.top() < r1.top())
            r2.moveTop(r1.top());
        else if (r2.bottom() > r1.bottom())
            r2.moveBottom(r1.bottom());

        data.val = r2;
    }

    it.value() = data;

    emit constraintChanged(property, data.constraint);

    d_ptr->setConstraint(property, data.constraint, data.val);

    if (isclose(oldVal, data.val, data.absTol, data.relTol))
        return;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    \fn void QtRectFPropertyManager::setPrecision(QtProperty *property, int prec)

    Sets the precision of the given \a property to \a prec.

    The valid decimal range is 0-13. The default is 2.

    \sa precision()
*/
void QtRectFPropertyManager::setPrecision(QtProperty *property, int prec)
{
    const QtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectFPropertyManagerPrivate::Data data = it.value();

    if (prec > 13)
        prec = 13;
    else if (prec < 0)
        prec = 0;

    if (data.precision == prec)
        return;

    data.precision = prec;
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToX[property], prec);
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToY[property], prec);
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToW[property], prec);
    d_ptr->m_doublePropertyManager->setPrecision(d_ptr->m_propertyToH[property], prec);

    it.value() = data;

    emit precisionChanged(property, data.precision);
}

/*!
    Sets check status of the property.

    \sa QtRectFPropertyManager::setCheck
*/
void QtRectFPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtRectFPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtRectFPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtRectFPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtRectFPropertyManagerPrivate::Data();

    QtProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
    xProp->setPropertyName(tr("X"));
    d_ptr->m_doublePropertyManager->setPrecision(xProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(xProp, 0);
    d_ptr->m_propertyToX[property] = xProp;
    d_ptr->m_xToProperty[xProp] = property;
    property->addSubProperty(xProp);

    QtProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
    yProp->setPropertyName(tr("Y"));
    d_ptr->m_doublePropertyManager->setPrecision(yProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(yProp, 0);
    d_ptr->m_propertyToY[property] = yProp;
    d_ptr->m_yToProperty[yProp] = property;
    property->addSubProperty(yProp);

    QtProperty *wProp = d_ptr->m_doublePropertyManager->addProperty();
    wProp->setPropertyName(tr("Width"));
    d_ptr->m_doublePropertyManager->setPrecision(wProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(wProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(wProp, 0);
    d_ptr->m_propertyToW[property] = wProp;
    d_ptr->m_wToProperty[wProp] = property;
    property->addSubProperty(wProp);

    QtProperty *hProp = d_ptr->m_doublePropertyManager->addProperty();
    hProp->setPropertyName(tr("Height"));
    d_ptr->m_doublePropertyManager->setPrecision(hProp, precision(property));
    d_ptr->m_doublePropertyManager->setValue(hProp, 0);
    d_ptr->m_doublePropertyManager->setMinimum(hProp, 0);
    d_ptr->m_propertyToH[property] = hProp;
    d_ptr->m_hToProperty[hProp] = property;
    property->addSubProperty(hProp);
}

/*!
    \reimp
*/
void QtRectFPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *xProp = d_ptr->m_propertyToX[property];
    if (xProp) {
        d_ptr->m_xToProperty.remove(xProp);
        delete xProp;
    }
    d_ptr->m_propertyToX.remove(property);

    QtProperty *yProp = d_ptr->m_propertyToY[property];
    if (yProp) {
        d_ptr->m_yToProperty.remove(yProp);
        delete yProp;
    }
    d_ptr->m_propertyToY.remove(property);

    QtProperty *wProp = d_ptr->m_propertyToW[property];
    if (wProp) {
        d_ptr->m_wToProperty.remove(wProp);
        delete wProp;
    }
    d_ptr->m_propertyToW.remove(property);

    QtProperty *hProp = d_ptr->m_propertyToH[property];
    if (hProp) {
        d_ptr->m_hToProperty.remove(hProp);
        delete hProp;
    }
    d_ptr->m_propertyToH.remove(property);

    d_ptr->m_values.remove(property);
}

// QtEnumPropertyManager

class QtEnumPropertyManagerPrivate
{
    QtEnumPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtEnumPropertyManager)
public:

    struct Data
    {
        Data() : val(-1),
                 absTol(0), relTol(0), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        int val;
        int absTol;
        int relTol;
        bool check;
        QBrush foreground;
        QStringList enumNames;
        QMap<int, QIcon> enumIcons;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QtEnumPropertyManager

    \brief The QtEnumPropertyManager provides and manages enum properties.

    Each enum property has an associated list of enum names which can
    be retrieved using the enumNames() function, and set using the
    corresponding setEnumNames() function. An enum property's value is
    represented by an index in this list, and can be retrieved and set
    using the value() and setValue() slots respectively.

    Each enum value can also have an associated icon. The mapping from
    values to icons can be set using the setEnumIcons() function and
    queried with the enumIcons() function.

    In addition, QtEnumPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes. The enumNamesChanged() or enumIconsChanged() signal is emitted
    whenever the list of enum names or icons is altered.

    \sa QtAbstractPropertyManager, QtEnumEditorFactory
*/

/*!
    \fn void QtEnumPropertyManager::valueChanged(QtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtEnumPropertyManager::enumNamesChanged(QtProperty *property, const QStringList &names)

    This signal is emitted whenever a property created by this manager
    changes its enum names, passing a pointer to the \a property and
    the new \a names as parameters.

    \sa setEnumNames()
*/

/*!
    \fn void QtEnumPropertyManager::enumIconsChanged(QtProperty *property, const QMap<int, QIcon> &icons)

    This signal is emitted whenever a property created by this manager
    changes its enum icons, passing a pointer to the \a property and
    the new mapping of values to \a icons as parameters.

    \sa setEnumIcons()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtEnumPropertyManager::QtEnumPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtEnumPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtEnumPropertyManager::~QtEnumPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value which is an index in the
    list returned by enumNames()

    If the given property is not managed by this manager, this
    function returns -1.

    \sa enumNames(), setValue()
*/
int QtEnumPropertyManager::value(const QtProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, -1);
}

/*!
    Returns the given \a property's list of enum names.

    \sa value(), setEnumNames()
*/
QStringList QtEnumPropertyManager::enumNames(const QtProperty *property) const
{
    return getData<QStringList>(d_ptr->m_values, &QtEnumPropertyManagerPrivate::Data::enumNames, property, QStringList());
}

/*!
    Returns the given \a property's map of enum values to their icons.

    \sa value(), setEnumIcons()
*/
QMap<int, QIcon> QtEnumPropertyManager::enumIcons(const QtProperty *property) const
{
    return getData<QMap<int, QIcon> >(d_ptr->m_values, &QtEnumPropertyManagerPrivate::Data::enumIcons, property, QMap<int, QIcon>());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtEnumPropertyManager::setCheck
*/
bool QtEnumPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtEnumPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtEnumPropertyManager::valueText(const QtProperty *property) const
{
    const QtEnumPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QtEnumPropertyManagerPrivate::Data &data = it.value();

    const int v = data.val;
    if (v >= 0 && v < data.enumNames.count())
        return data.enumNames.at(v);
    return QString();
}

/*!
    \reimp
*/
QIcon QtEnumPropertyManager::valueIcon(const QtProperty *property) const
{
    const QtEnumPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    const QtEnumPropertyManagerPrivate::Data &data = it.value();

    const int v = data.val;
    return data.enumIcons.value(v);
}

/*!
 \reimp
 */
QIcon QtEnumPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtEnumPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given  \a property to \a value.

    The specified \a value must be less than the size of the given \a
    property's enumNames() list, and larger than (or equal to) 0.

    \sa value(), valueChanged()
*/
void QtEnumPropertyManager::setValue(QtProperty *property, int val)
{
    const QtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtEnumPropertyManagerPrivate::Data data = it.value();

    if (val >= data.enumNames.count())
        return;

    if (val < 0 && data.enumNames.count() > 0)
        return;

    if (val < 0)
        val = -1;

    if (data.val == val)
        return;

    data.val = val;

    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's list of enum names to \a
    enumNames. The \a property's current value is reset to 0
    indicating the first item of the list.

    If the specified \a enumNames list is empty, the \a property's
    current value is set to -1.

    \sa enumNames(), enumNamesChanged()
*/
void QtEnumPropertyManager::setEnumNames(QtProperty *property, const QStringList &enumNames)
{
    const QtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtEnumPropertyManagerPrivate::Data data = it.value();

    if (data.enumNames == enumNames)
        return;

    data.enumNames = enumNames;

    data.val = -1;

    if (enumNames.count() > 0)
        data.val = 0;

    it.value() = data;

    emit enumNamesChanged(property, data.enumNames);

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's map of enum values to their icons to \a
    enumIcons.

    Each enum value can have associated icon. This association is represented with passed \a enumIcons map.

    \sa enumNames(), enumNamesChanged()
*/
void QtEnumPropertyManager::setEnumIcons(QtProperty *property, const QMap<int, QIcon> &enumIcons)
{
    const QtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    it.value().enumIcons = enumIcons;

    emit enumIconsChanged(property, it.value().enumIcons);

    emit propertyChanged(property);
}

/*!
    Sets check status of the property.

    \sa QtEnumPropertyManager::setCheck
*/
void QtEnumPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtEnumPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtEnumPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtEnumPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtEnumPropertyManagerPrivate::Data();
}

/*!
    \reimp
*/
void QtEnumPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

// QtFlagPropertyManager

class QtFlagPropertyManagerPrivate
{
    QtFlagPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtFlagPropertyManager)
public:

    void slotBoolChanged(QtProperty *property, bool value);
    void slotPropertyDestroyed(QtProperty *property);

    struct Data
    {
        Data() : val(-1),
                 absTol(0), relTol(0), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        int val;
        int absTol;
        int relTol;
        bool check;
        QBrush foreground;
        QStringList flagNames;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtBoolPropertyManager *m_boolPropertyManager;

    QMap<const QtProperty *, QList<QtProperty *> > m_propertyToFlags;

    QMap<const QtProperty *, QtProperty *> m_flagToProperty;
};

void QtFlagPropertyManagerPrivate::slotBoolChanged(QtProperty *property, bool value)
{
    QtProperty *prop = m_flagToProperty.value(property, nullptr);
    if (prop == nullptr)
        return;

    QListIterator<QtProperty *> itProp(m_propertyToFlags[prop]);
    int level = 0;
    while (itProp.hasNext()) {
        QtProperty *p = itProp.next();
        if (p == property) {
            int v = m_values[prop].val;
            if (value) {
                v |= (1 << level);
            } else {
                v &= ~(1 << level);
            }
            q_ptr->setValue(prop, v);
            return;
        }
        level++;
    }
}

void QtFlagPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    QtProperty *flagProperty = m_flagToProperty.value(property, nullptr);
    if (flagProperty == nullptr)
        return;

    m_propertyToFlags[flagProperty].replace(m_propertyToFlags[flagProperty].indexOf(property), nullptr);
    m_flagToProperty.remove(property);
}

/*!
    \class QtFlagPropertyManager

    \brief The QtFlagPropertyManager provides and manages flag properties.

    Each flag property has an associated list of flag names which can
    be retrieved using the flagNames() function, and set using the
    corresponding setFlagNames() function.

    The flag manager provides properties with nested boolean
    subproperties representing each flag, i.e. a flag property's value
    is the binary combination of the subproperties' values. A
    property's value can be retrieved and set using the value() and
    setValue() slots respectively. The combination of flags is represented
    by single int value - that's why it's possible to store up to
    32 independent flags in one flag property.

    The subproperties are created by a QtBoolPropertyManager object. This
    manager can be retrieved using the subBoolPropertyManager() function. In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QtFlagPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes, and the flagNamesChanged() signal which is emitted
    whenever the list of flag names is altered.

    \sa QtAbstractPropertyManager, QtBoolPropertyManager
*/

/*!
    \fn void QtFlagPropertyManager::valueChanged(QtProperty *property, int value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a  property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    \fn void QtFlagPropertyManager::flagNamesChanged(QtProperty *property, const QStringList &names)

    This signal is emitted whenever a property created by this manager
    changes its flag names, passing a pointer to the \a property and the
    new \a names as parameters.

    \sa setFlagNames()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtFlagPropertyManager::QtFlagPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtFlagPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_boolPropertyManager = new QtBoolPropertyManager(this);
    d_ptr->m_boolPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(QtProperty *, bool)),
                this, SLOT(slotBoolChanged(QtProperty *, bool)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtFlagPropertyManager::~QtFlagPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that produces the nested boolean subproperties
    representing each flag.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtBoolPropertyManager *QtFlagPropertyManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns 0.

    \sa flagNames(), setValue()
*/
int QtFlagPropertyManager::value(const QtProperty *property) const
{
    return getValue<int>(d_ptr->m_values, property, 0);
}

/*!
    Returns the given \a property's list of flag names.

    \sa value(), setFlagNames()
*/
QStringList QtFlagPropertyManager::flagNames(const QtProperty *property) const
{
    return getData<QStringList>(d_ptr->m_values, &QtFlagPropertyManagerPrivate::Data::flagNames, property, QStringList());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtFlagPropertyManager::setCheck
*/
bool QtFlagPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtFlagPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtFlagPropertyManager::valueText(const QtProperty *property) const
{
    const QtFlagPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QtFlagPropertyManagerPrivate::Data &data = it.value();

    QString str;
    int level = 0;
    const QChar bar = QLatin1Char('|');
    const QStringList::const_iterator fncend = data.flagNames.constEnd();
    for (QStringList::const_iterator it =  data.flagNames.constBegin(); it != fncend; ++it) {
        if (data.val & (1 << level)) {
            if (!str.isEmpty())
                str += bar;
            str += *it;
        }

        level++;
    }
    return str;
}

/*!
 \reimp
 */
QIcon QtFlagPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtFlagPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    The specified \a value must be less than the binary combination of
    the property's flagNames() list size (i.e. less than 2\sup n,
    where \c n is the size of the list) and larger than (or equal to)
    0.

    \sa value(), valueChanged()
*/
void QtFlagPropertyManager::setValue(QtProperty *property, int val)
{
    const QtFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtFlagPropertyManagerPrivate::Data data = it.value();

    if (data.val == val)
        return;

    if (val > (1 << data.flagNames.count()) - 1)
        return;

    if (val < 0)
        return;

    data.val = val;

    it.value() = data;

    QListIterator<QtProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    int level = 0;
    while (itProp.hasNext()) {
        QtProperty *prop = itProp.next();
        if (prop)
            d_ptr->m_boolPropertyManager->setValue(prop, val & (1 << level));
        level++;
    }

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets the given \a property's list of flag names to \a flagNames. The
    property's current value is reset to 0 indicating the first item
    of the list.

    \sa flagNames(), flagNamesChanged()
*/
void QtFlagPropertyManager::setFlagNames(QtProperty *property, const QStringList &flagNames)
{
    const QtFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtFlagPropertyManagerPrivate::Data data = it.value();

    if (data.flagNames == flagNames)
        return;

    data.flagNames = flagNames;
    data.val = 0;

    it.value() = data;

    QListIterator<QtProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    while (itProp.hasNext()) {
        QtProperty *prop = itProp.next();
        if (prop) {
            d_ptr->m_flagToProperty.remove(prop);
            delete prop;
        }
    }
    d_ptr->m_propertyToFlags[property].clear();

    QStringListIterator itFlag(flagNames);
    while (itFlag.hasNext()) {
        const QString flagName = itFlag.next();
        QtProperty *prop = d_ptr->m_boolPropertyManager->addProperty();
        prop->setPropertyName(flagName);
        property->addSubProperty(prop);
        d_ptr->m_propertyToFlags[property].append(prop);
        d_ptr->m_flagToProperty[prop] = property;
    }

    emit flagNamesChanged(property, data.flagNames);

    emit propertyChanged(property);
    emit valueChanged(property, data.val);
}

/*!
    Sets check status of the property.

    \sa QtFlagPropertyManager::setCheck
*/
void QtFlagPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtFlagPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtFlagPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtFlagPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtFlagPropertyManagerPrivate::Data();

    d_ptr->m_propertyToFlags[property] = QList<QtProperty *>();
}

/*!
    \reimp
*/
void QtFlagPropertyManager::uninitializeProperty(QtProperty *property)
{
    QListIterator<QtProperty *> itProp(d_ptr->m_propertyToFlags[property]);
    while (itProp.hasNext()) {
        QtProperty *prop = itProp.next();
        if (prop) {
            d_ptr->m_flagToProperty.remove(prop);
            delete prop;
        }
    }
    d_ptr->m_propertyToFlags.remove(property);

    d_ptr->m_values.remove(property);
}

// QtSizePolicyPropertyManager

class QtSizePolicyPropertyManagerPrivate
{
    QtSizePolicyPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtSizePolicyPropertyManager)
public:

    struct Data
    {
        Data()
            : val(QSizePolicy()), check(false),
              foreground(QBrush(Qt::black, Qt::SolidPattern)){}
        QSizePolicy val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    QMap<const QtProperty *, Data> m_values;

    QtSizePolicyPropertyManagerPrivate();

    void slotIntChanged(QtProperty *property, int value);
    void slotEnumChanged(QtProperty *property, int value);
    void slotPropertyDestroyed(QtProperty *property);

    QtIntPropertyManager *m_intPropertyManager;
    QtEnumPropertyManager *m_enumPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToHPolicy;
    QMap<const QtProperty *, QtProperty *> m_propertyToVPolicy;
    QMap<const QtProperty *, QtProperty *> m_propertyToHStretch;
    QMap<const QtProperty *, QtProperty *> m_propertyToVStretch;

    QMap<const QtProperty *, QtProperty *> m_hPolicyToProperty;
    QMap<const QtProperty *, QtProperty *> m_vPolicyToProperty;
    QMap<const QtProperty *, QtProperty *> m_hStretchToProperty;
    QMap<const QtProperty *, QtProperty *> m_vStretchToProperty;
};

QtSizePolicyPropertyManagerPrivate::QtSizePolicyPropertyManagerPrivate()
{
}

void QtSizePolicyPropertyManagerPrivate::slotIntChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_hStretchToProperty.value(property, nullptr)) {
        QSizePolicy sp = m_values[prop].val;
        sp.setHorizontalStretch(value);
        q_ptr->setValue(prop, sp);
    } else if (QtProperty *prop = m_vStretchToProperty.value(property, nullptr)) {
        QSizePolicy sp = m_values[prop].val;
        sp.setVerticalStretch(value);
        q_ptr->setValue(prop, sp);
    }
}

void QtSizePolicyPropertyManagerPrivate::slotEnumChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_hPolicyToProperty.value(property, nullptr)) {
        QSizePolicy sp = m_values[prop].val;
        sp.setHorizontalPolicy(metaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    } else if (QtProperty *prop = m_vPolicyToProperty.value(property, nullptr)) {
        QSizePolicy sp = m_values[prop].val;
        sp.setVerticalPolicy(metaEnumProvider()->indexToSizePolicy(value));
        q_ptr->setValue(prop, sp);
    }
}

void QtSizePolicyPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_hStretchToProperty.value(property, nullptr)) {
        m_propertyToHStretch[pointProp] = nullptr;
        m_hStretchToProperty.remove(property);
    } else if (QtProperty *pointProp = m_vStretchToProperty.value(property, nullptr)) {
        m_propertyToVStretch[pointProp] = nullptr;
        m_vStretchToProperty.remove(property);
    } else if (QtProperty *pointProp = m_hPolicyToProperty.value(property, nullptr)) {
        m_propertyToHPolicy[pointProp] = nullptr;
        m_hPolicyToProperty.remove(property);
    } else if (QtProperty *pointProp = m_vPolicyToProperty.value(property, nullptr)) {
        m_propertyToVPolicy[pointProp] = nullptr;
        m_vPolicyToProperty.remove(property);
    }
}

/*!
    \class QtSizePolicyPropertyManager

    \brief The QtSizePolicyPropertyManager provides and manages QSizePolicy properties.

    A size policy property has nested \e horizontalPolicy, \e
    verticalPolicy, \e horizontalStretch and \e verticalStretch
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by QtIntPropertyManager and QtEnumPropertyManager
    objects. These managers can be retrieved using the subIntPropertyManager()
    and subEnumPropertyManager() functions respectively. In order to provide
    editing widgets for the subproperties in a property browser widget,
    these managers must be associated with editor factories.

    In addition, QtSizePolicyPropertyManager provides the valueChanged()
    signal which is emitted whenever a property created by this
    manager changes.

    \sa QtAbstractPropertyManager, QtIntPropertyManager, QtEnumPropertyManager
*/

/*!
    \fn void QtSizePolicyPropertyManager::valueChanged(QtProperty *property, const QSizePolicy &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtSizePolicyPropertyManager::QtSizePolicyPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtSizePolicyPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QtIntPropertyManager(this);
    d_ptr->m_intPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotIntChanged(QtProperty *, int)));
    d_ptr->m_enumPropertyManager = new QtEnumPropertyManager(this);
    d_ptr->m_enumPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotEnumChanged(QtProperty *, int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtSizePolicyPropertyManager::~QtSizePolicyPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the nested \e horizontalStretch
    and \e verticalStretch subproperties.

    In order to provide editing widgets for the mentioned subproperties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtSizePolicyPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the manager that creates the nested \e horizontalPolicy
    and \e verticalPolicy subproperties.

    In order to provide editing widgets for the mentioned subproperties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtEnumPropertyManager *QtSizePolicyPropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns the default size policy.

    \sa setValue()
*/
QSizePolicy QtSizePolicyPropertyManager::value(const QtProperty *property) const
{
    return getValue<QSizePolicy>(d_ptr->m_values, property, QSizePolicy());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtSizePolicyPropertyManager::setCheck
*/
bool QtSizePolicyPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtSizePolicyPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtSizePolicyPropertyManager::valueText(const QtProperty *property) const
{
    const QtSizePolicyPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    const QSizePolicy sp = getValue<QSizePolicy>(d_ptr->m_values, property, QSizePolicy());
    const QtMetaEnumProvider *mep = metaEnumProvider();
    const int hIndex = mep->sizePolicyToIndex(sp.horizontalPolicy());
    const int vIndex = mep->sizePolicyToIndex(sp.verticalPolicy());
    //! Unknown size policy on reading invalid uic3 files
    const QString hPolicy = hIndex != -1 ? mep->policyEnumNames().at(hIndex) : tr("<Invalid>");
    const QString vPolicy = vIndex != -1 ? mep->policyEnumNames().at(vIndex) : tr("<Invalid>");
    const QString str = tr("[%1, %2, %3, %4]").arg(hPolicy, vPolicy).arg(sp.horizontalStretch()).arg(sp.verticalStretch());
    return str;
}

/*!
 \reimp
 */
QIcon QtSizePolicyPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtSizePolicyPropertyManager::setValue(QtProperty *property, const QSizePolicy &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtSizePolicyPropertyManager::setValue(QtProperty *property, const QSizePolicy &val)
{
    const QtSizePolicyPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val == val)
        return;

    it.value().val = val;

    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToHPolicy[property],
                metaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToVPolicy[property],
                metaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToHStretch[property],
                val.horizontalStretch());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToVStretch[property],
                val.verticalStretch());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    Sets check status of the property.

    \sa QtSizePolicyPropertyManager::setCheck
*/
void QtSizePolicyPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtSizePolicyPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtSizePolicyPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtSizePolicyPropertyManager::initializeProperty(QtProperty *property)
{
    QSizePolicy val;
    d_ptr->m_values[property].val = val;

    QtProperty *hPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    hPolicyProp->setPropertyName(tr("Horizontal Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(hPolicyProp, metaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(hPolicyProp,
                metaEnumProvider()->sizePolicyToIndex(val.horizontalPolicy()));
    d_ptr->m_propertyToHPolicy[property] = hPolicyProp;
    d_ptr->m_hPolicyToProperty[hPolicyProp] = property;
    property->addSubProperty(hPolicyProp);

    QtProperty *vPolicyProp = d_ptr->m_enumPropertyManager->addProperty();
    vPolicyProp->setPropertyName(tr("Vertical Policy"));
    d_ptr->m_enumPropertyManager->setEnumNames(vPolicyProp, metaEnumProvider()->policyEnumNames());
    d_ptr->m_enumPropertyManager->setValue(vPolicyProp,
                metaEnumProvider()->sizePolicyToIndex(val.verticalPolicy()));
    d_ptr->m_propertyToVPolicy[property] = vPolicyProp;
    d_ptr->m_vPolicyToProperty[vPolicyProp] = property;
    property->addSubProperty(vPolicyProp);

    QtProperty *hStretchProp = d_ptr->m_intPropertyManager->addProperty();
    hStretchProp->setPropertyName(tr("Horizontal Stretch"));
    d_ptr->m_intPropertyManager->setValue(hStretchProp, val.horizontalStretch());
    d_ptr->m_intPropertyManager->setRange(hStretchProp, 0, 0xff);
    d_ptr->m_propertyToHStretch[property] = hStretchProp;
    d_ptr->m_hStretchToProperty[hStretchProp] = property;
    property->addSubProperty(hStretchProp);

    QtProperty *vStretchProp = d_ptr->m_intPropertyManager->addProperty();
    vStretchProp->setPropertyName(tr("Vertical Stretch"));
    d_ptr->m_intPropertyManager->setValue(vStretchProp, val.verticalStretch());
    d_ptr->m_intPropertyManager->setRange(vStretchProp, 0, 0xff);
    d_ptr->m_propertyToVStretch[property] = vStretchProp;
    d_ptr->m_vStretchToProperty[vStretchProp] = property;
    property->addSubProperty(vStretchProp);

}

/*!
    \reimp
*/
void QtSizePolicyPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *hPolicyProp = d_ptr->m_propertyToHPolicy[property];
    if (hPolicyProp) {
        d_ptr->m_hPolicyToProperty.remove(hPolicyProp);
        delete hPolicyProp;
    }
    d_ptr->m_propertyToHPolicy.remove(property);

    QtProperty *vPolicyProp = d_ptr->m_propertyToVPolicy[property];
    if (vPolicyProp) {
        d_ptr->m_vPolicyToProperty.remove(vPolicyProp);
        delete vPolicyProp;
    }
    d_ptr->m_propertyToVPolicy.remove(property);

    QtProperty *hStretchProp = d_ptr->m_propertyToHStretch[property];
    if (hStretchProp) {
        d_ptr->m_hStretchToProperty.remove(hStretchProp);
        delete hStretchProp;
    }
    d_ptr->m_propertyToHStretch.remove(property);

    QtProperty *vStretchProp = d_ptr->m_propertyToVStretch[property];
    if (vStretchProp) {
        d_ptr->m_vStretchToProperty.remove(vStretchProp);
        delete vStretchProp;
    }
    d_ptr->m_propertyToVStretch.remove(property);

    d_ptr->m_values.remove(property);
}

// QtFontPropertyManager:
// QtFontPropertyManagerPrivate has a mechanism for reacting
// to QApplication::fontDatabaseChanged() [4.5], which is emitted
// when someone loads an application font. The signals are compressed
// using a timer with interval 0, which then causes the family
// enumeration manager to re-set its strings and index values
// for each property.

Q_GLOBAL_STATIC(QFontDatabase, fontDatabase)

class QtFontPropertyManagerPrivate
{
    QtFontPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtFontPropertyManager)
public:

    struct Data
    {
        Data() : val(QFont()), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QFont val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    QtFontPropertyManagerPrivate();

    void slotIntChanged(QtProperty *property, int value);
    void slotEnumChanged(QtProperty *property, int value);
    void slotBoolChanged(QtProperty *property, bool value);
    void slotPropertyDestroyed(QtProperty *property);
    void slotFontDatabaseChanged();
    void slotFontDatabaseDelayedChange();

    QStringList m_familyNames;

    QtIntPropertyManager *m_intPropertyManager;
    QtEnumPropertyManager *m_enumPropertyManager;
    QtBoolPropertyManager *m_boolPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToFamily;
    QMap<const QtProperty *, QtProperty *> m_propertyToPointSize;
    QMap<const QtProperty *, QtProperty *> m_propertyToBold;
    QMap<const QtProperty *, QtProperty *> m_propertyToItalic;
    QMap<const QtProperty *, QtProperty *> m_propertyToUnderline;
    QMap<const QtProperty *, QtProperty *> m_propertyToStrikeOut;
    QMap<const QtProperty *, QtProperty *> m_propertyToKerning;

    QMap<const QtProperty *, QtProperty *> m_familyToProperty;
    QMap<const QtProperty *, QtProperty *> m_pointSizeToProperty;
    QMap<const QtProperty *, QtProperty *> m_boldToProperty;
    QMap<const QtProperty *, QtProperty *> m_italicToProperty;
    QMap<const QtProperty *, QtProperty *> m_underlineToProperty;
    QMap<const QtProperty *, QtProperty *> m_strikeOutToProperty;
    QMap<const QtProperty *, QtProperty *> m_kerningToProperty;

    bool m_settingValue;
    QTimer *m_fontDatabaseChangeTimer;
};

QtFontPropertyManagerPrivate::QtFontPropertyManagerPrivate() :
    m_settingValue(false),
    m_fontDatabaseChangeTimer(nullptr)
{
}

void QtFontPropertyManagerPrivate::slotIntChanged(QtProperty *property, int value)
{
    if (m_settingValue)
        return;
    if (QtProperty *prop = m_pointSizeToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setPointSize(value);
        q_ptr->setValue(prop, f);
    }
}

void QtFontPropertyManagerPrivate::slotEnumChanged(QtProperty *property, int value)
{
    if (m_settingValue)
        return;
    if (QtProperty *prop = m_familyToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setFamily(m_familyNames.at(value));
        q_ptr->setValue(prop, f);
    }
}

void QtFontPropertyManagerPrivate::slotBoolChanged(QtProperty *property, bool value)
{
    if (m_settingValue)
        return;
    if (QtProperty *prop = m_boldToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setBold(value);
        q_ptr->setValue(prop, f);
    } else if (QtProperty *prop = m_italicToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setItalic(value);
        q_ptr->setValue(prop, f);
    } else if (QtProperty *prop = m_underlineToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setUnderline(value);
        q_ptr->setValue(prop, f);
    } else if (QtProperty *prop = m_strikeOutToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setStrikeOut(value);
        q_ptr->setValue(prop, f);
    } else if (QtProperty *prop = m_kerningToProperty.value(property, nullptr)) {
        QFont f = m_values[prop].val;
        f.setKerning(value);
        q_ptr->setValue(prop, f);
    }
}

void QtFontPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_pointSizeToProperty.value(property, nullptr)) {
        m_propertyToPointSize[pointProp] = nullptr;
        m_pointSizeToProperty.remove(property);
    } else if (QtProperty *pointProp = m_familyToProperty.value(property, nullptr)) {
        m_propertyToFamily[pointProp] = nullptr;
        m_familyToProperty.remove(property);
    } else if (QtProperty *pointProp = m_boldToProperty.value(property, nullptr)) {
        m_propertyToBold[pointProp] = nullptr;
        m_boldToProperty.remove(property);
    } else if (QtProperty *pointProp = m_italicToProperty.value(property, nullptr)) {
        m_propertyToItalic[pointProp] = nullptr;
        m_italicToProperty.remove(property);
    } else if (QtProperty *pointProp = m_underlineToProperty.value(property, nullptr)) {
        m_propertyToUnderline[pointProp] = nullptr;
        m_underlineToProperty.remove(property);
    } else if (QtProperty *pointProp = m_strikeOutToProperty.value(property, nullptr)) {
        m_propertyToStrikeOut[pointProp] = nullptr;
        m_strikeOutToProperty.remove(property);
    } else if (QtProperty *pointProp = m_kerningToProperty.value(property, nullptr)) {
        m_propertyToKerning[pointProp] = nullptr;
        m_kerningToProperty.remove(property);
    }
}

void  QtFontPropertyManagerPrivate::slotFontDatabaseChanged()
{
    if (!m_fontDatabaseChangeTimer) {
        m_fontDatabaseChangeTimer = new QTimer(q_ptr);
        m_fontDatabaseChangeTimer->setInterval(0);
        m_fontDatabaseChangeTimer->setSingleShot(true);
        QObject::connect(m_fontDatabaseChangeTimer, SIGNAL(timeout()), q_ptr, SLOT(slotFontDatabaseDelayedChange()));
    }
    if (!m_fontDatabaseChangeTimer->isActive())
        m_fontDatabaseChangeTimer->start();
}

void QtFontPropertyManagerPrivate::slotFontDatabaseDelayedChange()
{
    typedef QMap<const QtProperty *, QtProperty *> PropertyPropertyMap;
    // rescan available font names
    const QStringList oldFamilies = m_familyNames;
    m_familyNames = fontDatabase()->families();

    // Adapt all existing properties
    if (!m_propertyToFamily.empty()) {
        PropertyPropertyMap::const_iterator cend = m_propertyToFamily.constEnd();
        for (PropertyPropertyMap::const_iterator it = m_propertyToFamily.constBegin(); it != cend; ++it) {
            QtProperty *familyProp = it.value();
            const int oldIdx = m_enumPropertyManager->value(familyProp);
            int newIdx = m_familyNames.indexOf(oldFamilies.at(oldIdx));
            if (newIdx < 0)
                newIdx = 0;
            m_enumPropertyManager->setEnumNames(familyProp, m_familyNames);
            m_enumPropertyManager->setValue(familyProp, newIdx);
        }
    }
}

/*!
    \class QtFontPropertyManager

    \brief The QtFontPropertyManager provides and manages QFont properties.

    A font property has nested \e family, \e pointSize, \e bold, \e
    italic, \e underline, \e strikeOut and \e kerning subproperties. The top-level
    property's value can be retrieved using the value() function, and
    set using the setValue() slot.

    The subproperties are created by QtIntPropertyManager, QtEnumPropertyManager and
    QtBoolPropertyManager objects. These managers can be retrieved using the
    corresponding subIntPropertyManager(), subEnumPropertyManager() and
    subBoolPropertyManager() functions. In order to provide editing widgets
    for the subproperties in a property browser widget, these managers
    must be associated with editor factories.

    In addition, QtFontPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtEnumPropertyManager, QtIntPropertyManager, QtBoolPropertyManager
*/

/*!
    \fn void QtFontPropertyManager::valueChanged(QtProperty *property, const QFont &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the
    new \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtFontPropertyManager::QtFontPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtFontPropertyManagerPrivate;
    d_ptr->q_ptr = this;
#if QT_VERSION >= 0x040500
    QObject::connect(qApp, SIGNAL(fontDatabaseChanged()), this, SLOT(slotFontDatabaseChanged()));
#endif

    d_ptr->m_intPropertyManager = new QtIntPropertyManager(this);
    d_ptr->m_intPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotIntChanged(QtProperty *, int)));
    d_ptr->m_enumPropertyManager = new QtEnumPropertyManager(this);
    d_ptr->m_enumPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_enumPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotEnumChanged(QtProperty *, int)));
    d_ptr->m_boolPropertyManager = new QtBoolPropertyManager(this);
    d_ptr->m_boolPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_boolPropertyManager, SIGNAL(valueChanged(QtProperty *, bool)),
                this, SLOT(slotBoolChanged(QtProperty *, bool)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
    connect(d_ptr->m_enumPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
    connect(d_ptr->m_boolPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtFontPropertyManager::~QtFontPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that creates the \e pointSize subproperty.

    In order to provide editing widgets for the \e pointSize property
    in a property browser widget, this manager must be associated
    with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtFontPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the manager that create the \e family subproperty.

    In order to provide editing widgets for the \e family property
    in a property browser widget, this manager must be associated
    with an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtEnumPropertyManager *QtFontPropertyManager::subEnumPropertyManager() const
{
    return d_ptr->m_enumPropertyManager;
}

/*!
    Returns the manager that creates the  \e bold, \e italic, \e underline,
    \e strikeOut and \e kerning subproperties.

    In order to provide editing widgets for the mentioned properties
    in a property browser widget, this manager must be associated with
    an editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtBoolPropertyManager *QtFontPropertyManager::subBoolPropertyManager() const
{
    return d_ptr->m_boolPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given property is not managed by this manager, this
    function returns a font object that uses the application's default
    font.

    \sa setValue()
*/
QFont QtFontPropertyManager::value(const QtProperty *property) const
{
    return getValue<QFont>(d_ptr->m_values, property, QFont());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtFontPropertyManager::setCheck
*/
bool QtFontPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtFontPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtFontPropertyManager::valueText(const QtProperty *property) const
{
    const QtFontPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return QtPropertyBrowserUtils::fontValueText(getValue<QFont>(d_ptr->m_values, property, QFont()));
}

/*!
    \reimp
*/
QIcon QtFontPropertyManager::valueIcon(const QtProperty *property) const
{
    const QtFontPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return QtPropertyBrowserUtils::fontValueIcon(getValue<QFont>(d_ptr->m_values, property, QFont()));
}

/*!
 \reimp
 */
QIcon QtFontPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtFontPropertyManager::setValue(QtProperty *property, const QFont &value)

    Sets the value of the given \a property to \a value. Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtFontPropertyManager::setValue(QtProperty *property, const QFont &val)
{
    const QtFontPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    const QFont oldVal = it.value().val;
    if (oldVal == val && oldVal.resolve() == val.resolve())
        return;

    it.value().val = val;

    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    bool settingValue = d_ptr->m_settingValue;
    d_ptr->m_settingValue = true;
    d_ptr->m_enumPropertyManager->setValue(d_ptr->m_propertyToFamily[property], idx);
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToPointSize[property], val.pointSize());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToBold[property], val.bold());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToItalic[property], val.italic());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToUnderline[property], val.underline());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToStrikeOut[property], val.strikeOut());
    d_ptr->m_boolPropertyManager->setValue(d_ptr->m_propertyToKerning[property], val.kerning());
    d_ptr->m_settingValue = settingValue;

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    Sets check status of the property.

    \sa QtFontPropertyManager::setCheck
*/
void QtFontPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtFontPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtFontPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtFontPropertyManager::initializeProperty(QtProperty *property)
{
    QFont val;
    d_ptr->m_values[property].val = val;

    QtProperty *familyProp = d_ptr->m_enumPropertyManager->addProperty();
    familyProp->setPropertyName(tr("Family"));
    if (d_ptr->m_familyNames.empty())
        d_ptr->m_familyNames = fontDatabase()->families();
    d_ptr->m_enumPropertyManager->setEnumNames(familyProp, d_ptr->m_familyNames);
    int idx = d_ptr->m_familyNames.indexOf(val.family());
    if (idx == -1)
        idx = 0;
    d_ptr->m_enumPropertyManager->setValue(familyProp, idx);
    d_ptr->m_propertyToFamily[property] = familyProp;
    d_ptr->m_familyToProperty[familyProp] = property;
    property->addSubProperty(familyProp);

    QtProperty *pointSizeProp = d_ptr->m_intPropertyManager->addProperty();
    pointSizeProp->setPropertyName(tr("Point Size"));
    d_ptr->m_intPropertyManager->setValue(pointSizeProp, val.pointSize());
    d_ptr->m_intPropertyManager->setMinimum(pointSizeProp, 1);
    d_ptr->m_propertyToPointSize[property] = pointSizeProp;
    d_ptr->m_pointSizeToProperty[pointSizeProp] = property;
    property->addSubProperty(pointSizeProp);

    QtProperty *boldProp = d_ptr->m_boolPropertyManager->addProperty();
    boldProp->setPropertyName(tr("Bold"));
    d_ptr->m_boolPropertyManager->setValue(boldProp, val.bold());
    d_ptr->m_propertyToBold[property] = boldProp;
    d_ptr->m_boldToProperty[boldProp] = property;
    property->addSubProperty(boldProp);

    QtProperty *italicProp = d_ptr->m_boolPropertyManager->addProperty();
    italicProp->setPropertyName(tr("Italic"));
    d_ptr->m_boolPropertyManager->setValue(italicProp, val.italic());
    d_ptr->m_propertyToItalic[property] = italicProp;
    d_ptr->m_italicToProperty[italicProp] = property;
    property->addSubProperty(italicProp);

    QtProperty *underlineProp = d_ptr->m_boolPropertyManager->addProperty();
    underlineProp->setPropertyName(tr("Underline"));
    d_ptr->m_boolPropertyManager->setValue(underlineProp, val.underline());
    d_ptr->m_propertyToUnderline[property] = underlineProp;
    d_ptr->m_underlineToProperty[underlineProp] = property;
    property->addSubProperty(underlineProp);

    QtProperty *strikeOutProp = d_ptr->m_boolPropertyManager->addProperty();
    strikeOutProp->setPropertyName(tr("Strikeout"));
    d_ptr->m_boolPropertyManager->setValue(strikeOutProp, val.strikeOut());
    d_ptr->m_propertyToStrikeOut[property] = strikeOutProp;
    d_ptr->m_strikeOutToProperty[strikeOutProp] = property;
    property->addSubProperty(strikeOutProp);

    QtProperty *kerningProp = d_ptr->m_boolPropertyManager->addProperty();
    kerningProp->setPropertyName(tr("Kerning"));
    d_ptr->m_boolPropertyManager->setValue(kerningProp, val.kerning());
    d_ptr->m_propertyToKerning[property] = kerningProp;
    d_ptr->m_kerningToProperty[kerningProp] = property;
    property->addSubProperty(kerningProp);
}

/*!
    \reimp
*/
void QtFontPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *familyProp = d_ptr->m_propertyToFamily[property];
    if (familyProp) {
        d_ptr->m_familyToProperty.remove(familyProp);
        delete familyProp;
    }
    d_ptr->m_propertyToFamily.remove(property);

    QtProperty *pointSizeProp = d_ptr->m_propertyToPointSize[property];
    if (pointSizeProp) {
        d_ptr->m_pointSizeToProperty.remove(pointSizeProp);
        delete pointSizeProp;
    }
    d_ptr->m_propertyToPointSize.remove(property);

    QtProperty *boldProp = d_ptr->m_propertyToBold[property];
    if (boldProp) {
        d_ptr->m_boldToProperty.remove(boldProp);
        delete boldProp;
    }
    d_ptr->m_propertyToBold.remove(property);

    QtProperty *italicProp = d_ptr->m_propertyToItalic[property];
    if (italicProp) {
        d_ptr->m_italicToProperty.remove(italicProp);
        delete italicProp;
    }
    d_ptr->m_propertyToItalic.remove(property);

    QtProperty *underlineProp = d_ptr->m_propertyToUnderline[property];
    if (underlineProp) {
        d_ptr->m_underlineToProperty.remove(underlineProp);
        delete underlineProp;
    }
    d_ptr->m_propertyToUnderline.remove(property);

    QtProperty *strikeOutProp = d_ptr->m_propertyToStrikeOut[property];
    if (strikeOutProp) {
        d_ptr->m_strikeOutToProperty.remove(strikeOutProp);
        delete strikeOutProp;
    }
    d_ptr->m_propertyToStrikeOut.remove(property);

    QtProperty *kerningProp = d_ptr->m_propertyToKerning[property];
    if (kerningProp) {
        d_ptr->m_kerningToProperty.remove(kerningProp);
        delete kerningProp;
    }
    d_ptr->m_propertyToKerning.remove(property);

    d_ptr->m_values.remove(property);
}

// QtColorPropertyManager

class QtColorPropertyManagerPrivate
{
    QtColorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtColorPropertyManager)
public:

    struct Data
    {
        Data() : val(QColor()), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QColor val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;

    void slotIntChanged(QtProperty *property, int value);
    void slotPropertyDestroyed(QtProperty *property);

    QtIntPropertyManager *m_intPropertyManager;

    QMap<const QtProperty *, QtProperty *> m_propertyToR;
    QMap<const QtProperty *, QtProperty *> m_propertyToG;
    QMap<const QtProperty *, QtProperty *> m_propertyToB;
    QMap<const QtProperty *, QtProperty *> m_propertyToA;

    QMap<const QtProperty *, QtProperty *> m_rToProperty;
    QMap<const QtProperty *, QtProperty *> m_gToProperty;
    QMap<const QtProperty *, QtProperty *> m_bToProperty;
    QMap<const QtProperty *, QtProperty *> m_aToProperty;
};

void QtColorPropertyManagerPrivate::slotIntChanged(QtProperty *property, int value)
{
    if (QtProperty *prop = m_rToProperty.value(property, nullptr)) {
        QColor c = m_values[prop].val;
        c.setRed(value);
        q_ptr->setValue(prop, c);
    } else if (QtProperty *prop = m_gToProperty.value(property, nullptr)) {
        QColor c = m_values[prop].val;
        c.setGreen(value);
        q_ptr->setValue(prop, c);
    } else if (QtProperty *prop = m_bToProperty.value(property, nullptr)) {
        QColor c = m_values[prop].val;
        c.setBlue(value);
        q_ptr->setValue(prop, c);
    } else if (QtProperty *prop = m_aToProperty.value(property, nullptr)) {
        QColor c = m_values[prop].val;
        c.setAlpha(value);
        q_ptr->setValue(prop, c);
    }
}

void QtColorPropertyManagerPrivate::slotPropertyDestroyed(QtProperty *property)
{
    if (QtProperty *pointProp = m_rToProperty.value(property, nullptr)) {
        m_propertyToR[pointProp] = nullptr;
        m_rToProperty.remove(property);
    } else if (QtProperty *pointProp = m_gToProperty.value(property, nullptr)) {
        m_propertyToG[pointProp] = nullptr;
        m_gToProperty.remove(property);
    } else if (QtProperty *pointProp = m_bToProperty.value(property, nullptr)) {
        m_propertyToB[pointProp] = nullptr;
        m_bToProperty.remove(property);
    } else if (QtProperty *pointProp = m_aToProperty.value(property, nullptr)) {
        m_propertyToA[pointProp] = nullptr;
        m_aToProperty.remove(property);
    }
}

/*!
    \class QtColorPropertyManager

    \brief The QtColorPropertyManager provides and manages QColor properties.

    A color property has nested \e red, \e green and \e blue
    subproperties. The top-level property's value can be retrieved
    using the value() function, and set using the setValue() slot.

    The subproperties are created by a QtIntPropertyManager object. This
    manager can be retrieved using the subIntPropertyManager() function.  In
    order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    In addition, QtColorPropertyManager provides the valueChanged() signal
    which is emitted whenever a property created by this manager
    changes.

    \sa QtAbstractPropertyManager, QtAbstractPropertyBrowser, QtIntPropertyManager
*/

/*!
    \fn void QtColorPropertyManager::valueChanged(QtProperty *property, const QColor &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtColorPropertyManager::QtColorPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtColorPropertyManagerPrivate;
    d_ptr->q_ptr = this;

    d_ptr->m_intPropertyManager = new QtIntPropertyManager(this);
    d_ptr->m_intPropertyManager->setAttributesEditable(BrowserCol::CHECK, false);
    connect(d_ptr->m_intPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotIntChanged(QtProperty *, int)));

    connect(d_ptr->m_intPropertyManager, SIGNAL(propertyDestroyed(QtProperty *)),
                this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtColorPropertyManager::~QtColorPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the manager that produces the nested \e red, \e green and
    \e blue subproperties.

    In order to provide editing widgets for the subproperties in a
    property browser widget, this manager must be associated with an
    editor factory.

    \sa QtAbstractPropertyBrowser::setFactoryForManager()
*/
QtIntPropertyManager *QtColorPropertyManager::subIntPropertyManager() const
{
    return d_ptr->m_intPropertyManager;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by \e this manager, this
    function returns an invalid color.

    \sa setValue()
*/
QColor QtColorPropertyManager::value(const QtProperty *property) const
{
    return getValue<QColor>(d_ptr->m_values, property, QColor());
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtColorPropertyManager::setCheck
*/
bool QtColorPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtColorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/

QString QtColorPropertyManager::valueText(const QtProperty *property) const
{
    const QtColorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return QtPropertyBrowserUtils::colorValueText(getValue<QColor>(d_ptr->m_values, property, QColor()));
}

/*!
    \reimp
*/

QIcon QtColorPropertyManager::valueIcon(const QtProperty *property) const
{
    const QtColorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();
    return QtPropertyBrowserUtils::brushValueIcon(QBrush(getValue<QColor>(d_ptr->m_values, property, QColor())));
}

/*!
 \reimp
 */
QIcon QtColorPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtColorPropertyManager::setValue(QtProperty *property, const QColor &value)

    Sets the value of the given \a property to \a value.  Nested
    properties are updated automatically.

    \sa value(), valueChanged()
*/
void QtColorPropertyManager::setValue(QtProperty *property, const QColor &val)
{
    const QtColorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val == val)
        return;

    it.value().val = val;

    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToR[property], val.red());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToG[property], val.green());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToB[property], val.blue());
    d_ptr->m_intPropertyManager->setValue(d_ptr->m_propertyToA[property], val.alpha());

    emit propertyChanged(property);
    emit valueChanged(property, val);
}

/*!
    Sets check status of the property.

    \sa QtColorPropertyManager::setCheck
*/
void QtColorPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtColorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtColorPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtColorPropertyManager::initializeProperty(QtProperty *property)
{
    QColor val;
    d_ptr->m_values[property].val = val;

    QtProperty *rProp = d_ptr->m_intPropertyManager->addProperty();
    rProp->setPropertyName(tr("Red"));
    d_ptr->m_intPropertyManager->setValue(rProp, val.red());
    d_ptr->m_intPropertyManager->setRange(rProp, 0, 0xFF);
    d_ptr->m_propertyToR[property] = rProp;
    d_ptr->m_rToProperty[rProp] = property;
    property->addSubProperty(rProp);

    QtProperty *gProp = d_ptr->m_intPropertyManager->addProperty();
    gProp->setPropertyName(tr("Green"));
    d_ptr->m_intPropertyManager->setValue(gProp, val.green());
    d_ptr->m_intPropertyManager->setRange(gProp, 0, 0xFF);
    d_ptr->m_propertyToG[property] = gProp;
    d_ptr->m_gToProperty[gProp] = property;
    property->addSubProperty(gProp);

    QtProperty *bProp = d_ptr->m_intPropertyManager->addProperty();
    bProp->setPropertyName(tr("Blue"));
    d_ptr->m_intPropertyManager->setValue(bProp, val.blue());
    d_ptr->m_intPropertyManager->setRange(bProp, 0, 0xFF);
    d_ptr->m_propertyToB[property] = bProp;
    d_ptr->m_bToProperty[bProp] = property;
    property->addSubProperty(bProp);

    QtProperty *aProp = d_ptr->m_intPropertyManager->addProperty();
    aProp->setPropertyName(tr("Alpha"));
    d_ptr->m_intPropertyManager->setValue(aProp, val.alpha());
    d_ptr->m_intPropertyManager->setRange(aProp, 0, 0xFF);
    d_ptr->m_propertyToA[property] = aProp;
    d_ptr->m_aToProperty[aProp] = property;
    property->addSubProperty(aProp);
}

/*!
    \reimp
*/
void QtColorPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtProperty *rProp = d_ptr->m_propertyToR[property];
    if (rProp) {
        d_ptr->m_rToProperty.remove(rProp);
        delete rProp;
    }
    d_ptr->m_propertyToR.remove(property);

    QtProperty *gProp = d_ptr->m_propertyToG[property];
    if (gProp) {
        d_ptr->m_gToProperty.remove(gProp);
        delete gProp;
    }
    d_ptr->m_propertyToG.remove(property);

    QtProperty *bProp = d_ptr->m_propertyToB[property];
    if (bProp) {
        d_ptr->m_bToProperty.remove(bProp);
        delete bProp;
    }
    d_ptr->m_propertyToB.remove(property);

    QtProperty *aProp = d_ptr->m_propertyToA[property];
    if (aProp) {
        d_ptr->m_aToProperty.remove(aProp);
        delete aProp;
    }
    d_ptr->m_propertyToA.remove(property);

    d_ptr->m_values.remove(property);
}

// QtCursorPropertyManager

// Make sure icons are removed as soon as QApplication is destroyed, otherwise,
// handles are leaked on X11.
static void clearCursorDatabase();
namespace {
struct CursorDatabase : public QtCursorDatabase
{
    CursorDatabase()
    {
        qAddPostRoutine(clearCursorDatabase);
    }
};
}
Q_GLOBAL_STATIC(QtCursorDatabase, cursorDatabase)

static void clearCursorDatabase()
{
    cursorDatabase()->clear();
}

class QtCursorPropertyManagerPrivate
{
    QtCursorPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtCursorPropertyManager)
public:

    struct Data
    {
        Data() : val(QCursor()), check(false),
                 foreground(QBrush(Qt::black, Qt::SolidPattern)) {}
        QCursor val;
        bool check;
        QBrush foreground;
    };

    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    \class QtCursorPropertyManager

    \brief The QtCursorPropertyManager provides and manages QCursor properties.

    A cursor property has a current value which can be
    retrieved using the value() function, and set using the setValue()
    slot. In addition, QtCursorPropertyManager provides the
    valueChanged() signal which is emitted whenever a property created
    by this manager changes.

    \sa QtAbstractPropertyManager
*/

/*!
    \fn void QtCursorPropertyManager::valueChanged(QtProperty *property, const QCursor &value)

    This signal is emitted whenever a property created by this manager
    changes its value, passing a pointer to the \a property and the new
    \a value as parameters.

    \sa setValue()
*/

/*!
    Creates a manager with the given \a parent.
*/
QtCursorPropertyManager::QtCursorPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new QtCursorPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
QtCursorPropertyManager::~QtCursorPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a default QCursor object.

    \sa setValue()
*/
#ifndef QT_NO_CURSOR
QCursor QtCursorPropertyManager::value(const QtProperty *property) const
{
    return getValue<QCursor>(d_ptr->m_values, property, QCursor());
}
#endif

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtCursorPropertyManager::setCheck
*/
bool QtCursorPropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtCursorPropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
    \reimp
*/
QString QtCursorPropertyManager::valueText(const QtProperty *property) const
{
   const QtCursorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QString();

    return cursorDatabase()->cursorToShapeName(getValue<QCursor>(d_ptr->m_values, property, QCursor()));
}

/*!
    \reimp
*/
QIcon QtCursorPropertyManager::valueIcon(const QtProperty *property) const
{
    const QtCursorPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return cursorDatabase()->cursorToShapeIcon(getValue<QCursor>(d_ptr->m_values, property, QCursor()));
}

/*!
 \reimp
 */
QIcon QtCursorPropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    \fn void QtCursorPropertyManager::setValue(QtProperty *property, const QCursor &value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void QtCursorPropertyManager::setValue(QtProperty *property, const QCursor &value)
{
#ifndef QT_NO_CURSOR
    const QtCursorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value().val.shape() == value.shape() && value.shape() != Qt::BitmapCursor)
        return;

    it.value().val = value;

    emit propertyChanged(property);
    emit valueChanged(property, value);
#endif
}

/*!
    Sets check status of the property.

    \sa QtCursorPropertyManager::setCheck
*/
void QtCursorPropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtCursorPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtCursorPropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
    \reimp
*/
void QtCursorPropertyManager::initializeProperty(QtProperty *property)
{
#ifndef QT_NO_CURSOR
    d_ptr->m_values[property].val = QCursor();
#endif
}

/*!
    \reimp
*/
void QtCursorPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

class QtFilePropertyManagerPrivate
{
    QtFilePropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(QtFilePropertyManager)
public:
    struct Data {
        Data() : val(QString()),
                 absTol(QString()), relTol(QString()),
                 filter("All Files (*)"), fileMode(QFileDialog::AnyFile), check(false) {}
         QString val;
         QString absTol;
         QString relTol;
         QString filter;
         QFileDialog::FileMode fileMode;
         bool check;
         bool readOnly;
    };
    typedef QMap<const QtProperty *, Data> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
 \class QtFilePropertyManager

 \brief The QtFilePropertyManager provides and manages file path QString properties.

 A QString property Value has a current file path which can be
 retrieved using the value() function, and set using the setValue()
 slot. In addition, a QtString property Filter stores the file open/save dialog
 filter information.

 \sa QtAbstractPropertyManager
 */

/*!
 \fn void QtFilePropertyManager::valueChanged(QtProperty *property, const QString &value)

 This signal is emitted whenever a property created by this manager
 changes its value, passing a pointer to the \a property and the new
 \a value as parameters.

 \sa setValue()
 */

/*!
 Creates a manager with the given \a parent.
 */
QtFilePropertyManager::QtFilePropertyManager(QObject *parent)
: QtAbstractPropertyManager(parent)
{
    d_ptr = new QtFilePropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
 Destroys this manager, and all the properties it has created.
 */
QtFilePropertyManager::~QtFilePropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
 Returns the given \a property's value.

 If the given \a property is not managed by this manager, this
 function returns an empty QString.

 \sa setValue()
 */
QString QtFilePropertyManager::value(const QtProperty *property) const
{
    return getValue<QString>(d_ptr->m_values, property);
}

/*!
 Returns the given \a property's filter.

 If the given \a property is not managed by this manager, this
 function returns an empty QString.

 \sa setValue()
 */
QString QtFilePropertyManager::filter(const QtProperty *property) const
{
    return getData<QString>(d_ptr->m_values, &QtFilePropertyManagerPrivate::Data::filter, property, "");
}

/*!
 Returns the given \a property's fileMode.

 \sa setFileMode()
 */
QFileDialog::FileMode QtFilePropertyManager::fileMode(const QtProperty *property) const
{
    return getData<QFileDialog::FileMode>(d_ptr->m_values, &QtFilePropertyManagerPrivate::Data::fileMode, property, QFileDialog::AnyFile);
}

/*!
 Returns read-only status of the property.

 When property is read-only it's value can be selected and copied from editor but not modified.

 \sa QtQtFilePropertyManager::setReadOnly
 */
bool QtFilePropertyManager::isReadOnly(const QtProperty *property) const
{
    return getData<bool>(d_ptr->m_values, &QtFilePropertyManagerPrivate::Data::readOnly, property, false);
}

/*!
    Returns check status of the property.

    When property is checked a user-defined behavior is defined.

    \sa QtFilePropertyManager::setCheck
*/
bool QtFilePropertyManager::check(const QtProperty *property) const
{
    typedef QMap<const QtProperty *, QtFilePropertyManagerPrivate::Data> PropertyToData;
    typedef PropertyToData::const_iterator PropertyToDataConstIterator;
    const PropertyToDataConstIterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return false;
    return it.value().check;
}

/*!
 \fn void QtQtFilePropertyManager::setValue(QtProperty *property, const QString &value)

 Sets the value of the given \a property to \a value.

 \sa value(), valueChanged()
 */
void QtFilePropertyManager::setValue(QtProperty *property, const QString &value)
{
    const QtFilePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    QtFilePropertyManagerPrivate::Data data = it.value();

    if (data.val == value)
        return;

    data.val = value;
    it.value() = data;

    emit propertyChanged(property);
    emit valueChanged(property, value);
}

/*!
 \fn void QtQtFilePropertyManager::setFilter(QtProperty *property, const QString &filter)

 Sets the filter of the given \a property to \a filter.

 \sa filter()
 */
void QtFilePropertyManager::setFilter(QtProperty *property, const QString &filter)
{
    const QtFilePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    QtFilePropertyManagerPrivate::Data data = it.value();

    if (data.filter == filter)
        return;

    data.filter = filter;
    it.value() = data;

    emit filterChanged(property, filter);
}

/*!
 \fn void QtQtFilePropertyManager::setFileMode(QtProperty *property, const QFileDialog::FileMode mode)

 Sets the filter of the given \a property to \a filter.

 \sa filter()
 */
void QtFilePropertyManager::setFileMode(QtProperty *property, const QFileDialog::FileMode mode)
{
    const QtFilePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;
    QtFilePropertyManagerPrivate::Data data = it.value();

    if (data.fileMode == mode)
        return;

    data.fileMode = mode;
    it.value() = data;
}

/*!
 Sets read-only status of the property.

 \sa QtFilePropertyManager::setReadOnly
 */
void QtFilePropertyManager::setReadOnly(QtProperty *property, bool readOnly)
{
    const QtFilePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtFilePropertyManagerPrivate::Data data = it.value();

    if (data.readOnly == readOnly)
        return;

    data.readOnly = readOnly;
    it.value() = data;

    emit propertyChanged(property);
    emit readOnlyChanged(property, data.readOnly);
}

/*!
 \reimp
 */
QString QtFilePropertyManager::valueText(const QtProperty *property) const
{
    return value(property);
}

/*!
 \reimp
 */
QIcon QtFilePropertyManager::checkIcon(const QtProperty *property) const
{
    if (!attributesEditable(BrowserCol::CHECK))
        return QIcon();
    return property->check() ? drawCheckBox(true) : drawCheckBox(false);
}

/*!
    Sets check status of the property.

    \sa QtFilePropertyManager::setCheck
*/
void QtFilePropertyManager::setCheck(QtProperty *property, bool check)
{
    const QtFilePropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    QtFilePropertyManagerPrivate::Data data = it.value();

    if (data.check == check)
        return;

    data.check = check;
    it.value() = data;

    emit propertyChanged(property);
    emit checkChanged(property, data.check);
}

/*!
 \reimp
 */
void QtFilePropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = QtFilePropertyManagerPrivate::Data();
}

/*!
 \reimp
 */
void QtFilePropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

#if QT_VERSION >= 0x040400
QT_END_NAMESPACE
#endif

#include "moc_qtpropertymanager.cpp"
#include "qtpropertymanager.moc"
