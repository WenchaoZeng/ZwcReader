/**
 * @addtogroup FPDFVIEW
 * Header file for the view module
 * @{
 */


 /** (C) 2011 Foxit Corporation. All Rights Reserved.
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
 * Functions in this header file, require "view" module to be enabled in your SDK license.
 * \file
 * \author	Foxit Corporation
 * \brief	Header file for the view module - to render PDF documents and obtain basic PDF information.
 * \note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please
 *			request for enabling view module explicitly.
 * \version 3.1
*/


#ifndef _FPDFVIEW_H_
#define _FPDFVIEW_H_

#if defined(_WIN32) && !defined(__WINDOWS__)
#include <windows.h>
#endif

/** Data types*/
typedef void*	FPDF_MODULEMGR;

/** PDF types*/
typedef void*	FPDF_DOCUMENT;		
typedef void*	FPDF_PAGE;			
typedef void*	FPDF_PAGEOBJECT;	
typedef void*	FPDF_PATH;
typedef void*	FPDF_CLIPPATH;	
typedef void*	FPDF_BITMAP;	
typedef void*	FPDF_FONT;			

typedef void*	FPDF_TEXTPAGE;
typedef void*	FPDF_SCHHANDLE;
typedef void*	FPDF_PAGELINK;
typedef void*	FPDF_HMODULE;
typedef void*	FPDF_DOCSCHHANDLE;

typedef void*	FPDF_BOOKMARK;
typedef void*	FPDF_DEST;
typedef void*	FPDF_ACTION;
typedef void*	FPDF_LINK;

/** Basic data types*/
typedef int				FPDF_BOOL;
typedef int				FPDF_ERROR;	
typedef unsigned long	FPDF_DWORD;

/** String types*/
typedef unsigned short			FPDF_WCHAR;
typedef unsigned char const*	FPDF_LPCBYTE;


/** FPDFSDK may use three types of strings: byte string, wide string (UTF-16LE encoded), and platform dependent string*/
typedef const char*				FPDF_BYTESTRING;

/** Foxit PDF SDK always use UTF-16LE encoding wide string, each character use 2 bytes (except subrogation), with low byte first. */
typedef const unsigned short*	FPDF_WIDESTRING;		 

/**
* For Windows programmers: for most case it's OK to treat FPDF_WIDESTRING as Windows unicode string,
*		 however, special care needs to be taken if you expect to process Unicode larger than 0xffff.
* For Linux/Unix programmers: most compiler/library environment uses 4 bytes for a Unicode character,
*		you have to convert between FPDF_WIDESTRING and system wide string by yourself.
*/

#ifdef _WIN32_WCE
typedef const unsigned short* FPDF_STRING;
#else
typedef const char* FPDF_STRING;
#endif

#ifdef _WIN32
/** On Windows system, functions are exported in a DLL */
#define DLLEXPORT __declspec( dllexport )
#define STDCALL __stdcall
#else
#define DLLEXPORT
#define STDCALL
#endif

#ifdef __cplusplus
extern "C" {
#endif



/**
* Initialize the FPDFSDK library 
* @param[in] hInstance	-	For WIN32 system only: the instance of the executable or DLL module.
* @note		You have to call this function before you can call any PDF processing functions.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_InitLibrary(void* hInstance);

/**
* Get the module of this DLL.
* @retval	FPDF_MODULEMGR	-	The handle of this module.  
*/
DLLEXPORT FPDF_MODULEMGR STDCALL FPDF_GetModuleMgr();

/**
* Release all resources allocated by the FPDFSDK library.
* @note		You can call this function to release all memory blocks allocated by the library. 
*			After this function is called, you should not call any PDF processing functions.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_DestroyLibrary();

/**
* Unlock the DLL using license key info received from Foxit.
* @param[in] license_id		-	A string received from Foxit identifying the SDK license.
* @param[in] unlock_code	-	A string received from Foxit for unlocking the DLL.
* @note		For SDK evaluators, this function call is not required, then all
*			rendered pages will come with an evaluation mark.
*			For purchased SDK customers, this should be the first function
*			called before any other functions to be called.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_UnlockDLL(FPDF_BYTESTRING license_id, FPDF_BYTESTRING unlock_code);

/**
* Open and load a PDF document.
* @param[in] file_path	-	Path to the PDF file (including extension).
* @param[in] password	-	A string used as the password for PDF file. 
*							If no password needed, empty or NULL can be used.
* @note		Loaded document can be closed by FPDF_CloseDocument.
*			If this function fails, you can use FPDF_GetLastError() to retrieve
*			the reason why it fails.
* @retval	A handle to the loaded document. If failed, NULL is returned.
*/
DLLEXPORT FPDF_DOCUMENT	STDCALL FPDF_LoadDocument(FPDF_STRING file_path, 
												  FPDF_BYTESTRING password);
/**
* Open and load a PDF document from memory.
* @param[in] data_buf	-	Pointer to a buffer containing the PDF document.
* @param[in] size		-	Number of bytes in the PDF document.
* @param[in] password	-	A string used as the password for PDF file. 
*							If no password needed, empty or NULL can be used.
* @note		The memory buffer must remain valid when the document is open.
*			Loaded document can be closed by FPDF_CloseDocument.
*			If this function fails, you can use FPDF_GetLastError() to retrieve
*			the reason why it fails.
* @retval	A handle to the loaded document. If failed, NULL is returned.
*/
DLLEXPORT FPDF_DOCUMENT	STDCALL FPDF_LoadMemDocument(const void* data_buf, 
											int size, FPDF_BYTESTRING password);

/** 
* @name Custom file access.
*/
/**@{*/
typedef struct {
	/** 
	* @brief  File length, in bytes.
	*/
	unsigned long	m_FileLen;

	
	/**
	* A function pointer for getting a block of data from specific position.
	* Position is specified by byte offset from beginning of the file.
	* The position and size will never go out range of file length.
	* It may be possible for FPDFSDK to call this function multiple times for same position.
	* @retval Should be non-zero if successful, zero for error.
	*/
	int				(*m_GetBlock)(void* param, unsigned long position, unsigned char* pBuf, unsigned long size);

	/** 
	* @brief  A custom pointer for all implementation specific data.
	*	      This pointer will be used as the first parameter to m_GetBlock callback.
	*/
	void*			m_Param;
} FPDF_FILEACCESS;
/**@}*/

/**
* Load PDF document from a custom access descriptor.
* @param[in] pFileAccess	-	A structure for access the file.
* @param[in] password		-	Optional password for decrypting the PDF file.
* @note		The application should maintain the file resources being valid until the PDF document close.
*			Loaded document can be closed by FPDF_CloseDocument.
* @retval	A handle to the loaded document. If failed, NULL is returned.
*/
DLLEXPORT FPDF_DOCUMENT STDCALL FPDF_LoadCustomDocument(FPDF_FILEACCESS* pFileAccess, 
														FPDF_BYTESTRING password);


/** 
* @name Last error code
*@{
*/
/** @brief No error. */
#define FPDF_ERR_SUCCESS		0
/** @brief Unknown error. */
#define FPDF_ERR_UNKNOWN		1
/** @brief Unknown error. */
#define FPDF_ERR_FILE			2
/** @brief File not found or could not be opened. */
#define FPDF_ERR_FORMAT			3
/** @brief Password required or incorrect password. */
#define FPDF_ERR_PASSWORD		4
/** @brief Unsupported security scheme. */
#define FPDF_ERR_SECURITY		5
/** @brief Page not found or content error. */
#define FPDF_ERR_PAGE			6	  
/**@}*/	



/**
* Get last error code when an SDK function failed.
* @note		If the previous SDK call succeeded, the return value of this function
*			is not defined.
* @retval	A 32-bit integer indicating error codes (defined above).
*/
DLLEXPORT unsigned long	STDCALL FPDF_GetLastError();

/**
* Get file permission flags of the document.
* @param[in] document	-	Handle to document. Returned by FPDF_LoadDocument function.
* @retval	A 32-bit integer indicating permission flags. Please refer to PDF Reference for
*			detailed description. If the document is not protected, 0xffffffff will be returned.
*/
DLLEXPORT unsigned long	STDCALL FPDF_GetDocPermissions(FPDF_DOCUMENT document);

/**
* Get total number of pages in a document.
* @param[in] document	-	Handle to document. Returned by FPDF_LoadDocument function.
* @retval	Total number of pages in the document.
*/
DLLEXPORT int STDCALL FPDF_GetPageCount(FPDF_DOCUMENT document);

/**
* Load a page inside a document.
* @param[in] document	-	Handle to document. Returned by FPDF_LoadDocument function.
* @param[in] page_index	-	Index number of the page. 0 for the first page.
* @note		Loaded page can be rendered to devices using FPDF_RenderPage function.
*			Loaded page can be closed by FPDF_ClosePage.
* @retval	A handle to the loaded page. If failed, NULL is returned.
*/
DLLEXPORT FPDF_PAGE	STDCALL FPDF_LoadPage(FPDF_DOCUMENT document, int page_index);

/**
* Get page width.
* @param[in] page	-	Handle to the page. Returned by FPDF_LoadPage function.
* @retval	Page width (excluding non-displayable area) measured in points.
*			One point is 1/72 inch (around 0.3528 mm).
*
*/
DLLEXPORT double STDCALL FPDF_GetPageWidth(FPDF_PAGE page);

/**
* Get page height.
* @param[in] page	-	Handle to the page. Returned by FPDF_LoadPage function.
* @retval	Page height (excluding non-displayable area) measured in points.
*			One point is 1/72 inch (around 0.3528 mm)
*
*/
DLLEXPORT double STDCALL FPDF_GetPageHeight(FPDF_PAGE page);

/**
* Get the size of a page by index.
* @param[in] document	-	Handle to document. Returned by FPDF_LoadDocument function.
* @param[in] page_index	-	Page index, zero for the first page.
* @param[in] width		-	Pointer to a double receiving the page width (in points).
* @param[in] height		-	Pointer to a double receiving the page height (in points).
* @retval	Non-zero for success. 0 for error (document or page not found).
*
*/
DLLEXPORT int STDCALL FPDF_GetPageSizeByIndex(FPDF_DOCUMENT document, int page_index, double* width, double* height);

/**
* Declares of a pointer type to the callback function for the FPDF_EnumPageSize method.
*			page_index	-	Page index, zero for the first page.
*			width		-	The page width.
*			height		-	The page height.
* @retval	None. 		
*/
typedef void (*FPDF_ENUMPAGESIZEPROC)(int page_index, double width, double height);

/**
* Enumerating all pages within the document.
* @param[in] document	-	Handle to document. Returned by FPDF_LoadDocument function.
* @param[in] callback	-	A pointer to a callback function.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_EnumPageSize(FPDF_DOCUMENT document, FPDF_ENUMPAGESIZEPROC callback);

/** 
* @name The result of the process which check linearized to be rendered.
*@{
*/
/** Set if annotations are to be rendered. */
#define FPDF_ANNOT			0x01		 
/**  Set if using text rendering optimized for LCD display. */
#define FPDF_LCD_TEXT		0x02		
/**  Don't use the native text output available on some platforms Applicable to desktop Windows systems only.*/
#define FPDF_NO_NATIVETEXT	0x04		
/**  Grayscale output.*/
#define FPDF_GRAYSCALE		0x08		
/**  Set if you want to get some debug info.  Please discuss with Foxit first if you need to collect debug info.*/
#define FPDF_DEBUG_INFO		0x80		 
/**  Set if you don't want to catch exception.*/
#define FPDF_NO_CATCH		0x100		
/**@}*/
#ifdef _WIN32

/**
* Render contents in a page to a device (screen, bitmap, or printer). This function is only supported on Windows system. 
* @param[in] dc			-	Handle to device context.
* @param[in] page		-	Handle to the page. Returned by FPDF_LoadPage function.
* @param[in] start_x	-	Left pixel position of the display area in the device coordinate.
* @param[in] start_y	-	Top pixel position of the display area in the device coordinate.
* @param[in] size_x		-	Horizontal size (in pixels) for displaying the page.
* @param[in] size_y		-	Vertical size (in pixels) for displaying the page.
* @param[in] rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
*							2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
* @param[in] flags		-	0 for normal display, or combination of flags defined above.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_RenderPage(HDC dc, FPDF_PAGE page, int start_x, int start_y, int size_x, int size_y,
						int rotate, int flags);
#endif

/**
* Render contents in a page to a device independent bitmap
* @param[in] bitmap		-	Handle to the device independent bitmap (as the output buffer).
*							Bitmap handle can be created by FPDFBitmap_Create function.
* @param[in] page		-	Handle to the page. Returned by FPDF_LoadPage function.
* @param[in] start_x	-	Left pixel position of the display area in the bitmap coordinate.
* @param[in] start_y	-	Top pixel position of the display area in the bitmap coordinate.
* @param[in] size_x		-	Horizontal size (in pixels) for displaying the page.
* @param[in] size_y		-	Vertical size (in pixels) for displaying the page.
* @param[in] rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
*							2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
* @param[in] flags		-	0 for normal display, or combination of flags defined above.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_RenderPageBitmap(FPDF_BITMAP bitmap, FPDF_PAGE page, int start_x, int start_y, 
						int size_x, int size_y, int rotate, int flags);

/**
* Draw a thumbnail of a page into a bitmap.
* @param[in] bitmap		-	Handle to the device independent bitmap (as the output buffer).
*							Bitmap handle can be created by FPDFBitmap_Create function.
* @param[in] page		-	Handle to the page. Returned by FPDF_LoadPage function.
* @param[in] start_x	-	Left pixel position of the display area in the device coordinate.
* @param[in] start_y	-	Top pixel position of the display area in the device coordinate.
* @param[in] size_x		-	Horizontal size (in pixels) for displaying the page.
* @param[in] size_y		-	Vertical size (in pixels) for displaying the page.
* @param[in] rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
*							 2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
* @param[in] flags		-	Currently must be zero.
* @note		This functions draws a very low-resolution thumbnail of a page, sometimes with
*			inaccurate shape or position. The result thumbnail is meant for a very rough preview
*			of the page contents, just giving user some idea about how the page looks like.
*			The thumbnail is often useful in multi-threaded or progressive environment, the
*			application can first display the low-resolution thumbnail, start to respond to
*			user input, and a higher resolution thumbnail can be generated by FPDF_RenderPageBitmap 
*			function.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_QuickDrawPage(FPDF_BITMAP bitmap, FPDF_PAGE page, int start_x, int start_y, 
										  int size_x, int size_y, int rotate, int flags);

/**
* Close a loaded PDF page.
* @param[in] page		-	Handle to the loaded page.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_ClosePage(FPDF_PAGE page);

/**
* Close a loaded PDF document.
* @param[in] document	-	Handle to the loaded document.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_CloseDocument(FPDF_DOCUMENT document);

/**
* Convert the screen coordinate of a point to page coordinate.
* @param[in] page		-	Handle to the page. Returned by FPDF_LoadPage function.
* @param[in] start_x	-	Left pixel position of the display area in the device coordinate.
* @param[in] start_y	-	Top pixel position of the display area in the device coordinate.
* @param[in] size_x		-	Horizontal size (in pixels) for displaying the page.
* @param[in] size_y		-	Vertical size (in pixels) for displaying the page.
* @param[in] rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
*							 2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
* @param[in] device_x	-	X value in device coordinate, for the point to be converted.
* @param[in] device_y	-	Y value in device coordinate, for the point to be converted.
* @param[in] page_x		-	A Pointer to a double receiving the converted X value in page coordinate.
* @param[in] page_y		-	A Pointer to a double receiving the converted Y value in page coordinate.
* @note
*			The page coordinate system has its origin at left-bottom corner of the page, with X axis goes along
*			the bottom side to the right, and Y axis goes along the left side upward. NOTE: this coordinate system 
*			can be altered when you zoom, scroll, or rotate a page, however, a point on the page should always have 
*			the same coordinate values in the page coordinate system. 
*
*			The device coordinate system is device dependent. For screen device, its origin is at left-top
*			corner of the window. However this origin can be altered by Windows coordinate transformation
*			utilities. You must make sure the start_x, start_y, size_x, size_y and rotate parameters have exactly
*			same values as you used in FPDF_RenderPage() function call.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_DeviceToPage(FPDF_PAGE page, int start_x, int start_y, int size_x, int size_y,
						int rotate, int device_x, int device_y, double* page_x, double* page_y);

/**
* Convert the page coordinate of a point to screen coordinate.
* @param[in] page		-	Handle to the page. Returned by FPDF_LoadPage function.
* @param[in] start_x	-	Left pixel position of the display area in the device coordinate.
* @param[in] start_y	-	Top pixel position of the display area in the device coordinate.
* @param[in] size_x		-	Horizontal size (in pixels) for displaying the page.
* @param[in] size_y		-	Vertical size (in pixels) for displaying the page.
* @param[in] rotate		-	Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
*							 2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
* @param[in] page_x		-	X value in page coordinate, for the point to be converted.
* @param[in] page_y		-	Y value in page coordinate, for the point to be converted.
* @param[in] device_x	-	A pointer to an integer receiving the result X value in device coordinate.
* @param[in] device_y	-	A pointer to an integer receiving the result Y value in device coordinate.
* @note
*			See comments of FPDF_DeviceToPage() function.
*
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_PageToDevice(FPDF_PAGE page, int start_x, int start_y, int size_x, int size_y,
						int rotate, double page_x, double page_y, int* device_x, int* device_y);

/**
* Create a Foxit Device Independent Bitmap (FXDIB).
* @param[in] width		-	Number of pixels in a horizontal line of the bitmap. Must be greater than 0.
* @param[in] height		-	Number of pixels in a vertical line of the bitmap. Must be greater than 0.
* @param[in] alpha		-	A flag indicating whether alpha channel is used. Non-zero for using alpha, zero for not using.
* @note
*			An FXDIB always use 4 byte per pixel. The first byte of a pixel is always double word aligned.
*			Each pixel contains red (R), green (G), blue (B) and optionally alpha (A) values.
*			The byte order is BGRx (the last byte unused if no alpha channel) or BGRA.
*			
*			The pixels in a horizontal line (also called scan line) are stored side by side, with left most
*			pixel stored first (with lower memory address). Each scan line uses width*4 bytes.
*
*			Scan lines are stored one after another, with top most scan line stored first. There is no gap
*			between adjacent scan lines.
*
*			This function allocates enough memory for holding all pixels in the bitmap, but it doesn't 
*			initialize the buffer. Applications can use FPDFBitmap_FillRect to fill the bitmap using any color.
* @retval	The created bitmap handle, or NULL if parameter error or out of memory.
*/
DLLEXPORT FPDF_BITMAP STDCALL FPDFBitmap_Create(int width, int height, int alpha);

/** 
* @name More DIB formats
*@{
*/
/** Gray scale bitmap, one byte per pixel. */
#define FPDFBitmap_Gray		1		 
/** 3 bytes per pixel, byte order: blue, green, red. */
#define FPDFBitmap_BGR		2		 
/**  4 bytes per pixel, byte order: blue, green, red, unused. */
#define FPDFBitmap_BGRx		3		
/**  4 bytes per pixel, byte order: blue, green, red, alpha. */
#define FPDFBitmap_BGRA		4		
/**@}*/

/**
* Create a Foxit Device Independent Bitmap (FXDIB)
* @param[in] width		-	Number of pixels in a horizontal line of the bitmap. Must be greater than 0.
* @param[in] height		-	Number of pixels in a vertical line of the bitmap. Must be greater than 0.
* @param[in] format		-	A number indicating for bitmap format, as defined above.
* @param[in] first_scan	-	A pointer to the first byte of first scan line, for external buffer
*							only. If this parameter is NULL, then the SDK will create its own buffer.
* @param[in] stride		-	Number of bytes for each scan line, for external buffer only..
* @note		Similar to FPDFBitmap_Create function, with more formats and external buffer supported. 
*			Bitmap created by this function can be used in any place that a FPDF_BITMAP handle is 
*			required. 
*
*			If external scanline buffer is used, then the application should destroy the buffer
*			by itself. FPDFBitmap_Destroy function will not destroy the buffer.
* @retval	The created bitmap handle, or NULL if parameter error or out of memory.
*
*/
DLLEXPORT FPDF_BITMAP STDCALL FPDFBitmap_CreateEx(int width, int height, int format, void* first_scan, int stride);

/**
* Fill a rectangle area in an FXDIB.
* @param[in] bitmap		-	The handle to the bitmap. Returned by FPDFBitmap_Create function.
* @param[in] left		-	The left side position. Starting from 0 at the left-most pixel.
* @param[in] top		-	The top side position. Starting from 0 at the top-most scan line.
* @param[in] width		-	Number of pixels to be filled in each scan line.
* @param[in] height		-	Number of scan lines to be filled.
* @param[in] red		-	A number from 0 to 255, identifying the red intensity.
* @param[in] green		-	A number from 0 to 255, identifying the green intensity.
* @param[in] blue		-	A number from 0 to 255, identifying the blue intensity.
* @param[in] alpha		-	(Only if the alpha channeled is used when bitmap created) A number from 0 to 255,
*							identifying the alpha value.
* @note
*			This function set the color and (optionally) alpha value in specified region of the bitmap.
*			NOTE: If alpha channel is used, this function does NOT composite the background with the source color,
*			instead the background will be replaced by the source color and alpha.
*			If alpha channel is not used, the "alpha" parameter is ignored.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDFBitmap_FillRect(FPDF_BITMAP bitmap, int left, int top, int width, int height, 
									int red, int green, int blue, int alpha);

/**
* Get data buffer of an FXDIB
* @param[in] bitmap		-	Handle to the bitmap. Returned by FPDFBitmap_Create function.
* @note		Applications can use this function to get the bitmap buffer pointer, then manipulate any color
*			and/or alpha values for any pixels in the bitmap.
* @retval	The pointer to the first byte of the bitmap buffer.
*/
DLLEXPORT void* STDCALL FPDFBitmap_GetBuffer(FPDF_BITMAP bitmap);

/**
* Get width of an FXDIB.
* @param[in] bitmap		-	Handle to the bitmap. Returned by FPDFBitmap_Create function.
* @retval	The number of pixels in a horizontal line of the bitmap.
*/
DLLEXPORT int STDCALL FPDFBitmap_GetWidth(FPDF_BITMAP bitmap);

/**
* Get height of an FXDIB.
* @param[in] bitmap		-	Handle to the bitmap. Returned by FPDFBitmap_Create function.
* @retval	The number of pixels in a vertical line of the bitmap.
*/
DLLEXPORT int STDCALL FPDFBitmap_GetHeight(FPDF_BITMAP bitmap);

/**
* Get number of bytes for each scan line in the bitmap buffer.
* @param[in] bitmap		-	Handle to the bitmap. Returned by FPDFBitmap_Create function.
* @retval	The number of bytes for each scan line in the bitmap buffer.
*/
DLLEXPORT int STDCALL FPDFBitmap_GetStride(FPDF_BITMAP bitmap);

/**
* Destroy an FXDIB and release all related buffers. 
* @param[in] bitmap		-	Handle to the bitmap. Returned by FPDFBitmap_Create function.
* @note		This function will not destroy any external buffer.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDFBitmap_Destroy(FPDF_BITMAP bitmap);

/**
* Allocate memory block in FPDFSDK. This memory can be freed by FPDF_FreeMemory function.
* @param[in] size		-	Byte size of requested memory block. Can not be zero.
* @note		Some FPDFSDK interface may require application to allocate memory for internal use of
*			FPDFSDK. In this case application must call this function to allocate memory, don't
*			use malloc() or other memory allocator.
*			If an error handler installed and exception/long jump is used in the out of memory handling,
*			this function might never return if no memory available.
* @retval	The allocated pointer. NULL if memory not available.
*/
DLLEXPORT void* STDCALL FPDF_AllocMemory(unsigned long size);

/**
* Free a memory area allocated by Foxit SDK.
* @param[in] p		-	The pointer. Should not be NULL.
* @retval	None.
* @note		In case FPDFSDK allocated some memory for user application, the user application
*			must free it to avoid memory leakage. And the application must call FPDF_FreeMemory
*			function to do that. Do NOT use c/c++ memory free() function or other similar functions.
*/
DLLEXPORT void STDCALL FPDF_FreeMemory(void* p);

/** Out of memory. The error handler should quit the application, or use long jump to get out of current rendering.*/
#define FPDFERR_OUT_OF_MEMORY		1		
/** Missing PDF feature. The error handler can safely continue with other rendering.*/
#define FPDFERR_MISSING_FEATURE		2		 

typedef void (*FPDF_ErrorHandler)(int code, FPDF_BYTESTRING msg);

/**
* Set a call back function when FPDFSDK has some error to report.
* @param[in] func	-	Pointer to the error handler function.
* @note		Currently only two error codes are defined (see above).
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_SetErrorHandler(FPDF_ErrorHandler func);

/**
* Set the folder path for module files (like the FPDFCJK.BIN).
* @param[in] module_name	-	Name of the module. Currently please use NULL (0) only.
* @param[in] folder_name	-	Name of the folder. For example: "C:\\program files\\FPDFSDK".
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_SetModulePath(FPDF_STRING module_name, FPDF_STRING folder_name);



/** @brief  Define an interface for generating glyph bitmaps.
*			This interface does not exist on desktop Windows system. But on alternative systems,
*			including mobile system, this interface must be implemented in order to display
*			non-embedded non-western fonts, like Chinese/Japanese/Korean characters.
*			To make use of a glyph provider, call FPDF_SetGlyphProvider function.
*/
typedef struct {

	/**
	* Map a font with particular name. The implementation can return any pointer to some
	* internal font structure. Or it can return NULL if font mapping not supported (like if 
	* there is only one font available in the system).
	* The result of this interface function will be passed back to other interface functions
	* as "font handle".
	* @param[in] name		-	The single byte encoded name of the font. It might be a MBCS encoded name.
	* @param[in] codepage	-	The Windows code page identifier for the font, indicating the primary character set
	*							of the font. Currently it can be one of the followings:
	*							0	-	unknown character set,
	*							932	-	Japanese character set,
	*							936	-	Simplified Chinese character set,
	*							949	-	Korean character set,
	*							950	-	Traditional character set,
	*							1200-	Unicode character set,
	*/
	void*	(*MapFont)(FPDF_BYTESTRING name, int codepage);

	/**
	* Get bounding box of a glyph. The boundaries are measured in PDF font units, which is
	* 1/1000 of the em size. For example, if a character's top boundary is at half of the em square,
	* then the top value should be 500.
	* It's OK to return a box larger than the actual bounding box of the character. So some 
	* implementation may just return a fixed bounding box for all glyphs. But returning a 
	* box smaller than the actually bounding box will cause some problem like during scrolling.
	* @param[in] font		-	The font handle returned by MapFont interface.
	* @param[in] unicode	-	The unicode of the character
	* @param[in] cid		-	The CID code (see Adobe CID specifications) of the character. 0 if not available.
	*							 For most characters, implementation can ignore this parameter. However, if precise
	*							 display of CJK characters is required, some special CID (like half width/full width,
	*							 rotated, etc) needs special handling.
	* @param[in] left		-	[OUT] Pointer to returned left boundary
	* @param[in] top		-	[OUT] Pointer to returned top boundary
	* @param[in] right		-	[OUT] Pointer to returned right boundary
	* @param[in] bottom		-	[OUT] Pointer to returned bottom boundary
	*/
	void	(*GetGlyphBBox)(void* font, int unicode, int cid, int* left, int* top, int* right, int* bottom);

	/**
	* This interface is the main interface for getting glyph bitmaps. The input include font handle,
	* unicode and CID code, font size, then the implementation should allocate a sufficient buffer
	* to hold the grayscale bitmap for the character, and return its position (relative to origin
	* of the character), size, buffer, and stride to FPDFSDK.
	* FPDFSDK then will use the returned bitmap and position information to display the glyph.
	* @param[in] font		-	The font handle returned by MapFont interface.
	* @param[in] unicode	-	The unicode of the character
	* @param[in] cid		-	The CID code of the character. See comments in GetCharBBox interface.
	* @param[in] size		-	The font size (size for em square).
	* @param[in] left		-	[OUT] Pointer to left offset of the bitmap, from the character origin.
	*							Negative means the bitmap should move to left of the origin,
	*							positive means the bitmap should move to right side of the origin.
	* @param[in] top		-	[OUT] Pointer to top offset of the bitmap, from the character origin.
	*							Negative means the bitmap should move downward from the origin,
	*							positive means the bitmap should move to upward from the origin.
	* @param[in] width		-	[OUT] Pointer to output width (number of pixels per scanline)
	* @param[in] height		-	[OUT] Pointer to output height (number of scanlines)
	* @param[in] buffer		-	[OUT] Pointer to another pointer which points to a buffer containing the
	*							glyph bitmap. This buffer must be allocated by FPDF_AllocMemory function. 
	*							This buffer must contain scanlines of the bitmap from top to bottom.
	*							Each byte in the buffer represent a pixel of the glyph, 0 means not inside
	*							the glyph, 255 means fully inside the glyph. Implementation can also use
	*							gray scale (between 0-255) to identify pixels on the border of the glyph.
	*							Implementation doesn't need to free the buffer, FPDFSDK will do that.
	* @param[in] stride		-	[OUT] Pointer to output stride (number of bytes per scanline in the buffer).
	* @retval	Implementation should return non-zero if success, 0 if error happens (like character not found).
	*/
	int		(*GetGlyphBitmap)(void* font, int unicode, int cid, double size, int* left, int* top, 
							int* width, int* height, void** buffer, int* stride);
} FPDF_GLYPHPROVIDER;

/**
* Make use of a custom glyph bitmap provider.
* Not available on Desktop Windows system.
* @param[in] pProvider	-	Pointer to a provider structure. This structure must be available all the time
*							(better put it in static data). And all member interfaces of this structure
*							should be properly set and implemented.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDF_SetGlyphProvider(FPDF_GLYPHPROVIDER* pProvider);

/**
* Make use of a system font. The font file must be in TrueType or Type1 format and must be
* encoded in a standard encoding system.
* Available for embedded Linux system only.
* @param[in] file_path	-	The full path of the font file.
* @retval	Non-zero for success. Zero for error.
*
*/
DLLEXPORT int STDCALL FPDF_SetSystemFontFile(FPDF_BYTESTRING file_path);



/**
* Get first child of a bookmark item, or first top level bookmark item.
* @param[in] document -	Handle to the document. Returned by FPDF_LoadDocument or FPDF_LoadMemDocument.
* @param[in] bookmark -	Handle to the current bookmark. Can be NULL if you want to get the first top level item.
* @retval Handle to the first child or top level bookmark item. NULL if no child or top level bookmark found.
*/
DLLEXPORT FPDF_BOOKMARK STDCALL FPDFBookmark_GetFirstChild(FPDF_DOCUMENT document, FPDF_BOOKMARK bookmark);


/**
* Get next bookmark item on the same level.
* @param[in] document -	Handle to the document. Returned by FPDF_LoadDocument or FPDF_LoadMemDocument.
* @param[in] bookmark -	Handle to the current bookmark. Cannot be NULL.
* @retval Handle to the next bookmark item on the same level. NULL if this is the last bookmark on this level.
*/
DLLEXPORT FPDF_BOOKMARK STDCALL FPDFBookmark_GetNextSibling(FPDF_DOCUMENT document, FPDF_BOOKMARK bookmark);


/**
* Find a bookmark in the document, using the bookmark title.
* @param[in] document	-	Handle to the document. Returned by FPDF_LoadDocument or FPDF_LoadMemDocument.
* @param[in] title		-	The UTF-16LE encoded Unicode string for the bookmark title to be searched. Can't be NULL.
* @note It always returns the first found bookmark if more than one bookmarks have the same title.
* @retval Handle to the found bookmark item. NULL if the title can't be found.
*/
DLLEXPORT FPDF_BOOKMARK STDCALL FPDFBookmark_Find(FPDF_DOCUMENT document, FPDF_WIDESTRING title);


/**
* Get designated color of a bookmark item.
* @param[in] bookmark -	Handle to the bookmark.
* @retval A COLORREF value (0x00ggbbrr) for the bookmark item.
*/
DLLEXPORT unsigned long STDCALL FPDFBookmark_GetColorRef(FPDF_BOOKMARK bookmark);


/** 
* @name Bookmark font styles
*@{
*/
/**  @brief NORMAL */
#define PDFBOOKMARK_NORMAL			0
/**  @brief ITALIC */
#define PDFBOOKMARK_ITALIC			1
/**  @brief BOLD */
#define PDFBOOKMARK_BOLD			2
/**  @brief BOLD ITALIC */
#define PDFBOOKMARK_BOLDITALIC		3
/**@}*/

/**
* Get designated font style for a bookmark item.
* @param[in] bookmark -	Handle to the bookmark.
* @retval A number indicating the font style, as the bookmark font styles.
*/
DLLEXPORT unsigned long STDCALL FPDFBookmark_GetFontStyle(FPDF_BOOKMARK bookmark);


/**
* Get title of a bookmark.
* @param[in] bookmark	-	Handle to the bookmark.
* @param[out] buffer	-	A buffer for output the title. Can be NULL.
* @param[in] buflen		-	The length of the buffer, number of bytes. Can be 0..
* @note No matter on what platform, the title is always output in UTF-16LE encoding, which means the buffer 
* 		can be regarded as an array of WORD (on Intel and compatible CPUs), each WORD represent the Unicode of 
* 		a character (some special Unicode may take 2 WORDs). The string is followed by two bytes of zero 
* 		indicating end of the string.
* 
* 		The return value always indicated number of bytes required for the buffer, even when there is
* 		no buffer specified, or the buffer size is less then required. In this case, the buffer will not
* 		be modified.
* @retval Number of bytes the title consumes, including trailing zeros.
*/
DLLEXPORT unsigned long STDCALL FPDFBookmark_GetTitle(FPDF_BOOKMARK bookmark, void* buffer, unsigned long buflen);


/**
* Get the action associated with a bookmark item.
* @param[in] bookmark -	Handle to the bookmark.
* @retval Handle to the action data. NULL if no action is associated with this bookmark. In this case, the 
*		  application should try FPDFBookmark_GetDest.
*/
DLLEXPORT FPDF_ACTION STDCALL FPDFBookmark_GetAction(FPDF_BOOKMARK bookmark);


/**
* Get the destination associated with a bookmark item.
* @param[in] document -	Handle to the document.
* @param[in] bookmark -	Handle to the bookmark.
* @retval Handle to the destination data. NULL if no destination is associated with this bookmark.
*/
DLLEXPORT FPDF_DEST STDCALL FPDFBookmark_GetDest(FPDF_DOCUMENT document, FPDF_BOOKMARK bookmark);


/**
* Get first text line of the page, which can be used for alternative bookmark,
* if no bookmark is available.
* @param[in]  page		-	The page handle.
* @param[out] buffer	-	A buffer for output the text. Can be NULL.
* @param[in]  buflen	-	The length of the buffer, number of bytes. Can be 0.
* @note No matter on what platform, the title is always output in UTF-16LE encoding, which means the buffer 
*		can be regarded as an array of WORD (on Intel and compatible CPUs), each WORD represent the Unicode of 
*		a character (some special Unicode may take 2 WORDs). The string is followed by two bytes of zero 
*		indicating end of the string.
*
*		The return value always indicated number of bytes required for the buffer, even when there is
*		no buffer specified, or the buffer size is less then required. In this case, the buffer will not
*		be modified.
*		
*		TEMPORARY FUNCTION WILL BE OBSOLETE SOON!
* @retval Number of bytes the text line consumes, including trailing zeros.
*/
DLLEXPORT int STDCALL FPDFBookmark_GetPageFirstLine(FPDF_PAGE page, void* buffer, int buflen);

/** 
* @name Action styles
*@{
*/
/** @brief Unsupported action type. */
#define PDFACTION_UNSUPPORTED		0		
/** @brief Go to a destination within current document. */
#define PDFACTION_GOTO				1		 
/** @brief Go to a destination within another document. */
#define PDFACTION_REMOTEGOTO		2		 
/** @brief Universal Resource Identifier, including web pages and other Internet based resources. */
#define PDFACTION_URI				3		 
/** @brief Launch an application or open a file.*/
#define PDFACTION_LAUNCH			4		 
/**@}*/

/**
* Get type of an action.
* @param[in] action -	Handle to the action.
* @retval A type number as the action styles.
*/
DLLEXPORT unsigned long STDCALL FPDFAction_GetType(FPDF_ACTION action);


/**
* Get file path of a remote goto action.
* @param[in]  action	-	Handle to the action. Must be a RMEOTEGOTO or LAUNCH action.
* @param[out] buffer	-	A buffer for output the path string. Can be NULL.
* @param[in]  buflen	-	The length of the buffer, number of bytes. Can be 0.
* @note The file path is output in local encoding.
*		The return value always indicated number of bytes required for the buffer, even when there is
*		no buffer specified, or the buffer size is less then required. In this case, the buffer will not
*		be modified.
* @retval Number of bytes the file path consumes, including trailing zero.
*/
DLLEXPORT unsigned long STDCALL FPDFAction_GetFilePath(FPDF_ACTION action, void* buffer, unsigned long buflen);


/**
* Get destination of an action.
* @param[in] document -	Handle to the document..
* @param[in] action -	Handle to the action. It must be a GOTO or REMOTEGOTO action.
* @note In case of remote goto action, the application should first use FPDFAction_GetFilePath to
*		get file path, then load that particular document, and use its document handle to call this
*		function.
* @retval Handle to the destination data.
*/
DLLEXPORT FPDF_DEST STDCALL FPDFAction_GetDest(FPDF_DOCUMENT document, FPDF_ACTION action);



/**
* Get URI path of a URI action.
* @param[in]  document	-	Handle to the document.
* @param[in]  action	-	Handle to the action. Must be a URI action.
* @param[out] buffer	-	A buffer for output the path string. Can be NULL.
* @param[in]  buflen	-	The length of the buffer, number of bytes. Can be 0.
* @note The URI path is always encoded in 7-bit ASCII.
*		The return value always indicated number of bytes required for the buffer, even when there is
*		no buffer specified, or the buffer size is less then required. In this case, the buffer will not
*		be modified.
* @retval Number of bytes the URI path consumes, including trailing zeros.
*/
DLLEXPORT unsigned long STDCALL FPDFAction_GetURIPath(FPDF_DOCUMENT document, FPDF_ACTION action, 
													  void* buffer, unsigned long buflen);



/**
* Get page index of a destination.
* @param[in] document	-	Handle to the document.
* @param[in] dest		-	Handle to the destination.
* @retval The page index. Starting from 0 for the first page.
*/
DLLEXPORT unsigned long STDCALL FPDFDest_GetPageIndex(FPDF_DOCUMENT document, FPDF_DEST dest);

/** 
* @name Zoom modes
*@{
*/
/** @brief Zoom level with specified offset. */
#define PDFZOOM_XYZ				1			 
/** @brief Fit both the width and height of the page (whichever smaller). */
#define PDFZOOM_FITPAGE			2			 
/** @brief Fit the page width. */
#define PDFZOOM_FITHORZ			3			 
/** @brief Fit the page height. */
#define PDFZOOM_FITVERT			4			
/** @brief Fit a specific rectangle area within the window. */
#define PDFZOOM_FITRECT			5		
/** @brief Fit the bounding box entirely within the window both horizontally and vertically. */	 
#define PDFZOOM_FITBBOX			6			
/** @brief The contents of the page magnified just enough to fit the entire width of its bounding box within the window.*/
#define PDFZOOM_FITBHORZ		7
/** @brief The contents of the page magnified just enough to fit the entire height of its bounding box within the window.*/
#define PDFZOOM_FITBVERT		8			
/**@}*/

/**
* Get the designated zoom mode of a destination.
* @param[in] dest -	Handle to the destination.
* @retval A type number as the zoom modes.
*/
DLLEXPORT unsigned long STDCALL FPDFDest_GetZoomMode(FPDF_DEST dest);


/**
* Get zoom parameters.
* @param[in] dest	-	Handle to the destination.
* @param[in] param	-	Index of the parameter, starting with zero (see comments below).
* @note	Different zoom mode has different parameters. Here is a list:
*		XYZ				Three parameters: x, y position in the page and the zoom ratio (0 for not specified).
*		FITPAGE			No parameters;
*		FITHORZ			One parameter: the top margin of the page.
*		FITVERT			One parameter: the left margin of the page.
*		FITRECT			Four parameters: the left, top, right, bottom margin of the fitting rectangle.
*						Use 0-3 as parameter index for them, respectively.
* @retval A float number for the zoom parameter.
*/
DLLEXPORT double STDCALL FPDFDest_GetZoomParam(FPDF_DEST dest, int param);



/**
* Find a link at specified point on a document page.
* @param[in] page	-	Handle to the document page.
* @param[in] x		-	The x coordinate of the point, specified in page coordinate system.
* @param[in] y		-	The y coordinate of the point, specified in page coordinate system.
* @note	The point coordinates are specified in page coordinate system. You can convert coordinates 
*		from screen system to page system using FPDF_DeviceToPage functions.
* @retval Handle to the link. NULL if no link found at that point.
*/
DLLEXPORT FPDF_LINK STDCALL FPDFLink_GetLinkAtPoint(FPDF_PAGE page, double x, double y);



/**
* Get destination info of a link.
* @param[in] document	-	Handle to the document.
* @param[in] link		-	Handle to the link. Returned by FPDFLink_GetLinkAtPoint.
* @retval Handle to the destination. NULL if there is no destination associated with the link, in this case
*		  the application should try FPDFLink_GetAction.
*/
DLLEXPORT FPDF_DEST STDCALL FPDFLink_GetDest(FPDF_DOCUMENT document, FPDF_LINK link);


/**
* Get action info of a link.
* @param[in] link -	Handle to the link.
* @retval	Handle to the action. NULL if there is no action associated with the link.
*/
DLLEXPORT FPDF_ACTION STDCALL FPDFLink_GetAction(FPDF_LINK link);

#ifdef _WIN32

/**
* Get stored thumbnail image of a page. Only supported on Windows system.
* @param[in] page -	Handle to a page.
* @note	If no thumbnail is stored for a page, the application can render the page into a small bitmap for thumbnail.
*		The application should free the image with DeleteObject WIN32 function, when it's done with the thumbnail.
*		NOTE: This function is not supported on Windows CE.
* @retval	Handle to a Windows bitmap storing the thumbnail. NULL if no thumbnail is stored for this page.
*/
DLLEXPORT HBITMAP STDCALL FPDF_GetPageThumbnail(FPDF_PAGE page);
#endif



/**
* Get a text from meta data of the document. Result is encoded in UTF-16LE.
* @param[in]  doc		- Handle to a document
* @param[in]  tag		- The tag for the meta data. Currently, It can be "Title", "Author", 
*							"Subject", "Keywords", "Creator", "Producer", "CreationDate", or "ModDate".
*							For detailed explanation of these tags and their respective values,
*							please refer to PDF Reference 1.6, section 10.2.1, "Document Information Dictionary".
* @param[out] buffer	- A buffer for output the title. Can be NULL.
* @param[in]  buflen	- The length of the buffer, number of bytes. Can be 0.
* @note	No matter on what platform, the title is always output in UTF-16LE encoding, which means the buffer 
*		can be regarded as an array of WORD (on Intel and compatible CPUs), each WORD represent the Unicode of 
*		a character (some special Unicode may take 2 WORDs). The string is followed by two bytes of zero 
*		indicating end of the string.
*
*		The return value always indicated number of bytes required for the buffer, even when there is
*		no buffer specified, or the buffer size is less then required. In this case, the buffer will not
*		be modified.
* @retval Number of bytes the title consumes, including trailing zeros.
*/
DLLEXPORT unsigned long STDCALL FPDF_GetMetaText(FPDF_DOCUMENT doc, FPDF_BYTESTRING tag,
												 void* buffer, unsigned long buflen);




#ifdef _WIN32_WCE


/** @brief  For Windows Mobile Only:
*			An interface for mapping PDF fonts to system fonts on Windows mobile.
*			Used for Chinese/Japanese/Korean fonts only.
*			By default, FPDFSDK picks the system default font for particular character sets. If your 
*			system has more than one fonts installed for a particular character set, you can build a 
*			font mapper structure and call FPDF_SetWCEFontMapper function to set to FPDFSDK engine. 
*			This will allow FPDFSDK to pick different fonts for different styles.
*			Any of the following interfaces can be NULL, then default implementation will be used.
*/
typedef struct {
	/**
	* Get a font identifier number for a particular font, from its name and character set.
	* If the system supports more than one font for a particular character set, the implementation
	* should assign different identifier number for each of the fonts supported. For example,
	* assign 0 to the default font, 1 for an alternative font, etc.
	* @param[in] name		-	Zero-terminated byte string name for the font. This is the name used in
	*							PDF document. The implementation can analyze the name and try to figure out
	*							font style. For example, if the name contains "Gothic", it indicates a bold 
	*							style in Japanese font.
	* @param[in] charset	-	Windows charset identifier, like GB2312_CHARSET, SHIFTJIS_CHARSET. See
	*							MSDN document for CreateFont function.
	* @retval	An identifier number between 0 and 255 (within one byte range).
	*		FPDFSDK will use this return value in GetFontById interface.
	*
	*/
	int (*MapFontId)(FPDF_BYTESTRING name, int charset);

	/**
	* Get face name of the font by its identifier (returned by MapFontId interface).
	* @param[in] buffer		-	An output buffer used to hold unicode name of the font face. It must be
	*							terminated by NULL character (unicode 0).
	* @param[in] size		-	Size of the buffer (number of characters, including the terminator)
	* @param[in] charset	-	Windows charset identifier, like GB2312_CHARSET, SHIFTJIS_CHARSET. See
	*							MSDN document for CreateFont function.
	* @param[in] font_id	-	The font id returned by MapFontId interface.
	* @retval	None.
	*
	*/
	void (*GetFontById)(unsigned short* buffer, int size, int charset, int font_id);
	
	/**
	* Substitute a unicode to be displayed with another one within the font,
	* if the unicode to be displayed doesn't exist in the font.
	* @param[in] font_id	-	The font id returned by MapFontId interface.
	* @param[in] unicode	-	Unicode to be displayed.
	* @retval	If the unicode to be displayed doesn't exist in the font, implementation should
	*			return a unicode that exists in the font, for same or similar character.
	*			Otherwise, the original unicode should be returned.
	*/
	unsigned short (*SubstUnicode)(int font_id, unsigned short unicode);
} FPDF_WCEFONTMAPPER;

/**
* For Windows Mobile Only: make use of a font mapper for CJK charsets.
* This function should be called before page rendering.
* @param[in] mapper		-	Pointer to the mapper structure.
* @retval	None.
*
*/
DLLEXPORT void STDCALL FPDF_SetWCEFontMapper(FPDF_WCEFONTMAPPER* mapper);





/** 
* @name OOM struct
*/
/**@{*/
typedef	struct _OOM_INFO
{

	/** 
	* @brief Version number of the interface. Currently must be 1.
	*/
	int version;
	
	/**
	* Out-Of-Memory handling function.
	* @param[in] pThis		-	Pointer to the interface structure itself.
	* @retval None.
	*/
	void(*FSDK_OOM_Handler)(_OOM_INFO* pThis);
}OOM_INFO;


/**@}*/
/**
* Setup an Out-Of-Memory handler for foxit sdk. 
* @param[in] oomInfo	-	Pointer to a OOM_INFO structure.
* @retval TRUE means successful. FALSE means fails. 
**/
DLLEXPORT FPDF_BOOL STDCALL FSDK_SetOOMHandler(OOM_INFO* oomInfo);


#endif	///< _WIN32_WCE

#ifdef __cplusplus
};
#endif

#endif 
///< _FPDFVIEW_H_
/** @} */
