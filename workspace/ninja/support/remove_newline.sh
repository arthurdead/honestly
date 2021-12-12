if [[ -z $1 ]]; then
	echo -n ''
	exit
fi

echo -n $1 | tr -d '\n'