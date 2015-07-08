#include <stdio.h>
// exit, fopen
#include <stdlib.h> 
#include <string.h>
#include "./helper/code_gen.h" // load helper function

#define WEB_ADDR_BUFF (100)
#define XAMMP_DRIVE_BUFF (100)
#define PATH_BUFF (300)


// TODO
// add more validations
// use typedef :S
// test buffer size

static char webiste[WEB_ADDR_BUFF];        // website name
static char xammp_drive[XAMMP_DRIVE_BUFF]; // dir where xammp is located 
static char webiste_path[PATH_BUFF];
static char xammp_path[PATH_BUFF];

// for code update
static char vhost_path[PATH_BUFF];
static const char host_path[] = "C:/Windows/System32/drivers/etc/hosts";


// restart appache
// apache\bin\httpd.exe -k restart

// create full path
void create_site_dir()
{
    int status;
    status = mkdir(webiste_path);

    if (status < 0){
        printf("Error: unable to create Dir \"%s\"\n", webiste_path);
        exit(1);
    }
}


void init_cli()
{
    fputs("Site Name: ", stdout);
    fgets(webiste, WEB_ADDR_BUFF, stdin);

    fputs("xammp Drive:", stdout);
    fgets(xammp_drive, XAMMP_DRIVE_BUFF, stdin);

    // remove new line char
    webiste[strcspn(webiste, "\r\n")] = 0;
    xammp_drive[strcspn(xammp_drive, "\r\n")] = 0;

    // update var
    strcpy(webiste_path, xammp_drive);
    strcat(webiste_path, ":/xampp/htdocs/");
    strcat(webiste_path, webiste);

    strcpy(xammp_path, xammp_drive);
    strcat(xammp_path, ":/xampp/");
    
    strcpy(vhost_path, xammp_path);
    strcat(vhost_path, "apache/conf/extra/httpd-vhosts.conf");
}

// typedef struct
// {
//     char webiste[WEB_ADDR_BUFF];        // website name
//     char websit_dir[PATH_BUFF];
//     char xammp[XAMMP_DRIVE_BUFF]; // dir where xammp is located 
//     char xammp_drive[PATH_BUFF];
//     char vhost[PATH_BUFF];
// } cli_info;


// void init_cli_str()
// {
//     cli_info ci;   
//     fputs("Site Name: ", stdout);
//     fgets(ci.webiste, sizeof(ci.webiste), stdin);

//     fputs("xammp Drive:", stdout);
//     fgets(ci.xammp_drive, sizeof(ci.xammp_drive), stdin);

//     // remove new line char
//     ci.webiste[strcspn(ci.webiste, "\r\n")] = 0;
//     ci.xammp_drive[strcspn(ci.xammp_drive, "\r\n")] = 0;

//     // xammmp_drive:/xammp/htdocs/website
//     snprintf(ci.websit_dir, sizeof(ci.websit_dir), 
//             "%s%s%s", ci.xammp_drive,":/xampp/htdocs/", ci.webiste);

//     // xammmp_drive:/xammp/
//     snprintf(ci.xammp, sizeof(ci.xammp),
//             "%s%s", ci.xammp_drive, ":/xampp/");
    
//     snprintf(ci.vhost, sizeof(ci.xammp),
//             "%s%s", ci.xammp, "apache/conf/extra/httpd-vhosts.conf");
// }

void f_append(const char *path, const char *text)
{
    FILE *fd;    
    fd = fopen(path, "a");

    if (fd == NULL){
        printf("Error: unable to Write to file %s\n", path);
        exit(1);
    }

    fprintf(fd, text);
    fclose(fd);
}

void append_to_host()
{
    char *hosts_code = host_code(webiste);
    f_append(host_path, hosts_code);
}

void append_to_vhost()
{
     char *vhost_content = vhost_code(webiste, webiste_path);
     f_append(vhost_path, vhost_content);
}

int main()
{
    init_cli();
    // init_cli_str();
    create_site_dir(); // create dir
    append_to_host();
    append_to_vhost();

    return 0;
}
