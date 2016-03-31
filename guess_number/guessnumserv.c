#include    "unp.h"
#include    <stdlib.h>
#include    <stdio.h>
#include    <sys/time.h>

void sig_chld(int signo)
{
        pid_t   pid;
        int     stat;

        while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        return;
}

int answer1, answer2, answer3, answer4;

void check(int ans1, int ans2, int ans3, int ans4, FILE *fp){
    int ran[10];
    int an;
    for(an=0;an<10;an++) ran[an]=11;
    ran[ans1]=0;
    while(ran[ans2]==0) {ans2=rand()%10;}
    ran[ans2]=0;
    answer2=ans2;
    while(ran[ans3]==0) {ans3=rand()%10;}
    ran[ans3]=0;
    answer3=ans3;
    while(ran[ans4]==0) {ans4=rand()%10;}
    ran[ans4]=0;
    answer4=ans4;
}

void gameRun(int sockfd, FILE *fp)
{   
    int z = 1, n;
    char line[MAXLINE];
    char line2[MAXLINE];  
    if ((n = Readline(sockfd, line, MAXLINE)) == 0) {
        fprintf(fp, "no id received. quitting\n");
        return;
    }
    sprintf(line2, "%s", line);
    fprintf(fp, "player: %s\n", line);
       
    while(z!=0 && z!=2){
        answer1=rand()%10;
        answer2=rand()%10;
        answer3=rand()%10;
        answer4=rand()%10;
        check(answer1, answer2, answer3, answer4, fp);
        printf("ans: %d%d%d%d\n", answer1, answer2 , answer3, answer4);
        sprintf(line, "%d%d%d%d\n", answer1, answer2 , answer3, answer4);
        Writen(sockfd, line , strlen(line));
        fprintf(fp, "the answer is: %s\n", line);
        if ((n = Readline(sockfd, line, MAXLINE)) == 0) {
            fprintf(fp, "no response. quitting\n");
            return;
        }
    z = atoi(line);
    if (z == 0 )
        fprintf(fp, "The game of player %s with computer is over, the final winner is computer and game is over \n", line2);
    if (z == 1 )
        fprintf(fp, "The game of player %s with computer is over,winner is computer and  game is still continue...\n", line2);
    if (z == 2 )
        fprintf(fp, "The game of player %s with computer is over,the final winner is %s and game is over \n", line2, line2);
    if (z == 3 )
        fprintf(fp, "The game of player %s with computer is over,winner is %s and  game is still continue...\n",line2,line2);
    }
    return ;
} 

int
main(int argc, char **argv)
{
    int         listenfd, connfd;
    pid_t           childpid;
    socklen_t       clilen;
    struct sockaddr_in  cliaddr, servaddr;
        char                    buff[MAXLINE];
        time_t          ticks;
        FILE            *fp;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

        Signal(SIGCHLD, sig_chld);      /* must call waitpid() */

        if ((fp = fopen("guessnumserv.log", "a")) == NULL) {
           printf("log file open error!\n");
           exit(0);
        }
    for ( ; ; ) {
        clilen = sizeof(cliaddr);
                if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
                        if (errno == EINTR)
                                continue;               /* back to for() */
                        else
                                err_sys("accept error");
                }

        if ( (childpid = Fork()) == 0) {    /* child process */
            Close(listenfd);    /* close listening socket */
                        ticks = time(NULL);
                        fprintf(fp, "===================\n");
                        fprintf (fp, "%.24s: connected from %s, port %d\n",
                        ctime(&ticks),
                        Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof (buff)),
                        ntohs(cliaddr.sin_port));
                        srand((int) ticks);

            gameRun(connfd, fp);    /* process the request */
                        ticks = time(NULL);
                        fprintf (fp, "%.24s: disconnected from %s, port %d\n",
                             ctime(&ticks),
                             Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof (buff)),
                             ntohs(cliaddr.sin_port));

            exit(0);
        }
        Close(connfd);          /* parent closes connected socket */
    }
}
