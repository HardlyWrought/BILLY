struct word_t;
/******************************************************************************/
void Open_Database(const char *filepath);
/******************************************************************************/
void Close_Database();
/******************************************************************************/
struct word_t *Create_Word_From_Text(const char *text);
/******************************************************************************/
void Set_Tag(struct word_t *word, const char *tag);
/******************************************************************************/
void Set_Tag_Odds(struct word_t *word, float odds);
/******************************************************************************/
void Destroy_Tagged_Word(struct word_t *tagged_word);
/******************************************************************************/
struct word_t *Add_Tag(struct word_t *tagged_word, const char *text,
                                    const char *tag, float odds);
/******************************************************************************/
struct word_t *Assign_Possible_Tags(const char *word);
/******************************************************************************/
struct word_t *Create_Trellis_Diagram(char *text);
/******************************************************************************/
struct word_t *Insert_Tagged_Word(struct word_t *tagged_word, const char *word);
/******************************************************************************/
void Print_Tags(struct word_t *head);
/******************************************************************************/
