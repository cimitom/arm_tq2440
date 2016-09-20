#!/bin/sh

#2.2
a="hello world"
b=12

echo $a
echo $b

#2.3
echo "number of vars:" $#
echo "value of vars:"  $*
echo "name of script:" $0
echo "var1 is: "$1
echo "var2 is: "$2

#2.4
var1=10
var2=20
var3=`expr $var2 / $var1`
var4=`expr $var2 + $var1`
echo "var3 is: "$var3
echo "var4 is:" $var4

#2.5
var=10
if [ $var -gt 5 ]
then
    echo "var greater than 5"
fi

#2.6
list="Sun Mon Tus Wen Thu Fri Sat"
for day in $list
do
    echo $day
done

#2.7
var=5
while [ $var -gt 0 ]
do
    echo $var
    var=`expr $var - 1`
done
