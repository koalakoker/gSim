#ifndef WPLOT_H
#define WPLOT_H

#include <QWidget>
#include <QThread>
#include <QFile>
#include <QMouseEvent>

#include "plotter.h"

class WPlot : public QWidget {
    Q_OBJECT
public:
    WPlot(QWidget * parentb = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);

public slots:
    void updatePlot(void);

private:
    QImage plot;
    QThread* m_thread;
    Plotter* m_plotter;
};

#endif // WPLOT_H
