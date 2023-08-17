#ifndef MOFIP_PUSHBUTTON_HPP
#define MOFIP_PUSHBUTTON_HPP

#include <QtWidgets>

namespace MofIPWidgets {

    class MofIPPushButton : public QPushButton
    {
    public:
        MofIPPushButton(QWidget* parent = nullptr);
        MofIPPushButton(const QString& text, QWidget* parent = nullptr);
    protected:
        virtual void    paintEvent          (QPaintEvent* e) override;
        virtual void	mousePressEvent     (QMouseEvent* event) override;
        virtual void	mouseReleaseEvent   (QMouseEvent* event) override;
        virtual void	resizeEvent         (QResizeEvent* event) override;
        virtual void	leaveEvent          (QEvent* event) override;
        virtual void	enterEvent          (QEvent* event) override;
    public:
        virtual QSize	sizeHint() const override;
    private:
        void init();
    private:
        QSize mSizeButton;
        bool mIsPressed = false;
    private:
        static const QFont mFont;
        static const qreal mRadius;
        static const qreal mBoundWidth;
        static const qreal mPenWidth;
        static const QColor mColorButton;
    };
    
}

#endif //MOFIP_PUSHBUTTON_HPP
