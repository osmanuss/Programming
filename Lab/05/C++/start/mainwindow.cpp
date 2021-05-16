#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QImage>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QBitArray>
#include <QMessageBox>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->load_button, &QPushButton::clicked, this, &MainWindow::loadImage);
    connect(ui->save_button, &QPushButton::clicked, this, &MainWindow::saveImage);
    connect(ui->code_button, &QPushButton::clicked, this, &MainWindow::encodeMsg);
    connect(ui->decode_button, &QPushButton::clicked, this, &MainWindow::decodeMsg);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::msgChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Допустимые форматы (*.png)"));
    if (!image.load(fileName, "PNG"))
    {
        ui->label->setText("Изображение не загружено");
        return;
    }
    ui->label->setText("Изображение успешно загружено");
    image.convertTo(QImage::Format_ARGB32);

    not_used = (image.width() * image.height() * 3) / 8 - serdechko.size() - 4;
}

void MainWindow::saveImage()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить изображение"), "", "Допустимые форматы (*.png)");
        if (image.save(path, "PNG"))
        {
            ui->label->setText(QString("Изображение успешно сохранено").arg(path));
        }
        else
        {
            ui->label->setText("Изображение не сохранилось");
        }
}

void writeBit(QImage &img, int index, bool val)
{
    int pixelIndex = index / 3;
    int x = pixelIndex % img.width();
    int y = pixelIndex / img.width();
    switch (index % 3)
    {
    case 0:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x010000) | (val << 16));
    case 1:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x000100) | (val << 8));
    default:
        img.setPixel(x, y, (img.pixel(x, y) & ~0x000001) | val);
    }
}

void writeByte(QImage& img, uint begin, QByteArray& byteArray)
{
    uint end = (begin + byteArray.size()) * 8;

    for (uint i = begin * 8; i < end; ++i)
    {
        writeBit(img, i, (byteArray[i / 8] >> (7 - i % 8)) & 1);
    }
}

void MainWindow::encodeMsg()
{
    used = ui->plainTextEdit->toPlainText().toUtf8().size();
    if (not_used < used)
    {
        ui->label->setText("Ошибка. Недостаточно места!");
        return;
    }
    QByteArray array;
    array.push_back(serdechko);
    for (int i = 4 - 1; i >= 0; --i)
    {
        array.push_back((used >> i*8) & 0xff);
    }
    array.push_back(ui->plainTextEdit->toPlainText().toUtf8());
    writeByte(image, 0, array);
    ui->label->setText("Сообщение добавлено в картинку!");
}

bool readBit(const QImage &img, int index)
{
    int pixelIndex = index / 3;
    int x = pixelIndex % img.width();
    int y = pixelIndex / img.width();

    switch (index % 3)
    {
    case 0:
        return (img.pixel(x, y) >> 16) & 1;
    case 1:
        return (img.pixel(x, y) >> 8) & 1;
    default:
        return img.pixel(x, y) & 1;
    }
}

QByteArray readByte(const QImage& img, uint begin, uint length)
{
    QByteArray array;
    char x = 0;
    uint end = (begin + length) * 8;

    for (uint i = begin * 8; i < end; ++i) {
        x = (x << 1) | readBit(img, i);
        if (i % 8 == 7)
        {
            array.push_back(x);
            x = 0;
        }
    }

    return array;
}

void MainWindow::decodeMsg()
{
    int headerSize = serdechko.size() + 4;
        QByteArray array;
        array = readByte(image, 0, headerSize);

        for (uint i = 0; i < serdechko.size(); ++i)
        {
            if (serdechko[i] != array[i])
            {
                ui->label->setText("Сообщение не обнаружено");
                return;
            }
        }

        uint size_message = 0;
        for (uint i = serdechko.size(); i < serdechko.size() + 4; ++i)
        {
            size_message = (size_message << 8) + static_cast<unsigned char>(array[i]);
        }
        array = readByte(image, headerSize, size_message);

        ui->label->setText(QString("Присутствует сообщение длиной %1 байт").arg(size_message));
        ui->plainTextEdit->setPlainText(QString::fromUtf8(array));
}

void MainWindow::msgChanged()
{
    if (not_used < 0) return;
    used = ui->plainTextEdit->toPlainText().toUtf8().size();
    if (not_used >= used)
    {
        ui->label->setText(QString("Ещё можно ввести: %1 байт").arg(not_used - used));
    }
    else
    {
        ui->label->setText(QString("Слишком много символов"));
    }
}

