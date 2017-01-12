
#include "oop.h"

    typedef struct {

        int (*open)(void *self, char *fspec);

        int (*close)(void *self);

        int (*read)(void *self, void *buff, size_t max_sz, size_t *p_act_sz);

        int (*write)(void *self, void *buff, size_t max_sz, size_t *p_act_sz);

    } tCommClass;


    static int tcpOpen (void *tcp, char *fspec) {

        printf ("Opening TCP: %s\n", fspec);

        return 0;

    }

    static int tcpInit (tCommClass *tcp) {

        tcp->open = &tcpOpen;

        return 0;

    }

    static int httpOpen (void *http, char *fspec) {

        printf ("Opening HTTP: %s\n", fspec);

        return 0;

    }

    static int httpInit (tCommClass *http) {

        http->open = &httpOpen;

        return 0;

    }

    int main (void) {

        int status;

        tCommClass commTcp, commHttp;


        // Same 'base' class but initialized to

        // different sub-classes.

        tcpInit (&commTcp);

        httpInit (&commHttp);


        // Called in exactly the same manner.

        status = (commTcp.open)(&commTcp, "bigiron.box.com:5000");

        status = (commHttp.open)(&commHttp, "http://www.microsoft.com");


        return 0;
    }


#if 0
    tCommClass commRs232; /* RS-232 communication class */

    commRs232.open = &rs232Open;

    commRs232.write = &rs232Write;


    tCommClass commTcp; /* TCP communication class */

    commTcp.open = &tcpOpen;

    commTcp.write = &tcpWrite;
#endif