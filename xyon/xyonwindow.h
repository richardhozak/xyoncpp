#ifndef XYONWINDOW_H
#define XYONWINDOW_H

#include <QWindow>
#include <QObject>
#include <QMouseEvent>

class XyonWindow : public QWindow
{
    Q_OBJECT

public:
    explicit XyonWindow();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
private:
    QPoint clickPos;
};

#endif // XYONWINDOW_H
