#ifndef MOFIP_STYLE_HPP
#define MOFIP_STYLE_HPP

#include <QProxyStyle>
#include <QPalette>

QT_BEGIN_NAMESPACE
class QPainterPath;
QT_END_NAMESPACE

class MofIPStyle : public QProxyStyle
{
    Q_OBJECT
public:
    MofIPStyle();

    void polish(QWidget* widget) override;
    void unpolish(QWidget* widget) override;
    QPalette standardPalette() const;

    void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
        QPainter* painter, const QWidget* widget) const override;
    void drawControl(ControlElement control, const QStyleOption* option,
        QPainter* painter, const QWidget* widget) const override;
    void drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex* option,
        QPainter* painter, const QWidget* widget = nullptr) const;
    int pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option = nullptr,
        const QWidget* widget = nullptr) const;
    QSize sizeFromContents(QStyle::ContentsType type, const QStyleOption* option,
        const QSize& contentsSize, const QWidget* widget = nullptr) const;
    QStyle::SubControl hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex* option,
        const QPoint& position, const QWidget* widget = nullptr) const;
    QIcon standardIcon(QStyle::StandardPixmap standardIcon,
        const QStyleOption* option = 0, const QWidget* widget = 0) const;
    int styleHint(QStyle::StyleHint hint, const QStyleOption* option = nullptr,
        const QWidget* widget = nullptr, QStyleHintReturn* returnData = nullptr) const;
    QRect subControlRect(QStyle::ComplexControl control,
        const QStyleOptionComplex* option, QStyle::SubControl subControl, const QWidget* widget = nullptr) const;
    QRect subElementRect(QStyle::SubElement element,
        const QStyleOption* option, const QWidget* widget = nullptr) const;
private:
    static const QFont mFont;
};

#endif // MOFIP_STYLE_HPP
