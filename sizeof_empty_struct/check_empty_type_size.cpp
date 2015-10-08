#include <stdio.h>

struct s
{

};

int main(int argc, char **argv)
{
    struct s object;
    printf("Empty type size in g++: [%lu]\n", sizeof(object));
    return 0;
}
