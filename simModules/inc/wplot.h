#ifndef WPLOT_H
#define WPLOT_H

#include <QMainWindow>

#include "plotter.h"

namespace Ui {
class WPlot;
}

class WPlot : public QMainWindow
{
    Q_OBJECT

public:
    explicit WPlot(QWidget *parent = 0, QString fileName = "model2.txt");
    ~WPlot();

    const Qt::MouseButton dragButton = Qt::LeftButton;
    const Qt::MouseButton addCursorButton = Qt::RightButton;

public slots:
    void updatePlot(void);

private:
    Ui::WPlot *ui;

    QImage plot;
    QThread *m_thread;
    Plotter *m_plotter;
    QMenuBar *menu;

    bool m_drag;
    QPoint m_lastPoint;
    bool m_movingUndo;

    void createMenu(void);

private slots:
    void actionOpen  (void);
    void actionExport(void);
    void actionUndo  (void);
    void actionRedo  (void);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    bool event(QEvent* event);
    void resizeEvent(QResizeEvent *event);

};

#endif // WPLOT_H
