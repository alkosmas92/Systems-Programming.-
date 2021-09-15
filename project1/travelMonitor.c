int lim=atoi(argv[3]); //tosa einai ta paidia

  for (num_e=0;num_e<lim; num_e++)								//dimourgise tosa paidia osa to lim me ena patera
    if ( (pid = fork()) <= 0 )
       break;

/*-----------------------------------Child--------------------------------------------------------*/


     if(pid==0){
       sprintf(choice, "%d", num_e % lim);							//perna to number ws char
        if((execl("./prime1_1","prime1_1",start_1[num_e] , end_1[num_e] , choice , final_file[num_e],NULL)) == -1){
                          perror("exec");
              }
     }


/*-----------------------------------Parent--------------------------------------------------------*/
    else{
