#include "text_tag.h"
#include "text_clean.h"
#include "text_data.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
/******************************************************************************/
struct word_t
{
  const char *text;
  char  tag[5];
  float odds;
  struct word_t *alt;
  struct word_t *prev;
  struct word_t *next;
};
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
struct word_t *Create_Word_From_Text(const char *text)
{
  struct word_t *word = calloc(sizeof(struct word_t), 1);
  word->text = text;
  return word;
}
/******************************************************************************/
void Set_Tag(struct word_t *word, const char *tag)
{
  if (word)
  {
    Copy_Text(word->tag, tag);
  }
}
/******************************************************************************/
void Set_Tag_Odds(struct word_t *word, float odds)
{
  if (word)
  {
    word->odds = odds;
  }
}
/******************************************************************************/
void Destroy_Tagged_Word(struct word_t *tagged_word)
{
  free(tagged_word);
}
/******************************************************************************/
struct word_t *Add_Tag(struct word_t *word, const char *text,
                                     const char *tag, float odds)
{
  if (!word)
  {
    word = Create_Word_From_Text(text);
    Set_Tag(word, tag);
    Set_Tag_Odds(word, odds);
    return word;
  }
  else
  {
    word->alt = Add_Tag(word->alt, text, tag, odds);
  }
  return word;
}
/******************************************************************************/
struct word_t *Assign_Possible_Tags(const char *word)
{	
  char *sql = "SELECT \"tag\", \"odds\" FROM \"emission\" WHERE \"word\" = ?1"
              "ORDER BY \"odds\" DESC";

  sqlite3_stmt *stmt = NULL;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not set possible tags for '%s'!\nError code: %d\t%s\n\n", word, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return NULL;
  }
  rc = sqlite3_bind_text(stmt, 1, word, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind '%s!'\nError code: %d\t%s\n\n", word, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return NULL;
  }
  struct word_t *tagged_word = NULL;
  const char *tag = NULL;
  float odds = 0.0f; 
  
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
	do
	{
      tag  = (const char *)sqlite3_column_text(stmt, 0);
      odds = (float)sqlite3_column_double(stmt, 1);
      tagged_word = Add_Tag(tagged_word, word, tag, odds);
    } while (sqlite3_step(stmt) == SQLITE_ROW);
  }
  else
  {
	tagged_word = Add_Tag(tagged_word, word, "NN", 1.0f);
  }
  sqlite3_finalize(stmt);
  return tagged_word;
}
/******************************************************************************/
struct word_t *Create_Trellis_Diagram(char *text)
{
  Clean_Text(text);

  int num_of_words = Get_Num_Words(text);
  
  char **divided_text = Divide_Text_Words(text);
  
  struct word_t *tagged_word = NULL;
  
  for (int i = 0; i < num_of_words; i++)
  {
    tagged_word = Insert_Tagged_Word(tagged_word, divided_text[i]);
  }
  return tagged_word;
}
/******************************************************************************/
struct word_t *Insert_Tagged_Word(struct word_t *word, const char *text)
{
  if (!word)
  {
    word = Assign_Possible_Tags(text);
    return word;
  }
  else
  {
    word->next = Insert_Tagged_Word(word->next, text);
    word->next->prev = word;
    struct word_t *temp = word;

    while (temp->alt)
    {
      temp->alt->next = temp->next;
      temp = temp->alt;
	}
	temp = word->next;

    while (temp->alt)
    {
      temp->alt->prev = temp->prev;
      temp = temp->alt;
	}
  }
  return word;
}
/******************************************************************************/
void Print_Tags(struct word_t *head)
{
  struct word_t *temp = head;
  printf("\n");
  
  while (temp)
  {
    printf("%s_%s %f", temp->text, temp->tag, temp->odds);
    if (temp->prev)
    {
      printf("\t\tprev = %s", temp->prev->text);
    }
    else
	{
	   printf("\t\tprev = X");
	}
	if (temp->next)
	{
      printf("\t\tnext = %s", temp->next->text);
	}
	else
	{
      printf("\t\tnext = X");
	}
    struct word_t *alt_tag  = temp->alt;
    
    while (alt_tag)
    {
      printf("\n%s_%s %f", alt_tag->text, alt_tag->tag, alt_tag->odds);
      if (alt_tag->prev)
      {
        printf("\t\tprev = %s", alt_tag->prev->text);
	  }
	  else
	  {
	     printf("\t\tprev = X");
	  }
	  if (alt_tag->next)
      {
        printf("\t\tnext = %s", alt_tag->next->text);
	  }
	  else
	  {
	     printf("\t\tnext = X");
	  }
      alt_tag = alt_tag->alt;
	}
	printf("\n\n");
    temp = temp->next;
  }
  printf("\n");
}
/******************************************************************************/
int Get_Num_Tags(struct word_t *word)
{
  int i = 1;	
  if (word)
  {
	struct word_t *temp = word->alt;
    while (temp)
    {
      i++;
      temp = temp->alt;
    }
  }
  return i;
}
/******************************************************************************/
float **Create_Odds_Table(struct word_t *word)
{
  int num_tags      = Get_Num_Tags(word);
  int num_prev_tags = Get_Num_Tags(word->prev);
  
  float *odds = calloc(num_tags * num_prev_tags, sizeof(float));
  float **tag = malloc(num_tags * sizeof(float *));

  for (int i = 0; i < num_tags; i++)
  {
    tag[i] = odds + (num_prev_tags * i);
  }
  return tag;
}
/******************************************************************************/
float **Populate_Odds_Table(struct word_t *word)
{
  float **odds_table = Create_Odds_Table(word);
  struct word_t *temp = word;
  struct word_t *temp_prev = temp->prev;
  int i = 0;
  int j = 0;

  if (!temp_prev)
  {
    while (temp)
    {
      odds_table[0][i] = Get_Odds(temp->tag, "X");
      odds_table[0][i] *= temp->odds;
      i++;
      temp = temp->alt;
	}
	return odds_table;
  }
  while (temp)
  {
    while (temp_prev)
    {
      odds_table[i][j] = Get_Odds(temp->tag, temp_prev->tag)
      odds_table[i][j] *= temp->odds;
      j++;
      temp_prev = temp->prev->alt;
	}
	i++;
	temp = temp->alt;
  }
}
/******************************************************************************/
float Get_Odds(const char *current_tag, const char *prev_tag);
{
  const char *sql = "SELECT \"odds\" FROM \"transition\" WHERE \"tag\" = ?1 AND"
                    " \"next_tag\" = ?2";

  sqlite3_stmt *stmt = NULL;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not set odds for '%s' to '%s'!\nError code: %d\t%s\n\n", current_tag, prev_tag, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return NULL;
  }
  rc = sqlite3_bind_text(stmt, 1, current_tag, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind '%s!'\nError code: %d\t%s\n\n", current_tag, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return NULL;
  }
   rc = sqlite3_bind_text(stmt, 2, prev_tag, -1, SQLITE_STATIC);
  
  if (rc != SQLITE_OK)
  {
	printf("\n\nCould not bind '%s!'\nError code: %d\t%s\n\n", prev_tag, rc, sqlite3_errmsg(db));
	sqlite3_finalize(stmt);
	return NULL;
  }
  float odds = 0.0f; 
  
  if (sqlite3_step(stmt) == SQLITE_ROW)
  {
    odds = (float)sqlite3_column_double(stmt, 0);
  }
  return odds;
}
/******************************************************************************/
