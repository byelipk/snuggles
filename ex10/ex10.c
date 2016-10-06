#include <stdio.h>

// We can convert a lowercase char to uppercase by subtracting 32
char upcase(char letter) {
  if (letter >= 'a' && letter <= 'z') {
    return letter - 32;
  } else {
    return letter;
  }
}

// We can convert an uppercase char to lowercase by adding 32
char downcase(char letter) {
  if (letter >= 'A' && letter <= 'Z') {
    return letter + 32;
  } else {
    return letter;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("ERROR: You need one argument.\n");
    // This is how you abort a program
    return 1;
  }

  int i = 0;
  for (i = 0; i < argv[1][i] != '\0'; i++;) {
    /* char letter = argv[1][i]; */
    char letter = upcase(argv[1][i]);
    /* char letter = downcase(argv[1][i]); */

    switch (letter) {
      // Fallthrough
      case 'a':
      case 'A':
        printf("%d: 'A'\n", i);
        break;

      // Fallthrough
      case 'e':
      case 'E':
        printf("%d: 'E'\n", i);
        break;

      // Fallthrough
      case 'i':
      case 'I':
        printf("%d: 'I'\n", i);
        break;

      // Fallthrough
      case 'o':
      case 'O':
        printf("%d: 'O'\n", i);
        break;

      // Fallthrough
      case 'u':
      case 'U':
        printf("%d: 'U'\n", i);
        break;

      // Fallthrough
      case 'y':
      case 'Y':
        // why i > 2? is this a bug?
        if (i > 2) {
          // it's only sometimes i
          printf("%d: 'Y'\n", i);
        }

        break;
      
      default:
        printf("%d: %c is not a vowel.\n", i, letter);
    }
  }

  return 0;
}
