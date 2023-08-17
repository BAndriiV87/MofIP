#ifndef MOFIP_PUSHBUTTON_HPP
#define MOFIP_PUSHBUTTON_HPP

#include <QtWidgets>

namespace MofIPWidgets {

    class MofIPPushButton : public QPushButton
    {
    public:
        MofIPPushButton(const QString &text);
    protected:
        virtual void paintEvent(QPaintEvent* e) override;
        virtual QSize	sizeHint() const override;
        virtual void	mousePressEvent(QMouseEvent* event) override;
        virtual void	mouseReleaseEvent(QMouseEvent* event) override;
        virtual void	resizeEvent(QResizeEvent* event) override;
        virtual void	leaveEvent(QEvent* event) override;
        virtual void	enterEvent(QEvent* event) override;
    private:
        QSize sizeButton() const;
    private:
        QString mTextButton;
        QRectF mRectButton = {0, 0, 200, 50 };
        qreal mBoundWidth = 4;
        const qreal mPenWidth = 2.5;
        const qreal mRadius = 10;
        QColor mColorButton = { Qt::white };
    };
    
}

#endif //MOFIP_PUSHBUTTON_HPP
