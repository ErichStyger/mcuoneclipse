/** @file
 * 
 * uffs_shell.c
 *
 *  Created on: Aug 30, 2013
 *      Author: Marc Lindahl
 *      
 *  Interface to command Shell
 *  Assumes use of FreeRTOS
 */

#include "CLS1.h"
#include "FreeRTOS.h"
#include "uffs_config.h"
#include "uffs_user.h"

#include "TmDt1.h"


#define PFX NULL

uffs_DIR *cwd;

#define FAT_SUPPORT		///< define if you have a FAT1 component instantiated and want to support cross filesystem operations (copy)

#ifdef FAT_SUPPORT
#include "ff.h"
#include "FAT1.h"
#endif

static void CmdUsageError(const unsigned char *cmd, byte *usage, const CLS1_StdIOType *io) {
  CLS1_SendStr((unsigned char*)"*** error while reading command: ", io->stdErr);
  CLS1_SendStr(cmd, io->stdErr);
  CLS1_SendStr((unsigned char*)"\r\n*** Usage: ", io->stdErr);
  CLS1_SendStr((unsigned char*)usage, io->stdErr);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdErr);
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
	uffs_MountTable *m;
	MSGLN("UFFS defined mount points:");
	m = get_flash_mount_table();
	while (m->dev)
	{
		MSGLN("Mount point: %s, start: %d, end: %d",
				m->mount, m->start_block, m->end_block);
		m++;
	}
	MSGLN("mounted list:");
	m = uffs_MtbGetMounted();
	while (m)
	{
		MSGLN("Mount point: %s, start: %d, end: %d",
				m->mount, m->start_block, m->end_block);
		m = m->next;
	}
	MSGLN("unmounted list:");
	m = uffs_MtbGetUnMounted();
	while (m)
	{
		MSGLN("Mount point: %s, start: %d, end: %d",
				m->mount, m->start_block, m->end_block);
		//m->next;
	}

	return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
	CLS1_SendHelpStr((unsigned char*)"UFFS", (unsigned char*)"Group of UFFS commands\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  init", (unsigned char*)"Initialize UFFS driver\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  uninit", (unsigned char*)"Un-initialize UFFS driver\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  cd [<directoryName>]", (const unsigned char*)"Change the current directory or display the name of the current directory\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  dir [<directoryName>]", (const unsigned char*)"Prints a directory\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  delete <filename>", (const unsigned char*)"Delete a file\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  mkdir <directory>", (const unsigned char*)"Create a directory\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  format <mountPath>", (const unsigned char*)"Format a partition\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  rename <src> <dst>", (const unsigned char*)"Rename a file\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  diskinfo", (const unsigned char*)"Print disk information\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*)"  benchmark", (const unsigned char*)"Run disk benchmark\r\n", io->stdOut);
#ifdef FAT_SUPPORT
	CLS1_SendHelpStr((unsigned char*)"  copy <src> <dst>", (const unsigned char*)"Copy a file. FAT paths should start with drive number and colon (e.g. 0:/path/to/file)\r\n", io->stdOut);
#endif
	return ERR_OK;
}

static byte InitCmd(const CLS1_ConstStdIOType *io)
{
	uffs_SetupDebugOutputCLS(io);
	MSGLN("initializing UFFS");
	my_init_filesystem();
	return ERR_OK;
}

static byte UninitCmd(const CLS1_ConstStdIOType *io)
{
	MSGLN("un-initializing UFFS");
	my_release_filesystem();
	return ERR_OK;
}



static byte CdCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io) {
  /* precondition: cmd starts with "cd" */
	
	// TODO: support relative pathnames 
	
	char d_name[UFFS_PATHSIZE];
	byte res = ERR_OK;
	
	if (*(cmd + sizeof("cd") - 1) == ' ')
	{ /* space after "cd": read name */
		if (UTIL1_ReadEscapedName(cmd + sizeof("cd"),
				(unsigned char*)d_name, sizeof(d_name), NULL,
				NULL, NULL) == ERR_OK)
		{
			cwd = uffs_opendir(d_name);
			res = uffs_get_error();
		}
		else
		{
			CLS1_SendStr((unsigned char*) "reading directory name failed!\r\n",
					io->stdErr);
			res = ERR_FAILED;
		}
	}
	
	/* print current directory */
	CLS1_SendStr((unsigned char*)cwd->obj->name, io->stdOut);
	CLS1_SendStr((unsigned char*) "\r\n", io->stdOut);
	
	return res;
}

/// dir is the DOS equivalent of ls
static byte DirCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io) {
	/* precondition: cmd starts with "dir" */
	uffs_DIR *curdir = cwd;
	char d_name[UFFS_PATHSIZE];
	byte res = ERR_OK;
	
	if (*(cmd + sizeof("dir") - 1) == ' ')
	{ /* space after "dir": read name */
		if (UTIL1_ReadEscapedName(cmd + sizeof("dir"),
				(unsigned char*)d_name, sizeof(d_name), NULL,
				NULL, NULL) == ERR_OK)
		{
			curdir = uffs_opendir(d_name);
			res = uffs_get_error();
		}
		else
		{
			CLS1_SendStr((unsigned char*) "reading directory name failed!\r\n",
					io->stdErr);
			res = ERR_FAILED;
		}
	}
	// else use current directory
	struct uffs_dirent *entry;
	
	if (curdir == NULL)
	{
		CLS1_SendStr((unsigned char*) "can't open dir\r\n", io->stdErr);
		res = ERR_FAILED;
	}
	uffs_rewinddir(curdir);

	while ((entry = uffs_readdir(curdir)))
	{
		MSGLN( "%s", entry->d_name);
	}
	// unless it was cwd close it
	if (*(cmd + sizeof("dir") - 1) == ' ')
		uffs_closedir(curdir);
	return res;
}


static byte DeleteCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io)
{
	/* precondition: cmd starts with "delete" */
	char f_name[UFFS_PATHSIZE];
	byte res = ERR_OK;

	if (UTIL1_ReadEscapedName(cmd + sizeof("delete"),
			(unsigned char*)f_name, sizeof(f_name), NULL,
			NULL, NULL) == ERR_OK)
	{
		res = uffs_remove( f_name );
		if(uffs_get_error() == UEISDIR)
		{
			res = uffs_rmdir( f_name );
		}
	}
	else
	{
		CmdUsageError(cmd, (unsigned char*) "delete fileName", io);
		res = ERR_FAILED;
	}
	return res;
}



static byte MkdirCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io) {
	/* precondition: cmd starts with "mkdir" */
	char d_name[UFFS_PATHSIZE];
	byte res = ERR_OK;
	if (UTIL1_ReadEscapedName(cmd + sizeof("mkdir"),
			(unsigned char*)d_name, sizeof(d_name), NULL,
			NULL, NULL) == ERR_OK)
	{
		res = uffs_mkdir( d_name );
	} 
	else 
	{
		CmdUsageError(cmd, (unsigned char*)"mkdir directoryName", io);
		res = ERR_FAILED;
	}
	return res;
}

static byte RenameCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io) {
	/* precondition: cmd starts with "rename" */
	char to_name[UFFS_PATHSIZE];
	char from_name[UFFS_PATHSIZE];
	byte res = ERR_OK;
	size_t lenRead;

	if ((UTIL1_ReadEscapedName(cmd+sizeof("rename"), (unsigned char*)from_name,
			sizeof(from_name), &lenRead, NULL, NULL)==ERR_OK)
			&& *(cmd+sizeof("rename")+lenRead)==' '
					&& (UTIL1_ReadEscapedName(cmd+sizeof("rename")+lenRead+1,
							(unsigned char*)to_name, sizeof(to_name), NULL, NULL, NULL)==ERR_OK))
	{
		res = uffs_rename( from_name, to_name );
	} 
	else 
	{
		CmdUsageError(cmd, (unsigned char*)"rename srcFileName dstFileName", io);
		res = ERR_FAILED;
	}
	return res;
}


static byte FormatCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io) {
	/* precondition: cmd starts with "mkdir" */
	char d_name[UFFS_PATHSIZE];
	byte res = ERR_OK;
	if (UTIL1_ReadEscapedName(cmd + sizeof("format"),
			(unsigned char*)d_name, sizeof(d_name), NULL,
			NULL, NULL) == ERR_OK)
	{
		MSGLN("Formatting %s...", d_name);
		res = uffs_format( d_name );
	} 
	else 
	{
		CmdUsageError(cmd, (unsigned char*)"format mountPath", io);
		res = ERR_FAILED;
	}
	return res;
}

#ifdef FAT_SUPPORT
/*!
 * \brief Copy the source file to a destination file
 * \param[in] srcFileName Source file name
 * \param[in] dstFileName Destination file name
 * \param[in] io IO handler for output
 * \return Error code, ERR_OK for success.
 */
byte UFFS_FAT_CopyFile(const byte *srcFileName, const byte *dstFileName, const CLS1_StdIOType *io)
{
	bool sourceUffs = pdTRUE;	///< source is uffs (otherwise FAT)
	bool destUffs = pdTRUE;		///< destination is uffs (otherwise FAT)
	int fd1=-1, fd2=-1;			// uffs file pointers
	FAT1_FIL fsrc, fdst;  	// FAT file objects
	FAT1_FRESULT fres;		// FAT result
	uint8_t buffer[32];   /* copy buffer */
	UINT br, bw, bt=0;          /* file read/write counters */
	byte res =  ERR_OK;
	
	if( srcFileName[1] == ':')
		sourceUffs = pdFALSE;
	if( dstFileName[1] == ':')
	{
		destUffs = pdFALSE;
		if (FAT1_isWriteProtected() || FAT1_FS_READONLY) 
		{
			MSGLN("destination FAT disk is write protected!");
			return ERR_FAILED;
		}
	}

	/* open source file */
	
	if(sourceUffs)
	{
		fd1 = uffs_open((char*)srcFileName, UO_RDONLY);
		if (fd1  < 0) {
			MSGLN("open source file failed");
			return ERR_FAILED;
		}		
	}
	else
	{
		fres = FAT1_open(&fsrc, (char*)srcFileName, FA_OPEN_EXISTING | FA_READ);
		if (fres != FR_OK) 
			{
				MSGLN("open source file failed. Result=%d", fres);
				return ERR_FAILED;
			}
	}
	
	/* create destination file */
	
	if(destUffs)
	{
		fd2 = uffs_open((char*)dstFileName, UO_CREATE|UO_WRONLY);
		if (fd2  < 0) {
			MSGLN("open destination file failed");
			return ERR_FAILED;
		}		
	}
	else
	{
		fres = FAT1_open(&fdst, (char*)dstFileName, FA_CREATE_ALWAYS | FA_WRITE);
		if (fres != FR_OK) {
			MSGLN("open destination file failed. Result=%d", fres);
			return ERR_FAILED;
		}
	}
	
	/* now copy source to destination */
	
	for (;;) 
	{
		if(sourceUffs)
		{
			br = uffs_read(fd1, buffer, sizeof(buffer));
		}
		else
		{
			fres = FAT1_read(&fsrc, buffer, sizeof(buffer), &br);
			if (fres != FR_OK) 
			{
				MSGLN("reading source file failed. Result=%d", fres);
				res = ERR_FAILED;
				break;
			}
		}
		bt += br;
		if (br == 0) 
		{ /* EOF */
			break; /* get out of loop */
		}
		if(destUffs)
		{
			bw = uffs_write(fd2, buffer, br);
		}
		else
		{
			fres = FAT1_write(&fdst, buffer, br, &bw);
			if (fres != ERR_OK) {
				MSGLN("writing destination file failed. Result=%d", fres);
				res = ERR_FAILED;
				break;
			}			
		}
		if (bw < br) {
			MSGLN("failed writing destination file, or disk full");
			res = ERR_FAILED;
			break;
		}
	} /* for */
	
	/* close all files */
	
	if(sourceUffs)
		uffs_close(fd1);
	else
	{
		fres = FAT1_close(&fsrc);
		if (fres != FR_OK) 
		{
			MSGLN("closing source file failed. Result=%d", fres);
			res = ERR_FAILED;
		}
	}
	if(destUffs)
		uffs_close(fd2);
	else
	{
		fres = FAT1_close(&fdst);
		if (fres != FR_OK) {
			MSGLN("closing destination file failed. Result=%d", fres);
			res = ERR_FAILED;
		}
	}
	MSGLN("%u bytes copied.", bt);
	return res;
}


static byte CopyCmd(const unsigned char *cmd, const CLS1_ConstStdIOType *io) {
	/* precondition: cmd starts with "copy" */
	byte res = ERR_OK;
	size_t lenRead;
	char fileName[UFFS_PATHSIZE];
	char fileName2[UFFS_PATHSIZE];

	if (   (UTIL1_ReadEscapedName(cmd+sizeof("copy"), (unsigned char*)fileName,
			sizeof(fileName), &lenRead, NULL, NULL)==ERR_OK)
			&& *(cmd+sizeof("copy")+lenRead)==' '
					&& (UTIL1_ReadEscapedName(cmd+sizeof("copy")+lenRead+1, (unsigned char*)fileName2,
							sizeof(fileName2), NULL, NULL, NULL)==ERR_OK)
	)
	{
		res = UFFS_FAT_CopyFile((unsigned char*)fileName, (unsigned char*)fileName2, io);
	} else {
		CmdUsageError(cmd, (unsigned char*)"copy srcFileName dstFileName", io);
		res = ERR_FAILED;
	}
	return res;
}
#endif

byte UFFS_PrintDiskInfo(const CLS1_StdIOType *io)
{
	uffs_MountTable *m;
	//uffs_Device *d;
	int i, b = 0, g = 0;
	MSGLN("UFFS disk info:");
	m = get_flash_mount_table();
	while (m->dev)
	{
		MSGLN("Mount point: %s, start: %d, end: %d",
				m->mount, m->start_block, m->end_block);
		MSGLN("Space: %ld Used: %ld Free: %ld",
				uffs_space_total(m->mount), 
				uffs_space_used(m->mount), 
				uffs_space_free(m->mount));
		for(i = m->start_block; i <= m->end_block; i++)
		{
			if(uffs_FlashIsBadBlock(m->dev, i))
				b++;
			else
				g++;
		}
		MSGLN("Blocks: %d good: %d bad: %d (%d %%)", m->end_block - m->start_block + 1, g, b, b*100/(b+g));
		m++;
	}

	return ERR_OK;
}


#ifndef UFFS_BENCHMARK
static byte UFFS_Benchmark(const unsigned char *cmd, const CLS1_ConstStdIOType *io)
{
	uint16_t i, j;
	uint8_t read_buf[10];
	TIMEREC time, startTime;
	int32_t start_mseconds, mseconds;

	int fd, fd2;

	/* write benchmark */
	MSGLN("Benchmark: open file, write 10k times 10 bytes (100'000 bytes), close file:");
	MSGLN("Deleting existing benchmark files...");
	uffs_remove("/bench.txt");
	uffs_remove("/copy.txt");

	MSGLN("Creating benchmark file...");
	(void)TmDt1_GetTime(&startTime);
	fd = uffs_open("/bench.txt", UO_CREATE|UO_WRONLY);
	if (fd  < 0) {
		MSGLN("*** Failed opening benchmark file!");
		return ERR_FAILED;
	}
	for(i=0;i<10000;i++) {
		if (uffs_write(fd, "benchmark ", sizeof("benchmark ")-1) <= 0) {
			MSGLN("*** Failed writing file!");
			uffs_close(fd);
			return ERR_FAILED;
		}
	}
	uffs_close(fd);
	(void)TmDt1_GetTime(&time);
	start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
	mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
	MSGLN("%ld ms needed for creating.",mseconds);

	/* read benchmark */
	MSGLN("Reading benchmark file...");
	(void)TmDt1_GetTime(&startTime);
	fd = uffs_open("/bench.txt", UO_RDONLY);
	if (fd < 0) {
		MSGLN("*** Failed opening benchmark file!");
		return ERR_FAILED;
	}
	for(i=0;i<10000;i++) {
		if (uffs_read(fd, read_buf, sizeof(read_buf)) <= 0) {
			MSGLN("*** Failed reading file!");
			uffs_close(fd);
			return ERR_FAILED;
		}
	}
	uffs_close(fd);
	(void)TmDt1_GetTime(&time);
	start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
	mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
	MSGLN("%ld ms needed for reading.",mseconds);

	/* copy benchmark */
	MSGLN("Copy file (100'000 bytes)...");
	(void)TmDt1_GetTime(&startTime);
	
	fd2 = uffs_open("/copy.txt", UO_CREATE|UO_WRONLY);
	if (fd2  < 0) {
		MSGLN("*** Failed opening copy file!");
		return ERR_FAILED;
	}
	fd = uffs_open("/bench.txt", UO_RDONLY);
	if (fd < 0) {
		MSGLN("*** Failed opening benchmark file!");
		return ERR_FAILED;
	}
	i = 0;
	do
	{
		j = uffs_read(fd, read_buf, sizeof(read_buf));
		i += j;
		if (uffs_write(fd2, read_buf, j) < j) {
			MSGLN("*** Failed writing file!");
			uffs_close(fd);
			uffs_close(fd2);
			return ERR_FAILED;
		}
	} while( j > 0);
	uffs_close(fd);
	uffs_close(fd2);
	
	(void)TmDt1_GetTime(&time);
	start_mseconds = startTime.Hour*60*60*1000 + startTime.Min*60*1000 + startTime.Sec*1000 + startTime.Sec100*10;
	mseconds = time.Hour*60*60*1000 + time.Min*60*1000 + time.Sec*1000 + time.Sec100*10 - start_mseconds;
	MSGLN("%ld ms needed for copy.",mseconds);
	
	return ERR_OK;
}

#endif


/*
** ===================================================================
**     Method      : UFFS_ParseCommand 
**     Description :
**         Shell Command Line parser.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command string
**       * handled         - Pointer to variable which tells if
**                           the command has been handled or not
**       * io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
byte UFFS_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io)
{
	if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
			|| UTIL1_strcmp((char*)cmd, "UFFS help") == 0)
	{
		*handled = TRUE;
		return PrintHelp(io);
	}
	else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS) == 0)
			|| (UTIL1_strcmp((char*)cmd, "UFFS status") == 0))
	{
		*handled = TRUE;
		return PrintStatus(io);
	}
	else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS) == 0)
			|| (UTIL1_strcmp((char*)cmd, "UFFS init") == 0))
	{
		*handled = TRUE;
		return InitCmd(io);
	}
	else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS) == 0)
			|| (UTIL1_strcmp((char*)cmd, "UFFS uninit") == 0))
	{
		*handled = TRUE;
		return UninitCmd(io);
	}
	else if (UTIL1_strncmp((char*)cmd, "UFFS cd", sizeof("UFFS cd")-1) == 0)
	{
		*handled = TRUE;
		return CdCmd(cmd + sizeof("UFFS"), io);
	}
	else if (UTIL1_strncmp((char*)cmd, "UFFS dir", sizeof("UFFS dir")-1) == 0)
	{
		*handled = TRUE;
		return DirCmd(cmd + sizeof("UFFS"), io);
	}
	else if (UTIL1_strncmp((char*)cmd, "UFFS delete", sizeof("UFFS delete")-1) == 0)
	{
		*handled = TRUE;
		return DeleteCmd(cmd + sizeof("UFFS"), io);
	}
	else if (UTIL1_strncmp((char*)cmd, "UFFS mkdir", sizeof("UFFS mkdir")-1) == 0)
	{
		*handled = TRUE;
		return MkdirCmd(cmd + sizeof("UFFS"), io);
	}
	else if (UTIL1_strncmp((char*)cmd, "UFFS format", sizeof("UFFS format")-1) == 0)
	{
		*handled = TRUE;
		return FormatCmd(cmd + sizeof("UFFS"), io);
	}
	else if (UTIL1_strncmp((char*)cmd, "UFFS rename", sizeof("UFFS rename")-1) == 0)
	{
		*handled = TRUE;
		return RenameCmd(cmd + sizeof("UFFS"), io);
	}
#ifdef FAT_SUPPORT
	else if (UTIL1_strncmp((char*)cmd, "UFFS copy", sizeof("UFFS copy")-1) == 0) 
	{
	    *handled = TRUE;
	    return CopyCmd(cmd+sizeof("UFFS"), io);
	}
#endif
	else if (UTIL1_strcmp((char*)cmd, "UFFS diskinfo") == 0)
	{
		*handled = TRUE;
		return UFFS_PrintDiskInfo(io);
	}
	else if (UTIL1_strcmp((char*)cmd, "UFFS benchmark") == 0)
	{
		*handled = TRUE;
		return UFFS_Benchmark(cmd + sizeof("UFFS"), io);
	}
	return ERR_OK;
}



