# Deamon-process-example-
A daemon process is a process which runs in background and has no controlling terminal.

Since a daemon process usually has no controlling terminal so almost no user interaction is required. Daemon processes are used to provide services that can well be done in background without any user interaction.

For example a process that runs in background and observes network activity and logs any suspicious communication can be developed as a daemon process.
Daemon Process Design

A daemon process can be developed just like any other process but there is one thing that differentiates it with any other normal process ie having no controlling terminal. This is a major design aspect in creating a daemon process. This can be achieved by :

    Create a normal process (Parent process)
    Create a child process from within the above parent process
    The process hierarchy at this stage looks like :  TERMINAL -> PARENT PROCESS -> CHILD PROCESS
    Terminate the the parent process.
    The child process now becomes orphan and is taken over by the init process.
    Call setsid() function to run the process in new session and have a new group.
    After the above step we can say that now this process becomes a daemon process without having a controlling terminal.
    Change the working directory of the daemon process to root and close stdin, stdout and stderr file descriptors.
    Let the main logic of daemon process run.

So we see that above steps mark basic design steps for creating a daemon.
