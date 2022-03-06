#include "snow_stem.h"
#include "../text_clean/text_clean.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    Clean_Text(argv[i]);
    char **words = Divide_Text_Words(argv[i]);
    printf("\n");
    
    for (int j = 0; j < Get_Num_Words(argv[i]); j++)
    {
      Stem_Word(words[j]);
      printf("%s", words[j]);

      if (j < Get_Num_Words(argv[i])-1)
      {
        printf(" ");
	  }
    }
  printf("\n\n");
  Destroy_Divided_Text(words);
  }
  return 55;
}
