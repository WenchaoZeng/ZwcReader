/**
 * @addtogroup FPDFEDITBASE
 * Header file for the Ebase module
 * @{
 */


 /** (C) 2011 Foxit Corporation. All Rights Reserved.
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
 * Functions in this header file, require "Ebase" module to be enabled in your SDK license.
 * \file
 * \author	Foxit Corporation
 * \brief	Header file for the Ebase module - provides the base functions for document editing.
 * \note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please
 *		explicitly request for enabling Ebase module.
 * \version 	3.1
*/



#ifndef _FPDFEDITBASE_H_
#define _FPDFEDITBASE_H_
#include "fpdfview.h"
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
typedef unsigned char			FX_BYTE;
typedef unsigned long			FX_DWORD;
#define FPDF_ARGB(a,r,g,b)		((((FX_DWORD)(((FX_BYTE)(b)|((FX_WORD)((FX_BYTE)(g))<<8))|(((FX_DWORD)(FX_BYTE)(r))<<16)))) | (((FX_DWORD)(FX_BYTE)(a))<<24))
#define FPDF_GetBValue(argb)    ((FX_BYTE)(argb))
#define FPDF_GetGValue(argb)    ((FX_BYTE)(((FX_DWORD)(argb)) >> 8))
#define FPDF_GetRValue(argb)    ((FX_BYTE)((argb)>>16))
#define FPDF_GetAValue(argb)    ((FX_BYTE)((argb)>>24))


#ifndef UNICODE
	#define FPDF_SetMetaText				FPDF_SetMetaTextA
	#define FPDF_VIEWERREF_SetUI			FPDF_VIEWERREF_SetUIA
	#define FPDF_VIEWERREF_PrintScaling		FPDF_VIEWERREF_PrintScalingA
	#define FPDFAction_SetFilePath			FPDFAction_SetFilePathA
	#define FPDFBookmark_AddBookmark		FPDFBookmark_AddBookmarkA
	#define FPDFBookmark_SetTitle			FPDFBookmark_SetTitleA
#else
	#define FPDF_SetMetaText				FPDF_SetMetaTextW
	#define FPDF_VIEWERREF_SetUI			FPDF_VIEWERREF_SetUIW
	#define FPDF_VIEWERREF_PrintScaling		FPDF_VIEWERREF_PrintScalingW
	#define FPDFAction_SetFilePath			FPDFAction_SetFilePathW
	#define FPDFBookmark_AddBookmark		FPDFBookmark_AddBookmarkW
	#define FPDFBookmark_SetTitle			FPDFBookmark_SetTitleW
#endif


/**
* Creates a new PDF document.
* @retval	A handle to a document. If failed, NULL is returned.
*/
DLLEXPORT FPDF_DOCUMENT STDCALL FPDF_CreateNewDocument();



/**
* @name PDF document permissions, according to PDF Reference, Table 3.20
*@{
*/
/** @brief bit 3. Print the document. */
#define FPDF_PERM_PRINT				0x0004
/** @brief bit 4. Modify the contents of the document by operations other than those controlled by bits 6, 9, and 11. */
#define FPDF_PERM_MODIFY			0x0008
/** @brief bit 5. Copy or otherwise extract text and graphics from the document by operations other than that is controlled by bit 10.*/
#define FPDF_PERM_EXTRACT			0x0010
/** @brief bit 6. Add or modify text annotations and fill in interactive form fields.If bit 4 is also set, create or modify interactive form fields */
#define FPDF_PERM_ANNOT_FORM		0x0020
/** @brief bit 9. Fill in existing interactive form fields (including signature fields), even if bit 6 is clear. */
#define FPDF_PERM_FILL_FORM			0x0100
/** @brief bit 10. Extract text and graphics. */
#define FPDF_PERM_EXTRACT_ACCESS	0x0200
/** @brief bit 11. Assemble the document, even if bit 4 is clear.*/
#define FPDF_PERM_ASSEMBLE			0x0400
/** @brief bit 12. Print the document to a representation, which a faithful digital copy of the PDF content could be generated.*/
#define FPDF_PERM_PRINT_HIGH		0x0800
/**@}*/



/**
* Saves the specified document with a new name or format.
* @param[in] document		- Handle to a document. Returned by FPDF_LoadDocument and FPDF_CreateNewDocument.
* @param[in] file_name		- The path of PDF file that is different from the currently opened file path(including extension).//这句话和原来的2.0不一样，确认下
* @param[in] permissions	- The PDF document permissions defined above.
* @param[in] UserPwd		- A 32-byte string user's password. Could be NULL.
* @param[in] nUserPwdLen	- The length of the UserPwd.
* @param[in] OwnerPwd		- A 32-byte string owner's password. Could be NULL.
* @param[in] nOwnerPwdLen	- The length of the OwnerPwd.
* @note		The new file_name should be different from the old one.
* @retval	TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_SaveAsFile(FPDF_DOCUMENT document, char* file_name,
											FPDF_DWORD permissions,
											FPDF_LPCBYTE UserPwd, long nUserPwdLen,
											FPDF_LPCBYTE OwnerPwd, long nOwnerPwdLen);



/** @brief Structure for custom file write
*/
struct FPDF_FILEWRITE{

	/**
	* @brief  Version number of the interface. Currently, it must be 1.
	*/
	int version;

	/**
	* Output a block of data in your custom way.
	* @param[out] pThis	- Pointer to the structure itself
	* @param[out] pData	- Pointer to a outputted buffer.
	* @param[in]  size	- The size of the buffer.
	* @retval Should be non-zero if successful, zero for error.
	*/
	int (CDECL *WriteBlock)( FPDF_FILEWRITE* pThis, const void* pData, unsigned long size);
	
};


/** @brief Incremental. */
#define FPDF_INCREMENTAL		1
/** @brief No Incremental. */
#define FPDF_NO_INCREMENTAL		2





/**
* Saves the specified document in a custom way.
* @param[in] document		- Handle to a document. Returned by FPDF_LoadDocument and FPDF_CreateNewDocument.
* @param[in] pFileWrite		- A pointer to a custom file write structure.
* @param[in] permissions	- The PDF document permissions that is defined above.
* @param[in] UserPwd		- A 32-byte string user's password. Could be NULL.
* @param[in] nUserPwdLen	- The length of the UserPwd.
* @param[in] OwnerPwd		- A 32-byte string owner's password. Could be NULL.
* @param[in] nOwnerPwdLen	- The length of the OwnerPwd.
* @param[in] flags			- The creating flags.The values are defined above.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_SaveDocument( FPDF_DOCUMENT document,FPDF_FILEWRITE * pFileWrite,
											   FPDF_DWORD permissions,
											   FPDF_LPCBYTE UserPwd, long nUserPwdLen,
											   FPDF_LPCBYTE OwnerPwd, long nOwnerPwdLen,
											   FPDF_DWORD flags);




/**
* Saves the copy of a specified document in custom way.
* @param[in] document		- Handle to a document. Returned by FPDF_LoadDocument and FPDF_CreateNewDocument.
* @param[in] pFileWrite		- A pointer to a custom file write structure.
* @param[in] flags			- A creating flags.The values are defined above.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_SaveAsCopy( FPDF_DOCUMENT document,FPDF_FILEWRITE * pFileWrite,
											 FPDF_DWORD flags );



/**
* Sets PDF document info
* @param[in] document	- Handle to a document returned by FPDF_loadDocument.
* @param[in] tag		- The key string of the document info. It could be "Title","Subject","Author",
*			  			  "Keywords","Creator" and other document information string.
* @param[in] value		- The information the user want to set it to.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_SetMetaTextA(FPDF_DOCUMENT document,FPDF_BYTESTRING tag,FPDF_BYTESTRING value);

DLLEXPORT FPDF_BOOL STDCALL FPDF_SetMetaTextW(FPDF_DOCUMENT document,FPDF_WIDESTRING tag,FPDF_WIDESTRING value);


/**
* @name Flags for Page Boundary
*@{
*/
/** @brief The visible rectangle.*/
#define FPDF_RECT_PAGE				0
/** @brief The bounding box of the all object in this page.*/
#define FPDF_RECT_BOUNDING			1
/** @brief The boundaries of the physical medium on which the page is to be printed.*/
#define FPDF_RECT_MEDIABOX			2
/** @brief The region to which the contents of the page are to be clipped (cropped) when displayed or printed. */
#define FPDF_RECT_CROPBOX			3
/** @brief The region to which the contents of the page should be clipped when output in a production environment. */
#define FPDF_RECT_TRIMBOX			4
/** @brief The intended dimensions of the finished page after trimming. */
#define FPDF_RECT_ARTBOX			5
/** @brief The extent of the page's meaningful content (including potential white space) as intended by the page's creator.*/
#define FPDF_RECT_BLEEDBOX			6
/**@}*/




/**
* Gets viewer preference information
* @param[in] doc	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] tag	- Flag bit, can be "HideToolbar", "HideMenubar", "HideWindowUI", "FitWindow", "CenterWindow" and other characters info
* @retval Return the specified tag value.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_GetUIA(FPDF_DOCUMENT document,FPDF_BYTESTRING tag);


DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_GetUIW(FPDF_DOCUMENT document,FPDF_BYTESTRING tag);


/**
* Sets viewer preference info.
* @param[in] document	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] tag		- Flag bit, can be "HideToolbar", "HideMenubar", "HideWindowUI", "FitWindow", "CenterWindow" and other characters info.
* @param[in] value		- Setting value.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_SetUIA(FPDF_DOCUMENT document,FPDF_BYTESTRING tag,FPDF_BOOL value);

DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_SetUIW(FPDF_DOCUMENT document,FPDF_WIDESTRING tag,FPDF_BOOL value);

/**
* Sets the area range of displaying page.
* @param[in] document	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] value		- Set the boundary of the printing page.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_ViewArea(FPDF_DOCUMENT document,int nRectType);


/**
* Gets the page number of the printing pages.
* @param[in] doc	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] form	- Get the start page.
* @param[in] to		- Get the end page.
* @retval None
*/
DLLEXPORT void STDCALL FPDF_VIEWERREF_GetPrintPageRange(FPDF_DOCUMENT document,int* from,int* to);


/**
* Sets the printing page number of the document.
* @param[in] document		- Handle to a document returned by FPDF_loadDocument function.
* @param[in] printPageRange	- Page number range. Negative is invalid.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_SetPrintPageRange(FPDF_DOCUMENT document,int from,int to);




/**
* Gets the number of the printing pages.
* @param[in] document   - Handle to a document returned by FPDF_loadDocument function.
* @retval Return the setting number of printing pages.
*/
DLLEXPORT int STDCALL FPDF_VIEWERREF_GetNumCoipes(FPDF_DOCUMENT document);


/**
* Sets the printing quantity.
* @param[in] document	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] value		- Quantity value.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_SetNumCoipes(FPDF_DOCUMENT document,int value);


/**
* Gets the cutting area of the printing page.
* @param[in] doc   - Document returned by FPDF_loadDocument function.
* @retval Return the cutting area's type of the printing page. The type value is defined by the viewer reference above.
*/
DLLEXPORT int STDCALL FPDF_VIEWERREF_GetPrintClip(FPDF_DOCUMENT document);



/**
* Sets the cutting area of the printing page. The name of the page boundary to which the contents of a page are to be clipped when printing the document.
* @param[in] document	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] nRectType	- Set the type of cutting area defined by the viewer reference above.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_SetPrintClip(FPDF_DOCUMENT document,int nRectType);


/**
* Sets the zoom proportion of print.
* @param[in] document	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] value		- Set as None or AppDefault that is supported by the application.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_PrintScalingA(FPDF_DOCUMENT document,FPDF_BYTESTRING value);

DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_PrintScalingW(FPDF_DOCUMENT document,FPDF_WIDESTRING value);


/**
* Gets the printing area range.
* @param[in] doc - Handle to a document returned by FPDF_loadDocument function.
* @retval Return the setting area range's type of printing. The type value is defined by the viewer reference above.
*/
DLLEXPORT int STDCALL FPDF_VIEWERREF_GetPrintArea(FPDF_DOCUMENT document);


/**
* Sets the printing area range.
* @param[in] document	- Handle to a document returned by FPDF_loadDocument function.
* @param[in] nRectType	- The type of page boundary. The values are defined above.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_VIEWERREF_SetPrintArea(FPDF_DOCUMENT document,int nRectType);


/**
* @name Flags for Action type
*@{
*/
/** @brief Unsupported action type.*/
#define PDFACTION_UNSUPPORTED		0
/** @brief Go to a destination within current document.*/
#define PDFACTION_GOTO				1
/** @brief Go to a destination within another document.*/
#define PDFACTION_REMOTEGOTO		2
/** @brief Universal Resource Identifier, including web pages and other Internet based resources.*/
#define PDFACTION_URI				3
/** @brief Launch an application or open a file.*/
#define PDFACTION_LAUNCH			4
/**@}*/


/**
* Creates an action.
* @param[in] document	- Handle to a document that will contains the action.
* @param[in] actiontype - The type of the action. The values are defined above.
* @retval Handle to a action or NULL if an error occurs.
*/
DLLEXPORT FPDF_ACTION STDCALL FPDF_CreateAction(FPDF_DOCUMENT document,int actiontype);



/**
* Deletes an action.
* @param[in] action - Handle to a action.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDF_DeleteAction(FPDF_ACTION action);



/**
* Sets the file path of action. The path can be URL.
* @param[in] action		- Handle to a action.
* @param[in] pFilePath	- File path.
* @param[in] bURL		- Whether the path is URL.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFAction_SetFilePathA(FPDF_ACTION action,FPDF_BYTESTRING pFilePath,FPDF_BOOL bURL);

DLLEXPORT FPDF_BOOL STDCALL FPDFAction_SetFilePathW(FPDF_ACTION action,FPDF_WIDESTRING pFilePath,FPDF_BOOL bURL);




/**
* Sets the URI path of Action
* @param[in] action		- Handle to a action.
* @param[in] pFilePath	- URL address.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFAction_SetURI(FPDF_ACTION action, FPDF_BYTESTRING csURI);


/**
* Gets the URI path of Action.
* @param[in]  action	- Handle to a action.
* @param[out] buffer	- The buffer that will contain URL.
* @param[in]  buflen	- The length of URL path.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT unsigned long STDCALL FPDFAction_GetURI(FPDF_DOCUMENT document,FPDF_ACTION action, void* buffer, unsigned long buflen);



/**
* Sets the type of action's destination.
* @param[in]  action	- Handle to a action.
* @param[out] dest		- Handle to a destination, returned by FPDF_CreateDest.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFAction_SetDest(FPDF_ACTION action, FPDF_DEST dest);



/**
* @name Flags for zoom modes
*@{
*/
/** @brief Zoom level with specified offset.*/
#define PDFZOOM_XYZ				1
/** @brief Fit both the width and height of the page (whichever smaller).*/
#define PDFZOOM_FITPAGE			2
/** @brief Fit the page width.*/
#define PDFZOOM_FITHORZ			3
/** @brief Fit the page height.*/
#define PDFZOOM_FITVERT			4
/** @brief Fit a specific rectangle area within the window.*/
#define PDFZOOM_FITRECT			5
/** @brief Fit the bounding box entirely within the window both horizontally and vertically. */
#define PDFZOOM_FITBBOX			6
/** @brief The contents of the page magnified just enough to fit the entire width of its bounding box within the window.*/
#define PDFZOOM_FITBHORZ		7
/** @brief The contents of the page magnified just enough to fit the entire height of its bounding box within the window.*/
#define PDFZOOM_FITBVERT		8
/**@}*/



/**
* Sets the page pointed by destination.
* @param[in] document	- Handle to a document returned by FPDF_LoadDocument or FPDF_LoadMemDocument.
* @param[in] dest		- Handle to a destination.
* @param[in] page_index - Page number.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetPageIndex(FPDF_DOCUMENT document, FPDF_DEST dest, int page_index);




/**
* Creates destination.
* @param[in] mode - The mode of destination. Refer to the fpdfdoc.h, the definition of zoom mode.
* @retval Handle to a destination or NULL if an error occurs.
*/
DLLEXPORT FPDF_DEST   STDCALL FPDF_CreateDest(int mode);


/**
* Deletes destination.
* @param[in] dest - Handle to the destination returned by the FPDF_CreateDest.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL   STDCALL FPDF_DeleteDest(FPDF_DEST dest);



/**
* Sets the zoom mode.
* @param[in] dest - Handle to the destination returned by FPDF_CreateDest.
* @param[in] mode - The zoom mode of destination. Refer to the fpdfview.h, the definition of zoom mode.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetZoomMode(FPDF_DEST dest, int mode);




/**
* Sets the parameters of xyz zoom mode.
* @param[in] dest	- Handle to the destination returned by FPDF_CreateDest.
* @param[in] x		- Left coordinate point
* @param[in] y		- Top coordinate point
* @param[in] z		- Zooming value
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetXYZParam(FPDF_DEST dest,double x,double y,double z);




/**
* Sets the parameters for FITHORZ zoom mode.
* @param[in] dest	- Handle to the destination returned by FPDF_CreateDest.
* @param[in] param	- The parameters of the vertical coordinate positioned at the top edge of the window.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetFITHORZParam(FPDF_DEST dest,double param);



/**
* Sets the parameters of FITVERT zoom mode.
* @param[in] dest	- Handle to the destination returned by FPDF_CreateDest.
* @param[in] param	- The parameters of the horizontal coordinate positioned at the left edge of the window
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetFITVERTParam(FPDF_DEST dest,double param);




/**
* Sets the parameters of FitRect zoom mode. The rectangle range consists of left, bottom, right and top.
* @param[in] dest	- Handle to the destination returned by FPDF_CreateDest.
* @param[in] param	- The parameters's contents must be magnified just enough to fit the rectangle specified
*			  		  by the coordinates left, bottom, right and top. Contents must fit entirely within the window both horizontally and vertically.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetFitRectParam(FPDF_DEST dest,double left,double bottom,double right,double top);


/**
* Sets the parameters of FitBHorz zoom mode.
* @param[in] dest	- Handle to the destination returned by FPDF_CreateDest.
* @param[in] param	- The parameters of bounding box.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetFitBHorzParam(FPDF_DEST dest,double param);



/**
* Sets the parameters of FitBV zoom mode.
* @param[in] dest	- Handle to the destination returned by FPDF_CreateDest.
* @param[in] param	- The parameters of the horizontal coordinate positioned at the left edge of the window.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFDest_SetFitBVertParam(FPDF_DEST dest,double param);



/**
* Adds the bookmark to the document.
* @param[in] document		- Handle to a document returned by FPDF_loadDocument function.
* @param[in] parent			- Parent node.
* @param[in] InsterAfter	- Former node.
* @param[in] titlename		- Bookmark name.
* @retval Return the setting bookmark object, if successful. If failed, NULL is returned.
*/
DLLEXPORT FPDF_BOOKMARK STDCALL FPDFBookmark_AddBookmarkA(FPDF_DOCUMENT document, FPDF_BOOKMARK parent,FPDF_BOOKMARK InsterAfter,FPDF_BYTESTRING titlename);

DLLEXPORT FPDF_BOOKMARK STDCALL FPDFBookmark_AddBookmarkW(FPDF_DOCUMENT document, FPDF_BOOKMARK parent,FPDF_BOOKMARK InsterAfter,FPDF_WIDESTRING titlename);




/**
* Deletes the bookmark object
* @param[in] document - Handle to a document returned by FPDF_loadDocument function.
* @param[in] bookmark - Handle to a bookmark.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFBookmark_DeleteBookmark(FPDF_DOCUMENT document,FPDF_BOOKMARK bookmark);


/**
* @name Flags for Bookmark Font Style
*@{
*/
/** @brief Normal typeface */
#define FONTNORMAL			0x00
/** @brief Italic */
#define FONTITALIC			0x01
/** @brief Bold*/
#define FONTBOLD			0x02
/**@}*/


/**
* Sets the bookmark title.
* @param[in] bookmark	- Handle to a bookmark.
* @param[in] titlename	- Title name.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFBookmark_SetTitleA(FPDF_BOOKMARK bookmark,FPDF_BYTESTRING titlename);

DLLEXPORT FPDF_BOOL STDCALL FPDFBookmark_SetTitleW(FPDF_BOOKMARK bookmark,FPDF_WIDESTRING titlename);


/**
* Sets the bookmark color. The color value such as (0xFF00FF).
* @param[in] bookmark	- Handle to a bookmark.
* @param[in] color		- Set color value.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFBookmark_SetColorRef(FPDF_BOOKMARK bookmark,unsigned long color);



/**
* Sets the bookmark font (such as bold, italic and so on).
* @param[in] bookmark	- Handle to a bookmark.
* @param[in] Fontstyle	- Font type defined by the value above.
* @note The bookmark font style such as bold,italic and so on.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFBookmark_SetFontStyle(FPDF_BOOKMARK bookmark,unsigned long fontstyle);



/**
* Sets the action actuation of bookmark.
* @param[in] bookmark	- Handle to a bookmark.
* @param[in] action		- Handle to action.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFBookmark_SetAction(FPDF_BOOKMARK bookmark,FPDF_ACTION action);



/**
* Constructs an empty page.
* @param[in] document	- Handle to a document. Returned by FPDF_LoadDocument and FPDF_CreateNewDocument.
* @param[in] page_index - The index of a page.
* @param[in] width		- The page width.
* @param[in] height		- The page height.
* @note		Loaded page can be deleted by FPDFPage_Delete.
* @retval	The handle to the page.
*/
DLLEXPORT FPDF_PAGE STDCALL FPDFPage_New(FPDF_DOCUMENT document, int page_index, double width, double height);


/**
* Deletes a PDF page.
* @param[in] document	- Handle to a document. Returned by FPDF_LoadDocument and FPDF_CreateNewDocument.
* @param[in] page_index - The index of a page.
* @retval None
*/
DLLEXPORT void STDCALL FPDFPage_Delete(FPDF_DOCUMENT document, int page_index);

/**
* @name Index values for getting boxes, used in xxx_GetRectangle and xxx_GetBBox functions.
*@{
*/
/** @brief The visible rectangle.*/
#define FPDF_RECT_PAGE			0
/** @brief The bounding box of the all object in this page.*/
#define FPDF_RECT_BOUNDING		1
/** @brief The boundaries of the physical medium on which the page is to be printed.*/
#define FPDF_RECT_MEDIABOX		2
/** @brief The region to which the contents of the page are to be clipped (cropped) when displayed or printed. */
#define FPDF_RECT_CROPBOX		3
/** @brief The region to which the contents of the page should be clipped when output in a production environment. */
#define FPDF_RECT_TRIMBOX		4
/** @brief The intended dimensions of the finished page after trimming.  */
#define FPDF_RECT_ARTBOX		5
/** @brief The extent of the page's meaningful content (including potential white space) as intended by the page's creator.*/
#define FPDF_RECT_BLEEDBOX		6
/**@}*/




/**
* Inserts an object to the page. The page object is automatically freed.
* @param[in] page		- Handle to a page. Returned by FPDFPage_New.
* @param[in] page_obj	- Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx or FPDFPageObj_NewPathObj.
* @retval None
*/
DLLEXPORT void STDCALL FPDFPage_InsertObject(FPDF_PAGE page, FPDF_PAGEOBJECT page_obj);


/**
* Deletes an object from the page. The page object is automatically freed.
* @param[in] page	- Handle to a page. Returned by FPDFPage_New.
* @param[in] index	- The index of a page object.
* @retval None
*/
DLLEXPORT void STDCALL FPDFPage_DeleteObject(FPDF_PAGE page, int index);


/**
* Gets number of page objects inside the page.
* @param[in] page - Handle to a page. Returned by FPDFPage_New.
* @retval The number of page objects.
*/
DLLEXPORT int STDCALL FPDFPage_CountObject(FPDF_PAGE page);



/**
* Gets page object by index.
* @param[in] page	- Handle to a page. Returned by FPDFPage_New.
* @param[in] index	- The index of a page object.
* @retval The handle to the page object. If failed, NULL is returned.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPage_GetObject(FPDF_PAGE page, int index);



/**
* Gets the index of the page object in the specify page.
* @param[in] page		- Handle to a page. Returned by FPDFPage_New.
* @param[in] page_obj	- Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx, FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @retval If successful, returns the index of the page object. Otherwise, returns -1.
*/
DLLEXPORT int STDCALL FPDFPage_GetPageObjectIndex(FPDF_PAGE page, FPDF_PAGEOBJECT page_obj);



/**
* Generates PDF Page content.
* @param[in] page	- Handle to a page. Returned by FPDFPage_New.
* @note		Before you save the page to a file, or reload the page, you must call the FPDFPage_GenerateContent function
*			or the changed information will be lost.
* @retval	TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPage_GenerateContent(FPDF_PAGE page);





/**
* Transforms (scale, rotate, shear, move) page object.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*						   FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @param[in] a	- The coefficient "a" of the matrix.
* @param[in] b	- The coefficient "b" of the matrix.
* @param[in] c	- The coefficient "c" of the matrix.
* @param[in] d	- The coefficient "d" of the matrix.
* @param[in] e	- The coefficient "e" of the matrix.
* @param[in] f	- The coefficient "f" of the matrix.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_Transform(FPDF_PAGEOBJECT page_object,
							double a, double b, double c, double d, double e, double f);



/**
* Creates a new page object based on this page object.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*						   FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @retval Handle to a page object.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_Clone(FPDF_PAGEOBJECT page_object);



/**
* Free a page object.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*							FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_Free(FPDF_PAGEOBJECT page_object);


/**
* @name The page object constants.
*@{
*/
/** @brief Text object */
#define FPDF_PAGEOBJ_TEXT		1
/** @brief Path object */
#define FPDF_PAGEOBJ_PATH		2
/** @brief Image object */
#define FPDF_PAGEOBJ_IMAGE		3
/** @brief Shading object */
#define FPDF_PAGEOBJ_SHADING	4
/** @brief From object */
#define FPDF_PAGEOBJ_FORM		5
/**@}*/


/**
* Gets page object type.
* @param[in] page_object  - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*			    FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @retval One of the FPDF_PAGEOBJ_xxxx constants defined above.
*/
DLLEXPORT int STDCALL FPDFPageObj_GetType(FPDF_PAGEOBJECT page_object);


/**
* Gets page object type.
* @param[in] page_object	- Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*				  FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @param[in] left		- Pointer to a double value receiving the left of a rectangle (in points).
* @param[in] bottom		- Pointer to a double value receiving the bottom of a rectangle (in points).
* @param[in] right		- Pointer to a double value receiving the right of a rectangle (in points).
* @param[in] top		- Pointer to a double value receiving the top of a rectangle (in points).
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_GetBBox(FPDF_PAGEOBJECT page_object,
						 double* left, double* bottom, double* right, double* top );

/**
* Gets the clip number of a page object.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*							FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @retval The clip count.
*/
DLLEXPORT int STDCALL FPDFPageObj_GetClipCount(FPDF_PAGEOBJECT page_object);



/**
* Gets the clip path of a page object.
* @param[in] page_object	- Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*				  FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @param[in] index		- The index of a path.
* @retval Handle to a path.
*/
DLLEXPORT FPDF_PATH STDCALL FPDFPageObj_GetClip(FPDF_PAGEOBJECT page_object, int index);



/**
* @name Fill mode types
*@{
*/
/** @brief No fill color.*/
#define FPDF_FILL_NULL			0
/** @brief Represents a fill mode in which the system fills the area between odd-numbered and even-numbered polygon sides on each scan line.*/
#define FPDF_FILL_ALTERNATE		1
/** @brief Represents a fill mode in which the system uses the direction in which a figure was drawn to determine whether to fill the area.*/
#define FPDF_FILL_WINDING		2
/**@}*/



/**
* Adds a clip to a page object.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*			   FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @param[in] path	 - Handle to a path. Returned by FPDFPathObj_GetPath.
* @param[in] type	 - The fill mode types that is defined above.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPageObj_AddClip(FPDF_PAGEOBJECT page_object, FPDF_PATH path, int type);


/**
* Appends a path to the current clip.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*			   FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @param[in] path	 - Handle to a path. Returned by FPDFPathObj_GetPath.
* @param[in] type	 - The fill mode types that is defined above.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPageObj_AppendPathToClip(FPDF_PAGEOBJECT page_object, FPDF_PATH path, int type);



/**
* Removes a clip from the page object.
* @param[in] page_object - Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*			   FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @param[in] index	 	- The index of the clip.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_RemoveClip(FPDF_PAGEOBJECT page_object, int index);


/**
* Gets the fill color of a page object.
* @param[in] page_object	- Handle of a page object. It could be text_object, path_object and uncolored images.
* @retval The fill-color of a page object. Constructed by 0xaarrggbb.
*/
DLLEXPORT FPDF_DWORD STDCALL FPDFPageObj_GetFillColor(FPDF_PAGEOBJECT page_object);



/**
* Sets the fill color of a page object.
* @param[in] page_object	- Handle of a page object. It could be text_object, path_object and uncolored images.
* @param[in] argb			- The fill color of a page object. Constructed by 0xaarrggbb.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetFillColor(FPDF_PAGEOBJECT page_object, FPDF_DWORD argb);


/**
* Gets the stroke color of a page object.
* @param[in] page_object - Handle of a page object. It could be text_object, path_object and uncolored images.
* @retval The stroke color of a page object. Constructed by 0xaarrggbb.
*/
DLLEXPORT FPDF_DWORD STDCALL FPDFPageObj_GetStrokeColor(FPDF_PAGEOBJECT page_object);

/**
* Sets the stroke color of a page object.
* @param[in] page_object - Handle of a page object. It could be text_object, path_object and uncolored images.
* @param[in] argb	- The stroke color of a page object. Constructed by 0xaarrggbb.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetStrokeColor(FPDF_PAGEOBJECT page_object, FPDF_DWORD argb);


/**
* Gets the line width of a path object.
* @param[in] page_object - Handle of a page object. It could be path_object or stroke text_object.
* @retval Return the line width of the page object.
*/
DLLEXPORT double STDCALL FPDFPageObj_GetLineWidth(FPDF_PAGEOBJECT page_object);

/**
* Sets the line width of a path object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] width			- The line width of the page object.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetLineWidth(FPDF_PAGEOBJECT page_object, double width);


/**
* @name Line cap styles
*@{
*/
/** @brief The stroke is squared off at the endpoint of the path. There is no projection beyond the end of the path. */
#define FPDF_LINECAP_BUTT		0
/** @brief A semicircular arc with a diameter equal to the line width is drawn around the endpoint and filled in. */
#define FPDF_LINECAP_ROUND		1
/** @brief The stroke continues beyond the endpoint of the path for a distance equal to half the line width and is squared off. */
#define FPDF_LINECAP_PROJECT	2
/**@}*/

/**
* Gets the line cap style of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @retval The line cap styles defined above.
*/
DLLEXPORT int STDCALL FPDFPageObj_GetLineCapStyle(FPDF_PAGEOBJECT page_object);


/**
* Sets the line cap style of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] style		- The line cap styles defined above.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetLineCapStyle(FPDF_PAGEOBJECT page_object, int style);


/**
* @name Line join styles
*@{
*/
/** @brief The outer edges of the strokes for the two segments are extended  until they meet at an angle*/
#define FPDF_LINEJOIN_MITER		0
/** @brief An arc of a circle with a diameter equal to the line width is drawn around the point where the two segments meet, connecting the outer edges of  the strokes for the two segments. */
#define FPDF_LINEJOIN_ROUND		1
/** @brief  The two segments are finished with butt caps and the resulting notch beyond the ends of the segments is filled with a triangle.  */
#define FPDF_LINEJOIN_BEVEL		2
/**@}*/

/**
* Gets the line join style of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @retval Return the line join styles that is defined above.
*/
DLLEXPORT int STDCALL FPDFPageObj_GetLineJoinStyle(FPDF_PAGEOBJECT page_object);


/**
* Sets the line join style of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] style			- The line join styles that is defined above.
* @retval  None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetLineJoinStyle(FPDF_PAGEOBJECT page_object, int style);


/**
* Gets the miter limit of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @note		The miter limit imposes a maximum on the ratio of the miter length to the line width.
*			When the limit is exceeded, the join is converted from a miter to a bevel.
* @retval	The miter limit of a page_object.
*/
DLLEXPORT double STDCALL FPDFPageObj_GetMiterLimit(FPDF_PAGEOBJECT page_object);


/**
* Sets the miter limit of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] miter_limit	- The miter limit of a page_object.
* @note		The miter limit imposes a maximum on the ratio of the miter length to the line width.
*			When the limit is exceeded, the join is converted from a miter to a bevel.
* @retval   None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetMiterLimit(FPDF_PAGEOBJECT page_object, double miter_limit);


/**
* Gets dash count of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @retval The dash count of a page object.
*/
DLLEXPORT int STDCALL FPDFPageObj_GetDashCount(FPDF_PAGEOBJECT page_object);


/**
* Sets dash count of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] count			- The dash count of a page object.
* @note Setting the count will release the old dash array of the page object and allocate a new dash array.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetDashCount(FPDF_PAGEOBJECT page_object, int count);



/**
* Get dash array elements of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] index			- The index of a dash array element.
* @note	    The dash array's elements are numbers that specify the lengths of alternating dashes and gaps;
*	    the numbers must be nonnegative and not all zero.
* @retval   Return the dash value of the specific index of the dash array.
*/
DLLEXPORT double STDCALL FPDFPageObj_GetDashArray(FPDF_PAGEOBJECT page_object, int index);


/**
* Sets dash array elements of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] index			- The index of a dash array element.
* @param[in] dash_value		- The dash value of specific index of the dash array.
* @note	  The dash array's elements are numbers that specify the lengths of alternating dashes and gaps;
*         the numbers must be nonnegative and not all zero.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetDashArray(FPDF_PAGEOBJECT page_object, int index, double dash_value);


/**
* Gets dash phase of a page object.
* @param[in] page_object	- Handle of a page object. It could be path_object or stroke text_object.
* @note   The dash phase specifies the distance into the dash pattern at which to start the dash.
* @retval The dash phase value of a page object.
*/
DLLEXPORT double STDCALL FPDFPageObj_GetDashPhase(FPDF_PAGEOBJECT page_object);


/**
* Sets dash phase of a page object.
* @param[in] page_object		- Handle of a page object. It could be path_object or stroke text_object.
* @param[in] phase_value		- The dash phase value.
* @note   The dash phase specifies the distance into the dash pattern where you can start the dash.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPageObj_SetDashPhase(FPDF_PAGEOBJECT page_object, double phase_value);


#ifdef __cplusplus
};
#endif


#endif



///< _FPDFEDITBASE_H_
/** @} */