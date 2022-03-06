#include "snow_stem.h"
#include "../text_clean/text_clean.h"
/******************************************************************************/

/**********************COMPARE FUNCTIONS***************************************/

/******************************************************************************/
int Is_Vowel(const char *word, int i)
{
  return word[i] == 'a' || word[i] == 'e' || word[i] == 'i' ||
         word[i] == 'o' || word[i] == 'u' ||
        (word[i] == 'y' && i > 0 && Is_Consonant(word, i-1));
}
/******************************************************************************/
int Is_Consonant(const char *word, int i)
{
  return Is_Alphabetic(word[i]) && !Is_Vowel(word, i);
}
/******************************************************************************/
char *Get_Measure_Offset(char *word)
{
  int length = Get_Text_Length(word);
  
  for (int i = 2; i < length - 1; i++)
  {
    if (Is_Vowel(word, i - 2) && Is_Consonant(word, i - 1))
    {
      char *offset = word + i;
      return offset;
	}
  }
  char *offset = word + length;
  return offset;
}
/******************************************************************************/
int Has_Vowel(const char *word)
{
  for (int i = 0; i < Get_Text_Length(word); i++)
  {
    if (Is_Vowel(word, i))
    {
      return 1;
	}
  }
  return 0;
}
/******************************************************************************/
int Is_Short_Word(char *word)
{
  const char *r1 = Get_Measure_Offset(word);

  return (Ends_In_Short_Syllable(word) && *r1 == '\0');
}
/******************************************************************************/

/******************SUFFIX MANIP FUNCTIONS**************************************/

/******************************************************************************/
int Remove_Suffix(char *word, const char *suffix)
{
  if (Has_Suffix(word, suffix))
  {
    word[Get_Text_Length(word) - Get_Text_Length(suffix)] = '\0';
    return 1;
  }
  return 0;
}
/******************************************************************************/

/******************ENDS IN * FUNCTIONS*****************************************/

/******************************************************************************/
int Ends_In_Double(const char *word)
{
  int last_letter = Get_Text_Length(word)-1;
  
  return (word[last_letter] == word[last_letter-1]              &&
         (word[last_letter] == 'b'  || word[last_letter] == 'd' ||
          word[last_letter] == 'f'  || word[last_letter] == 'g' ||
          word[last_letter] == 'm'  || word[last_letter] == 'n' ||
          word[last_letter] == 'p'  || word[last_letter] == 'r' ||
          word[last_letter] == 't')); 
}
/******************************************************************************/
int Ends_In_Valid_LI(const char *word)
{
  const char valid_ending[] = {'c', 'd', 'e', 'g', 'h', 'k', 'm', 'n', 'r', 't', 0};

  int length = Get_Text_Length(word) - 1;

  int i = 0;

  while (valid_ending[i])
  {
    if (word[length] == valid_ending[i])
    {
      return 1;
	}
  }
  return 0;
}
/******************************************************************************/
int Ends_In_Short_Syllable(const char *word)
{
  int last_letter = Get_Text_Length(word)-1;
  
  return Is_Consonant(word, last_letter-2) &&
         Is_Vowel(word, last_letter-1)     &&
         Is_Consonant(word, last_letter)   &&
         (!Ends_In_Char(word, 'w')         &&
          !Ends_In_Char(word, 'x')         &&
          !Ends_In_Char(word, 'y'));
}
/******************************************************************************/

/************************PORTER ALGORITHM**************************************/

/******************************************************************************/
void Step_0(char *word)
{
  const char *suffix[] = {"'s'", "'s", "'", 0};

  int i = 0;

  while (suffix[i])
  {
    if (Remove_Suffix(word, suffix[i]))
    {
      return;
	}
	i++;
  }
  return;
}
/******************************************************************************/
void Step_1a(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  
  Copy_Text(buffer, word);
            
  if (Remove_Suffix(buffer, "sses"))
  {
	Append_Text(buffer, "ss");
	Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(buffer, "ied") ||
           Remove_Suffix(buffer, "ies"))
  {
    if (Get_Text_Length(buffer) == 1)
    {
      Append_Text(buffer, "ie");
	}
	else
	{
      Append_Text(buffer, "i");   
	}
	Copy_Text(word, buffer);
  }
  else if (Has_Suffix(buffer, "us") || Has_Suffix(buffer, "ss"))
  {
    return;
  }
  else if (Remove_Suffix(buffer, "s"))
  {  
    if (!Is_Vowel(buffer, Get_Text_Length(buffer) - 1) && Has_Vowel(buffer))
    {
      Copy_Text(word, buffer);
    }
  }
  return;
}
/******************************************************************************/
void Step_1b(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  
  Copy_Text(buffer, word);

  char *r1 = Get_Measure_Offset(buffer);

  if (Remove_Suffix(r1, "eedly") || Remove_Suffix(r1, "eed"))
  {
    Append_Text(buffer, "ee");
    Copy_Text(word, buffer);
  }
  else if ((Remove_Suffix(buffer, "ingly") || Remove_Suffix(buffer, "ing") ||
            Remove_Suffix(buffer, "edly")  || Remove_Suffix(buffer, "ed")) &&
            Has_Vowel(buffer))
  {
    Step_1b_Subroutine(buffer);
    Copy_Text(word, buffer);
  }
}
/******************************************************************************/
void Step_1b_Subroutine(char *word)
{
  if (Has_Suffix(word, "at") || Has_Suffix(word, "bl") || Has_Suffix(word, "iz"))
  {
	Append_Text(word, "e");
  }
  else if (Ends_In_Double(word))
  {
    Strip_Last_Char(word);
  }
  else if (Is_Short_Word(word))
  {
    Append_Text(word,"e");
  }
  return;
}
/******************************************************************************/
void Step_1c(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  
  Copy_Text(buffer, word);
  
  if (Remove_Suffix(buffer, "y"))
  {
    if (Is_Consonant(buffer, Get_Text_Length(buffer)-1) &&
        Get_Text_Length(buffer) > 1)
    {
      Append_Text(buffer, "i");
      Copy_Text(word, buffer);
	} 
  }
  return;
}
/******************************************************************************/
void Step_2(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  Copy_Text(buffer, word);

  char *r1 = Get_Measure_Offset(buffer);
  
  if (Remove_Suffix(r1, "ational") || Remove_Suffix(r1, "ation") ||
      Remove_Suffix(r1, "ator"))
  {
    Append_Text(buffer, "ate");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "ization") || Remove_Suffix(r1, "izer"))
  {
    Append_Text(buffer, "ize");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "iveness") || Remove_Suffix(r1, "iviti"))
  {
    Append_Text(buffer, "ive");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "ousli") || Remove_Suffix(r1, "ousness"))
  {
    Append_Text(buffer, "ous");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "alism") || Remove_Suffix(r1, "aliti") ||
           Remove_Suffix(r1, "alli"))
  {
    Append_Text(buffer, "al");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "biliti"))
  {
    Append_Text(buffer, "ble");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "tional"))
  {
    Append_Text(buffer, "tion");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "enci"))
  {
    Append_Text(buffer, "ence");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "anci"))
  {
    Append_Text(buffer, "ance");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "abli"))
  {
    Append_Text(buffer, "able");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "bli"))
  {
    Append_Text(buffer, "ble");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "entli"))
  {
    Append_Text(buffer, "ent");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "fulness") || Remove_Suffix(r1, "fulli"))
  {
    Append_Text(buffer, "ful");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "ogi"))
  {
	if (buffer[Get_Text_Length(buffer)-1] == 'l')
	{
      Append_Text(buffer, "og");
      Copy_Text(word, buffer);
    }  
  }
  else if (Remove_Suffix(r1, "lessli"))
  {
    Append_Text(buffer, "less");
    Copy_Text(word, buffer);
  }
   else if (Remove_Suffix(r1, "li"))
  {
	if (Ends_In_Valid_LI(buffer))
	{
      Copy_Text(word, buffer);
    }  
  }
}
/******************************************************************************/
void Step_3(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  Copy_Text(buffer, word);

  char *r1 = Get_Measure_Offset(buffer);
  char *r2 = Get_Measure_Offset(r1);

  if (Remove_Suffix(r1, "ational"))
  {
    Append_Text(buffer, "ate");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "tional"))
  {
    Append_Text(buffer, "tion");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "alize"))
  {
    Append_Text(buffer, "al");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "icate") || Remove_Suffix(r1, "iciti") ||
           Remove_Suffix(r1, "ical"))
  {
    Append_Text(buffer, "ic");
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r1, "ful") || Remove_Suffix(r1, "ness"))
  {
    Copy_Text(word, buffer);
  }
  else if (Remove_Suffix(r2, "ative"))
  {
    Copy_Text(word, buffer);
  }
  return;
}
/******************************************************************************/
void Step_4(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  Copy_Text(buffer, word);

  char *r2 = Get_Measure_Offset(Get_Measure_Offset(buffer));
 
  const char *suffix[] = {"al",    "ance", "ence", "er",  "ic",  "able", "ant",
	                      "ement", "ment", "ent",  "ism", "ate", "iti",  "ous",
	                      "ive",   "ize",  0};
  int i = 0;

  while (suffix[i])
  {
    if (Remove_Suffix(r2, suffix[i]))
    {
	  Copy_Text(word, buffer);
      return;
	}
	i++;
  }
  if (Remove_Suffix(r2, "ion"))
  {
	if (buffer[Get_Text_Length(buffer)-1] == 's' ||
	    buffer[Get_Text_Length(buffer)-1] == 't')
	{
      Copy_Text(word, buffer);
    }  
  }  
  return;
}
/******************************************************************************/
void Step_5(char *word)
{
  char buffer[Get_Text_Length(word)+1];
  Copy_Text(buffer, word);

  char *r1 = Get_Measure_Offset(buffer);
  char *r2 = Get_Measure_Offset(r1);
  
  if (Remove_Suffix(r2, "e") || (Remove_Suffix(r1, "e") &&
                                !Ends_In_Short_Syllable(buffer)))
  {
    Copy_Text(buffer, word);
  }
  else if (Remove_Suffix(r2, "l") && buffer[Get_Text_Length(buffer)-1] == 'l')
  {
    Copy_Text(word, buffer);
  }
  return;
}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void Stem_Word(char *word)
{
  if (Get_Text_Length(word) > 2)
  {
	Step_0 (word);
    Step_1a(word);
    Step_1b(word);
    Step_1c(word);
    Step_2 (word);
    Step_3 (word);
    Step_4 (word);
    Step_5(word);
  }
}
