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
    explicit WPlot(QWidget *parent = 0);
    ~WPlot();
    void loadDataFile(QString fileName);

    const Qt::MouseButton dragButton = Qt::LeftButton;
    const Qt::MouseButton addCursorButton = Qt::RightButton;

public slots:
    void updatePlot(void);

private:
    Ui::WPlot *ui;

    QImage plot;
    Plotter *m_plotter;

    bool m_drag;
    QPoint m_lastPoint;
    bool m_movingUndo;

    void createMenu(void);

private slots:
    void on_actionOpen_data_file_triggered();
    void on_actionExport_data_file_triggered();
    void on_actionZoom_Undo_triggered();
    void on_actionZoom_Redo_triggered();

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
