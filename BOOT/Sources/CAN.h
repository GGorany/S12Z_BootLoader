

#ifndef CAN_H_
#define CAN_H_


void Init_UDS(void);
void TASK_UDS(void);

void RXMESSAGE(void);


// TA (Target Address) : 
// SA (Source Address) :
// Functional Address type : 0x18DBXXYY (With XX is TA and YY is SA)
// Physical Address type : 0x18DAXXYY (With XX is TA and YY is SA)

// TA (target addresse) : 1 byte ( 0x00 - 0xFF )
// SA (source addresse) : 1 byte ( 0x00 - 0xFF ):
// TA_type (target adresse type) : physical / functional
// If TA_type is physical , TA is the adresse of one ECU, then only this ECU may responds
// If TA_type is functional, TA represent a functional service (example 0x33 : OBD system). Then all ECU that implements this service may responds.

// There is some TA and SA values reserved :

// 0x00 - 0x07 : physical addresse of ECUs 0 - 7
// 0x33 : functional addresse for ECUs OBD systems
// 0xF1 : physical addresse of external test equipement

// SJB's TA : 0x87

/* 
ISO 15765-4 defines the Scanner_request, ECU_response CAN IDs:
29-bit:
request: 0x18DB33F1 (functional), 0x18DAxxF1 (physical)
response: 0x18DAF1xx (physical)
where: xx=ECU_number
11-bit:
request: 0x7DF (functional), 0x7Ex (physical)
response: 0x7Ey (functional)
where: y=x+8
*/


#define FuncReq_ID      0x18DB33F1      // 0x7DF

#define PhysReq_ID      0x18DA87F1      // 0x7E0
#define PhysResp_ID     0x18DAF187      // 0x7E8



#endif /* CAN_H_ */
