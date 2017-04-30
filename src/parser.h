#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include <assert.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "structs.h"
#include "TCD.h"

TCD_istruct parseBackup(int nfiles, char** xml_filenames, TCD_istruct TCD);

#endif
