//----------------------------------------------------------------------------
// excel_common.h
//----------------------------------------------------------------------------
#ifdef	_EXCEL_COMMON_H_
#pragma message ("    HINT: " __FILE__ " included multiple times in this translation unit")
#else
#define _EXCEL_COMMON_H_

//----------------------------------------------------------------------------
// INCLUDE
//----------------------------------------------------------------------------
#ifndef _APPCOMMON_H_
#include "appcommon.h"
#endif

//----------------------------------------------------------------------------
// CONSTANTS
//----------------------------------------------------------------------------
#if ISVERSION(DEVELOPMENT) || ISVERSION(SERVER_VERSION)
#define	EXCEL_FILE_LINE								1
#else
#define	EXCEL_FILE_LINE								0
#endif

#define COOKED_FILE_EXTENSION												"cooked"					// extension for cooked file names
#define EXCEL_LINK_INVALID													((EXCEL_LINK)-1)
#define EXCEL_STR_INVALID													(-1)
#define NaN																	(Math_GetNaN())
#define EXCEL_MAX_FIELD_LEN						65536						// maximum field length
#define EXCEL_STRING_TABLE_MAX_LANGUAGES		64							// maximum number of languages


//----------------------------------------------------------------------------
// ENUMS
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
enum EXCEL_SET_FIELD_RESULT
{
	ESFR_OK,			// field set
	ESFR_ERROR,			// error occurred
	ESFR_INHERITED,		// row has now been inherited
};


enum EXCEL_APP_VERSION_FLAG
{
	EXCEL_APP_VERSION_HELLGATE =											MAKE_MASK(0),
	EXCEL_APP_VERSION_TUGBOAT =												MAKE_MASK(1),

	EXCEL_APP_VERSION_ALL =													EXCEL_APP_VERSION_HELLGATE | EXCEL_APP_VERSION_TUGBOAT,
	EXCEL_APP_VERSION_DEFAULT =												EXCEL_APP_VERSION_ALL,

	EXCEL_PACKAGE_VERSION_DEVELOPMENT =										MAKE_MASK(0),
	EXCEL_PACKAGE_VERSION_DEMO =											MAKE_MASK(1),
	EXCEL_PACKAGE_VERSION_BETA =											MAKE_MASK(2),
	EXCEL_PACKAGE_VERSION_RELEASE =											MAKE_MASK(3),
	EXCEL_PACKAGE_VERSION_ONGOING =											MAKE_MASK(4),
	EXCEL_PACKAGE_VERSION_EXPANSION =										MAKE_MASK(5),
	
	EXCEL_PACKAGE_VERSION_ALL =												EXCEL_PACKAGE_VERSION_DEVELOPMENT | EXCEL_PACKAGE_VERSION_DEMO | 
																			EXCEL_PACKAGE_VERSION_BETA |
																			EXCEL_PACKAGE_VERSION_RELEASE | EXCEL_PACKAGE_VERSION_ONGOING | EXCEL_PACKAGE_VERSION_EXPANSION,

	EXCEL_PACKAGE_VERSION_DEFAULT =											EXCEL_PACKAGE_VERSION_DEVELOPMENT | EXCEL_PACKAGE_VERSION_DEMO |
																			EXCEL_PACKAGE_VERSION_BETA |
																			EXCEL_PACKAGE_VERSION_RELEASE | EXCEL_PACKAGE_VERSION_ONGOING | EXCEL_PACKAGE_VERSION_EXPANSION,
};


//----------------------------------------------------------------------------
// MACROS
//----------------------------------------------------------------------------
#define EXCEL_STRUCT_DEF(s)													template <class T>void ExcelRegisterStruct_##s(void) { struct EXCEL_STRUCT * excelStruct = ExcelRegisterStructBegin(#s, sizeof(s));  if (!excelStruct) { return; }
#define EXCEL_STRUID_DEF(n, s)												template <class T>void ExcelRegisterStruct_##n(void) { struct EXCEL_STRUCT * excelStruct = ExcelRegisterStructBegin(#n, sizeof(s));  if (!excelStruct) { return; }
#define EXCEL_STRUCT_END													ExcelRegisterStructEnd(excelStruct); }

// helper macros
#define EX_SIZEOF(s, m)														sizeof((((s *)0)->m))
#define EX_ARRSIZE(s, m)													arrsize((((s *)0)->m))

#define EXCEL_INDEX_DEF(n, kf)												template <class T>void ExcelRegisterStruct_##n(void) { struct EXCEL_STRUCT * excelStruct = ExcelRegisterStructBegin(#n, sizeof(EXCEL_INDEX_TABLE));  if (!excelStruct) { return; } \
																			ExcelRegisterFieldCharString(excelStruct, EXCEL_FIELDTYPE_STRING, kf, (unsigned int)OFFSET(EXCEL_INDEX_TABLE, szIndex), EX_ARRSIZE(EXCEL_INDEX_TABLE, szIndex), 0);		EXCEL_SET_INDEX(0, EXCEL_INDEX_WARN_DUPLICATE, kf)		EXCEL_STRUCT_END

// field definitions
#define EF_STRING(n, m, ...)												ASSERT(EX_SIZEOF(T, m[0]) == sizeof(char)); ExcelRegisterFieldCharString(excelStruct, EXCEL_FIELDTYPE_STRING, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), 0, __VA_ARGS__);
#define EF_DSTRING(n, m, ...)												ASSERT(EX_SIZEOF(T, m) == sizeof(const char *)); ExcelRegisterFieldDynamicString(excelStruct, EXCEL_FIELDTYPE_DYNAMIC_STRING, n, (unsigned int)OFFSET(T, m), 0, __VA_ARGS__);
#define EF_DSTRELE(n, m, i, ...)											ASSERT(EX_SIZEOF(T, m[0]) == sizeof(const char *)); ExcelRegisterFieldDynamicStringArrayElement(excelStruct, EXCEL_FIELDTYPE_DYNAMIC_STRING, n, (unsigned int)OFFSET(T, m[i]), (unsigned int)OFFSET(T, m[0]) + i * 8, 0, __VA_ARGS__);
#define EF_FILE(n, m, ...)													EF_STRING(n, m, __VA_ARGS__)
#define EF_STR_LOWER(n, m, ...)												ASSERT(EX_SIZEOF(T, m[0]) == sizeof(char)); ExcelRegisterFieldCharString(excelStruct, EXCEL_FIELDTYPE_STRING, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), EXCEL_STRING_LOWER, __VA_ARGS__);
#define EF_DSTR_LOWER(n, m, ...)											ASSERT(EX_SIZEOF(T, m) == sizeof(const char *)); ExcelRegisterFieldDynamicString(excelStruct, EXCEL_FIELDTYPE_DYNAMIC_STRING, n, (unsigned int)OFFSET(T, m), EXCEL_STRING_LOWER, __VA_ARGS__);
#define EF_STRINT(n, m, ...)												ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldStringInt(excelStruct, EXCEL_FIELDTYPE_STRINT, n, (unsigned int)OFFSET(T, m));
#define EF_FLAG(n, m, b, ...)												ASSERT(EX_SIZEOF(T, m) * 8 >= b); ExcelRegisterFieldFlag(excelStruct, EXCEL_FIELDTYPE_FLAG, n, (unsigned int)OFFSET(T, m), b, __VA_ARGS__);
#define EF_CHAR(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(char)); ExcelRegisterFieldChar(excelStruct, EXCEL_FIELDTYPE_CHAR, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_BYTE(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(BYTE)); ExcelRegisterFieldByte(excelStruct, EXCEL_FIELDTYPE_BYTE, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_SHORT(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(short)); ExcelRegisterFieldShort(excelStruct, EXCEL_FIELDTYPE_SHORT, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_WORD(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(WPRD)); ExcelRegisterFieldWord(excelStruct, EXCEL_FIELDTYPE_WORD, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_INT(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldInt(excelStruct, EXCEL_FIELDTYPE_INT, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_DWORD(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(DWORD)); ExcelRegisterFieldDword(excelStruct, EXCEL_FIELDTYPE_DWORD, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_BOOL(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(BOOL)); ExcelRegisterFieldBool(excelStruct, EXCEL_FIELDTYPE_BOOL, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_FLOAT(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(float)); ExcelRegisterFieldFloat(excelStruct, EXCEL_FIELDTYPE_FLOAT, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_FLOAT_PCT(n, m, ...)												ASSERT(EX_SIZEOF(T, m) == sizeof(float)); ExcelRegisterFieldFloatPercent(excelStruct, EXCEL_FIELDTYPE_FLOAT, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_BYTE_PCT(n, m, ...)												ASSERT(EX_SIZEOF(T, m) == sizeof(BYTE)); ExcelRegisterFieldBytePercent(excelStruct, EXCEL_FIELDTYPE_BYTE_PERCENT, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_FOURCC(n, m, ...)												ASSERT(EX_SIZEOF(T, m) == sizeof(DWORD)); ExcelRegisterFieldFourCC(excelStruct, EXCEL_FIELDTYPE_FOURCC, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_THREECC(n, m, ...)												ASSERT(EX_SIZEOF(T, m) == sizeof(DWORD)); ExcelRegisterFieldThreeCC(excelStruct, EXCEL_FIELDTYPE_THREECC, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_TWOCC(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(WORD)); ExcelRegisterFieldTwoCC(excelStruct, EXCEL_FIELDTYPE_TWOCC, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_ONECC(n, m, ...)													ASSERT(EX_SIZEOF(T, m) == sizeof(BYTE)); ExcelRegisterFieldOneCC(excelStruct, EXCEL_FIELDTYPE_ONECC, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_LINK_CHAR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m) == sizeof(char)); ExcelRegisterFieldLinkChar(excelStruct, EXCEL_FIELDTYPE_LINK_CHAR, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_SHORT(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m) == sizeof(short)); ExcelRegisterFieldLinkShort(excelStruct, EXCEL_FIELDTYPE_LINK_SHORT, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_INT(n, m, tbl, ...)											ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldLinkInt(excelStruct, EXCEL_FIELDTYPE_LINK_INT, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_FOURCC(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m) == sizeof(DWORD)); ExcelRegisterFieldLinkFourCC(excelStruct, EXCEL_FIELDTYPE_LINK_FOURCC, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_THREECC(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m) == sizeof(DWORD)); ExcelRegisterFieldLinkThreeCC(excelStruct, EXCEL_FIELDTYPE_LINK_THREECC, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_TWOCC(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m) == sizeof(WORD)); ExcelRegisterFieldLinkTwoCC(excelStruct, EXCEL_FIELDTYPE_LINK_TWOCC, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_ONECC(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m) == sizeof(BYTE)); ExcelRegisterFieldLinkOneCC(excelStruct, EXCEL_FIELDTYPE_LINK_ONECC, n, (unsigned int)OFFSET(T, m), tbl, __VA_ARGS__);
#define EF_LINK_TABLE(n, m, ...)											ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldLinkTable(excelStruct, EXCEL_FIELDTYPE_LINK_TABLE, n, (unsigned int)OFFSET(T, m), __VA_ARGS__);
#define EF_LINK_STAT(n, s, t, ...)											ExcelRegisterFieldLinkStat(excelStruct, EXCEL_FIELDTYPE_LINK_STAT, n, s, t, __VA_ARGS__);
#define EF_DICT_CHAR(n, m, dict)											ASSERT(EX_SIZEOF(T, m) == sizeof(char)); ExcelRegisterFieldDictChar(excelStruct, EXCEL_FIELDTYPE_DICT_CHAR, n, (unsigned int)OFFSET(T, m), dict, arrsize(dict));
#define EF_DICT_SHORT(n, m, dict)											ASSERT(EX_SIZEOF(T, m) == sizeof(short)); ExcelRegisterFieldDictShort(excelStruct, EXCEL_FIELDTYPE_DICT_SHORT, n, (unsigned int)OFFSET(T, m), dict, arrsize(dict)); 
#define EF_DICT_INT(n, m, dict)												ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldDictInt(excelStruct, EXCEL_FIELDTYPE_DICT_INT, n, (unsigned int)OFFSET(T, m), dict, arrsize(dict));
#define EF_DICT_INT_ARR(n, m, dict, ...)									ASSERT(EX_SIZEOF(T, m[0]) == sizeof(int)); ExcelRegisterFieldDictIntArray(excelStruct, EXCEL_FIELDTYPE_DICT_INT_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), dict, arrsize(dict), __VA_ARGS__);
#define EF_CARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(char)); ExcelRegisterFieldCharArray(excelStruct, EXCEL_FIELDTYPE_CHAR_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_BARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(BYTE)); ExcelRegisterFieldByteArray(excelStruct, EXCEL_FIELDTYPE_BYTE_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_SARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(short)); ExcelRegisterFieldShortArray(excelStruct, EXCEL_FIELDTYPE_SHORT_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_WARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(WORD)); ExcelRegisterFieldWordArray(excelStruct, EXCEL_FIELDTYPE_WORD_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_IARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(int)); ExcelRegisterFieldIntArray(excelStruct, EXCEL_FIELDTYPE_INT_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_DARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(DWORD)); ExcelRegisterFieldDwordArray(excelStruct, EXCEL_FIELDTYPE_DWORD_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_FARR(n, m, ...)													ASSERT(EX_SIZEOF(T, m[0]) == sizeof(DWORD)); ExcelRegisterFieldFloatArray(excelStruct, EXCEL_FIELDTYPE_FLOAT_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_LINK_BARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(BYTE)); ExcelRegisterFieldLinkByteArray(excelStruct, EXCEL_FIELDTYPE_LINK_BYTE_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_WARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(WORD)); ExcelRegisterFieldLinkWordArray(excelStruct, EXCEL_FIELDTYPE_LINK_WORD_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_IARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(int)); ExcelRegisterFieldLinkIntArray(excelStruct, EXCEL_FIELDTYPE_LINK_INT_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_4CCARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0])) == sizeof(DWORD)); ExcelRegisterFieldLinkFourCCArray(excelStruct, EXCEL_FIELDTYPE_LINK_FOURCC_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_3CCARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(DWORD)); ExcelRegisterFieldLinkThreeCCArray(excelStruct, EXCEL_FIELDTYPE_LINK_THREECC_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_2CCARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(WORD)); ExcelRegisterFieldLinkTwoCCArray(excelStruct, EXCEL_FIELDTYPE_LINK_TWOCC_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_1CCARR(n, m, tbl, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(BYTE)); ExcelRegisterFieldLinkOneCCArray(excelStruct, EXCEL_FIELDTYPE_LINK_ONECC_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), tbl, __VA_ARGS__);
#define EF_LINK_FARR(n, m, tbl, ...)										ExcelRegisterFieldLinkFlagArray(excelStruct, EXCEL_FIELDTYPE_LINK_FLAG_ARRAY, n, (unsigned int)OFFSET(T, m), EX_SIZEOF(T, m) * 8, tbl, __VA_ARGS__);
#define EF_STR_TABLE(n, m, appGame, ...)									ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldStrTableLink(excelStruct, EXCEL_FIELDTYPE_STR_TABLE, n, (unsigned int)OFFSET(T, m), appGame, __VA_ARGS__);
#define EF_IARR_STR(n, m, appGame, ...)										ASSERT(EX_SIZEOF(T, m[0]) == sizeof(int)); ExcelRegisterFieldStrTableLinkArray(excelStruct, EXCEL_FIELDTYPE_STR_TABLE_ARRAY, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), appGame, __VA_ARGS__);
#define EF_FILEID(n, m, path, pak)											ASSERT(EX_SIZEOF(T, m) == sizeof(FILEID)); ExcelRegisterFieldFileid(excelStruct, EXCEL_FIELDTYPE_FILEID, n, (unsigned int)OFFSET(T, m), path, pak);
#define EF_COOKED_FILEID(n, m, path, pak)									ASSERT(EX_SIZEOF(T, m) == sizeof(FILEID)); ExcelRegisterFieldFileid(excelStruct, EXCEL_FIELDTYPE_COOKED_FILEID, n, (unsigned int)OFFSET(T, m), path, pak);
#define EF_CODE(n, m)														ASSERT(EX_SIZEOF(T, m) == sizeof(PCODE)); ExcelRegisterFieldCode(excelStruct, EXCEL_FIELDTYPE_CODE, n, (unsigned int)OFFSET(T, m));
#define EF_DEFCODE(n)														ExcelRegisterFieldDefCode(excelStruct, EXCEL_FIELDTYPE_DEFCODE, n);
#define EF_STAT(n, st, ...)													ExcelRegisterFieldStat(excelStruct, EXCEL_FIELDTYPE_DEFSTAT, n, st, __VA_ARGS__);
#define EF_STAT_FLOAT(n, st, ...)											ExcelRegisterFieldStatFloat(excelStruct, EXCEL_FIELDTYPE_DEFSTAT_FLOAT, n, st, __VA_ARGS__);
#define EF_LINK_UTYPE(n, m, ...)											ASSERT(EX_SIZEOF(T, m[0]) == sizeof(int)); ExcelRegisterFieldUnitTypes(excelStruct, EXCEL_FIELDTYPE_UNITTYPES, n, (unsigned int)OFFSET(T, m), EX_ARRSIZE(T, m), __VA_ARGS__);
#define EF_PARSE(n, m, fp, ...)												ExcelRegisterFieldParse(excelStruct, EXCEL_FIELDTYPE_PARSE, n, (unsigned int)OFFSET(T, m), EX_SIZEOF(T, m), fp, __VA_ARGS__);
#define EF_INHERIT_ROW(n, m)												ASSERT(EX_SIZEOF(T, m) == sizeof(int)); ExcelRegisterFieldInheritRow(excelStruct, EXCEL_FIELDTYPE_INHERIT_ROW, n, (unsigned int)OFFSET(T, m));

// field settings
#define EXCEL_SET_FLAG(fl)													ExcelSetFlags(excelStruct, fl);

// struct settings
#define EXCEL_SET_INDEX(idx, fl, ...)										ExcelSetIndex(excelStruct, idx, fl, __VA_ARGS__);
#define EXCEL_SET_NAMEFIELD(fn)												ExcelSetNameField(excelStruct, fn);
#define EXCEL_SET_ISA(fn)													ExcelSetIsAField(excelStruct, fn);
#define EXCEL_SET_ALLOW_DYNAMIC_STATS();									ExcelSetAllowDynamicStats(excelStruct);
#define EXCEL_SET_POSTINDEX(fp)												ExcelSetPostIndex(excelStruct, fp);
#define EXCEL_SET_POSTPROCESS_ROW(fp)										ExcelSetPostProcessRow(excelStruct, fp);
#define EXCEL_SET_POSTPROCESS_TABLE(fp)										ExcelSetPostProcessTable(excelStruct, fp);
#define EXCEL_SET_POSTPROCESS_ALL(fp)										ExcelSetPostProcessAll(excelStruct, fp);
#define EXCEL_SET_TABLEFREE(fp)												ExcelSetTableFree(excelStruct, fp);
#define EXCEL_SET_ROWFREE(fp)												ExcelSetRowFree(excelStruct, fp);
#define EXCEL_SET_MAXROWS(n)												ExcelSetMaxRows(excelStruct, n);
#define EXCEL_ADD_ANCESTOR(t)												ExcelAddAncestor(excelStruct, t);
#define EXCEL_SET_SELFINDEX()												ExcelSetSelfIndex(excelStruct);

// table definitions
#define EXCEL_TABLE_DEF(i, s, g, p, n)										BOOL ExcelRegisterTable_##i(void) { ExcelRegisterStruct_##s<s>();  EXCEL_TABLE * table = ExcelRegisterTable(i, #s, g, p, n); ASSERT_RETFALSE(table); 
#define EXCEL_TBIDX_DEF(i, s, g, p, n)										BOOL ExcelRegisterTable_##i(void) { ExcelRegisterStruct_##i<s>();  EXCEL_TABLE * table = ExcelRegisterTable(i, #i, g, p, n); ASSERT_RETFALSE(table); 
#define EXCEL_TABLE_NIL(i)													BOOL ExcelRegisterTable_##i(void) { return TRUE; }
#define EXCEL_TABLE_ADD_FILE(n, g, p, ...)									ExcelTableAddFile(table, n, g, p, __VA_ARGS__);
#define EXCEL_TABLE_POST_CREATE(data)										ExcelSetPostCreate(table, (const void *)data, arrsize(data));
#define EXCEL_TABLE_SET_TRACE												ExcelSetTableTrace(table);
#define EXCEL_TABLE_SET_NOLOAD												ExcelSetTableNoLoad(table);
#define EXCEL_TABLE_SET_NAME(n, s)											ExcelSetTableName(table, n, s);
#define EXCEL_TABLE_END														return TRUE; }

// table list macros
#define EXCEL_TABLES_BEGIN													BOOL ExcelInit(const EXCEL_LOAD_MANIFEST & manifest) { /*ExcelCommonInit();*/ ExcelRegisterStart(); RegisterExcelFunctions();	// this function should be defined in calling file
#define EXCEL_TABLES_END													ScriptRegisterTableNames(); BOOL result = ExcelInitManifest(manifest); ExcelRegisterEnd(); return result; }
#define EXCEL_TABLE(i)														extern BOOL ExcelRegisterTable_##i(void); ExcelRegisterTable_##i();


//----------------------------------------------------------------------------
// ENUMS
//----------------------------------------------------------------------------
enum EXCEL_INDEX_FLAG
{
	EXCEL_INDEX_WARN_DUPLICATE =											MAKE_MASK(0),
	EXCEL_INDEX_WARN_DUPLICATE_NONBLANK =									MAKE_MASK(1),
	EXCEL_INDEX_DONT_ADD_BLANK =											MAKE_MASK(2),
};


enum EXCEL_STRING_FLAG
{
	EXCEL_STRING_LOWER =													MAKE_MASK(0),
};


enum EXCEL_TABLE_SCOPE
{
	EXCEL_TABLE_SHARED,														// common data table that is shared between all games (hellgate, mythos, etc)
	EXCEL_TABLE_PRIVATE,													// data table is not shared
};


enum EXCEL_FIELDTYPE
{
	EXCEL_FIELDTYPE_INVALID,
	EXCEL_FIELDTYPE_STRING,													// fixed-size char array
	EXCEL_FIELDTYPE_DYNAMIC_STRING,											// string pointer
	EXCEL_FIELDTYPE_STRINT,													// parse a string, store as int based on str dictionary in field
	EXCEL_FIELDTYPE_FLAG,													// bit flag
	EXCEL_FIELDTYPE_CHAR,													// char
	EXCEL_FIELDTYPE_BYTE,													// byte
	EXCEL_FIELDTYPE_SHORT,													// short
	EXCEL_FIELDTYPE_WORD,													// word
	EXCEL_FIELDTYPE_INT,													// int
	EXCEL_FIELDTYPE_DWORD,													// dword
	EXCEL_FIELDTYPE_BOOL,													// boolean
	EXCEL_FIELDTYPE_FLOAT,													// float  (should implement float_percent as extended data)
	EXCEL_FIELDTYPE_BYTE_PERCENT,											// translate a float point percent into a byte
	EXCEL_FIELDTYPE_FOURCC,													// four-character code
	EXCEL_FIELDTYPE_THREECC,												// three-character code
	EXCEL_FIELDTYPE_TWOCC,													// two-character code
	EXCEL_FIELDTYPE_ONECC,													// one-character code
	EXCEL_FIELDTYPE_LINK_CHAR,												// index link, stored as char
	EXCEL_FIELDTYPE_LINK_SHORT,												// index link, stored as short
	EXCEL_FIELDTYPE_LINK_INT,												// index link, stored as int
	EXCEL_FIELDTYPE_LINK_FOURCC,											// index link
	EXCEL_FIELDTYPE_LINK_THREECC,											// index link
	EXCEL_FIELDTYPE_LINK_TWOCC,												// index link
	EXCEL_FIELDTYPE_LINK_ONECC,												// index link
	EXCEL_FIELDTYPE_LINK_TABLE,												// link to datatable index
	EXCEL_FIELDTYPE_LINK_STAT,												// sets a particular stat in the default stats to a index link
	EXCEL_FIELDTYPE_DICT_CHAR,												// link to strdictionary entry defined in subheader or code
	EXCEL_FIELDTYPE_DICT_SHORT,												// link to strdictionary entry defined in subheader or code
	EXCEL_FIELDTYPE_DICT_INT,												// link to strdictionary entry defined in subheader or code
	EXCEL_FIELDTYPE_DICT_INT_ARRAY,											// array of links to strdictionary entry defined in subheader of code
	EXCEL_FIELDTYPE_CHAR_ARRAY,												// char array
	EXCEL_FIELDTYPE_BYTE_ARRAY,												// byte array
	EXCEL_FIELDTYPE_SHORT_ARRAY,											// short array
	EXCEL_FIELDTYPE_WORD_ARRAY,												// word array
	EXCEL_FIELDTYPE_INT_ARRAY,												// int array
	EXCEL_FIELDTYPE_DWORD_ARRAY,											// dword array
	EXCEL_FIELDTYPE_FLOAT_ARRAY,											// float array
	EXCEL_FIELDTYPE_LINK_BYTE_ARRAY,										// array of EXCEL_FIELDTYPE_LINK_BYTE
	EXCEL_FIELDTYPE_LINK_WORD_ARRAY,										// array of EXCEL_FIELDTYPE_LINK_WORD
	EXCEL_FIELDTYPE_LINK_INT_ARRAY,											// array of EXCEL_FIELDTYPE_LINK_INT
	EXCEL_FIELDTYPE_LINK_FOURCC_ARRAY,										// array of EXCEL_FIELDTYPE_LINK_FOURCC
	EXCEL_FIELDTYPE_LINK_THREECC_ARRAY,										// array of EXCEL_FIELDTYPE_LINK_THREECC
	EXCEL_FIELDTYPE_LINK_TWOCC_ARRAY,										// array of EXCEL_FIELDTYPE_LINK_TWOCC
	EXCEL_FIELDTYPE_LINK_ONECC_ARRAY,										// array of EXCEL_FIELDTYPE_LINK_TWOCC
	EXCEL_FIELDTYPE_LINK_FLAG_ARRAY,										// array of EXCEL_FIELDTYPE_LINKS expressed as flags (index = flag offset)
	EXCEL_FIELDTYPE_STR_TABLE,												// string table link
	EXCEL_FIELDTYPE_STR_TABLE_ARRAY,										// array of string table links
	EXCEL_FIELDTYPE_FILEID,													// link to a file
	EXCEL_FIELDTYPE_COOKED_FILEID,											// link to a file (add cooked extension)
	EXCEL_FIELDTYPE_CODE,													// script code
	EXCEL_FIELDTYPE_DEFCODE,												// runs a script on the default stats
	EXCEL_FIELDTYPE_DEFSTAT,												// sets a particular stat in the default stats
	EXCEL_FIELDTYPE_DEFSTAT_FLOAT,											// sets a particular floating-point stat in the default stats
	EXCEL_FIELDTYPE_UNITTYPES,												// unit and not unit (exceptions) array
	EXCEL_FIELDTYPE_PARSE,													// parse callback
	EXCEL_FIELDTYPE_INHERIT_ROW,											// specifies a type of row which points to a row to be inherited
	EXCEL_FIELDTYPE_VERSION_APP,											// version app flags
	EXCEL_FIELDTYPE_VERSION_PACKAGE,										// version package flags
	EXCEL_FIELDTYPE_VERSION_MAJOR,											// version major flags
	EXCEL_FIELDTYPE_VERSION_MINOR,											// version minor flags

	NUM_EXCEL_FIELDTYPE
};


//----------------------------------------------------------------------------
// TYPES
//----------------------------------------------------------------------------
struct EXCEL_INDEX;
struct EXCEL_STRUCT;
struct EXCEL_TABLE;

typedef unsigned int	EXCEL_LINK;

typedef BOOL EXCEL_POSTPROCESS(EXCEL_TABLE * table);
typedef BOOL EXCEL_POSTPROCESS_ROW(EXCEL_TABLE * table, unsigned int row, BYTE * rowdata);
typedef void EXCEL_ROW_FREE(EXCEL_TABLE * table, BYTE * rowdata);

typedef EXCEL_SET_FIELD_RESULT EXCEL_PARSEFUNC(EXCEL_TABLE * table, const struct EXCEL_FIELD * field, unsigned int row, BYTE * fielddata, const char * token, unsigned int toklen, int param);

// imported functions from prime for specialized fields
typedef BYTE * EXCEL_SCRIPTPARSE(struct GAME * game, const char * token, BYTE * buf, int len, int errorlog, const char * errorstr);
typedef struct STATS * EXCEL_STATSLIST_INIT(struct GAME * game);
typedef void EXCEL_STATSLIST_FREE(struct GAME * game, struct STATS * stats);
typedef int EXCEL_SCRIPT_EXECUTE(struct GAME * game, struct UNIT * subject, struct UNIT * object, struct STATS * statslist, BYTE * buf, int len, const char * errorstr);
typedef int EXCEL_STATS_GET_STAT(struct STATS * statslist, int wStat, DWORD dwParam);
typedef void EXCEL_STATS_SET_STAT(struct GAME * game, STATS * stats, int wStat, DWORD dwParam, int nValue);
typedef float EXCEL_STATS_GET_STAT_FLOAT(struct GAME * game, struct STATS * statslist, int wStat, DWORD dwParam);
typedef void EXCEL_STATS_SET_STAT_FLOAT(struct GAME * game, STATS * stats, int wStat, DWORD dwParam, float fValue);
typedef BOOL EXCEL_STATS_WRITE_STATS(struct GAME * game, STATS * stats,	BIT_BUF & buf, enum STATS_WRITE_METHOD eMethod);
typedef BOOL EXCEL_STATS_READ_STATS(struct GAME * game, STATS * stats, BIT_BUF & buf, enum STATS_WRITE_METHOD eMethod);
typedef BOOL EXCEL_STATS_PARSE_TOKEN(const char * token, int & wStat, DWORD & dwParam);
typedef BOOL EXCEL_SCRIPT_ADD_MARKER(unsigned int id);
typedef BOOL EXCEL_SCRIPT_WRITE_TO_PAK(unsigned int id, WRITE_BUF_DYNAMIC & buf);
typedef BOOL EXCEL_SCRIPT_READ_FROM_PAK(BYTE_BUF & buf);
typedef DWORD EXCEL_SCRIPT_GET_IMPORT_CRC(void);
typedef enum EXCEL_UPDATE_STATE EXCEL_STRING_TABLES_LOAD(void);



//----------------------------------------------------------------------------
// STRUCTS
//----------------------------------------------------------------------------
// this is the manifest used during pakfile generation & excel translation
// that determines what lines to read
struct EXCEL_LOAD_MANIFEST
{
	DWORD										m_VersionApp;
	DWORD										m_VersionPackage;
	WORD										m_VersionMajorMin;
	WORD										m_VersionMajorMax;
	WORD										m_VersionMinorMin;
	WORD										m_VersionMinorMax;
	EXCEL_LOAD_MANIFEST(void);
};

// this is used during data access to determine which lines to use
struct EXCEL_READ_MANIFEST
{
	DWORD										m_VersionApp;
	DWORD										m_VersionPackage;
	WORD										m_VersionMajor;
	WORD										m_VersionMinor;
	EXCEL_READ_MANIFEST(void);
};

struct EXCEL_CONTEXT
{
	struct GAME *								game;
	EXCEL_READ_MANIFEST							manifest;

	EXCEL_CONTEXT() : game(0) {};
	EXCEL_CONTEXT(struct GAME * in_game) : game(in_game) {};
};

struct EXCEL_INDEX_TABLE
{
	char szIndex[DEFAULT_INDEX_SIZE];
};

struct EXCEL_TABLE_DEFINITION
{
	char szName[DEFAULT_INDEX_SIZE];
	WORD wCode;
};


//----------------------------------------------------------------------------
// FUNCTIONS
//----------------------------------------------------------------------------
BOOL ExcelInitManifest(
	const EXCEL_LOAD_MANIFEST & manifest);

void ExcelCommonInit(
	void);

void ExcelFree(
	void);

void ExcelRegisterStart(
	void);

void ExcelRegisterEnd(
	void);

void ExcelRegisterImports(
	EXCEL_SCRIPTPARSE * fpScriptParse,
	EXCEL_STATSLIST_INIT * fpStatsListInit,
	EXCEL_STATSLIST_FREE * fpStatsListFree,
	EXCEL_SCRIPT_EXECUTE * fpScriptExecute,
	EXCEL_STATS_GET_STAT * fpStatsGetStat,
	EXCEL_STATS_SET_STAT * fpStatsSetStat,
	EXCEL_STATS_GET_STAT_FLOAT * fpStatsGetStatFloat,
	EXCEL_STATS_SET_STAT_FLOAT * fpStatsSetStatFloat,
	EXCEL_STATS_WRITE_STATS * fpStatsWriteStats,
	EXCEL_STATS_READ_STATS * fpStatsReadStats,
	EXCEL_STATS_PARSE_TOKEN * fpStatsParseToken,
	EXCEL_SCRIPT_ADD_MARKER * fpScriptAddMarker,
	EXCEL_SCRIPT_WRITE_TO_PAK * fpScriptWriteToPak,
	EXCEL_SCRIPT_READ_FROM_PAK * fpScriptReadFromPak,
	EXCEL_SCRIPT_GET_IMPORT_CRC * fpScriptGetImportCRC,
	EXCEL_STRING_TABLES_LOAD * fpStringTablesLoad);

EXCEL_TABLE * ExcelRegisterTable(
	unsigned int idTable,
	const char * structName,
	APP_GAME appGame,
	EXCEL_TABLE_SCOPE scope,
	const char * name,
	unsigned int data1 = 0);

BOOL ExcelTableAddFile(
	EXCEL_TABLE * table,
	const char * filename,
	APP_GAME appGame,
	EXCEL_TABLE_SCOPE scope,
	unsigned int data1 = 0);

BOOL ExcelSetPostCreate(
	EXCEL_TABLE * table,
	const void * data, 
	unsigned int size);

void ExcelSetTableTrace(
	EXCEL_TABLE * table);

EXCEL_STRUCT * ExcelRegisterStructBegin(
	const char * name,
	unsigned int size);

void ExcelRegisterStructEnd(
	EXCEL_STRUCT * excelStruct);

void ExcelRegisterFieldCharString(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft,
	const char * name,
	unsigned int offset,
	unsigned int len,
	DWORD flags,
	const char * defaultValue = NULL);

void ExcelRegisterFieldDynamicString(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft,
	const char * name,
	unsigned int offset,
	DWORD flags,
	const char * defaultValue = NULL);

void ExcelRegisterFieldDynamicStringArrayElement(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft,
	const char * name,
	unsigned int offset,
	unsigned int offset64,
	DWORD flags,
	const char * defaultValue = NULL);

void ExcelRegisterFieldStringInt(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft,
	const char * name,
	unsigned int offset);

void ExcelRegisterFieldFlag(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft,
	const char * name,
	unsigned int offset,
	unsigned int bit,
	BOOL defaultValue = FALSE);							

void ExcelRegisterFieldChar(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	char defaultValue = 0);

void ExcelRegisterFieldByte(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	BYTE defaultValue = 0);

void ExcelRegisterFieldShort(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	short defaultValue = 0);

void ExcelRegisterFieldWord(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	WORD defaultValue = 0);

void ExcelRegisterFieldInt(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	int defaultValue = 0);

void ExcelRegisterFieldDword(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	DWORD defaultValue = 0);

void ExcelRegisterFieldBool(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	BOOL defaultValue = FALSE);

void ExcelRegisterFieldFloat(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	float defaultValue = 0.0f);

void ExcelRegisterFieldFloatPercent(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	float defaultValue = 0.0f);

void ExcelRegisterFieldBytePercent(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	float defaultValue = 0.0f);

void ExcelRegisterFieldFourCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	const char * defaultValue = NULL);

void ExcelRegisterFieldThreeCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	const char * defaultValue = NULL);

void ExcelRegisterFieldTwoCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	const char * defaultValue = NULL);

void ExcelRegisterFieldOneCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkChar(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkShort(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkInt(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkFourCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkThreeCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkTwoCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkOneCC(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkTable(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	int defaultValue = EXCEL_LINK_INVALID);
								 
void ExcelRegisterFieldLinkStat(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int stat,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldDictChar(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	struct STR_DICT * dict,
	unsigned int max,
	const char * defaultValue = NULL);

void ExcelRegisterFieldDictShort(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	struct STR_DICT * dict,
	unsigned int max,
	const char * defaultValue = NULL);

void ExcelRegisterFieldDictInt(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	const struct STR_DICT * dict,
	unsigned int max,
	const char * defaultValue = NULL);

void ExcelRegisterFieldDictIntArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	const STR_DICT * dict,
	unsigned int max,	
	const char * defaultValue = NULL);
		
void ExcelRegisterFieldCharArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	char defaultValue = 0);
						
void ExcelRegisterFieldByteArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	BYTE defaultValue = 0);
						
void ExcelRegisterFieldShortArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	short defaultValue = 0);
						
void ExcelRegisterFieldWordArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	WORD defaultValue = 0);

void ExcelRegisterFieldIntArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	int defaultValue = 0);

void ExcelRegisterFieldDwordArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	DWORD defaultValue = 0);

void ExcelRegisterFieldFloatArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	float defaultValue = 0.0f);

void ExcelRegisterFieldLinkByteArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);
						
void ExcelRegisterFieldLinkWordArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);
							
void ExcelRegisterFieldLinkIntArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldLinkFlagArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0);
									 
void ExcelRegisterFieldLinkFourCCArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);
						
void ExcelRegisterFieldLinkThreeCCArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);
						
void ExcelRegisterFieldLinkTwoCCArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);
						
void ExcelRegisterFieldLinkOneCCArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	unsigned int idTable,
	unsigned int idIndex = 0,
	const char * defaultValue = NULL);

void ExcelRegisterFieldStrTableLink(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	enum APP_GAME appGame,
	const char * defaultValue = NULL);

void ExcelRegisterFieldStrTableLinkArray(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int count,
	enum APP_GAME appGame,
	const char * defaultValue = NULL);

void ExcelRegisterFieldFileid(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft,
	const char * name,
	unsigned int offset,
	const char * path,
	unsigned int pakid);

void ExcelRegisterFieldCode(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset);						

void ExcelRegisterFieldDefCode(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name);
					
void ExcelRegisterFieldStat(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	int wStat,
	int defaultValue = 0,
	DWORD dwParam = 0);

void ExcelRegisterFieldStatFloat(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	int wStat,
	float defaultValue = 0.0f,
	DWORD dwParam = 0);

void ExcelRegisterFieldUnitTypes(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int size,
	const char * defaultValue = NULL);						
							
void ExcelRegisterFieldParse(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset,
	unsigned int size,
	EXCEL_PARSEFUNC * fpParseFunc,
	int param = 0);

void ExcelRegisterFieldInheritRow(
	EXCEL_STRUCT * excelStruct,
	EXCEL_FIELDTYPE eft, 
	const char * name,
	unsigned int offset);

void ExcelSetFlags(
	EXCEL_STRUCT * excelStruct,
	DWORD dwFlags);

void ExcelSetIndex(
	EXCEL_STRUCT * excelStruct,
	unsigned int index,
	DWORD flags,
	const char * field1,
	const char * field2 = NULL,
	const char * field3 = NULL);

void ExcelAddAncestor(
	EXCEL_STRUCT * excelStruct, 
	unsigned int idTable);

void ExcelSetSelfIndex(
	EXCEL_STRUCT * excelStruct);

void ExcelSetNameField(
	EXCEL_STRUCT * excelStruct,
	const char * name);

void ExcelSetIsAField(
	EXCEL_STRUCT * excelStruct,
	const char * name);

void ExcelSetPostIndex(
	EXCEL_STRUCT * excelStruct,
	EXCEL_POSTPROCESS * fpPostProcess);

void ExcelSetPostProcessRow(
	EXCEL_STRUCT * excelStruct,
	EXCEL_POSTPROCESS_ROW * fpPostProcess);

void ExcelSetPostProcessTable(
	EXCEL_STRUCT * excelStruct,
	EXCEL_POSTPROCESS * fpPostProcess);

void ExcelSetPostProcessAll(
	EXCEL_STRUCT * excelStruct,
	EXCEL_POSTPROCESS * fpPostProcess);

void ExcelSetTableFree(
	EXCEL_STRUCT * excelStruct,
	EXCEL_POSTPROCESS * fpTableFree);

void ExcelSetRowFree(
	EXCEL_STRUCT * excelStruct,
	EXCEL_ROW_FREE * fpRowFree);

void ExcelSetMaxRows(
	EXCEL_STRUCT * excelStruct,
	unsigned int max);

void ExcelSetTableNoLoad(
	EXCEL_TABLE * table);

void ExcelSetTableName(
	EXCEL_TABLE * table,
	const char * name,
	EXCEL_TABLE_SCOPE scope);

EXCEL_LINK ExcelGetLineByFourCC(
	unsigned int idTable,
	unsigned int idIndex,
	DWORD fourCC);

EXCEL_LINK ExcelGetLineByThreeCC(
	unsigned int idTable,
	unsigned int idIndex,
	DWORD threeCC);

EXCEL_LINK ExcelGetLineByTwoCC(
	unsigned int idTable,
	unsigned int idIndex,
	WORD twoCC);

EXCEL_LINK ExcelGetLineByOneCC(
	unsigned int idTable,
	unsigned int idIndex,
	BYTE oneCC);

const void * _ExcelGetData(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row
#if EXCEL_FILE_LINE
	,
	 const char * file,
	 unsigned int line
#endif 
	 );

#if EXCEL_FILE_LINE
#define ExcelGetData(ctxt, tbl, rw)		_ExcelGetData(ctxt, tbl, rw, __FILE__, __LINE__)
#else
#define ExcelGetData(ctxt, tbl, rw)		_ExcelGetData(ctxt, tbl, rw)
#endif

void * _ExcelGetDataNotThreadSafe(				// not thread safe
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row
#if EXCEL_FILE_LINE
	,
	 const char * file,
	 unsigned int line
#endif 
	 );

#if EXCEL_FILE_LINE
#define ExcelGetDataNotThreadSafe(ctxt, tbl, rw)		_ExcelGetDataNotThreadSafe(ctxt, tbl, rw, __FILE__, __LINE__)
#else
#define ExcelGetDataNotThreadSafe(ctxt, tbl, rw)		_ExcelGetDataNotThreadSafe(ctxt, tbl, rw)
#endif

const void * ExcelGetDataEx(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row);

DWORD ExcelGetCode(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row);

BOOL ExcelHasScript(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int field_offset,
	unsigned int row);

int ExcelEvalScript(
	const EXCEL_CONTEXT & context,
	struct UNIT * subject,
	struct UNIT * object,
	struct STATS * statslist,
	unsigned int idTable,
	unsigned int field_offset,
	unsigned int row);

struct STATS * ExcelGetStats(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row);

#define ExcelGetNumRows						ExcelGetCount
unsigned int ExcelGetCount(
	const EXCEL_CONTEXT & context,
	unsigned int idTable);

EXCEL_LINK ExcelGetLineByStrKey(
	unsigned int idTable,
	const char * key);

EXCEL_LINK ExcelGetLineByStrKey(
	unsigned int idTable,
	unsigned int idIndex,
	const char * key);

EXCEL_LINK ExcelGetLineByStringIndex(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const char * strkey);

EXCEL_LINK ExcelGetLineByStringIndex(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int idIndex,
	const char * strkey);

const void * ExcelGetDataByStringIndex(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const char * strkey);

void * ExcelGetDataByStringIndexNotThreadSafe(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const char * strkey);

const char * ExcelGetStringIndexByLine(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int idIndex,
	unsigned int row);

const char * ExcelGetStringIndexByLine(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row);

const void * ExcelGetDataByCode(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	DWORD cc);

unsigned int ExcelGetLineByCode(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	DWORD cc);

unsigned int ExcelGetCodeIndex(
	unsigned int idTable);

unsigned int ExcelGetCodeIndexSize(
	unsigned int idTable);

EXCEL_LINK ExcelGetLineByKey(
	unsigned int idTable,
	unsigned int idIndex,
	const void * key,
	unsigned int len);

EXCEL_LINK ExcelGetLineByKey(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const void * key,
	unsigned int len,
	unsigned int idIndex,
	BOOL bExact = TRUE);

EXCEL_LINK ExcelGetNextLineByKey(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const void * key,
	unsigned int len,
	unsigned int idIndex = 0);

EXCEL_LINK ExcelGetPrevLineByKey(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const void * key,
	unsigned int len,
	unsigned int idIndex = 0);

EXCEL_LINK ExcelGetNextLineByStrKey(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const char * strkey,
	unsigned int idIndex = 0);

EXCEL_LINK ExcelGetPrevLineByStrKey(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const char * strkey,
	unsigned int idIndex = 0);

const void * ExcelGetDataByKey(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const void * key,
	unsigned int len,
	unsigned int idIndex = 0);

void * ExcelGetDataByKeyNotThreadSafe(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	const void * key,
	unsigned int len,
	unsigned int idIndex = 0);

BYTE * ExcelGetScriptCode(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	PCODE code_offset,
	int * maxlen = NULL);

BOOL ExcelHasRowNameString(
	const EXCEL_CONTEXT & context,
	unsigned int idTable);

const WCHAR * ExcelGetRowNameString(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int row,
	GRAMMAR_NUMBER eNumber = SINGULAR);

const char * ExcelGetTableName(
	unsigned int idTable);

const char * ExcelTableGetFilePath( 
	unsigned int idTable);

unsigned int ExcelGetFieldByName(
	unsigned int idTable,
	const char * field);

int ExcelLookup(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int idField,
	unsigned int row,
	unsigned int arrayindex = 0);

BOOL ExcelCommonLoadStringTable(
	const char * file,
	int nStringFileIndex,
	BOOL bIsCommon,
	BOOL bForceDirect,
	int nLanguage,
	BOOL bAddToPak);

BOOL ExcelTestIsA(
	const EXCEL_CONTEXT & context,
	unsigned int idTable,
	unsigned int a,
	unsigned int b);

const EXCEL_TABLE_DEFINITION * ExcelTableGetDefinition(
	unsigned int idTable);
	
DWORD ExcelTableGetCode(
	unsigned int idTable);

unsigned int ExcelTableGetByCode(
	DWORD dwCode);

unsigned int ExcelGetTableCount(
	void);

DWORD ExcelGetVersionPackageByString(
	const TCHAR * pszString);

DWORD ExcelGetVersionPackage(
	void);

enum EXCEL_TOK ExcelGetStrTableGetToken(
	WCHAR * & cur,
	WCHAR * & token);

BOOL ExcelStringTableLoadDirectAddHeader( 
	struct LANGUAGE_COLUMN_HEADER * header, 
	WCHAR * str,
	int index);

//----------------------------------------------------------------------------
// INLINE
//----------------------------------------------------------------------------
template <typename T>
inline BOOL ExcelIsLinkInvalid(
	T link)
{
	return (link == (T)EXCEL_LINK_INVALID);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
inline struct EXCEL & Excel(
	void)
{
	extern EXCEL g_Excel;
	return g_Excel;
}

#endif
