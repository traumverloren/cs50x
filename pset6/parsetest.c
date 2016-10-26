// feature test macro requirements
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

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
    
        // no double spaces allowed!
    if (strstr(line, "  ") != NULL)
    {
        return "400";
    }
    
    // copy const char line into a new temp variable
    char* temp = strdup(line);
    
    char* method = strtok(temp, " ");
    char* requestTarget = strtok(NULL, " ");
    char* http = strtok(NULL, "\r\n");
    
    printf("method: %s\nrequestTarget: %s\nhttp:%s\n", method, requestTarget, http);
    
    printf("%c\n", requestTarget[0]);
    
    // Ensure that request-line (which is passed into parse as line) is consistent with these rules. If it is not, respond to the browser with 400 Bad Request and return false.
    // if method is not GET, respond to the browser with 405 Method Not Allowed and return false;
    if (strcmp(method, "GET") != 0) 
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

    // set temp abs_path and query pointers
    char* abs_path_temp = strtok(requestTarget, "?");
    char* query_temp = strtok(NULL, "?");
    
    strcpy(abs_path, abs_path_temp);
    
    printf("%s\n", abs_path_temp);

    if (query_temp == NULL)
    {
        strcpy(query, "\0");
    }
    else
    {
        strcpy(query, query_temp);
    }
    
        printf("%s\n", query);    


    // get the abs_path and set query if no "?" in requestTarget
    // if (strchr(requestTarget, '?') == NULL)
    // {
    //     abs_path = requestTarget;
    //     query = "";
    //     printf("%s\n", abs_path);
    //     printf("%s\n", query);    
        
    //     return "123";
    // }
    
   
    // printf("%s\n", abs_path);
    // printf("%s\n", query);    
    return "done";

}
