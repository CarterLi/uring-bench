#include <unistd.h>

int main() {
  static char str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < 999999; i++) {
    write(STDOUT_FILENO, &str[i % 26], 1);
  }
}
