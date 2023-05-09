
#ifndef AMPDATABASE_H_
#define AMPDATABASE_H_

/***************************************************************************
 * 
 * Copyright (C) 2015 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		AMPDatabase.h
* Library	 	 : 		AMP Component
* Date Coded  : 		08/04/2015
**************************************************************************/

#include <string>
#include "LinkList.h"
#include "AMPDefine.h"
#include "AMPDataTypes.h"

// Store everything on DB as blob data
#define DB_STORED_AS_BLOB

// Enable Sensitive Data Storage
#define DB_SECURED_SENSITIVE_DATA

// Maximum number of Columns/Field for the database
#define MAX_DB_FIELDS 1024

typedef enum {
	ASCENDING,
	DESCENDING
} DB_DATA_ORDER;

typedef enum {
	INTEGER,		// Integer
	REAL,			// Floating Point, Double
	TEXT,			// String
	BLOB,			// Hex binary
#ifdef DB_SECURED_SENSITIVE_DATA
	ENCIPHERED,		// Encrypted Data
#endif
} DB_DATA_TYPE;

typedef struct {
	char 		 Name[MAX_STR_SZ+1];	// Data Element Name
	DB_DATA_TYPE Type;					// Data Element Type
} DB_DATA_DEFINITION;

typedef struct {
	char 		  Name[MAX_STR_SZ+1];	// Data Element Name
	DB_DATA_TYPE Type;					// Data Element Type
	unsigned char *Data;				// Pointer to Data location
	int			  Size;					// Size of Data
} DB_DATA;

typedef int (*DB_QUERY_CB)(void *NotUsed, int argc, char **argv, char **azColName);

class cDataList : public cLinkList {
	friend class cAMPDatabase;
public:
	
	cDataList();
	~cDataList();
	
	int GetData(const char *key, void *buffer, int buffer_len, DB_DATA_TYPE *Type = NULL);
	int PutData(const char *key, const void *data_buffer, int data_len, DB_DATA_TYPE Type = BLOB);

	DB_DATA* GetFirstData(void);
	DB_DATA* GetNextData(void);

	void ClearAll();
	
protected:
	int FindDataByKey(const char *key);
	void delete_data(void *data);
	
};

class cAMPDatabase {
public:
	
	cAMPDatabase();
	virtual ~cAMPDatabase();

	/*
	* Methods for Databse open/closing
	*/

	int OpenDB(const char* DBFileName);
	int CloseDB(void);
	BOOL IsDBOpen(void);

	/*
	* Methods for Adding/Altering tables in a Database
	*/

	int CreateTable(const char* TableName, DB_DATA_DEFINITION ElementsDef[]);
	int DestroyTable(const char* TableName);
	int DestroyTable(void);
	BOOL IsTableExist(const char* TableName);
	void SelectTable(const char* TableName);
	char* GetSelectedTable(void);

	/*
	* Methods for altering table data
	*	returns the RecordID ( >= 0 ), negative if failed
	*	this methods will be executed base on the currently selected Table
	*/

	// Insert set of data elements as new record (NOTE: Doesn't check for duplicates)
	//	Returns the RecordID (Value of greater than Zero)
	int InsertTableData(cDataList* DataElements);

	// Update existing record
	int UpdateTableData(int RecordID, cDataList* NewDataElements);
	int UpdateTableData(cDataList* Criteria, cDataList* NewDataElements);

	// Delete existing record
	int DeleteTableData(int RecordID);
	int DeleteTableData(cDataList* Criteria);

	/*
	* Methods for Browsing Record
	*	- After Retreiving a Record, subsequently call Retrieve Next or Retrieve Previous to browse through.
	*	- Retrieving Data with Criteria will only return records that matches the Criteria.
	*	- Retrieving w/ RecordID only return 1 Record, since the RecordID is unique.
	*	- Sorting depends on how you store the data on the Elements (SortByElementName). This will be RecordID by default if left NULL.
	*/
	int RetrieveTableData(int RecordID, cDataList* OutDataElements,
					char* SortByElementName = NULL, DB_DATA_ORDER SortByOrder = ASCENDING);
	int RetrieveTableData(cDataList* Criteria, cDataList* OutDataElements,
					char* SortByElementName = NULL, DB_DATA_ORDER SortByOrder = ASCENDING);
	int RetrieveNextTableData(cDataList* OutDataElements);
	int RetrievePreviousTableData(cDataList* OutDataElements);

	// Checks if there is a table data existing base on the criteria specified
	BOOL IsTableDataExist(cDataList* Criteria);

	// Get the number of records currently present on the table
	int GetRecordCount(void);

	// Shrink the size of selected table
	int ShrinkTable(void);

	// Release memory used for any pending query (optional, but suggested to call after completing some retrieval functions)
	void StopQuery(void);

	/*
	* Normalize Record ID of a currently selected Table
	*	- In most cases you don't need to do this
	*	- RecordID is just purely incremental, during many insert/delete process the record id will have unused IDs in between.
	*	   Use this function to make the RecordID normalize 
	*		(e.g. if you have 3 rec that currently have RecID of 2,7, & 9, it will updated to have IDs 1,2, & 3 instead)
	*/
	int NormalizeRecordIDs(void);

	/*
	*	Methods for record data encryption/decryption
	*/

#ifdef DB_SECURED_SENSITIVE_DATA
	void SetKeyEncryptionIndex(int nIndex);
	int GetKeyEncryptionIndex(void);
	int GenerateNewEncryptionKey(void);
	int GetEncryptionKeyKCV(BYTE KCV[3]);
#endif

protected:

	/*
	* 	Methods for Database transasction
	*/
	
	int Begin(void);
	int Commit(void);
	int Rollback(void);

	/*
	* 	SQL Methods
	*/
	
	int CreateTable(const char* TableName, DB_DATA_DEFINITION ElementsDef[], BOOL bTemporary);
	int GetTableFields(const char* TableName, DB_DATA_DEFINITION OutTableField[]);
	int UpdateTableData(int RecordID, cDataList* Criteria, cDataList* NewDataElements);
	int DeleteTableData(int RecordID, cDataList* Criteria);	
	int RetrieveTableData(int RecordID, cDataList* Criteria, cDataList* OutDataElements,
					char* SortByElementName, DB_DATA_ORDER SortByOrder, int CursorStep);
	int ExecuteSQLStatement(cDataList* OutDataElements);

	/*
	* 	Utitlity Functions
	*/

	BOOL IsTableFieldsSame(DB_DATA_DEFINITION OldTableField[], 
					DB_DATA_DEFINITION NewTableField[]);
	int GetCommonTblFld(DB_DATA_DEFINITION TableField1[], 
					DB_DATA_DEFINITION TableField2[],
					DB_DATA_DEFINITION TableFieldCommon[]);
	int CopyTableFields(const char* FromTable, const char* ToTable, DB_DATA_DEFINITION FieldList[]);

protected:
	
	std::string SQL_CMD;

	void* m_DBHandle;
	void* m_DBQuery;

	char m_DBFileName[MAX_FILNAME_SZ+1];
	char m_TableName[MAX_STR_SZ+1];
	DB_DATA_DEFINITION m_TableFldDef[MAX_DB_FIELDS];

	struct {
		int				RecordID;
		cDataList*		Criteria;
		char*			SortByElement;
		DB_DATA_ORDER	SortByOrder;
		char			CurrentValue[MAX_DB_FIELDS+1];
	} m_Cursor;

private:
#ifdef DB_SECURED_SENSITIVE_DATA
	//4 Index where to get the key for encrypting/decrypting data
	static int m_nKeyIdx;
#endif

	static char m_className[];
	
};

#endif /* AMPDATABASE_H_ */

