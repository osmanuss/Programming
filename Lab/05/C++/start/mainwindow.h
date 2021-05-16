#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void loadImage();
    void saveImage();
    void encodeMsg();
    void decodeMsg();
    void msgChanged();

private:
    QImage image;
    uint not_used = 0;
    uint used = 0;
    const QList<char> serdechko
    {
            static_cast<char>(0b11100010),
            static_cast<char>(0b10011101),
            static_cast<char>(0b10100100)
    };
};
#endif // MAINWINDOW_H
