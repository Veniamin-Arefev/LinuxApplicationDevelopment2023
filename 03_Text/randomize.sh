#!/bin/bash
if [ $# -ne 1 ]; then
  echo "Must supply only one argument"
  exit 1
fi

LINE_COUNT=0
TEXT=""
while IFS="" read -r LINE; do
  for (( SYM_INDEX=0; SYM_INDEX<${#LINE}; SYM_INDEX++ )); do
    if [ "${LINE:$SYM_INDEX:1}" != " " ]; then
      TEXT="${TEXT}$LINE_COUNT $SYM_INDEX ${LINE:$SYM_INDEX:1} \n"
    fi
  done
  LINE_COUNT=$((LINE_COUNT+1))
done

TEXT="$(printf "$TEXT" | shuf)\n"
tput clear
printf "$TEXT" | while read -r COL INDEX CHAR; do
  tput cup "$COL" "$INDEX"
  echo "$CHAR"
  sleep $1
done

tput cup $((LINE_COUNT))
