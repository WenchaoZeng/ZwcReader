/**
 * @addtogroup FPDFSECURITY
 * Header file for the security module
 * @{
 */

 /** (C) 2011 Foxit Corporation. All Rights Reserved.
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
 * Functions in this header file, require "security" module to be enabled in your SDK license.
 * \file
 * \author	Foxit Corporation
 * \brief	Header file for the security module - encrypt, decrypt and remove encryption from existing PDF documents.
 * \note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please
 *			request for enabling security module explicitly.
 * \version 3.1
*/



#ifndef _FPDFSECURITY_H_
#define _FPDFSECURITY_H_

#ifndef _FPDFVIEW_H_
#include "fpdfview.h"
#endif

#ifdef _WIN32
/** On Windows system, functions are exported in a DLL */
#define DLLEXPORT __declspec( dllexport )
#define STDCALL __stdcall
#define CDECL   _cdecl
#else
#define DLLEXPORT
#define STDCALL
#define CDECL
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef void* FPDF_DECRYPT_OUTPUT;

/** 
* @name PDF document permissions, according to PDF Reference, Table 3.20
*@{
*/
/** @brief bit 3. Print the document */
#define FPDF_PERM_PRINT				0x0004			 
/** @brief bit 4. Modify the contents of the document by operations other than those controlled by bits 6, 9, and 11. */
#define FPDF_PERM_MODIFY			0x0008			 
/** @brief bit 5. Copy or otherwise extract text and graphics from the document by operations other than that controlled by bit 10.*/
#define FPDF_PERM_EXTRACT			0x0010			 
/** @brief bit 6. Add or modify text annotations, fill in interactive form fields.If bit 4 is also set, create or modify interactive form fields */
#define FPDF_PERM_ANNOT_FORM		0x0020			 
/** @brief bit 9. Fill in existing interactive form fields (including signature fields), even if bit 6 is clear. */
#define FPDF_PERM_FILL_FORM			0x0100			 
/** @brief bit 10. Extract text and graphics */
#define FPDF_PERM_EXTRACT_ACCESS	0x0200			 
/** @brief bit 11. Assemble the document, even if bit 4 is clear.*/
#define FPDF_PERM_ASSEMBLE			0x0400			 
/** @brief bit 12. Print the document to a representation from which a faithful digital copy of the PDF content could be generated.*/
#define FPDF_PERM_PRINT_HIGH		0x0800			  
/**@}*/	

#define FPDFCIPHER_NONE	0
#define FPDFCIPHER_RC4	1
#define FPDFCIPHER_AES	2

/** 
* @brief This structure holds a number of interfaces allowing application to use customized
*		 security handlers. A security handler is responsible for decrypting data and enforce 
*	     document permissions.
*/
/**@{*/
struct FPDF_SECURITY_HANDLER
{
	/**
	* SDK calls this interface to initialize the custom handler.
	* @retval	A pointer to the internal data structure of the custom handler, NULL for error.
	*			This pointer is supplied when SDK calls all other interfaces.
	*/
	void*	(CDECL *CreateHandler)();

	/**
	* Get permission settings of the document.
	* @param[in] handler	-	Internal handler pointer, returned by CreateHandler interface.
	* @param[in] permission -	The original permission settings of the document.
	* @retval	A combination of permission flags defined above (FPDFPERM_xxx constants).
	*
	*/
	unsigned long	(CDECL *GetPermissions)(void* handler,unsigned long permission);
	
	/**
	* Setup a decryption filter, for decrypting a data stream.
	* @param[in] handler	-	Internal handler pointer, returned by CreateHandler interface.
	* @param[in] objnum		-	PDF object number for the object we are decrypting.
	* @param[in] version	-	PDF version number for the object we are decrypting.
	* @retval	Implementation should return a pointer to internal structure of the created filter.
	*			Return NULL for failure.
	*/
	void*	(CDECL *CreateFilter)(void* handler, int objnum, int version);
	
	/**
	* Input encrypted data to the filter.
	* @param[in] filter		-	Internal filter pointer, returned by CreateFilter interface
	* @param[in] output		-	An output buffer handle supplied by SDK.
	*							Can be used when calling FPDF_OutputDecrypted to output decrypted data.
	* @param[in] src_data	-	Source (encrypted) data
	* @param[in] src_len	-	Length (number of bytes) of the source data
	* @retval	Non-zero for success, 0 for failure.
	* @note		Implementation of this interface should be prepared to be called several times,
	*			for the same data stream to be decrypted. Each time, SDK supplies part of the source
	*			data. Whenever the implementation is ready to output some decrypted data, it should
	*			do so by calling FPDF_OutputDecrypted function.
	*/
	int		(CDECL *FilterInput)(void* filter, FPDF_DECRYPT_OUTPUT output, FPDF_BYTESTRING src_data, int src_len);

	/**
	* Finish a decrypt filter.
	* @param[in] filter	-	Internal filter pointer, returned by CreateFilter interface
	* @param[in] output	-	An output buffer handle supplied by SDK.
	*						Can be used when calling FPDF_OutputDecrypted to output decrypted data.
	* @retval	Non-zero for success, 0 for failure.
	* @note		FinishFilter implementation can also call FPDF_OutputDecrypted function to output 
	*			any left-over decrypted data.
	*			It's also OK for the filter implementation to cache all the input data in FilterInput
	*			interface, and decrypt the whole data stream when FinishFilter is called. 
	*			If an internal filter structure is created during CreateFilter interface, then this is
	*			the time to free that structure and any associated resources.
	*/
	int		(CDECL *FinishFilter)(void* filter, FPDF_DECRYPT_OUTPUT output);

	/**
	*Finish the custom security handler.
	* @param[in] handler	-	Internal handler pointer, returned by CreateHandler interface
	* @note		It's time to free the internal handler structure and all associated resources.
	*/
	void	(CDECL *FinishHandler)(void* handler);
	
	/**
	* Get encryption information including standard algorithm and key. SDK will call the function twice,  
	* first to receive the required length of the buffer, and second to receive the buffer of key content.
	* @param[in]		handler		-	Internal handler pointer, returned by CreateHandler interface
	* @param[in]	    cipher		-	Receives cipher identifier (FPDFCIPHER_NONE, FPDFCIPHER_RC4 or FPDFCIPHER_AES).
	* @param[in]		buffer		-	Pointer to a key.If it is NULL, then "keylen" should received the required length of the buffer.
	* @param[in]		keylen		-	Length (number of bytes) of the buffer.
	* @note		As long as one of CreateFilter,FilterInput and FinishFilte is set to NULL, 
	*			we think users are using standard encryption for encryption and decryption.
	*			The GetCryptInfo method must be set.
	*/
	FPDF_BOOL	(CDECL *GetCryptInfo)(void* handler,int* cipher,unsigned char * buffer, int*  keylen);

	 /**
	 * Get encrypted data size for a source data block.
	 * The returned size should equal to or be larger than the final encrypted data block.
	 * @param[in] handler	-	Internal handler pointer, returned by CreateHandler interface.
	 * @param[in] objnum	-	PDF object number for the object we are encrypting.
	 * @param[in] version	-	PDF version number for the object we are encrypting.
	 * @param[in] src_buf	-	The source data block.
	 * @param[in] src_size	-	The size in bytes of the source data.
	 * @retval Return The encrypted data size. It should equal to or be larger than the final encrypted data block.
	 *
	 */
	 FPDF_DWORD (CDECL *EncryptGetSize)(void* handler,int objnum, int version, unsigned char* src_buf, FPDF_DWORD src_size);

	 /**
	 * Do the encryption process.
	 * Final encrypted data block should be output in the "dest_size" parameter.
	 * @param[in] handler	-	Internal handler pointer, returned by CreateHandler interface
	 * @param[in] objnum	-	PDF object number for the object we are encrypting.
	 * @param[in] version	-	PDF version number for the object we are encrypting.
	 * @param[in] src_buf	-	The source data block.
	 * @param[in] src_size	-	The size in bytes of the source data.
	 * @param[in] dest_buf	-	It receives the encrypted data.
	 * @param[in] dest_size	-	It receives the size in bytes of the encrypted data.
	 * @retval Return True means success, otherwise failure.
	 *
	 */
	 FPDF_BOOL	(CDECL *EncryptContent)(void* handler,int objnum, int version, unsigned char* src_buf, FPDF_DWORD src_size,
							unsigned char* dest_buf, FPDF_DWORD* dest_size);

};
/**@}*/

/**
* Register a PDF security handler with Foxit PDF SDK, enabling access to a PDF document
* protected by non-standard security handler.
* @param[in] name		-	Name of the handler.
* @param[in] pHandler	-	Pointer	to a structure containing callback functions for the handler.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_RegisterSecurityHandler(FPDF_BYTESTRING handler_name, 
												struct FPDF_SECURITY_HANDLER* pHandler);


/**
* Destroy a PDF security handler with Foxit PDF SDK.
* @param[in] name		-	Name of the handler.
* @param[in] pHandler	-	Pointer	to a structure containing callback functions for the handler.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_DestroySecurityHandler(FPDF_BYTESTRING handler_name, 
												struct FPDF_SECURITY_HANDLER* pHandler);


/**
* Output data decrypted by a custom security handler
* @param[out] output	-	Handler to the output buffer.
* @param[in]  data		-	Pointer to decrypted data.
* @param[in]  len		-	Number of bytes for the decrypted data.
* @retval	TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_OutputDecrypted(FPDF_DECRYPT_OUTPUT output, FPDF_BYTESTRING data, int len);

/**
* Encrypt the PDF in custom way,the PDF document will be protected by no-standard security handler.
* @param[in]  document			-	Handler to the document.
* @param[in]  handler_name		-	The name of the handler.
* @param[in]  pHandler			-	Pointer	to a structure containing callback functions for the handler.
* @param[in]  fileWrite			-	A pointer to a custom file write structure.
* @retval	True if encrypt successfully, else False.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_CustomEncrypt(FPDF_DOCUMENT document, FPDF_STRING handler_name, FPDF_SECURITY_HANDLER* pHandler,FPDF_FILEWRITE* fileWrite);

/**
* Remove all the security setting of the PDF document, the output PDF will be decrypted.
* @param[in]  document		-   Handler to the document.
* @param[in]  fileWrite		-	A pointer to a custom file write structure.
* @retval	True if successfully remove the security, else False.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_RemoveSecurity(FPDF_DOCUMENT document, FPDF_FILEWRITE* fileWrite);

/**
* Get level of password
* @param[in]  document	-	Document handle.
* @retval     0 for no password, 1 for user level password, 2 for owner level password.
*/
DLLEXPORT int STDCALL FPDF_GetPasswordLevel(FPDF_DOCUMENT doc);

#ifdef __cplusplus
};
#endif

#endif	
/** @} */