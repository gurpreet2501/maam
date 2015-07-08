#include <stdio.h>
#include "code_gen.h"

#define VHOST_BUFF (1028)
#define HOST_BUFF (514)

char *vhost_code(char *webiste, char *xammp_path)
{
    static char vhost_content[VHOST_BUFF];

    snprintf(vhost_content, VHOST_BUFF,
            "\n<VirtualHost *:80>\n"    
            "   ServerAdmin webmaster@%s\n"
            "   DocumentRoot \"%s\" \n"
            "   ServerName %s\n"
            "   ErrorLog \"logs/%s-error.log\"\n"
            "   CustomLog \"logs/%s-access.log\" common\n"
            "</VirtualHost>\n", 
            webiste, xammp_path, webiste, webiste, webiste
    );

    return vhost_content;

}

char *host_code(char *webiste)
{
    static char host_content[HOST_BUFF];
    snprintf(host_content, HOST_BUFF, "\n127.0.0.1   %s\n127.0.0.1   www.%s\n", webiste, webiste);
    return host_content;
}
