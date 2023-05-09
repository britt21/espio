
#ifndef AMPCRYPTO_H_
#define AMPCRYPTO_H_

/***************************************************************************
 * 
 * Copyright (C) 2015 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		AMPCrypto.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/24/2015
**************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
*	BASE 64
**************************************************************************/

	/*
	* Encode Base64 Block
	* 	NOTE: Size of outbuf must be atleast size(inbuf)*1.33
	* 	On encoding every three bytes (or parthere of) gets converted to 4bytes.
	* 	For example 30bytes (a multiple of 3) gets convereted to 40bytes, while 31bytes takes 44bytes
	*/
	void Base64Encode( const unsigned char *	pchInBuf,
						unsigned char * 		pchOutBuf,
						short					shInSize,
						short					shOutMaxSize,
						short * 				shOutSize);

	/*
	* Decode Base64 Block
	*/
	void Base64Decode(const unsigned char *pchInBuf,
						unsigned char * 		pchOutBuf,
						short					shInSize,
						short					shOutMaxSize,
						short * 				shOutSize);


	/*
	* Compute size of block after encoding
	*/
	int Base64ComputeEncodedSize(const unsigned char *	pchInBuf,
									short					shInSize);

/***************************************************************************
*	RSA
**************************************************************************/

	typedef enum {
		RSA_PAD_PKCS1           =1,
		RSA_PAD_SSLV23          =2,
		RSA_PAD_NONE            =3,
		RSA_PAD_PKCS1_OAEP      =4,
		RSA_PAD_X931            =5,
		RSA_PAD_PKCS1_PSS       =6,
	} RsaPadType;

	//! Reads a Rsa Public Pem Key file and assigns its keys
	int RsaAssignPublicKey(const char* pemkeyfile_);

	//! Reads a Rsa Private Pem Key file and assigns its keys
	int RsaAssignPrivateKey(const char* pemkeyfile_, const char* passphrase = NULL /* max 32 len */);

	//! Encrypt using Public key. If success returns the encrypted size
	int RsaPublicEncrypt(unsigned char* input_plaintext, int input_size, 
		unsigned char* output_ciphertext, RsaPadType padding);

	//! Decrypt using Private key. If success returns the decrypted size
	int RsaPrivateDecrypt(unsigned char* input_ciphertext, int input_size, 
		unsigned char* output_plaintext, RsaPadType padding);

	//! Sign a stream of data using the Private key and put it into buffer. Return the sign buff size if success
	int EvpPrivateSign(unsigned char* input_buffer, int input_size, 
		unsigned char* output_signbuff);

	//! Verify a data and its signature using the public key. Returns AMP_SUCCESS if verified successfully
	int EvpPublicVerifySign(unsigned char* input_databuffer, int input_datasize, 
		unsigned char* input_signbuffer, int input_signsize);


/***************************************************************************
*	TRIPLE DES
**************************************************************************/

	typedef enum {
		SINGLE_LEN = 8,
		DOUBLE_LEN = 16, 
		TRIPLE_LEN = 24, 
	} KeyLength;

	typedef enum {
		CBC,
		EBC, 
	} ChainMode;

	//! Encrypt
	int TDES_Encrypt(unsigned char* hexWorkingKey, KeyLength KeyLen, unsigned char hexInitVector[8], ChainMode ChainMod, 
			unsigned char* in_hexClear, int in_SizeClear, unsigned char* out_hexCiphered);
	
	//! Decrypt
	int TDES_Decrypt(unsigned char* hexWorkingKey, KeyLength KeyLen, unsigned char hexInitVector[8], ChainMode ChainMod, 
			unsigned char* in_hexCiphered, int in_SizeCiphered, unsigned char* out_hexClear);


/***************************************************************************
*	KCV
**************************************************************************/

	//! Calculate the KCV of a Triple DES Key
	int CalculateKCV(unsigned char* hexWorkingKey, KeyLength KeyLen, unsigned char KCVOut[3]);


/***************************************************************************
*	PEM Ceritifcate
**************************************************************************/

	//! Verify a Pem Certificate (cert_file) from a CA (ca_bundle)
	int VerifyPemCertificate(const char* ca_bundlestr, const char* cert_filestr);

	//! Extract public key from a Certificate File
	int ExtractPubKeyFromPemCert(const char* cert_filestr, const char* pubkey_filestr) ;

	//! Get the Validity of a Certificate File
	int GetPemCertValidity(const char* cert_filestr, char* NotBefore, char* NotAfter);

/***************************************************************************
*	Message Digest - HASH
**************************************************************************/

	//! Calculate the MD5 Checksum of a given buffer, output is a 16 byte hash value in bin hex format
	void MD5(const unsigned char* DataBuffer, int DataLen, unsigned char* HashOut);


#ifdef __cplusplus
}
#endif

#endif /* AMPCRYPTO_H_ */

