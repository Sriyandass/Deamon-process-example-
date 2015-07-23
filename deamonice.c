/*
 * This example daemonizes a process, 
 * creates a new directory if ctrl-n is pressed,
 * sleeps 20 seconds and terminates afterwards.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void skeleton_daemon()
{
    pid_t pid;

    if((pid = fork()) < 0)                  /* Fork off the parent process */
        exit(1);
    if(pid > 0)                             /* Success: Let the parent terminate */
        exit(0);
    if(setsid() < 0)                        /* On success: The child process becomes session leader */
        exit(1);        
    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */                    
    signal(SIGCHLD, SIG_IGN);               /* Catch, ignore and handle signals */
    signal(SIGHUP, SIG_IGN);
    if((pid = fork()) < 0)                  /* Fork off for the second time*/
        exit(0);
    if(pid > 0)                             /* Success: Let the parent terminate */
        exit(0);
    umask(0);                               /* Set new file permissions */
    chdir("/");                             /* Change directory to root*/

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }
    openlog ("firstdaemon", LOG_PID, LOG_DAEMON);
}

int main()
{
    skeleton_daemon();
    while (1)
    {
        //TODO: Insert daemon code here.
        syslog (LOG_NOTICE, "First daemon started.");
        sleep (20);
        break;
    }
    syslog (LOG_NOTICE, "First daemon terminated.");
    closelog();
    return 0;
}