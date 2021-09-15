#!bin/bash

L=$(($3));
check=$(($4));

echo $L

RANGE=10000
FLOOR=1
R=120
LESS=2
myArray+=( "YES" "NO" )
D_START=0
D_END=31
M_START=0
M_END=13
Y_START=2000
Y_END=2021



  counter=1
  while [ $counter -le $L ]
  do
    dis=$(shuf -n 1 $1);
    cou=$(shuf -n 1 $2);
    D=" "
    # echo $A  #virus
    # echo $B  #countries
  #--------date-----------------/
  date1=0   #initialize
  while [ "$date1" -le $D_START ]
  do
    date1=$RANDOM
    let "date1 %= $D_END"  # Scales $date down within $D_END.
  done

  #--------month-----------------/

  date2=0   #initialize
  while [ "$date2" -le $M_START ]
  do
  date2=$RANDOM
  let "date2 %= $M_END"  # Scales $date down within $D_END.
  done


  #--------year-----------------/

  date3=0   #initialize
  while [ "$date3" -le $Y_START ]
  do
  date3=$RANDOM
  let "date3 %= $Y_END"  # Scales $date down within $D_END.
  done


  #--------SUM-DATE-----------------/
  E="-"
  DATE=$date1$E$date2$E$date3
  # echo $DATE


  #--------YES/NO-----------------/
  answer=$RANDOM
  let "answer %= $LESS"
  #           ^^


  #--------citizenid-----------------/
  if [ $check -eq 0 ]
  then
  id=$RANDOM
  let "id %= $RANGE" #citizenid
  else
    id=$RANDOM
    let "id %= $RANGE" #citizenid
    while  [[ "${my_id[@]}" =~ $id ]]; do # check if the user input is valid
      id=$RANDOM
      let "id %= $RANGE" #citizenid

    done
  fi


  #--------age-----------------/

  number=0   #initialize
  while [ "$number" -le $FLOOR ]
  do
    number=$RANDOM
    let "number %= $R"  #age.
  done

  #--------name-----------------/

  symbols='abcdefghijklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVYXWZ'  # name '
  count_symbols=${#symbols}
  (( length = RANDOM % 13 + 3 ))
  name=""
  for i in $(seq 1 $length) ; do
      name+=${symbols:RANDOM % count_symbols:1}
  done

  #--------last_name-----------------/

  symbols='abcdefghijklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUVYXWZ'  # last_name '
  count_symbols=${#symbols}
  (( length = RANDOM % 13 + 3 ))
  last=""
  for i in $(seq 1 $length) ; do
      last+=${symbols:RANDOM % count_symbols:1}
  done

  #-----------check-for-answer---------------/
  if [ $answer -eq 0 ]
  then
  C=$id$D$name$D$last$D$cou$D$number$D$dis$D${myArray[answer]}$D$DATE
  else
  C=$id$D$name$D$last$D$cou$D$number$D$dis$D${myArray[answer]}
  fi

  my_id+=($id)



  echo "$C" >> touch.txt
  command >> touch.txt


  ((counter++))
done
