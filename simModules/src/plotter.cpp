#include "plotter.h"

QImage Plotter::plot()
{
    QElapsedTimer t;
    t.start();
    QImage img(_size, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    QPainter p(&img);
    QPen pen(Qt::darkBlue);
    pen.setWidth(1);
    p.setPen(pen);
    switch (m_style)
    {
    case POINT_STYLE:
        {
            for (int i = 0; i < _data.size(); i += 2)
            {
                p.drawPoint(map(_data[i], _data[i + 1]));
            }
        }
        break;
    case LINE_STYLE:
        {
            for (int i = 0; i < _data.size() - 2; i += 2) {
                p.drawLine(map(_data[i], _data[i + 1]), map(_data[i+2], _data[i + 3]));
            }
        }
        break;
    default:
        break;
    }

    //qDebug() << "plotted in" << t.elapsed() << "msec";
    return img;
}

inline QPointF Plotter::map(double x, double y)
{
    return QPointF(                (_size.width () * ((x - _range.x()) / _range.width ())),
                   (_size.height()-(_size.height() * ((y - _range.y()) / _range.height()))));
}
