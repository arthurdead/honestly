if [[ -z $1 ]]; then
	echo 'remove_whitespace.sh missing filename' >&2
	exit 1
fi

file=$(readlink -nm $1)

sed -i '/^[[:space:]]*$/d' $file
sed -Ei 's/ {2,}/ /g' $file