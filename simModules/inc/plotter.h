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
        : m_size(size), m_range(range), m_data(data), m_style(style), m_cursorDrag(0) { }

    void setRangeX_Min(qreal val) {m_range.setLeft  (val);}
    void setRangeX_Max(qreal val) {m_range.setRight (val);}
    void setRangeY_Min(qreal val) {m_range.setBottom(val);}
    void setRangeY_Max(qreal val) {m_range.setTop   (val);}

    void scrollX(qreal val) {m_range.setLeft(m_range.left() + val); m_range.setRight (m_range.right()  + val);}
    void scrollY(qreal val) {m_range.setTop (m_range.top()  + val); m_range.setBottom(m_range.bottom() + val);}

    void scrollXpixel(int pix) {scrollX((m_range.width()  * (qreal)(pix))/(qreal)(m_size.width ()));}
    void scrollYpixel(int pix) {scrollY((m_range.height() * (qreal)(pix))/(qreal)(m_size.height()));}

    void zoomX(qreal val) {
        qreal delta = m_range.width() * val * 0.05;
        m_range.setLeft(m_range.left() + delta);
        m_range.setRight(m_range.right() - delta);
    }

    void zoomY(qreal val) {
        qreal delta = m_range.height() * val * 0.05;
        m_range.setTop   (m_range.top()    + delta);
        m_range.setBottom(m_range.bottom() - delta);
    }

    void setSize(QSize size) {m_size = size;}

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
    QPointF map(double x, double y);
    double invMapX(double x);
    double mapY(double y);

    QSize m_size;
    QRectF m_range;
    QVector<SData> m_data;

    style_t m_style;

    // Cursors
    QVector<qreal> m_cursorPos;
    QVector<QRect> m_cursorRect;
    int m_cursorDrag; // 0 none, index + 1 (zero based) if cursor index is dragged
    const int m_cursorMargin = 5;
};

#endif // PLOTTER_H
