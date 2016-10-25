#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>


char* lookup(char* path);

int main(void)
{
    printf("test path, please:\n");
    string path = GetString();
    
    string word = lookup(path);
    
    printf("%s\n", word);
}

char* lookup(char* path)
{
    // use strchr to go to the dot in the path
    char* fileExtension;

    fileExtension = strchr(path, '.');
    
    if (fileExtension != NULL)
    {
        // compare what is after the dot to know the file type & return that MIME type
        // strcasecmp ignores case
        if (strcasecmp(fileExtension, ".css") == 0)
            return "text/css";
        else if (strcasecmp(fileExtension, ".html") == 0)
            return "text/html";
        else if (strcasecmp(fileExtension, ".gif") == 0)
            return "image/gif";
        else if (strcasecmp(fileExtension, ".ico") == 0)
            return "image/x-icon";
        else if (strcasecmp(fileExtension, ".jpg") == 0)
            return "image/jpg";
        else if (strcasecmp(fileExtension, ".js") == 0)
            return "text/javascript";
        else if (strcasecmp(fileExtension, ".php") == 0)
            return "text/x-php";
        else if (strcasecmp(fileExtension, ".png") == 0)
            return "image/png";
    }
    return NULL;

}


