if [[ -z $1 ]]; then
	echo -n ''
	exit
fi

for str in $@; do
	rev=$str' '$rev
done
echo -n $rev