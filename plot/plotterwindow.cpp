#include "plotterwindow.h"
#include "ui_plotterwindow.h"

#include <QGestureEvent>
#include <QFileDialog>
#include <QDebug>

PlotterWindow::PlotterWindow(QString name, QWidget *parent) : QMainWindow(parent), ui(new Ui::PlotterWindow), wCursorInfo(nullptr), m_name(name)
{
    ui->setupUi(this);

    m_plotter = nullptr;
    m_drag = false;
    grabGesture(Qt::PinchGesture);
    ui->Plot->setMouseTracking(true);
    setMouseTracking(true);

    zoomButton=new QToolButton(this);
    zoomButton->setIcon(QIcon(":/png/zoomMenu.png"));
    zoomButton->setPopupMode(QToolButton::InstantPopup);
    zoomButton->setCheckable(true);
    zoomButton->setChecked(false);
    zoomButton->setMenu(ui->menuZoom);
    ui->toolBar->addWidget(zoomButton);

    cursorsButton=new QToolButton(this);
    cursorsButton->setIcon(QIcon(":/png/cursorInfo.png"));
    cursorsButton->setPopupMode(QToolButton::InstantPopup);
    cursorsButton->setCheckable(true);
    cursorsButton->setChecked(false);
    cursorsButton->setMenu(ui->menuCursors);
    ui->toolBar->addWidget(cursorsButton);

    axisButton=new QToolButton(this);
    axisButton->setIcon(QIcon(":/png/axis_bottom_left.png"));
    axisButton->setPopupMode(QToolButton::InstantPopup);
    axisButton->setCheckable(true);
    axisButton->setChecked(false);
    axisButton->setMenu(ui->menuAxis);
    ui->toolBar->addWidget(axisButton);

    ui->toolBar->setIconSize(QSize(30,24));
}

PlotterWindow::~PlotterWindow()
{
    delete ui;
    if (wCursorInfo)
        delete wCursorInfo;
}

void PlotterWindow::closeEvent(QCloseEvent *event)
{
    if (wCursorInfo)
    {
        wCursorInfo->close();
    }
    event->accept();
}

QVector<QVector<double>> PlotterWindow::getCursorValueTrack(void)
{
    if (m_plotter)
        return m_plotter->getCursorValueTrack();
    return QVector<QVector<double>>();
}
QVector<double> PlotterWindow::getCursorValueTrack(int cur)
{

    if (m_plotter)
        return m_plotter->getCursorValueTrack(cur);
    return QVector<double>();
}
QVector<double> PlotterWindow::getSelectedCursorValueTrack(void)
{
    if (m_plotter)
        return m_plotter->getSelectedCursorValueTrack();
    return QVector<double>();
}

void PlotterWindow::addPoint(double t, SData y)
{
    foreach (double val, y.data())
    {
        if (val > m_y_max)
        {
            m_y_max = val;
        }

        if (val < m_y_min)
        {
            m_y_min = val;
        }

    }

    y.prepend(t);
    m_data.append(y);
}

void PlotterWindow::onCursorChange()
{
    emit cursorChanged();
    if (wCursorInfo)
    {
        wCursorInfo->updateInfo(getCursorValueTrack());
    }
}

// Private Slots
void PlotterWindow::on_cursorPosChanged(int cur, qreal value)
{
    m_plotter->setCursorPos(cur, value);
    updatePlot();
}

// Actions
void PlotterWindow::on_actionOpen_data_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open data file","","*.*");
    if (fileName != "")
    {
        loadDataFile(fileName);
    }
}
void PlotterWindow::on_actionExport_data_file_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Export data file","","*.*");
    saveDataFile(fileName);
}
void PlotterWindow::on_actionZoom_Undo_triggered()
{
    zoom_Undo();
}
void PlotterWindow::on_actionZoom_Redo_triggered()
{
    zoom_Redo();
}
void PlotterWindow::on_actionInfo_data_triggered(bool checked)
{
    if (!wCursorInfo)
    {
        wCursorInfo = new WCursorInfo(this->frameGeometry());
        wCursorInfo->show();
        wCursorInfo->updateInfo(getCursorValueTrack());
        connect (wCursorInfo, SIGNAL(cursorPosChanged(int,qreal)), this, SLOT(on_cursorPosChanged(int,qreal)));
    }
    wCursorInfo->setVisible(checked);
}
void PlotterWindow::on_actionBottom_toggled(bool arg1)
{
    if (m_plotter)
    {
        m_plotter->m_axsisBottom = arg1;
        updatePlot();
    }
    ui->actionBottom_Left->blockSignals(true);
    ui->actionBottom_Left->setChecked(ui->actionBottom->isChecked() && ui->actionLeft->isChecked());
    ui->actionBottom_Left->blockSignals(false);
}
void PlotterWindow::on_actionLeft_toggled(bool arg1)
{
    if (m_plotter)
    {
        m_plotter->m_axsisLeft = arg1;
        updatePlot();
    }
    ui->actionBottom_Left->blockSignals(true);
    ui->actionBottom_Left->setChecked(ui->actionBottom->isChecked() && ui->actionLeft->isChecked());
    ui->actionBottom_Left->blockSignals(false);
}
void PlotterWindow::on_actionRight_toggled(bool arg1)
{
    if (m_plotter)
    {
        m_plotter->m_axsisRight = arg1;
        updatePlot();
    }
    ui->actionTop_Right->blockSignals(true);
    ui->actionTop_Right->setChecked(ui->actionTop->isChecked() && ui->actionRight->isChecked());
    ui->actionTop_Right->blockSignals(false);
}
void PlotterWindow::on_actionTop_toggled(bool arg1)
{
    if (m_plotter)
    {
        m_plotter->m_axsisTop = arg1;
        updatePlot();
    }
    ui->actionTop_Right->blockSignals(true);
    ui->actionTop_Right->setChecked(ui->actionTop->isChecked() && ui->actionRight->isChecked());
    ui->actionTop_Right->blockSignals(false);
}
void PlotterWindow::on_actionBottom_Left_toggled(bool arg1)
{
    ui->actionBottom->setChecked(arg1);
    ui->actionLeft->setChecked(arg1);
}
void PlotterWindow::on_actionTop_Right_toggled(bool arg1)
{
    ui->actionTop->setChecked(arg1);
    ui->actionRight->setChecked(arg1);
}
void PlotterWindow::on_actionAdd_triggered()
{
    // Add cursor
    m_plotter->addCursor();
    updatePlot();

    // If not present show cursor info
    if (!wCursorInfo)
    {
        on_actionInfo_data_triggered(true);
    }
    else
    {
        wCursorInfo->setVisible(true);
    }
}
void PlotterWindow::on_actionZoom_In_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->zoomXToCursors(QPoint(ui->Plot->size().width()/2,ui->Plot->size().height()/2));
    updatePlot();
}
void PlotterWindow::on_actionZoom_Out_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->zoomOutHorizontal();
    updatePlot();
}
void PlotterWindow::on_actionZoom_Vertical_In_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->zoomInVertical();
    updatePlot();
}
void PlotterWindow::on_actionZoom_Vertical_Out_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->zoomOutVertical();
    updatePlot();
}
void PlotterWindow::on_actionReset_Zoom_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->resetView();
    updatePlot();
}
void PlotterWindow::on_actionMaximize_vertical_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->resetVertical();
    updatePlot();
}
void PlotterWindow::on_actionMaximize_orizontal_triggered()
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->resetHorizontal();
    updatePlot();
}

void PlotterWindow::createPlot(void)
{
    qreal x_min = 0, x_max = 0;
    if (m_data.size() != 0)
    {
        x_min = m_data[0][0];
        x_max = m_data[m_data.size()-1][0];
    }

    m_plotter = new Plotter(
                ui->Plot->size() - QSize(2,2),
                QRectF(x_min, m_y_min, x_max - x_min, m_y_max - m_y_min),
                m_data,
                Plotter::LINE_STYLE);


    updatePlot();

    connect(m_plotter, SIGNAL(cursorChanged()), this, SLOT(onCursorChange()));
    setWindowTitle(m_fileName + " " + m_name);
}

void PlotterWindow::updatePlot(void)
{
    ui->Plot->setPixmap(QPixmap::fromImage(m_plotter->plot()));
    ui->Plot->setMinimumSize(1, 1);
    repaint();
}

void PlotterWindow::mousePressEvent(QMouseEvent* event)
{
    if (!m_plotter)
        return;

    if (event->button() == dragButton)
    {
        int selected = 0;
        m_lastPoint = ui->Plot->mapFrom(this,event->pos());
        if (m_plotter->onCursor(m_lastPoint, selected, true))
        {

        }
        else
        {
            m_movingUndo = true;
            m_drag = true;
        }

    }

    if (event->button() == addCursorButton)
    {
        int selected = 0;
        if (!(m_plotter->onCursor(ui->Plot->mapFrom(this,event->pos()), selected, false)))
        {
            m_plotter->addCursorAtPixel(ui->Plot->mapFrom(this,event->pos()).x());
        }
        else
        {
            m_plotter->removeCursor(selected);
        }
        updatePlot();
    }
}


void PlotterWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (!m_plotter)
        return;
    if (event->button() == dragButton)
    {
        if (m_drag)
        {
            m_drag = false;
        }
        if (m_plotter->getCursorDragged() != 0)
        {
            m_plotter->releaseCursor();
        }
    }
}

void PlotterWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_plotter)
        return;
    if (m_drag)
    {
        if (m_movingUndo) // Add undo to be done only once
        {
            m_plotter->AddUndoStatus();
            m_movingUndo = false;
        }

        QPoint delta = m_lastPoint - ui->Plot->mapFrom(this,event->pos());
        m_lastPoint = ui->Plot->mapFrom(this,event->pos());
        m_plotter->scrollXpixel( delta.x());
        m_plotter->scrollYpixel(-delta.y());
        updatePlot();
    }

    int index = m_plotter->getCursorDragged();
    if (index != 0)
    {
        QPoint delta =  ui->Plot->mapFrom(this,event->pos()) - m_lastPoint;
        m_lastPoint = ui->Plot->mapFrom(this,event->pos());
        m_plotter->cursorScrollPixel(index-1, delta.x());
        updatePlot();
    }

    int selected = 0;
    if (m_plotter->onCursor(ui->Plot->mapFrom(this,event->pos()), selected, false))
    {
        this->setCursor(Qt::SizeHorCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void PlotterWindow::wheelEvent(QWheelEvent* event)
{
    if (!m_plotter)
        return;
    QPoint angleDelta = event->angleDelta();
    if (angleDelta != QPoint(0,0))
    {
        m_plotter->AddUndoStatus(); // To be filetered
        m_plotter->zoomX(static_cast<qreal>(angleDelta.y())/120);
        m_plotter->zoomY(static_cast<qreal>(angleDelta.x())/120);
        updatePlot();
    }
}

void PlotterWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (!m_plotter)
        return;
    m_plotter->AddUndoStatus();
    m_plotter->zoomXToCursors(ui->Plot->mapFrom(this,event->pos()));
    updatePlot();
}

bool PlotterWindow::event(QEvent *event)
{
    if (!m_plotter)
        QWidget::event(event);
    if (event->type() == QEvent::Gesture)
    {
        QGestureEvent* gest = static_cast<QGestureEvent*>(event);
        if (QGesture *pinch = gest->gesture(Qt::PinchGesture))
        {
            QPinchGesture* pinchGest = static_cast<QPinchGesture *>(pinch);
            qreal factor = pinchGest->scaleFactor();
            m_plotter->AddUndoStatus(); // To be filetered
            m_plotter->zoomX((factor-1)*5);
            m_plotter->zoomY((factor-1)*5);
            updatePlot();
        }
    }
    if (event->type() == QEvent::HoverMove)
    {
        mouseMoveEvent(static_cast<QMouseEvent*>(event));
    }
    return QWidget::event(event);
}

void PlotterWindow::resizeEvent(QResizeEvent *event)
{
    if (!m_plotter)
        return;
    if (event->type() == QEvent::Resize)
    {
        m_plotter->setSize(ui->Plot->size() - QSize(2,2));
        updatePlot();
    }
}

void PlotterWindow::loadDataFile(QString fileName)
{
    double y_max = 0, y_min = 0;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        m_data.clear();
        QTextStream stream(&file);
        QString line;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            QStringList fields = line.split(QRegExp("[\t ]+"));
            SData sample;
            for (int i = 0; i < fields.size(); i++)
            {
                double val = fields.at(i).toDouble();
                sample.append(val);
                if (i != 0)
                {
                    if (val > y_max)
                    {
                        y_max = val;
                    }

                    if (val < y_min)
                    {
                        y_min = val;
                    }
                }
            }
            m_data.append(sample);
        }
        m_fileName = fileName;

        if (m_plotter)
        {
            delete m_plotter; // remove old data plotter
        }

        createPlot();
    }
    file.close();
}

void PlotterWindow::saveDataFile(QString fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        for (int row = 0; row < m_data.size(); row++)
        {
            SData dataRow = m_data.at(row);
            for (int i = 0; i < dataRow.size(); i++)
            {
                double val = dataRow.data().at(i);
                if (i == 0)
                {
                    stream << val;
                }
                else
                {
                    stream << " " << val;
                }
            }
            stream << endl;
        }
    }
    file.close();
}

void PlotterWindow::zoom_Undo(void)
{
    if (!m_plotter)
        return;
    m_plotter->Undo();
    updatePlot();
}

void PlotterWindow::zoom_Redo(void)
{
    if (!m_plotter)
        return;
    m_plotter->Redo();
    updatePlot();
}
