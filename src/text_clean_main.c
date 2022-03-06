#include "text_clean.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    Clean_Text(argv[i]);
    printf("\n%s\n\n", argv[i]);
  }
  return 55;
}
