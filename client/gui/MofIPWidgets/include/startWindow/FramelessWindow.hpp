#ifndef FRAMELESS_WINDOW_HPP
#define FRAMELESS_WINDOW_HPP

#include <QtWidgets>

namespace mofipgui {

	class FramelessWindow : public QFrame {
        Q_OBJECT
    private:
        typedef char region_t;
        typedef char action_t;
        enum WIDGET_ACTION : action_t {
            NOT_ACTION,
            MOVE,
            RESIZE
        };
        enum WIDGET_REGION : region_t {
            INSIDE = 0x00,
            LEFT = 0x01,
            RIGHT = 0x02,
            BOTTOM = 0x04,
            TOP = 0x0008,
            LEFT_TOP = LEFT | TOP,
            LEFT_BOTTOM = LEFT | BOTTOM,
            RIGHT_TOP = RIGHT | TOP,
            RIGHT_BOTTOM = RIGHT | BOTTOM
        };
        region_t getWidgetRegion(QMouseEvent* event);
        void updateCursor();
        void changeWIdgetSize(QMouseEvent* event);
        void moveWidgetPos(QMouseEvent* event);
        int minWidth();
        int minHeight();

        bool modifyLeft(QRect& rect, QMouseEvent* event);
        bool modifyRight(QRect& rect, QMouseEvent* event);
        bool modifyTop(QRect& rect, QMouseEvent* event);
        bool modifyBottom(QRect& rect, QMouseEvent* event);
    public:
        explicit FramelessWindow(QWidget* wgt = nullptr);
    protected:
        void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
        void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;
        void changeEvent(QEvent* event) Q_DECL_OVERRIDE;
        void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    public slots:
        void collapseSlot();
        void maxWindowSlot();
        void minWindowSlot();
    private:
        QPoint mDeltaWidgetMousePos;
        region_t mRegion;
        action_t mAction;
        QPushButton* mCloseButton;
        QPushButton* mCollapseButton;
        QPushButton* mMaxButton;
        QPushButton* mMinButton;
	};

}

#endif FRAMELESS_WINDOW_HPP
