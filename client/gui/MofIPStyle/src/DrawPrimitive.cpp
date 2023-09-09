#include "DrawPrimitive.h"
#include "StyleUtility.h"

bool IDrawPrimitive::print_type = true;
bool IDrawPrimitive::call_standard = true;

#define printType if (IDrawPrimitive::print_type) std::cout << "[PRIMITIVE] " << QtEnumToString(element) << std::endl
#define callStandard if (IDrawPrimitive::call_standard) proxy->QProxyStyle::drawPrimitive(element, option, painter, widget)

// This is common class for unitialize style types
template<int value>
void DrawPrimitive<value>::operator()(const QProxyStyle* proxy, QStyle::PrimitiveElement element, 
	const QStyleOption* option, QPainter* painter, const QWidget* widget)
{
	printType;
	callStandard;
}

#define caseControl(type) case QStyle::type: \
		static IDrawPrimitive* type_##type = new DrawPrimitive<QStyle::type>; \
		primitive = type_##type; break
IDrawPrimitive* getDrawPrimitive(QStyle::PrimitiveElement element)
{
	IDrawPrimitive* primitive = nullptr;
	
	switch (element) {
		caseControl(PE_FrameTabWidget);
		caseControl(PE_PanelButtonCommand);
	default: 
		static IDrawPrimitive* CustomBase = new DrawPrimitive<QStyle::PE_CustomBase>; // common template
		primitive = CustomBase; break;
	}

	return primitive;
}

// Concrete drawPrimitive implementation
// -----------------------------------------------------------

// This is specialize classes for style type
#define templateMethodDrawPrimitive(style_type) \
void DrawPrimitive<QStyle::##style_type>::operator()(const QProxyStyle *proxy, QStyle::PrimitiveElement element, \
	const QStyleOption* option, QPainter* painter, const QWidget* widget)

// -----------------------------------------------------------

templateMethodDrawPrimitive(PE_PanelButtonCommand)
{
	printType;
    PainterStateGuard painterguard(painter);
    const QStyleOptionButton* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
    if (opt) {
        bool isenable = opt->state & QStyle::State_Enabled;
        bool ispressed = opt->state & QStyle::State_Sunken;

        QColor slightlyOpaqueBlack(0, 0, 0, 20);
        QColor bordercolor(opt->palette.brush(isenable ? QPalette::Dark : QPalette::Light).color());
        QColor shadowcolor(opt->palette.brush(QPalette::Light).color());
        
        int buttonshift = proxy->pixelMetric(QStyle::PM_ButtonShiftHorizontal, option, widget);
        int width = opt->rect.width() - buttonshift - 1;
        int height = opt->rect.height() - buttonshift - 1;
        int x = opt->rect.x() + 1;
        int y = opt->rect.y() + 1;

        int penwidth = proxy->pixelMetric(QStyle::PM_DefaultFrameWidth, opt, widget);
        qreal radius = 8;

        QRect buttonrect = QRect(x, y, width, height);
        QRect shadowrect = QRect(x + buttonshift, y + buttonshift, width, height);

        if (ispressed || !isenable) {
            QRect middlerect = QRect(QRect(x + buttonshift / 2, y + buttonshift / 2, width, height));
            buttonrect = shadowrect = middlerect;
        }

        painter->setRenderHint(QPainter::Antialiasing, true);

        // Draw shadow
        if (!ispressed || !isenable) {
            painter->fillPath(rectRoundPath(shadowrect, radius), shadowcolor);
        }
        // Draw button
        painter->setBrush(opt->palette.brush(QPalette::Light));
        painter->setPen(QPen(bordercolor, penwidth));
        painter->drawPath(rectRoundPath(buttonrect, radius));

        if (opt->state & (QStyle::State_On | QStyle::State_MouseOver)) {
            painter->fillPath(rectRoundPath(buttonrect, radius), slightlyOpaqueBlack);
        }
    }
}

templateMethodDrawPrimitive(PE_FrameTabWidget)
{
	printType;
	const QStyleOptionTabWidgetFrame* opt = qstyleoption_cast<const QStyleOptionTabWidgetFrame*>(option);
	if (opt) {
		PainterStateGuard painterguard(painter);
		int penwidth = proxy->QProxyStyle::pixelMetric(QStyle::PM_DefaultFrameWidth, opt, widget);
		QPen pen = QPen(opt->palette.brush(QPalette::Dark), penwidth);
		pen.setJoinStyle(Qt::MiterJoin);
		painter->setPen(pen);
		painter->fillRect(opt->rect, opt->palette.brush(QPalette::Base));
		painter->drawRect(opt->rect);
	}
}
