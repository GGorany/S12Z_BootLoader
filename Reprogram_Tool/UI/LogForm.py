# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'LogForm.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_LogForm(object):
    def setupUi(self, LogForm):
        LogForm.setObjectName("LogForm")
        LogForm.resize(1000, 400)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/icon/logo_icon.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        LogForm.setWindowIcon(icon)
        self.gridLayout_3 = QtWidgets.QGridLayout(LogForm)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.gridLayout_2 = QtWidgets.QGridLayout()
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.textEdit_Log = QtWidgets.QTextEdit(LogForm)
        self.textEdit_Log.setReadOnly(True)
        self.textEdit_Log.setObjectName("textEdit_Log")
        self.gridLayout_2.addWidget(self.textEdit_Log, 0, 0, 1, 1)
        self.gridLayout_3.addLayout(self.gridLayout_2, 0, 0, 1, 1)

        self.retranslateUi(LogForm)
        QtCore.QMetaObject.connectSlotsByName(LogForm)

    def retranslateUi(self, LogForm):
        _translate = QtCore.QCoreApplication.translate
        LogForm.setWindowTitle(_translate("LogForm", "Log Display"))


import UI.resources


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    LogForm = QtWidgets.QWidget()
    ui = Ui_LogForm()
    ui.setupUi(LogForm)
    LogForm.show()
    sys.exit(app.exec_())
