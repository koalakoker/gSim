#ifndef WPLOT_H
#define WPLOT_H

#include <QWidget>
#include <QThread>
#include <QFile>
#include <QMouseEvent>
#include <QWheelEvent>

#include "plotter.h"

class WPlot : public QWidget {
    Q_OBJECT
public:
    WPlot(QWidget * parentb = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

public slots:
    void updatePlot(void);

private:
    QImage plot;
    QThread* m_thread;
    Plotter* m_plotter;

    bool m_drag;
    QPoint m_lastPoint;
};

#endif // WPLOT_H
