
import sys
from PyQt5.QtWidgets import QWidget
from PyQt5 import QtCore, QtGui
from UI.LogForm import Ui_LogForm


class Stream(QtCore.QObject):
    """Redirects console output to text widget."""
    newText = QtCore.pyqtSignal(str)

    def write(self, text):
        self.newText.emit(str(text))


class LogDisplay(QWidget, Ui_LogForm):

    def __init__(self, parent=None):
        super(LogDisplay, self).__init__()
        self.logForm = Ui_LogForm()
        self.setupUi(self)
        self.parent = parent
        self.setWindowFlag(QtCore.Qt.WindowMinimizeButtonHint, False)
        self.setWindowFlag(QtCore.Qt.WindowMaximizeButtonHint, False)
        self.setWindowFlag(QtCore.Qt.WindowCloseButtonHint, False)

        # TextEdit Color
        pal = QtGui.QPalette()
        pal.setColor(QtGui.QPalette.Base, QtGui.QColor(43, 43, 43))
        pal.setColor(QtGui.QPalette.Text, QtGui.QColor(169, 183, 198))
        self.textEdit_Log.setPalette(pal)

        # Custom output stream.
        sys.stdout = Stream(newText=self.onUpdateText)

    def onUpdateText(self, text):
        cursor = self.textEdit_Log.textCursor()
        cursor.movePosition(QtGui.QTextCursor.End)
        cursor.insertText(text)
        self.textEdit_Log.setTextCursor(cursor)
        self.textEdit_Log.ensureCursorVisible()

    def closeEvent(self, event):
        # Return stdout to defaults.
        sys.stdout = sys.__stdout__
        super().closeEvent(event)

    def closeWindow(self):
        self.close()

