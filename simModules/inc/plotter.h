#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QElapsedTimer>
#include <QPainter>
#include <QDebug>

#include "sdata.h"

class Plotter : public QObject {
    Q_OBJECT

public:
    typedef enum {
        POINT_STYLE,
        LINE_STYLE
    } style_t;

    Plotter(QSize size, QRectF range, QVector<SData> data, style_t style = LINE_STYLE)
        : _size(size), _range(range), _data(data), m_style(style) { }

    void setRangeX_Min(qreal val) {_range.setLeft  (val);}
    void setRangeX_Max(qreal val) {_range.setRight (val);}
    void setRangeY_Min(qreal val) {_range.setBottom(val);}
    void setRangeY_Max(qreal val) {_range.setTop   (val);}

    void scrollX(qreal val) {_range.setLeft(_range.left() + val); _range.setRight (_range.right()  + val);}
    void scrollY(qreal val) {_range.setTop (_range.top()  + val); _range.setBottom(_range.bottom() + val);}

    void scrollXpixel(int pix) {scrollX((_range.width()  * (qreal)(pix))/(qreal)(_size.width ()));}
    void scrollYpixel(int pix) {scrollY((_range.height() * (qreal)(pix))/(qreal)(_size.height()));}

    void zoomX(qreal val) {
        qreal delta = _range.width() * val * 0.05;
        _range.setLeft(_range.left() + delta);
        _range.setRight(_range.right() - delta);
    }

    void zoomY(qreal val) {
        qreal delta = _range.height() * val * 0.05;
        _range.setTop   (_range.top()    + delta);
        _range.setBottom(_range.bottom() - delta);
    }

    void setSize(QSize size) {_size = size;}

    // Cursors
    void addCursor(qreal pos);
    void setCursorPos(int index, qreal pos);
    void cursorScrollPixel(int index, int pix);
    bool onCursor(QPoint point, bool select = false);
    void dragCursor(int index);
    void releaseCursor();
    int getCursorDragged();

signals:
    void done(QImage);
    void cleanup();

public slots:
    QImage plot();

private:
    inline QPointF map(double x, double y);

    QSize _size;
    QRectF _range;
    QVector<SData> _data;

    style_t m_style;

    // Cursors
    QVector<qreal> m_cursorPos;
    QVector<QRect> m_cursorRect;
    int m_cursorDrag; // 0 none, index + 1 (zero based) if cursor index is dragged
    const int m_cursorMargin = 5;
};

#endif // PLOTTER_H
