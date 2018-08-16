#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.1.0(14)"

#define GRN "\x1B[32m"
#define RESET "\x1B[0m"

void usage();
void print_version();
void lntrim(char *str);
char* find_xcode_path(const char *version);
void switch_xcode_version(char *version);

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
	    char* argument = argv[1];
        if (strcmp(argument, "--version") == 0)
        {
            print_version();
        }
        else if (strcmp(argument, "--help") == 0)
        {
            usage();
        }
        else
        {
            switch_xcode_version(argument);
        }
    	return 0;
    }

    usage();
	return -1;
}

void usage()
{
    printf("Usage: \n\n    $ %sxcselect%s <xcode_version> [--version] [--help]\n\nex.\n    $ xcselect 9.4.1\n    $ xcselect 8.2.1\n    $ xcselect 7.3.1\n\n", GRN, RESET);
}

void print_version()
{
    printf("%s\n", VERSION);
}

void switch_xcode_version(char *version) 
{
    char *path = find_xcode_path(version);
    if (path != NULL)
    {
        char buffer[255];
        snprintf(buffer, sizeof(buffer), "sudo xcode-select -s \"%s\"", path);
        system(buffer);

        system("xcodebuild -version");
    } 
    else 
    {
        printf("Error: the specified version(%s) of Xcode was not found.\n", version);
    }
}

char* find_xcode_path(const char *version)
{
    system("rm -rf /tmp/xcselect && mkdir /tmp/xcselect");
    system("xcode_plist_paths=$(ls -l /Applications/ | grep -i \"xcode\" | awk '{print $9}');for p in $xcode_plist_paths; do echo `defaults read \"/Applications/${p}/Contents/Info.plist\" CFBundleShortVersionString`\",/Applications/${p}\" >> \"/tmp/xcselect/detected_xcode_versions\"; done");

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/tmp/xcselect/detected_xcode_versions", "r");
    if (fp == NULL)
        return NULL;

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        char *xcode_version = strsep(&line,",");
        char *xcode_path = strsep(&line,",");
        lntrim(xcode_path);
        if (xcode_version != NULL && xcode_path != NULL && strstr(xcode_version, version) != NULL) 
        {
            char *tmp_path = "/Contents/Developer";
            char *found_path = (char *) malloc(1 + strlen(xcode_path) + strlen(tmp_path));
            strcpy(found_path, xcode_path);
            strcat(found_path, tmp_path);
            return found_path;
        }
    }

    fclose(fp);
    if (line)
        free(line);

    return NULL;
}

void lntrim(char *str)
{  
    char *p;  
    p = strchr(str, '\n');  
    if (p != NULL)
    {  
        *p = '\0';  
    }  
}
