#include "text_data.h"
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
