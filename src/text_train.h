#include <stdio.h>
#include <sqlite3.h>
/******************************************************************************/
#define MAX_STMT_LEN 1000
#define MAX_TAG_LEN     5
#define MAX_WORD_LEN   20
#define BUF_SIZE       31
/******************************************************************************/
void Open_Database(const char *filepath);
/******************************************************************************/
void Close_Database();
/******************************************************************************
void Expand_Contractions(char *word);
******************************************************************************/
int Record_Exists(const char *table, const char *column, const char *record);
/******************************************************************************/
void Add_To_Dictionary(const char *table, const char *col_1, const char *col_2,
                                          const char *value);
/******************************************************************************/
void Insert_Row(const char *table, const char *col_1, const char *col_2,
                                   const char *val_1, const char *val_2);
/******************************************************************************/
void Increment_Count(const char *table, const char *col_1, const char *col_2,
                                        const char *val_1, const char *val_2);
/******************************************************************************/
void Increment_Total(const char *table, const char *column, const char *value);
/******************************************************************************/
void Split_Token(char *buffer, char *word, char *tag);
/******************************************************************************/
int Train_Tagger(const char *filepath);
/******************************************************************************/
void Tag_Sentence_Start(char *current_tag, char *prev_tag);
/******************************************************************************/
int Is_Clean_Word(char *word);
/******************************************************************************/
int Is_Clean_Tag(char *tag);
/******************************************************************************/
int Is_Part_Of_Tag(const char ch);
/******************************************************************************/
int Is_Tagged_Word(const char *text);
/******************************************************************************/
int Execute_SQL(const char *sql);
/******************************************************************************/
void Improperize_Noun(char *tag);
/******************************************************************************/
void Tag_Single_Letter_Word(const char *word, char *tag);
/******************************************************************************/
int Is_End_Of_Sentence(const char *tagged_text);
/******************************************************************************/
void Tag_Word(char *tagged_text, char *prev_tag);
/******************************************************************************/
void Build_Database(FILE *file);
/******************************************************************************/
