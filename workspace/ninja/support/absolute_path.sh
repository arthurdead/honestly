if [[ -z $3 ]]; then
	is_dir=false
else
	if [[ $3 == 'true' ]]; then
		is_dir=true
	else
		is_dir=false
	fi
fi

if [[ -z $1 ]]; then
	echo 'absolute_path.sh missing filename' >&2
	if [[ $is_dir == 'true' ]]; then
		echo -n $(mktemp -d)
	else
		echo -n $(mktemp)
	fi
	exit 1
fi

if [[ -z $2 ]]; then
	mode=m
else
	mode=$2
fi

readlink -n$mode $(echo -n $1 | tr -d '\n')