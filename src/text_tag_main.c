#include "text_tag.h"

int main(int argc, char **argv)
{
  Open_Database("./data/db/training_dict.db");

  for (int i = 1; i < argc; i++)
  { 
    struct word_t *tagged_words = Create_Trellis_Diagram(argv[i]);
    Print_Tags(tagged_words);
  }
  free(tagged_words);
  Close_Database();
  return 55;
}
