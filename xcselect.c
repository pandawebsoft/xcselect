#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define VERSION "1.0.0(8)"

#define GRN	"\x1B[32m"
#define RESET "\x1B[0m"

void usage();
void print_version();
char* find_xcode_path(const char *path, const char *keyword);
void switch_xcode_version(char *version);

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
	    char* argument = argv[1];
        if (strcmp(argument, "--version") == 0)
        {
            print_version();
        }
        else if(strcmp(argument, "--help") == 0)
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

char* find_xcode_path(const char *path, const char *keyword)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        return "";
    }

    char *xcode_path = "";
    while ((entry = readdir(dir)) != NULL)
    {
		if (strcasestr(entry->d_name, "xcode") != NULL && strstr(entry->d_name, keyword) != NULL)
		{
			char *tmp_path = "/Contents/Developer";
			xcode_path = (char *) malloc(1 + strlen(path) + strlen(tmp_path));
			strcpy(xcode_path, path);
			strcat(xcode_path, entry->d_name);
			strcat(xcode_path, tmp_path);
		    break;
		}
	}

    closedir(dir);
    return xcode_path;
}

void switch_xcode_version(char *version) 
{
    char *path = find_xcode_path("/Applications/", version);

    char buffer[255];
    snprintf(buffer, sizeof(buffer), "sudo xcode-select -s \"%s\"", path);
    system(buffer);

    system("xcodebuild -version");
}
