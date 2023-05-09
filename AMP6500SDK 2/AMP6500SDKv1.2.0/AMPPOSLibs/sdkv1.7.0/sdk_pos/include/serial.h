
#ifndef __SERIAL__H__
#define __SERIAL__H__

#include "uart.h"

#define     PORT_RET_OK           0x00        //  �ɹ�
#define     PORT_RET_NOTEMPTY     0x01        //  ���ͻ��廹������
#define     PORT_RET_PORTERR      0x02        //  �߼����ںŷǷ�
#define     PORT_RET_NOTOPEN      0x03        //  ����δ��
#define     PORT_RET_BUSY         0x05        //  û����������Դ����
#define     PORT_RET_MODEM_INUSE  0xf0		    //  MODEMͨ������ϵͳռ�ã������PortNum=PORT_MODEM��
#define     PORT_RET_PARAERR      0xfe        //  ��Ч��ͨѶ����
#define     PORT_RET_TIMEOUT      0xff        //  ��ʱ

enum {
    PORT_COM1,
    PORT_EXT,
    PORT_MODEM,
    PORT_WNET,
    PORT_PINPAD,
    PORT_GPS,
    PORT_XX,
    PORT_6210LINK8210,
    PORT_6210LINK8210ACM,
    PORT_HID
};

int portOpen(int PortNum, const char *PortPara);
int portClose(int PortNum);
int portSends(int PortNum, const void *SendBuf, size_t SendLen);
int portRecv(int PortNum, uint8_t *RecvBuf, uint32_t TimeOutMs);
int portReset(int PortNum);
int portCheckRecvBuf(int PortNum);
int GetPortFd(int PortNum);

#endif
