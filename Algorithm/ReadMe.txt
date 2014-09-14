http://stackoverflow.com/questions/12885628/changing-the-scanf-delimiter

######################<<Changing the scanf() delimiter>>###################################

Consider this (C99) code:

#include <stdio.h>

int main(void)
{
    char buffer[256];

    while (scanf("%255[^\n]", buffer) == 1)
        printf("Found <<%s>>\n", buffer);
    int c;
    if ((c = getchar()) != EOF)
        printf("Failed on character %d (%c)\n", c, c);
    return(0);
}
When I run it and type in a string 'absolutely anything with   spaces TABTABtabs galore!', it gives me:

Found <<absolutely anything with   spaces       tabs galore!>>
Failed on character 10 (
)
ASCII (UTF-8) 1010 is newline, of course.

Does this help you understand your problem?

It works in this case (for a single line) but if I want to take multiple lines of input into an array of arrays then it fails. And I don't get how scanf returns a value in your code?

There are reasons why many (most?) experienced C programmers avoid scanf() and fscanf() like the plague; they're too hard to get to work correctly. I'd recommend this alternative, using sscanf(), which does not get the same execration that scanf() and fscanf() do.

#include <stdio.h>

int main(void)
{
    char line[256];
    char sen[256];

    while (fgets(line, sizeof(line), stdin) != 0)
    {
        if (sscanf(line, "%255[^\n]", sen) != 1)
            break;
        printf("Found <<%s>>\n", sen);
    }
    int c;
    if ((c = getchar()) != EOF)
        printf("Failed on character %d (%c)\n", c, c);
    return(0);
}
This reads the line of input (using fgets() which ensures no buffer overflow (pretend that the gets() function, if you've heard of it, melts your computer to a pool of metal and silicon), then uses sscanf() to process that line. This deals with newlines, which are the downfall of the original code.

char sen[20];
for (i=0;i<2;i++)
{
    scanf("%[^\n]s",sen);
    printf("%s\n",sen);
}
Problems:

You do not check whether scanf() succeeded.
You leave the newline in the buffer on the first iteration; the second iteration generates a return value of 0 because the first character to read is newline, which is the character excluded by the scan set.
The gibberish you see is likely the first line of input, repeated. Indeed, if it were not for the bounded loop, it would not wait for you to type anything more; it would spit out the first line over and over again.
Return value from scanf()

The definition of scanf() (from ISO/IEC 9899:1999) is:

§7.19.6.4 The scanf function

Synopsis

 #include <stdio.h>
 int scanf(const char * restrict format, ...);
Description

2 The scanf function is equivalent to fscanf with the argument stdin interposed before the arguments to scanf.

Returns

3 The scanf function returns the value of the macro EOF if an input failure occurs before any conversion. Otherwise, the scanf function returns the number of input items assigned, which can be fewer than provided for, or even zero, in the event of an early matching failure.

Note that when the loop in my first program exits, it is because scanf() returned 0, not EOF.