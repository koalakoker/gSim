#include "wplot.h"
#include <QGestureEvent>
#include <QApplication>

WPlot::WPlot(QString fileName, QWidget * parent) : QWidget(parent)
{
    m_drag = false;
    grabGesture(Qt::PinchGesture);
    setMouseTracking(true);

    QVector<SData> data;
    double y_max = 0, y_min = 0;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream( &file );
        QString line;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            QStringList fields = line.split(" ");
            SData sample;
            for (int i = 0; i < fields.size(); i++)
            {
                double val = fields.at(i).toDouble();
                sample.append(val);
                if (i != 0)
                {
                    if (val > y_max)
                    {
                        y_max = val;
                    }

                    if (val < y_min)
                    {
                        y_min = val;
                    }
                }
            }
            data.append(sample);
        }
    }
    file.close();

    qreal x_min = 0, x_max = 0;
    if (data.size() != 0)
    {
        x_min = data[0][0];
        x_max = data[data.size()-1][0];
    }

    m_plotter = new Plotter(
                size(),
                QRectF(x_min, y_min, x_max - x_min, y_max - y_min),
                data,
                Plotter::LINE_STYLE);
    //m_plotter->addCursor(x_min + (x_max - x_min)/2);
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
        int selected = 0;
        m_lastPoint = event->pos();
        if (m_plotter->onCursor(m_lastPoint, selected, true))
        {

        }
        else
        {
            m_movingUndo = true;
            m_drag = true;
        }

    }
    if (event->button() == addCursorButton)
    {
        int selected = 0;
        if (!(m_plotter->onCursor(event->pos(), selected, false)))
        {
            m_plotter->addCursorAtPixel(event->pos().x());
        }
        else
        {
            m_plotter->removeCursor(selected);
        }
        updatePlot();
    }
}

void WPlot::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_plotter->AddUndoStatus();
    m_plotter->zoomXToCursors(event->pos());
    updatePlot();
}

void WPlot::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == dragButton)
    {
        if (m_drag)
        {
            m_drag = false;
        }
        if (m_plotter->getCursorDragged() != 0)
        {
            m_plotter->releaseCursor();
        }
    }
}

void WPlot::mouseMoveEvent(QMouseEvent* event)
{
    if (m_drag)
    {
        if (m_movingUndo) // Add undo to be done only once
        {
            m_plotter->AddUndoStatus();
            m_movingUndo = false;
        }

        QPoint delta = m_lastPoint - event->pos();
        m_lastPoint = event->pos();
        m_plotter->scrollXpixel( delta.x());
        m_plotter->scrollYpixel(-delta.y());
        updatePlot();
    }

    int index = m_plotter->getCursorDragged();
    if (index != 0)
    {
        QPoint delta =  event->pos() - m_lastPoint;
        m_lastPoint = event->pos();
        m_plotter->cursorScrollPixel(index-1, delta.x());
        updatePlot();
    }

    int selected = 0;
    if (m_plotter->onCursor(event->pos(), selected, false))
    {
        this->setCursor(Qt::SizeHorCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void WPlot::wheelEvent(QWheelEvent* event)
{
    QPoint angleDelta = event->angleDelta();
    if (angleDelta != QPoint(0,0))
    {
        m_plotter->AddUndoStatus(); // To be filetered
        m_plotter->zoomX((qreal)angleDelta.y()/120);
        m_plotter->zoomY((qreal)angleDelta.x()/120);
        updatePlot();
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
            m_plotter->AddUndoStatus(); // To be filetered
            m_plotter->zoomX((factor-1)*5);
            m_plotter->zoomY((factor-1)*5);
            updatePlot();
        }
    }
    return QWidget::event(event);
}

void WPlot::resizeEvent(QResizeEvent *event)
{
    m_plotter->setSize(event->size());
    updatePlot();
}

void WPlot::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Z) && (QApplication::keyboardModifiers()) && (Qt::ControlModifier))
    {
        m_plotter->Undo();
        updatePlot();
    }
    if ((event->key() == Qt::Key_X) && (QApplication::keyboardModifiers()) && (Qt::ControlModifier))
    {
        m_plotter->Redo();
        updatePlot();
    }
}
