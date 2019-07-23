
@echo on
python -m PyQt5.uic.pyuic -x MainForm.ui -o MainForm.py
python -m PyQt5.uic.pyuic -x LogForm.ui -o LogForm.py

pyrcc5 resources.qrc -o resources.py

pause
