echo "Enter the string"
read str
len=`expr $str | wc -c`
len=`expr $len - 1`
i=1
j=`expr $len / 2`
while [ $i -le $j ]
do
k=`expr $str | cut -c $i`
l=`expr $str | cut -c $len`
if test $k != $l
then
echo "String is not palindrome"
exit
fi
i=`expr $i + 1`
len=`expr $len - 1`
done
echo "String is palindrome"
