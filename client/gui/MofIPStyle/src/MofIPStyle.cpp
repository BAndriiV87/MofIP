#include <QtWidgets>
#include <QObject>

#include "MofIPStyle.h"
#include "StyleUtility.h"
#include "DrawPrimitive.h"
#include "DrawControl.h"
#include "DrawComplexControl.h"

#define printsubmethod(type, result) QDebug debug = qDebug(); debug.noquote(); debug << "[SUBMETHOD] setnewval(QStyle::" << \
                       QString::fromStdString(QtEnumToString(type)) << ", " << result << "); // default: " << result
#define printsubmethod(type, result) 0
#define setnewval(type, val) case type: result = val; break

MofIPStyle::MofIPStyle()
    : QProxyStyle(QStyleFactory::create("windows"))
{
    IDrawPrimitive::print(false);
    IDrawPrimitive::call(false);
    IDrawControl::print(true);
    IDrawControl::call(true);
    IDrawComplexControl::print(false);
    IDrawComplexControl::call(false);
    setObjectName("MofIPStyle");
    qApp->setPalette(standardPalette());
}

QPalette MofIPStyle::standardPalette() const {
    QPalette palette = QProxyStyle::standardPalette();

    //palette.setBrush(QPalette::WindowText, Qt::black);
    palette.setBrush(QPalette::Button, Qt::lightGray);
    palette.setBrush(QPalette::Dark, Qt::darkGray);
    palette.setBrush(QPalette::Mid, Qt::gray);
    palette.setBrush(QPalette::Light, QColor(221, 221, 221, 255));
    //palette.setBrush(QPalette::Midlight, Qt::gray);
    //palette.setBrush(QPalette::Text, Qt::green);
    palette.setBrush(QPalette::BrightText, Qt::lightGray);
    palette.setBrush(QPalette::ButtonText, Qt::black);
    palette.setBrush(QPalette::Base, Qt::white);
    palette.setBrush(QPalette::Window, Qt::white);
    //palette.setBrush(QPalette::Shadow, Qt::darkRed);
    //palette.setBrush(QPalette::Highlight, Qt::darkGreen);
    //palette.setBrush(QPalette::HighlightedText, Qt::darkBlue);
    //palette.setBrush(QPalette::Link, Qt::darkCyan);
    //palette.setBrush(QPalette::LinkVisited, Qt::darkMagenta);
    //palette.setBrush(QPalette::AlternateBase, Qt::darkYellow);
    //palette.setBrush(QPalette::NoRole, Qt::white);
    //palette.setBrush(QPalette::ToolTipBase, Qt::cyan);
    //palette.setBrush(QPalette::ToolTipText, Qt::cyan);
    //palette.setBrush(QPalette::PlaceholderText, Qt::cyan);

    return palette;
}

void MofIPStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void MofIPStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

// Draw Elements
// ----------------------------------------------

void MofIPStyle::drawPrimitive(PrimitiveElement element,
                                       const QStyleOption *option,
                                       QPainter *painter,
                                       const QWidget *widget) const
{
    getDrawPrimitive(element)->operator()(this, element, option, painter, widget);
}

void MofIPStyle::drawControl(ControlElement element,
                                     const QStyleOption *option,
                                     QPainter *painter,
                                     const QWidget *widget) const
{
    getDrawControl(element)->operator()(this, element, option, painter, widget);
}

void MofIPStyle::drawComplexControl(QStyle::ComplexControl control, 
                                    const QStyleOptionComplex * option,
                                    QPainter * painter, 
                                    const QWidget * widget) const 
{
    getDrawComplexControl(control)->operator()(this, control, option, painter, widget);
}

// Sub Method for Elements
// ----------------------------------------------

#define callmethod QProxyStyle::pixelMetric(metric, option, widget)
int MofIPStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option,
    const QWidget* widget) const 
{
    int result;
    switch (metric) {
        setnewval(QStyle::PM_DefaultFrameWidth, 1); // default:  2
        setnewval(QStyle::PM_TabBarBaseOverlap, 2); // default:  2
        setnewval(QStyle::PM_TabBarTabShiftHorizontal, 4); // default:  0
        setnewval(QStyle::PM_ButtonShiftHorizontal, 3); // default:  0

        // Debug
    default:
        result = callmethod;
    }
    printsubmethod(metric, result);
    return result;
}

#define callmethod QProxyStyle::sizeFromContents(type, option, contentsSize, widget)
QSize MofIPStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption* option,
    const QSize& contentsSize, const QWidget* widget) const 
{
    QSize result;
    switch (type) {
        //setnewval();
    default:
        result = callmethod;
    }
    printsubmethod(type, result);
    return result;
}

#define callmethod QProxyStyle::hitTestComplexControl(control, option, position, widget)
QStyle::SubControl MofIPStyle::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex* option,
    const QPoint& position, const QWidget* widget) const 
{
    QStyle::SubControl result;
    switch (control) {
        //setnewval();
    default:
        result = callmethod;
    }
    printsubmethod(control, result);
    return result;
}

#define callmethod QProxyStyle::standardIcon(standardIcon, option, widget)
QIcon MofIPStyle::standardIcon(QStyle::StandardPixmap standardIcon,
    const QStyleOption* option, const QWidget* widget) const 
{
    QIcon result;
    switch (standardIcon) {
        //setnewval();
    default:
        result = callmethod;
    }
    printsubmethod(standardIcon, -1);
    return result;
}

#define callmethod QProxyStyle::styleHint(hint, option, widget, returnData)
int MofIPStyle::styleHint(QStyle::StyleHint hint, const QStyleOption* option,
    const QWidget* widget, QStyleHintReturn* returnData) const 
{
    int result;
    switch (hint) {
        //setnewval();
    default:
        result = callmethod;
    }
    printsubmethod(hint, result);
    return result;
}

#define callmethod QProxyStyle::subControlRect(control, option, subControl, widget)
QRect MofIPStyle::subControlRect(QStyle::ComplexControl control,
    const QStyleOptionComplex* option, QStyle::SubControl subControl, const QWidget* widget) const 
{
    QRect result;
    switch (control) {
        //setnewval();
    default:
        result = callmethod;
    }
    printsubmethod(control, result);
    return result;
}

#define callmethod QProxyStyle::subElementRect(element, option, widget)
QRect MofIPStyle::subElementRect(QStyle::SubElement element,
    const QStyleOption* option, const QWidget* widget) const 
{
    QRect result;
    switch (element) {
        //setnewval();
    default:
        result = callmethod;
    }
    printsubmethod(element, result);
    return result;
}
