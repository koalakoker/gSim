#ifndef WSCOPE_H
#define WSCOPE_H

#include <QWidget>
#include "oscope.h"

namespace Ui {
class WScope;
}

class WScope : public QWidget
{
    Q_OBJECT
public:
    explicit WScope(QWidget *parent = 0);

    OScope oscope;

private:
    Ui::WScope *ui;

signals:

public slots:
	void refresh(void);
private slots:
    void on_listPlot_currentRowChanged(int currentRow);
};

#endif // WSCOPE_H
