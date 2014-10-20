/**
 * @addtogroup FPDFAVAIL
 * Header file for the asynchronous module.
 * @{
 */

 /** (C) 2011 Foxit Corporation. All Rights Reserved.
  * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
  * Functions in this header file, require "asynchronous" module to be enabled in your SDK license.
  * \file
  * \author	Foxit Corporation
  * \brief	Header file for the asynchronous module - allows reading and downloading of a 
  *			PDF file to occur at the same time. For example, an application can display the first page of the document 
  *   		while the other pages are still downloading.
  * \note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please
  *			request for enabling asynchronous module explicitly.
  * \version 3.1
  */

#ifndef _FPDFAVAIL_H_
#define _FPDFAVAIL_H_
#include "fpdfview.h"

/** 
 * @name The result of the process which check linearized PDF.
 * @{
 */
/** @brief Indicates PDF is linearized. */
#define FSDK_IS_LINEARIZED		1
/** @brief Indicates PDF is not linearized. */
#define FSDK_NOT_LINEARIZED		0
/** @brief Unknown. */
#define FSDK_UNKNOW_LINEARIZED	-1  
/**@}*/	

/** @brief A struct that provides an interface for checking whether the specified section of a PDF file is available. 
*/
typedef struct _FX_FILEAVAIL {

	/** 
	 * @brief Version number of the interface. Currently must be 1.
	 */
	int version;

	/**
	  * Report whether the specified data section is available. A section is available only if all bytes in the section are available. 
	  * @param[out] pThis	-	Pointer to the interface structure itself.
	  * @param[in]  offset	-	The offset of the hint reported to be downloaded.
	  * @param[in]  size	-	The size of the hint reported to be downloaded.
	  * @note	Called by the Foxit SDK to check whether the data section is ready.
	  * @retval True means the specified data section is available.
	  */
	bool (*IsDataAvail)(struct _FX_FILEAVAIL* pThis, size_t offset, size_t size);
} FX_FILEAVAIL;

typedef void* FPDF_AVAIL;

/**
 * Create a document availability provider.
 * @param[in] file_avail 	-	Pointer to the file availability interface to check availability of file data.
 * @param[in] file 			-	Pointer to a file access interface for reading data from file.
 * @note   Application must call FPDFAvail_Destroy when done with the availability provider.
 * @retval A handle to the document availability provider or NULL to indicate an error occurred.
 */
DLLEXPORT FPDF_AVAIL STDCALL FPDFAvail_Create(FX_FILEAVAIL* file_avail, FPDF_FILEACCESS* file);

/**
 * Destroy a document availability provider. 
 * @param[in] avail 	-	Handle to document availability provider returned by FPDFAvail_Create.
 * @retval None
 */
DLLEXPORT void STDCALL FPDFAvail_Destroy(FPDF_AVAIL avail);

/**
 * @brief An interface for receiving download hints. Use to receive hints for further downloading.
 */
typedef struct _FX_DOWNLOADHINTS {

	/** 
	* @brief Version number of the interface. Currently must be 1.
	*/
	int version;
	
	/**
	 * Add a section to be downloaded.
	 * @param[out] 	pThis	- Pointer to the interface structure itself.
	 * @param[in] 	offset	- The offset of the hint reported to be downloaded.
	 * @param[in] 	size	- The size of the hint reported to be downloaded.
	 * @note   Called by the Foxit SDK to report downloading hints for the download manager.
	 *		   The position and size of the section may not be accurate because part of the section might 
	 *         already be available. The download manager must manage this to maximize download efficiency.
	 * @retval None.
	 */
	void (*AddSegment)(struct _FX_DOWNLOADHINTS* pThis, size_t offset, size_t size);
} FX_DOWNLOADHINTS;

/**
* Check whether the document is ready for loading, if not, get download hints.
* @param[in] avail  - Handle to document availability provider returned by FPDFAvail_Create.
* @param[in] hints  - Pointer to a download hints structure that will receive generated hints.
* @note	The application should call this function whenever new data arrives.  It should process all the
*		generated download hints, if any, until the function returns a non-zero value. Then the 
*		application can call FPDFAvail_GetDocument() to get a document handle.
* @retval Non-zero indicates the page is fully available, 0 indicates the page not yet available.
*/
DLLEXPORT int STDCALL FPDFAvail_IsDocAvail(FPDF_AVAIL avail, FX_DOWNLOADHINTS* hints);

/**
* Get document from the availability provider.
* @param[in] avail -  Handle to the document availability provider returned by FPDFAvail_Create.
* @note After FPDFAvail_IsDocAvail() returns TRUE, the application should call this function to
*		get the document handle. To close the document, use the FPDF_CloseDocument function.
* @retval Handle to the document or NULL if an error occurs.
*/
DLLEXPORT FPDF_DOCUMENT STDCALL FPDFAvail_GetDocument(FPDF_AVAIL avail);


/**
* Get the page number of the first available page in a linearized PDF.
* @param[in] document   -   A document handle returned by FPDFAvail_GetDocument.
* @note For most linearized PDFs, the first available page would be just the first page. However,
*		there are some PDFs that set the first available page to be a page other than the first page.
*		For non-linearized PDF, this function will always return zero.
* @retval Zero-based index for the first available page.
*/
DLLEXPORT int STDCALL FPDFAvail_GetFirstPageNum(FPDF_DOCUMENT document);
	
/**
* Check whether a page is ready for loading, if not, get download hints.
* @param[in] avail		-  Handle to document availability provider returned by FPDFAvail_Create.
* @param[in] page_index	-  Index number of the page. 0 for the first page.
* @param[out] hints		-  Pointer to a download hints interface structure that receives generated hints.
* @note This function can only be called after FPDFAvail_GetDocument is called.
*		The application should call this function whenever new data arrives. It should process all the
*		generated download hints, if any, until the function returns a non-zero value. Then the 
*		application can perform page loading.
* @retval Non-zero value indicates a page is fully available, 0 indicates a page is not yet available.
*/
DLLEXPORT int STDCALL FPDFAvail_IsPageAvail(FPDF_AVAIL avail, int page_index, FX_DOWNLOADHINTS* hints);


/**
* Check whether form data is ready for initialization, if not, get download hints.
* @param[in] avail		-  Handle to document availability provider returned by FPDFAvail_Create.
* @param[out] hints 	-  Pointer to a download hints interface structure that receives generated hints.
* @note This function can only be called after FPDFAvail_GetDocument is called. 
*		The application should call this function whenever new data arrives. The application should process all the
*		generated download hints, if any, until the function returns a non-zero value. Then the 
*		application can perform page loading. FPDFDOC_InitFormFillEnviroument should be called
*		after the function returns a non-zero value.
* @retval Non-zero value indicates form data is fully available, 0 indicates form data is not yet available.
*			Details: -1 -  Error, the input parameter is not correct (e.g. hints is NULL).
*				     0	-  Data is not available.
*				     1	-  Data is available.
*				     2	-  No form data.
*/
DLLEXPORT int STDCALL FPDFAvail_IsFormAvail(FPDF_AVAIL avail, FX_DOWNLOADHINTS* hints);

/**
* Check whether a document is a Linearized PDF.
* @param[in] avail - Handle to document availability provider returned by FPDFAvail_Create.
* @note   Returns TRUE/FALSE as soon as the first 1K chunk of data is received. 
*		  The function must recive at least 1K to determine if the document is a linearized PDF.
* @retval Return TRUE means the document is a linearized PDF; otherwise it is not a linearized PDF.
*		  FSDK_IS_LINEARIZED is a linearized PDF.
*		  FSDK_NOT_LINEARIZED is not a linearized PDF.
*		  FSDK_UNKNOW_LINEARIZED can't deterine whether the file is a linearized PDF.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFAvail_IsLinearized(FPDF_AVAIL avail);

#endif
///< _FPDFAVAIL_H_
/** @} */
