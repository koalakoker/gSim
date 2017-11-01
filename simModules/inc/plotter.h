#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QElapsedTimer>
#include <QPainter>
#include <QDebug>

class Plotter : public QObject {
    Q_OBJECT
public:
    Plotter(QSize size, QRectF range, QVector<double> data)
        : _size(size), _range(range), _data(data) { }

signals:
    void done(QImage);
    void cleanup();

public slots:
    void plot() {
        QElapsedTimer t;
        t.start();
        QImage img(_size, QImage::Format_ARGB32_Premultiplied);
        img.fill(Qt::white);
        QPainter p(&img);
        QPen pen(Qt::darkBlue);
        pen.setWidth(1);
        p.setPen(pen);
//        for (int i = 0; i < _data.size(); i += 2) {
//            p.drawPoint(map(_data[i], _data[i + 1]));
//        }
        for (int i = 0; i < _data.size() - 2; i += 2) {
            p.drawLine(map(_data[i], _data[i + 1]),map(_data[i+2], _data[i + 3]));
        }
        qDebug() << "plotted in" << t.elapsed() << "msec";
        emit done(img);
        emit cleanup();
    }

private:
    inline QPointF map(double x, double y) {
        return QPointF(_size.width() * ((x * 1) / (_range.width() - _range.x())),
                       (_size.height() * ((1-y) / (_range.height() - _range.y()))));
    }

    QSize _size;
    QRectF _range;
    QVector<double> _data;
};

#endif // PLOTTER_H
