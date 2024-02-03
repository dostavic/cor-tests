for filename in ./*.dat; do
	if [[ $filename =~ ([0-9]*)_Rig_bins.dat ]]; then 
		#printf "$filename"
		#myvar=$(awk '{ print $2 " " $3 " " $4 " " $1}' $filename) #change order of collumns so the first two are energy and intensity
		myvar=$(awk '{ print $1 " " $2 " " $3 }' $filename) #remove rigidity because it is same in all files
		#echo ${BASH_REMATCH[1]}.dat
		rm $filename
		echo "$myvar" > ${BASH_REMATCH[1]}.dat
	fi
	#awk '{ print $2 " " $3 " " $4 " " $1}' 1409.dat
done 

#rename 's/_Rig_bins//' *

