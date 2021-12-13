if [[ -z $1 ]]; then
	echo 'hash.sh: missing argument' >&2
	echo -n '0'
	exit 1
fi

echo -n $(cksum <<< $1 | cut -f 1 -d ' ')