
#ifndef AMP_LINKLIST_H
#define AMP_LINKLIST_H

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
* File       	 : 		LinkList.h
* Application	 : 		AMP Component
* Date Coded  : 		04/07/2015
**************************************************************************/

struct Linkist_Element
{
	void *data;				/*!Element data pointer*/
	Linkist_Element *prev;	/*!Pointer the the previous element*/
	Linkist_Element *next;	/*!Pointer the the next element*/
};

typedef int (*fnCompare) (void*, void*);


class cLinkList
{
public:
	cLinkList(void *data_ptr);
	cLinkList();
	virtual ~cLinkList();

	int add_x(void *add_obj);
	int remove_x();
	void insert_x(void *insert_rec, fnCompare comp);
	int locate_x(void *locate_key, fnCompare comp);

	int first_x();
	int last_x();
	void *value_x();
	int next_x();
	int prev_x();

	int isEmpty();
	int isBOL();
	int isEOL();
	
protected:
	Linkist_Element *head;
	Linkist_Element *cursor;

	virtual void delete_data(void *data) = 0;
private:

	static char m_className[];
};

#endif  /*AMP_LINKLIST_H*/

