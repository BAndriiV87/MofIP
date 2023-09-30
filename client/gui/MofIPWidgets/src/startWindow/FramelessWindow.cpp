#include "startWindow/FramelessWindow.hpp"
#include "startWindow/ToolButton.hpp"
#include "startWindow/CommonDefinitions.hpp"

template<typename QEnum>
static QString QtEnumToString(const QEnum value)
{
    return QString::fromStdString(std::string(QMetaEnum::fromType<QEnum>().valueToKey(value)));
}

namespace mofipgui {

    constexpr int toolbtnshift = 1;

    FramelessWindow::FramelessWindow(QWidget* wgt)
        : QFrame(wgt),
        mDeltaWidgetMousePos(QPoint(-1, -1)),
        mRegion(WIDGET_REGION::INSIDE)
    {
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
        setMouseTracking(true);

        mCloseButton = new ToolButton<CloseButtonPainter>(this);
        mCloseButton->move(width() - mCloseButton->width() - toolbtnshift, toolbtnshift);
        mMaxButton = new ToolButton<MaxButtonPainter>(this);
        mMaxButton->move(width() - mMaxButton->width() * 2 - toolbtnshift, toolbtnshift);
        mMinButton = new ToolButton<MinButtonPainter>(this);
        mMinButton->move(width() - mMinButton->width() * 2 - toolbtnshift, toolbtnshift);
        mMinButton->setHidden(true);
        mCollapseButton = new ToolButton<CollapseButtonPainter>(this);
        mCollapseButton->move(width() - mCollapseButton->width() * 3 - toolbtnshift, toolbtnshift);

        connect(mCloseButton, &ToolButton<CloseButtonPainter>::clicked, this, &FramelessWindow::close);
        connect(mCollapseButton, &ToolButton<CollapseButtonPainter>::clicked, this, &FramelessWindow::collapseSlot);
        connect(mMaxButton, &ToolButton<MaxButtonPainter>::clicked, this, &FramelessWindow::maxWindowSlot);
        connect(mMinButton, &ToolButton<MinButtonPainter>::clicked, this, &FramelessWindow::minWindowSlot);
    }
    
    void FramelessWindow::mousePressEvent(QMouseEvent* event) {
        if (this->isMaximized()) {
            mAction = WIDGET_ACTION::NOT_ACTION;
            mDeltaWidgetMousePos = QPoint(-1, -1);
        }
        else {
            if (event->buttons() == Qt::LeftButton)
                mAction = (mRegion == WIDGET_REGION::INSIDE)
                        ? WIDGET_ACTION::MOVE
                        : WIDGET_ACTION::RESIZE;
            mDeltaWidgetMousePos = pos() - event->globalPos();
        }
        QWidget::mousePressEvent(event);
    }

    void FramelessWindow::mouseReleaseEvent(QMouseEvent* event) {
        mAction = WIDGET_ACTION::NOT_ACTION;
        mDeltaWidgetMousePos = QPoint(-1, -1);
        QWidget::mouseReleaseEvent(event);
    }

    void FramelessWindow::updateCursor() {
        Qt::CursorShape cursorShape = Qt::ArrowCursor;
        switch (mRegion)
        {
        case FramelessWindow::LEFT:
        case FramelessWindow::RIGHT:
            cursorShape = Qt::SizeHorCursor;
            break;
        case FramelessWindow::BOTTOM:
        case FramelessWindow::TOP:
            cursorShape = Qt::SizeVerCursor;
            break;
        case FramelessWindow::LEFT_TOP:
        case FramelessWindow::RIGHT_BOTTOM:
            cursorShape = Qt::SizeFDiagCursor;
            break;
        case FramelessWindow::LEFT_BOTTOM:
        case FramelessWindow::RIGHT_TOP:
            cursorShape = Qt::SizeBDiagCursor;
            break;
        }
        setCursor(cursorShape);
    }

    int FramelessWindow::minWidth() {
        return minimumWidth() >= layout()->minimumSize().width() ? minimumWidth() : layout()->minimumSize().width();
    }
    int FramelessWindow::minHeight() {
        return minimumHeight() >= layout()->minimumSize().height() ? minimumHeight() : layout()->minimumSize().height();
    }

    bool FramelessWindow::modifyLeft(QRect& rect, QMouseEvent* event) {
        if (width() > minWidth() || event->globalPos().x() < x()) {
            int deltaX = event->globalPos().x() - x();
            if ((width() - deltaX) > minWidth()) {
                rect.setX(x() + deltaX);
                rect.setWidth(width() - deltaX);
                return true;
            }
        }
        return false;
    }

    bool FramelessWindow::modifyRight(QRect& rect, QMouseEvent* event) {
        if (width() > minWidth() || event->globalPos().x() > (x() + width())) {
            int deltaX = event->globalPos().x() - x() - width();
            rect.setWidth(width() + deltaX);
            return true;
        }
        return false;
    }

    bool FramelessWindow::modifyTop(QRect& rect, QMouseEvent* event) {
        if (height() > minHeight() || event->globalPos().y() < (y() + height())) {
            int deltaY = event->globalPos().y() - y();
            if ((height() - deltaY) > minHeight()) {
                rect.setY(y() + deltaY);
                rect.setHeight(height() - deltaY);
                return true;
            }
        }
        return false;
    }

    bool FramelessWindow::modifyBottom(QRect& rect, QMouseEvent* event) {
        if (height() > minHeight() || event->globalPos().y() > (y() + height())) {
            int deltaY = event->globalPos().y() - y() - height();
            rect.setHeight(height() + deltaY);
            return true;
        }
        return false;
    }

    void FramelessWindow::changeWIdgetSize(QMouseEvent* event) {
        if (mRegion == FramelessWindow::INSIDE)
            return;
        QRect rec(x(), y(), width(), height());
        bool update = false;
        switch (mRegion)
        {
        case FramelessWindow::LEFT: 
            update |= modifyLeft(rec, event);
            break;
        case FramelessWindow::RIGHT:
            update |= modifyRight(rec, event);
            break;
        case FramelessWindow::BOTTOM:
            update |= modifyBottom(rec, event);
            break;
        case FramelessWindow::TOP:
            update |= modifyTop(rec, event);
            break;
        case FramelessWindow::LEFT_TOP:
            update |= modifyLeft(rec, event);
            update |= modifyTop(rec, event);
            break;
        case FramelessWindow::RIGHT_BOTTOM:
            update |= modifyRight(rec, event);
            update |= modifyBottom(rec, event);
            break;
        case FramelessWindow::LEFT_BOTTOM:
            update |= modifyLeft(rec, event);
            update |= modifyBottom(rec, event);
            break;
        case FramelessWindow::RIGHT_TOP:
            update |= modifyRight(rec, event);
            update |= modifyTop(rec, event);
            break;
        }
        if (update) {
            setGeometry(rec);
        }
    }

    void FramelessWindow::moveWidgetPos(QMouseEvent* event) {
        if (mRegion == FramelessWindow::INSIDE)
            move(event->globalPos() + mDeltaWidgetMousePos);
    }

    FramelessWindow::region_t FramelessWindow::getWidgetRegion(QMouseEvent* event) {
        region_t region = INSIDE;
        if (event->pos().x() <= CLIP_BORDER)
            region |= WIDGET_REGION::LEFT;
        else if (width() - event->pos().x() <= CLIP_BORDER)
            region |= WIDGET_REGION::RIGHT;
        if (event->pos().y() <= CLIP_BORDER)
            region |= WIDGET_REGION::TOP;
        else if (height() - event->pos().y() <= CLIP_BORDER)
            region |= WIDGET_REGION::BOTTOM;
        return region;
    }

    void FramelessWindow::mouseMoveEvent(QMouseEvent* event) {
        if (mAction == WIDGET_ACTION::NOT_ACTION && !this->isMaximized()) {
            mRegion = getWidgetRegion(event);
            updateCursor();
        }

        if (mAction == WIDGET_ACTION::RESIZE)
            changeWIdgetSize(event);

        if (mAction == WIDGET_ACTION::MOVE)
            moveWidgetPos(event);

        QWidget::mouseMoveEvent(event);
    }

    void FramelessWindow::resizeEvent(QResizeEvent* event) {
        mCloseButton->move(event->size().width() - mCloseButton->width() - toolbtnshift, toolbtnshift);
        mMaxButton->move(event->size().width() - mMaxButton->width() * 2 - toolbtnshift, toolbtnshift);
        mMinButton->move(event->size().width() - mMinButton->width() * 2 - toolbtnshift, toolbtnshift);
        mCollapseButton->move(event->size().width() - mCollapseButton->width() * 3 - toolbtnshift, toolbtnshift);
        QWidget::resizeEvent(event);
    }

    void FramelessWindow::collapseSlot() {
        this->showMinimized();
    }
    void FramelessWindow::maxWindowSlot() {
        mMaxButton->setHidden(true);
        mMinButton->setHidden(false);
        this->setWindowState(Qt::WindowMaximized);
    }
    void FramelessWindow::minWindowSlot() {
        mMinButton->setHidden(true);
        mMaxButton->setHidden(false);
        this->setWindowState(Qt::WindowNoState);
    }

    void FramelessWindow::changeEvent(QEvent* event) {
        if (event->type() == QEvent::WindowStateChange)
            if (!isVisible())
                this->showNormal();
        QWidget::changeEvent(event);
    }

    void FramelessWindow::paintEvent(QPaintEvent* event) {
        QPainter painter(this);
        painter.setPen(QPen(QColor(70, 70, 70, 255), 2));
        painter.drawRect(rect());
    }

}
