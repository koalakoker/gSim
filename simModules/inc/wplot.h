#ifndef WPLOT_H
#define WPLOT_H

#include <QWidget>
#include <QThread>
#include <QFile>

#include "plotter.h"

class WPlot : public QWidget {
    Q_OBJECT
public:
    WPlot(QWidget * parentb = 0);

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void updatePlot(QImage p);

private:
    QImage plot;
};

#endif // WPLOT_H
