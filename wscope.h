#ifndef WSCOPE_H
#define WSCOPE_H

#include <QWidget>
#include "QVector"
#include "qcustomplot.h"
#include <QMouseEvent>

#define ELEMENT 100
#define CURSOR_NUMBER 2
#define MAX_TRACKS 4

namespace Ui {
class WScope;
}

class WScope : public QWidget
{
    Q_OBJECT
public:
    explicit WScope(int tracks = 1, QWidget *parent = 0);

    void reset(void);
    void addPoint(double t, QVector<double> y);
    void setData(QVector<double> tArray, QVector<QVector<double> > yArray);
    void exportData(void);
    void setAxis(double xMin,double  xMax,double  yMin,double  yMax);

    void setdt(double dt);
    double dt(void) {return this->dtVal;}

    int tracks() {return tracksNum;}
    int selectedTrack() {return selectedTrackValue;}
    bool setSelectedTrack(int tr);

private:
    Ui::WScope *ui;
    QCPItemLine* vCursor[CURSOR_NUMBER];
    bool vCursorDrag[CURSOR_NUMBER];
    const QColor vCursorColor[CURSOR_NUMBER] = {Qt::black, Qt::black};
    const Qt::PenStyle vCursorStyle[CURSOR_NUMBER] = {Qt::DashLine, Qt::DashDotLine};

    bool controlVisible;

    int tracksNum;
    int selectedTrackValue;
    QVector<double> tArray;
    QVector<QVector<double>> yArray;

    double dtVal;

    double xMin;
    double xMax;
    double yMin;
    double yMax;

    double getMaxSignalY(void);
    double getMaxSignalX(void);
    double getMinSignalY(void);
    double getMinSignalX(void);

    void updateControls(void);
    double calculateYfromX(double x);

private slots:
    void mousePress(QMouseEvent* event);
    void mouseWheel();
    void mouseMove(QMouseEvent* event);
    void mouseRelease();

    void setTracks(int num);

    void setXMin(double val);
    void setXMax(double val);
    void setYMin(double val);
    void setYMax(double val);

    void maximizeX();
    void maximizeY();

    void axisXSelect(bool ch);
    void axisYSelect(bool ch);

    void cursorUpdated(int cur, double x);

    void selectionChanged();

    void closeEvent(QCloseEvent *event);
    void on_showControl_clicked();

signals:
    void cursorMoved(int cur, double x, double y);
    void hiding(void);

public slots:
	void refresh(void);
};

#endif // WSCOPE_H
