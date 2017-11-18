#ifndef MWPLOT_H
#define MWPLOT_H

#include "wcursorinfo.h"

#include <QMainWindow>

namespace Ui {
class MWPlot;
}

class MWPlot : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWPlot(QWidget *parent = 0);
    ~MWPlot();
    void loadDataFile(QString fileName);
    QVector<QVector<double>> getCursorValueTrack(void);
    QVector<double> getCursorValueTrack(int cur);
    QVector<double> getSelectedCursorValueTrack(void);

public slots:
    void onNewPlotter();
    void onCursorChange();

signals:
    void cursorChanged();

private slots:
    void on_cursorPosChanged(int cur, qreal value);
    void on_actionOpen_data_file_triggered();
    void on_actionExport_data_file_triggered();
    void on_actionZoom_Undo_triggered();
    void on_actionZoom_Redo_triggered();
    void on_actionInfo_data_changed();
    void on_actionBottom_toggled(bool arg1);
    void on_actionLeft_toggled(bool arg1);
    void on_actionRight_toggled(bool arg1);
    void on_actionTop_toggled(bool arg1);

    void on_actionTest_triggered();

private:
    Ui::MWPlot *ui;
    WCursorInfo *wCursorInfo;
};

#endif // MWPLOT_H
