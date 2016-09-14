/*
#  MODULE DESCRIPTION:
#  cnfglobals.h
#  <enter module description here>
#
#  AUTHORS:
#  Author Name		Raffaele Ficcadenti
#  Author email		raffaele.ficcadenti@asdc.asi.it
#
#
#  HISTORY:
#  -[Date]- -[Who]------------- -[What]---------------------------------------
#  00.00.00 Author Name         Creation date
#--
#
*/


#ifndef _CNFGLOBALS_H
#define _CNFGLOBALS_H

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qvector.h>

#define PAMELA_RES 		"PAMELA_RES"
#define PAMELA_CONFIG_FILE 	"pamela.ini"

// This define classes and data structs to access config file headers

#define HDR_TAG_LEN     20
#define HDR_DSCR_LEN    160
#define HDR_NUM_LEN     14      // YYYYMMDDHHMMSS
#define HDR_BOOL_LEN    1

// Other defines

#define c_qstrncpy(d, s, n)     { memset(d,0,n); qstrncpy(d,s,n); }

typedef QVector<QString> QStringVector;

typedef struct {
        QStringList values;
        QStringList labels;
} TagList;

#endif
