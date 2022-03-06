#include <stdlib.h>
#include "text_clean.h"
/******************************************************************************/

/******************CHARACTER COMPARE FUNCTIONS*********************************/

/******************************************************************************/
int Is_Punctuation(const char ch)
{	
  return ((ch >= '!' && ch <= '/') || (ch >= ':' && ch <= '@') ||
          (ch >= '[' && ch <= '`') || (ch >= '{' && ch <= '~'));
}
/******************************************************************************/
int Is_Stop_Character(const char ch)
{	
  return (ch == '.' || ch == '?' || ch == '!' || ch == ',' ||
          ch == ';' || ch == ':');
}
/******************************************************************************/
int Is_Whitespace(const char ch)
{	
  return (ch == '\f' || ch == '\t' || ch == '\r' || ch == '\n' ||
          ch == '\v' || ch == ' ');
}
/******************************************************************************/
int Is_Alphabetic(const char ch)
{
  return (Is_Capital_Letter(ch) || Is_Lowercase_Letter(ch));
}
/******************************************************************************/
int Is_Digit(const char ch)
{
  return (ch >= '0' && ch <= '9');
}
/******************************************************************************/
int Is_Alphanumeric(const char ch)
{
  return (Is_Alphabetic(ch) || Is_Digit(ch));
}
/******************************************************************************/
int Is_Part_Of_Word(const char ch)
{
  return (Is_Alphanumeric(ch) || Is_Whitespace(ch) || ch == '\'');
}
/******************************************************************************/
int Is_Lowercase_Letter(const char ch)
{
  return (ch >= 'a' && ch <= 'z');
}
/******************************************************************************/
int Is_Capital_Letter(const char ch)
{
  return (ch >= 'A' && ch <= 'Z');
}
/******************************************************************************/

/******************WORD COMPARE FUNCTIONS**************************************/

/******************************************************************************/
int Is_Same(const char *input, const char *reference)
{	
  if (Get_Text_Length(input) != Get_Text_Length(reference))
  {
    return 0;
  }
  for (int i = 0; i < Get_Text_Length(input); i++)
  {
    if (input[i] != reference[i])
    {
      return 0;
    }
  }
  return 1;
}
/******************************************************************************/
int Is_Stop_Word(const char *word)
{
  return (Is_Same(word, "the")   || Is_Same(word, "it") ||
          Is_Same(word, "her")   || Is_Same(word, "in") ||
          Is_Same(word, "for")   || Is_Same(word, "is") ||
          Is_Same(word, "a")     || Is_Same(word, "so") ||
          Is_Same(word, "such")  || Is_Same(word, "as") ||
          Is_Same(word, "then")  || Is_Same(word, "me") ||
          Is_Same(word, "this")  || Is_Same(word, "to") ||
          Is_Same(word, "was")   || Is_Same(word, "at") ||
          Is_Same(word, "but")   || Is_Same(word, "of") ||
          Is_Same(word, "his")   || Is_Same(word, "an") ||
          Is_Same(word, "there") || Is_Same(word, "my")); 
}
/******************************************************************************/
int Is_Number(const char *word)
{
  for (int i = 0; i < Get_Text_Length(word); i++)
  {
	if (Is_Digit(word[i]))
	{
	  return 1;
    }
  }
  return 0;
}
/******************************************************************************/
int Is_One_Character(const char *word)
{
  return (Get_Text_Length(word) == 1);
}
/******************************************************************************/
int Is_One_Letter_Word(const char *word)
{
  return (Is_Same(word, "i") || Is_Same(word, "a"));
         
}
/******************************************************************************/
int Has_Char(const char *text, const char ch)
{
  for (int i = 0; i < Get_Text_Length(text); i++)
  {
    if (text[i] == ch)
    {
      return 1;
	}
  }
  return 0;
}
/******************************************************************************/
int Ends_In_Char(const char *word, const char ch)
{
  return word[Get_Text_Length(word)-1] == ch;
}
/******************************************************************************/
int Has_Suffix(const char *word, const char *suffix)
{
  for (int i = Get_Text_Length(word) - Get_Text_Length(suffix), j = 0;
           i < Get_Text_Length(word); i++, j++)
  {
    if (word[i] != suffix[j])
    {
	  return 0;
	}
  }
  return 1;
}
/******************************************************************************/
int Get_Chars_In_Text(const char *input, const char *reference)
{
  int count;
  for (count = 0; count < Get_Text_Length(input); count++)
  {
    for (int i = 0; i < Get_Text_Length(reference); i++)
    {
	  if (input[count] != reference[i])
	  {
        return count;
      }
    }
  }
  return count;
}
/******************************************************************************/
int Get_Chars_Not_In_Text(const char *input, const char *reference)
{
  int count;
  
  for (count = 0; count < Get_Text_Length(input); count++)
  {
    for (int i = 0; i < Get_Text_Length(reference); i++)
    {
	  if (input[count] == reference[i])
	  {
        return count;
      }
    }
  }
  return count;
}
/******************************************************************************/

/******************TEXT COMPARE FUNCTIONS**************************************/

/******************************************************************************/
int Is_In_Text(const char *text, const char *reference)
{
  int txt_len = Get_Text_Length(text);
  int ref_len = Get_Text_Length(reference);
  
  for (int i = 0; i <= txt_len-ref_len; i++)
  {
    if (text[i] == reference[0])
    {
      for (int j = 0; j < ref_len; j++)
      {
        if (text[i+j] != reference[j])
        {
          break;
        }
	    else if (j == ref_len-1)
	    {
		  return 1;
		}  
	  }
	}
  }
  return 0;
}
/******************************************************************************/

/********************TEXT DATA FUNCTIONS***************************************/

/******************************************************************************/
int Get_Num_Char(const char *text, const char ch)
{	
  int text_length = Get_Text_Length(text);
  int num_of_char = 0;
  
  for (int i = 0; i < text_length; ++i)
  {  
    if (text[i] == ch)
    {
      ++num_of_char;
    }
  }
  return num_of_char;
}
/******************************************************************************/
int Get_Num_Delimiters(const char *text)
{	
  int text_length = Get_Text_Length(text);
  int num_of_delimiters = 0;
  
  for (int i = 0; i < text_length; ++i)
  {  
    if (Is_Whitespace(text[i]))
    {
      if (!Is_Whitespace(text[i + 1]))
      {  
        ++num_of_delimiters;
      }
    }
  }  
  return num_of_delimiters;
}
/******************************************************************************/
int Get_Num_Words(const char *text)
{
  int text_length = Get_Text_Length(text);
  int num_of_words = Get_Num_Delimiters(text) + 1;
  
  if (num_of_words > 1)
  {
    if (Is_Whitespace(*text))
    {
	  --num_of_words;
	}
	if (Is_Whitespace(text[text_length - 1]))
	{
	  --num_of_words;
	}
  }
  return num_of_words;
}
/******************************************************************************/
int Get_Text_Length(const char *text)
{
  int length = 0;
  
  if (text)
  {
    while (length < MAX_TEXT_LEN)
    {
      if (text[length] == '\0')
      {
	    return length;
      }
      length++;
    }
  }
  return length;
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
{	
  char  *value   = malloc(rows * columns * sizeof(char));
  char **row_ptr = malloc(rows * sizeof(char *));

  for (int i = 0; i < rows; ++i)
  {
    row_ptr[i]  = value + (i * columns);
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
char *Tokenize_Text(char *text, char *delim, char **save_ptr)
{
  if (!text) {
    text = *save_ptr;
  }
  if (*text == '\0') {
    *save_ptr = text;
    return NULL;
  }
  text += Get_Chars_In_Text(text, delim);
  
  if (*text == '\0') {
    *save_ptr = text;
    return NULL;
  }
  char *end = text + Get_Chars_Not_In_Text(text, delim);
  
  if (*end == '\0') {
    *save_ptr = end;
    return text;
  }
  *end = '\0';
  *save_ptr = end + 1;
  return text;
}
/******************************************************************************/
void Delete_Text(char *text)
{
  for (int i = Get_Text_Length(text); i > 0; i--)
  {
    text[i-1] = '\0';
  }
}
/******************************************************************************/
void Clean_Text(char *text)
{
  Normalize_Whitespace(text);
  Leave_Chars(text, Is_Part_Of_Word);
  Convert_Text_Lowercase(text);
  Strip_Words(text, Is_Stop_Word);
  Strip_Words(text, Is_One_Character);
  Strip_Words(text, Is_Number);
}
/******************************************************************************/
