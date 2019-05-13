#ifndef SBK_QTINTPROPERTYMANAGERWRAPPER_H
#define SBK_QTINTPROPERTYMANAGERWRAPPER_H

#include <qtpropertymanager.h>

namespace PySide { class DynamicQMetaObject; }

class QtIntPropertyManagerWrapper : public QtIntPropertyManager
{
public:
    QtIntPropertyManagerWrapper(QObject * parent = 0);
    inline QIcon checkIcon_protected(const QtProperty * property) const { return QtIntPropertyManager::checkIcon(property); }
    QIcon checkIcon(const QtProperty * property) const override;
    inline void childEvent_protected(QChildEvent * event) { QtIntPropertyManager::childEvent(event); }
    void childEvent(QChildEvent * event) override;
    inline void connectNotify_protected(const QMetaMethod & signal) { QtIntPropertyManager::connectNotify(signal); }
    void connectNotify(const QMetaMethod & signal) override;
    inline QtProperty * createProperty_protected() { return QtIntPropertyManager::createProperty(); }
    QtProperty * createProperty() override;
    inline void customEvent_protected(QEvent * event) { QtIntPropertyManager::customEvent(event); }
    void customEvent(QEvent * event) override;
    inline void disconnectNotify_protected(const QMetaMethod & signal) { QtIntPropertyManager::disconnectNotify(signal); }
    void disconnectNotify(const QMetaMethod & signal) override;
    inline QString displayText_protected(const QtProperty * property) const { return QtIntPropertyManager::displayText(property); }
    QString displayText(const QtProperty * property) const override;
    inline QLineEdit::EchoMode echoMode_protected(const QtProperty * arg__1) const { return QtIntPropertyManager::echoMode(arg__1); }
    QLineEdit::EchoMode echoMode(const QtProperty * arg__1) const override;
    bool event(QEvent * event) override;
    bool eventFilter(QObject * watched, QEvent * event) override;
    QBrush foreground(const QtProperty * property) const override;
    inline QString formatText_protected(const QtProperty * property) const { return QtIntPropertyManager::formatText(property); }
    QString formatText(const QtProperty * property) const override;
    inline bool hasValue_protected(const QtProperty * property) const { return QtIntPropertyManager::hasValue(property); }
    bool hasValue(const QtProperty * property) const override;
    inline void initializeProperty_protected(QtProperty * property) { QtIntPropertyManager::initializeProperty(property); }
    void initializeProperty(QtProperty * property) override;
    bool isReadOnly(const QtProperty * property) const override;
    inline bool isSignalConnected_protected(const QMetaMethod & signal) const { return QtIntPropertyManager::isSignalConnected(signal); }
    inline QString maximumText_protected(const QtProperty * property) const { return QtIntPropertyManager::maximumText(property); }
    QString maximumText(const QtProperty * property) const override;
    const QMetaObject * metaObject() const override;
    inline QString minimumText_protected(const QtProperty * property) const { return QtIntPropertyManager::minimumText(property); }
    QString minimumText(const QtProperty * property) const override;
    inline QString pkAvgText_protected(const QtProperty * property) const { return QtIntPropertyManager::pkAvgText(property); }
    QString pkAvgText(const QtProperty * property) const override;
    inline int receivers_protected(const char * signal) const { return QtIntPropertyManager::receivers(signal); }
    inline QObject * sender_protected() const { return QtIntPropertyManager::sender(); }
    inline int senderSignalIndex_protected() const { return QtIntPropertyManager::senderSignalIndex(); }
    inline void timerEvent_protected(QTimerEvent * event) { QtIntPropertyManager::timerEvent(event); }
    void timerEvent(QTimerEvent * event) override;
    inline void uninitializeProperty_protected(QtProperty * property) { QtIntPropertyManager::uninitializeProperty(property); }
    void uninitializeProperty(QtProperty * property) override;
    inline QString unitText_protected(const QtProperty * property) const { return QtIntPropertyManager::unitText(property); }
    QString unitText(const QtProperty * property) const override;
    inline QIcon valueIcon_protected(const QtProperty * property) const { return QtIntPropertyManager::valueIcon(property); }
    QIcon valueIcon(const QtProperty * property) const override;
    inline QString valueText_protected(const QtProperty * property) const { return QtIntPropertyManager::valueText(property); }
    QString valueText(const QtProperty * property) const override;
    ~QtIntPropertyManagerWrapper();
public:
    int qt_metacall(QMetaObject::Call call, int id, void** args) override;
    void* qt_metacast(const char* _clname) override;
    static void pysideInitQtMetaTypes();
};

#  ifndef SBK_QTABSTRACTPROPERTYMANAGERWRAPPER_H
#  define SBK_QTABSTRACTPROPERTYMANAGERWRAPPER_H

// Inherited base class:
class QtAbstractPropertyManagerWrapper : public QtAbstractPropertyManager
{
public:
    QtAbstractPropertyManagerWrapper(QObject * parent = 0);
    inline QIcon checkIcon_protected(const QtProperty * property) const { return QtAbstractPropertyManager::checkIcon(property); }
    QIcon checkIcon(const QtProperty * property) const override;
    inline void childEvent_protected(QChildEvent * event) { QtAbstractPropertyManager::childEvent(event); }
    void childEvent(QChildEvent * event) override;
    inline void connectNotify_protected(const QMetaMethod & signal) { QtAbstractPropertyManager::connectNotify(signal); }
    void connectNotify(const QMetaMethod & signal) override;
    inline QtProperty * createProperty_protected() { return QtAbstractPropertyManager::createProperty(); }
    QtProperty * createProperty() override;
    inline void customEvent_protected(QEvent * event) { QtAbstractPropertyManager::customEvent(event); }
    void customEvent(QEvent * event) override;
    inline void disconnectNotify_protected(const QMetaMethod & signal) { QtAbstractPropertyManager::disconnectNotify(signal); }
    void disconnectNotify(const QMetaMethod & signal) override;
    inline QString displayText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::displayText(property); }
    QString displayText(const QtProperty * property) const override;
    inline QLineEdit::EchoMode echoMode_protected(const QtProperty * arg__1) const { return QtAbstractPropertyManager::echoMode(arg__1); }
    QLineEdit::EchoMode echoMode(const QtProperty * arg__1) const override;
    bool event(QEvent * event) override;
    bool eventFilter(QObject * watched, QEvent * event) override;
    inline QBrush foreground_protected(const QtProperty * property) const { return QtAbstractPropertyManager::foreground(property); }
    QBrush foreground(const QtProperty * property) const override;
    inline QString formatText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::formatText(property); }
    QString formatText(const QtProperty * property) const override;
    inline bool hasValue_protected(const QtProperty * property) const { return QtAbstractPropertyManager::hasValue(property); }
    bool hasValue(const QtProperty * property) const override;
    inline void initializeProperty_protected(QtProperty * property) { initializeProperty(property); }
    void initializeProperty(QtProperty * property) override;
    bool isReadOnly(const QtProperty * arg__1) const override;
    inline bool isSignalConnected_protected(const QMetaMethod & signal) const { return QtAbstractPropertyManager::isSignalConnected(signal); }
    inline QString maximumText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::maximumText(property); }
    QString maximumText(const QtProperty * property) const override;
    const QMetaObject * metaObject() const override;
    inline QString minimumText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::minimumText(property); }
    QString minimumText(const QtProperty * property) const override;
    inline QString pkAvgText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::pkAvgText(property); }
    QString pkAvgText(const QtProperty * property) const override;
    inline int receivers_protected(const char * signal) const { return QtAbstractPropertyManager::receivers(signal); }
    inline QObject * sender_protected() const { return QtAbstractPropertyManager::sender(); }
    inline int senderSignalIndex_protected() const { return QtAbstractPropertyManager::senderSignalIndex(); }
    inline void timerEvent_protected(QTimerEvent * event) { QtAbstractPropertyManager::timerEvent(event); }
    void timerEvent(QTimerEvent * event) override;
    inline void uninitializeProperty_protected(QtProperty * property) { QtAbstractPropertyManager::uninitializeProperty(property); }
    void uninitializeProperty(QtProperty * property) override;
    inline QString unitText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::unitText(property); }
    QString unitText(const QtProperty * property) const override;
    inline QIcon valueIcon_protected(const QtProperty * property) const { return QtAbstractPropertyManager::valueIcon(property); }
    QIcon valueIcon(const QtProperty * property) const override;
    inline QString valueText_protected(const QtProperty * property) const { return QtAbstractPropertyManager::valueText(property); }
    QString valueText(const QtProperty * property) const override;
    ~QtAbstractPropertyManagerWrapper();
public:
    int qt_metacall(QMetaObject::Call call, int id, void** args) override;
    void* qt_metacast(const char* _clname) override;
    static void pysideInitQtMetaTypes();
};

#  endif // SBK_QTABSTRACTPROPERTYMANAGERWRAPPER_H

#  ifndef SBK_QOBJECTWRAPPER_H
#  define SBK_QOBJECTWRAPPER_H

// Inherited base class:
class QObjectWrapper : public QObject
{
public:
    QObjectWrapper(QObject * parent = nullptr);
    inline void childEvent_protected(QChildEvent * event) { QObject::childEvent(event); }
    void childEvent(QChildEvent * event) override;
    inline void connectNotify_protected(const QMetaMethod & signal) { QObject::connectNotify(signal); }
    void connectNotify(const QMetaMethod & signal) override;
    inline void customEvent_protected(QEvent * event) { QObject::customEvent(event); }
    void customEvent(QEvent * event) override;
    inline void disconnectNotify_protected(const QMetaMethod & signal) { QObject::disconnectNotify(signal); }
    void disconnectNotify(const QMetaMethod & signal) override;
    bool event(QEvent * event) override;
    bool eventFilter(QObject * watched, QEvent * event) override;
    inline bool isSignalConnected_protected(const QMetaMethod & signal) const { return QObject::isSignalConnected(signal); }
    const QMetaObject * metaObject() const override;
    inline int receivers_protected(const char * signal) const { return QObject::receivers(signal); }
    inline QObject * sender_protected() const { return QObject::sender(); }
    inline int senderSignalIndex_protected() const { return QObject::senderSignalIndex(); }
    inline void timerEvent_protected(QTimerEvent * event) { QObject::timerEvent(event); }
    void timerEvent(QTimerEvent * event) override;
    ~QObjectWrapper();
public:
    int qt_metacall(QMetaObject::Call call, int id, void** args) override;
    void* qt_metacast(const char* _clname) override;
    static void pysideInitQtMetaTypes();
};

#  endif // SBK_QOBJECTWRAPPER_H

#endif // SBK_QTINTPROPERTYMANAGERWRAPPER_H
