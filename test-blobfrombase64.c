#include "sqlite3.h"

#include "sqlite3_base64.h"

#include <assert.h>

#include <string.h>

static int assert_blob_count = 0;

static int assert_blob_value(void * _, int result_count, char ** results, char ** _2) {
  assert(result_count == 1);
  assert(!strcmp(results[0], "010203"));
  ++assert_blob_count;
  return 0;
}

static int assert_blob_type_count = 0;

static int assert_blob_type(void * _, int result_count, char ** results, char ** _2) {
  assert(result_count == 1);
  assert(!strcmp(results[0], "blob"));
  ++assert_blob_type_count;
  return 0;
}

int main(int argc, char ** argv) {
  sqlite3 * testdb;

  int open_rc = sqlite3_open(":memory:", &testdb);

  assert(open_rc == 0);

  assert(sqlite3_base64_init(testdb) == 0);

  sqlite3_exec(testdb, "SELECT HEX(BLOBFROMBASE64('AQID'))", assert_blob_value, NULL, NULL);
  assert(assert_blob_count == 1);

  sqlite3_exec(testdb, "SELECT TYPEOF(BLOBFROMBASE64('AQID'))", assert_blob_type, NULL, NULL);
  assert(assert_blob_type_count == 1);
}