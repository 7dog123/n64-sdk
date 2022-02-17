typedef struct {
	unsigned short bfType;      /* file type (should be 'BM'(= 19778)) */
	unsigned long  bfSize;      /* file size */
	unsigned short bfReserved1; /* always 0 */
	unsigned short bfReserved2; /* always 1 */
	unsigned long  bfOffBits;   /* offset to bitmap data */
} BITMAPFILEHEADER;

#define BI_RGB   0L  /* non-compression */
#define BI_RLE8  1L  /* run-length (8bit/pixel) */
#define BI_RLE4  2L  /* run-length (4bit/pixel) */

typedef struct {
	unsigned long  biSize;      /* size of this structure */
	long           biWidth;     /* width of bitmap */
	long           biHeight;    /* height of bitmap */
	unsigned short biPlanes;    /* number of planes (should be 1) */
	unsigned short biBitCount;  /* bit per pixels */
	unsigned long  biCompression; 
	                            /* compression type */
	                            /* BI_RGB, BI_RLE8 or BI_RLE4 */
	unsigned long  biSizeImage; /* size of image (when BI_RGB, can be 0) */
	long           biXPelsPerMeter; /* pixele per meter for width */
	long           biYPelsPerMeter; /* pixels per meter for width */
	unsigned long  biClrUsed;   /* number of color index */
	unsigned long  biClrImportant; /* number of important color indexes */
} BITMAPINFOHEADER;


typedef struct{
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved; /* always 0 */
} RGBQUAD;

