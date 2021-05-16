# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindowAZBraj.ui'
##
## Created by: Qt User Interface Compiler version 6.0.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(531, 454)
        MainWindow.setStyleSheet(u"QPushButton:hover{color: blue; font: bold 10pt;}")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.verticalLayout = QVBoxLayout(self.centralwidget)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.load_button = QPushButton(self.centralwidget)
        self.load_button.setObjectName(u"load_button")
        sizePolicy = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.load_button.sizePolicy().hasHeightForWidth())
        self.load_button.setSizePolicy(sizePolicy)
        font = QFont()
        font.setPointSize(11)
        font.setBold(False)
        font.setItalic(False)
        font.setUnderline(False)
        font.setKerning(True)
        font.setStyleStrategy(QFont.PreferDefault)
        self.load_button.setFont(font)
        self.load_button.setCursor(QCursor(Qt.OpenHandCursor))

        self.verticalLayout.addWidget(self.load_button)

        self.save_button = QPushButton(self.centralwidget)
        self.save_button.setObjectName(u"save_button")
        sizePolicy.setHeightForWidth(self.save_button.sizePolicy().hasHeightForWidth())
        self.save_button.setSizePolicy(sizePolicy)
        self.save_button.setFont(font)
        self.save_button.setCursor(QCursor(Qt.OpenHandCursor))

        self.verticalLayout.addWidget(self.save_button)

        self.code_button = QPushButton(self.centralwidget)
        self.code_button.setObjectName(u"code_button")
        sizePolicy.setHeightForWidth(self.code_button.sizePolicy().hasHeightForWidth())
        self.code_button.setSizePolicy(sizePolicy)
        self.code_button.setFont(font)
        self.code_button.setCursor(QCursor(Qt.OpenHandCursor))

        self.verticalLayout.addWidget(self.code_button)

        self.decode_button = QPushButton(self.centralwidget)
        self.decode_button.setObjectName(u"decode_button")
        sizePolicy.setHeightForWidth(self.decode_button.sizePolicy().hasHeightForWidth())
        self.decode_button.setSizePolicy(sizePolicy)
        self.decode_button.setFont(font)
        self.decode_button.setCursor(QCursor(Qt.OpenHandCursor))

        self.verticalLayout.addWidget(self.decode_button)

        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")
        self.label.setStyleSheet(u"")

        self.verticalLayout.addWidget(self.label)

        self.plainTextEdit = QPlainTextEdit(self.centralwidget)
        self.plainTextEdit.setObjectName(u"plainTextEdit")
        self.plainTextEdit.setEnabled(True)
        sizePolicy1 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.plainTextEdit.sizePolicy().hasHeightForWidth())
        self.plainTextEdit.setSizePolicy(sizePolicy1)
        self.plainTextEdit.setStyleSheet(u"")

        self.verticalLayout.addWidget(self.plainTextEdit)

        self.pushButton = QPushButton(self.centralwidget)
        self.pushButton.setObjectName(u"pushButton")
        font1 = QFont()
        font1.setPointSize(11)
        self.pushButton.setFont(font1)
        self.pushButton.setCursor(QCursor(Qt.OpenHandCursor))

        self.verticalLayout.addWidget(self.pushButton)

        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        self.pushButton.clicked.connect(MainWindow.close)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.load_button.setText(QCoreApplication.translate("MainWindow", u"\u0417\u0430\u0433\u0440\u0443\u0437\u0438\u0442\u044c \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443", None))
        self.save_button.setText(QCoreApplication.translate("MainWindow", u"\u0421\u043e\u0445\u0440\u0430\u043d\u0438\u0442\u044c \u043a\u0430\u0440\u0442\u0438\u043d\u043a\u0443", None))
        self.code_button.setText(QCoreApplication.translate("MainWindow", u"\u0417\u0430\u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442", None))
        self.decode_button.setText(QCoreApplication.translate("MainWindow", u"\u0414\u0435\u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c \u0442\u0435\u043a\u0441\u0442", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"<html><head/><body><p><span style=\" font-size:11pt; color:#aa0000;\">\u0427\u0442\u043e \u0431\u0443\u0434\u0435\u043c \u0441\u0435\u0433\u043e\u0434\u043d\u044f \u043a\u043e\u0434\u0438\u0440\u043e\u0432\u0430\u0442\u044c?</span></p></body></html>", None))
        self.plainTextEdit.setPlaceholderText(QCoreApplication.translate("MainWindow", u"\u0412\u0432\u0435\u0434\u0438\u0442\u0435 \u0442\u0435\u043a\u0441\u0442...", None))
        self.pushButton.setText(QCoreApplication.translate("MainWindow", u"\u0417\u0430\u043a\u0440\u044b\u0442\u044c \u043e\u043a\u043d\u043e", None))
    # retranslateUi
    
class MainWindow(QMainWindow):

    serdechko = bytes((0b11100010, 0b10011101, 0b10100100))
    image = QImage()
    canUse = 0
    used = 0

    def __init__(self):
        super(MainWindow, self).__init__(None)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.plainTextEdit.textChanged.connect(self.msgChanged)
        self.ui.load_button.clicked.connect(self.loadImage)
        self.ui.save_button.clicked.connect(self.saveImage)
        self.ui.code_button.clicked.connect(self.encodeMsg)
        self.ui.decode_button.clicked.connect(self.decodeMsg)

    @Slot()
    def loadImage(self):
        path, _ = QFileDialog.getOpenFileName(self, "Open Image", "", "Допустимые форматы (*.png)")

        self.image.convertTo(QImage.Format_ARGB32)
        self.canUse = (self.image.width() * self.image.height() * 3) // 8 - len(self.serdechko) - 4
        if self.image.load(path):
            self.ui.label.setText("Изображение успешно загружено")
        else:
            self.ui.label.setText("Изображение не загружено")
            return

    @Slot()
    def saveImage(self):

        path, _ = QFileDialog.getSaveFileName(self, "Сохранить картинку", "", "Допустимые форматы (*.png)")

        if self.image.save(path, "PNG"):
            self.ui.label.setText("Изображение успешно сохранено")                                                      
            return
        else:
            self.ui.label.setText('Не удалось сохранить изображение')

    @Slot()
    def encodeMsg(self):

        self.used = len(self.ui.plainTextEdit.toPlainText())
        if self.canUse < self.used:
            self.ui.label.setText("Ошибка. Недостаточно места!")
            return
            
        byteArray = QByteArray()
        byteArray.push_back(self.ui.plainTextEdit.toPlainText().encode())
        for i in range(4):
            byteArray.push_front(bytes(((self.used >> i * 8) & 0xff,)))
        for i in range(len(MainWindow.serdechko) - 1, -1, -1):
            byteArray.push_front(bytes((MainWindow.serdechko[i],)))

        write_byte(self.image, byteArray, 0)

        self.ui.label.setText("Сообщение добавлено в картинку!")

    @Slot()
    def decodeMsg(self):

        header_size = len(self.serdechko) + 4
        byteArray = read_byte(self.image, 0, header_size)

        for i in range(0, len(self.serdechko)):
            if bytes((self.serdechko[i],)) != byteArray[i]:
                self.ui.label.setText("Сообщение не обнаружено")
                return

        msgSize = 0
        for i in range(len(self.serdechko), len(self.serdechko) + 4):
            msgSize = (msgSize << 8) + int.from_bytes(byteArray[i], "big")
        byteArray.clear()
        byteArray = read_byte(self.image, header_size, msgSize)

        self.ui.plainTextEdit.setText(bytes(byteArray).decode("utf-8"))
        self.ui.label.setText(f"Присутствует сообщение длиной {msgSize} байт.")

    @Slot()
    def msgChanged(self):
        if self.canUse < 0:
            return

        byte_array = QByteArray()
        byte_array.push_back(self.ui.plainTextEdit.toPlainText().encode())
        self.used = len(self.ui.plainTextEdit.toPlainText())

        if self.canUse < self.used:
            self.ui.label.setText(f"Размер сообщения превышен.")
        else:
            self.ui.label.setText(f"Ещё можно ввести: {self.canUse - self.used} байт.")







def write_bit(image: QImage, index, value) -> None:
    pxIndex = index // 3
    x = pxIndex % image.width()
    y = pxIndex // image.width()

    switch = index % 3
    if switch == 0:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x010000) | (value << 16))
    elif switch == 1:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x000100) | (value << 8))
    elif switch == 2:
        image.setPixel(x, y, (image.pixel(x, y) & ~0x000001) | value)

def write_byte(image: QImage, byteArray: QByteArray, begin) -> None:
    last = (begin + byteArray.size()) * 8
    for i in range(begin * 8, last):
        write_bit(image, i, (int.from_bytes(byteArray[i // 8], "big") >> (7 - i % 8)) & 1)

def read_bit(image: QImage, index) -> bool:
    pxIndex = index // 3
    x = pxIndex % image.width()
    y = pxIndex // image.width()

    switch = index % 3
    if switch == 0:
        return (image.pixel(x, y) >> 16) & 1
    elif switch == 1:
        return (image.pixel(x, y) >> 8) & 1
    elif switch == 2:
        return image.pixel(x, y) & 1
    else:
        raise Exception()

def read_byte(image: QImage, begin, length) -> QByteArray:
    byteArray = QByteArray()
    buffer = 0
    last = (begin + length) * 8

    for i in range(begin * 8, last):
        buffer = (buffer << 1) | read_bit(image, i)

        if i % 8 == 7:
            byteArray.push_back(bytes((buffer,)))
            buffer = 0

    return byteArray

    







if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
  
    window = MainWindow()
    window.show()
  
    sys.exit(app.exec())
