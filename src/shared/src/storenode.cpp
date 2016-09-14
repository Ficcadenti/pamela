/*
#  MODULE DESCRIPTION:
#  <enter module description here>
#
#  AUTHORS:
#  Author Name <raffaele.ficcadenti@gmail.com>
#
#
#  HISTORY:
#  -[Date]- -[Who]------------- -[What]---------------------------------------
#  00.00.00 Author Name         Creation date
#--
#
*/

#include "storenode.h"

static char nbuf[1024];
static char pbuf[1024];
static char cbuf[1024];
static QString exenam;

void StoreNode::set(char *name)
{
	qstrcpy(nbuf, name);
}

void StoreNode::setPrefix(char *prefix)
{
	qstrcpy(pbuf, prefix);
}

char * StoreNode::get()
{
	return nbuf;
}

char * StoreNode::combine(char * prefix)
{
	if (prefix == 0)
		prefix = pbuf;
	qstrcpy(cbuf, prefix);
	return strcat(cbuf, nbuf);
}

void StoreNode::setMyExeName(const QString & exename)
{
	exenam = exename;
}

QString StoreNode::myExeName()
{
	return exenam;
}
