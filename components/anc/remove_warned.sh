if [[ -z $1 ]]; then
	echo 'missing dir' >&2
	exit 1
fi

while read -e warned; do
	while read -e file; do
		if [[ -z $file ]]; then
			continue
		fi
		rm -f $file
	done <<< $(cat $warned)
	if [[ -z $warned ]]; then
		continue
	fi
	rm $warned
done <<< $(find $1 -name 'warned.txt')