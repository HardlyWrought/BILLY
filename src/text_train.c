#include "text_train.h"
#include "text_clean.h"
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
void Expand_Contractions(char *word)
{
  if (Is_Same(word, "n't"))
  {
    Copy_Text(word, "not");
  }
  else if (Is_Same(word, "'ve"))
  {
    Copy_Text(word, "have");
  }
  else if (Is_Same(word, "'re"))
  {
    Copy_Text(word, "are");
  }
  else if (Is_Same(word, "'ll"))
  {
    Copy_Text(word, "will");
  }
  return;
}
/******************************************************************************/
int Record_Exists(const char *table, const char *column, const char *record)
{
  char buffer[MAX_STMT_LEN] = {0};
  
  Copy_Text(buffer, "SELECT * FROM ");
  Append_Text(buffer, table);
  Append_Text(buffer, "WHERE ");
  Append_Text(buffer, column);
  Append_Text(buffer, " = ?1");

  sqlite3_stmt *stmt = NULL;

  int rc = sqlite3_prepare_v2(db, buffer, -1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not check record \"%s\" in table %s!\nError code: %d\t%s\n\n", record, table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return -1;
  }
  rc = sqlite3_bind_text(stmt, 1, record, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind record \"%s\" to table %s! (Insert_Row)\nError code: %d\t%s\n\n", record, table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return -1;
  }
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_ROW;
}
/******************************************************************************/
void Add_Word_To_Dict(const char *word)
{
  if (!Record_Exists("\"emission_count\"", "\"word\"", word))
  {
    char *tags[32] = {"CC",  "CD",  "DT",  "EX",  "IN",  "JJ",  "JJR", "JJS",
		              "LS",  "MD",  "NN",  "NNS", "PDT", "POS", "PRP", "PRP$",
		              "RB",  "RBR", "RBS", "RP",  "TO",  "UH",  "VB",  "VBD",
		              "VBG", "VBN", "VBP", "VBZ", "WDT", "WP",  "WP$", "WRB"};

    for (int i = 0; i < 32; i++)
    {
      Insert_Row("\"emission_count\"", "\"word\"", "\"tag\"", word, tags[i]);
    }
  }
  return;
}
/******************************************************************************/
void Add_Tag_To_Dict(const char *tag)
{
  if (!Record_Exists("\"transition_count\"", "\"tag\"", tag))
  {
    char *next_tag[33] = {"CC",  "CD",  "DT",  "EX",  "IN",  "JJ",  "JJR", "JJS",
		                  "LS",  "MD",  "NN",  "NNS", "PDT", "POS", "PRP", "PRP$",
		                  "RB",  "RBR", "RBS", "RP",  "TO",  "UH",  "VB",  "VBD",
		                  "VBG", "VBN", "VBP", "VBZ", "WDT", "WP",  "WP$", "WRB",
		                  "X"};

    for (int i = 0; i < 33; i++)
    {
      Insert_Row("\"transition_count\"", "\"tag\"", "\"next_tag\"", tag, next_tag[i]);
    }
  }
  return;
}
/******************************************************************************/
void Insert_Row(const char *table, const char *col_1, const char *col_2,
                                   const char *val_1, const char *val_2)
{
  char buffer[MAX_STMT_LEN] = {0};
  
  Copy_Text(buffer, "INSERT OR IGNORE INTO ");
  Append_Text(buffer, table);
  Append_Text(buffer, " (");
  Append_Text(buffer, col_1);
  Append_Text(buffer, ", ");
  Append_Text(buffer, col_2);
  Append_Text(buffer, ") VALUES (?1, ?2)");
  
  sqlite3_stmt *stmt = NULL;

  int rc = sqlite3_prepare_v2(db, buffer, -1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not insert into table %s!\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  rc = sqlite3_bind_text(stmt, 1, val_1, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind first value to table %s! (Insert_Row)\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  rc = sqlite3_bind_text(stmt, 2, val_2, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind second value to table %s! (Insert_Row)\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return;
}
/******************************************************************************/
void Increment_Count(const char *table, const char *col_1, const char *col_2,
                                       const char *val_1, const char *val_2)
{
  char buffer[MAX_STMT_LEN] = {0};

  Copy_Text  (buffer, "UPDATE ");
  Append_Text(buffer, table);
  Append_Text(buffer, " SET \"count\" = \"count\" + 1 WHERE ");
  Append_Text(buffer, col_1);
  Append_Text(buffer, " = ?1 AND ");
  Append_Text(buffer, col_2);
  Append_Text(buffer, " = ?2");

  sqlite3_stmt *stmt = NULL;

  int rc = sqlite3_prepare_v2(db, buffer, -1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not increment count in table %s!\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  rc = sqlite3_bind_text(stmt, 1, val_1, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind first value to %s table! (Increment_Count)\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  rc = sqlite3_bind_text(stmt, 2, val_2, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind second value to %s table! (Increment_Count)\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return;
}
/******************************************************************************/
void Increment_Total(const char *table, const char *column, const char *value)
{
  char buffer[MAX_STMT_LEN] = {0};

  Copy_Text  (buffer, "UPDATE ");
  Append_Text(buffer, table);
  Append_Text(buffer, " SET \"total\" = \"total\" + 1 WHERE ");
  Append_Text(buffer, column);
  Append_Text(buffer, " = ?1");

  sqlite3_stmt *stmt = NULL;

  int rc = sqlite3_prepare_v2(db, buffer, -1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not increment total in table %s!\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  rc = sqlite3_bind_text(stmt, 1, value, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind value to table %s (Increment_Total)!\nError code: %d\t%s\n\n", table, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return;
  }
  do 
  {
    rc = sqlite3_step(stmt);
  } while (rc == SQLITE_ROW);
  
  sqlite3_finalize(stmt);
  return;
}
/******************************************************************************/
void Split_Token(char *buffer, char *word, char *tag)
{
  char *ptr   = buffer;
  char *token = NULL;
  
  token = Tokenize_Text(ptr, "_", &ptr);
  Copy_Text(word, token);
  token = Tokenize_Text(ptr, "_", &ptr);
  Copy_Text(tag, token);
  return;
}
/******************************************************************************/
int Train_Tagger(const char *filepath)
{
  FILE *text_file = fopen(filepath, "r");
      
  Execute_SQL("BEGIN TRANSACTION");

  Build_Database(text_file);
  
  Execute_SQL("END TRANSACTION");
  
  fclose(text_file);
  return 55;
}
/******************************************************************************/
int Is_Clean_Word(char *word)
{
  if (word != NULL               &&
      Is_Alphabetic(word[0]))
  {
	Constrain_Text_Length(word, MAX_WORD_LEN);
    Expand_Contractions(word);
    Leave_Chars(word, Is_Alphabetic);
    Convert_Text_Lowercase(word);
    
    if (Get_Text_Length(word) >= 13 ||
       (Get_Text_Length(word) == 1 && !Is_One_Letter_Word(word)))
    {
      return 0;
	}
    return 1;  
  }
  return 0;
}
/******************************************************************************/
int Is_Clean_Tag(char *tag)
{
  Leave_Chars(tag, Is_Part_Of_Tag);
  Constrain_Text_Length(tag, MAX_TAG_LEN);
  Improperize_Noun(tag);

  char *tags[32] = {"CC",  "CD",  "DT",  "EX",  "IN",  "JJ",  "JJR", "JJS",
		            "LS",  "MD",  "NN",  "NNS", "PDT", "POS", "PRP", "PRP$",
		            "RB",  "RBR", "RBS", "RP",  "TO",  "UH",  "VB",  "VBD",
		            "VBG", "VBN", "VBP", "VBZ", "WDT", "WP",  "WP$", "WRB"};

    for (int i = 0; i < 32; i++)
  {
    if (Is_Same(tag, tags[i]))
    {
      return 1;
	}
  }
  return 0;
}
/******************************************************************************/
int Is_Part_Of_Tag(const char ch)
{
  return (Is_Capital_Letter(ch) || ch == '$');
}
/******************************************************************************/
int Is_Tagged_Word(const char *tagged_word)
{
  return (Is_Alphabetic(tagged_word[0])                   &&
          Get_Num_Char(tagged_word, '_') == 1             &&
          tagged_word[Get_Text_Length(tagged_word)]-1 != '_');
}
/******************************************************************************/
int Execute_SQL(const char *sql)
{
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, Get_Text_Length(sql)+1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("Could not execute SQL statement \n\"%s\"\n\tError code: %d\t%s\n\n", sql, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return 0;
  }
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  return rc == SQLITE_DONE;
}
/******************************************************************************/
void Improperize_Noun(char *tag)
{
  if (Is_Same(tag, "NNP"))
  {
    Copy_Text(tag, "NN");
  }
  else if (Is_Same(tag, "NNPS"))
  {
    Copy_Text(tag, "NNS");
  }
  return;
}
/******************************************************************************/
void Tag_Single_Letter_Word(const char *word, char *tag)
{
  if (Is_One_Letter_Word(word))
  {
    if (Is_Same(word, "i"))
    {
      Copy_Text(tag, "PRP");
	}
	else if (Is_Same(word, "a"))
    {
      Copy_Text(tag, "DT");
	}
  }
  return;
}
/******************************************************************************/
int Is_End_Of_Sentence(const char *tagged_text)
{
  return (Has_Suffix(tagged_text, "_."));
}
/******************************************************************************/
int Tag_End_Of_Sentence(const char *tagged_text, char *prev_tag)
{
  int tagged = 0;
	
  if (Is_End_Of_Sentence(tagged_text))
  {
    Increment_Count("\"transition_count\"","\"tag\"", "\"next_tag\"", prev_tag, "X");
    Increment_Total("\"transition_count\"","\"tag\"", prev_tag);
    Copy_Text(prev_tag, "X");
    tagged = 1;
  }
  return tagged;  
}
/******************************************************************************/
void Tag_Word(char *tagged_text, char *prev_tag)
{
  if (Is_Tagged_Word(tagged_text))
  {
    char word[BUF_SIZE]        = {0};
    char current_tag[BUF_SIZE] = {0};
            
	Split_Token(tagged_text, word, current_tag);
           
    if (Is_Clean_Word(word) && Is_Clean_Tag(current_tag))
	{
      Add_Word_To_Dict(word);
	  Increment_Count("\"emission_count\"", "\"word\"", "\"tag\"", word, current_tag);
      Increment_Total("\"emission_count\"", "\"word\"", word);
		      
	  Add_Tag_To_Dict(prev_tag);
	  Increment_Count("\"transition_count\"","\"tag\"", "\"next_tag\"", prev_tag, current_tag);
	  Increment_Total("\"transition_count\"","\"tag\"", prev_tag);
      Copy_Text(prev_tag, current_tag);
    }
  }
  return;
}
/******************************************************************************/
void Build_Database(FILE *file)
{
  char sentence[MAX_TEXT_LEN] = {0};
	
  while (fgets(sentence, MAX_TEXT_LEN-1, file))
  {
	Constrain_Text_Length(sentence, MAX_TEXT_LEN);
	
    int   sentence_offset        = 0;
	char *sentence_ptr           = sentence;
    char  tagged_text[BUF_SIZE]  = {0};
	char  prev_tag[MAX_TAG_LEN]  = {'X'};
	
	while (sscanf(sentence_ptr, "%30s%n", tagged_text, &sentence_offset) == 1)
	{
      Constrain_Text_Length(tagged_text, BUF_SIZE);

      if (!Tag_End_Of_Sentence(tagged_text, prev_tag))
      {
		Tag_Word(tagged_text, prev_tag);
	  }  
      sentence_ptr += sentence_offset;
    }
  }
}
