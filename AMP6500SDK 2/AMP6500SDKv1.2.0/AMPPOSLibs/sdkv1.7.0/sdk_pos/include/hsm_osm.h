


#ifndef __HSM_H__
#define __HSM_H__

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum
{
    HSM_OBJECT_DATA_TYPE_pem    = 0, //pem证书格式 
    HSM_OBJECT_DATA_TYPE_der    = 1, //der编码证书格式
    HSM_OBJECT_DATA_TYPE_p7b    = 2, //PKCS #7证书格式
    HSM_OBJECT_DATA_TYPE_pfx    = 3, //PKCS #12证书格式    
}HSM_OBJECT_DATA_TYPE;  //证书数据格式

typedef enum
{
    HSM_OBJECT_TYPE_private_key  = 0, //私钥证书
    HSM_OBJECT_TYPE_public_key   = 1, //公钥证书 
    HSM_OBJECT_TYPE_cert         = 2, //CERT证书     
}HSM_OBJECT_TYPE;  //证书类型

typedef struct
{
    unsigned char strID[32];        //   证书结构体ID号
    unsigned char strLabel[32];     //   证书名称 //证书别名
    unsigned char strPassword[32];  //   获取正式密码
    HSM_OBJECT_TYPE nObjectType;    //   证书类型标识
}HSM_OBJECT_PROPERTY;

typedef enum
{
    E_OK                = 0,    //  操作/返回成功
    E_DEVICENAME        = -1,   //  设备名称不存在
    E_IO                = -2,   //  底层I/O错误
    E_UNKOWN            = -10,  //  未知错误
    E_HAL_UNKOWN        = -100, //  未知错误
    E_HAL_ARG           = -101, //  输入参数错误
    E_HAL_IO            = -102, //  底层I/O错误
    E_OPEN_FAIL         = -103, //  打开设备失败
    E_DEV_NOT_OPEN      = -104, //  设备未打开
    E_INV_OBJ_DATA_TYPE = -105, //  证书类型错误
    E_INV_DEL_ALL_PIN   = -106, //  删除所有证书pin错误
    E_CERT_NOT_EXIST    = -107, //  证书不存在
    E_PRI_KEY_NOT_ALLOW = -108, //  load 接口不允许load私钥
}HSM_RET_CODE;


/////////////////////////////////////////////////////////////////////////////////////////////////////
/*
A.1.1.2.6.1　打开硬件证书管理与加密运算模块设备
函数    int hsm_osm_open();
描述    打开硬件证书管理与加密运算模块设备
参数    无
返回值  
1. 等于0，打开成功
2. 小于0，错误
*/
int hsm_osm_open(void);

/*
A.1.1.2.6.2　关闭硬件证书管理与加密运算模块设备
函数    int hsm_osm_close();
描述    关闭硬件证书管理与加密运算模块设备
参数    无
返回值  
1. 等于0，关闭成功
2. 小于0，错误
*/
int hsm_osm_close(void);


/*
A.1.1.2.6.3　保存安全证书
函数    int hsm_osm_save_object(HSM_OBJECT_PROPERTY* pObjectProperty, unsigned char* pObjectData, unsigned int nDataLength, HSM_OBJECT_DATA_TYPE nDataType);
描述    保存安全证书至硬件证书管理与加密运算模块设备
参数    
    pObjectProperty HSM_OBJECT_PROPERTY*    必选    证书属性。
    pObjectData unsigned char*
    必选    证书数据
    nDataLength unsigned int
    必选    证书数据长度
    nDataType   HSM_OBJECT_DATA_TYPE    必选    证书格式。    
返回值  
1. 等于0，保存成功。
2. 小于0，保存失败。
*/
int hsm_osm_save_object(HSM_OBJECT_PROPERTY* pObjectProperty, unsigned char* pObjectData, unsigned int nDataLength, HSM_OBJECT_DATA_TYPE nDataType);

/*
A.1.1.2.6.4　删除指定证书
函数    int hsm_osm_delete_object(HSM_OBJECT_PROPERTY* pObjectProperty, char* pPIN, unsigned int nPINLength);
描述    从硬件证书管理与加密运算模块设备中删除指定证书
参数    
    pObjectProperty HSM_OBJECT_PROPERTY*    必选    证书属性。
    pPIN    char*
    必选    PIN值。这个是什么鬼
    nPINLength  unsigned int    必选    PIN值长度。
返回值  
1. 等于0，删除成功
2. 小于0，错误
*/
int hsm_osm_delete_object(HSM_OBJECT_PROPERTY* pObjectProperty, char* pPIN, unsigned int nPINLength);


/*
A.1.1.2.6.4.1　删除所有证书
函数    int hsm_osm_delete_all(char* pPIN, unsigned int nPINLength);
描述    从硬件证书管理与加密运算模块中设备删除所有证书
参数    
    pPIN    char* 必选    保留的Pin值
    nPINLength  unsigned int    必选    PIN值长度
返回值  
1. 等于0，删除成功
2. 小于0，错误
*/
int hsm_osm_delete_all(char* pPIN, unsigned int nPINLength);

/*
A.1.1.2.6.5　查询证书数量
函数    int HSM_OSM_QUERY_OBJECT_COUNT(HSM_OBJECT_PROPERTY* pObjectProperty);
描述    从硬件证书管理与加密运算模块内查询证书数量
参数    pObjectProperty HSM_OBJECT_PROPERTY*    必选    证书属性。
返回值  
1. 小于0，查询失败。
2. 大于等于0，证书数量。
*/
int HSM_OSM_QUERY_OBJECT_COUNT(HSM_OBJECT_PROPERTY* pObjectProperty);


/*
A.1.1.2.6.6　读取证书
函数    int hsm_osm_load_object(unsigned int nIndex, HSM_OBJECT_PROPERTY* pObjectProperty, unsigned char* pDataBuffer, unsigned int nDataBufferLength, HSM_OBJECT_DATA_TYPE nDataType);
描述    从硬件证书管理与加密运算模块内读取证书
参数    
    nIndex  unsigned int    必选    证书索引号。
    pObjectProperty HSM_OBJECT_PROPERTY*    必选    证书属性。
    pDataBuffer unsigned char*  必选    证书数据。
    nDataBufferLength   unsigned int    必选    证书数据长度。
    nDataType   HSM_OBJECT_DATA_TYPE    必选    证书格式。
返回值  
1. 等于0，读取成功
2. 小于0，读取失败
*/
int hsm_osm_load_object(unsigned int nIndex, HSM_OBJECT_PROPERTY* pObjectProperty, unsigned char* pDataBuffer, unsigned int nDataBufferLength, HSM_OBJECT_DATA_TYPE nDataType);


/*
　注入私钥证书函数 
函数    int inject_private_key(HSM_OBJECT_PROPERTY* pObjectProperty);
描述    将私钥证书注入硬件证书管理与加密运算模块内
参数    
    pObjectData unsigned char*
    必选    证书数据
    nDataLength unsigned int
    必选    证书数据长度
    nDataType   HSM_OBJECT_DATA_TYPE    必选    证书格式。
返回值  
1. 小于0，查询失败。
2. 大于等于0，证书数量。
*/
int hsm_osm_inject_private_key(unsigned char* pObjectData, unsigned int nDataLength, HSM_OBJECT_DATA_TYPE nDataType);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//以下为新增两个接口，数据加密和解密，要求在C端完成

/*
　使用硬件模块对数据加密函数 
函数    如下;
描述    通过硬件证书管理与加密运算模块，对输入数据进行加密
参数  
    名称                数据类型         必/可选  说明
    algorithm           int             必选     加密算法类型
    aliasPrivateKey     char*           必选     私钥别名
    pDataBuffer         unsigned char*  必选     预加密数据的byte流
    nDataBufferLength   unsigned int    必选     预加密数据的byte流长度
    pDataBufferOut      unsigned char*  必选     数据加密后的byte流
    nDataBufferLengthOut unsigned int*  必选     数据加密后的byte流长度
返回值  
1. 小于0，加密失败。
2. 等于0，加密成功。
*/
int hsm_osm_encrypt(int algorithm, char* aliasPrivateKey, unsigned char* pDataBuffer, unsigned int nDataBufferLength,
    unsigned char* pDataBufferOut, unsigned int *pDataBufferLengthOut);


/*
描述    通过硬件证书管理与加密运算模块，对输入数据进行解密
参数  
    名称                数据类型         必/可选  说明
    algorithm           int             必选     解密算法类型
    aliasPrivateKey     char*           必选     私钥别名
    pDataBuffer         unsigned char*  必选     预解密数据的byte流
    nDataBufferLength   unsigned int    必选     预解密数据的byte流长度
    pDataBufferOut      unsigned char*  必选     数据解密后的byte流
    nDataBufferLengthOut  unsigned int* 必选     数据解密后的byte流长度
返回值  
1. 小于0，解密失败
2. 等于0，解密成功
*/
int hsm_osm_decrypt(int algorithm, char* aliasPrivateKey, unsigned char* pDataBuffer, unsigned int nDataBufferLength,
    unsigned char* pDataBufferOut, unsigned int *pDataBufferLengthOut);

/*
描述    让安全模块生成密钥对
参数  
    名称                数据类型         必/可选  说明    
    aliasPrivateKey     char*           必选     私钥别名
    algorithm           int             必选     解密算法类型
    keySize             int             必选     密钥长度，目前只支持2048位。
返回值  
1. 小于0，生成密钥对失败
2. 等于0，生成密钥对成功
*/
//这里生成密钥对的意思是: 生成一组密钥对(一个私钥+一个公钥，他们的别名都是一样的aliasPrivateKey)
int hsm_osm_generate_key_pair(char *aliasPrivateKey, int algorithm, int keySize);


/*
描述   删除终端私钥（密钥对）
参数  
    名称                数据类型         必/可选  说明    
    aliasPrivateKey     char*           必选     私钥别名
返回值  
1. 小于0，删除密钥对失败
2. 等于0，删除密钥对成功
*/
int hsm_osm_delete_key_pair(char *aliasPrivateKey);


/*
描述    让安全模块生成密钥对
参数  
    名称                数据类型         必/可选  说明    
    certType             int             必选     证书类型
    certAliasStr         char*           必选     证书别名存储空间， 返回格式"alias1|alias2|alias3|...|aliasn"  (以'|'作为分隔符)  
返回值  
1. 小于0，查询失败
2. 等于0或大于0，成功，返回查询到的数量，
*/
int hsm_osm_query_certificates(int certType, char *certAliasStr);


/*
　获取硬件加密接口的剩余或可用空闲空间
函数 如下;
描述 获取硬件加密接口的剩余或可用空闲空间
参数 无
返回值  
1. 小于0 获取失败
2. 其他(等于0或大于0)，硬件加密接口的剩余或可用空闲空间，空间大小单位为byte。
*/
int hsm_osm_get_free_space(void);


/*
描述 生成终端公钥的证书签名请求CSR。
参数  
    名称                数据类型         必/可选  说明    
    aliasPrivateKey     char*            必选     私钥别名
    CSRObjId            char*            必选     CSR中的主体名称等
    pCSRDataOut         unsigned char*  必选      PEM格式的CSR数据流
    pCSRDataLenOut      unsigned int* 必选        PEM格式的CSR数据流长度返回值  
1. 小于0，生成CSR失败
2. 等于0，生成CSR成功，
*/
int hsm_osm_generate_CSR(char* aliasPrivateKey, char *CSRObjId, unsigned char* pCSRDataOut, unsigned int *pCSRDataLenOut);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

