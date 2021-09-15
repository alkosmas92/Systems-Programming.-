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
#include <dirent.h>
#include "skip_list.h"
#include <time.h>
#include <sys/times.h>  /* times() */
#include <unistd.h>     /* sysconf() */
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr




volatile sig_atomic_t fl_s =0;



int main(int argc , char * argv[]) {
	struct dirent *pNirent; struct dirent *pLirent; struct dirent *pDirent;
	 DIR *pNir; DIR *pLir;
	 DIR *pDir;
	int status,fd1,fd2,fd3,rc,num_file;
	char str[20];
	int lim,num_e;
	pid_t pid;
	int k=0 , b_size;
	char child[10];
	char my_str[30];
	int my_port;
	char char_num_thread[30];
	int num_thread;
	char log_file[]="log_file.";
//	lim=atoi(argv[1]);


	 while(k<argc){					// vres tis simaies kai pare ta data pou xriazesai
 	 	if(!strcmp("-s",argv[k])){
			 b_size = atoi(argv[k+1]) ;
		 }
		else if(!strcmp("-m",argv[k])){
			 lim = atoi(argv[k+1]) ;
			 strcpy(child , argv[k+1]);
		 }
		else if(!strcmp("-p",argv[k])){
			 my_port = atoi(argv[k+1]) ;
		 }
		else if(!strcmp("-t",argv[k])){
			strcpy(char_num_thread , argv[k+1]);
			 num_thread = atoi(argv[k+1]) ;
		 }
		 k++;
	 }

	 int port_list[lim];
	 char find_ip[lim][30];
	 pid_t my_pid[lim];
	 pid_t pid_temp;

	 int size_bf=(b_size*8)/32;
	 int table[size_bf];
	 for(int i=0 ; i<size_bf ; i++){
		 table[i] = 0;
	 }

	 char hostname[128];
	 char ip[16];
	 struct hostent* host;
	 struct sockaddr_in sock_addr;
	 int i;

	 // 取得 hostname
	 gethostname(hostname, sizeof(hostname));

	 // 根據 hostname 取得 hostent struct
	 host = gethostbyname(hostname);

	 // 印出 hostname 的 alias
	 for (i = 0; host->h_aliases[i]; ++i) {
	 }

	 // h_addr_list point to (struct in_addr)
	 // 印出所有的 ip address
	 for (i = 0; host->h_addr_list[i]; ++i) {
		 sock_addr.sin_addr = *((struct in_addr*) host->h_addr_list[i]);
		 inet_ntop(AF_INET, &sock_addr.sin_addr, ip, sizeof(ip));
	 }


	int sockfd[lim], connfd[lim], len;

	for(num_e=0 ; num_e <lim ; num_e++){
		port_list[num_e]=my_port+num_e;
	}



	struct sockaddr_in servaddr, cli;

	// socket create and verification
	 num_e=0;


	 for (num_e=0 ; num_e < lim ; num_e ++){

		 sockfd[num_e] = socket(AF_INET, SOCK_STREAM, 0);


		 struct sockaddr_in sin;
		 socklen_t lenn = sizeof(sin);

			//Accept the data packet from client and verification
			if (sockfd[num_e] == -1) {
			 printf("socket creation failed...\n");
			 exit(0);
			}
			else
			 printf("Socket successfully created..\n");
			bzero(&servaddr, sizeof(servaddr));

			// assign IP, PORT
			servaddr.sin_family = AF_INET;
			servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
			servaddr.sin_port = htons(port_list[num_e]);

			// Binding newly created socket to given IP and verification
			if ((bind(sockfd[num_e], (SA*)&servaddr, sizeof(servaddr))) != 0) {
			 printf("socket bind failed...\n");
			 exit(0);
			}
			else
			 printf("Socket successfully binded..\n");
		 }

		 char my_name[20];
		 char symbol='/'; char temp[2]; char country[30];
		 	strcpy(country,"Countries");

		 	ios_hash *H=create_hash_ios(size_bf);
		 	ios_hash *TEMP=create_hash_ios(size_bf);
		 	ios_hash *FUN=create_hash_ios(size_bf);
		 	ios_hash *HELP=create_hash_ios(size_bf);


		 	FUN->bloom=malloc(size_bf * sizeof(int));  // orizw to bllom wste na mporw na eisagw ta stoixeia metepeita
		 	for(int k=0 ; k<size_bf ; k++){
		 		FUN->bloom[k]=0;
		 	}
		 	TEMP=FUN;


		 	pNir = opendir (country);   //anoigw to file gia na vgw to plithos twn fakelo xwrwn
		 	if (pNir == NULL) {
		 			printf ("Cannot open directory '%s'\n", country);
		 			return 1;
		 	}

		 	// Process each entry.
		 	num_file=0;
		 	while ((pNirent = readdir(pNir)) != NULL) {
		 		memcpy(temp , pNirent->d_name , 1);
		 		// take only name of country
		 		if (isalpha(temp[0]) != 0){
		 								num_file++;
		 							}
		 				strcpy(country,"Countries");
		 		}
		 		closedir(pNir);

		 		int size_array[lim];  //array gia na krataei to megethos pou diaxeirizetai kathe paidi

		 		int temp_size;
		 		int my_div=num_file % lim;
		 		temp_size = (num_file / lim)+1;
		 		my_num temp_prime[lim][temp_size];

		 		for (num_e=0;num_e<lim; num_e++){
		 			size_array[num_e]=temp_size;
		 		}

		 		for(num_e=0 ; num_e < lim ; num_e++){
		 			if(num_e>=my_div){
		 			size_array[num_e] = size_array[num_e] - 1;
		 			}
		 		}



		 		pDir = opendir (country);  //anoigw to fakelo na parw tis xwres
		 		if (pDir == NULL) {
		 				printf ("Cannot open directory '%s'\n", country);
		 				return 1;
		 		}
		 		int test;


		 			status=0;
		 			num_e=0;
		 			while ((pDirent = readdir(pDir)) != NULL) {
		 				memcpy(temp , pDirent->d_name , 1);
		 				if (isalpha(temp[0]) != 0){
		 					strncat(country, &symbol, 1);
		 					strncat(country, &pDirent->d_name, strlen(pDirent->d_name)+1);
		 					if(size_array[num_e] <= status){
		 						num_e++;
		 						status=0;
		 						printf("\n" );
		 					}
		 							strcpy(temp_prime[num_e][status].country,country);

		 									status++;
		 				}
		 				strcpy(country,"Countries");
		 			}


					char log_pid[20];




	 	 for (num_e=0;num_e<lim; num_e++)								//dimourgise tosa paidia osa to lim me ena patera//apo smaragdaki
			if ( (pid = fork()) <= 0 )
				 break;
/*-----------------------------------Child--------------------------------------------------------*/


   if(pid==0){
		 char **orderedIds;

		 int variableNumberOfElements=4+size_array[num_e];

		 orderedIds = malloc((variableNumberOfElements+1) * sizeof(char*));
		 for (int i = 0; i < variableNumberOfElements; i++)
		 orderedIds[i] = malloc((20+1) * sizeof(char));

		 sprintf(my_str, "%d", port_list[num_e]);
		 sprintf(my_str, "%d", port_list[num_e]);
		 strcpy(orderedIds[0] , "./mysig" );
		 strcpy(orderedIds[1] , my_str );
		 strcpy(orderedIds[2] , ip   );
		 strcpy(orderedIds[3] , log_file   );


		 for(int r = 0 ; r < size_array[num_e] ; r++  ){
 			 strcpy(orderedIds[4+r] , temp_prime[num_e][r].country );
 		}


      if((execvp("./mysig",orderedIds )) == -1){
                        perror("exec");
            }
   }


/*-----------------------------------Parent--------------------------------------------------------*/
			else{

				for (num_e=0 ; num_e < lim ; num_e ++){

					//Now server is ready to listen and verification
					 if ((listen(sockfd[num_e], 5)) != 0) {
					 	printf("Listen failed...\n");
					 	exit(0);
					 }
					 else
					 	printf("Server listening..\n");

					 len = sizeof(cli);
					 connfd[num_e] = accept(sockfd[num_e], (SA*)&cli, &len);
					 if (connfd < 0) {
					 	printf("server acccept failed...\n");
					 	exit(0);
					 }
					 else
					 	printf("server acccept the client...\n");
						int len=getpid();




						 write(connfd[num_e] , &len , sizeof(int));  //write the pid from father

						 write(connfd[num_e] , &b_size ,sizeof(int)); //write size for bloom

 						write(connfd[num_e] , &size_array[num_e] ,sizeof(int)); //write how mach child read every child

						read (connfd[num_e] ,  &pid_temp, sizeof(pid_t) );  //diavase to kathe paidi_id
						 my_pid[num_e]=pid_temp;			//kratise to kathe pid tou kathe paidioy

						 while(strcmp(my_name,"NULL")!=0){
							 read (connfd[num_e] ,  &my_name, 20 );
							 if(strcmp(my_name,"NULL")!=0){

									TEMP=H;
									initiaze_ios_for(TEMP ,my_name , size_bf); //arxikopoiesai to ios_table
									int k=0;
									while(TEMP->next!=NULL){  // perna ta stoixeia sto bllom
										if(strcmp(TEMP->name_ios,my_name)==0){
											for(int i=0 ; i<size_bf ; i++){
												read (connfd[num_e] ,  &FUN->bloom[i], sizeof(int) );
												if(FUN->bloom[i]!=0){
													TEMP->bloom[i]=FUN->bloom[i];
												}
											}
											break;
										}
										TEMP=TEMP->next;
									}
								}
						 }
						 strcpy(my_name , "NO"  );
					 }


						 int retain_child;
						 		Slist * S=simple_list_create_n();
						 		Slist * S_country=simple_list_create_n();

							 for (num_e=0;num_e<lim; num_e++){
							 }

							 sprintf(my_str, "%d", getpid());
							 strncat(log_file, &my_str, sizeof(strlen(my_str)));

							 printMenu();

							 char *UserCommand = NULL;
								 size_t combytes = 200;
								 UserCommand = (char *) malloc(combytes);
								 char * line = (char *) malloc(combytes);
								 char *broke;
								 char garaze[25];
								 int r_quest;
								 int ff;

							 record * my_rec=malloc(sizeof(record));

							 while(getline(&UserCommand, &combytes, stdin) != EOF) {
									 strcpy(line, UserCommand);
									 broke = strtok(UserCommand, " \n");    // Tokenize input
									 char check[]=" ";

								 if (broke != NULL) {

									 strcpy(garaze,broke);  //perna to prwto orisma

/*----------------1isinartisi-------------travelRequest---------------------------*/

									 if (strcmp(garaze, "/travelRequest") == 0) {

										 record * my_rec=malloc(sizeof(record));
										 //
										 broke = strtok(NULL,check);
										 strcpy(my_rec->id,broke);
										 broke = strtok(NULL,check);
										 strcpy(my_rec->date,broke);
										 broke = strtok(NULL,check);
										 strcpy(my_rec->countryfrom,broke);
										 strcpy(my_rec->country,broke);
										 broke = strtok(NULL,check);
										 strcpy(my_rec->countryto,broke);
										 broke = strtok(NULL,check);
										 strcpy(my_rec->ios,broke);

										 strcpy(country,"Countries/");
										 strncat(country, &my_rec->countryfrom , strlen(my_rec->countryfrom)+1);

										 for(num_e=0 ; num_e < lim ; num_e++ ){  //vres se poio paidi tha to steileis
											 for(int k = 0 ; k < size_array[num_e] ; k++){

												 if(strcmp(temp_prime[num_e][k].country , country)==0){
													 retain_child = num_e; //apothikeuse to
												 }

											 }
										 }
										 if(!vacine_check(H , my_rec->id ,my_rec->ios , size_bf)) {
								 			printf("MAYBE\n");
											ff=1;
												 write(connfd[retain_child] , &garaze ,25); //perna tis katalliles eggrafes
												 write(connfd[retain_child] , &ff ,sizeof(int)); //perna tis katalliles eggrafes
												 write(connfd[retain_child] , &my_rec->id ,30);
												 write(connfd[retain_child] , &my_rec->date ,20);
												 write(connfd[retain_child] , &my_rec->countryfrom ,20);
												 write(connfd[retain_child] , &my_rec->countryto ,20);
												 write(connfd[retain_child] , &my_rec->ios ,20);
												 kill(my_pid[retain_child], SIGUSR1);

												read (connfd[retain_child] , &r_quest , sizeof(int) ); //diavase to request
												 my_rec->request = r_quest ;

									 }
									 else{
										 ff=0;
										 write(connfd[retain_child] , &garaze ,25); //perna tis katalliles eggrafes
										 write(connfd[retain_child] , &ff ,sizeof(int)); //perna tis katalliles eggrafes
										 printf("REQUEST REJECTED – YOU ARE NOT VACCINATED\n" );
										 my_rec->request = 1;
									 }
									 insert_simple(S,my_rec); //apothikeuse ta aitimata
									 insert_simple_country(S_country , my_rec); // apothikeuse tis xwres kai tou ious apo ta aitimata
								 }

/*-----------------------------2i sinartisi----------------------------------*/

						 	  else if (strcmp(broke, "/travelStats") == 0) {
										 char check_country[20];
										 char date1[20];
										 char date2[20];
										 char virusName[20];
										 broke = strtok(NULL,check);
										 strcpy(virusName , broke );
										 broke = strtok(NULL,check);
										 strcpy(date1 , broke );
										 broke = strtok(NULL,check);
										 strcpy(date2 , broke );
										 broke = strtok(NULL,check);
										 strcpy(check_country , broke );

										 if(check_for_empty(check_country)==1){
													 result_simple_list(S ,virusName , date1 , date2);
								 		 }
										 else 	if(check_for_empty(check_country)==0){
											 result_simple_list_country(S ,virusName  , date1 , date2 ,check_country);
										 }
									 }

 /*-----------------------------3i sinartisi----------------------------------*/
	 							else if (strcmp(broke, "/addVaccinationRecords") == 0) {
		 									char new_cou[20];
		 									int sel;
		 									int count_filaname;
		 									broke = strtok(NULL,check);
		 									strcpy(new_cou,broke);

		 									strcpy(country,"Countries/");
		 									strncat(country, &new_cou, strlen(new_cou)+1);

		 									for(num_e=0 ; num_e < lim ; num_e++ ){

		 										for(int k = 0 ; k < size_array[num_e] ; k++){
		 											if(strcmp(temp_prime[num_e][k].country , country)==0){
		 												retain_child = num_e;
		 											}
		 										}
		 									}
		 									write(connfd[retain_child] , &garaze ,25);
		 									write(connfd[retain_child] , &country ,30);
		 	 								kill(my_pid[retain_child], SIGUSR1);
																								strcpy(my_name,"NO");
																								read (connfd[retain_child] , &r_quest , sizeof(int) );
																								my_rec->request = r_quest ;

																								H=TEMP;
																								if(r_quest==1){
																								while(H->next!=NULL){
																									HELP=TEMP;

																									read (connfd[retain_child] ,  &my_name, 20 );
																									if(strcmp("NULL",my_name)==0){
																										break;
																									}
																										initiaze_ios_for(HELP ,my_name , size_bf);
																										int k=0;

																										while(HELP->next!=NULL){
																												if(strcmp(HELP->name_ios,my_name)==0){
																										// 			printf("my_name3333 is %s\n", my_name );
																													for(int i=0 ; i<size_bf ; i++){
																														read (connfd[retain_child] ,  &FUN->bloom[i], sizeof(int) );
																														if(FUN->bloom[i]!=0){
																															HELP->bloom[i]=FUN->bloom[i];
																														}
																													}
																													break;
																												}
																												HELP=HELP->next;
																											}
																											H=H->next;
																										}
																								}
																							 printf("ADDED\n" );
								 }

		 /*-----------------------------4i sinartisi----------------------------------*/


	 							 else	if (strcmp(broke, "/searchVaccinationStatus") == 0) {
			 								char id[30];
			 								char date1[20];
			 								char date2[20];
			 								char virusName[20];
			 								broke = strtok(NULL,check);
			 								strcpy(my_rec->id , broke);

			 								for(num_e=0 ; num_e < lim ; num_e++){  // pigene se ola ta paidia kai psakse
												test=4;

												write(connfd[num_e] , &garaze ,25);
												write(connfd[num_e] , &my_rec->id ,30);
												kill(my_pid[num_e], SIGUSR1);

												read (connfd[num_e] , &r_quest , sizeof(int) );
												my_rec->request = r_quest ;

												if(r_quest>0){
												for(int i =0 ; i < r_quest ; i++ ){
												read(connfd[num_e] , &my_rec->id ,30);
													read(connfd[num_e] , &my_rec->first_name ,20);
													read(connfd[num_e] , &my_rec->last_name ,20);
													read(connfd[num_e] , &my_rec->country ,20);
													read(connfd[num_e] , &my_rec->age ,20);
													read(connfd[num_e] , &my_rec->ios ,20);
													read(connfd[num_e] , &my_rec->date ,20);
													read(connfd[num_e] , &my_rec->vacine ,20);
											 //
												 if(i==0){
												 printf("%s  ", my_rec->id );
												 printf(" %s  ", my_rec->first_name );
												 printf(" %s  ", my_rec->last_name );
												 printf(" %s \n", my_rec->country );
											 }
										 }
									 }
								 }
							 }

							 if (strcmp(broke, "/exit") == 0) {
								 result_simple_list_country_log(S ,S_country, S_country->rec->ios  , log_file);

								 for(num_e=0 ; num_e <lim ;num_e++){

									 write(fd3 , &garaze ,25);
									kill(connfd[num_e],SIGUSR2);

								}
								return 0;
							 }
						 }
					 }



					 printf("geia\n" );
					 close(sockfd);
				}
				//print_hash_table(H,size_bf);
				//return 0;

			}
