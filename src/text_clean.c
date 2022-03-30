#include "text_clean.h"
#include "text_data.h"
#include <stdlib.h>
/******************************************************************************/

/*********************TEXT CLEANING FUNCTIONS**********************************/

/******************************************************************************/
void Strip_Chars(char *text, int (*Compare_Func)(const char))
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
    if (Compare_Func(text[i]))
    {
      for (int j = i; j < Get_Text_Length(text); j++)
      {
        text[j] = text[j+1];
      }
      i--;
    }
  }
}
/******************************************************************************/
void Leave_Chars(char *text, int (*Compare_Func)(const char))
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
    if (!Compare_Func(text[i]))
    {
      for (int j = i; j < Get_Text_Length(text); j++)
      {
        text[j] = text[j+1];
      }
      i--;
    }
  }
}
/******************************************************************************/
void Strip_Words(char *text, int (*Compare_Func)(const char *))
{
  char **word = Divide_Text_Words(text);
  int num_of_words = Get_Num_Words(text);
  Delete_Text(text);
  
  for (int i = 0; i < num_of_words; i++)
  {
    if (!Compare_Func(word[i]))
    {  
	  Append_Word(text, word[i]);
	}
  }
  Destroy_Divided_Text(word);
}
/******************************************************************************/
void Strip_Leading_Whitespace(char *text)
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
	if (Is_Whitespace(*text))
	{
      for (int j = 0; j < Get_Text_Length(text); j++)
      {
        text[j] = text[j+1];
      }
	}
	else
	{
      return;
    }	
  }
}
/******************************************************************************/
void Strip_Trailing_Whitespace(char *text)
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
	if (Is_Whitespace(text[Get_Text_Length(text)-1]))
	{
     Strip_Last_Char(text);
	}
	else
	{
      return;
	}
  }
}
/******************************************************************************/
void Strip_Double_Whitespace(char *text)
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
    if (Is_Whitespace(text[i]) && Is_Whitespace(text[i + 1]))
    {
      for (int j = i; j < Get_Text_Length(text); j++)
      {
        text[j] = text[j+1];
      }
      i--;
    }
  }
}
/******************************************************************************/
void Convert_Whitespace_To_Space(char *text)
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
    if (Is_Whitespace(text[i]))
    {
	  text[i] = ' ';
	}
  }
}
/******************************************************************************/
void Normalize_Whitespace(char *text)
{
  Strip_Leading_Whitespace(text);
  Strip_Double_Whitespace(text);
  Strip_Trailing_Whitespace(text);
  Convert_Whitespace_To_Space(text);
}
/******************************************************************************/
void Strip_Last_Char(char *text)
{
  if (*text)
  {	
    text[Get_Text_Length(text)-1] = '\0';
  }
}
/******************************************************************************/

/******************TEXT CREATE/DESTROY FUNCTIONS*******************************/

/******************************************************************************/
char **Create_Matrix_Chars(int rows, int columns)
{ //memory block to hold each character
  char  *value   = malloc(rows * columns * sizeof(char));
  //pointers to beginning of each word
  char **row_ptr = malloc(rows * sizeof(char *));

  for (int i = 0; i < rows; ++i)
  {
	 //set word pointer to the actual word
     row_ptr[i] = value + (i * columns);
     //set each word to empty (first character NULL)
    *row_ptr[i] = '\0';
  }
  return row_ptr;
}
/******************************************************************************/
char **Divide_Text_Words(const char *text)
{	
  int text_length  = Get_Text_Length(text);
  int num_of_words = Get_Num_Words(text);
  int longest_word = Get_Length_Longest_Word(text);
  
  char **word = Create_Matrix_Chars(num_of_words, longest_word + 1);
  char *token[num_of_words];
  char buffer[text_length + 1];
  Copy_Text(buffer, text);
  char *word_pointer = buffer;
 
  for (int i = 0; i < num_of_words; i++)
  {
    token[i] = Tokenize_Text(word_pointer, " \t\r\n\v\f", &word_pointer);
    Copy_Text(word[i], token[i]);
  }
  return word;
}
/******************************************************************************/
char *Tokenize_Text(char *text, char *delim, char **save_ptr)
{
  if (!text)
  {
    text = *save_ptr;
  }
  if (*text == '\0')
  {
    *save_ptr = text;
    return NULL;
  }
  text += Get_Chars_In_Text(text, delim);
  
  if (*text == '\0')
  {
    *save_ptr = text;
    return NULL;
  }
  char *end = text + Get_Chars_Not_In_Text(text, delim);
  
  if (*end == '\0')
  {
    *save_ptr = end;
    return text;
  }
  *end = '\0';
  *save_ptr = end + 1;
  return text;
}
/******************************************************************************/
void Destroy_Divided_Text(char **text)
{
  free(*text);
  free(text);
}
/******************************************************************************/

/*********************CHARACTER MANIP FUNCTIONS********************************/

/******************************************************************************/
char Convert_Char_Lowercase(char ch)
{
  if (ch >= 'A' && ch <= 'Z')
  {
    ch += 32;
  }
  return ch;
}
/******************************************************************************/

/*********************WORD MANIP FUNCTIONS*************************************/

/******************************************************************************/
void Append_Word(char *text, const char *word)
{
  if (*word)
  {
	if (*text)
	{
      Append_Text(text, " ");
    }
	Append_Text(text, word);
  }
}
/******************************************************************************/

/*********************TEXT MANIP FUNCTIONS*************************************/

/******************************************************************************/
void Constrain_Text_Length(char *text, int length)
{
  text[length-1] = '\0';
}
/******************************************************************************/
void Convert_Text_Lowercase(char *text)
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
    text[i] = Convert_Char_Lowercase(text[i]);
  }
}
/******************************************************************************/
void Copy_Text(char *destination, const char *source)
{
  int src_len = Get_Text_Length(source);
  
  Delete_Text(destination);
  
  for (int i = 0; i < src_len; i++)
  { 
    destination[i] = source[i];
  }
  destination[src_len] = '\0';
  return;
}
/******************************************************************************/
void Append_Text(char *destination, const char *source)
{
  int dest_len = Get_Text_Length(destination);
  
  for (int i = 0; i <= MAX_TEXT_LEN - dest_len; ++i)
  {
    if (source[i])
    {	
      destination[dest_len + i] = source[i];
    }
    else
    {
      destination[dest_len + i] = '\0';
      return;
    }
  }
}
/******************************************************************************/
void Delete_Text(char *text)
{
  text[0] = '\0';
}
/******************************************************************************/
void Clean_Text(char *text)
{
  Normalize_Whitespace(text);
  Leave_Chars(text, Is_Part_Of_Word);
  Convert_Text_Lowercase(text);
  Strip_Words(text, Is_Number);
}
/******************************************************************************/
int Get_Length_Longest_Word(const char *text)
{
  char *delimiters = " \t\r\n\v\f";
 
  char buffer[Get_Text_Length(text) + 1];
  Copy_Text(buffer, text);
  char *word_ptr = buffer;
  
  int num_of_words = Get_Num_Words(buffer);
  char *word[num_of_words];
  int length[num_of_words];
  
  for (int i = 0; i < num_of_words; ++i)
  {
    word[i] = Tokenize_Text(word_ptr, delimiters, &word_ptr);
    length[i] = Get_Text_Length(word[i]);
  }
  for (int i = num_of_words-1; i > 0; --i)
  {
	if (length[i] > length[i-1])
	{
	  int temp    = length[i];
	  length[i]   = length[i-1];
	  length[i-1] = temp;
	}
  }
  return *length;
}
/******************************************************************************/
