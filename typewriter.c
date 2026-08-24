#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *read_f(char path[]) {
  FILE *f = fopen(path, "r");
  if (!f) {
    return NULL;
  }
  unsigned int size = 4096;
  char *text = malloc(size);
  if (!text) {
    fclose(f);
    return NULL;
  }
  char letter;
  unsigned int pos = 0;
  while ((letter = fgetc(f)) != EOF) {
    if (pos >= size) {
      char *tmp = realloc(text, size << 1);
      if (!tmp) {
        return NULL;
      }
      text = tmp;
      size <<= 1;
    }
    text[pos++] = letter;
  }
  text[pos] = '\0';
  fclose(f);
  return text;
}

void typewriter(char path[], double speed) {
  char *text = read_f(path);
  if (text == NULL) {
    return;
  }
  printf("\033[H\033[J");
  for (int i = 0; i < strlen(text); i++) {
    printf("%c", text[i]);
    fflush(stdout);
    usleep((int)(speed * 1e6));
  }
  free(text);
}

int main(int argc, char *argv[]) {
  int opt = 0;
  double speed = 0.1;
  char *path = NULL;
  while ((opt = getopt(argc, argv, "s:h")) != -1) {
    switch (opt) {
    case 's':
      speed = atof(optarg);
      if (speed <= 0) {
        fprintf(stderr, "SPEED VALUE MUST BE POSITIVE\n");
        return 1;
      }

      break;
    case 'h':
      fprintf(stdout, "USAGE: command <filename> -s <value>\n");
      return 1;
    case '?':
      fprintf(stderr, "UNRECOGNIZED FLAG\n");
      return 1;
    }
  }

  if (optind < argc) {
    path = argv[optind];
  } else {
    fprintf(stderr, "FILE NOT FOUND\n");
    return 1;
  }
  typewriter(path, speed);
}
