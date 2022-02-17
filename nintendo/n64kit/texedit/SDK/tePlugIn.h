#ifndef __tePlugIn_H__
#define __tePlugIn_H__

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

struct TMF {
    int m_width;
    int m_height;
    int m_bits;
    u32* m_pBitmap;
};

struct TLF {
    u32 m_type;
    s32 m_num;
    u16* m_color_array;
};

/* Picture */
struct Pic {
    TMF* m_pTMF;
    TLF* m_pTLF;
    void* m_pReserved;
    int m_palette;
};

#pragma pack()

//// TextureEditor Plug-In Type
enum TEPIT {
    TEPIT_IMPORT = 1,
    TEPIT_EXPORT = 2,
    TEPIT_PREVIEW = 4,
};

#define DLLEXPORT __declspec(dllexport)
/*
//// YOU MUST BE IMPLEMENT BELOW FUNCTIONS ////
// get type of plug-in
// ex) return TEPIT_IMPORT | TEPIT_EXPORT;
// caution: preview type plug-in is only one.
*/
DLLEXPORT int PASCAL EXPORT TEPI_getType();
/* check an application version. if available then return TRUE. */
DLLEXPORT BOOL PASCAL EXPORT TEPI_isAvail(DWORD version);
DLLEXPORT BOOL PASCAL EXPORT TEPI_property();
DLLEXPORT BOOL PASCAL EXPORT TEPI_about();
DLLEXPORT BOOL PASCAL EXPORT TEPI_import(Pic* pInput, Pic* pOutput); /* called on import. */
DLLEXPORT BOOL PASCAL EXPORT TEPI_export(Pic* pInput); /* called on export. */

/* You can select to use each functions. */
/* preview() function uses single texutre. */
DLLEXPORT BOOL PASCAL EXPORT TEPI_preview(Pic* pInput); /* called on update time of TMF/TLF. */
/* preview2() function uses more texture. 'no' parameter is number of texture. */
DLLEXPORT BOOL PASCAL EXPORT TEPI_preview2(Pic* pInput, int no); /* called on update time of TMF/TLF */

#ifdef __cplusplus
};
#endif

#endif