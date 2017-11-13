#ifndef MWPLOT_H
#define MWPLOT_H

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

private slots:
    void on_actionOpen_data_file_triggered();
    void on_actionExport_data_file_triggered();
    void on_actionZoom_Undo_triggered();
    void on_actionZoom_Redo_triggered();

private:
    Ui::MWPlot *ui;
};

#endif // MWPLOT_H
