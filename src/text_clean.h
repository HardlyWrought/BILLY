#define MAX_TEXT_LEN 5000
/******************************************************************************/

/******************CHARACTER COMPARE FUNCTIONS*********************************/

/******************************************************************************/
int Is_Punctuation(const char ch);
/******************************************************************************/
int Is_Stop_Character(const char ch);
/******************************************************************************/
int Is_Whitespace (const char ch);
/******************************************************************************/
int Is_Alphabetic(const char ch);
/******************************************************************************/
int Is_Alphanumeric(const char ch);
/******************************************************************************/
int Is_Part_Of_Word(const char ch);
/******************************************************************************/
int Is_Digit(const char ch);
/******************************************************************************/
int Is_Lowercase_Letter(const char ch);
/******************************************************************************/
int Is_Capital_Letter(const char ch);
/******************************************************************************/

/******************WORD COMPARE FUNCTIONS**************************************/

/******************************************************************************/
int Is_Same(const char *input, const char *reference);
/******************************************************************************/
int Is_Stop_Word(const char *word);
/******************************************************************************/
int Is_Number(const char *word);
/******************************************************************************/
int Is_One_Character(const char *word);
/******************************************************************************/
int Is_One_Letter_Word(const char *word);
/******************************************************************************/
int Has_Char(const char *text, const char ch);
/******************************************************************************/
int Ends_In_Char(const char *word, const char ch);
/******************************************************************************/
int Has_Suffix(const char *word, const char *suffix);
/******************************************************************************/
int Get_Chars_In_Text(const char *input, const char *reference);
/******************************************************************************/
int Get_Chars_Not_In_Text(const char *input, const char *reference);
/******************************************************************************/

/******************TEXT COMPARE FUNCTIONS**************************************/

/******************************************************************************/
int Is_In_Text(const char *text, const char *reference);
/******************************************************************************/

/********************TEXT DATA FUNCTIONS***************************************/

/******************************************************************************/
int Get_Num_Char(const char *text, const char ch);
/******************************************************************************/
int Get_Num_Delimiters(const char *text);
/******************************************************************************/
int Get_Num_Words(const char *text);
/******************************************************************************/
int Get_Text_Length(const char *text);
/******************************************************************************/
int Get_Length_Longest_Word(const char *text);
/******************************************************************************/
/******************************************************************************/

/*********************TEXT CLEANING FUNCTIONS**********************************/

/******************************************************************************/
void Strip_Chars(char *text, int (*Compare_Func)(const char));
/******************************************************************************/
void Leave_Chars(char *text, int (*Compare_Func)(const char));
/******************************************************************************/
void Strip_Words(char *text, int (*Compare_Func)(const char *));
/******************************************************************************/
void Strip_Leading_Whitespace (char *text);
/******************************************************************************/
void Strip_Trailing_Whitespace (char *text);
/******************************************************************************/
void Strip_Double_Whitespace(char *text);
/******************************************************************************/
void Convert_Whitespace_To_Space(char *text);
/******************************************************************************/
void Normalize_Whitespace(char *text);
/******************************************************************************/
void Strip_Last_Char(char *text);
/******************************************************************************/

/******************TEXT CREATE/DESTROY FUNCTIONS*******************************/

/******************************************************************************/
char **Create_Matrix_Chars(int rows, int columns);
/******************************************************************************/
char **Divide_Text_Words(const char *text);
/******************************************************************************/
void Destroy_Divided_Text(char **text);
/******************************************************************************/

/*********************CHARACTER MANIP FUNCTIONS********************************/

/******************************************************************************/
char Convert_Char_Lowercase(char ch);
/******************************************************************************/

/*********************WORD MANIP FUNCTIONS*************************************/

/******************************************************************************/
void Append_Word(char *text, const char *word);
/******************************************************************************/

/*********************TEXT MANIP FUNCTIONS*************************************/

/******************************************************************************/
void Constrain_Text_Length(char *text, int length);
/******************************************************************************/
void Copy_Text(char *destination, const char *source);
/******************************************************************************/
void Append_Text(char *destination, const char *source);
/******************************************************************************/
void Convert_Text_Lowercase(char *text);
/******************************************************************************/
void Delete_Text(char *text);
/******************************************************************************/
char *Tokenize_Text(char *text, char *delim, char **save_ptr);
/******************************************************************************/
void Clean_Text(char *text);
/******************************************************************************/
