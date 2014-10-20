/**
 * @addtogroup FPDFPROGRESSIVE
 * Header file for the progressive module.
 * @{
 */

 /** 
  * (C) 2011 Foxit Corporation. All Rights Reserved.
  * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
  * Functions in this header file require the "progressive" module to be enabled in the SDK license.
  * \file
  * \author	Foxit Corporation
  * \brief	Header file for the progressive module - progressive functionality allows an application to respond to other 
  *			operations while a document is in the process of displaying.  
  * \note	If you want to purchase license of Foxit PDF SDK and use ANY of the following functions, 
  *			please request for enabling progressive module explicitly.
  * \version 3.1
  */

#ifndef _FPDFPROGRESSIVE_H_
#define _FPDFPROGRESSIVE_H_
#include "fpdfview.h"
#ifdef _WIN32
#define DLLEXPORT __declspec( dllexport )
#define STDCALL __stdcall
#else
#define DLLEXPORT
#define STDCALL
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
/** Flags for progressive process status. */
 #define FPDF_RENDER_READER				0
 #define FPDF_RENDER_TOBECOUNTINUED		1
 #define FPDF_RENDER_DONE				2
 #define FPDF_RENDER_FAILED				3
  
    /** @brief IFSDK_PAUSE interface. */
  typedef struct _IFSDK_PAUSE
  {
	/** 
	 * @brief Version number of the interface. Currently must be 1.
	 */
  	int version;
  	
	/** 
	* Check if a progressive process needs to be paused.
	* @param[out] pThis		-	Pointer to the interface structure itself.
	* @retval Non-zero for pause now, 0 for continue.
	*/
  	FPDF_BOOL (*NeedToPauseNow) (struct _IFSDK_PAUSE* pThis);
  	
	/** 
	* @brief A user defined data pointer that is used by the user application. Can be NULL.
	*/
  	void*		user;
  } IFSDK_PAUSE;
  
  /**
  * Progressively render the specified page contents to a device independent bitmap.
  * @param[in] bitmap		-	Handle to the device independent bitmap (as the output buffer).
  *											Bitmap handle can be created by the FPDFBitmap_Create function.
  * @param[in] page			-	Handle to the page. Returned by FPDF_LoadPage function.
  * @param[in] start_x		-	Left pixel position of the display area in bitmap coordinates.
  * @param[in] start_y		-	Top pixel position of the display area in bitmap coordinates.
  * @param[in] size_x		-	Horizontal size (in pixels) for displaying the page.
  * @param[in] size_y		-	Vertical size (in pixels) for displaying the page.
  * @param[in] rotate			-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
  *											2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).

 * @param[in] flags		-	0 for normal display, or combination of flags defined in fpdfpview.h.

  * @param[in] pause		-	The IFSDK_PAUSE interface. A callback mechanism that allows the page rendering process
  *										to be paused before it is finished. This can be set to NULL if pause is not needed.

  * @retval The rendering status. See "progressive process status" flags above for more details.	
  *
  */
  DLLEXPORT int STDCALL FPDF_RenderPageBitmap_Start(FPDF_BITMAP bitmap, FPDF_PAGE page, int start_x, int start_y, int size_x,
  												  int size_y, int rotate, int flags, IFSDK_PAUSE * pause);
  
  #ifdef _WIN32
  
  /**
  * Progressively render the specified page contents to a device (screen, bitmap, or printer). This function is only supported on Windows.
  * @param[in] dc			-	Handle to device context.
  * @param[in] page		-	Handle to the page. Returned by FPDF_LoadPage function.
  * @param[in] start_x	-	Left pixel position of the display area in device coordinates.
  * @param[in] start_y	-	Top pixel position of the display area in device coordinates.
  * @param[in] size_x	-	Horizontal size (in pixels) for displaying the page.
  * @param[in] size_y	-	Vertical size (in pixels) for displaying the page.
  * @param[in] rotate	-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
  *							2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
  * @param[in] flags	-	0 for normal display, or combination of flags defined in fpdfpview.h.
  * @param[in] pause	-	The IFSDK_PAUSE interface. A callback mechanism that allows the page rendering process
  *							to be paused before it is finished. This can be set to NULL if pause is not needed.
  * @retval The rendering status. See "progressive process status" flags for more details.
  */
  DLLEXPORT int STDCALL FPDF_RenderPage_Start(HDC dc, FPDF_PAGE page, int start_x, int start_y, int size_x,
  											int size_y, int rotate, int flags, IFSDK_PAUSE * pause);
  #endif
  
  /**
  * Continue rendering a PDF page.
  * Parameters: 
  * @param[in] page		-	Handle to the page. Returned by the FPDF_LoadPage function.
  * @param[in] pause	-	The IFSDK_PAUSE interface. A callback mechanism that allows the page rendering process
  *							to be paused before it is finished. This can be set to NULL if pause is not needed.
  * @retval The rendering status. See "progressive process status" flags for more details.
  */
  DLLEXPORT int STDCALL FPDF_RenderPage_Continue(FPDF_PAGE page,IFSDK_PAUSE * pause);
  
  /**
  * Provides the current status of the page rendering process (meaured in percent complete).
  * @param[in] page		-	Handle to the page. Return by FPDF_LoadPage function.
  * @retval An estimated value (in percent complete) of the current rendering progress.  
  */
  DLLEXPORT int STDCALL FPDF_RenderPage_EstimateProgress(FPDF_PAGE page);

  /**
  * Release the page resource allocated during page rendering. This function must be called after page rendering finishes or 
  * if rendering of the page is canceled.
  * @param[in]page	-	Handle to the page. Returned by the FPDF_LoadPage function.
  * @retval No return value.
  */
  DLLEXPORT void STDCALL FPDF_RenderPage_Close(FPDF_PAGE page);

#ifdef __cplusplus
};
#endif

#endif
 

///< _FPDFPROGRESSIVE_H_
/** @} */
