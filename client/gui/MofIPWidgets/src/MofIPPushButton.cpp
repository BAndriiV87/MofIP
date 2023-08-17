#include "MofIPWidgets/MofIPPushButton.hpp"
#include "MofIPWidgets/MofipWidgetsCommon.hpp"

#define BUTTON_SIZE mSizeButton
#define BUTTON_WIDTH BUTTON_SIZE.width()
#define BUTTON_HEIGHT BUTTON_SIZE.height()
#define BUTTON_RECT(topleft) QRectF(topleft, topleft, BUTTON_WIDTH - mBoundWidth, BUTTON_HEIGHT - mBoundWidth)

namespace MofIPWidgets {

    const QFont MofIPPushButton::mFont = QFont(QString("Comic Sans MS"), 10);
    const qreal MofIPPushButton::mRadius = 10;
    const qreal MofIPPushButton::mBoundWidth = 4;
    const qreal MofIPPushButton::mPenWidth = 2;
    const QColor MofIPPushButton::mColorButton = { Qt::white };


    MofIPPushButton::MofIPPushButton(QWidget* parent) 
        : QPushButton(parent)
    {
        init();
    }

    MofIPPushButton::MofIPPushButton(const QString& text, QWidget* parent)
        : QPushButton(text, parent)
    {
        init();
    }

    void MofIPPushButton::init() {
        mSizeButton = QSize(140, 35);
    }

    void MofIPPushButton::paintEvent(QPaintEvent* e) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Draw shadow rectangle
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::gray);
        qreal bound = mBoundWidth - (mIsPressed ? mBoundWidth * 0.6 : 0);
        painter.drawPath(rectRoundPath(BUTTON_RECT(bound), mRadius));

        // Draw main rect of button
        painter.setPen(QPen(Qt::black, mPenWidth));
        painter.setBrush(mColorButton);
        painter.drawPath(rectRoundPath(BUTTON_RECT(0), mRadius));
        if (this->testAttribute(Qt::WA_Hover)) {
            painter.fillPath(rectRoundPath(BUTTON_RECT(0), mRadius), QColor(0, 0, 0, 30));
        }
        // Draw text inside button
        painter.setPen(QColor(Qt::black));
        painter.setFont(mFont);
        painter.drawText(BUTTON_RECT(0), Qt::AlignCenter, QPushButton::text());
    }

    QSize MofIPPushButton::sizeHint() const {
        return BUTTON_SIZE;
    }

    void MofIPPushButton::mousePressEvent(QMouseEvent* event) {
        mIsPressed = true;
        this->update();
        QPushButton::mousePressEvent(event);
    }

    void MofIPPushButton::mouseReleaseEvent(QMouseEvent* event) {
        mIsPressed = false;
        this->update();
        QPushButton::mouseReleaseEvent(event);
    }

    void MofIPPushButton::resizeEvent(QResizeEvent* event) {
        mSizeButton.setWidth(event->size().width());
        mSizeButton.setHeight(event->size().height());
    }

    void MofIPPushButton::leaveEvent(QEvent* event) {
        this->setAttribute(Qt::WA_Hover, false);
        this->update();
        QPushButton::leaveEvent(event);
    }

    void MofIPPushButton::enterEvent(QEvent* event) {
        this->setAttribute(Qt::WA_Hover, true);
        this->update();
        QPushButton::enterEvent(event);
    }

}
