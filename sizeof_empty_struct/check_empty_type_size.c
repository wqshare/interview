#include <stdio.h>

struct s
{

};

int main(int argc, char **argv)
{
    struct s object;
    printf("Empty type size in gcc: [%lu]\n", sizeof(object));
    return 0;
}
