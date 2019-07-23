
# This Project is developed by DH.Kim

import os
import sys
import threading
import time
from SRecord import SRecord
from UDS import UDS
from PyQt5 import QtGui
from PyQt5.QtCore import *
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog
from UI.MainForm import Ui_MainWindow
from LogDisplay import LogDisplay


class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.mainform = Ui_MainWindow()
        self.setupUi(self)

        # Log Display
        self.logDlg = LogDisplay()

        # main window
        self.actionConnect.setVisible(True)
        self.actionDisConnect.setVisible(False)
        self.actionConnect.setDisabled(True)
        self.actionDisConnect.setDisabled(True)

        # interface connection
        self.actionConnect.triggered.connect(self.menuConnectClicked)
        self.actionDisConnect.triggered.connect(self.menuDisConnectClicked)

        # buttons
        self.btn_OpenLog.setText('Open Log Dialog')
        self.btn_ReadAppVer.clicked.connect(self.ReadAppVer)
        self.btn_ReadBootVer.clicked.connect(self.ReadBootVer)
        self.btn_GotoApp.clicked.connect(self.GotoApp)
        self.btn_GotoBoot.clicked.connect(self.GotoBoot)
        self.btn_Openfile.clicked.connect(self.Openfile)
        self.btn_OpenLog.clicked.connect(self.OpenLog)
        self.btn_Start.clicked.connect(self.StartProcess)
        self.btn_ReadAppVer.setDisabled(True)
        self.btn_ReadBootVer.setDisabled(True)
        self.btn_GotoApp.setDisabled(True)
        self.btn_GotoBoot.setDisabled(True)
        self.btn_Openfile.setDisabled(True)
        self.btn_OpenLog.setDisabled(True)
        self.btn_Start.setDisabled(True)

        # lineEdit Init
        self.lineEdit_AccessCode.setValidator(QtGui.QIntValidator(0, 10000))

        # init status
        self.label_Status.setText("<font color=red><b>" + "CAN Hardware is not connected." + "</b></font>")

        # S-Record Instance (file & linelist)
        self.srecfile = None
        self.srecs = []

        # palette Init
        self.palette_red = QtGui.QPalette()
        self.palette_red.setColor(QtGui.QPalette.Text, Qt.red)
        self.palette_darkgreen = QtGui.QPalette()
        self.palette_darkgreen.setColor(QtGui.QPalette.Text, Qt.darkGreen)
        self.palette_blue = QtGui.QPalette()
        self.palette_blue.setColor(QtGui.QPalette.Text, Qt.blue)

        # UDS Init
        self.uds = UDS(self)

        # Progress Bar
        self.progressBarDN.setValue(0)

        # thread - uds status display
        self.threadstatus = ThreadStatus(self.uds)
        self.threadstatus.change_value.connect(self.progressBarDN.setValue)
        self.threadstatus.change_status.connect(self.label_Status.setText)
        self.threadstatus.start()

        # Thread TP
        self.mThreadTP = threading.Thread(target=self.threadTP, name="threadTP")
        self.TP_Terminate = False

    def canOpenSuccess(self):
        self.actionConnect.setDisabled(False)
        self.actionDisConnect.setDisabled(False)

    def menuConnectClicked(self):
        self.actionConnect.setVisible(False)
        self.actionDisConnect.setVisible(True)

        if self.uds is None:
            self.uds = UDS(self)

        self.uds.connect()

        if self.threadstatus.isFinished():
            self.threadstatus = ThreadStatus(self.uds)
            self.threadstatus.change_value.connect(self.progressBarDN.setValue)
            self.threadstatus.change_status.connect(self.label_Status.setText)
            self.threadstatus.start()

        self.btn_ReadAppVer.setDisabled(False)
        self.btn_ReadBootVer.setDisabled(False)
        self.btn_GotoApp.setDisabled(False)
        self.btn_GotoBoot.setDisabled(False)
        self.btn_Openfile.setDisabled(False)
        self.btn_OpenLog.setDisabled(False)
        self.btn_Start.setDisabled(False)

    def menuDisConnectClicked(self):
        self.actionConnect.setVisible(True)
        self.actionDisConnect.setVisible(False)
        self.uds.disconnect()

        self.uds.bus.stop_all_periodic_tasks()
        self.uds.bus.shutdown()

        self.uds = None

        # thread - uds status display
        if self.threadstatus.isRunning():
            self.threadstatus.stop()

        self.btn_ReadAppVer.setDisabled(True)
        self.btn_ReadBootVer.setDisabled(True)
        self.btn_GotoApp.setDisabled(True)
        self.btn_GotoBoot.setDisabled(True)
        self.btn_Openfile.setDisabled(True)
        self.btn_OpenLog.setDisabled(True)
        self.btn_Start.setDisabled(True)

    def ReadAppVer(self):
        self.lineEdit_AppVersion.clear()
        mTh = threading.Thread(target=self.uds.readAppVersion, name="uds.readAppVersion")
        mTh.start()

    def ReadBootVer(self):
        self.lineEdit_BootVersion.clear()
        mTh = threading.Thread(target=self.uds.readBootVersion, name="uds.readBootVersion")
        mTh.start()

    def GotoApp(self):
        self.uds.diagSessionControl(Reqtype=0, session=0x03, spr=True)  # Functional / session Extended / No response
        self.uds.ecuReset(0x10)     # reset to App

    def GotoBoot(self):
        self.uds.diagSessionControl(Reqtype=0, session=0x03, spr=True)  # Functional / session Extended / No response
        self.uds.ecuReset(0x20)     # reset to BT

    def Openfile(self):
        self.srecs.clear()
        fname = QFileDialog.getOpenFileName(self, 'Open S19 file', "", "S19 Files(*.S19)")
        if fname[0]:
            try:
                self.srecfile = open(fname[0])
            except:
                exc = sys.exc_info()[1]     # file open fail
                self.lineEdit_S19FileLocation.setPalette(self.palette_red)
                self.lineEdit_S19FileLocation.setText(str(exc))
            else:
                temp = os.path.split(fname[0])
                self.lineEdit_S19FileLocation.setPalette(self.palette_darkgreen)
                self.lineEdit_S19FileLocation.setText(temp[1])
                for line in self.srecfile:
                    srec = SRecord()
                    result = srec.process(srecline=line)
                    if result is '':
                        self.srecs.append(srec)
                    else:
                        self.lineEdit_S19FileLocation.setPalette(self.palette_red)
                        self.lineEdit_S19FileLocation.setText(result + ". line_" + str(len(self.srecs)+1))
                        self.srecs.clear()
                        break
            finally:
                self.srecfile.close()

    def OpenLog(self):
        if self.logDlg.isHidden() is True:
            self.logDlg.show()
            self.btn_OpenLog.setText('Close Log Dialog')
        else:
            self.logDlg.hide()
            self.btn_OpenLog.setText('Open Log Dialog')

    def StartProcess(self):
        if not self.srecs:
            self.lineEdit_S19FileLocation.setPalette(self.palette_red)
            self.lineEdit_S19FileLocation.setText('!! S-record file is not opened. !!')
            return

        '''
        self.uds.diagSessionControl(Reqtype=0, session=0x03,
                                           spr=True)  # Functional / session Extended / No response
        self.uds.diagSessionControl(Reqtype=0, session=0x03, spr=True)  # Functional / session Extended / No response
        self.uds.communicationControl(3)  # disable Rx and Tx
        self.uds.diagSessionControl(Reqtype=1, session=0x02, spr=False)  # Physical / session Program / response
        self.mTPthreadTerminate = False
        self.mTPthread.start()
        '''

        mTh = threading.Thread(target=self.thStartProcess, name="thStartProcess")
        mTh.start()

    def thStartProcess(self):
        self.uds.routineControl(rtid=0xFF00, control_type=0x01, spr=False)  # erase memory / Start routine
        th = threading.Thread(target=self.uds.runFlashData, name="uds.runFlashData")
        print('... Start FlashData Thread ...')
        th.start()
        th.join()
        if self.uds.Repro_completeflag is True:
            self.GotoApp()

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        self.TP_Terminate = True    # Terminate TP
        try:
            self.threadstatus.stop()
            self.uds.disconnect()
            self.uds.bus.stop_all_periodic_tasks()
            self.uds.bus.shutdown()
        except:
            pass
        self.logDlg.closeWindow()

    def threadTP(self):
        while self.TP_Terminate is False:
            self.uds.tester_Present(spr=True)  # tester present
            time.sleep(3)


class ThreadStatus(QThread):
    change_value = pyqtSignal(int)
    change_status = pyqtSignal(str)

    def __init__(self, uds):
        QThread.__init__(self)
        self.mutex = QMutex()
        self.uds = uds
        self._stop = True

    def run(self):
        while self._stop:
            self.mutex.lock()
            time.sleep(0.1)
            self.change_value.emit(self.uds.Repro_num)
            self.change_status.emit(self.uds.statusText)
            self.mutex.unlock()

    def stop(self):
        self._stop = False


if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    app.exec_()

