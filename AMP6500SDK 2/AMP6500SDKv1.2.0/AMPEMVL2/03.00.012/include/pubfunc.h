/*
 * pubfunc.h
 *
 *  Created on: Nov 17, 2010
 *      Author: neal
 */

#ifndef PUBFUNC_H_
#define PUBFUNC_H_

#ifdef __cplusplus
extern "C"
{
#endif

void auxBCDToLong(uint8_t *pStr,int cLen,uint32_t *lLng);
void auxLongToBCD(uint8_t *pStr,int cLen,uint32_t lLng);
void LongToStr(uint32_t ldat, uint8_t *str);
uint32_t asc2ulong(char *asc,int len);
void sTwoOne(char *two, int len,uint8_t *one);
void sOneTwo(uint8_t *One, int len, char *Two);
void bcd_to_asc(char *asc, uint8_t *bcd, int asc_len);
uint8_t ConvBcdAmount(uint8_t *bcdAmt, char *amount_ptr);
uint8_t HexToBinary(const char * pszHex, uint8_t * pBuff, uint32_t iBuffLen);
uint8_t HexToBinaryEx(const char * pszHex, uint32_t iHexLen, uint8_t * pBuff, uint32_t iBuffLen);
int CheckHexStr(const char * pszHex);

void BinaryToHex(const uint8_t * pBuff, char * pszHex, uint32_t iBinarySize);
void StepMsg(const char * pszMsg);
void FormatAmount(char * pszMsg, uint32_t uiAmount);


int  ActiveDeactiveSelect(const char * pszTitle, int Actived);
int  EnableDisableSelect(const char * pszTitle, int Enabled);
int  ItemSelect(const char * pszTitle, const char * Items[], int count, int defaultSelect);


extern int emv_get_tag(const void *tlv, int len, uint8_t *taglen);

void pan_mask( char * pan);

#ifdef __cplusplus
}
#endif


#endif /* PUBFUNC_H_ */
