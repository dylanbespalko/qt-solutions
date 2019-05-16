//
//  qcomplexedit.h
//  demo
//
//  Created by Dylan Bespalko on 2015-02-07.
//
//

#ifndef QCOMPLEXEDIT_H
#define QCOMPLEXEDIT_H

#include <QToolButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QWidget>

#include <complex>
#include <qvalidator.h>

#if QT_VERSION >= 0x040400
QT_BEGIN_NAMESPACE
#endif

#if defined(Q_OS_WIN)
#  if !defined(QT_QTPROPERTYBROWSER_EXPORT) && !defined(QT_QTPROPERTYBROWSER_IMPORT)
#    define QT_QTPROPERTYBROWSER_EXPORT
#  elif defined(QT_QTPROPERTYBROWSER_IMPORT)
#    if defined(QT_QTPROPERTYBROWSER_EXPORT)
#      undef QT_QTPROPERTYBROWSER_EXPORT
#    endif
#    define QT_QTPROPERTYBROWSER_EXPORT __declspec(dllimport)
#  elif defined(QT_QTPROPERTYBROWSER_EXPORT)
#    undef QT_QTPROPERTYBROWSER_EXPORT
#    define QT_QTPROPERTYBROWSER_EXPORT __declspec(dllexport)
#  endif
#else
#  define QT_QTPROPERTYBROWSER_EXPORT
#endif

QString double2str(double val, int precision);

enum Format
{
    RE,
    RE_IM,
    LIN_DEG,
    LOG_DEG
};
extern QMap<Format, QString> FormatNameMap;

enum Scale {
    T,
    G,
    M,
    K,
    _,
    m,
    u,
    n,
    p,
};
extern QMap<Scale, QString> ScaleNameMap;
extern QMap<Scale, int> ScaleValueMap;

enum PkAvg
{
    PK,
    AVG
};
extern QMap<PkAvg, QString> PkAvgNameMap;

enum Domain
{
    TF,
    FF,
    FT,
    TT,
    TH,
};
extern QMap<Domain, QString> DomainNameMap;


enum Attribute
{
    NONE,
    UNIT,
    PKAVG,
    FORMAT,
    MINIMUM,
    MAXIMUM,
    CHECK
};
extern QMap<Attribute, QString> AttributeNameMap;

extern double infinity;
extern double neg_infinity;
extern double highest;
extern double lowest;

class QIntEditPrivate;

class QT_QTPROPERTYBROWSER_EXPORT QIntEdit : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Format)
public:
    explicit QIntEdit(QWidget *parent = 0);
    ~QIntEdit();
    
    int value() const;
    double minimum() const;
    double maximum() const;
    int precision() const;
    Scale scale() const;
    Format format() const;
    
    QValidator::State validate(QString &input, int &pos) const;
    bool eventFilter(QObject *obj, QEvent *ev);
    
public Q_SLOTS:
    void setValue();
    void setValue(int val);
    void setMinimum(double min);
    void setMaximum(double max);
    void setRange(double min, double max);
    void setPrecision(int);
    void setScale(Scale);
    void setFormat(Format);
    void setReadOnly(bool readOnly);
    
Q_SIGNALS:
    void valueChanged(int val);
    void destroyed(QObject *obj);
    
protected:
    void paintEvent(QPaintEvent *);
    
private:
    QIntEditPrivate *d_ptr;
    Q_DISABLE_COPY(QIntEdit)
    Q_DECLARE_PRIVATE(QIntEdit)
    
public:
    static QString num2str(int val, const Scale scale, const Format format, int precision);
    static int str2num(const QString &text, const Scale scale, const Format format);
};


class QDoubleEditPrivate;

class QT_QTPROPERTYBROWSER_EXPORT QDoubleEdit : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Format)
public:
    
    explicit QDoubleEdit(QWidget *parent = 0);
    ~QDoubleEdit();
    
    double value() const;
    double minimum() const;
    double maximum() const;
    int precision() const;
    Scale scale() const;
    Format format() const;
    
    QValidator::State validate(QString &input, int &pos) const;
    bool eventFilter(QObject *obj, QEvent *ev);
    
    public Q_SLOTS:
    void setValue();
    void setValue(double val);
    void setMinimum(double min);
    void setMaximum(double max);
    void setRange(double min, double max);
    void setPrecision(int);
    void setScale(Scale);
    void setFormat(Format);
    void setReadOnly(bool readOnly);
    
Q_SIGNALS:
    void valueChanged(double val);
    void destroyed(QObject *obj);
    
protected:
    void paintEvent(QPaintEvent *);
    
private:
    QDoubleEditPrivate *d_ptr;
    Q_DISABLE_COPY(QDoubleEdit)
    Q_DECLARE_PRIVATE(QDoubleEdit)
    
public:
    static QString num2str(double val, const Scale scale, const Format format, int precision);
    static double str2num(const QString &text, const Scale scale, const Format format);
};

class QT_QTPROPERTYBROWSER_EXPORT QComplex : public std::complex<double>
{
public:
    QComplex(double re = 0.0, double im = 0.0);
    QComplex(std::complex<double> parent);
};


class QComplexEditPrivate;

class QT_QTPROPERTYBROWSER_EXPORT QComplexEdit : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Format)
public:
    explicit QComplexEdit(QWidget *parent = 0);
    ~QComplexEdit();
    
    QComplex value() const;
    double minimum() const;
    double maximum() const;
    int precision() const;
    Scale scale() const;
    Format format() const;
    
    QValidator::State validate(QString &input, int &pos) const;
    bool eventFilter(QObject *obj, QEvent *ev);
    
    public Q_SLOTS:
    void setValue();
    void setValue(const QComplex &val);
    void setMinimum(double min);
    void setMaximum(double max);
    void setRange(double min, double max);
    void setPrecision(int);
    void setScale(Scale);
    void setFormat(Format);
    void setReadOnly(bool readOnly);
    
Q_SIGNALS:
    void valueChanged(const QComplex &val);
    void destroyed(QObject *obj);
    
protected:
    void paintEvent(QPaintEvent *);
    
private:
    QComplexEditPrivate *d_ptr;
    Q_DISABLE_COPY(QComplexEdit)
    Q_DECLARE_PRIVATE(QComplexEdit)
    
public:
    static QString num2str(const QComplex &val, const Scale scale, const Format format, int precision);
    static QComplex str2num(const QString &text, const Scale scale, const Format format);
};

class QFileEdit : public QWidget {
    Q_OBJECT

public:
    QFileEdit(QWidget *parent);
    ~QFileEdit();

    bool eventFilter(QObject *obj, QEvent *ev);

    bool fileExists(QString path) const;
    bool validExtension(QString path) const;

    public Q_SLOTS:
    void setValue(const QString &value);
    void setFilter(const QString &filter);
    void setFileMode(const QFileDialog::FileMode mode);
    void setReadOnly(const bool readOnly);

Q_SIGNALS:
    void valueChanged(const QString &value);
    void destroyed(QObject *obj);
protected:
    void paintEvent(QPaintEvent *);

private Q_SLOTS:
    void slotEditFinished();
    void slotButtonClicked();

private:
    QString m_fileName;
    QString m_filter;
    QFileDialog::FileMode m_fileMode;
    bool m_readOnly;
    QLineEdit *m_edit;
    QToolButton *m_button;
};

QT_END_NAMESPACE

#endif // QCOMPLEXEDIT_H
