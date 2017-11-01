#ifndef WPLOT_H
#define WPLOT_H

#include <QWidget>
#include <QThread>
#include <QFile>

#include "plotter.h"

class WPlot : public QWidget {
    Q_OBJECT
public:
    WPlot(QWidget * parent = 0) : QWidget(parent) {
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

        // create plotter and thread
        Plotter * p = new Plotter(size(), QRectF(0, 0, 1, 1), data);
        QThread * thread = new QThread;
        p->moveToThread(thread);

        // do connections
        connect(thread, SIGNAL(started()), p, SLOT(plot()));
        connect(p, SIGNAL(done(QImage)), this, SLOT(updatePlot(QImage)));
        connect(p, SIGNAL(cleanup()), thread, SLOT(quit()));
        connect(thread, SIGNAL(finished()), p, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        thread->start();
    }

protected:
    void paintEvent(QPaintEvent *) {
        QPainter p(this);
        p.drawImage(QPoint(0, 0), plot);
    }

public slots:
    void updatePlot(QImage p) {
        plot = p;
        repaint();
    }
private:
    QImage plot;
};

#endif // WPLOT_H