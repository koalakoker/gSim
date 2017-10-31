#include <QWidget>
#include <QElapsedTimer>
#include <QPainter>
#include <QDebug>
#include <QThread>
#include <QFile>

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

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget * parent = 0) : QWidget(parent) {
        // prepping data
        QVector<double> data;
        //data.reserve(200000);

        QFile file("C:\\MyProjects\\build-gSim\\scope_teta.txt");
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

        //for (int i = 0; i < 200000; ++i) data.append((double)qrand() / RAND_MAX);
//        for (int i = 0; i < 100000; ++i)
//        {
//            data.append((double)i / 100000);
//            data.append((1+sin(((double)i / 100000)*6.28*10))/2);
//        }

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
