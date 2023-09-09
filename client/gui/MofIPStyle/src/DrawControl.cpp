#include "DrawControl.h"
#include "StyleUtility.h"

bool IDrawControl::print_type = true;
bool IDrawControl::call_standard = true;

#define printType if (IDrawControl::print_type) std::cout << "[CONTROL] " << QtEnumToString(element) << std::endl
#define callStandard if (IDrawControl::call_standard) proxy->QProxyStyle::drawControl(element, option, painter, widget)

template<int value>
void DrawControl<value>::operator()(const QProxyStyle* proxy, QStyle::ControlElement element,
	const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
	printType;
	callStandard;
}

#define caseControl(type) case QStyle::type: \
		static IDrawControl* type_##type = new DrawControl<QStyle::type>; \
		primitive = type_##type; break
IDrawControl* getDrawControl(QStyle::ControlElement element)
{
	IDrawControl* primitive = nullptr;

	switch (element) {
		caseControl(CE_TabBarTab);
		caseControl(CE_TabBarTabLabel);
		caseControl(CE_PushButtonLabel);
	default:
		static IDrawControl* CustomBase = new DrawControl<QStyle::CE_CustomBase>; // common template
		primitive = CustomBase; break;
	}

	return primitive;
}

// Concrete drawPrimitive implementation
// -----------------------------------------------------------

#define templateMethodDrawControl(style_type) \
void DrawControl<QStyle::##style_type>::operator()(const QProxyStyle *proxy, QStyle::ControlElement element, \
	const QStyleOption* option, QPainter* painter, const QWidget* widget) const

// ============================================

templateMethodDrawControl(CE_PushButtonLabel)
{
	printType;
	PainterStateGuard painterguard(painter);
	const QStyleOptionButton* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
	if (opt) {
		bool isenable = opt->state & QStyle::State_Enabled;
		bool state = opt->state & QStyle::State_Sunken;

		int shiftbutton = proxy->pixelMetric(QStyle::PM_ButtonShiftHorizontal, option, widget);
		qreal x, y, width, height;
		x = opt->rect.x() + (state ? (shiftbutton / 2) : 0);
		y = opt->rect.y() + (state ? (shiftbutton / 2) : 0);
		width = opt->rect.width() - shiftbutton;
		height = opt->rect.height() - shiftbutton;

		Qt::Alignment align = Qt::AlignHCenter | Qt::AlignVCenter;
		QRect buttonrect = QRect(x, y, width, height);

		painter->setFont(QFont(FONT_NAME_STRING, 8));
		proxy->drawItemText(painter, buttonrect, align, opt->palette,
			true, opt->text, isenable ? QPalette::ButtonText : QPalette::BrightText);
	}
}
templateMethodDrawControl(CE_TabBarTabLabel)
{
	printType;
	const QStyleOptionTab* opt = qstyleoption_cast<const QStyleOptionTab*>(option);
	if (opt) {
		PainterStateGuard painterguard(painter);
		bool isenable = opt->state & QStyle::State_Enabled;

		Qt::Alignment align = Qt::AlignHCenter | Qt::AlignVCenter;

		// Draw text into tab
		painter->setFont(QFont(FONT_NAME_STRING, 8));
		proxy->drawItemText(painter, opt->rect, align, opt->palette,
			true, opt->text, isenable ? QPalette::ButtonText : QPalette::Light);
	}
}

templateMethodDrawControl(CE_TabBarTab)
{
	printType;
	const QStyleOptionTab* opt = qstyleoption_cast<const QStyleOptionTab*>(option);
	if (opt) {
		PainterStateGuard painterguard(painter);
		bool selected = option->state & QStyle::State_Selected;
		bool isenable = opt->state & QStyle::State_Enabled;

		int overlap = proxy->pixelMetric(QStyle::PM_TabBarBaseOverlap, option, widget);
		int penwidth = proxy->pixelMetric(QStyle::PM_DefaultFrameWidth, option, widget);
		int shifttab = proxy->pixelMetric(QStyle::PM_TabBarTabShiftHorizontal, option, widget);

		QRectF buttonrect = option->rect;
		buttonrect.setWidth(buttonrect.width() - shifttab);
		buttonrect.setHeight(buttonrect.height() - overlap);
		buttonrect = buttonrect.adjusted(overlap, 0, overlap, 0);
		QRectF fillrect = selected ? buttonrect.adjusted(0, 0, 0, penwidth) : buttonrect;

		QColor fillcolor = option->palette.brush(selected ? QPalette::Base : QPalette::Light).color();
		QColor colorpen = option->palette.brush(isenable ? QPalette::Dark : QPalette::Light).color();
		QPen pen = QPen(colorpen, penwidth);

		// Draw tabs
		painter->setRenderHint(QPainter::Antialiasing, true);
		painter->setPen(pen);
		painter->fillPath(tabpathRect(fillrect, shifttab), fillcolor);
		painter->drawPath(tabpathRect(buttonrect, shifttab));

		// Draw text into tab
		proxy->drawControl(QStyle::CE_TabBarTabLabel, option, painter, widget);
	}
}
