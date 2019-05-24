#ifndef PLOTTERWINDOW_H
#define PLOTTERWINDOW_H

#include "wcursorinfo.h"
#include "sdata.h"
#include "plotter.h"

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
#include <QToolButton>

namespace Ui {
class PlotterWindow;
}

class PlotterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotterWindow(QString name, QWidget *parent = nullptr);
    ~PlotterWindow();

    QVector<QVector<double>> getCursorValueTrack(void);
    QVector<double> getCursorValueTrack(int cur);
    QVector<double> getSelectedCursorValueTrack(void);
    void addPoint(double t, SData y);
    void createPlot(void);
    void updatePlot(void);
    void exportData(QString filename) {qDebug() << "Export: " << filename;}
    virtual void closeEvent ( QCloseEvent * event );

public slots:
    void onCursorChange();

signals:
    void cursorChanged();

private slots:
    void on_cursorPosChanged(int cur, qreal value);
    void on_actionOpen_data_file_triggered();
    void on_actionExport_data_file_triggered();
    void on_actionZoom_Undo_triggered();
    void on_actionZoom_Redo_triggered();
    void on_actionInfo_data_triggered(bool checked);
    void on_actionBottom_toggled(bool arg1);
    void on_actionLeft_toggled(bool arg1);
    void on_actionRight_toggled(bool arg1);
    void on_actionTop_toggled(bool arg1);
    void on_actionBottom_Left_toggled(bool arg1);
    void on_actionTop_Right_toggled(bool arg1);
    void on_actionAdd_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionReset_Zoom_triggered();
    void on_actionMaximize_vertical_triggered();
    void on_actionMaximize_orizontal_triggered();
    void on_actionZoom_Vertical_In_triggered();
    void on_actionZoom_Vertical_Out_triggered();

private:
    Ui::PlotterWindow *ui;
    QToolButton *zoomButton;
    QToolButton *cursorsButton;
    QToolButton *axisButton;

    WCursorInfo *wCursorInfo;
    QString m_name;

    Plotter *m_plotter;
    QVector<SData> m_data;
    double m_y_max = 0, m_y_min = 0;
    QString m_fileName;
    QPoint m_lastPoint;
    bool m_movingUndo;
    bool m_drag;

    const Qt::MouseButton dragButton = Qt::LeftButton;
    const Qt::MouseButton addCursorButton = Qt::RightButton;

    void loadDataFile(QString fileName);
    void saveDataFile(QString fileName);
    void zoom_Undo(void);
    void zoom_Redo(void);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    bool event(QEvent* event);
    void resizeEvent(QResizeEvent *event);

};

#endif // PLOTTERWINDOW_H
