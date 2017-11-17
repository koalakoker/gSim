#ifndef WTABLE_H
#define WTABLE_H

#include <QTableWidget>

class WTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit WTable(QWidget *parent = nullptr);

signals:
    void resized(void);

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
};

#endif // WTABLE_H
