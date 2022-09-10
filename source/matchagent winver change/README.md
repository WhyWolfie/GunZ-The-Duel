Open (MatchAgent/stdafx.h)
Find

    // stdafx.h : Àß º¯°æµÇÁö ¾Ê°í ÀÚÁÖ »ç¿ëÇÏ´Â
    // Ç¥ÁØ ½Ã½ºÅÛ Æ÷ÇÔ ÆÄÀÏ ¹× ÇÁ·ÎÁ§Æ® °ü·Ã Æ÷ÇÔ ÆÄÀÏÀÌ 
    // µé¾î ÀÖ´Â Æ÷ÇÔ ÆÄÀÏÀÔ´Ï´Ù.

    #pragma once

    #ifndef VC_EXTRALEAN
    #define VC_EXTRALEAN		// Windows Çì´õ¿¡¼­ °ÅÀÇ »ç¿ëµÇÁö ¾Ê´Â ³»¿ëÀ» Á¦¿Ü½ÃÅµ´Ï´Ù.
    #endif

    // ¾Æ·¡ ÁöÁ¤µÈ ÇÃ·§Æûº¸´Ù ¿ì¼±ÇÏ´Â ÇÃ·§ÆûÀ» ´ë»óÀ¸·Î ÇÏ´Â °æ¿ì ´ÙÀ½ Á¤ÀÇ¸¦ ¼öÁ¤ÇÏ½Ê½Ã¿À.
    // ´Ù¸¥ ÇÃ·§Æû¿¡ »ç¿ëµÇ´Â ÇØ´ç °ªÀÇ ÃÖ½Å Á¤º¸´Â MSDNÀ» ÂüÁ¶ÇÏ½Ê½Ã¿À.
    #ifndef WINVER				// Windows 95 ¹× Windows NT 4 ÀÌÈÄ ¹öÀü¿¡¼­¸¸ ±â´ÉÀ» »ç¿ëÇÒ ¼ö ÀÖ½À´Ï´Ù.
    #define WINVER 0x0400		// Windows 98°ú Windows 2000 ÀÌÈÄ ¹öÀü¿¡ ¸Âµµ·Ï ÀûÇÕÇÑ °ªÀ¸·Î º¯°æÇØ ÁÖ½Ê½Ã¿À.
    #endif

    #ifndef _WIN32_WINNT		// Windows NT 4 ÀÌÈÄ ¹öÀü¿¡¼­¸¸ ±â´ÉÀ» »ç¿ëÇÒ ¼ö ÀÖ½À´Ï´Ù.
    #define _WIN32_WINNT 0x0400		// Windows 98°ú Windows 2000 ÀÌÈÄ ¹öÀü¿¡ ¸Âµµ·Ï ÀûÇÕÇÑ °ªÀ¸·Î º¯°æÇØ ÁÖ½Ê½Ã¿À.
    #endif						

    #ifndef _WIN32_WINDOWS		// Windows 98 ÀÌÈÄ ¹öÀü¿¡¼­¸¸ ±â´ÉÀ» »ç¿ëÇÒ ¼ö ÀÖ½À´Ï´Ù.
    #define _WIN32_WINDOWS 0x0410 // Windows Me ÀÌÈÄ ¹öÀü¿¡ ¸Âµµ·Ï ÀûÇÕÇÑ °ªÀ¸·Î º¯°æÇØ ÁÖ½Ê½Ã¿À.
    #endif

    #ifndef _WIN32_IE			// IE 4.0 ÀÌÈÄ ¹öÀü¿¡¼­¸¸ ±â´ÉÀ» »ç¿ëÇÒ ¼ö ÀÖ½À´Ï´Ù.
    #define _WIN32_IE 0x0400	// IE 5.0 ÀÌÈÄ ¹öÀü¿¡ ¸Âµµ·Ï ÀûÇÕÇÑ °ªÀ¸·Î º¯°æÇØ ÁÖ½Ê½Ã¿À.
    #endif

    #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ÀÏºÎ CString »ý¼ºÀÚ´Â ¸í½ÃÀûÀ¸·Î ¼±¾ðµË´Ï´Ù.

    // MFCÀÇ °øÅë ºÎºÐ°ú ¹«½Ã °¡´ÉÇÑ °æ°í ¸Þ½ÃÁö¿¡ ´ëÇÑ ¼û±â±â¸¦ ÇØÁ¦ÇÕ´Ï´Ù.
    #define _AFX_ALL_WARNINGS


    #include <afxwin.h>         // MFC ÇÙ½É ¹× Ç¥ÁØ ±¸¼º ¿ä¼Ò
    #include <afxext.h>         // MFC ÀÍ½ºÅÙ¼Ç
    #include <afxdisp.h>        // MFC ÀÚµ¿È­ Å¬·¡½º

    #include <afxdtctl.h>		// Internet Explorer 4 °ø¿ë ÄÁÆ®·Ñ¿¡ ´ëÇÑ MFC Áö¿ø
    #ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>			// Windows °ø¿ë ÄÁÆ®·Ñ¿¡ ´ëÇÑ MFC Áö¿ø
    #include <afxrich.h>
    #include <afxcview.h>
    #endif // _AFX_NO_AFXCMN_SUPPORT

Replace with

    #pragma once

    #ifndef VC_EXTRALEAN
    #define VC_EXTRALEAN
    #endif

    #ifndef WINVER
    #define WINVER 0x601
    #endif

    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x601
    #endif						

    #ifndef _WIN32_WINDOWS
    #define _WIN32_WINDOWS 0x601
    #endif

    #ifndef _WIN32_IE
    #define _WIN32_IE 0x601
    #endif

    #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
    #define _AFX_ALL_WARNINGS

    #include <afxwin.h>
    #include <afxext.h>
    #include <afxdisp.h>

    #include <afxdtctl.h>
    #ifndef _AFX_NO_AFXCMN_SUPPORT
    #include <afxcmn.h>
    #include <afxrich.h>
    #include <afxcview.h>
    #endif

Remove MatchAgent.pdb file from your folder and rebuild it again :) <br>
If you're lazy to do this i will rebuild MatchAgent for you.
