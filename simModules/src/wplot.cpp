#include "wplot.h"
#include <QGestureEvent>

WPlot::WPlot(QWidget * parent) : QWidget(parent)
{
    m_drag = false;
    grabGesture(Qt::PinchGesture);

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
    if (event->button() == dragButton)
    {
        m_drag = true;
        m_lastPoint = event->pos();
    }
}

void WPlot::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == dragButton)
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
        //qDebug() << "Angle:" << angleDelta;
        m_plotter->zoomX((qreal)angleDelta.y()/120);
        m_plotter->zoomY((qreal)angleDelta.x()/120);
        updatePlot();
    }
    if (pixelDelta != QPoint(0,0))
    {
        qDebug() << "Pixel:" << pixelDelta;
    }
}

bool WPlot::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        QGestureEvent* gest = static_cast<QGestureEvent*>(event);
        if (QGesture *pinch = gest->gesture(Qt::PinchGesture))
        {
            QPinchGesture* pinchGest = static_cast<QPinchGesture *>(pinch);
            qreal factor = pinchGest->scaleFactor();
            m_plotter->zoomX((factor-1)*5);
            m_plotter->zoomY((factor-1)*5);
            updatePlot();
        }
    }
    return QWidget::event(event);
}

