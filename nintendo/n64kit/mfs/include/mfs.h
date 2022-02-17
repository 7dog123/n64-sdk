/*======================================================================*/
/*	NINTENDO64 DiskDrive MultiFileSystem Library			*/
/*									*/
/*		mfs.h							*/
/*									*/
/*		Copyright (C) 1997, NINTENDO Co,Ltd.			*/
/*				Created by Kensaku Ohki(SLANP)		*/
/*======================================================================*/
/* $Id$									*/
/*======================================================================*/
#ifndef _MFS_H_
#define _MFS_H_
#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/leo.h>
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*	GLOABL DEFINE							*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*--------------------------------------*/
/*	FORAMT	MODE			*/
/*--------------------------------------*/
#define MFS_FORMAT_NORMAL	0
#define MFS_FORMAT_FORCE	1
    
/*--------------------------------------*/
/*	MFS VOLUME DEFINE		*/
/*--------------------------------------*/
#define MFS_VOLUME_NAME_LEN		20
#define MFS_VOLUME_NAME_SIZE		(MFS_VOLUME_NAME_LEN + 1) /* Includes NULL terminator */
#define MFS_VOLUME_ATTR_VPROTECT_WRITE	0x20
#define MFS_VOLUME_ATTR_VPROTECT_READ	0x40
#define MFS_VOLUME_ATTR_WPROTECT	0x80
#define MFS_VOLUME_DESTINATION_JAPAN	0
#define MFS_VOLUME_DESTINATION_US	1

/*--------------------------------------*/
/*	MFS DIRECTORY/FILE DEFINE	*/
/*--------------------------------------*/
#define MFS_FILE_NAME_LEN		20
#define MFS_FILE_NAME_SIZE		21	/* Includes NULL terminator */
#define MFS_FILE_TYPE_LEN		5
#define MFS_FILE_TYPE_SIZE		6	/* Includes NULL terminator */
#define MFS_FILE_ATTR_DIRECTORY		0x8000
#define MFS_FILE_ATTR_FILE		0x4000
#define MFS_FILE_ATTR_FORBID_W		0x2000
#define MFS_FILE_ATTR_FORBID_R		0x1000
#define MFS_FILE_ATTR_HIDDEN		0x0800
#define MFS_FILE_ATTR_ENCODE		0x0400
#define MFS_FILE_ATTR_COPYLIMIT		0x0200
#define MFS_FILE_ATTR_NONE		0x0000
#define MFS_FILENAME_MAX		128

/*--------------------------------------*/
/*	ERROR				*/
/*--------------------------------------*/
#define	MFS_ERR_NO		0
#define	MFS_ERR_ARG		-1	/* argument error		*/
#define MFS_ERR_DEVICE		-2	/* device error 		*/
#define MFS_ERR_NOINIT		-3	/* uninitialized error 		*/
#define MFS_ERR_NAME		-4	/* file name error 		*/
#define MFS_ERR_NOTFOUND	-5	/* no file/directory    	*/
#define MFS_ERR_FULL		-6	/* disk is full 		*/
#define MFS_ERR_FILEEXIST	-7	/* file (directory) with this name already exists */
#define MFS_ERR_PROTECT		-8	/* write protected		*/
#define MFS_ERR_REFUSE		-9	/* invalid operation		*/
#define MFS_ERR_HEADER		-10	/* header is damaged		*/
#define MFS_ERR_SEARCHEND	-13	/* file search terminated	*/
#define MFS_ERR_FATAL		-14	/* failure to open		*/
#define MFS_ERR_FILEEND		-15
#define MFS_ERR_LENGTH		-16	/* character range exceeded	*/
#define MFS_ERR_NOTMFSDISK	-17
#define MFS_ERR_DISKCHANGE	-18	/* media has been changed	*/
#define MFS_ERR_VERSION		-19	/* incompatible version 	*/
    
/*--------------------------------------*/
/*	DIR ID				*/
/*--------------------------------------*/
#define MFS_DIRID_ROOT		0
#define MFS_DIRID_ROOTUP	0xfffe
#define MFS_ROOT_NAME		'/'
#define MFS_ALL_FILES		-10
#define MFS_DIRECTORY_MARK	'/'
#define	MFS_TYPE_MARK		'.'
#define	MFS_DRIVE_MARK		':'
    
#define MFS_DISKTYPE0_DIRENTRY_NUM	899
#define MFS_DISKTYPE1_DIRENTRY_NUM	814
#define MFS_DISKTYPE2_DIRENTRY_NUM	729
#define MFS_DISKTYPE3_DIRENTRY_NUM	644
#define MFS_DISKTYPE4_DIRENTRY_NUM	559
#define MFS_DISKTYPE5_DIRENTRY_NUM	474


    
#define MFS_DESTINATION_JAPAN	0
#define MFS_DESTINATION_US	1
#define MFS_GET_FILE		0
#define MFS_GET_PATH		1
#define MFS_WRITE_MODE_APPEND	-1
/*--------------------------------------*/
/*	CACHE				*/
/*--------------------------------------*/
#define MFS_CACHE_BUF_SIZE	BLK_SIZE_ZONE3

/*--------------------------------------*/
/*	 OPEN MODE			*/
/*--------------------------------------*/
#define MFS_OPEN_NONE		0x0000
#define	MFS_OPEN_READ		0x0001
#define MFS_OPEN_WRITE		0x0002
#define MFS_OPEN_UPDATE		0x0000
#define MFS_OPEN_APPEND		0x0010
#define MFS_OPEN_CREATE		0x0020

    
/*--------------------------------------*/
/*	 SEEK MODE			*/
/*--------------------------------------*/
#define MFS_SEEK_SET		0
#define MFS_SEEK_CUR		1
#define MFS_SEEK_END		2

/*--------------------------------------*/
/*	NAME				*/
/*--------------------------------------*/
#define MFS_MAXPATH		128
#define MFS_MAXDRIVE		3
#define	MFS_MAXDIR		100
#define MFS_MAXFILE		21
#define MFS_MAXTYPE		7

/*--------------------------------------*/
/*	fnsplit				*/
/*--------------------------------------*/
/*#define MSF_FNSPLIT_WILDCARDS	0x01*/
#define MFS_FNSPLIT_TYPE	0x02
#define	MFS_FNSPLIT_FILENAME	0x04
#define	MFS_FNSPLIT_DIRECTORY	0x08
#define MFS_FNSPLIT_DRIVE	0x10

/*--------------------------------------*/
/*	Drive				*/
/*--------------------------------------*/
#define MFS_DRIVE_ROM		'A'		/* ROM AREA DRIVE */
#define	MFS_DRIVE_RAM		'B'		/* RAM AREA DRIVE */

/*--------------------------------------*/
/*	MEDIA CHECK FLAG		*/
/*--------------------------------------*/
#define MFS_MCHECK_INSERT	0x0001
#define MFS_MCHECK_CHANGE	0x0002
    
#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*	STRUCTURE	 						*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
typedef	s16	MfsDirID;
typedef u32	MfsDate;

/*--------------------------------------*/
/* MFS DirectoryEntry Info		*/
/*--------------------------------------*/
typedef struct st_MfsDiskInfo {
    LEOCapacity	cap;			/* Disk Capacity		*/
    LEODiskID	diskID;			/* Disk ID			*/
    u16		blockNum;		/* ROM Block 			*/
} MfsDiskInfo;



/*--------------------------------------*/
/* File Handle				*/
/*--------------------------------------*/
typedef struct st_stat{
    u32	size;
    LEODiskTime	time;
    u16	attribute;
    u16	dirID;
    u16	upDirID;
    u8	gameCode[4];
    u8	companyCode[2];
    u8	copyCounter;
    u8	renewalCounter;
} MfsStat;

typedef struct st_DirList {
    MfsDirID	upDirID;
    MfsDirID	nextDirID;
    u16		attr;
} MfsDirList;



typedef struct st_MfsFileOperations{
    u8	name;				/* drive name	*/
    struct st_MfsFileOperations* next;
    /* disk ope. */
    s32 (*mediaCheck)(void);
    s32 (*mediaFormat)(s32 mode);
    s32 (*flash)(void);

    /* file ope. */
    s32 (*getFileDirID)(MfsDirID upDirID, u8* name, u8* type);
    s32 (*createFile)(MfsDirID upDirID, u8* name, u8* type);
    s32 (*readFile)(MfsDirID dirID, void* buf, s32 offset,u32 len);
    s32 (*writeFile)(MfsDirID dirID, void* buf, s32 offset,u32 len);
    s32 (*seekFile)(MfsDirID dirID, s32 offset);
    s32 (*removeFile)(MfsDirID dirID);
    s32 (*getFileName)( MfsDirID dirID,u8* name, u8* type);
    s32 (*getFileAttr)(MfsDirID dirID);
    s32 (*setFileAttr)(MfsDirID dirID, u16 attr);
    s32 (*getFileDate)(MfsDirID dirID, LEODiskTime* time);
    s32 (*setFileDate)(MfsDirID dirID, LEODiskTime time);
    s32 (*getFileSize)(MfsDirID dirID);
    s32 (*renameFile)(MfsDirID dirID, u8* name, u8* type);
    s32 (*getFileCopyCount)(MfsDirID dirID);
    s32 (*setFileCopyCount)(MfsDirID dirID, u8 count);
    s32 (*getFileGameCode)(MfsDirID dirID, u8* companyCode, u8* gameCode);
    s32 (*setFileGameCode)(MfsDirID dirID, u8* companyCode, u8* gameCode);
    s32 (*getFileRC)(MfsDirID dirID);
    s32 (*resetFileRC)(MfsDirID dirID);
    s32 (*getFileParentDir)(MfsDirID dirID);
    s32 (*setFileParentDir)(MfsDirID upDirID, MfsDirID dirID);
    s32 (*resizeFile)(MfsDirID dirID,s32 offset);
    s32 (*getFileStat)(MfsDirID dirID, MfsStat* stat);
    s32 (*getDirListFirst)(MfsDirID upDirID, MfsDirList* dirList, u16 attr);
    s32 (*getDirListNext)(MfsDirList* dirList);
    
    /* dir ope. */
    s32 (*getDirID)(MfsDirID upDirID, u8* name);
    s32 (*removeDir)(MfsDirID dirID);
    s32 (*makeDir)(MfsDirID upDirID, u8* name);
    s32 (*renameDir)(MfsDirID dirID, u8* name);
    s32 (*getDirName)(MfsDirID dirID, u8* name);

    /* volume ope. */
    s32 (*setVolumeName)(u8* name);
    s32 (*setVolumeAttr)(u8 attr);
    s32 (*getVolumeAttr)(void);
    s32 (*getVolumeName)(u8* name);
    s32 (*getVolumeDate)(LEODiskTime* time);
    s32 (*getVolumeRC)(void);
    s32 (*resetVolumeRC)(void);
    s32 (*getDestination)(void);
} MfsFileOperations;

typedef struct st_ffblk {
    MfsFileOperations* fileOpe;
    MfsStat	stat;
    u8		name[MFS_FILE_NAME_SIZE + MFS_FILE_TYPE_SIZE];
    u8		path[MFS_FILE_NAME_SIZE + MFS_FILE_TYPE_SIZE];
    MfsDirList	dirList;
} MfsFfblk;

typedef struct st_Handle {
    MfsFileOperations* fileOpe;
    s32 	offset;
    u16		mode;
    s16		dirID;
    s32 	error;
} MfsFileHandle;

typedef MfsFileHandle*	MfsFile;

typedef struct st_VolumeInfo {
    LEODiskTime	time;
    u16	renewalCounter;
    u8	name[MFS_VOLUME_NAME_SIZE];
    u8	attribute;
    u8	destination;
} MfsVolumeInfo;

/*----------------------------------------------------------------------*/
/*	FileSystem Operation 						*/
/*----------------------------------------------------------------------*/
typedef struct st_IoOperations {
    s32 (*seek)(LEOCmd*, u32, OSMesgQueue*);
    s32 (*readWrite)(LEOCmd*, s32, u32, void*, u32, OSMesgQueue*);
    s32 (*readDiskID)(LEOCmd*, LEODiskID*, OSMesgQueue*);
    s32 (*readRTC)(LEOCmd*, OSMesgQueue*);
    s32 (*setRTC)(LEOCmd*, LEODiskTime*, OSMesgQueue*);
    s32 (*spdlMotor)(LEOCmd*, LEOSpdlMode, OSMesgQueue*);
    s32 (*modeSelectAsync)(LEOCmd*, u32, u32, OSMesgQueue*);
    s32 (*reZero)(LEOCmd*, OSMesgQueue*);
    s32 (*testUnitReady)(LEOStatus* status);
} MfsIoOperations;

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*	GLOBAL VALUE	 						*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
extern s32		mfsError;
extern OSMesgQueue	mfsMesgQ;
extern u8		mfsCompanyCode[];
extern u8		mfsGameCode[];
extern MfsDiskInfo	mfsDiskInfo;
extern u8		mfsHCurrentDrive;
extern MfsDirID		mfsHCurrentDirID;
extern MfsFile		mfsHFileHandlePtr;/* file handle structure pointer */
extern u8		mfsHFileHandleNum;/* file handle structure number */
extern s32 		mfsDiskChange;
extern MfsIoOperations*	mfsIoOperations;
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*	FUNCTION	 						*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*--------------------------------------*/
/*	Initialize Function		*/
/*--------------------------------------*/
extern s32 mfsInit(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsRamInit(void* buff);
extern s32 mfsRomInit(void* buff);

extern s32 mfsInitDiskRom(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsInitDiskRam(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsInitDiskRomRam(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsInitCasRom(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsInitCasRam(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsInitCasRomRam(u8* companyCode, u8* gameCode,u8 dest);
extern s32 mfsDiskIdCheck(void);

/*--------------------------------------*/
/*	Disk Function			*/
/*--------------------------------------*/
/*------------- RAM --------------------*/
extern s32 mfsRamMediaFormat(s32 mode);

extern s32 mfsRamMediaCheck(void);
extern s32 mfsRamFlash(void);
extern s32 mfsRamGetFreeSize(void);
extern s32 mfsRamGetFreeDirEntryNum(void);
extern s32 mfsRamGetVolumeAttr(void);
extern s32 mfsRamGetVolumeName(u8* name);
extern s32 mfsRamGetDiskType(void);
extern s32 mfsRamGetVolumeDate(LEODiskTime* time);
extern s32 mfsRamGetVolumeRC(void);
extern s32 mfsRamGetDestination(void);
extern s32 mfsRamResetVolumeRC(void);
extern s32 mfsRamSetVolumeName(u8* name);
extern s32 mfsRamSetVolumeAttr(u8 attr);
extern s32 mfsRamSetVolumeDate(LEODiskTime time);
extern s32 mfsRamSetDestination(u8 destination);
extern s32 mfsRamGetFileNum(MfsDirID upDirID,u16 attr);
extern s32 mfsRamRepairHeader(void);

/*------------- ROM --------------------*/
extern s32 mfsRomMediaCheck(void);
extern s32 mfsRomGetVolumeAttr(void);
extern s32 mfsRomGetVolumeName(u8* name);
extern s32 mfsRomGetDiskType(void);
extern s32 mfsRomGetVolumeDate(LEODiskTime* time);
extern s32 mfsRomGetDestination(void);
extern s32 mfsRomGetFileNum(MfsDirID dirID,u16 attr);

/*--------------------------------------*/
/*	Support Function		*/
/*--------------------------------------*/
extern s32 mfsStrCmp(const u8* s1, const u8* s2);
extern s32 mfsStrnCmp(const u8* s1, const u8* s2, s32 count);
extern u8* mfsStrCpy(u8* dest, const u8* src);
extern u8* mfsStrnCpy(u8* dest, u8* src, s32 count);
extern void mfsSetGameCode(u8* companyCode, u8* gameCode);
extern void mfsGetGameCode(u8* companyCode, u8* gameCode);
extern s32 mfsStrLen(const u8* src);
extern u8* mfsStrrChr(const u8* src, s32 c);
extern u8* mfsStrCat(u8* dest, const u8* src);
extern s32 mfsStrWCmp(const u8* src1, const u8* src2);

/*--------------------------------------*/
/*	IO Function			*/
/*--------------------------------------*/
extern s32 mfsReadWriteLBA(u32 startLBA, u32 nLBAs, void* buf,s32 direction);
extern s32 mfsReadDiskID(LEODiskID *diskID);
extern s32 mfsSeekLBA(u32 LBA);
extern s32 mfsSpdlMotor(LEOSpdlMode mode);
extern s32 mfsTestUnit(LEOStatus* status);
extern void mfsSetLeoBusyFunc(void (*func)(void));
extern void mfsSetLeoReadyFunc(void (*func)(void));
extern void mfsSetLeoErrorFunc(void (*func)(s32));

/*--------------------------------------*/
/*	RTC Function			*/
/*--------------------------------------*/
extern s32 mfsReadRTC(LEODiskTime* time);
extern s32 mfsSetRTC(LEODiskTime* time);
extern u32 mfsRTCToDate(LEODiskTime time);
extern s32 mfsGetMfsDate(MfsDate* date);
extern void mfsDateToRTC(MfsDate date, LEODiskTime *time);


/*--------------------------------------*/
/*	Low Level Directry Function	*/
/*--------------------------------------*/
/*------------- RAM --------------------*/
extern s32 mfsRamGetDirID(MfsDirID upDirID, u8* name);
extern s32 mfsRamRemoveDir(MfsDirID dirID);
extern s32 mfsRamMakeDir(MfsDirID upDirID, u8* name);
extern s32 mfsRamRenameDir(MfsDirID dirID, u8* name);
extern s32 mfsRamGetDirName(MfsDirID dirID, u8* name);

/*------------- ROM --------------------*/
extern s32 mfsRomGetDirID(MfsDirID upDirID, u8* name);
extern s32 mfsRomGetDirName(MfsDirID dirID, u8* name);
/*--------------------------------------*/
/*	Low Level File Function		*/
/*--------------------------------------*/
/*------------- RAM --------------------*/
extern s32 mfsRamGetFileDirID(MfsDirID upDirID, u8* name, u8* type);
extern s32 mfsRamCreateFile(MfsDirID upDirID, u8* name, u8* type);
extern s32 mfsRamReadFile(MfsDirID dirID, void* buf, s32 offset,u32 len);
extern s32 mfsRamWriteFile(MfsDirID dirID, void* buf, s32 offset,u32 len);
extern s32 mfsRamSeekFile(MfsDirID dirID, s32 offset);
extern s32 mfsRamRemoveFile(MfsDirID dirID);
extern s32 mfsRamGetFileName( MfsDirID dirID,u8* name, u8* type);
extern s32 mfsRamGetFileAttr(MfsDirID dirID);
extern s32 mfsRamSetFileAttr(MfsDirID dirID, u16 attr);
extern s32 mfsRamGetFileDate(MfsDirID dirID, LEODiskTime* time);
extern s32 mfsRamSetFileDate(MfsDirID dirID, LEODiskTime time);
extern s32 mfsRamRenameFile(MfsDirID dirID, u8* name, u8* type);
extern s32 mfsRamGetFileCopyCount(MfsDirID dirID);
extern s32 mfsRamSetFileCopyCount(MfsDirID dirID, u8 count);
extern s32 mfsRamGetFileParentDir(MfsDirID dirID);
extern s32 mfsRamSetFileParentDir(MfsDirID upDirID, MfsDirID dirID);
extern s32 mfsRamGetFileSize(MfsDirID dirID);
extern s32 mfsRamGetFileGameCode(MfsDirID dirID, u8* companyCode, u8* gameCode);
extern s32 mfsRamSetFileGameCode(MfsDirID dirID, u8* companyCode, u8* gameCode);
extern s32 mfsRamGetFileRC(MfsDirID dirID);
extern s32 mfsRamResetFileRC(MfsDirID dirID);
extern s32 mfsRamResizeFile(MfsDirID dirID,s32 offset);
extern s32 mfsRamGetFileStat(MfsDirID dirID, MfsStat* stat);
extern s32 mfsRamGetDirListFirst(MfsDirID upDirID, MfsDirList* dirList, u16 attr);
extern s32 mfsRamGetDirListNext(MfsDirList* dirList);


/*------------- ROM --------------------*/
extern s32 mfsRomGetFileDirID(MfsDirID upDirID, u8* name, u8* type);
extern s32 mfsRomReadFile(MfsDirID dirID, void* buf, s32 offset,u32 len);
extern s32 mfsRomSeekFile(MfsDirID dirID, s32 offset);
extern s32 mfsRomGetFileName( MfsDirID dirID,u8* name, u8* type);
extern s32 mfsRomGetFileAttr(MfsDirID dirID);
extern s32 mfsRomGetFileDate(MfsDirID dirID, LEODiskTime* time);
extern s32 mfsRomGetFileParentDir(MfsDirID dirID);
extern s32 mfsRomGetFileSize(MfsDirID dirID);
extern s32 mfsRomGetFileGameCode(MfsDirID dirID, u8* companyCode, u8* gameCode);
extern s32 mfsRomGetFileStat(MfsDirID dirID, MfsStat* stat);
extern s32 mfsRomGetFileLBA(MfsDirID dirID, s16* LBA, s16* offset);
extern s32 mfsRomGetDirListFirst(MfsDirID upDirID, MfsDirList* dirList, u16 attr);
extern s32 mfsRomGetDirListNext(MfsDirList* dirList);

/*--------------------------------------*/
/*	High Level init Function	*/
/*--------------------------------------*/
extern s32 mfsHInitHandle(MfsFile handle,u8 handleNum);
extern s32 mfsHInitRam(void);
extern s32 mfsHInitRom(void);
extern s32 mfsHInitDiskBoot(MfsFile handle,u8 handleNum, u8 *company, u8* game,u8 dest);
extern  s32 mfsHInitCasBoot(MfsFile filePtr, u8 handleNum, u8* company, u8* game, u8 dest);
extern s32 mfsHMediaCheck(void);
extern s32 mfsHMediaFormat(s32 drive, s32 mode, u8* name, u8 attr);

extern s32 mfsHFopen(MfsFile* handle, u8* path, u16 mode);
extern s32 mfsHFread(MfsFile handle, void* buf, s32 len);
extern s32 mfsHFwrite(MfsFile handle, void* buf, s32 len);
extern s32 mfsHFclose(MfsFile handle);
extern s32 mfsHFseek(MfsFile handle, s32 offset, s32 fromwhere);
extern s32 mfsHFtell(MfsFile handle);
extern s32 mfsHFstat(MfsFile handle, MfsStat* stat);
extern s32 mfsHFgetAttr(MfsFile handle);
extern s32 mfsHFsetAttr(MfsFile handle, u16 attr);
extern s32 mfsHFgetCopyCount(MfsFile handle);
extern s32 mfsHFsetCopyCount(MfsFile handle, u8 count);
extern s32 mfsHFgetRC(MfsFile handle);
extern s32 mfsHFresetRC(MfsFile handle);

extern s32 mfsHRemoveFile(const u8* path);
extern s32 mfsHRenameFile(const u8* oldname, const u8* newname);
extern s32 mfsHGetFileCopyCount(const u8* path);
extern s32 mfsHSetFileCopyCount(const u8* path, u8 count);

extern s32 mfsHGetAttr(const u8* path);
extern s32 mfsHSetAttr(const u8* path, u16 attr);
extern s32 mfsHGetRC(const u8* path);
extern s32 mfsHResetRC(const u8* path);
extern s32 mfsHGetStat(const u8* path, MfsStat* stat);

extern s32 mfsHDirIDToPath(u8 drive, MfsDirID dirID, u8* path, s32 bufLen);
extern s32 mfsHGetCwd(u8* path, s32 bufLen);
extern s32 mfsHChDir(const u8* path);
extern s32 mfsHPathToDirID(const u8* path, MfsDirID* upDirIDPtr);
extern s32 mfsHRmDir(const u8* path);
extern s32 mfsHMkDir(const u8* path, u16 attr);

extern s32 mfsHGetVolumeInfo(s32 drive, MfsVolumeInfo* volumeInfo);
extern s32 mfsHGetVolumeAttr(s32 drive);
extern s32 mfsHSetVolumeAttr(s32 drive, u8 attr);
extern s32 mfsHGetVolumeRC(s32 drive);
extern s32 mfsHResetVolumeRC(s32 drive);


extern s32 mfsHFnsplit(const u8* path, u8* drive, u8* dir, u8* name, u8* type);
extern void mfsHFnmerge(u8* path, const u8* drive, const u8* dir, const u8* name, const u8* type);
extern s32 mfsHRegisterFileSystem(MfsFileOperations* fileOpe);

extern MfsFileOperations* mfsHGetFileSystem(u8 name);s32 mfsHInitDiskBoot(MfsFile handle,u8 handleNum, u8 *company, u8* game,u8 dest);
extern s32 mfsHGetDisk(void);
extern s32 mfsHSetDisk(s32 drive);
extern s32 mfsHErrorHandler(s32 errorNo);

extern s32 mfsHFindFirst(const u8* path, MfsFfblk *ffblk, u16 attr);
extern s32 mfsHFindNext(MfsFfblk *ffblk);


typedef s32 (*MfsErrorFunc)(s32 errorNo);

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*	MACRO		 						*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

#define mfsReadLBA(startLBA, nLBAs, buf)			\
	mfsReadWriteLBA(startLBA, nLBAs, buf, OS_READ)
	    
#define mfsWriteLBA(startLBA, nLBAs, buf)			\
	mfsReadWriteLBA(startLBA, nLBAs, buf, OS_WRITE)
	    
#define MFS_HEX2ASC(hex)						\
    ((hex/10 + '0') * 0x100 + ((hex % 10) + '0'))

#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */
#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
#endif /* _MFS_H_ */
