// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpihsm.h
// PURPOSE....  Generic Platform Interface - High Security Module
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * gpiGetEMVCertificate
// * gpiGetEMVCRL
// * gpiInitializeHSM
// * gpiRsaComputation
// * gpiShaFinal
// * gpiShaInit
// * gpiGetRandomNumber
// * gpiShaUpdate
// * gpiGetChecksum
// * gpiSREDIsPKPresent
// * gpiSREDGetPKLength
// * gpiSREDRsaComputation
// * gpiSREDIsPKPANValid
// * gpiSREDSetCDOLOffset
// * gpiSREDGetCDOLOffset
// * gpiCLIPCheckPANInCertificate
// * gpiSECUREDPANMatched
// * gpiSECUREDPrefixPANMatched
// * gpiSECUREDShaInit
// * gpiSECUREDShaUpdateOnTLV
// * gpiSECUREDShaUpdateOnData
// * gpiSECUREDShaUpdateOnCertificateData
// * gpiSECUREDShaFinal
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPIHSM_H_
#define GPIHSM_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpierrors.h"
#include "gpi_agnos_framework_globals.h"

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================
#define MAX_EMV_KEY_LEN					248
#define MAX_KEY_FILE_NAME				500

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct { // EMV Public Key
		unsigned char	modulus[MAX_EMV_KEY_LEN];	// CA Key Modulus
		unsigned char	modulusLn;			// Length
		unsigned char	exponent[3];		// CA Public Exponent
		unsigned char	exponentLn;			// Length
}tEMVPubKey;
#ifdef PACKING
#pragma pack()
#endif


//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
/**
 * Initialize the High Security Module
 * @param CertificateFilesName Name of the certificate files
 * @param CertificatesRevocationListFileName Name of revocated certificates file
 * @param ExceptionFileName Name of the exception file
 */
DLLEXPORT tGPIError gpiInitializeHSM(
	const char* CertificateFilesName,
	const char* CertificatesRevocationListFileName,
	const char* ExceptionFileName
);

/**
 * Get EMV CA Certificate from RID and Index
 * @param rid RID (5 bytes)
 * @param index CA Certificate index (8F, 1 byte)
 * @param key CA Public Key
 */
DLLEXPORT tGPIError gpiGetEMVCertificate(
	unsigned char*		rid,
	unsigned char		index,
	tEMVPubKey*			key
);

/**
 * Get EMV Certificate Revocation from RID, Index and Serial Number
 * @param rid RID (5 bytes)
 * @param index CA Certificate index (8F, 1 byte)
 * @param sn Certificate Serial Number
 */
DLLEXPORT tGPIError gpiGetEMVCRL(
	unsigned char*		rid,
	unsigned char		index,
	unsigned char*		sn
);

/**
 * Find PAN from current Exception File List
 * @param pan (5A)
 * @param pan length
 */
DLLEXPORT tGPIError gpiFindPANfromEFL(
	unsigned char*		pan,
	unsigned char		panLen,
	unsigned char*		psn
);

/**
 * RSA Public Key Computation
 * @note usually to decrypt signature or encrypt data
 * @param modulus Key Modulus
 * @param modLn Length
 * @param exponent Public Exponent
 * @param expLn Length
 * @param input Data Input Block
 * @param output Data Output Block
 */
DLLEXPORT tGPIError gpiRsaComputation(
	unsigned char*	modulus,
	unsigned int	modLn,
	unsigned char*	exponent,
	unsigned int	expLn,
	unsigned char*	input,
	unsigned char*	output
);

/**
 * SHA Initialisation
 */
DLLEXPORT void gpiShaInit(void);

/**
 * SHA Intermediate Processing on a piece of Data
 * @param data Partial Mesage To Hash
 * @param dataLn Length
 */
DLLEXPORT void	gpiShaUpdate(
	unsigned char*  data,	// Partial Message To Hash
	int     dataLn			// Length
);

/**
 * Last SHA Processing
 * @param hash Hash Result (20 bytes)
 */
DLLEXPORT void gpiShaFinal(
	unsigned char*  hash	// Hash Result (20 bytes)
);

/**
 * Return a random number
 * @param random (out) Random number between 0 and limit
 * @param limit Max random value
 */
DLLEXPORT tGPIError gpiGetRandomNumber(
	unsigned int* random,
	unsigned int limit
);

/**
 * Return a checksum for the corresponding component identifier
 * @param component software component identifier
 * @param checksum stringified checksum
 */
DLLEXPORT tGPIError gpiGetChecksum(
	unsigned char component,
	char* checksum
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSREDIsPKPresent(
	unsigned short tagCertificate
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSREDGetPKLength(
	unsigned short tagCertificate,
	unsigned char* length
);

/**
 * RSA Public Key Computation from SRED module
 * @note usually to decrypt signature or encrypt data
 * @param modulus Key Modulus
 * @param modLn Length
 * @param exponent Public Exponent
 * @param expLn Length
 * @param tag certificate to process
 * @param output Data Output Block
 */
DLLEXPORT tGPIError gpiSREDRsaComputation (
	unsigned char*	modulus,
	unsigned int	modLn,
	unsigned char*	exponent,
	unsigned int	expLn,
	unsigned short	tagCertificate,
	unsigned char*	output
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSREDIsPKPANValid(
	unsigned short tagCertificate,
	unsigned char offset
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSREDSetCDOLOffset(
	unsigned char _56Length, unsigned char _56Offset,
	unsigned char _57Length, unsigned char _57Offset,
	unsigned char _5aLength, unsigned char _5aOffset);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSREDGetCDOLOffset(
	unsigned char* _56Length, unsigned char* _56Offset,
	unsigned char* _57Length, unsigned char* _57Offset,
	unsigned char* _5aLength, unsigned char* _5aOffset
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiCLIPCheckPANInCertificate(
	unsigned short tagCertificate,
	unsigned char offset,
	const unsigned char* certificate,
	unsigned char certificateLength
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSECUREDPANMatched(void);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiSECUREDPrefixPANMatched(
	unsigned short tagCertificate,
	unsigned char offset,
	const unsigned char* certificate,
	unsigned char certificateLength
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT void gpiSECUREDShaInit(void);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT void gpiSECUREDShaUpdateOnTLV(
	const unsigned char* tlv,
	unsigned char tlvLength
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT void gpiSECUREDShaUpdateOnCertificateData(
	unsigned short tagCertificate,
	unsigned char offset,
	unsigned char length
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT void gpiSECUREDShaUpdateOnData(
	const unsigned char* data,
	unsigned char length
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT void gpiSECUREDShaUpdateOnDOL(
	unsigned short tagDOL,
	const unsigned char* data,
	unsigned char length
);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT void gpiSECUREDShaFinal(
	unsigned char* hash
);

#ifdef __cplusplus
}
#endif

#endif /* GPIHSM_H_ */
