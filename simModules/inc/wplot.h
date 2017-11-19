#ifndef WPLOT_H
#define WPLOT_H

#include <QWidget>

#include "plotter.h"

class WPlot : public QWidget
{
    Q_OBJECT

public:
    explicit WPlot(QWidget *parent = 0);
    ~WPlot();
    void loadDataFile(QString fileName);
    void saveDataFile(QString fileName);

    const Qt::MouseButton dragButton = Qt::LeftButton;
    const Qt::MouseButton addCursorButton = Qt::RightButton;

    Plotter *m_plotter;
    QString m_fileName;

public slots:
    void updatePlot(void);
    void zoom_Undo(void);
    void zoom_Redo(void);

signals:
    void newPlotter(void);

private:
    QVector<SData> data;
    QImage plot;
    bool m_drag;
    QPoint m_lastPoint;
    bool m_movingUndo;

    void createMenu(void);

private slots:

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
