#include "myStyle/MyStyle.h"

#include <QtWidgets>
#include <QObject>

#define printtype(type) qDebug()        <<  "STANDARD [" << QString(#type) << "]"
#define printtypecustom(type) qDebug()  <<  "CUSTOM   [" << QString(#type) << "]"
#define casetype(type) case QStyle::##type: printtype(type); break;

namespace {
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
} // namespace

static QPainterPath rectRoundPath(QRectF rect, qreal radius) {
    qreal halfradius = radius / 2;
    QPainterPath path;
    path.moveTo(rect.left() + halfradius, rect.top());
    path.lineTo(rect.right() - halfradius, rect.top());
    // right top corner
    path.arcTo(QRectF(rect.right() - radius, rect.top(), radius, radius), 90, -90);
    path.lineTo(rect.right(), rect.bottom() - halfradius);
    // right bottom corner
    path.arcTo(QRectF(rect.right() - radius, rect.bottom() - radius, radius, radius), 0, -90);
    path.lineTo(rect.left() + halfradius, rect.bottom());
    // left bottom corner
    path.arcTo(QRectF(rect.left(), rect.bottom() - radius, radius, radius), -90, -90);
    path.lineTo(rect.left(), rect.top() + halfradius);
    // left top corner
    path.arcTo(QRectF(rect.left(), rect.top(), radius, radius), 180, -90);
    return path;
}

const QFont MyStyle::mFont = QFont(QString("Comic Sans MS"), 10);

template<typename QEnum>
static std::string QtEnumToString(const QEnum value)
{
    return std::string(QMetaEnum::fromType<QEnum>().valueToKey(value));
}

MyStyle::MyStyle() :
    QProxyStyle(QStyleFactory::create("windows"))
{
    setObjectName("MyStyle");
    qApp->setPalette(standardPalette());
}

QPalette MyStyle::standardPalette() const {
    QPalette palette = QProxyStyle::standardPalette();

    palette.setBrush(QPalette::Base, Qt::darkGreen);
    palette.setBrush(QPalette::Window, Qt::white); // main window color
    palette.setBrush(QPalette::Light, Qt::lightGray); // this is for shadow light
    palette.setBrush(QPalette::Dark, Qt::darkGray); // shadow dark
    palette.setBrush(QPalette::Button, QColor(235, 235, 235));
    palette.setBrush(QPalette::ButtonText, Qt::black);
    palette.setBrush(QPalette::BrightText, Qt::lightGray);
    palette.setBrush(QPalette::Mid, Qt::gray);

    //palette.setBrush(QPalette::Text, Qt::black);
    //palette.setBrush(QPalette::WindowText, Qt::red);
    //palette.setBrush(QPalette::AlternateBase, Qt::green);
    //palette.setBrush(QPalette::ToolTipBase, Qt::darkGreen);
    //palette.setBrush(QPalette::ToolTipText, Qt::blue);
    //palette.setBrush(QPalette::PlaceholderText, Qt::darkBlue);
    //palette.setBrush(QPalette::Text, Qt::red);
    //palette.setBrush(QPalette::Midlight, Qt::darkYellow);
    //palette.setBrush(QPalette::Shadow, Qt::lightGray);
    //palette.setBrush(QPalette::Highlight, Qt::black);
    //palette.setBrush(QPalette::HighlightedText, Qt::black);
    //palette.setBrush(QPalette::Link, Qt::black);
    //palette.setBrush(QPalette::LinkVisited, Qt::black);

    return palette;
}

void MyStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void MyStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

#define casePrimitiveElement(type) case QStyle::##type: qDebug() << "[" << QString(#type) << "]";
#define DRAW_PRIMITIVE_STANDARD QProxyStyle::drawPrimitive(element, option, painter, widget);

#define BUTTON_SIZE QSize(opt->rect.width(), opt->rect.height())
#define BUTTON_WIDTH BUTTON_SIZE.width()
#define BUTTON_HEIGHT BUTTON_SIZE.height()
#define BUTTON_RECT(topleft) QRectF(topleft, topleft, BUTTON_WIDTH - boundrect, BUTTON_HEIGHT - boundrect)

void MyStyle::drawPrimitive(PrimitiveElement element,
                                       const QStyleOption *option,
                                       QPainter *painter,
                                       const QWidget *widget) const
{
    switch (element) {
        casePrimitiveElement(QStyle::PE_FrameStatusBar)
            DRAW_PRIMITIVE_STANDARD
            break;
    case QStyle::PE_PanelButtonCommand: {
        printtypecustom(QStyle::PE_PanelButtonCommand);
        PainterStateGuard painterguard(painter);
        const QStyleOptionButton* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
        if (opt) {

            bool isenable = opt->state & QStyle::State_Enabled;
            bool isdown = opt->state & QStyle::State_Sunken;

            QColor slightlyOpaqueBlack(0, 0, 0, 20);
            QColor contourbutton(opt->palette.brush(isenable ? QPalette::Dark : QPalette::Light).color());
            int buttonshift = pixelMetric(QStyle::PM_ButtonShiftHorizontal, option, widget);
            int width = opt->rect.width() - buttonshift - 1;
            int height = opt->rect.height() - buttonshift - 1;
            int x = opt->rect.x() + 1;
            int y = opt->rect.y() + 1;
            qreal radius = height;

            QRect buttonrect = QRect(x, y, width, height);
            QRect shadowrect = QRect(x + buttonshift, y + buttonshift, width, height);

            if (isdown || !isenable) {
                QRect middlerect = QRect(QRect(x + buttonshift / 2, y + buttonshift / 2, width, height));
                buttonrect = shadowrect = middlerect;
            }

            painter->setRenderHint(QPainter::Antialiasing, true);

            painter->setPen(Qt::NoPen);
            // Draw shadow
            if (!isdown || !isenable) {
                painter->setBrush(opt->palette.brush(QPalette::Mid));
                painter->drawPath(rectRoundPath(shadowrect, radius));
            }
            // Draw button
            painter->setBrush(opt->palette.brush(QPalette::Button));
            painter->drawPath(rectRoundPath(buttonrect, radius));

            if (opt->state & (QStyle::State_On | QStyle::State_MouseOver)) {
                painter->fillPath(rectRoundPath(buttonrect, radius), slightlyOpaqueBlack);
            }
        }
    } break;
        casePrimitiveElement(QStyle::PE_FrameDefaultButton)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelButtonBevel)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelButtonTool)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelLineEdit)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorButtonDropDown)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorArrowUp)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorArrowDown)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorArrowRight)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorArrowLeft)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorSpinUp)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorSpinDown)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorSpinPlus)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorSpinMinus)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorItemViewItemCheck)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorCheckBox)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorRadioButton)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorDockWidgetResizeHandle)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_Frame)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameMenu)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelMenuBar)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelScrollAreaCorner)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameDockWidget)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameTabWidget)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameLineEdit)
            DRAW_PRIMITIVE_STANDARD
            break;
    case QStyle::PE_FrameGroupBox: {
        printtypecustom(QStyle::PE_FrameGroupBox);
        PainterStateGuard painterguard(painter);
        const QStyleOptionGroupBox* opt = qstyleoption_cast<const QStyleOptionGroupBox*>(option);
        if (opt) {
            int shiftframe = 1;
            qreal fontheight = QFontMetrics(mFont).height();
            int x = opt->rect.x() + shiftframe;
            int y = opt->rect.y() + fontheight * 0.7;
            int width = opt->rect.width() - shiftframe - shiftframe;
            int height = opt->rect.height() - fontheight * 0.7 - shiftframe;
            QRect rect = QRect(x, y, width, height);

            int radiusframe = 10;
            int widthframe = pixelMetric(QStyle::PM_DefaultFrameWidth, option, widget);
            QColor pen = opt->palette.brush((opt->state & (QStyle::State_Enabled)) 
                ? QPalette::Dark : QPalette::Light).color();

            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->setPen(QPen(pen, widthframe));
            painter->drawPath(rectRoundPath(rect, radiusframe));
        }
    } break;
        casePrimitiveElement(QStyle::PE_FrameButtonBevel)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameButtonTool)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorHeaderArrow)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameWindow)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorMenuCheckMark)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorProgressChunk)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorBranch)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorToolBarHandle)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorToolBarSeparator)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelToolBar)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelTipLabel)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_FrameTabBarBase)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorTabTear)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorTabTearRight)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorColumnViewArrow)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_Widget)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_CustomBase)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorItemViewItemDrop)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelItemViewItem)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelItemViewRow)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelStatusBar)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_IndicatorTabClose)
            DRAW_PRIMITIVE_STANDARD
            break;
        casePrimitiveElement(QStyle::PE_PanelMenu)
            DRAW_PRIMITIVE_STANDARD
            break;
    default:
        QtEnumToString(element);
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}

#define DRAW_CONTROL_STANDARD QProxyStyle::drawControl(element, option, painter, widget);
void MyStyle::drawControl(ControlElement element,
                                     const QStyleOption *option,
                                     QPainter *painter,
                                     const QWidget *widget) const
{
    painter->save();

    switch (element) {
    case QStyle::CE_PushButton:
            DRAW_CONTROL_STANDARD
            break;
    case QStyle::CE_PushButtonBevel:
            DRAW_CONTROL_STANDARD
            break;
    case QStyle::CE_PushButtonLabel: {
        printtypecustom(QStyle::CE_PushButtonLabel);
        PainterStateGuard painterguard(painter);
        const QStyleOptionButton* opt = qstyleoption_cast<const QStyleOptionButton*>(option);
        if (opt) {
            bool isenable = opt->state & QStyle::State_Enabled;
            bool state = opt->state & QStyle::State_Sunken;
            
            int shiftbutton = pixelMetric(QStyle::PM_ButtonShiftHorizontal, option, widget);
            qreal x, y, width, height;
            x = opt->rect.x() + (state ? (shiftbutton / 2) : 0);
            y = opt->rect.y() + (state ? (shiftbutton / 2) : 0);
            width = opt->rect.width() - shiftbutton;
            height = opt->rect.height() - shiftbutton;

            Qt::Alignment align = Qt::AlignHCenter | Qt::AlignVCenter;
            QRect buttonrect = QRect(x, y, width, height);

            painter->setFont(MyStyle::mFont);
            drawItemText(painter, buttonrect, align, opt->palette,
                true, opt->text, isenable ? QPalette::ButtonText : QPalette::BrightText);
        }
    } break;
        casetype(QStyle::CE_DockWidgetTitle)
            DRAW_CONTROL_STANDARD
            break;
    case QStyle::CE_Splitter: {
        printtypecustom(QStyle::CE_PushButtonLabel);
        PainterStateGuard painterguard(painter);
        if (option) {
            bool sunken = option->state & QStyle::State_Sunken;
            QColor color = option->palette.brush(sunken ? QPalette::Dark : QPalette::Light).color();
            painter->fillRect(option->rect, color);
        }
        
    } break;
        casetype(QStyle::CE_CheckBox)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_CheckBoxLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_RadioButton)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_RadioButtonLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_TabBarTab)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_TabBarTabShape)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_TabBarTabLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ProgressBar)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ProgressBarGroove)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ProgressBarContents)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ProgressBarLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ToolButtonLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuBarItem)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuBarEmptyArea)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuItem)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuScroller)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuTearoff)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuEmptyArea)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuHMargin)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_MenuVMargin)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ToolBoxTab)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_SizeGrip)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_Header)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_HeaderSection)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_HeaderLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarAddLine)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarSubLine)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarAddPage)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarSubPage)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarSlider)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarFirst)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ScrollBarLast)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_RubberBand)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_FocusFrame)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ItemViewItem)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_CustomBase)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ComboBoxLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ToolBar)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ToolBoxTabShape)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ToolBoxTabLabel)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_HeaderEmptyArea)
            DRAW_CONTROL_STANDARD
            break;
        casetype(QStyle::CE_ShapedFrame)
            DRAW_CONTROL_STANDARD
            break;
        break;
    default:
        QtEnumToString(element);
        QProxyStyle::drawControl(element, option, painter, widget);
    }

    painter->restore();
}

#define DRAW_COMPLEX_STANDARD QProxyStyle::drawComplexControl(control, option, painter, widget);
void MyStyle::drawComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex * option,
    QPainter * painter, const QWidget * widget) const 
{
    painter->save();

    switch (control) {
        casetype(QStyle::CC_SpinBox)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_ComboBox)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_ScrollBar)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_Slider)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_ToolButton)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_TitleBar)
            DRAW_COMPLEX_STANDARD
            break;
    case QStyle::CC_GroupBox: {
        printtypecustom(QStyle::CC_GroupBox);
        PainterStateGuard painterguard(painter);
        const QStyleOptionGroupBox* opt = qstyleoption_cast<const QStyleOptionGroupBox*>(option);
        if (opt) {
            proxy()->drawPrimitive(QStyle::PE_FrameGroupBox, option, painter, widget);
            const QGroupBox* grpbx = qobject_cast<const QGroupBox*>(widget);
            if (grpbx) {
                QFontMetrics metric(mFont);
                QString title = grpbx->title();
                qreal fontheight = metric.height();
                qreal fontwidth = metric.width(title);
                QRect textrect = QRect(
                    opt->rect.x() + opt->rect.width() / 2 - fontwidth / 2, 
                    opt->rect.y(),
                    fontwidth, 
                    fontheight);
                painter->fillRect(textrect, opt->palette.brush(QPalette::Window));
                painter->setFont(MyStyle::mFont);
                drawItemText(painter, textrect, Qt::AlignHCenter | Qt::AlignVCenter, option->palette,
                    true, title, (option->state & QStyle::State_Enabled) ? QPalette::ButtonText : QPalette::BrightText);
            }
        }
    } break;
        casetype(QStyle::CC_Dial)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_MdiControls)
            DRAW_COMPLEX_STANDARD
            break;
        casetype(QStyle::CC_CustomBase)
            DRAW_COMPLEX_STANDARD
            break;
    default:
        QtEnumToString(control);
        QProxyStyle::drawComplexControl(control, option, painter, widget);
    }
    painter->restore();
}

#define DRAW_PIXEL_METRIC QProxyStyle::pixelMetric(metric, option, widget);
int MyStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption* option,
    const QWidget* widget) const {
    int result = DRAW_PIXEL_METRIC
    switch (metric) {
        casetype(QStyle::PM_ButtonMargin)
        casetype(QStyle::PM_ButtonDefaultIndicator)
        casetype(QStyle::PM_MenuButtonIndicator)
    case QStyle::PM_ButtonShiftHorizontal:
    case QStyle::PM_ButtonShiftVertical: printtypecustom(QStyle::PM_ButtonShiftHorizontal_PM_ButtonShiftVertical); result = 2; break;
    case QStyle::PM_DefaultFrameWidth: result = 1; break;
        casetype(QStyle::PM_SpinBoxFrameWidth)
        casetype(QStyle::PM_ComboBoxFrameWidth)
        casetype(QStyle::PM_MaximumDragDistance)
        casetype(QStyle::PM_ScrollBarExtent)
        casetype(QStyle::PM_ScrollBarSliderMin)
        casetype(QStyle::PM_SliderThickness)             // total slider thickness
        casetype(QStyle::PM_SliderControlThickness)      // thickness of the business part
        casetype(QStyle::PM_SliderLength)                // total length of slider
        casetype(QStyle::PM_SliderTickmarkOffset)        //
        casetype(QStyle::PM_SliderSpaceAvailable)        // available space for slider to move
        casetype(QStyle::PM_DockWidgetSeparatorExtent)
        casetype(QStyle::PM_DockWidgetHandleExtent)
        casetype(QStyle::PM_DockWidgetFrameWidth)
        casetype(QStyle::PM_TabBarTabOverlap)
        casetype(QStyle::PM_TabBarTabHSpace)
        casetype(QStyle::PM_TabBarTabVSpace)
        casetype(QStyle::PM_TabBarBaseHeight)
        casetype(QStyle::PM_TabBarBaseOverlap)
        casetype(QStyle::PM_ProgressBarChunkWidth)
        casetype(QStyle::PM_SplitterWidth)
        casetype(QStyle::PM_TitleBarHeight)
        casetype(QStyle::PM_MenuScrollerHeight)
        casetype(QStyle::PM_MenuHMargin)
        casetype(QStyle::PM_MenuVMargin)
        casetype(QStyle::PM_MenuPanelWidth)
        casetype(QStyle::PM_MenuTearoffHeight)
        casetype(QStyle::PM_MenuDesktopFrameWidth)
        casetype(QStyle::PM_MenuBarPanelWidth)
        casetype(QStyle::PM_MenuBarItemSpacing)
        casetype(QStyle::PM_MenuBarVMargin)
        casetype(QStyle::PM_MenuBarHMargin)
        casetype(QStyle::PM_IndicatorWidth)
        casetype(QStyle::PM_IndicatorHeight)
        casetype(QStyle::PM_ExclusiveIndicatorWidth)
        casetype(QStyle::PM_ExclusiveIndicatorHeight)
        casetype(QStyle::PM_DialogButtonsSeparator)
        casetype(QStyle::PM_DialogButtonsButtonWidth)
        casetype(QStyle::PM_DialogButtonsButtonHeight)
        casetype(QStyle::PM_MdiSubWindowFrameWidth)
        casetype(QStyle::PM_MdiSubWindowMinimizedWidth)
#if QT_DEPRECATED_SINCE(5, 13) // ### Qt 6: remove
            //casetype(PM_MDIFrameWidth)
            //casetype(PM_MDIMinimizedWidth)
#endif
        casetype(QStyle::PM_HeaderMargin)
        casetype(QStyle::PM_HeaderMarkSize)
        casetype(QStyle::PM_HeaderGripMargin)
        casetype(QStyle::PM_TabBarTabShiftHorizontal)
        casetype(QStyle::PM_TabBarTabShiftVertical)
        casetype(QStyle::PM_TabBarScrollButtonWidth)
        casetype(QStyle::PM_ToolBarFrameWidth)
        casetype(QStyle::PM_ToolBarHandleExtent)
        casetype(QStyle::PM_ToolBarItemSpacing)
        casetype(QStyle::PM_ToolBarItemMargin)
        casetype(QStyle::PM_ToolBarSeparatorExtent)
        casetype(QStyle::PM_ToolBarExtensionExtent)
        casetype(QStyle::PM_SpinBoxSliderHeight)
#if QT_DEPRECATED_SINCE(5, 15) // ### Qt 6: remove
        casetype(QStyle::PM_DefaultTopLevelMargin)
        casetype(QStyle::PM_DefaultChildMargin)
        casetype(QStyle::PM_DefaultLayoutSpacing)
#endif
        casetype(QStyle::PM_ToolBarIconSize)
        casetype(QStyle::PM_ListViewIconSize)
        casetype(QStyle::PM_IconViewIconSize)
        casetype(QStyle::PM_SmallIconSize)
        casetype(QStyle::PM_LargeIconSize)
        casetype(QStyle::PM_FocusFrameVMargin)
        casetype(QStyle::PM_FocusFrameHMargin)
        casetype(QStyle::PM_ToolTipLabelFrameWidth)
        casetype(QStyle::PM_CheckBoxLabelSpacing)
        casetype(QStyle::PM_TabBarIconSize)
        casetype(QStyle::PM_SizeGripSize)
        casetype(QStyle::PM_DockWidgetTitleMargin)
        casetype(QStyle::PM_MessageBoxIconSize)
        casetype(QStyle::PM_ButtonIconSize)
        casetype(QStyle::PM_DockWidgetTitleBarButtonMargin)
        casetype(QStyle::PM_RadioButtonLabelSpacing)
        casetype(QStyle::PM_LayoutLeftMargin)
        casetype(QStyle::PM_LayoutTopMargin)
        casetype(QStyle::PM_LayoutRightMargin)
        casetype(QStyle::PM_LayoutBottomMargin)
        casetype(QStyle::PM_LayoutHorizontalSpacing)
        casetype(QStyle::PM_LayoutVerticalSpacing)
        casetype(QStyle::PM_TabBar_ScrollButtonOverlap)
        casetype(QStyle::PM_TextCursorWidth)
        casetype(QStyle::PM_TabCloseIndicatorWidth)
        casetype(QStyle::PM_TabCloseIndicatorHeight)
        casetype(QStyle::PM_ScrollView_ScrollBarSpacing)
        casetype(QStyle::PM_ScrollView_ScrollBarOverlap)
        casetype(QStyle::PM_SubMenuOverlap)
        casetype(QStyle::PM_TreeViewIndentation)
        casetype(QStyle::PM_HeaderDefaultSectionSizeHorizontal)
        casetype(QStyle::PM_HeaderDefaultSectionSizeVertical)
        casetype(QStyle::PM_TitleBarButtonIconSize)
        casetype(QStyle::PM_TitleBarButtonSize)
        casetype(QStyle::PM_CustomBase)
    }
    return result;
}

#define drawSizeFromContents QProxyStyle::sizeFromContents(type, option, contentsSize, widget);
QSize MyStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption* option,
    const QSize& contentsSize, const QWidget* widget) const {
    QSize result = drawSizeFromContents
    switch (type)
    {
    casetype(QStyle::CT_PushButton)
    casetype(QStyle::CT_CheckBox)
    casetype(QStyle::CT_RadioButton)
    casetype(QStyle::CT_ToolButton)
    casetype(QStyle::CT_ComboBox)
    casetype(QStyle::CT_Splitter)
    casetype(QStyle::CT_ProgressBar)
    casetype(QStyle::CT_MenuItem)
    casetype(QStyle::CT_MenuBarItem)
    casetype(QStyle::CT_MenuBar)
    casetype(QStyle::CT_Menu)
    casetype(QStyle::CT_TabBarTab)
    casetype(QStyle::CT_Slider)
    casetype(QStyle::CT_ScrollBar)
    casetype(QStyle::CT_LineEdit)
    casetype(QStyle::CT_SpinBox)
    casetype(QStyle::CT_SizeGrip)
    casetype(QStyle::CT_TabWidget)
    casetype(QStyle::CT_DialogButtons)
    casetype(QStyle::CT_HeaderSection)
    casetype(QStyle::CT_GroupBox)
    casetype(QStyle::CT_MdiControls)
    casetype(QStyle::CT_ItemViewItem)
    casetype(QStyle::CT_CustomBase)
    default:
        result = drawSizeFromContents 
        break;
    }
    //qDebug() << "[SPLITTER] " << result;
    return result;
}

#define drawHitTestComplexControl QProxyStyle::hitTestComplexControl(control, option, position, widget);
QStyle::SubControl MyStyle::hitTestComplexControl(QStyle::ComplexControl control, const QStyleOptionComplex* option,
    const QPoint& position, const QWidget* widget) const {
    QStyle::SubControl subcontrl = drawHitTestComplexControl
    switch (control)
    {
    casetype(QStyle::CC_SpinBox)
    casetype(QStyle::CC_ComboBox)
    casetype(QStyle::CC_ScrollBar)
    casetype(QStyle::CC_Slider)
    casetype(QStyle::CC_ToolButton)
    casetype(QStyle::CC_TitleBar)
    casetype(QStyle::CC_Dial)
    casetype(QStyle::CC_GroupBox)
    casetype(QStyle::CC_MdiControls)
    casetype(QStyle::CC_CustomBase)
    default:
        break;
    }
    return subcontrl;
}

#define drawStandardIcon QProxyStyle::standardIcon(standardIcon, option, widget);
QIcon MyStyle::standardIcon(QStyle::StandardPixmap standardIcon,
    const QStyleOption* option, const QWidget* widget) const {
    QIcon result = drawStandardIcon
    switch (standardIcon)
    {
    casetype(QStyle::SP_TitleBarMenuButton)
    casetype(QStyle::SP_TitleBarMinButton)
    casetype(QStyle::SP_TitleBarMaxButton)
    casetype(QStyle::SP_TitleBarCloseButton)
    casetype(QStyle::SP_TitleBarNormalButton)
    casetype(QStyle::SP_TitleBarShadeButton)
    casetype(QStyle::SP_TitleBarUnshadeButton)
    casetype(QStyle::SP_TitleBarContextHelpButton)
    casetype(QStyle::SP_DockWidgetCloseButton)
    casetype(QStyle::SP_MessageBoxInformation)
    casetype(QStyle::SP_MessageBoxWarning)
    casetype(QStyle::SP_MessageBoxCritical)
    casetype(QStyle::SP_MessageBoxQuestion)
    casetype(QStyle::SP_DesktopIcon)
    casetype(QStyle::SP_TrashIcon)
    casetype(QStyle::SP_ComputerIcon)
    casetype(QStyle::SP_DriveFDIcon)
    casetype(QStyle::SP_DriveHDIcon)
    casetype(QStyle::SP_DriveCDIcon)
    casetype(QStyle::SP_DriveDVDIcon)
    casetype(QStyle::SP_DriveNetIcon)
    casetype(QStyle::SP_DirOpenIcon)
    casetype(QStyle::SP_DirClosedIcon)
    casetype(QStyle::SP_DirLinkIcon)
    casetype(QStyle::SP_DirLinkOpenIcon)
    casetype(QStyle::SP_FileIcon)
    casetype(QStyle::SP_FileLinkIcon)
    casetype(QStyle::SP_ToolBarHorizontalExtensionButton)
    casetype(QStyle::SP_ToolBarVerticalExtensionButton)
    casetype(QStyle::SP_FileDialogStart)
    casetype(QStyle::SP_FileDialogEnd)
    casetype(QStyle::SP_FileDialogToParent)
    casetype(QStyle::SP_FileDialogNewFolder)
    casetype(QStyle::SP_FileDialogDetailedView)
    casetype(QStyle::SP_FileDialogInfoView)
    casetype(QStyle::SP_FileDialogContentsView)
    casetype(QStyle::SP_FileDialogListView)
    casetype(QStyle::SP_FileDialogBack)
    casetype(QStyle::SP_DirIcon)
    casetype(QStyle::SP_DialogOkButton)
    casetype(QStyle::SP_DialogCancelButton)
    casetype(QStyle::SP_DialogHelpButton)
    casetype(QStyle::SP_DialogOpenButton)
    casetype(QStyle::SP_DialogSaveButton)
    casetype(QStyle::SP_DialogCloseButton)
    casetype(QStyle::SP_DialogApplyButton)
    casetype(QStyle::SP_DialogResetButton)
    casetype(QStyle::SP_DialogDiscardButton)
    casetype(QStyle::SP_DialogYesButton)
    casetype(QStyle::SP_DialogNoButton)
    casetype(QStyle::SP_ArrowUp)
    casetype(QStyle::SP_ArrowDown)
    casetype(QStyle::SP_ArrowLeft)
    casetype(QStyle::SP_ArrowRight)
    casetype(QStyle::SP_ArrowBack)
    casetype(QStyle::SP_ArrowForward)
    casetype(QStyle::SP_DirHomeIcon)
    casetype(QStyle::SP_CommandLink)
    casetype(QStyle::SP_VistaShield)
    casetype(QStyle::SP_BrowserReload)
    casetype(QStyle::SP_BrowserStop)
    casetype(QStyle::SP_MediaPlay)
    casetype(QStyle::SP_MediaStop)
    casetype(QStyle::SP_MediaPause)
    casetype(QStyle::SP_MediaSkipForward)
    casetype(QStyle::SP_MediaSkipBackward)
    casetype(QStyle::SP_MediaSeekForward)
    casetype(QStyle::SP_MediaSeekBackward)
    casetype(QStyle::SP_MediaVolume)
    casetype(QStyle::SP_MediaVolumeMuted)
    casetype(QStyle::SP_LineEditClearButton)
    casetype(QStyle::SP_DialogYesToAllButton)
    casetype(QStyle::SP_DialogNoToAllButton)
    casetype(QStyle::SP_DialogSaveAllButton)
    casetype(QStyle::SP_DialogAbortButton)
    casetype(QStyle::SP_DialogRetryButton)
    casetype(QStyle::SP_DialogIgnoreButton)
    casetype(QStyle::SP_RestoreDefaultsButton)
    casetype(QStyle::SP_CustomBase)
    default:
        break;
    }
    return result;
}

#define drawStyleHint QProxyStyle::styleHint(hint, option, widget, returnData);
int MyStyle::styleHint(QStyle::StyleHint hint, const QStyleOption* option,
    const QWidget* widget, QStyleHintReturn* returnData) const {
    int result = drawStyleHint
    switch (hint)
    {
    casetype(QStyle::SH_EtchDisabledText)
    casetype(QStyle::SH_DitherDisabledText)
    casetype(QStyle::SH_ScrollBar_MiddleClickAbsolutePosition)
    casetype(QStyle::SH_ScrollBar_ScrollWhenPointerLeavesControl)
    casetype(QStyle::SH_TabBar_SelectMouseType)
    casetype(QStyle::SH_TabBar_Alignment)
    casetype(QStyle::SH_Header_ArrowAlignment)
    casetype(QStyle::SH_Slider_SnapToValue)
    casetype(QStyle::SH_Slider_SloppyKeyEvents)
    casetype(QStyle::SH_ProgressDialog_CenterCancelButton)
    casetype(QStyle::SH_ProgressDialog_TextLabelAlignment)
    casetype(QStyle::SH_PrintDialog_RightAlignButtons)
    casetype(QStyle::SH_MainWindow_SpaceBelowMenuBar)
    casetype(QStyle::SH_FontDialog_SelectAssociatedText)
    casetype(QStyle::SH_Menu_AllowActiveAndDisabled)
    casetype(QStyle::SH_Menu_SpaceActivatesItem)
    casetype(QStyle::SH_Menu_SubMenuPopupDelay)
    casetype(QStyle::SH_ScrollView_FrameOnlyAroundContents)
    casetype(QStyle::SH_MenuBar_AltKeyNavigation)
    casetype(QStyle::SH_ComboBox_ListMouseTracking)
    casetype(QStyle::SH_Menu_MouseTracking)
    casetype(QStyle::SH_MenuBar_MouseTracking)
    casetype(QStyle::SH_ItemView_ChangeHighlightOnFocus)
    casetype(QStyle::SH_Widget_ShareActivation)
    casetype(QStyle::SH_Workspace_FillSpaceOnMaximize)
    casetype(QStyle::SH_ComboBox_Popup)
    casetype(QStyle::SH_TitleBar_NoBorder)
    casetype(QStyle::SH_Slider_StopMouseOverSlider)
    casetype(QStyle::SH_BlinkCursorWhenTextSelected)
    casetype(QStyle::SH_RichText_FullWidthSelection)
    casetype(QStyle::SH_Menu_Scrollable)
    casetype(QStyle::SH_GroupBox_TextLabelVerticalAlignment)
    casetype(QStyle::SH_GroupBox_TextLabelColor)
    casetype(QStyle::SH_Menu_SloppySubMenus)
    casetype(QStyle::SH_Table_GridLineColor)
    casetype(QStyle::SH_LineEdit_PasswordCharacter)
    casetype(QStyle::SH_DialogButtons_DefaultButton)
    casetype(QStyle::SH_ToolBox_SelectedPageTitleBold)
    casetype(QStyle::SH_TabBar_PreferNoArrows)
    casetype(QStyle::SH_ScrollBar_LeftClickAbsolutePosition)
    casetype(QStyle::SH_ListViewExpand_SelectMouseType)
    casetype(QStyle::SH_UnderlineShortcut)
    casetype(QStyle::SH_SpinBox_AnimateButton)
    casetype(QStyle::SH_SpinBox_KeyPressAutoRepeatRate)
    casetype(QStyle::SH_SpinBox_ClickAutoRepeatRate)
    casetype(QStyle::SH_Menu_FillScreenWithScroll)
    casetype(QStyle::SH_ToolTipLabel_Opacity)
    casetype(QStyle::SH_DrawMenuBarSeparator)
    casetype(QStyle::SH_TitleBar_ModifyNotification)
    casetype(QStyle::SH_Button_FocusPolicy)
    casetype(QStyle::SH_MessageBox_UseBorderForButtonSpacing)
    casetype(QStyle::SH_TitleBar_AutoRaise)
    casetype(QStyle::SH_ToolButton_PopupDelay)
    casetype(QStyle::SH_FocusFrame_Mask)
    casetype(QStyle::SH_RubberBand_Mask)
    casetype(QStyle::SH_WindowFrame_Mask)
    casetype(QStyle::SH_SpinControls_DisableOnBounds)
    casetype(QStyle::SH_Dial_BackgroundRole)
    casetype(QStyle::SH_ComboBox_LayoutDirection)
    casetype(QStyle::SH_ItemView_EllipsisLocation)
    casetype(QStyle::SH_ItemView_ShowDecorationSelected)
    casetype(QStyle::SH_ItemView_ActivateItemOnSingleClick)
    casetype(QStyle::SH_ScrollBar_ContextMenu)
    casetype(QStyle::SH_ScrollBar_RollBetweenButtons)
    casetype(QStyle::SH_Slider_AbsoluteSetButtons)
    casetype(QStyle::SH_Slider_PageSetButtons)
    casetype(QStyle::SH_Menu_KeyboardSearch)
    casetype(QStyle::SH_TabBar_ElideMode)
    casetype(QStyle::SH_DialogButtonLayout)
    casetype(QStyle::SH_ComboBox_PopupFrameStyle)
    casetype(QStyle::SH_MessageBox_TextInteractionFlags)
    casetype(QStyle::SH_DialogButtonBox_ButtonsHaveIcons)
    casetype(QStyle::SH_SpellCheckUnderlineStyle)
    casetype(QStyle::SH_MessageBox_CenterButtons)
    casetype(QStyle::SH_Menu_SelectionWrap)
    casetype(QStyle::SH_ItemView_MovementWithoutUpdatingSelection)
    casetype(QStyle::SH_ToolTip_Mask)
    casetype(QStyle::SH_FocusFrame_AboveWidget)
    casetype(QStyle::SH_TextControl_FocusIndicatorTextCharFormat)
    casetype(QStyle::SH_WizardStyle)
    casetype(QStyle::SH_ItemView_ArrowKeysNavigateIntoChildren)
    casetype(QStyle::SH_Menu_Mask)
    casetype(QStyle::SH_Menu_FlashTriggeredItem)
    casetype(QStyle::SH_Menu_FadeOutOnHide)
    casetype(QStyle::SH_SpinBox_ClickAutoRepeatThreshold)
    casetype(QStyle::SH_ItemView_PaintAlternatingRowColorsForEmptyArea)
    casetype(QStyle::SH_FormLayoutWrapPolicy)
    casetype(QStyle::SH_TabWidget_DefaultTabPosition)
    casetype(QStyle::SH_ToolBar_Movable)
    casetype(QStyle::SH_FormLayoutFieldGrowthPolicy)
    casetype(QStyle::SH_FormLayoutFormAlignment)
    casetype(QStyle::SH_FormLayoutLabelAlignment)
    casetype(QStyle::SH_ItemView_DrawDelegateFrame)
    casetype(QStyle::SH_TabBar_CloseButtonPosition)
    casetype(QStyle::SH_DockWidget_ButtonsHaveFrame)
    casetype(QStyle::SH_ToolButtonStyle)
    casetype(QStyle::SH_RequestSoftwareInputPanel)
    casetype(QStyle::SH_ScrollBar_Transient)
    casetype(QStyle::SH_Menu_SupportsSections)
    casetype(QStyle::SH_ToolTip_WakeUpDelay)
    casetype(QStyle::SH_ToolTip_FallAsleepDelay)
    casetype(QStyle::SH_Widget_Animate)
    casetype(QStyle::SH_Splitter_OpaqueResize)
    casetype(QStyle::SH_ComboBox_UseNativePopup)
    casetype(QStyle::SH_LineEdit_PasswordMaskDelay)
    casetype(QStyle::SH_TabBar_ChangeCurrentDelay)
    casetype(QStyle::SH_Menu_SubMenuUniDirection)
    casetype(QStyle::SH_Menu_SubMenuUniDirectionFailCount)
    casetype(QStyle::SH_Menu_SubMenuSloppySelectOtherActions)
    casetype(QStyle::SH_Menu_SubMenuSloppyCloseTimeout)
    casetype(QStyle::SH_Menu_SubMenuResetWhenReenteringParent)
    casetype(QStyle::SH_Menu_SubMenuDontStartSloppyOnLeave)
    casetype(QStyle::SH_ItemView_ScrollMode)
    casetype(QStyle::SH_TitleBar_ShowToolTipsOnButtons)
    casetype(QStyle::SH_Widget_Animation_Duration)
    casetype(QStyle::SH_ComboBox_AllowWheelScrolling)
    casetype(QStyle::SH_SpinBox_ButtonsInsideFrame)
    casetype(QStyle::SH_SpinBox_StepModifier)
    casetype(QStyle::SH_CustomBase)
    default:
        break;
    }
    return result;
}

#define drawSubControlRect QProxyStyle::subControlRect(control, option, subControl, widget);
QRect MyStyle::subControlRect(QStyle::ComplexControl control,
    const QStyleOptionComplex* option, QStyle::SubControl subControl, const QWidget* widget) const {
    QRect result = drawSubControlRect
    switch (control)
    {
    casetype(QStyle::CC_SpinBox)
    casetype(QStyle::CC_ComboBox)
    casetype(QStyle::CC_ScrollBar)
    casetype(QStyle::CC_Slider)
    casetype(QStyle::CC_ToolButton)
    casetype(QStyle::CC_TitleBar)
    casetype(QStyle::CC_Dial)
    casetype(QStyle::CC_GroupBox)
    casetype(QStyle::CC_MdiControls)
    casetype(QStyle::CC_CustomBase)
    default:
        break;
    }
    return result;
}

#define drawSubElementRect QProxyStyle::subElementRect(element, option, widget);
QRect MyStyle::subElementRect(QStyle::SubElement element,
    const QStyleOption* option, const QWidget* widget) const {
    QRect result = drawSubElementRect
    switch (element)
    {
    casetype(QStyle::SE_PushButtonContents)
    casetype(QStyle::SE_PushButtonFocusRect)
    casetype(QStyle::SE_CheckBoxIndicator)
    casetype(QStyle::SE_CheckBoxContents)
    casetype(QStyle::SE_CheckBoxFocusRect)
    casetype(QStyle::SE_CheckBoxClickRect)
    casetype(QStyle::SE_RadioButtonIndicator)
    casetype(QStyle::SE_RadioButtonContents)
    casetype(QStyle::SE_RadioButtonFocusRect)
    casetype(QStyle::SE_RadioButtonClickRect)
    casetype(QStyle::SE_ComboBoxFocusRect)
    casetype(QStyle::SE_SliderFocusRect)
    casetype(QStyle::SE_ProgressBarGroove)
    casetype(QStyle::SE_ProgressBarContents)
    casetype(QStyle::SE_ProgressBarLabel)
    casetype(QStyle::SE_ToolBoxTabContents)
    casetype(QStyle::SE_HeaderLabel)
    casetype(QStyle::SE_HeaderArrow)
    casetype(QStyle::SE_TabWidgetTabBar)
    casetype(QStyle::SE_TabWidgetTabPane)
    casetype(QStyle::SE_TabWidgetTabContents)
    casetype(QStyle::SE_TabWidgetLeftCorner)
    casetype(QStyle::SE_TabWidgetRightCorner)
    casetype(QStyle::SE_ItemViewItemCheckIndicator)
    casetype(QStyle::SE_TabBarTearIndicator) // the same as SE_TabBarTearIndicatorLeft
    casetype(QStyle::SE_TreeViewDisclosureItem)
    casetype(QStyle::SE_LineEditContents)
    casetype(QStyle::SE_FrameContents)
    casetype(QStyle::SE_DockWidgetCloseButton)
    casetype(QStyle::SE_DockWidgetFloatButton)
    casetype(QStyle::SE_DockWidgetTitleBarText)
    casetype(QStyle::SE_DockWidgetIcon)
    casetype(QStyle::SE_CheckBoxLayoutItem)
    casetype(QStyle::SE_ComboBoxLayoutItem)
    casetype(QStyle::SE_DateTimeEditLayoutItem)
    casetype(QStyle::SE_DialogButtonBoxLayoutItem)
    casetype(QStyle::SE_LabelLayoutItem)
    casetype(QStyle::SE_ProgressBarLayoutItem)
    casetype(QStyle::SE_PushButtonLayoutItem)
    casetype(QStyle::SE_RadioButtonLayoutItem)
    casetype(QStyle::SE_SliderLayoutItem)
    casetype(QStyle::SE_SpinBoxLayoutItem)
    casetype(QStyle::SE_ToolButtonLayoutItem)
    casetype(QStyle::SE_FrameLayoutItem)
    casetype(QStyle::SE_GroupBoxLayoutItem)
    casetype(QStyle::SE_TabWidgetLayoutItem)
    casetype(QStyle::SE_ItemViewItemDecoration)
    casetype(QStyle::SE_ItemViewItemText)
    casetype(QStyle::SE_ItemViewItemFocusRect)
    casetype(QStyle::SE_TabBarTabLeftButton)
    casetype(QStyle::SE_TabBarTabRightButton)
    casetype(QStyle::SE_TabBarTabText)
    casetype(QStyle::SE_ShapedFrameContents)
    casetype(QStyle::SE_ToolBarHandle)
    casetype(QStyle::SE_TabBarScrollLeftButton)
    casetype(QStyle::SE_TabBarScrollRightButton)
    casetype(QStyle::SE_TabBarTearIndicatorRight)
    casetype(QStyle::SE_PushButtonBevel)
    casetype(QStyle::SE_CustomBase)
    default:
        break;
    }
    return result;
}
