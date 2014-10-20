/**
 * @addtogroup FPDFOBJECTEDIT
 * Header file for the object module
 * @{
 */

 /** (C) 2011 Foxit Corporation. All Rights Reserved.
 * The following code is copyrighted and contains proprietary information and trade secrets of Foxit Corporation.
 * Functions in this header file, require "object" module to be enabled in your SDK license.
 * \file
 * \author	Foxit Corporation
 * \brief	Header file for the object module - provides the interfaces for editing page objects. 
 * \note	If you want to purchase Foxit PDF SDK license and use ANY of the following functions, please
 *       	request for enabling object module explicitly.
 * \version 3.1
*/

#ifndef _FPDFOBJECTEDIT_H_
#define _FPDFOBJECTEDIT_H_

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

#include "fpdfview.h"
#include "fpdfeditbase.h"

/**
* Create a new text Object.
* @retval Handle to the text object.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_NewTextObj();

/**
* Create a new text object.
* @param[in] text		- Pointer to a string that stores the text for the object.
* @param[in] nwSize		- The length of the string.
* @param[in] font		- Handle to a FPDF_FONT object that can be obtained by calling any of the
*						  the following functions: FPDFTextObj_GetFont, FPDFFont_AddTrueType, or 
*						  FPDFFont_AddStandardFont.      
* @retval Handle to the text object or NULL if an error occurs.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_NewTextObjEx(FPDF_WIDESTRING text, int nwSize, FPDF_FONT font);

/**
* Get the font handle of a text object.
* @param[in] text_object	- Handle of the text object returned by FPDFPageObj_NewTextObj or FPDFPageObj_NewTextObjEx.
* @retval Handle of the font.
*/
DLLEXPORT FPDF_FONT STDCALL FPDFTextObj_GetFont(FPDF_PAGEOBJECT text_object);

/**
* Set the font of a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] font			- Handle to a FPDF_FONT object that can be obtained by calling any of the
*							  the following functions: FPDFTextObj_GetFont, FPDFFont_AddTrueType, or 
*							  FPDFFont_AddStandardFont.      
* @param[in] font_size		- The size of the font.  
* @retval None.
*/
DLLEXPORT void STDCALL FPDFTextObj_SetFont(FPDF_PAGEOBJECT text_object, FPDF_FONT font, double font_size);

/**
* Get the font size of a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.		
* @retval The value of the font size.
*/
DLLEXPORT double STDCALL FPDFTextObj_GetFontSize(FPDF_PAGEOBJECT text_object);

/**
* Get the text object matrix.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] a				- Pointer to a double value receiving the coefficient "a" of the matrix.	
* @param[in] b				- Pointer to a double value receiving the coefficient "b" of the matrix.	
* @param[in] c				- Pointer to a double value receiving the coefficient "c" of the matrix.	
* @param[in] d				- Pointer to a double value receiving the coefficient "d" of the matrix.	
* @param[in] e				- Pointer to a double value receiving the coefficient "e" of the matrix.	
* @param[in] f				- Pointer to a double value receiving the coefficient "f" of the matrix.	
* @retval None.
*/
DLLEXPORT void STDCALL FPDFTextObj_GetMatrix(FPDF_PAGEOBJECT text_object,
							double* a, double* b, double* c, double* d, double* e, double* f);

/**
* Set the text object matrix.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] a				- The coefficient "a" of the matrix.
* @param[in] b				- The coefficient "b" of the matrix.
* @param[in] c				- The coefficient "c" of the matrix.
* @param[in] d				- The coefficient "d" of the matrix.
* @param[in] e				- The coefficient "e" of the matrix.
* @param[in] f				- The coefficient "f" of the matrix.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFTextObj_SetMatrix(FPDF_PAGEOBJECT text_object,
							double a, double b, double c, double d, double e, double f);


/**
* Get the number of characters in a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @retval The character count of the text object.
*/
DLLEXPORT int STDCALL FPDFTextObj_CountChars(FPDF_PAGEOBJECT text_object);

/**
* Get the unicode of a specified character in a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] index			- The index of the character to get the unicode value of. 
* @retval The unicode value of the specified character.
*/
DLLEXPORT unsigned int STDCALL FPDFTextObj_GetUincode(FPDF_PAGEOBJECT text_object, int index);

/**
* Set the unicode of a specified character in a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] index			- The index of the character to set unicode value of.
* @param[in] nUnicode		- The unicode value.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFTextObj_SetUnicode(FPDF_PAGEOBJECT text_object,int index, int nUnicode);

/**
* Calculate the physical offset from the start to the specified character. 
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] index			- The index of the character to calculate the offset of.
* @retval Return the offset value.
*/
DLLEXPORT double STDCALL FPDFTextObj_GetOffset(FPDF_PAGEOBJECT text_object, int index);

/** 
* @name Text rendering modes
*@{
*/
/** @brief Fill text.*/
#define  FPDF_TEXTMODE_FILL						0
/** @brief Stroke text. */
#define  FPDF_TEXTMODE_STROKE					1	
/** @brief Fill, then stroke text. */
#define  FPDF_TEXTMODE_FILLANDSTROKE			2
/** @brief Neither fill nor stroke text (invisible). */
#define  FPDF_TEXTMODE_INVISIBLE				3	
/**@}*/


/**
* Get the text rendering mode.
* @param[in] text_object	- Handle to the text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @retval Return one of the enumerated "Text rendering modes".
*/
DLLEXPORT int STDCALL FPDFTextObj_GetTextMode(FPDF_PAGEOBJECT text_object);

/**
* Set the text rendering mode.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] text_mode		- One of the enumerated values defined under "Text rendering modes".
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFTextObj_SetTextMode(FPDF_PAGEOBJECT text_object, int text_mode);

/**
* Get the character spacing value of a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @note   The character spacing value is a number specified in unscaled text space units.
* @retval The character spacing value.
*/
DLLEXPORT double STDCALL FPDFTextObj_GetCharSpace(FPDF_PAGEOBJECT text_object);

/**
* Set the character spacing value of a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] charspace		- The character spacing value. 	
* @note   The character spacing value is a number specified in unscaled text space units. 
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFTextObj_SetCharSpace(FPDF_PAGEOBJECT text_object, double charspace);

/**
* Get the word spacing value of a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	 	
* @note   The word spacing value is a number expressed in unscaled text space units.
* @retval The word spacing value.
*/
DLLEXPORT double STDCALL FPDFTextObj_GetWordSpace(FPDF_PAGEOBJECT text_object);

/**
* Set the word spacing value of a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.	
* @param[in] wordspace		- The word spacing value.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFTextObj_SetWordSpace(FPDF_PAGEOBJECT text_object, double wordspace);


/**
* Insert a substring at the given index within the text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] text			- A pointer to the substring to be inserted.
* @param[in] nwSize			- The length of the substring.
* @param[in] index			- The index of the character before which the insertion will take place.
* @note   The index can be between 0 and the number of characters in a text object. (returned by FPDFTextObj_CountChars).
* @retval Return the length of the modified string. 
*/
DLLEXPORT int STDCALL FPDFTextObj_Insert(FPDF_PAGEOBJECT text_object, FPDF_WIDESTRING text, int nwSize, int index);

/**
* Delete a character or characters in the text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] index			- The index of the first character to delete.
* @param[in] nCount			- The number of characters to be removed.
* @note Call this member function to delete a character or characters from a string starting with the character at index. 
*		If nCount is longer than the string, the remainder of the string will be removed.
* @retval Return the character number of the changed text object.
*/
DLLEXPORT int STDCALL FPDFTextObj_Delete(FPDF_PAGEOBJECT text_object, int index, int nCount = 1);

/**
* Find a substring inside a text object.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] text			- A pointer to a string to search for.
* @param[in] nwSize			- The length of the string.
* @param[in] nStart			- The index of the character in the string to begin the search with, 
*							  or 0 to start from the beginning.
* @retval Return the zero-based index of the first character in this text object that matches the requested 
*		  substring or characters; -1 if the substring or character is not found.
*/
DLLEXPORT int STDCALL FPDFTextObj_Find(FPDF_PAGEOBJECT text_object, FPDF_WIDESTRING text, int nwSize, int nStart = 0);

/**
* Replace a character with another.
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj 
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] OldText		- A pointer to a string containing the character to be replaced by NewText.
* @param[in] nwOldSize		- The length of the old text.
* @param[in] NewText		- A pointer to a string containing the character replacing OldText.
* @param[in] nwNewSize		- The length of the new text.
* @retval Return the number of characters of the changed text object. -1 if the text object isn't changed.
*/
DLLEXPORT int STDCALL FPDFTextObj_Replace(FPDF_PAGEOBJECT text_object, FPDF_WIDESTRING OldText, int nwOldSize, 
											 FPDF_WIDESTRING NewText, int nwNewSize);
											 
/**
* Compare current text object characters with another string. 
* @param[in] text_object	- Handle to a text object returned by FPDFPageObj_NewTextObj  
*							  or FPDFPageObj_NewTextObjEx.
* @param[in] text			- The string used for comparison.
* @param[in] nwSize			- The length of the string.
* @retval TRUE if the texts are identical, and FALSE if they are different.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFTextObj_Compare(FPDF_PAGEOBJECT text_object, FPDF_WIDESTRING text, int nwSize);

/**
* Retrieve the face name of the font and return the name in a string.
* @param[in] font	- Handle to the font object.
* @retval Pointer to the string.
*/
DLLEXPORT FPDF_BYTESTRING STDCALL FPDFFont_GetFontName(FPDF_FONT font);

/** 
* @name The Font flags
*@{
*/
/** @brief All glyphs have the same width.*/
#define FPDF_FLAG_FIXEDPITCH		1				
/** @brief Glyphs have serifs, which are short strokes drawn at an angle on the top and bottom of glyph stems. */
#define FPDF_FLAG_SERIF				2				
/** @brief Font contains glyphs outside the Adobe standard Latin character set. This flag and the Nonsymbolic flag cannot both be set or cleared. */
#define FPDF_FLAG_SYMBOLIC			4				
/** @brief  Glyphs resemble cursive handwriting.*/
#define FPDF_FLAG_SCRIPT			8				 
/** @brief  Font uses the Adobe standard Latin character set or a subset of it. */
#define FPDF_FLAG_NONSYMBOLIC		32				
/** @brief  Glyphs have dominant vertical strokes that are slanted.*/
#define FPDF_FLAG_ITALIC			64				
/** @brief  Font contains no lowercase letters; typically used for display purposes, such as for titles or headlines. */
#define FPDF_FLAG_ALLCAP			0x10000			 
/** @brief  Font contains both uppercase and lowercase letters.*/													 
#define FPDF_FLAG_SMALLCAP			0x20000			 
/** @brief  Whether bold glyphs are painted with extra pixels even at very small text sizes.*/
#define FPDF_FLAG_FORCEBOLD			0x40000			 
/**@}*/

/**
* Get the value of the flags entry in a font descriptor.
* @param[in] font	- Handle to the font object.	
* @note   The value of the flags entry in a font descriptor is an unsigned 32-bit 
*         integer containing flags specifying various characteristics of the font.
* @retval The value of the Flags entry defined above.
*/
DLLEXPORT int STDCALL FPDFFont_GetFlags(FPDF_FONT font);

/**
* Get the font bounding box.
* @param[in] font		- Handle to the font object.	
* @param[in] left		- Pointer to a double value receiving the left of a rectangle (in points).
* @param[in] right		- Pointer to a double value receiving the right of a rectangle (in points).
* @param[in] bottom		- Pointer to a double value receiving the bottom of a rectangle (in points).
* @param[in] top		- Pointer to a double value receiving the top of a rectangle (in points).
* @retval None.
*/
DLLEXPORT void STDCALL FPDFFont_GetBBox(FPDF_FONT font, double* left, double* right, double* bottom, double* top);

/**
* Get the special character bounding box of a font object.
* @param[in] font		- Handle to the font object.	
* @param[in] char_code	- The character code.
* @param[in] left		- Pointer to a double value receiving the left of a rectangle (in points).
* @param[in] right		- Pointer to a double value receiving the right of a rectangle (in points).
* @param[in] bottom		- Pointer to a double value receiving the bottom of a rectangle (in points).
* @param[in] top		- Pointer to a double value receiving the top of a rectangle (in points).
* @retval None.
*/
DLLEXPORT void STDCALL FPDFFont_GetCharBBox(FPDF_FONT font, FPDF_DWORD char_code, double* left, double* right, double* bottom, double* top);

/**
* Get the special character width of a font object.
* @param[in] font		- Handle to the font object.		
* @param[in] char_code	- The character code.	
* @retval The value of the width.
*/
DLLEXPORT int STDCALL FPDFFont_GetCharWidth(FPDF_FONT font, FPDF_DWORD char_code);

/**
* Get the unicode value from a character code.
* @param[in] font		- Handle to the font object.	
* @param[in] char_code	- The character code.	
* @retval The Unicode value.
*/
DLLEXPORT unsigned short STDCALL FPDFFont_GetUnicode(FPDF_FONT font, FPDF_DWORD char_code);

/**
* Get the character size in the font.
* @param[in] font		- Handle to the font object.	
* @param[in] char_code	- The character code.	
* @retval The value of the character size.
*/
DLLEXPORT int STDCALL FPDFFont_GetCharSize(FPDF_FONT font, FPDF_DWORD char_code);	

/**
* Get the character code from a unicode value.
* @param[in] font		- Handle to the font object.	
* @param[in] unicode	- The unicode of a special character.	
* @retval The character code value.
*/
DLLEXPORT FPDF_DWORD STDCALL FPDFFont_GetCharCode(FPDF_FONT font, unsigned short unicode);

/**
* Get the descent value in the font.
* @param[in] font	- Handle to the font object.	
* @note   The descent value describes the maximum depth below the baseline 
* 		  reached by glyphs in this font. The value is a negative number.
* @retval The descent value.
*/
DLLEXPORT int STDCALL FPDFFont_GetFontDescent (FPDF_FONT font);

/**
* Get the ascent value in the font.
* @param[in] font	- Handle to the font object.		
* @note   The ascent value describes the maximum height above the baseline reached 
*         by glyphs in this font, excluding the height of glyphs for accented characters.
* @retval The ascent value.
*/
DLLEXPORT int STDCALL FPDFFont_GetFontAscent(FPDF_FONT font);

/** 
* @brief The tagFPDFLOGFONT structure defines the attributes of a font.
*/
/**@{*/
typedef struct tagFPDFLOGFONT {
	
	/** 
	* @brief Specifies the weight of the font in the range 0 through 1000. For example,
	*        400 is normal and 700 is bold. If this value is zero, a default weight is
	*        used. Not support yet, reserved.
	*/
	long lfWeight;
	/** 
	* @brief  Specifies an italic font if set to TRUE. Not support yet, reserved.
	*/					
	unsigned char lfItalic;	
	/** 
	* @brief  Specifies the character set.
	*/
	unsigned char lfCharSet;
	/** 
	* @brief  Specifies the pitch and family of the font.
	*/
	unsigned char lfPitchAndFamily;
	/** 
	* @brief  A null-terminated string that specifies the typeface name of the font.
	*/
	char lfFaceName[32];		
} FPDFLOGFONT, *PFPDFLOGFONT; 
/**@}*/

/**
* Create a true type font and add the font into the document.
* @param[in] document	- Handle to a document returned by either FPDF_LoadDocument or FPDF_CreateNewDocument.
* @param[in] pLogFont	- The tagFPDFLOGFONT structure defined above.
* @retval Handle to the new font object.
*/
DLLEXPORT FPDF_FONT STDCALL FPDFFont_AddTrueType(FPDF_DOCUMENT document, PFPDFLOGFONT pLogFont);

/** 
* @name Font encoding
*@{
*/
/** @brief Built-in encoding.*/
#define FPDF_ENCODING_DEFAULT		0 	
/** @brief WinAnsiEncoding.*/
#define FPDF_ENCODING_WINANSI		1	
/** MacRomanEncoding.*/
#define FPDF_ENCODING_MACROMAN		2	
/** MacExpertEncoding.*/
#define FPDF_ENCODING_MACEXPERT		3	
/**  StandardEncoding. Adobe standard encoding. */
#define FPDF_ENCODING_STANDARD		4	
/**  Not support yet. Reserved.*/
#define FPDF_ENCODING_IDENTITY		10	
/**  Not support yet. Reserved.*/
#define FPDF_ENCODING_GB			11	
/**  Not support yet. Reserved.*/
#define FPDF_ENCODING_BIG5			12	
/**  Not support yet. Reserved.*/
#define FPDF_ENCODING_SHIFT_JIS		13	
/**  Not support yet. Reserved.*/
#define FPDF_ENCODING_KOREAN		14	
/**@}*/

/**
* Create a standard type font and add the font into the document.
* @param[in] document	-	Handle to document. Returned by FPDF_LoadDocument and FPDF_CreateNewDocument.
* @param[in] font_name	-	A null-terminated string that specifies the typeface name of the font. 
* @param[in] encoding	-	The font encoding defined above.
* @retval Handle to the new font object.
*/
DLLEXPORT FPDF_FONT STDCALL FPDFFont_AddStandardFont(FPDF_DOCUMENT document, char* font_name, int encoding);

/**
* Create a new path Object.
* @retval Handle to the path object.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_NewPathObj();

/** 
* @name Path point types
*@{
*/
/** Specifies that the figure is automatically closed after the corresponding line 
 * or curve is drawn. The figure is closed by drawing a line from the line or 
 * curve endpoint to the point corresponding to the last PT_MOVETO. */
#define FPDF_PATH_CLOSEFIGURE	1	
/** Specifies that the previous point and the corresponding point in lpPoints are the endpoints of a line.*/									
#define FPDF_PATH_LINETO		2	
/** Specifies that the corresponding point in lpPoints is a control point or ending point for a B¨¦zier curve.*/
#define FPDF_PATH_BEZIERTO		4	
/** Specifies that the corresponding point in lpPoints starts a disjoint figure.*/
#define FPDF_PATH_MOVETO		6	
/**@}*/

/**
* Set the points in a path object.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] point_count	- The total number of points.
* @param[in] point_x		- The pointer to point at an array of X coordinate of points.
* @param[in] point_y		- The pointer to point at an array of Y coordinate of points.
* @param[in] flags			- The pointer to point at an array of the path point types defined above.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPathObj_SetPoints(FPDF_PAGEOBJECT path_object, int point_count, double* point_x, double* point_y, int* flags);

/**
* Insert a point to a path object.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] x				- The X coordinate of a point.
* @param[in] y				- The Y coordinate of a point.
* @param[in] flag			- The path point types defined above.
* @param[in] point_index	- The index of the point.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPathObj_InsertPoint(FPDF_PAGEOBJECT path_object, double x, double y, int flag, int point_index = -1);

/**
* Remove a point in a path object.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] point_index	- The index of the point.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPathObj_RemovePoint(FPDF_PAGEOBJECT path_object, int point_index);

/**
* Clear the points in a path object.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPathObj_ClearPoints(FPDF_PAGEOBJECT path_object);

/**
* Get the number of points in a path object.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @retval The point count in a path object.
*/
DLLEXPORT int STDCALL FPDFPathObj_CountPoints(FPDF_PAGEOBJECT path_object);

/**
* Get the type of a special point.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] point_index	- The index of the point.
* @retval The path point types defined above.
*/
DLLEXPORT int STDCALL FPDFPathObj_GetPointType(FPDF_PAGEOBJECT path_object, int point_index);

/**
* Get the X coordinate of a specific point.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] point_index	- The index of the point.
* @retval The value of the X coordinate of the point.
*/
DLLEXPORT double STDCALL FPDFPathObj_GetPointX(FPDF_PAGEOBJECT path_object, int point_index);

/**
* Get the Y coordinate of a specific point.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] point_index	- The index of the point.
* @retval The value of the Y coordinate of the point.
*/
DLLEXPORT double STDCALL FPDFPathObj_GetPointY(FPDF_PAGEOBJECT path_object, int point_index);

/**
* Get the path in a path object.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @retval The path in the path object.
*/
DLLEXPORT FPDF_PATH STDCALL FPDFPathObj_GetPath(FPDF_PAGEOBJECT path_object);

/**
* Get the stroke mode of the path.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @retval Return the stroke mode, TRUE for stroking the line, FALSE for no stroking.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPathObj_GetStroke(FPDF_PAGEOBJECT path_object);

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
* Get the fill mode of the path.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @retval Return fill mode types defined above.
*/
DLLEXPORT int STDCALL FPDFPathObj_GetFillMode(FPDF_PAGEOBJECT path_object);

/**
* Set the fill and stroke mode of the path.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] fill_type		- The fill mode enumeration defined above.
* @param[in] stroke			- The stroke mode. TRUE for stroking the line, FALSE for no stroking.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFPathObj_SetFillStroke(FPDF_PAGEOBJECT path_object, int fill_type, int stroke);	

/**
* Get the matrix of the path.
* @param[in] path_object	- Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] a				- Pointer to a double value receiving the coefficient "a" of the matrix.
* @param[in] b				- Pointer to a double value receiving the coefficient "b" of the matrix.
* @param[in] c				- Pointer to a double value receiving the coefficient "c" of the matrix.
* @param[in] d				- Pointer to a double value receiving the coefficient "d" of the matrix.
* @param[in] e				- Pointer to a double value receiving the coefficient "e" of the matrix.
* @param[in] f				- Pointer to a double value receiving the coefficient "f" of the matrix.
* @retval TRUE for successful, FALSE for failed.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPathObj_GetMatrix(FPDF_PAGEOBJECT path_object, 
									double* a, double* b, double* c, double* d,double* e, double* f);
									
/**
* Set the matrix of the path.
* @param[in] image_object	-	Handle to the path object returned by FPDFPageObj_NewPathObj.
* @param[in] a				-	The coefficient "a" of the matrix.
* @param[in] b				-	The coefficient "b" of the matrix.
* @param[in] c				-	The coefficient "c" of the matrix.
* @param[in] d				-	The coefficient "d" of the matrix.
* @param[in] e				-	The coefficient "e" of the matrix.
* @param[in] f				-	The coefficient "f" of the matrix.
* @retval TRUE for successful, FALSE for failed.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFPathObj_SetMatrix(FPDF_PAGEOBJECT path_object, 
									double a, double b, double c, double d, double e, double f);

/**
* Insert a page object to the form object. The page object is automatically freed.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @param[in] page_obj		- Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*			 				  FPDFPageObj_NewPathObj, FPDFPageObj_ImageObj, etc.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFFormObj_InsertSubObject(FPDF_PAGEOBJECT form_object, FPDF_PAGEOBJECT page_obj);

/**
* Render contents in a form object to a device (screen, bitmap, or printer).
* @param[in] form_object	- Handle to the form_object. Returned by FPDFPage_GetObject function.
* @param[in] device			- Handle to device context.
* @param[in] xPos			- Left pixel position of the display area in the device coordinate.
* @param[in] yPos			- Top pixel position of the display area in the device coordinate.
* @param[in] xSize			- Horizontal size (in pixels) for displaying the page.
* @param[in] ySize			- Vertical size (in pixels) for displaying the page.
* @param[in] iRotate		- Page orientation: 0 (normal), 1 (rotated 90 degrees clockwise),
*			 				  2 (rotated 180 degrees), 3 (rotated 90 degrees counter-clockwise).
* @retval None.
*/
DLLEXPORT void STDCALL FPDFFormObj_Display(FPDF_PAGEOBJECT form_object,void* device,int xPos,int yPos,int xSize, int ySize,int iRotate);

/**
* Delete a page object from the form object. The page object is automatically freed.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @param[in] index			- The index of a page object.
* @retval None.
*/
DLLEXPORT void STDCALL FPDFFormObj_DeleteSubObject(FPDF_PAGEOBJECT form_object, int index);

/**
* Get the number of page objects inside the form object.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @retval The number of page objects.
*/
DLLEXPORT int STDCALL FPDFFormObj_CountSubObjects(FPDF_PAGEOBJECT form_object);

/**
* Get the page object in form object.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @param[in] index			- The index of a page object.
* @retval Handle to the page object. Null if an error occurs.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFFormObj_GetSubObject(FPDF_PAGEOBJECT form_object, int index);

/**
* Get the index of the page object in the specified form object.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @param[in] page_obj		- Handle to a page object. Returned by FPDFPageObj_NewTextObj,FPDFPageObj_NewTextObjEx,
*			 				  FPDFPageObj_NewPathObj, FPDFPageObj_NewImageObj, etc.
* @retval If successful, returns the index of the page object. Otherwise, returns -1.
*/
DLLEXPORT int STDCALL FPDFFormObj_GetSubObjectIndex(FPDF_PAGEOBJECT form_object, FPDF_PAGEOBJECT page_obj);

/**
* Generate content of the form object.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @note	When the form object's information changes, the user must call the FPDFFormObj_GenerateContent function.
*		Otherwise, the modified information will be lost.
* @retval TRUE for success, otherwise FALSE.
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFFormObj_GenerateContent(FPDF_PAGEOBJECT form_object);

/**
* Get the form object matrix.
* @param[in] form_object	- Handle to a form object. Returned by FPDFPage_GetObject.
* @param[in] a				- Pointer to a double value receiving the coefficient "a" of the matrix.
* @param[in] b				- Pointer to a double value receiving the coefficient "b" of the matrix.
* @param[in] c				- Pointer to a double value receiving the coefficient "c" of the matrix.
* @param[in] d				- Pointer to a double value receiving the coefficient "d" of the matrix.
* @param[in] e				- Pointer to a double value receiving the coefficient "e" of the matrix.
* @param[in] f				- Pointer to a double value receiving the coefficient "f" of the matrix.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFFormObj_GetMatrix(FPDF_PAGEOBJECT form_object, 
		double* a, double* b, double* c, double* d,double* e, double* f);
		
/**
* Create a new image object.
* @param[in] document	- Handle to a document returned by FPDF_LoadDocument or FPDF_CreateNewDocument.
* @retval Handle to the image object.
*/
DLLEXPORT FPDF_PAGEOBJECT STDCALL FPDFPageObj_NewImgeObj(FPDF_DOCUMENT document);

/**
* Load image from an image file (e.g. *.bmp,*.jpeg) and set it to an image object.
* @param[in] pages			- Pointers to the start of all loaded pages.
* @param[in] nCount			- Number of pages.
* @param[in] image_object	- Handle to the image object returned by FPDFPageObj_NewImgeObj.
* @param[in] filename		- The full path of the image file.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFImageObj_LoadFromFile(FPDF_PAGE* pages, int nCount,FPDF_PAGEOBJECT image_object, FPDF_BYTESTRING filename);

/**
* Get the matrix of an image object.
* @param[in] image_object	- Handle to the image object returned by FPDFPageObj_NewImgeObj.
* @param[in] a				- Pointer to a double value receiving the coefficient "a" of the matrix.
* @param[in] b				- Pointer to a double value receiving the coefficient "b" of the matrix.
* @param[in] c				- Pointer to a double value receiving the coefficient "c" of the matrix.
* @param[in] d				- Pointer to a double value receiving the coefficient "d" of the matrix.
* @param[in] e				- Pointer to a double value receiving the coefficient "e" of the matrix.
* @param[in] f				- Pointer to a double value receiving the coefficient "f" of the matrix.
* @note		A matrix defines transformation of coordinate from one space to another.
*			In PDF, a matrix is defined by the following equations:
*			x' = a * x + c * y + e;
*			y' = b * x + d * y + f;
*			FPDFImageObj_GetMatrix function is used to get a,b,c,d,e,f coefficients of the transformation from
*			"image space" to "user space". 
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFImageObj_GetMatrix(FPDF_PAGEOBJECT image_object, 
												   double* a, double* b, double* c, double* d,double* e, double* f);

/**
* Set the matrix of an image object.
* @param[in] image_object	- Handle to the image object returned by FPDFPageObj_NewImgeObj.
* @param[in] a				- The coefficient "a" of the matrix.
* @param[in] b				- The coefficient "b" of the matrix.
* @param[in] c				- The coefficient "c" of the matrix.
* @param[in] d				- The coefficient "d" of the matrix.
* @param[in] e				- The coefficient "e" of the matrix.
* @param[in] f				- The coefficient "f" of the matrix.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFImageObj_SetMatrix(FPDF_PAGEOBJECT image_object,
												   double a, double b, double c, double d, double e, double f);

/**
* Get the bitmap from an image object.
* @param[in] image_object	- Handle to the image object returned by FPDFPageObj_NewImgeObj.
* @retval Handle to the bitmap.
*/
DLLEXPORT FPDF_BITMAP STDCALL FPDFImageObj_GetBitmap(FPDF_PAGEOBJECT image_object);

/**
* Set the bitmap to an image object.
* @param[in] pages			- Pointer's to the start of all loaded pages.
* @param[in] nCount			- Number of pages.
* @param[in] image_object	- Handle to the image object returned by FPDFPageObj_NewImgeObj.
* @param[in] bitmap			- Handle to the bitmap
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFImageObj_SetBitmap(FPDF_PAGE* pages,int nCount,FPDF_PAGEOBJECT image_object, FPDF_BITMAP bitmap);

/** 
* @name Highlight definition
*@{
*/
#define  HIGHLIGHT_NONE		0
#define  HIGHLIGHT_INVERT	1
#define  HIGHLIGHT_OUTLINE	2
#define  HIGHLIGHT_PUSH		3
/**@}*/

/** 
* @name Border style definition
*@{ 
*/
#define BORDERSTYLE_SOLID		0
#define BORDERSTYLE_DASHED		1
#define BORDERSTYLE_BEVELED		2
#define BORDERSTYLE_INSET		3
#define BORDERSTYLE_UNDERLINE	4
/**@}*/

/**
* Create link object.
* @param[in] document		- Document pointer returned by the FPDF_loadDocument.
* @param[in] nsrcPageIndex	- Specified page index.
* @param[in] lx,ly,ux,uy	- The coordinate points which forms a rectangle.
* @retval Return a handle to a link object if successful, NULL if an error occurred.
*/
DLLEXPORT FPDF_LINK STDCALL FPDFLinkObj_NewLinkObj(FPDF_DOCUMENT document,int nsrcPageIndex,double lx,double ly, double ux, double uy);

/**
* Delete a link object.
* @param[in] document	- Document pointer returned by the FPDF_loadDocument Function.
* @param[in] page		- Handle to the page object
* @param[in] link		- Handle to the link object.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFLinkObj_DelLinkObj(FPDF_DOCUMENT document,FPDF_PAGE page,FPDF_LINK link);

/**
* Set the action of the link object.
* @param[in] document	- Pointer to the handle to document 
* @param[in] link		- Pointer to the handle to the link object.
* @param[in] action		- Pointer to the handle to the action.
* @retval TRUE for success, otherwise FALSE. 
*/
DLLEXPORT FPDF_BOOL STDCALL FPDFLinkObj_SetAction(FPDF_DOCUMENT document,FPDF_LINK link,FPDF_ACTION action);

/**
* Get the total number of link objects in the current page.
* @param[in] page	- Handle to a page object.
* @retval	Return the total number of link objects in the current page. 
*/
DLLEXPORT int STDCALL FPDFLinkObj_CountLink(FPDF_PAGE page);

/**
* Get a handle to the specified link object in a page.
* @param[in] page	- Pointer to a handle to a page.		
* @param[in] index	- Index number of the link object.
* @retval	Return a handle to the link object.
*/
DLLEXPORT FPDF_LINK STDCALL FPDFLinkObj_GetLink(FPDF_PAGE page,int index);

/**
* Get the boundaries of a rectangle surrounding a link.
* @param[in] link	- Pointer to the handle to a link object.
* @param[in] left	- Pointer to a double value receiving the rectangle left boundary.
* @param[in] top	- Pointer to a double value receiving the rectangle top boundary.
* @param[in] right	- Pointer to a double value receiving the rectangle right boundary.
* @param[in] bottom	- Pointer to a double value receiving the rectangle bottom boundary.
* @retval	None.
*/
DLLEXPORT void STDCALL FPDFLinkObj_GetRect(FPDF_LINK link, 
						double* left, double* top, double* right, double* bottom);
 
#ifdef __cplusplus
};
#endif

#endif
///< _FPDFOBJECTEDIT_H_
/** @} */