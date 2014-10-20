/**
 * @addtogroup FPDFPPO
 * Header file for the page module
 * @{
 */


 /** (C) 2011 Foxit Corporation. All Rights Reserved.
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
 * Functions in this header file, require "page" module to be enabled in your SDK license.
 * \file
 * \author	Foxit Corporation
 * \brief	Header file for the page module - provides the interfaces for page manipulation.
 * \note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please
 *			request for enabling page module explicitly.
 * \version 3.1
*/



#ifndef _FPDFPPO_H_
#define _FPDFPPO_H_

#ifndef _FPDFVIEW_H_
#include "fpdfview.h"
#endif

/**
* Import some pages to a PDF document.
* @param[in] dest_doc		- The handle to the destination document which add the pages.
* @param[in] src_doc		- The handle to the document to be imported.
* @param[in] pagerange		- A page range string, Such as "1,3,5-7".
*  							  If this parameter is NULL, it would import all pages in src_doc.
* @param[in] index			- The page index where imported pages are added.
* @retval TRUE for success, otherwise FALSE.
*/

DLLEXPORT FPDF_BOOL STDCALL FPDF_ImportPages(FPDF_DOCUMENT dest_doc,FPDF_DOCUMENT src_doc, FPDF_BYTESTRING pagerange, int index);



/** @brief Flatten operation failed. */
#define FLATTEN_FAIL			0
/** @brief Flatten operation succeed. */
#define FLATTEN_SUCCESS			1
/** @brief There is nothing to flatten. */
#define FLATTEN_NOTINGTODO		2


#define FLAT_NORMALDISPLAY     0
#define FLAT_PRINT             1

/**
* Flatting a PDF page, annotations or form fields will make it a part of the page contents.
* @param[in] page  - Handle to the page. Return by FPDF_LoadPage function.
* @note	  Currently all version's fails return zero. If necessary we will assign different value
*		  to indicate different fail reason.
* @retval The result flag of the function, See flags above.
*/
DLLEXPORT int STDCALL FPDFPage_Flatten( FPDF_PAGE page,int nFlag );



/**
* Get a page rectangle, in points(1 point equals 1/72 inch).
* @param[in] page		- Handle to a page. Returned by FPDFPage_New.
* @param[in] iRect		- The index values for getting boxes are defined above.
* @param[in] left		- Pointer to a double number receiving the left of a rectangle (in points).
* @param[in] right		- Pointer to a double number receiving the right of a rectangle (in points).
* @param[in] bottom		- Pointer to a double number receiving the bottom of a rectangle (in points).
* @param[in] top		- Pointer to a double number receiving the top of a rectangle (in points).
* @retval TRUE if successful, FALSE otherwise.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPage_GetRectangle(FPDF_PAGE page, int iRect,
												  double* left, double* right, double* bottom, double* top);


/**
* Set a page rectangle, in points (1 point equals 1/72 inch).
* @param[in] page		- Handle to a page. Returned by FPDFPage_New.
* @param[in] iRect		- The index values for getting boxes are defined above.
* @param[in] left		- The left coordinate of a rectangle (in points).
* @param[in] right		- The right coordinate of a rectangle (in points).
* @param[in] bottom		- The bottom coordinate of a rectangle (in points).
* @param[in] top		- The top coordinate of a rectangle (in points).
* @note   After using this method, the content in the page will be changed, but not loaded.
*		  You must call the FPDF_LoadPage to reload the page.
* @retval TRUE if successful, FALSE otherwise.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPage_SetRectangle(FPDF_PAGE page, int iRect,
												  double left, double right, double bottom, double top);




/**
* Get the page rotation.
* @param[in] page	- Handle to a page. Returned by FPDFPage_New.
* @note   The PDF page rotation is rotated clockwise.
* @retval The PDF page rotation. One of following values will be returned: 0(0), 1(90), 2(180), 3(270).
*/
DLLEXPORT int STDCALL FPDFPage_GetRotation(FPDF_PAGE page);




/**
* Set page rotation. One of following values will be set: 0(0), 1(90), 2(180), 3(270).
* @param[in] page		- Handle to a page. Returned by FPDFPage_New.
* @param[in] rotate		- The value of the PDF page rotation.
* @note	  The PDF page rotation is rotated clockwise.
*		  After using this method, the content in this page will be changed, but not loaded.
*		  You must call the FPDF_LoadPage to reload the page.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPage_SetRotation(FPDF_PAGE page, int rotate);
#endif

///< _FPDFPPO_H_
/** @} */
