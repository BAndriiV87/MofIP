#include "DrawComplexControl.h"
#include "StyleUtility.h"

bool IDrawComplexControl::print_type = true;
bool IDrawComplexControl::call_standard = true;

#define printType std::cout << "[COMPLEX CONTROL] " << QtEnumToString(element) << std::endl;
#define callStandard proxy->QProxyStyle::drawComplexControl(element, option, painter, widget);

// This is common class for unitialize style types
template<int value>
void DrawComplexControl<value>::operator()(const QProxyStyle* proxy, QStyle::ComplexControl element,
	const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const
{
	if (IDrawComplexControl::print_type)
		printType
	if (IDrawComplexControl::call_standard)
		callStandard
}

IDrawComplexControl* getDrawComplexControl(QStyle::ComplexControl element)
{
	IDrawComplexControl* primitive = nullptr;

	switch (element) {
	//case QStyle::CC_SpinBox:
	//	static IDrawComplexControl* SpinBox = new DrawControl<QStyle::CC_SpinBox>;
	//	primitive = SpinBox;	break;
	default:
		static IDrawComplexControl* CustomBase = new DrawComplexControl<QStyle::CC_CustomBase>; // common template
		primitive = CustomBase; break;
	}

	return primitive;
}

// Concrete drawPrimitive implementation
// -----------------------------------------------------------

// This is specialize classes for style type
#define templateMethodDrawComplexControl(style_type) \
void DrawComplexControl<QStyle::##style_type>::operator()(const QProxyStyle *proxy, QStyle::ComplexControl element, \
	const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget) const

// PE_PanelButtonCommand
//templateMethodDrawComplexControl(CC_SpinBox)
//{
//	printType
//	callStandard
//}
