
#ifndef __VENDOR_H__
#define __VENDOR_H__

#include <linux/ioctl.h>

enum VENDOR_ID {
	VENDOR_ID_UPDATE = 0,
	VENDOR_ID_SN_CID,	
	VENDOR_ID_HARDWARE,	
	VENDOR_ID_LOGO,
	VENDOR_ID_MAX,
};

enum ENCRYPT {
	DISABLE = 0,
	DES_ENCODE,
};

struct vendor_t {
	enum VENDOR_ID id;
	enum ENCRYPT encrypt;
	
	uint32_t  len;
	uint8_t 	*data;
} __attribute__ ((packed));

#define VENDOR_IOC_MAGIC		'v'

#define VENDOR_READ	            _IOR(VENDOR_IOC_MAGIC,	1, struct vendor_t )
#define VENDOR_WRITE	        _IOW(VENDOR_IOC_MAGIC,	2, struct vendor_t )
#define VENDOR_FILE_READ	    _IOR(VENDOR_IOC_MAGIC,	3, struct vendor_t )
#define VENDOR_FILE_WRITE	    _IOW(VENDOR_IOC_MAGIC,	4, struct vendor_t )


#define COM_LEN       			(4 + 4 + 2 +8 + 4)// 1bype ID 1 bype cptyto,4bybe len,4bybe crc,8bype for reserve 4bybe for end
#define FILENAMEMAXLEN          256


extern int vendor_open(const char *filename, int flags, umode_t mode);
extern int vendor_close(int fd);

#if 0
extern int vendor_read(int fd, enum VENDOR_ID id, uint8_t *data, int len);
extern int vendor_write(int fd, enum VENDOR_ID id, enum ENCRYPT crypt, uint8_t *data, int len);
#endif

extern int vendor_read(int fd, char *buf, int len);
extern int vendor_write(int fd, const char *data, int len);

extern int vendor_file_read(int fd, enum VENDOR_ID id, const char *filename);
extern int vendor_file_write(int fd, enum VENDOR_ID id, enum ENCRYPT crypt, const char *filename);

#endif 

