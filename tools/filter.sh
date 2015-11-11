sed s/\ \ //g < item_info.txt > itemsf.txt
sed s/\|\ /\|/g < itemsf.txt > itemsf1.txt
sed s/\ \|/\|/g < itemsf1.txt > itemsf2.txt
sed s/\^\ //g < itemsf2.txt > itemsf3.txt
cat itemsf3.txt  | awk -F \| {' print "N:", $4, "\nI:", $1, "\nC: 0\n" '} > item0.lst
rm itemsf*.txt
