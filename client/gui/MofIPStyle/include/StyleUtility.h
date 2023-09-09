#ifndef STYLE_UTILITY_HPP
#define STYLE_UTILITY_HPP

#include <QtWidgets>

const QString FONT_NAME_STRING("Comic Sans MS");

QPainterPath rectRoundPath(QRectF rect, qreal radius);
QPainterPath tabpath(QRectF rect);
QPainterPath tabpathRect(QRectF rect, qreal radius);

template<typename QEnum>
static std::string QtEnumToString(const QEnum value)
{
    return std::string(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

class PainterStateGuard {
    Q_DISABLE_COPY_MOVE(PainterStateGuard)
public:
    explicit PainterStateGuard(QPainter* p) : m_painter(p) {}
    ~PainterStateGuard() {
        for (; m_level > 0; --m_level)
            m_painter->restore();
    }
    void save() {
        m_painter->save();
        ++m_level;
    }
    void restore() {
        m_painter->restore();
        --m_level;
    }
private:
    QPainter* m_painter;
    int m_level = 0;
};


#endif // STYLE_UTILITY_HPP
