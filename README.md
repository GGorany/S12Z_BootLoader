# S12Z_BootLoader
NXP S12Z - CAN Flash BootLoader

###  NXP S12Z MCU 의 CAN Flash BootLoader 소스코드 입니다.

VLG-MC9S12ZVC development 보드에서 테스트되었습니다.  
이 BootLoader 는 총 3개의 프로젝트로 나뉘어 있습니다.  
  
./BOOT => CAN BootLoader 입니다.  
./APP => 테트트용 Application 입니다.  
./Reprogram_Tool => 파이썬으로 작성된 UDS CAN Reprogram Tool 입니다.  


###  메모리 영역 나누기

| 영역 | 메모리 주소 | 메모리 크기 | 설명 |
|---|:---:|---:|---:|
|APP + BOOT 공통 영역|0x001000|0x1000|RAM|
|APP + BOOT 공통 영역|0x100000|0x400|EEPROM|
|APP 영역|0xFF0000|0x10|비워둠|
|   |0xFF0010|0x1EC|Interrupt Vector Table (APP)|
|   |0xFF01FC|0x4|비워둠|
|   |0xFF0200|0xBE00|실제 Application 이 위치함.|
|BOOT 영역|0xFFC000|0x3E00|실제 BootLoader 가 위치함.|
|   |0xFFFE00|0x10|Memory allow setting|
|   |0xFFFE10|0x1EC|Interrupt Vector Table (BOOT)|
|   |0xFFFFFC|0x4|Reset Vector|


###  추가 설명 및 참고 자료 링크

편집과 컴파일 - NXP CodeWarrior 11.0  
Processor Expert 사용.  
  
BootLoader 설계와 MCU 구조 - NXP문서 AN12086.  
  
UDS + ISOTP 프로토콜 스택 - https://github.com/jiangjie87481/mcu_uds_protol  
  
PC-APP 리프로그래머 -  
python-udsoncan https://github.com/pylessard/python-udsoncan  
python-isotp https://github.com/pylessard/python-can-isotp  
python-can https://github.com/hardbyte/python-can  
  
리프로그램 절차 - 현대 자동차 UDS 스펙을 간소화.
