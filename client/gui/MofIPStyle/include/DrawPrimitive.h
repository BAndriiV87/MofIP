#ifndef DRAW_PRIMITIVE
#define DRAW_PRIMITIVE

#include <iostream>

#include <QtWidgets>

class IDrawPrimitive {
public:
	virtual ~IDrawPrimitive() {}
	virtual void operator()(const QProxyStyle *proxy, QStyle::PrimitiveElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget) = 0;
public:
	static bool print_type;
	static void print(bool flag) { print_type = flag; }
	static bool call_standard;
	static void call(bool flag) { call_standard = flag; }
};

IDrawPrimitive* getDrawPrimitive(QStyle::PrimitiveElement element);

#define methoddrawPrimitive \
		void operator()(const QProxyStyle *proxy, QStyle::PrimitiveElement element, const QStyleOption* option, \
								QPainter* painter, const QWidget* widget)

template <int value>
class DrawPrimitive : public IDrawPrimitive {
public:
	methoddrawPrimitive;
};

#define drawPrimitiveClassSceleton(style_type) \
		template <> \
		class DrawPrimitive<QStyle::##style_type> : public IDrawPrimitive { \
			enum { style = QStyle::##style_type }; \
		public: \
			methoddrawPrimitive; \
		};

drawPrimitiveClassSceleton(PE_FrameTabWidget)
drawPrimitiveClassSceleton(PE_PanelButtonCommand)

#endif // DRAW_PRIMITIVE
