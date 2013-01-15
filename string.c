#include <sqlite3ext.h>
/*#include <stdio.h>*/
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

SQLITE_EXTENSION_INIT1

/**
 * Concatenates values.
 */
static void concat(
    sqlite3_context *context,
    int argc,
    sqlite3_value **argv)
{
    size_t lens[10];
    size_t lenall = 0;
    size_t lentilnow = 0;

    int i = 0;

    for(i=0; i < argc; i++)
    {
        lens[i] = strlen(sqlite3_value_text(argv[i]));
        lenall += lens[i];
    }

    char* all = (char*)malloc((lenall + argc)*sizeof(argv));
    all[lenall + argc - 1] = '\0';

    for(i = 0; i < argc - 1; i++)
    {
        memcpy(all + lentilnow + i, sqlite3_value_text(argv[i]), lens[i]);
        all[lentilnow + lens[i] + i] = ' ';
        lentilnow += lens[i];
    }
    memcpy
    (
        all + lentilnow + argc - 1,
        sqlite3_value_text(argv[argc - 1]),
        lens[argc - 1]
    );

    sqlite3_result_text(context, all, strlen(all), (void*) -1);
}

/**
 * SQLite invokes this routine once when it loads the extension.
 * Create new functions, collating sequences, and virtual table
 * modules here.  This is usually the only exported symbol in
 * the shared library.
 */
int sqlite3_extension_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
) {
    SQLITE_EXTENSION_INIT2(pApi);
    sqlite3_create_function(db, "concat", -1, SQLITE_ANY, 0, concat, 0, 0);
    return 0;
}