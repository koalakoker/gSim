#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QElapsedTimer>
#include <QPainter>
#include <QDebug>

class Plotter : public QObject {
    Q_OBJECT

public:
    typedef enum {
        POINT_STYLE,
        LINE_STYLE
    } style_t;

    Plotter(QSize size, QRectF range, QVector<double> data, style_t style = LINE_STYLE)
        : _size(size), _range(range), _data(data), m_style(style) { }

    void setRangeX_Min(qreal val) {_range.setLeft  (val);}
    void setRangeX_Max(qreal val) {_range.setRight (val);}
    void setRangeY_Min(qreal val) {_range.setBottom(val);}
    void setRangeY_Max(qreal val) {_range.setTop   (val);}

    void scrollX(qreal val) {_range.setLeft(_range.left() + val); _range.setRight(_range.right() + val); }

signals:
    void done(QImage);
    void cleanup();

public slots:
    QImage plot();

private:
    inline QPointF map(double x, double y);

    QSize _size;
    QRectF _range;
    QVector<double> _data;

    style_t m_style;
};

#endif // PLOTTER_H
