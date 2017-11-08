#include "plotter.h"

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

    int trackNum = m_data[0].size();
    int sampleNum = m_data.size();
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
                        p.drawPoint(QPointF(tSample[i+1], mapY(m_data[i][track])));
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
                    for (int i = 0; i < m_data.size() - 1; i++)
                    {
                        p.drawLine(prevP, nextP = map(m_data[i+1][0], m_data[i+1][track]));
                        prevP = nextP;
                        tSample.append(nextP.x());
                    }

                }
                else /* For the t/x value are used the preprocessed values */
                {
                    QPointF nextP, prevP = QPointF(tSample[0], mapY(m_data[0][track]));
                    for (int i = 0; i < m_data.size() - 1; i++)
                    {
                        p.drawLine(prevP, nextP = QPointF(tSample[i+1], mapY(m_data[i+1][track])));
                        prevP = nextP;
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

    qDebug() << "plotted in" << t.elapsed() << "msec";
    return img;
}

QPointF Plotter::map(double x, double y)
{
    return QPointF(                 (m_size.width () * ((x - m_range.x()) / m_range.width ())),
                   (m_size.height()-(m_size.height() * ((y - m_range.y()) / m_range.height()))));
}

double Plotter::mapY(double y)
{
    return (m_size.height()-(m_size.height() * ((y - m_range.y()) / m_range.height())));
}

// Cursors
void Plotter::addCursor(qreal pos)
{
    m_cursorPos.append(pos);
}

void Plotter::setCursorPos(int index, qreal pos)
{
    m_cursorPos[index] += pos;
}

void Plotter::cursorScrollPixel(int index, int pix)
{
    setCursorPos(index, (m_range.width()  * (qreal)(pix))/(qreal)(m_size.width ()));
}

bool Plotter::onCursor(QPoint point, bool select)
{
    bool retVal = false;
    for (int cursor = 0; cursor < m_cursorRect.size(); cursor++)
    {
        if (m_cursorRect.at(cursor).contains(point))
        {
            retVal = true;
            if (select)
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
