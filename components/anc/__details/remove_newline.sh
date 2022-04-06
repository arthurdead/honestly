if [[ -z $1 ]]; then
	echo 'remove_newline.sh: missing arg'  >&2
	echo -n ''
	exit 1
fi

echo -n $1 | tr -d '\n'