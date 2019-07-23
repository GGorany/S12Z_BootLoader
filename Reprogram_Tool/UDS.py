

import sys
import udsoncan
import isotp
from can.interfaces.vector import VectorBus
from udsoncan.connections import PythonIsoTpConnection
from udsoncan.client import Client
import udsoncan.configs
import time
import threading


# Refer to isotp documentation for full details about parameters
isotp_params_Func = {
   'stmin': 0,                          # Will request the sender to wait 32ms between consecutive frame. 0-127ms or 100-900ns with values from 0xF1-0xF9
   'blocksize': 0,                       # Request the sender to send 8 consecutives frames before sending a new flow control message
   'wftmax': 0,                          # Number of wait frame allowed before triggering an error
   'll_data_length': 8,                  # Link layer (CAN layer) works with 8 byte payload (CAN 2.0)
   'tx_padding': 0x55,                   # Will pad all transmitted CAN messages with byte 0x00. None means no padding
   'rx_flowcontrol_timeout': 1000,       # Triggers a timeout if a flow control is awaited for more than 1000 milliseconds
   'rx_consecutive_frame_timeout': 1000, # Triggers a timeout if a consecutive frame is awaited for more than 1000 milliseconds
   'squash_stmin_requirement': False     # When sending, respect the stmin requirement of the receiver. If set to True, go as fast as possible.
}

# Refer to isotp documentation for full details about parameters
isotp_params_Phys = {
   'stmin': 0,                          # Will request the sender to wait 32ms between consecutive frame. 0-127ms or 100-900ns with values from 0xF1-0xF9
   'blocksize': 4,                       # Request the sender to send 8 consecutives frames before sending a new flow control message
   'wftmax': 0,                          # Number of wait frame allowed before triggering an error
   'll_data_length': 8,                  # Link layer (CAN layer) works with 8 byte payload (CAN 2.0)
   'tx_padding': 0x55,                   # Will pad all transmitted CAN messages with byte 0x00. None means no padding
   'rx_flowcontrol_timeout': 1000,       # Triggers a timeout if a flow control is awaited for more than 1000 milliseconds
   'rx_consecutive_frame_timeout': 1000, # Triggers a timeout if a consecutive frame is awaited for more than 1000 milliseconds
   'squash_stmin_requirement': False     # When sending, respect the stmin requirement of the receiver. If set to True, go as fast as possible.
}

config = dict(udsoncan.configs.default_client_config)
config['data_identifiers'] = {
    0xF189: udsoncan.AsciiCodec(7),       # Codec that read ASCII string. We must tell the length of the string
    0xF195: udsoncan.AsciiCodec(7)       # Codec that read ASCII string. We must tell the length of the string
    }
config['p2_timeout'] = 4

'''
request:  0x18DB33F1 (functional), 0x18DAxxF1 (physical)
response:                          0x18DAF1xx (physical)
'''


class UDS(object):

    def __init__(self, parent):
        self.parent = parent
        self.bus = None

        self.Repro_numTotal = 0
        self.Repro_num = 0
        self.Repro_completeflag = False
        self.statusText = ''

        self.Func_addr = None
        self.Func_stack = None
        self.Func_conn = None

        self.Phys_addr = None
        self.Phys_stack = None
        self.Phys_conn = None

        # Vector Bus
        try:
            self.bus = VectorBus(channel=0, app_name='SANY SJB Reprogram', bitrate=250000)  # Link Layer (CAN protocol)
        except:
            self.set_statusText(color='red', text='CAN Open fail. Check the vector Hardware Configuration.')
        else:
            udsoncan.setup_logging('logging.conf')
            self.set_statusText(color='green', text='CAN Open Success.')
            self.parent.canOpenSuccess()

    def set_statusText(self, color=None, text='Missing Message'):
        if color == 'red':
            tmptext = "<font color=red><b>"
        elif color == 'green':
            tmptext = "<font color=green><b>"
        elif color == 'blue':
            tmptext = "<font color=blue><b>"
        else:
            tmptext = "<font color=black><b>"
        tmptext += text
        self.statusText = tmptext + "</b></font>"

    def connect(self):
        try:
            self.Func_addr = isotp.Address(isotp.AddressingMode.Normal_29bits, txid=0x18DB33F1, rxid=0x18DBF133)
            self.Phys_addr = isotp.Address(isotp.AddressingMode.Normal_29bits, txid=0x18DA87F1, rxid=0x18DAF187)
            self.Func_stack = isotp.CanStack(bus=self.bus, address=self.Func_addr,
                                             params=isotp_params_Func)  # Network/Transport layer (IsoTP protocol)
            self.Phys_stack = isotp.CanStack(bus=self.bus, address=self.Phys_addr,
                                             params=isotp_params_Phys)  # Network/Transport layer (IsoTP protocol)
            self.Func_conn = PythonIsoTpConnection(self.Func_stack)  # interface between Application and Transport layer
            self.Phys_conn = PythonIsoTpConnection(self.Phys_stack)  # interface between Application and Transport layer
        except:
            self.set_statusText(color='red', text='ISOTP Connection fail.')
            if self.Func_conn.is_open():
                self.Func_conn.close()
            if self.Phys_conn.is_open():
                self.Phys_conn.close()
        else:
            self.set_statusText(color='green', text='ISOTP Connection Success.')

    def disconnect(self):
        self.set_statusText(color='green', text='ISOTP Disconnection Success.')
        if self.Func_conn.is_open():
            self.Func_conn.close()
        if self.Phys_conn.is_open():
            self.Phys_conn.close()

    def readAppVersion(self):
        with Client(self.Phys_conn, request_timeout=1, config=config) as client:
            client.logger.info('============================================================')
            client.logger.info('================= Read Application Version =================')
            client.logger.info('============================================================')
            try:
                response = client.read_data_by_identifier_first(0xF189)
            except:
                exc = sys.exc_info()[1]
                self.parent.lineEdit_AppVersion.setPalette(self.parent.palette_red)
                self.parent.lineEdit_AppVersion.setText(str(exc))
                self.set_statusText(color='red', text='Read Application Version - Fail.    Application may not exist.')
            else:
                self.parent.lineEdit_AppVersion.setPalette(self.parent.palette_blue)
                self.parent.lineEdit_AppVersion.setText(response)
                self.set_statusText(color='green', text='Read Application Version - Success.')

    def readBootVersion(self):
        with Client(self.Phys_conn, request_timeout=1, config=config) as client:
            client.logger.info('============================================================')
            client.logger.info('================= Read BootLoader Version ==================')
            client.logger.info('============================================================')
            try:
                response = client.read_data_by_identifier_first(0xF195)
            except:
                exc = sys.exc_info()[1]
                self.parent.lineEdit_BootVersion.setPalette(self.parent.palette_red)
                self.parent.lineEdit_BootVersion.setText(str(exc))
                self.set_statusText(color='red', text='Read BootLoader Version - Fail.')
            else:
                self.parent.lineEdit_BootVersion.setPalette(self.parent.palette_blue)
                self.parent.lineEdit_BootVersion.setText(response)
                self.set_statusText(color='green', text='Read BootLoader Version - Success.')

    def diagSessionControl(self, Reqtype=0, session=0, spr=False):
        if Reqtype == 0:    # Functional Request
            with Client(self.Func_conn, request_timeout=1, config=config) as client:
                try:
                    if spr == True:
                        with client.suppress_positive_response:
                            client.change_session(session)
                            time.sleep(0.1)
                    else:
                        client.change_session(session)
                except:
                    exc = sys.exc_info()[1]
                    self.set_statusText(color='red', text=str(exc))
                else:
                    self.set_statusText(color='green', text='Diagnostic session change - Success.')
        elif Reqtype == 1:    # Physical Request
            with Client(self.Phys_conn, request_timeout=1, config=config) as client:
                try:
                    if spr == True:
                        with client.suppress_positive_response:
                            client.change_session(session)
                            time.sleep(0.1)
                    else:
                        client.change_session(session)
                except:
                    exc = sys.exc_info()[1]
                    self.set_statusText(color='red', text=str(exc))
                else:
                    self.set_statusText(color='green', text='Diagnostic session change - Success.')
        else:
            self.set_statusText(color='red', text='Diagnostic session change - Fail.')

    def communicationControl(self, control_type=0):
        communication_type = udsoncan.CommunicationType(subnet=0, normal_msg=True, network_management_msg=False)

        with Client(self.Func_conn, request_timeout=1, config=config) as client:
            try:
                with client.suppress_positive_response:
                    client.communication_control(control_type, communication_type)
                    time.sleep(0.1)
            except:
                exc = sys.exc_info()[1]
                self.set_statusText(color='red', text=str(exc))
            else:
                self.set_statusText(color='green', text='Communication Control - Success.')

    def tester_Present(self, spr=False):
        with Client(self.Func_conn, request_timeout=1, config=config) as client:
            try:
                if spr == True:
                    with client.suppress_positive_response:
                        client.tester_present()
                        time.sleep(0.1)
                else:
                    client.tester_present()
            except:
                exc = sys.exc_info()[1]
                self.set_statusText(color='red', text=str(exc))
            else:
                pass

    def routineControl(self, rtid=0x0000, control_type=0x01, spr=False):
        # control_type = 1(start routine), 2(stop routine), 3(requestRoutineResult)
        with Client(self.Phys_conn, request_timeout=5, config=config) as client:
            client.logger.info('============================================================')
            client.logger.info('===================== Erase Application ====================')
            client.logger.info('============================================================')
            try:
                if spr == True:
                    with client.suppress_positive_response:
                        client.routine_control(rtid, control_type)
                        time.sleep(0.1)
                else:
                    client.routine_control(rtid, control_type)
            except:
                exc = sys.exc_info()[1]
                self.set_statusText(color='red', text=str(exc))
            else:
                if rtid == 0xFF00:
                    self.set_statusText(color='green', text='Routine Control - Erase Application - Success.')
                else:
                    self.set_statusText(color='green', text='Routine Control Send - Success.')

    def ecuReset(self, reset_type=0x01):
        # reset_type = 0x01(Hard Reset), 0x10(Reset to App), 0x20(Reset to BT)
        with Client(self.Phys_conn, request_timeout=2, config=config) as client:
            client.logger.info('============================================================')
            client.logger.info('========================= ECU Reset ========================')
            client.logger.info('============================================================')
            try:
                client.ecu_reset(reset_type)
            except:
                exc = sys.exc_info()[1]
                self.set_statusText(color='red', text=str(exc))
            else:
                if reset_type == 0x01:
                    text = "Reset ECU - Hard Reset."
                elif reset_type == 0x10:
                    text = "Reset ECU - Reset to Application."
                elif reset_type == 0x20:
                    text = "Reset ECU - Reset to BootLoader."
                else:
                    pass
                self.set_statusText(color='green', text=text)

    def runFlashData(self):
        self.Repro_numTotal = 0
        self.Repro_num = 0
        self.Repro_completeflag = False
        timeStart = time.time()
        for index in self.parent.srecs:
            if index.type == "S2":
                self.Repro_numTotal = self.Repro_numTotal + 1
        self.parent.progressBarDN.setMaximum(self.Repro_numTotal)

        with Client(self.parent.uds.Phys_conn, request_timeout=1, config=config) as client:
            client.logger.info('============================================================')
            client.logger.info('====================== Start Reprogram =====================')
            client.logger.info('============================================================')

            self.Repro_completeflag = True
            for index in self.parent.srecs:
                if index.type == "S2":
                    data = index.addr.to_bytes(4, byteorder='big') + index.data
                    try:
                        sequenceNum = self.Repro_num % 100
                        client.transfer_data(sequenceNum, data)
                    except:
                        exc = sys.exc_info()[1]
                        self.set_statusText(color='red', text=str(exc))
                        self.Repro_completeflag = False
                        print('... Exception FlashData Thread ...')
                        break
                    else:
                        self.Repro_num = self.Repro_num + 1
                        text = str(self.Repro_num) + "/" + str(self.Repro_numTotal) + " Data is sent."
                        self.set_statusText(color='green', text=text)
                        client.logger.info(text)

            if self.Repro_completeflag is True:
                text = "Flash is complete." + "(" + str(round((time.time() - timeStart), 3)) + " sec)"
                self.set_statusText(color='green', text=text)
            else:
                text = "Flash is not complete." + "(" + str(round((time.time() - timeStart), 3)) + " sec)"
                self.set_statusText(color='red', text=text)

            client.logger.info('============================================================')
            client.logger.info('======================= End Reprogram ======================')
            client.logger.info('============================================================')

        print('... End FlashData Thread ...')

