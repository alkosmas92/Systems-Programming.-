#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <poll.h>
#include <math.h>
#include <sys/times.h>  /* times() */
#include <unistd.h>     /* sysconf() */
#include <time.h>
#include <dirent.h>
#include "skip_list.h"
#include <netdb.h>

#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define POOL_SIZE 6



// int num_of_items = 15;


#define YES 1
#define NO  0

volatile sig_atomic_t fl_s = 0;
void handle_sigusr1(int sigmy_num) {
	fl_s++;
	// printf("/\\/\\ Child1 Process %d: Received USR1\n", getpid());
}
void handle_sigusr2(int sigmy_num) {
	fl_s=fl_s+2;
	// printf("/\\/\\ Child1 +++++2222 %d: Received USR1\n", getpid());
}

volatile sig_atomic_t break_s = 0;
void handle_break1(int sigmy_num) {
	break_s++;
	printf("/\\/\\ Child1 Process %d: Received USR2\n", getpid());
}



/* Executable: mysig */
int main(int argc , char * argv[]){
	int test,start=0, rc , end=0 , counter=0,fd1 ,fd2;
	my_num prime[50];
	struct pollfd fdarray [1];
	char country[30]; char temp[2]; char symbol='/'; char filename[50];
	DIR *pNir; DIR *pLir;
	DIR *pDir;
  struct dirent *pNirent; struct dirent *pLirent; struct dirent *pDirent;
	char final_file[20];
	// strcpy(final_file,argv[1]);
	char final_file1[20];
	// strcpy(final_file1,argv[2]);
	int count_filaname=0;
	int sel=0;
	 	int i;
	signal(SIGUSR1, handle_sigusr1);
	signal(SIGUSR2, handle_sigusr2);


		int sockfd, connfd;
		struct sockaddr_in servaddr, cli;
		double t1, t2,t5, cpu_time;
		struct tms tb1, tb2;
		double ticspersec;
		int i_time, sum = 0 , num_file ,  size_bf;
		int num_thread =atoi(argv[3]);

		int my_size;
		int txt_num=0;

		 ios_hash *H;
		Slist * LC_DIR=simple_list_create();
		Slist * A=simple_list_create();
		Slist * TEMP_L=simple_list_create();

			record *dir=malloc(sizeof(record));
			 pid_t my_pid=getpid();

		// socket create and varification
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd == -1) {
			printf("socket creation failed...\n");
			exit(0);
		}
		else
			printf("Socket successfully created..\n");
		bzero(&servaddr, sizeof(servaddr));

		// assign IP, PORT
		servaddr.sin_family = AF_INET;
		servaddr.sin_addr.s_addr = inet_addr(argv[2]);
		servaddr.sin_port = htons(atoi(argv[1]));
		int con=0;
		// connect the client socket to server socket
		while(con!=1){

		if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {

		}
		else{
			printf("connected client  to the server..\n");
			con=1;
			}
		}
		int b_size;
		char inser[30];



		char log_file[30];
		char log_symbol[2]="\n";

		char my_str[20];
		int len;
		FILE* fp;
		strcpy(log_file , argv[3]);

/*_____READ FROM pid from parent_______*/

		  read(sockfd , &len , sizeof(int));
			sprintf(my_str, "%d", len);
			strncat(log_file, &my_str, sizeof(strlen(my_str))); //sximatise to swsto log_file

/*_____READ FROM SOCKET SIZE FOR BLLOM_______*/

		read (sockfd , &b_size , sizeof(int) );
		size_bf=(b_size*8)/32;
	
			H=create_hash_ios(size_bf);


/*_____read the count of countries_______*/
		read (sockfd , &my_size , sizeof(int) );
		char buffer_countries[my_size][30];
		my_num temp_prime[my_size];
		my_num temp_prime1[my_size];
		int sr=argc-(my_size);
		for(sr ; sr < argc ; sr++){			//apothikeuse ta directories kai grapse sto log file
			strcpy(temp_prime[sr-4].country,argv[sr]);
			strcpy(inser,argv[sr]);
			str_cut(inser,0,10);
			strncat(inser, &log_symbol, 2);
			fp = fopen(log_file, "a+");
			fputs(inser, fp);
			fclose(fp);
		}

		for(int i=0 ; i<my_size ; i++){ //Diavse to megethos pou diaxirizetai kathe paidi
			strcpy(country,temp_prime[i].country);
			 pNir = opendir (country);
			strncat(country, &symbol, 1);

			txt_num=0;
				while ((pNirent = readdir(pNir)) != NULL) {
					strcpy(filename , country);
						 // take first symbol
						memcpy(temp , pNirent->d_name , 1);
						// take only name of country
						if (isalpha(temp[0]) != 0){

							strncat(filename, &pNirent->d_name , strlen(pNirent->d_name)+1);
							 strcpy(dir->directory , filename);
							 strcpy(buffer_countries[i] , filename);

							   insert_simple_list(LC_DIR , dir ); //perna ta diractories se mia lista
							   read_file(H , A ,filename , size_bf  ); //perna ta stoixeia stis domes

						}
					}
		}



			 write(sockfd, &my_pid, sizeof(pid_t));  //perna to process id kathe paidiou
		while(H->next!=NULL){
			 write(sockfd, &H->name_ios, 20);  				//penra  name iou
			 for(int i=0 ; i<size_bf ; i++){
				 write(sockfd, &H->bloom[i], sizeof(int));   //grapse ta stoixeia tou bloom
			 }
		 H	=	H->next;
	 }
	 strcpy(H->name_ios , "NULL"  );
	 write(sockfd, &H->name_ios, 20);  				//penra  name iou
	 	char garaze[25];
		int ff;
		int r_quest;
	 	int celtics;


	 /*________-------------SIGNAL-----------------___________*/

	 while(!fl_s){
		 char request[20];
		 record * my_rec=malloc(sizeof(record));
 		 pause(); /* Wait For a Signal */


				 read (sockfd , &garaze , 25 );  // epeksergasou to aitimata
		if (strcmp(garaze, "/travelRequest") == 0) {
						read (sockfd , &ff , sizeof(int) );
						if(ff==1){
						read (sockfd , &my_rec->id , 30 );
						read (sockfd , &my_rec->date , 20 );
						read (sockfd , &my_rec->countryfrom , 20 );
						read (sockfd , &my_rec->countryto , 20 );
						read (sockfd , &my_rec->vacine , 20 );
						strcpy(my_rec->country , my_rec->countryfrom);

							r_quest =find_simple_list_request(A ,my_rec  );  ///elekse to aitima

							  write(sockfd, &r_quest, sizeof(int)); //gurna tin apantisi tou aitmatos ston patera
							}
							//	ff=0;
						 fl_s=0;
				 //}
			 }

		else if (strcmp(garaze, "/searchVaccinationStatus") == 0) {
					int num;
					read (sockfd , &my_rec->id , 30 );


					num=find_simple_list_num(A , my_rec->id );

					 write(sockfd , &num ,sizeof(int));

			 if(num>0){
						 for(int i =0 ; i < num ; i++ ){
							 A=find_simple_list_rec(A , my_rec->id);
							 write(sockfd , &A->rec->id ,30);
							 printf("ID %s \n",A->rec->id );
							 write(sockfd , &A->rec->first_name ,20);
							 printf("FIRST %s \n",A->rec->first_name );
							 write(sockfd , &A->rec->last_name ,20);
							 printf("LAST_NAME %s \n",A->rec->last_name );
							 write(sockfd , &A->rec->country ,20);
							 write(sockfd , &A->rec->age ,20);
							 write(sockfd , &A->rec->ios ,20);
							 write(sockfd , &A->rec->date ,20);
							 write(sockfd , &A->rec->vacine ,20);
							 }
				 	 }

		}

		 else if (strcmp(garaze, "/addVaccinationRecords") == 0) {
						 read (sockfd , &my_rec->id , 30 );
						 int count_filaname=0;
						 strcpy(country,my_rec->id);


							pNir = opendir (country);
						 strncat(country, &symbol, 1);

							 while ((pNirent = readdir(pNir)) != NULL) {
								 strcpy(filename , country);
										// take first symbol
									 memcpy(temp , pNirent->d_name , 1);
									 // take only name of country
									 if (isalpha(temp[0]) != 0){


										 strncat(filename, &pNirent->d_name , strlen(pNirent->d_name)+1);

											 sel=print_simple_list(LC_DIR , filename); //elenkse an uparxei neo directories
											 if(sel==1){
												 celtics=1;

											 }

												if(sel == 1){   //an uparxei neo dir tote kane ta akoloutha
													strcpy(dir->directory , filename);
													insert_simple_list(LC_DIR , dir );  //ananewse tis domes
													read_file_w(H , A ,filename , size_bf  );
												}
										}
									}
									closedir(pNir);
									write(sockfd, &celtics, sizeof(int));

									int size=sizeof(H->name_ios);

										if(celtics==1){
													while(H->next!=NULL){
													write(sockfd, &H->name_ios, 20);
														for(int i=0 ; i<size_bf ; i++){
															write(sockfd, &H->bloom[i], sizeof(int));
														}
													H	=	H->next;
												}
												strcpy(H->name_ios, "NULL");
												write(sockfd, &H->name_ios, 20);
										}
									fl_s=0;
						}

			 fl_s=0;
	 		}

 		close(sockfd);
		return 0;
}

	//

	// int size_bf=(atoi(argv[2])*8)/32;
	// ios_hash *H=create_hash_ios(size_bf);
	// 	// HList *HA=list_node_create();
	// 	// CList *C=list_country_node_create();
	// 	Slist * LC_DIR=simple_list_create();
	// 	Slist * A=simple_list_create();
	// 	Slist * TEMP_L=simple_list_create();
	//  ios_hash *H;
	// Slist * LC_DIR=simple_list_create();
	// Slist * A=simple_list_create();
	// Slist * TEMP_L=simple_list_create();
	// 	record *dir=malloc(sizeof(record));
	// 	signal(SIGUSR1, handle_sigusr1);
	// 	signal(SIGUSR2, handle_sigusr2);

// double t1, t2,t5, cpu_time;
// struct tms tb1, tb2;
// double ticspersec;
// int i_time, sum = 0 , num_file , b_size ,  size_bf;
//
//
//
// int my_size;
//
//  my_num temp_prime[12];
// //
//
// 			fd1 = open(final_file, O_RDONLY);
// 						 for (;;){
// 										 fdarray[0].fd = fd1 ;
// 										 fdarray[0].events = POLLIN ;
// 										 rc = poll ( fdarray , 1 , 0);
// 										if ( ( rc == 1) && ( fdarray [0].revents & POLLIN ) ){
// 													 if ( fdarray[0].fd == fd1 ){
//
// 																 read (fd1 , &b_size , sizeof(int) );
// 																  size_bf=(b_size*8)/32;
// 																 	H=create_hash_ios(size_bf);
// 																	 // HList *HA=list_node_create();
// 																	 // CList *C=list_country_node_create();
// 																	 record *dir=malloc(sizeof(record));
//
// 																read (fd1 , &my_size , sizeof(int) );
// 																read (fd1 , &temp_prime , my_size*sizeof(my_num) );
// 																for(int i=0 ; i<my_size ; i++){ //Diavse to megethos pou diaxirizetai kathe paidi
// 																	strcpy(country,temp_prime[i].country);
// 																	 pNir = opendir (country);
// 																	strncat(country, &symbol, 1);
//
// 																		while ((pNirent = readdir(pNir)) != NULL) {
// 																			strcpy(filename , country);
// 																				 // take first symbol
// 																				memcpy(temp , pNirent->d_name , 1);
// 																				// take only name of country
// 																				if (isalpha(temp[0]) != 0){
//
// 																					strncat(filename, &pNirent->d_name , strlen(pNirent->d_name)+1);
// 																					 strcpy(dir->directory , filename);
// 																					 insert_simple_list(LC_DIR , dir ); //perna ta diractories se mia lista
// 																					 read_file(H , A ,filename , size_bf  ); //perna ta stoixeia stis domes
//
// 																				}
// 																			}
// 																}
//
// 															 fflush ( stdout );
// 												 }
// 										 }
// 										 else if ( ( rc == 1) && ( fdarray [0].revents & POLLHUP ) ){
// 											 break;
// 										 }
// 										 else if ( ( rc == 0)  ){
// 											 	break;
// 										 }
// 							 }
// 				 close(fd1);
// 				 unlink(final_file);
// 				 closedir(pNir);
// 				 pid_t my_pid=getpid();
//
//
// 				 fd2 = open(final_file1 , O_WRONLY);
// 				 while(H->next!=NULL){
// 						write(fd2, &my_pid, sizeof(pid_t));  //perna to process id kathe paidiou
// 						write(fd2, &H->name_ios, 20);  				//penra  name iou
// 						for(int i=0 ; i<size_bf ; i++){
// 							write(fd2, &H->bloom[i], sizeof(int));   //grapse ta stoixeia tou bloom
// 						}
// 					H	=	H->next;
// 				}
// 				 close(fd2);
// 				 int k=0;
// 				 int myk_size;
// 				 int fd4;
// 				 int check,fd3;
// 				 int celtics;
// 				 int r_quest=1;
//
//
// 					char garaze[25];
//
// 				 while(!fl_s){
// 					 char request[20];
// 					 record * my_rec=malloc(sizeof(record));
// 					 pause(); /* Wait For a Signal */
//
// 					 fd3 = open(file_signal, O_RDONLY);
// 					 for (;;){
// 						 fdarray [0].fd = fd3 ;
// 						 fdarray [0].events = POLLIN ;
// 						 rc = poll ( fdarray , 1 , 0);
// 						 if ( ( rc == 1) && ( fdarray [0].revents & POLLIN ) ){
//
// 							 if ( fdarray [0]. fd == fd3 ){
//
// 								 read (fd3 , &garaze , 25 );  // epeksergasou to aitimata
//
// 							 if (strcmp(garaze, "/travelRequest") == 0) {
// 								 read (fd3 , &my_rec->id , 30 );
// 									 read (fd3 , &my_rec->date , 20 );
// 									 read (fd3 , &my_rec->countryfrom , 20 );
// 									 read (fd3 , &my_rec->countryto , 20 );
// 									 read (fd3 , &my_rec->vacine , 20 );
// 									 strcpy(my_rec->country , my_rec->countryfrom);
//
// 									 	 r_quest =find_simple_list_request(A ,my_rec  );
//
//
// 										fd4 = open(argv[4] , O_WRONLY);
// 											write(fd4, &r_quest, sizeof(int));
// 										close(fd4);
// 										fl_s=0;
// 								}
// 							 else if (strcmp(garaze, "/searchVaccinationStatus") == 0) {
// 								 int num;
// 								 read (fd3 , &my_rec->id , 30 );
//
//
// 								 num=find_simple_list_num(A , my_rec->id );
// 								 	fd4 = open(argv[4] , O_WRONLY);
// 									write(fd4 , &num ,sizeof(int));
//
// 							if(num>0){
// 								// printf("GIATI\n" );
// 							 		  for(int i =0 ; i < num ; i++ ){
// 											A=find_simple_list_rec(A , my_rec->id);
// 											fd4 = open(argv[4] , O_WRONLY);
// 											write(fd4 , &A->rec->id ,30);
// 											write(fd4 , &A->rec->first_name ,20);
// 											write(fd4 , &A->rec->last_name ,20);
// 											write(fd4 , &A->rec->country ,20);
// 											write(fd4 , &A->rec->age ,20);
// 											write(fd4 , &A->rec->ios ,20);
// 											write(fd4 , &A->rec->date ,20);
// 											write(fd4 , &A->rec->vacine ,20);
// 										 	 close(fd4);
// 										  }
// 								}
//
// 								fl_s=0;
// 							}
// 					 else if (strcmp(garaze, "/addVaccinationRecords") == 0) {
// 								 read (fd3 , &my_rec->id , 30 );
// 								 int count_filaname=0;
// 								 // printf("LEAA %s\n", my_rec->id );
// 								 strcpy(country,my_rec->id);
//
//
// 									pNir = opendir (country);
// 								 strncat(country, &symbol, 1);
//
// 									 while ((pNirent = readdir(pNir)) != NULL) {
// 										 strcpy(filename , country);
// 												// take first symbol
// 											 memcpy(temp , pNirent->d_name , 1);
// 											 // take only name of country
// 											 if (isalpha(temp[0]) != 0){
//
//
// 												 strncat(filename, &pNirent->d_name , strlen(pNirent->d_name)+1);
//
// 													 sel=print_simple_list(LC_DIR , filename); //elenkse an uparxei neo directories
// 													 if(sel==1){
// 														 celtics=1;
//
// 													 }
//
// 														if(sel == 1){   //an uparxei neo dir tote kane ta akoloutha
// 															strcpy(dir->directory , filename);
// 															insert_simple_list(LC_DIR , dir );  //ananewse tis domes
// 															read_file_w(H , A ,filename , size_bf  );
// 												;
//
// 														}
// 												}
// 											}
// 											closedir(pNir);
//
// 										int size=sizeof(H->name_ios);
// 											fd4 = open(final_file1 , O_WRONLY);
// 											if(celtics==1){
// 														while(H->next!=NULL){
// 														write(fd4, &celtics, sizeof(int));
// 														write(fd4, &H->name_ios, 20);
// 															for(int i=0 ; i<size_bf ; i++){
// 																write(fd4, &H->bloom[i], sizeof(int));
// 															}
// 														H	=	H->next;
// 													}
// 											}
// 											close(fd4);
// 											fl_s=0;
// 								}
// 							}
// 							if(strcmp(garaze, "/exit")==0){
// 								destractor_ios_hash(H);
// 							}
//
// 						 }
// 						 else if ( ( rc == 1) && ( fdarray [0].revents & POLLHUP ) ){
// 							 break;
// 						 }
// 						 else if ( ( rc == 0)){
// 							 break;
// 						 }
// 					 }
//
//
//
//
// 				 }
//
// 				 // printf("downnfl_s is %d \n",fl_s );
// 				 return 0;
// 			}
