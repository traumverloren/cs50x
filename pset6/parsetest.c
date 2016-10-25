#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

char* parse(const char* line, char* abs_path, char* query);

int main(void)
{
    printf("test line, please:\n");
    string line = GetString();
    
    char abs_path[50];
    char query[50];
    string word = parse(line, abs_path, query);
    
    printf("%s\n", word);
}


char* parse(const char* line, char* abs_path, char* query)
{
    // example of what needs parsing: 
    // GET hello.html HTTP/1.1
    
    // copy const char line into a new temp variable
    char temp[strlen(line)];
    strcpy(temp, line);
    
    char* sp = " ";
    char* methodPointer = strtok(temp, sp);
    char* requestTargetPointer = strtok(NULL, sp);
    char* httpPointer = strtok(NULL, sp);

    // have to get these out of pointers and copied into strings so can actually do stuff with them.
    char method[strlen(methodPointer)];
    char requestTarget[strlen(requestTargetPointer)];
    char http[strlen(httpPointer)];
    strcpy(method, methodPointer);
    strcpy(requestTarget, requestTargetPointer);
    strcpy(http, httpPointer);
    
    printf("method: %s\nrequestTarget: %s\nhttp:%s\n", method, requestTarget, http);
    
    // Ensure that request-line (which is passed into parse as line) is consistent with these rules. If it is not, respond to the browser with 400 Bad Request and return false.
    // if method is not GET, respond to the browser with 405 Method Not Allowed and return false;
    if (strcasecmp(method, "GET") != 0)
    {
        return "405";
    }

    // if request-target does not begin with /, respond to the browser with 501 Not Implemented and return false;
    if (requestTarget[0] != '/')
    {
        return "501";
    }
    
    // // if request-target contains a ", respond to the browser with 400 Bad Request and return false;
    if (strchr(requestTarget, '"') != NULL)
    {
        return "400";
    }
    
    // // if HTTP-version is not HTTP/1.1, respond to the browser with 505 HTTP Version Not Supported and return false.
    if (strcasecmp(http, "HTTP/1.1") != 0)
    {
        return "505";
    }

    // get the abs_path, query from requestTarget
    if (strchr(requestTarget, '?') == NULL)
    {
        abs_path = requestTarget;
        query = NULL;
        printf("%s\n", abs_path);
        printf("%s\n", query);    
        
        return "123";
    }
    
    char* abs_pathPointer = strtok(requestTarget, "?");
    char* queryPointer = strtok(NULL, "?");
    abs_path = strcpy(abs_path, abs_pathPointer);
    query = strcpy(query, queryPointer);

        
    printf("%s\n", abs_path);
    printf("%s\n", query);    
    return "done";

}
