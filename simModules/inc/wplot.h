#ifndef WPLOT_H
#define WPLOT_H

#include <QWidget>
#include <QThread>
#include <QFile>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMenuBar>

#include "plotter.h"

class WPlot : public QWidget {
    Q_OBJECT
public:
    WPlot(QString fileName, QWidget * parentb = 0);

    const Qt::MouseButton dragButton = Qt::LeftButton;
    const Qt::MouseButton addCursorButton = Qt::RightButton;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    bool event(QEvent* event);
    void resizeEvent(QResizeEvent *event);

public slots:
    void updatePlot(void);

private slots:
    void actionOpen  (void);
    void actionExport(void);
    void actionUndo  (void);
    void actionRedo  (void);

private:
    QImage plot;
    QThread *m_thread;
    Plotter *m_plotter;
    QMenuBar *menu;

    bool m_drag;
    QPoint m_lastPoint;
    bool m_movingUndo;

    void createMenu(void);
};

#endif // WPLOT_H
