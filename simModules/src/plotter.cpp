#include "plotter.h"

QImage Plotter::plot()
{
    const Qt::GlobalColor plotColor[] = {Qt::black, Qt::blue, Qt::green, Qt::red};

    QElapsedTimer t;
    t.start();
    QImage img(_size, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    QPainter p(&img);
    QPen pen(Qt::darkBlue);
    pen.setWidth(1);
    p.setPen(pen);

    int trackNum = _data[0].size();
    for (int track = 1; track < trackNum; track++) // Skip index 0 that is the time (x)
    {
        pen.setColor(plotColor[track-1]);
        p.setPen(pen);

        switch (m_style)
        {
        case POINT_STYLE:
            {
                for (int i = 0; i < _data.size(); i++)
                {
                    p.drawPoint(map(_data[i][0], _data[i][track]));
                }
            }
            break;
        case LINE_STYLE:
            {
                for (int i = 0; i < _data.size() - 1; i++) {
                    p.drawLine(map(_data[i][0], _data[i][track]), map(_data[i+1][0], _data[i+1][track]));
                }
            }
            break;
        default:
            break;
        }
    }
    //p.setPen(QPen(Qt::red));
    //p.drawText(10,20,QString("Rect: Top %1, Bottom %2").arg(_range.top()).arg(_range.bottom()));

    //qDebug() << "plotted in" << t.elapsed() << "msec";
    return img;
}

inline QPointF Plotter::map(double x, double y)
{
    return QPointF(                (_size.width () * ((x - _range.x()) / _range.width ())),
                   (_size.height()-(_size.height() * ((y - _range.y()) / _range.height()))));
}
