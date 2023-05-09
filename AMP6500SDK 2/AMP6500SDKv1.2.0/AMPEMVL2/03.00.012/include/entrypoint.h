// NAME.......  entrypoint.h
// PURPOSE....  Standard interface to manage payment transactions. This entry point is an extension of EMVCo books A and B.
//				It supports contactless processing.
//				This component implements no business rules; it is only a mean to map selected AID and combinations
//				to payment application that have been declared using a standard interface (see AFS details).
//				This component uses explicit dynamic library loading or static linking depending on constraints.
//
//				For contact transactions: DEPRECATED since Agnos framework 3.2
//
//				For contactless transactions: performance is an issue. Agnos entry point deals with many mechanisms to frame a transaction
//				in the tariffs required by payment networks. Multiple sessions are opened at preprocessing time (one for each combination
//				that is supported). Application selection is performed at this point of architecture. So, context setup is the
//				entry point's responsibility before initiating payment processing.
//				Globally, Agnos EP is responsible for:
//						- performing pre-processing
//						- discovering and selecting a contactless application that is supported by both the card and the reader
//						- activation of the appropriate kernel
//						- handling of outcomes returned by the kernel, including passing selected Outcomes to the reader
//
// PROJECT....  AGNOSEP
// REFERENCES.	--
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//


#ifndef ENTRYPOINT_H_
#define ENTRYPOINT_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- AgnosMW Headers ----
#include "paymentMW.h"
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"


//---------------------------------------------------------
//            Definitions
//---------------------------------------------------------
typedef tPaymentError (*ApplicationSelectionMethod)(tADFList *mutualList,tByte *MLIndex, tBoolean CL);

//---------------------------------------------------------
//            Public Primitives
//---------------------------------------------------------

//---------------------------------------------------------
//            enpSetCtlsAppFile()
//---------------------------------------------------------
//  Set the fine name that contains list of contactless application to be loaded
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetCtlsAppFile(const char *szFile);

//---------------------------------------------------------
//            enpConnectPaymentServices()
//---------------------------------------------------------
//  Register any services exporting payment services recognized by Agnos framework (AgnosService)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpConnectPaymentServices(const tString path);

//---------------------------------------------------------
//            enpDisconnectPaymentServices()
//---------------------------------------------------------
//  Unregister services exporting payment services recognized by Agnos framework (AgnosService)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpDisconnectPaymentServices(void);

//---------------------------------------------------------
//            enpInitialize()
//---------------------------------------------------------
//  Initialize Agnos entry point component and perform preprocessing if autorun = bTRUE
//	Other parameters are required if autorun = bTRUE. Else, may be NULL.
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpInitialize(
	tString		readerName,
	tString		pinpadName,
	tBoolean	signal,
	tBoolean	fallbackOnAID,	// DEPRECATED
	tBoolean	entryPoint,		// DEPRECATED
	tPaymentContext 	*payment //In: may be NULL is not autorun (contactless mechanism)
);

//---------------------------------------------------------
//            enpSetLegacyZIPStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following ZIP specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyZIPStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetLegacyPayPassStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following PayPass specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyPayPassStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetLegacyAMEXStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following AMEX specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyAMEXStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetPPSEJCBStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following JCB specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyJCBStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetPPSECUPStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following CUP specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyCUPStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetPPSEDPASStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following DPAS specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyDPASStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetPPSEVISAStatus()
//---------------------------------------------------------
//  Initialize Agnos entry point to manage PPSE select following VISA specifications
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetLegacyVISAStatus(tBoolean status);

//---------------------------------------------------------
//            enpSetApplicationSelectionMethod()
//---------------------------------------------------------
//  Initialize internal method used for final AID selection (once mutual list has been calculated and before actual final selection)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSetApplicationSelectionMethod(const ApplicationSelectionMethod method);

//---------------------------------------------------------
//            enpPSESelectionPerformed()
//---------------------------------------------------------
//  Used for contact processing, return bTRUE if PSE selection was performed
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean enpPSESelectionPerformed(void);

//---------------------------------------------------------
//            enpGetPPSEFCI()
//---------------------------------------------------------
//  Return a reference to PPSE FCI fetch during a contactless transaction
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tPSE* enpGetPPSEFCI(void);

//---------------------------------------------------------
//            enpAreAllCLAppplicationsNotAllowed()
//---------------------------------------------------------
//  Used for contactless processing, return bTRUE if no CL applications allowed
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tBoolean enpAreAllCLAppplicationsNotAllowed(void);

//---------------------------------------------------------
//            enpResetAreAllCLAppplicationsNotAllowed()
//---------------------------------------------------------
//  Return gAllCLApplicationNotAllowed to bFALSE
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpResetAreAllCLAppplicationsNotAllowed(void);

//---------------------------------------------------------
//            enpGetLastCardDetectionStatus()
//---------------------------------------------------------
//  Return the last error raised by low level at polling time (contactless) or power on time (contact)
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT tGPIError enpGetLastCardDetectionStatus(void);

//---------------------------------------------------------
//            enpSkipPollingOnNextStartB()
//---------------------------------------------------------
//  Skip polling on next enpExecutePaymentTransaction call
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpSkipPollingOnNextStartB(tGPIError detectedStatus);

//---------------------------------------------------------
//            enpReleasePaymentServices()
//---------------------------------------------------------
//  Get information from services. Available Only in sdk mode to fetch internal states
//
//  Visibility: Public
//  Hypothesis: --
//  Reference: --
//
DLLEXPORT void enpReleasePaymentServices(const tBoolean sdk);

//---------------------------------------------------------
//            enpExecutePaymentTransaction()
//---------------------------------------------------------
//  Single entry point for payment processing. Call this primitive to trig a contactless payment
//	See documentation for data structures management
//
//
//  Visibility: Public
//  Reference: --
//
DLLEXPORT void enpExecutePaymentTransaction (
	tStartingPoint 		sp,
	tPaymentContext		*payment,
	tOutComeParameter	*outcome
);

#ifdef __cplusplus
}
#endif

#endif /* ENTRYPOINT_H_ */
