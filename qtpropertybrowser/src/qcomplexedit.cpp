//
//  qcomplexedit.cpp
//  demo
//
//  Created by Dylan Bespalko on 2015-02-07.
//
//

#include "qcomplexedit.h"
#include <QHBoxLayout>
#include <QApplication>

#include <qlineedit.h>
#include <qlabel.h>
#include <qlocale.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <complex>
#include <stdio.h>

#include <QStyleOption>
#include <QPainter>

#ifdef Q_CC_MSVC
    #define isnan(x) _isnan(x)
    #define isinf(x) (!_finite(x) && !isnan(x))
    #define fpu_error(x) (isinf(x) || isnan(x))
#else
    #define isnan(x) std::isnan(x)
    #define isinf(x) std::isinf(x)
    #define fpu_error(x) (isinf(x) || isnan(x))
#endif

QT_BEGIN_NAMESPACE

QMap<Format, QString> FormatNameMap = {
    {Format::RE, "Re"},
    {Format::RE_IM, "Re+Imj"},
    {Format::LIN_DEG, QString("Lin") + QString(QChar(0x2220)) + QString("Deg")},
    {Format::LOG_DEG, QString("Log") + QString(QChar(0x2220)) + QString("Deg")}
};

QMap<Scale, QString> ScaleNameMap = {
    {Scale::p, "p"},
    {Scale::n, "n"},
    {Scale::u, "u"},
    {Scale::m, "m"},
    {Scale::_, " "},
    {Scale::K, "K"},
    {Scale::M, "M"},
    {Scale::G, "G"},
    {Scale::T, "T"},
};
QMap<Scale, int> ScaleValueMap = {
    {Scale::p, -12},
    {Scale::n, -9},
    {Scale::u, -6},
    {Scale::m, -3},
    {Scale::_, 0},
    {Scale::K, 3},
    {Scale::M, 6},
    {Scale::G, 9},
    {Scale::T, 12},
};

QMap<PkAvg, QString> PkAvgNameMap = {
    {PkAvg::PK, "pk"},
    {PkAvg::AVG, "avg"},
};
QMap<Domain, QString> DomainNameMap = {
    {Domain::TF, "TF"},
    {Domain::FF, "FF"},
    {Domain::FT, "FT"},
    {Domain::TT, "TT"},
    {Domain::TH, "TH"},
};
QMap<Attribute, QString> AttributeNameMap = {
    {Attribute::UNIT, "Unit"},
    {Attribute::PKAVG, "PkAvg"},
    {Attribute::FORMAT, "Format"},
    {Attribute::MINIMUM, "Minimum"},
    {Attribute::MAXIMUM, "Maximum"},
};

double infinity(std::numeric_limits<double>::infinity());
double neg_infinity(-std::numeric_limits<double>::infinity());
double highest(std::numeric_limits<double>::max());
double lowest(-std::numeric_limits<double>::max());

const QRegExp regExps[4] = {
    QRegExp("\\s*([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+|inf)(?:[eE][+-]?[0-9]+)?).*"),
    QRegExp("\\s*([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+|inf)(?:[eE][+-]?[0-9]+)?)?\\s*([+-]?)\\s*(?:([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+|inf)(?:[eE][+-]?[0-9]+)?)[JjIi])?.*"),
    QRegExp("\\s*([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+|inf)(?:[eE][+-]?[0-9]+)?)(\\s*[<\\x2220]\\s*)?([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+)(?:[eE][+-]?[0-9]+)?)?.*"),
    QRegExp("\\s*([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+|inf)(?:[eE][+-]?[0-9]+)?)(\\s*[<\\x2220]\\s*)?([+-]?(?:(?:\\d+(?:\\.\\d*)?)|\\.\\d+)(?:[eE][+-]?[0-9]+)?)?.*")};

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

QString double2str(double val, int precision)
{
    char text[50];
    if(val < lowest)
        std::sprintf(text,"%s","-inf");
    else if(val > highest)
        std::sprintf(text,"%s","inf");
    else
        std::sprintf(text,"%0.*g",precision+1, val);
    return QString(text);
}

// QComplex
QComplex::QComplex(std::complex<double> parent)
: std::complex<double>(parent)
{
    
}

QComplex::QComplex(double re, double im)
: std::complex<double>(re,im)
{
    
}


// QIntEdit

class QIntEditPrivate
{
    QIntEdit *q_ptr;
    Q_DECLARE_PUBLIC(QIntEdit)
public:
    QIntEditPrivate()
        : m_value(0),
          m_precision(3),
          m_format(Format::LIN_DEG),
          m_scale(Scale::_),
          m_readOnly(false) {}

    int m_value;
    double m_minimum;
    double m_maximum;
    int m_precision;
    
    Format m_format;
    Scale m_scale;
    bool m_readOnly;
    QLineEdit* m_edit;
    
private:
    QRegExpValidator *validator;
};

QIntEdit::QIntEdit(QWidget *parent) :
QWidget(parent)
{
    d_ptr = new QIntEditPrivate();
    d_ptr->q_ptr = this;
    
    d_ptr->m_edit = new QLineEdit("0");
    d_ptr->validator = new QRegExpValidator(regExps[Format::LIN_DEG], this);
    
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(d_ptr->m_edit);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));
    this->setFocusProxy(d_ptr->m_edit);
    
    connect(d_ptr->m_edit, SIGNAL(editingFinished()), this, SLOT(setValue()));
}

QIntEdit::~QIntEdit()
{
    disconnect(d_ptr->m_edit, SIGNAL(editingFinished()), this, SLOT(setValue()));
    emit destroyed(this);
}

int QIntEdit::value() const
{
    return d_ptr->m_value;
}

double QIntEdit::minimum() const
{
    return d_ptr->m_minimum;
}

double QIntEdit::maximum() const
{
    return d_ptr->m_maximum;
}

int QIntEdit::precision() const
{
    return d_ptr->m_precision;
}

Format QIntEdit::format() const
{
    return d_ptr->m_format;
}

Scale QIntEdit::scale() const
{
    return d_ptr->m_scale;
}

void QIntEdit::setValue()
{
    QString text = d_ptr->m_edit->text();
    int pos = 0;
    int val;
    
    if (!d_ptr->m_readOnly && validate(text,pos))
    {
        val = QIntEdit::str2num(d_ptr->m_edit->text(), d_ptr->m_scale, d_ptr->m_format);
        if (d_ptr->m_value != val) {
            d_ptr->m_value = val;
            emit valueChanged(val);
        }
    }
}

void QIntEdit::setValue(int val)
{
    if (d_ptr->m_value != val) {
        d_ptr->m_value = val;
        d_ptr->m_edit->setText(QIntEdit::num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
        emit valueChanged(val);
    }
}

void QIntEdit::setMinimum(double min)
{
    if (d_ptr->m_minimum != min) {
        if(d_ptr->m_value < min)
            setValue(min);
        d_ptr->m_minimum = min;
    }
}

void QIntEdit::setMaximum(double max)
{
    if (d_ptr->m_maximum != max) {
        if(d_ptr->m_value > max)
            setValue(max);
        d_ptr->m_maximum = max;
    }
}

void QIntEdit::setRange(double min, double max)
{
    if (min < max)
    {
        setMinimum(min);
        setMaximum(max);
    }
}

void QIntEdit::setPrecision(int prec)
{
    if (d_ptr->m_precision != prec) {
        d_ptr->m_precision = prec;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QIntEdit::setFormat(Format format_)
{
    if (d_ptr->m_format!= format_) {
        d_ptr->m_format = format_;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QIntEdit::setScale(Scale scale_)
{
    if (d_ptr->m_scale!= scale_) {
        d_ptr->m_scale = scale_;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QIntEdit::setReadOnly(bool readOnly)
{
    if (d_ptr->m_readOnly != readOnly)
        d_ptr->m_edit->setReadOnly(readOnly);
}

bool QIntEdit::eventFilter(QObject *obj, QEvent *ev)
{
    return QWidget::eventFilter(obj, ev);
}

void QIntEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QValidator::State QIntEdit::validate(QString &text, int &pos) const
{
    return d_ptr->validator->validate(text, pos);

}

QString QIntEdit::num2str(int val, const Scale scale, const Format format, int precision)
{
    double scaled_val;
    QString text;
    int scale_ = ScaleValueMap[scale];
    switch (format) {
        case Format::LOG_DEG:
            scaled_val = val/sqrt(pow(10, scale_));
            text = double2str(20*log10(scaled_val), precision);
            break;
        case Format::RE:
        case Format::RE_IM:
        case Format::LIN_DEG:
        default:
            scaled_val = val/pow(10, scale_);
            text = double2str(scaled_val, precision);
            break;
    }
    return text;
}

int QIntEdit::str2num(const QString &text, const Scale scale, const Format format)
{
    QRegExp regExp = regExps[format];
    int pos;
    int val = 0;
    int scale_ = ScaleValueMap[scale];
    switch (format) {
        case Format::LOG_DEG:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            val = int(pow(10,(regExp.cap(1).toDouble())/20));
            val *= sqrt(pow(10, scale_));
            break;
        case Format::RE:
        case Format::RE_IM:
        case Format::LIN_DEG:
        default:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            val = regExp.cap(1).toInt();
            val *= pow(10, scale_);
            break;
    }
    if (isinf(std::abs(val)))
        val = 0;
    return val;
}

// QDoubleEdit

class QDoubleEditPrivate
{
    QDoubleEdit *q_ptr;
    Q_DECLARE_PUBLIC(QDoubleEdit)
public:
    QDoubleEditPrivate()
        : m_value(0),
          m_precision(3),
          m_format(Format::LIN_DEG),
          m_scale(Scale::_),
          m_readOnly(false) {}

    double m_value;
    double m_minimum;
    double m_maximum;
    int m_precision;
    
    Format m_format;
    Scale m_scale;
    bool m_readOnly;
    QLineEdit* m_edit;
    
private:
    QRegExpValidator *validator;
};

QDoubleEdit::QDoubleEdit(QWidget *parent) :
QWidget(parent)
{
    d_ptr = new QDoubleEditPrivate();
    d_ptr->q_ptr = this;
    
    d_ptr->m_edit = new QLineEdit("0");
    d_ptr->validator = new QRegExpValidator(regExps[Format::LIN_DEG], this);
    
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(d_ptr->m_edit);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));
    this->setFocusProxy(d_ptr->m_edit);
    
    connect(d_ptr->m_edit, SIGNAL(editingFinished()), this, SLOT(setValue()));
}

QDoubleEdit::~QDoubleEdit()
{
    disconnect(d_ptr->m_edit, SIGNAL(editingFinished()), this, SLOT(setValue()));
    emit destroyed(this);
}

double QDoubleEdit::value() const
{
    return d_ptr->m_value;
}

double QDoubleEdit::minimum() const
{
    return d_ptr->m_minimum;
}

double QDoubleEdit::maximum() const
{
    return d_ptr->m_maximum;
}

int QDoubleEdit::precision() const
{
    return d_ptr->m_precision;
}

Format QDoubleEdit::format() const
{
    return d_ptr->m_format;
}

Scale QDoubleEdit::scale() const
{
    return d_ptr->m_scale;
}

void QDoubleEdit::setValue()
{
    QString text = d_ptr->m_edit->text();
    int pos = 0;
    double val;
    
    if (!d_ptr->m_readOnly && validate(text,pos))
    {
        val = str2num(d_ptr->m_edit->text(), d_ptr->m_scale, d_ptr->m_format);
        if (d_ptr->m_value != val) {
            d_ptr->m_value = val;
            emit valueChanged(val);
        }
    }
}

void QDoubleEdit::setValue(double val)
{
    if (d_ptr->m_value != val) {
        d_ptr->m_value = val;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
        emit valueChanged(val);
    }
}

void QDoubleEdit::setMinimum(double min)
{
    if (d_ptr->m_minimum != min) {
        if (d_ptr->m_value < min)
            setValue(min);
        d_ptr->m_minimum = min;
    }
}

void QDoubleEdit::setMaximum(double max)
{
    if (d_ptr->m_maximum != max) {
        if (d_ptr->m_value > max)
            setValue(max);
        d_ptr->m_maximum = max;
    }
}

void QDoubleEdit::setRange(double min, double max)
{
    if (min < max)
    {
        setMinimum(min);
        setMaximum(max);
    }
}

void QDoubleEdit::setPrecision(int prec)
{
    if (d_ptr->m_precision != prec) {
        d_ptr->m_precision = prec;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QDoubleEdit::setFormat(Format format_)
{
    if (d_ptr->m_format!= format_) {
        d_ptr->m_format = format_;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QDoubleEdit::setScale(Scale scale_)
{
    if (d_ptr->m_scale!= scale_) {
        d_ptr->m_scale = scale_;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QDoubleEdit::setReadOnly(bool readOnly)
{
    if (d_ptr->m_readOnly != readOnly)
    d_ptr->m_edit->setReadOnly(readOnly);
}

bool QDoubleEdit::eventFilter(QObject *obj, QEvent *ev)
{
    return QWidget::eventFilter(obj, ev);
}

void QDoubleEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QValidator::State QDoubleEdit::validate(QString &text, int &pos) const
{
    return d_ptr->validator->validate(text, pos);
    
}

QString QDoubleEdit::num2str(double val, const Scale scale, const Format format, int precision)
{
    double scaled_val;
    QString text;
    int scale_ = ScaleValueMap[scale];
    switch (format) {
        case Format::LOG_DEG:
            scaled_val = val/sqrt(pow(10, scale_));
            text = double2str(20*log10(scaled_val), precision);
            break;
        case Format::RE:
        case Format::RE_IM:
        case Format::LIN_DEG:
        default:
            scaled_val = val/pow(10, scale_);
            text = double2str(scaled_val, precision);
            break;
    }
    return text;
}

double QDoubleEdit::str2num(const QString &text, const Scale scale, const Format format)
{
    QRegExp regExp = regExps[format];
    int pos;
    double val = 0;
    int scale_ = ScaleValueMap[scale];
    switch (format) {
        case Format::LOG_DEG:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            val = pow(10,(regExp.cap(1).toDouble())/20);
            val *= sqrt(pow(10, scale_));
            break;
    case Format::RE:
    case Format::RE_IM:
    case Format::LIN_DEG:
    default:
        pos = regExp.indexIn(text);
        if (pos == -1)
            return val;
        val = regExp.cap(1).toDouble();
        val *= pow(10, scale_);
        break;
    }
    if (isinf(std::abs(val)))
        val = 0;
    return val;
}

// QComplexEdit

class QComplexEditPrivate
{
    QComplexEdit *q_ptr;
    Q_DECLARE_PUBLIC(QComplexEdit)
public:
    QComplexEditPrivate()
        : m_value(0),
          m_precision(3),
          m_format(Format::RE_IM),
          m_scale(Scale::_),
          m_readOnly(false) {}

    QComplex m_value;
    double m_minimum;
    double m_maximum;
    int m_precision;
    
    Format m_format;
    Scale m_scale;
    bool m_readOnly;
    QLineEdit* m_edit;
    
private:
    QRegExpValidator *validator;
};

QComplexEdit::QComplexEdit(QWidget *parent) :
QWidget(parent)
{
    d_ptr = new QComplexEditPrivate();
    d_ptr->q_ptr = this;
    
    d_ptr->m_edit = new QLineEdit("0");
    d_ptr->validator = new QRegExpValidator(regExps[Format::RE_IM], this);
    
    QHBoxLayout *lt = new QHBoxLayout(this);
    setupTreeViewEditorMargin(lt);
    lt->setSpacing(0);
    lt->addWidget(d_ptr->m_edit);
    lt->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Ignored));
    this->setFocusProxy(d_ptr->m_edit);
    
    connect(d_ptr->m_edit, SIGNAL(editingFinished()), this, SLOT(setValue()));
}

QComplexEdit::~QComplexEdit()
{
    disconnect(d_ptr->m_edit, SIGNAL(editingFinished()), this, SLOT(setValue()));
    emit destroyed(this);
}

QComplex QComplexEdit::value() const
{
    return d_ptr->m_value;
}

double QComplexEdit::minimum() const
{
    return d_ptr->m_minimum;
}

double QComplexEdit::maximum() const
{
    return d_ptr->m_maximum;
}

int QComplexEdit::precision() const
{
    return d_ptr->m_precision;
}

Format QComplexEdit::format() const
{
    return d_ptr->m_format;
}

Scale QComplexEdit::scale() const
{
    return d_ptr->m_scale;
}

void QComplexEdit::setValue()
{
    QString text = d_ptr->m_edit->text();
    int pos = 0;
    QComplex val;
    
    if (!d_ptr->m_readOnly && validate(text,pos))
    {
        val = QComplexEdit::str2num(d_ptr->m_edit->text(), d_ptr->m_scale, d_ptr->m_format);
        if (d_ptr->m_value != val) {
            d_ptr->m_value = val;
            emit valueChanged(val);
        }
    }
}

void QComplexEdit::setValue(const QComplex &val)
{
    if (d_ptr->m_value != val) {
        d_ptr->m_value = val;
        d_ptr->m_edit->setText(QComplexEdit::num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
        emit valueChanged(val);
    }
}

void QComplexEdit::setMinimum(double min)
{
    if (d_ptr->m_minimum != min) {
        if(abs(d_ptr->m_value) < min)
            setValue(min);
        d_ptr->m_minimum = min;
    }
}

void QComplexEdit::setMaximum(double max)
{
    if (d_ptr->m_maximum != max) {
        if(abs(d_ptr->m_value) > max)
            setValue(max);
        d_ptr->m_maximum = max;
    }
}

void QComplexEdit::setRange(double min, double max)
{
    if (min < max)
    {
        setMinimum(min);
        setMaximum(max);
    }
}

void QComplexEdit::setPrecision(int prec)
{
    if (d_ptr->m_precision != prec) {
        d_ptr->m_precision = prec;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QComplexEdit::setFormat(Format format_)
{
    if (d_ptr->m_format!= format_) {
        d_ptr->m_format = format_;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QComplexEdit::setScale(Scale scale_)
{
    if (d_ptr->m_scale!= scale_) {
        d_ptr->m_scale = scale_;
        d_ptr->m_edit->setText(num2str(d_ptr->m_value, d_ptr->m_scale, d_ptr->m_format, d_ptr->m_precision));
    }
}

void QComplexEdit::setReadOnly(bool readOnly)
{
    if (d_ptr->m_readOnly != readOnly)
        d_ptr->m_edit->setReadOnly(readOnly);
}

bool QComplexEdit::eventFilter(QObject *obj, QEvent *ev)
{
    return QWidget::eventFilter(obj, ev);
}

void QComplexEdit::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QValidator::State QComplexEdit::validate(QString &text, int &pos) const
{
    return d_ptr->validator->validate(text, pos);
    
}

QString QComplexEdit::num2str(const QComplex& val, const Scale scale, const Format format, int precision)
{
    QComplex scaled_val;
    QString text1, sep, text2;
    int scale_ = ScaleValueMap[scale];
    switch (format) {
        case Format::RE:
            scaled_val = val/pow(10, scale_);
            text1 = double2str(scaled_val.real(), precision);
            sep = QString("");
            text2 = QString("");
            break;
        case Format::RE_IM:
            scaled_val = val/pow(10, scale_);
            text1 = double2str(scaled_val.real(), precision);
            sep = QString("+");
            text2 = double2str(scaled_val.imag(), precision) + "j";
            break;
        case Format::LOG_DEG:
            scaled_val = val/sqrt(pow(10, scale_));
            text1 = double2str(20*log10(abs(scaled_val)), precision);
            sep = QString(QChar(0x2220));
            text2 = double2str(arg(scaled_val)*180/M_PI, precision);
            break;
        case Format::LIN_DEG:
        default:
            scaled_val = val/pow(10, scale_);
            text1 = double2str(abs(scaled_val), precision);
            sep = QString(QChar(0x2220));
            text2 = double2str(arg(scaled_val)*180/M_PI, precision);
            break;
    }
    return text1 + sep + text2;
}

QComplex QComplexEdit::str2num(const QString &text, const Scale scale, const Format format)
{
    QRegExp regExp = regExps[format];
    int pos;
    int scale_ = ScaleValueMap[scale];
    QComplex val = 0;
    switch (format) {
        case Format::RE:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            val = QComplex(regExp.cap(1).toDouble());
            val *= pow(10, scale_);
            break;
        case Format::RE_IM:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            if(regExp.captureCount() == 3)
                val = QComplex(regExp.cap(1).toDouble(),regExp.cap(3).toDouble());
            else
                val = QComplex(regExp.cap(1).toDouble());
            val *= pow(10, scale_);
            break;
        case Format::LOG_DEG:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            if(regExp.captureCount() == 3)
                val = std::polar(pow(10,(regExp.cap(1).toDouble())/20),regExp.cap(3).toDouble()*M_PI/180);
            else
                val = QComplex(pow(10,(regExp.cap(1).toDouble())/20),0);
            val *= sqrt(pow(10, scale_));
            break;
        case Format::LIN_DEG:
        default:
            pos = regExp.indexIn(text);
            if (pos == -1)
                return val;
            if(regExp.captureCount() == 3)
                val = std::polar(regExp.cap(1).toDouble(),regExp.cap(3).toDouble()*M_PI/180);
            else
                val = QComplex(regExp.cap(1).toDouble(),0);
            val *= pow(10, scale_);
            break;
    }
    if (isinf(std::abs(val)))
        val = 0;
    return val;
}

QT_END_NAMESPACE
