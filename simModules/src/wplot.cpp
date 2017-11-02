#include "wplot.h"

WPlot::WPlot(QWidget * parent) : QWidget(parent)
{
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
    static qreal xMax = 1;
    if (event->button() == Qt::RightButton)
    {
        xMax = xMax / 2;
    }
    if (event->button() == Qt::LeftButton)
    {
        xMax = xMax * 2;
    }
    m_plotter->setRangeX_Max(xMax);

    updatePlot();
}
