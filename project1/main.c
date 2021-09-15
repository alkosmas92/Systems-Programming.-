#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "bloom_filter.h"
#include "skip_list.h"








int main(int argc, char **argv) {
	// Open a file pointer named "log.txt" for writing (w+)
	// If you google c file i/o you'll find all the specifiers for
	// writing, reading, writing and reading, etc. I just chose
	// only writing here as an example

	FILE *f;
f = fopen("x.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
if (f == NULL) { /* Something is wrong   */}
fprintf(f, "I'm logging something ...\n");
fclose(f);
f = fopen("x.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
if (f == NULL) { /* Something is wrong   */}
fprintf(f, "I'm logging something ...\n");
fclose(f);

	// Slist * S=simple_list_create();
	// Slist * L=simple_list_create();
	// record * rec=malloc(sizeof(record));
	// 	 // char all2[20]="";
	//
	// 	 //char all1[20]="27-06-1000";
	// 	 char all1[20]="31";
	// 	 char all4[20]="27-06-2029";
	// 	 char all2[20]="MERS-COV";
	// 	 char all3[20]="67-9-2020";
	// 		strcpy(rec->id , all1);
	// 		strcpy(rec->ios , all2);
	// 		insert_simple_list(S,rec);
	// 	 // char all2[20]="";
	//
	// 	 //char all1[20]="27-06-1000";
	// 	 char a1[20]="31";
	// 	 char a4[20]="27-06-2029";
	// 	 char a2[20]="COVID-2029";
	// 	 char a3[20]="67-9-2020";
	// 		strcpy(rec->id , a1);
	// 		strcpy(rec->ios , a2);
	// 		insert_simple_list(S,rec);
	// 	 // char all2[20]="";
	//
	// 	 //char all1[20]="27-06-1000";
	// 	 char e1[20]="31";
	// 	 char e4[20]="27-06-2029";
	// 	 char e2[20]="EDV";
	// 	 char e3[20]="67-9-2020";
	// 		strcpy(rec->id , e1);
	// 		strcpy(rec->ios , e2);
	// 		insert_simple_list(S,rec);
	// 	 // char all2[20]="";
	//
	// 	 //char all1[20]="27-06-1000";
	// 	 char as1[20]="51";
	// 	 char as4[20]="27-06-2029";
	// 	 char as2[20]="MERS-COV";
	// 	 char as3[20]="67-9-2020";
	// 	 strcpy(rec->id , as1);
	// 	 strcpy(rec->ios , as2);
	// 	 insert_simple_list(S,rec);
	//
	//
	// 	 char gt1[20]="51";
	// 	 char gt4[20]="27-06-2029";
	// 	 char gt2[20]="MERS-COV";
	// 	 char gt3[20]="67-9-2020";
	// 	 strcpy(rec->id , gt1);
	// 	 strcpy(rec->ios , gt2);
	// 	 insert_simple_list(S,rec);
	//
	//
	//
	// 	 char fr1[20]="61";
	// 	 char fr4[20]="27-06-2029";
	// 	 char fr2[20]="MERS-COV";
	// 	 char fr3[20]="67-9-2020";
	// 	 strcpy(rec->id , fr1);
	// 	 strcpy(rec->ios , fr2);
	// 	 insert_simple_list(S,rec);
	// 	 // strcpy(rec->ios , all2);
	// 	 // strcpy(rec->date , all4);
	// 	 //
	// 	 //
	//
	// 	 print_simple_list(S);
	//
	// 	 // if(S->next==NULL){
	// 		//  printf("eimai nsi \n");
	// 	 // }
	// 	 //
	// 	 //
	// 	 //
	// 	 // printf("OLEEEE \n");
	//
	// int size_bf=(atoi(argv[4])*8)/32;
	// ios_hash *H=create_hash_ios(size_bf);
	//
	//
	// 		HList *HA=list_node_create();
	// 		CList *C=list_country_node_create();
	//
 	// read_file(H , argv, size_bf , HA ,C );
	//
	// printMenu();
	//
	// char *UserCommand = NULL;
	// size_t combytes = 200;
	// UserCommand = (char *) malloc(combytes);
	// char * line = (char *) malloc(combytes);
	// char *broke;
	//
	// while(getline(&UserCommand, &combytes, stdin) != EOF) {
	// 		strcpy(line, UserCommand);
	// 		broke = strtok(UserCommand, " \n");    // Tokenize input
	// 		char check[]=" ";
	//
	// 	if (broke != NULL) {
	// 			if (strcmp(broke, "VB") == 0) {
	// 				char citizenID[20];
	// 				char virusName[20];
	//
	//
	// 				broke = strtok(NULL,check);
	// 				strcpy(citizenID,broke);
	// 				broke = strtok(NULL,check);
	// 				strcpy(virusName,broke);
	// 				vacine_check(H , citizenID ,virusName , size_bf);
	//
	// 		}
	//
	// 		else if(strcmp(broke, "VS") == 0){
	// 						char citizenID[20];
	// 						char virusName[20];
	//
	//
	// 						broke = strtok(NULL,check);
	// 						strcpy(citizenID,broke);
	// 						broke = strtok(NULL,check);
	// 						put_the_broke(broke,virusName);
	//
	// 						vaccineStatus(HA ,citizenID ,virusName  );
	//
	// 		}
	// 		else if(strcmp(broke, "PS") == 0){
	// 						char country[20];
	// 						char virusName[20];
	// 						char date1[20];
	// 						char date2[20];
	//
	//
	// 						broke = strtok(NULL,check);
	// 						strcpy(virusName,broke);
	// 						broke = strtok(NULL,check);
	// 						put_the_broke(broke , date1);
	// 						broke = strtok(NULL,check);
	// 						put_the_broke(broke , date2);
	//
	// 						broke = strtok(NULL,check); //country
	// 						put_the_broke(broke,country);
	// 						populationStatus(C , country , virusName , date1 , date2 );
	//
	// 		}
	// 		else if(strcmp(broke, "PSA") == 0){
	// 			char country[20];
	// 			char virusName[20];
	// 			char date1[20];
	// 			char date2[20];
	//
	// 			broke = strtok(NULL,check);
	// 			strcpy(virusName,broke);
	// 			broke = strtok(NULL,check);
	// 			put_the_broke(broke , date1);
	// 			broke = strtok(NULL,check);
	// 			put_the_broke(broke , date2);
	//
	// 			broke = strtok(NULL,check); //country
	// 			put_the_broke(broke,country);
	// 			popStatusByAge(C , country , virusName , date1 , date2 );
	// 		}
	// 		else if(strcmp(broke, "ICR") == 0){
	//
	// 			int rec_no=0;
	// 			record * my_rec=malloc(sizeof(record));
	//
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->id,broke);
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->first_name,broke);
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->last_name,broke);
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->country,broke);
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->age,broke);
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->ios,broke);
	// 			broke = strtok(NULL,check);
	// 			strcpy( my_rec->vacine,broke);
	//
	// 			printf("id%s\n",my_rec->id );
	// 			printf("%s\n",my_rec->first_name );
	// 			printf("%s\n",my_rec->last_name );
	// 			printf("%s\n",my_rec->country );
	// 			printf("%s\n",my_rec->age );
	// 			printf("%s\n",my_rec->ios );
	// 			printf("%s\n",my_rec->vacine );
	//
	// 			if(strcmp(my_rec->vacine,"YES")==0){
	// 				date(my_rec->date);
	// 				date(my_rec->extraDate);
	// 				printf("date is %s\n",my_rec->date );
	// 			}
	// 			else{
	// 				broke=strtok(NULL,check);
	// 					if(broke!=NULL){
	// 						printf("ERROR RECORD HAVE PROBLEM NO INSERT\n" );
	// 						rec_no=1;
	// 					}
	// 			}
	//
	// 		if(rec_no!=1){
	// 				if(vaccineStatus_search(HA , my_rec->id , my_rec->ios)){
	// 					// printf("ERROR : CITIZEN %s ALREADY " ,my_rec->id );
	// 					// vaccineStatus(HA , citizenID , virusName);
	// 				}
	// 				else{
	// 						insert_hash_ios(H , size_bf , my_rec);
	// 						initiaze_table_vacine(HA , my_rec );
	// 						initiaze_county_table_vacine(C ,my_rec);
	// 							printf("inserttt\n" );
	// 				}
	// 		}
	//
	//
	// 		}
	// 		else if(strcmp(broke, "VN") == 0){
	// 				 broke = strtok(NULL,check);
	// 				 char virusName[20];
	// 				 strcpy(virusName  , broke);
	//
	// 				 	vaccineStatus_no_listprint(HA  , virusName);
	// 				// char* Year[20];
	// 				// strcpy(Year,broke);
	// 				// min_gpa( Year , Listhead );
	//
	// 		}
	// 		else if(strcmp(broke, "LNP") == 0){
	// 					//count(  Listhead );
	//
	// 		}
	// 		else if(strcmp(broke, "exit") == 0){
	// 			//	distractor_ios_table(H,size_bf);
	// 			//	distractor_Hlist(H);
	// 			//	distractor_Clist(C);
	// 				printf("exit without free \n" );
	// 				return;
	// 		}
	// 	}
	// }


}
