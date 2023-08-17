#include "MofIPWidgets/MofIPPushButton.hpp"
#include "MofIPWidgets/MofipWidgetsCommon.hpp"

namespace MofIPWidgets {

    QSize MofIPPushButton::sizeButton() const {
        return QSize(mRectButton.width() + mBoundWidth, mRectButton.height() + mBoundWidth);
    }

    MofIPPushButton::MofIPPushButton(const QString& text)
        : mTextButton(text)
    {
    }

    void MofIPPushButton::paintEvent(QPaintEvent* e) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        // Draw shadow rectangle
        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::gray);
        painter.drawPath(rectRoundPath(QRectF(mBoundWidth, mBoundWidth, mRectButton.width(), mRectButton.height()), mRadius));

        // Draw main rect of button
        painter.setPen(QPen(Qt::black, mPenWidth));
        painter.setBrush(mColorButton);
        painter.drawPath(rectRoundPath(mRectButton, mRadius));
        if (this->testAttribute(Qt::WA_Hover)) {
            painter.fillPath(rectRoundPath(mRectButton, mRadius), QColor(0, 0, 0, 30));
        }

        // Draw text inside button
        painter.setPen(QColor(Qt::black));
        painter.setFont(QFont(QString("Comic Sans MS"), 12));
        painter.drawText(mRectButton, Qt::AlignCenter, mTextButton);
    }

    QSize MofIPPushButton::sizeHint() const {
        return sizeButton();
    }

    void MofIPPushButton::mousePressEvent(QMouseEvent* event) {
        mBoundWidth -= 2;
        mColorButton = QColor(210, 210, 210);
        this->update();
        QPushButton::mousePressEvent(event);
    }

    void MofIPPushButton::mouseReleaseEvent(QMouseEvent* event) {
        mBoundWidth += 2;
        mColorButton = QColor(Qt::white);
        this->update();
        QPushButton::mouseReleaseEvent(event);
    }

    void MofIPPushButton::resizeEvent(QResizeEvent* event) {
        mRectButton.setWidth(event->size().width() - mBoundWidth);
        mRectButton.setHeight(event->size().height() - mBoundWidth);
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
