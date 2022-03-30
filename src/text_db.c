/******************************************************************************/
static sqlite3 *db;
/******************************************************************************/
void Open_Database(const char *filepath)
{
  if (sqlite3_open(filepath, &db) != SQLITE_OK)
  {
    printf("SQLite could not open database: %s\n", sqlite3_errmsg(db));
    Close_Database();
  }
  return;
}
/******************************************************************************/
void Close_Database()
{
  sqlite3_close(db);
}
/******************************************************************************/
int Execute_SQL(const char *sql)
{
  sqlite3_stmt *stmt;

  if (!Prepare_Statement(&stmt, sql))
  {
    printf("Could not prepare statement '%.30s'\n\n", sql);
    return 0;
  }
  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return 1;
}
/******************************************************************************/
int Prepare_Statement(sqlite3_stmt **stmt, const char *sql)
{
  int rc = sqlite3_prepare_v2(db, sql, -1, stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nError code: %d\t%s\n", rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return 0;
  }
  return 1;
}
/******************************************************************************/
int Bind_Text(sqlite3_stmt *stmt, const char *text, const int index)
{
  int rc = sqlite3_bind_text(stmt, index, text, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nError code: %d\t%s\n", rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return 0;
  }
  return 1;
}
/******************************************************************************/

/******************************************************************************/
