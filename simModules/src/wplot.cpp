#include "wplot.h"

WPlot::WPlot(QWidget * parent) : QWidget(parent)
{
    m_drag = false;

    // prepping data
    QVector<double> data;

    QFile file("scope_teta.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream( &file );
        QString line;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            QStringList fields = line.split(" ");

            QString x = fields.at(0); // t value
            double x_val = x.toDouble();

            QString y = fields.at(1); // y value
            double y_val = y.toDouble();

            data.append(x_val);
            data.append(y_val / 6.28);
        }
    }
    file.close();

    // create plotter
    m_plotter = new Plotter(size(), QRectF(0, 0, 1, 1), data);

    updatePlot();
}

void WPlot::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(QPoint(0, 0), plot);
}

void WPlot::updatePlot(void) {
    plot = m_plotter->plot();
    repaint();
}

void WPlot::mousePressEvent(QMouseEvent* event)
{
//    static qreal xMax = 1;
//    if (event->button() == Qt::RightButton)
//    {
//        xMax = xMax / 2;
//    }
//    if (event->button() == Qt::LeftButton)
//    {
//        xMax = xMax * 2;
//    }
//    m_plotter->setRangeX_Max(xMax);
//    updatePlot();
    if (event->button() == Qt::RightButton)
    {
        m_drag = true;
        m_lastPoint = event->pos();
    }
}

void WPlot::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        m_drag = false;
    }
}

void WPlot::mouseMoveEvent(QMouseEvent* event)
{
    if (m_drag)
    {
        QPoint delta = m_lastPoint - event->pos();
        m_lastPoint = event->pos();
        m_plotter->scrollXpixel( delta.x());
        m_plotter->scrollYpixel(-delta.y());
        updatePlot();
    }
}

void WPlot::wheelEvent(QWheelEvent* event)
{
    QPoint pixelDelta = event->pixelDelta();
    QPoint angleDelta = event->angleDelta();
    if (angleDelta != QPoint(0,0))
    {
        qDebug() << "Angle:" << angleDelta;
    }
    if (pixelDelta != QPoint(0,0))
    {
        qDebug() << "Pixel:" << pixelDelta;
    }
    m_plotter->scrollX((qreal)pixelDelta.x()/10);
    updatePlot();
}
