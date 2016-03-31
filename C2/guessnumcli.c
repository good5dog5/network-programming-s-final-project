#include "unp.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int _cl, _ck, _cj, _ch;
int firG, secG, thiG, fourG;
int A1, A2, A3, A4;

int _A1() {return A1;}
int _A2() {return A2;}
int _A3() {return A3;}
int _A4() {return A4;}

void a(int a) { A1=a;}   
void b(int b) { A2=b;}   
void c(int c) { A3=c;}   
void d(int d) { A4=d;} 
  
int _firG() {return firG;}
int _secG() {return secG;}
int _thiG() {return thiG;}
int _fourG() {return fourG;}

int cl1() {return _cl;}
int ck1() {return _ck;}
int cj1() {return _cj;}
int ch1() {return _ch;}

void first(int num) {firG=num/1000;}   
void second(int num) {secG=(num/100)%10;}   
void third(int num) {thiG=(num/10)%10;}   
void fourth(int num) {fourG=num%10;} 

void cl(int q) {_cl=q;}   
void ck(int w) {_ck=w;}   
void cj(int e) {_cj=e;}   
void ch(int r) {_ch=r;}   

void game() {	
	printf("======電腦會收到一組0~9的四個亂數，請進行猜數字遊戲======\n");
	printf("規則》》》\n");
	printf("1	輸入4個數字（ex:1234)\n");
	printf("2	若輸入數字之值對且位置對則為A，輸入數字值對且位置不對為B\n");
	printf("3	若輸入不足或超過四個數字皆為無效輸入\n");
	printf("4	電腦可重複輸入同一數字（ex:2222),玩家不可\n");

	_cl = 0;
	_ck = 0;
	_cj = 0;
	_ch = 0;
	firG = 0;
	secG = 0;
	thiG = 0;
	fourG = 0;
}

void cho(int answer1, int answer2, int answer3, int answer4){
	 A1 = answer1;
	 A2 = answer2;
	 A3 = answer3;
	 A4 = answer4;
}

void check(){	
	time_t	ticks;
	ticks = time(NULL);
        srand((int) ticks); 
	while(A1==A2) {A2=rand()%10;}
	while(A1==A3) {A3=rand()%10;}
	while(A1==A4) {A4=rand()%10;}
	while(A2==A3 || A1==A3) {A3=rand()%10;}
	while(A2==A4 || A1==A4) {A4=rand()%10;}
	while(A3==A4 || A2==A4 || A1==A4) {A4=rand()%10;}
}

int validnumber( int G1,int G2,int G3,int G4 ) {
    	int a=0;
	
	if( G1 == G2 || G1 == G3  || G1== G4){return 1;}
	else{a++;}

	if( G2 == G3 || G2== G4){return 1;}
	else{a++;}

	if( G3 ==  G4){return 1;}
	else{a++;}

	if(G1>57 || G1<48){return 1;}
	else{a++;}

	if(G2>57 || G2<48){return 1;}
	else{a++;}

	if(G3>57 || G3<48){return 1;}
	else{a++;}

	if(G4>57 || G4<48){return 1;}
	else{a++;}

	if(a==7){
	return 0;}
}

void enternumber(){
	int G1=0,G2=0,G3=0,G4=0;
	int v;
	int bigNum=0;
	char temp[MAXLINE];
	int num;
	printf("請輸入四個數字：\n");
	scanf("%s",temp);
	num=strlen(temp);
	
	if(num>4){
		printf("輸入數字有誤，請重新輸入：\n");
		printf("%s \n",temp);
		enternumber();
	}	
	else{
		G1=temp[0]; G2=temp[1]; G3=temp[2]; G4=temp[3];
		if((v=validnumber(G1,G2,G3,G4))==0) {
			bigNum=(G1-48)*1000+(G2-48)*100+(G3-48)*10+(G4-48);
			first(bigNum);
			second(bigNum);
			third(bigNum);
			fourth(bigNum);
		}
		else{
			printf("輸入數字有誤，請重新輸入：\n");
			enternumber();	
		}
	}
}


int guessa(int p,int o,int i,int u) {
	int rr=0;
	if(p==_A1()) {rr++;}
	if(o==_A2()) {rr++;}
	if(i==_A3()) {rr++;}
	if(u==_A4()) {rr++;}
	return rr;
}

int guessb(int p,int o,int i,int u){
	int A,rw=0;
	A = guessa(p,o,i,u);
	if(p==_A1() || p==_A2() || p==_A3() || p==_A4()){rw++;}
	if(o==_A1() || o==_A2() || o==_A3() || o==_A4()){rw++;}
	if(i==_A1() || i==_A2() || i==_A3() || i==_A4()){rw++;}
	if(u==_A1() || u==_A2() || u==_A3() || u==_A4()){rw++;}
	rw=rw-A;
	return rw;
}

void print(int A,int B){
	printf("此次猜測的數字結果為%dA%dB\n",A,B);
}

int playerwin(int sockfd) {
	int type;
	printf("此回合由玩家勝出，是否要繼續遊戲？\n") ;
	printf("若要繼續則輸入1，若不繼續則輸入2(隨便輸入以不繼續論)：");
	scanf("%d",&type);
	if(type==1){
		Writen(sockfd,"3\n", 2);
	return 1;}
	Writen(sockfd,"2\n", 2);
	return 0;
}
		
int compare(int a,int b) {
	if(a!=b) {return 1;}
	return 0;
}

int computerguess() {
	time_t	ticks;
	ticks = time(NULL);
        srand((int) ticks); 
	int Q=rand()%10, W=rand()%10, G=rand()%10, H=rand()%10, A=0, B=0;
	int e=cl1(), f=ck1(), g=cj1(), h=ch1();
	int ans1=_A1(), ans2=_A2(), ans3=_A3(), ans4=_A4();	
	while(Q==W || Q==G || Q==H) {Q=rand()%10;}
	while(W==G || W==H || W==Q) {W=rand()%10;}
	while(G==H || Q==G || W==G) {G=rand()%10;}
	while(G==H || W==H || Q==H) {H=rand()%10;}
	if(e!=ans1){
		if(e==0) {cl(Q);}
		e=cl1();
		if(compare(Q,e)==1) {cl(Q);}
		e=cl1();
	}
	if(f!=ans2){
		if(f==0) {ck(W);}
		f=ck1();
		if(compare(W,f)==1) {ck(W);}
		f=ck1();
	}
	if(g!=ans3){
		if(g==0) {cj(G);}
		g=cj1();
		if(compare(G,g)==1) {cj(G);}
		g=cj1();
	}
	if(h!=ans4){
		if(h==0) {ch(H);}
		h=ch1();
		if(compare(H,h)==1) {ch(H);}
		h=ch1();
	}
	printf("此次為電腦猜測，電腦猜測為%d%d%d%d\n",e,f,g,h);
	A=guessa(e, f, g, h);
	B=guessb(e, f, g, h);
	print(A,B);

	return 0;
}

int computerwin(int sockfd) {
	int type;
	printf("此回合由電腦勝出，是否要繼續遊戲？\n");
	printf("若要繼續則輸入1，若不繼續則輸入2(隨便輸入以不繼續論)：");
	scanf("%d",&type);
	if(type==1) {
		Writen(sockfd,"1\n", 2);
		return 1;
	}
	Writen(sockfd,"0\n", 2);
	return 0;
}
	
void
game_start(int sockfd, char sendline[MAXLINE])
{
	char	 recvline[MAXLINE];
	time_t	ticks;
	ticks = time(NULL);
        srand((int) ticks); 
	int A=0, B=0, C=1;
	int z;
	int ans=0, answer1, answer2, answer3, answer4;
	while(C==1) {
		int guess1, guess2, guess3, guess4;
		ans = 0;
		if (Readline(sockfd, recvline, 8) == 0)
			err_quit("str_cli: server terminated prematurely");
		for (z=0; recvline[z]!='\n'; z++){
			ans = ans*10 + (recvline[z]-'0');
		}
		answer1 = ans/1000;
		answer2 = (ans/100)%10;
		answer3 = (ans/10)%10;
		answer4 = ans%10;;
		game();
		cho(answer1, answer2, answer3, answer4);
		C = 3;
		while (C==3) {
			printf("由玩家%s進行猜數字\n",sendline);
			enternumber();
			guess1 = _firG();
			guess2 = _secG();
			guess3 = _thiG();
			guess4 = _fourG();
			A=guessa(guess1, guess2, guess3, guess4);
			B=guessb(guess1, guess2, guess3, guess4);
			print(A,B);
			if(A==4)
				C = playerwin(sockfd);
			else{
				A = computerguess();
				if(A==4)
					C = computerwin(sockfd);
			}
		}
	}	
}
int
main(int argc, char **argv)
{
	int			sockfd;
	struct sockaddr_in	servaddr;
	char 			sendline[MAXLINE];
	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	printf("您的學號為︰");
	scanf("%s", sendline);
	Writen(sockfd, sendline, 8);
	Writen(sockfd, "\n", 1);
	game_start(sockfd, sendline);
	exit(0);
}




