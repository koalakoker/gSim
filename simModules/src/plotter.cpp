#include "plotter.h"

#include <QElapsedTimer>
#include <QTimer>

QImage Plotter::plot()
{
    const Qt::GlobalColor plotColor[] = {Qt::black, Qt::blue, Qt::green, Qt::red};

    QElapsedTimer t;
    t.start();
    QImage img(m_size, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    QPainter p(&img);
    QPen pen(Qt::darkBlue);
    pen.setWidth(1);
    p.setPen(pen);

    if (m_data.size() != 0)
    {
        int trackNum = m_data[0].size();
        int sampleNum = m_data.size();

        double x0 = invMapX(0);
        double x1 = invMapX(1);
        double dX = x1-x0;
        double dY = m_data[1][0]-m_data[0][0];
        int di = dX/dY;
        if (di <= 0)
        {
            di = 1;
        }

        QVector<double> tSample;
        if (trackNum > 1)
        {
            tSample.reserve(sampleNum);
        }
        for (int track = 1; track < trackNum; track++) // Skip index 0 that is the time (x)
        {
            pen.setColor(plotColor[track-1]);
            p.setPen(pen);

            switch (m_style)
            {
            case POINT_STYLE:
                {
                    if (track == 1) /* See below the optimizaton description */
                    {
                        for (int i = 0; i < m_data.size(); i++)
                        {
                            QPointF point;
                            p.drawPoint(point = map(m_data[i][0], m_data[i][track]));
                            tSample.append(point.x());
                        }
                    }
                    else
                    {
                        for (int i = 0; i < m_data.size(); i++)
                        {
                            p.drawPoint(QPointF(tSample[i], mapY(m_data[i][track])));
                        }
                    }
                }
                break;
            case LINE_STYLE:
                {
                    if (track == 1) /* For first trac are computed t/x values and stored in temporary array tSample */
                    {
                        QPointF nextP, prevP = map(m_data[0][0], m_data[0][track]); /* To track the line the prev point is used */
                        tSample.append(prevP.x());
                        for (int i = 0; i < m_data.size() - di; i+=di)
                        {
                            p.drawLine(prevP, nextP = map(m_data[i+1][0], m_data[i+1][track]));
                            prevP = nextP;
                            tSample.append(nextP.x());
                        }

                    }
                    else /* For the t/x value are used the preprocessed values */
                    {
                        int j = 0;
                        QPointF nextP, prevP = QPointF(tSample[j], mapY(m_data[0][track]));
                        for (int i = 0; i < m_data.size() - di; i+=di)
                        {
                            p.drawLine(prevP, nextP = QPointF(tSample[j+1], mapY(m_data[i+1][track])));
                            prevP = nextP;
                            j++;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
        //p.setPen(QPen(Qt::red));
        //p.drawText(10,20,QString("Rect: Top %1, Bottom %2").arg(_range.top()).arg(_range.bottom()));
    }

    /* Cursors */
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    p.setPen(pen);

    m_cursorRect.clear();
    for (int cur = 0; cur < m_cursorPos.size(); cur++)
    {
        qreal curXpos       = m_cursorPos.at(cur);
        qreal curYposTop    = m_range.y();
        qreal curYposBottom = m_range.y()+m_range.height();
        p.drawLine(map(curXpos, curYposTop), map(curXpos, curYposBottom));

        QPointF top     = map(curXpos, curYposTop);
        QPointF bottom  = map(curXpos, curYposBottom);
        QPoint  topLeft    (top.x()    - m_cursorMargin, top.y());
        QPoint  bottomRight(bottom.x() + m_cursorMargin, bottom.y());
        QRect   rect(topLeft, bottomRight);
        m_cursorRect.append(rect);
    }

    //qDebug() << "plotted in" << t.elapsed() << "msec";
    return img;
}

QPointF Plotter::map(double x, double y)
{
    return QPointF(                 (m_size.width () * ((x - m_range.x()) / m_range.width ())),
                   (m_size.height()-(m_size.height() * ((y - m_range.y()) / m_range.height()))));
}

double Plotter::invMapX(double x)
{
    return (((x / m_size.width()) * m_range.width()) + m_range.x());
}

double Plotter::mapX(double x)
{
    return (m_size.width () * ((x - m_range.x()) / m_range.width ()));
}

double Plotter::mapY(double y)
{
    return (m_size.height()-(m_size.height() * ((y - m_range.y()) / m_range.height())));
}

// Scroll

void Plotter::scrollX(qreal val)
{
    m_range.setLeft(m_range.left() + val);
    m_range.setRight (m_range.right()  + val);
}

void Plotter::scrollY(qreal val)
{
    m_range.setTop (m_range.top()  + val);
    m_range.setBottom(m_range.bottom() + val);
}

void Plotter::scrollXpixel(int pix)
{
    scrollX((m_range.width()  * (qreal)(pix))/(qreal)(m_size.width ()));
}

void Plotter::scrollYpixel(int pix)
{
    scrollY((m_range.height() * (qreal)(pix))/(qreal)(m_size.height()));
}

// Zoom

void Plotter::zoomX(qreal val)
{
    qreal delta = m_range.width() * val * 0.05;
    m_range.setLeft(m_range.left() + delta);
    m_range.setRight(m_range.right() - delta);
}

void Plotter::zoomY(qreal val)
{
    qreal delta = m_range.height() * val * 0.05;
    m_range.setTop   (m_range.top()    + delta);
    m_range.setBottom(m_range.bottom() - delta);
}

void Plotter::zoomXToCursors(QPoint point)
{
    qreal xMin,xMax;
    qreal xPos = invMapX(point.x());

    QVector<qreal> xPoints;
    xPoints.append(xMin = m_range.left());
    xPoints.append(xMax = m_range.right());

    int i;
    for (i = 0; i < m_cursorPos.size(); i++)
    {
        xPoints.append(m_cursorPos.at(i));
    }

    qSort(xPoints);

    for (i = 0; i < xPoints.size(); i++)
    {
        if (xPos < xPoints.at(i))
        {
            xMin = xPoints.at(i-1);
            xMax = xPoints.at(i);
            break;
        }
    }

    if ((m_range.left() == xMin) && (m_range.right() == xMax))
    {
        zoomX(5);
    }
    else
    {
        m_range.setLeft(xMin);
        m_range.setRight(xMax);
    }
}

// Cursors
void Plotter::addCursor(qreal pos)
{
    m_cursorPos.append(pos);
}

void Plotter::addCursorAtPixel(int pos)
{
    m_cursorPos.append(invMapX(pos));
}

void Plotter::removeCursor(int index)
{
    m_cursorPos.remove(index);
}

void Plotter::setCursorPos(int index, qreal pos)
{
    m_cursorPos[index] += pos;
}

void Plotter::cursorScrollPixel(int index, int pix)
{
    setCursorPos(index, (m_range.width()  * (qreal)(pix))/(qreal)(m_size.width ()));
}

bool Plotter::onCursor(QPoint point, int& selectedCursor, bool startDrag)
{
    bool retVal = false;
    for (int cursor = 0; cursor < m_cursorRect.size(); cursor++)
    {
        if (m_cursorRect.at(cursor).contains(point))
        {
            retVal = true;
            selectedCursor = cursor;
            if (startDrag)
            {
                dragCursor(cursor);
            }
        }
    }
    return retVal;
}

void Plotter::dragCursor(int index)
{
    if ((index >= 0) && (index < m_cursorPos.size()))
    {
        m_cursorDrag = index + 1; // 0 none, index + 1 (zero based) if cursor index is dragged
    }
}

void Plotter::releaseCursor()
{
    m_cursorDrag = 0;
}

int Plotter::getCursorDragged()
{
    return m_cursorDrag;
}

// Undo
void Plotter::Undo(void)
{
    if (!m_undoRangeHystory.isEmpty())
    {
        m_redoRangeHystory.append(m_range);
        m_range = m_undoRangeHystory.takeLast();
    }
}

void Plotter::Redo(void)
{
    if (!m_redoRangeHystory.isEmpty())
    {
        m_undoRangeHystory.append(m_range);
        m_range = m_redoRangeHystory.takeLast();
    }
}

void Plotter::AddUndoStatus(void)
{
    if (!m_debounce)
    {
        m_undoRangeHystory.append(m_range);
        m_redoRangeHystory.clear();
        QTimer::singleShot(500, this, SLOT(endTimer()));
        m_debounce = true;
    }
}

void Plotter::endTimer()
{
    m_debounce = false;
}
