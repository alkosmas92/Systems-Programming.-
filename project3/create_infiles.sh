  #!/bin/bash

  File=$1
  if [ ! -f $File ]; then
    echo "File $File no exists"
  fi

  num_file=$(($3-1));
  count=0

  if [ -e ./Countries ]; then
    echo "File exists"
    rm -r Countries
    echo "file Countries removed "
  fi

  if [ -e ./Countries ]; then
    echo "File exists"
  else
    mkdir -p ./Countries
    echo no exists
  fi

  filename=$1
  while read text; do
  # reading each line

  #Define the string value

  # Set space as the delimiter
  IFS=' '

  #Read the split words into an array based on space delimiter
  read -a strarr <<< "$text"

  #Count the total words

  # Print each value of the array by using the loop


    if [ -e ./Countries/${strarr[3]} ]; then
      ((count++))
      COUNTRY=${strarr[3]}$count
      line=$(wc -l < ./Countries/${strarr[3]}/$COUNTRY.txt)
      filenum=$count
      while [ $count -le $num_file ];
        do
          ((count++))
          COUNTRY=${strarr[3]}$count
          temp=$(wc -l < ./Countries/${strarr[3]}/$COUNTRY.txt)
          if [ $line -gt $temp ];
          then
              filenum=$count
              line=$temp
          fi
        done
        COUNTRY=${strarr[3]}$filenum
        echo ${strarr[@]} >> ./Countries/${strarr[3]}/$COUNTRY.txt

        count=0
    else
      mkdir -p ./Countries/${strarr[3]}
      while [ $count -le $num_file ];
        do
          ((count++))
          COUNTRY=${strarr[3]}$count
          if [ $count -eq 1 ]; then
            touch ./Countries/${strarr[3]}/$COUNTRY.txt
            echo ${strarr[@]} > ./Countries/${strarr[3]}/$COUNTRY.txt

          else
            touch ./Countries/${strarr[3]}/$COUNTRY.txt
          fi
        done

    fi
    count=0



done < $filename
