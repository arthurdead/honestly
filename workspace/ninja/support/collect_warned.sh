if [[ -z $__COLLECT_WARNINGS_OUTPUT ]]; then
	output=0
	opts=$(getopt -au ':o:' $(echo $@))
	while read -d' ' arg; do
		if [[ $output == 1 ]]; then
			output=$arg
		elif [[ $arg == '-o' ]]; then
			output=1
		elif [[ $arg == '--' ]]; then
			if [[ $output == 1 ]]; then
				output=0
			fi
			break
		fi
	done <<< $opts

	if [[ $output == 0 || $output == 1 ]]; then
		echo 'collect_warned.sh: failed to find output arg' >&2
		exit 1
	fi
else
	output=$__COLLECT_WARNINGS_OUTPUT
fi

output=$(readlink -nm $output)

if [[ -z $__COLLECT_WARNINGS_FILE ]]; then
	echo 'collect_warned.sh: file not set' >&2
	exit 1
fi

__COLLECT_WARNINGS_FILE=$(readlink -nm $__COLLECT_WARNINGS_FILE)

tmplog=$(mktemp)
if [[ $? == 1 ]]; then
	echo 'collect_warned.sh: mktemp failed' >&2
	exit 1
fi

$@ 2>&1 | tee $tmplog
code=${PIPESTATUS[0]}

if [[ $code != 0 || -s $tmplog ]]; then
	mkdir -p $(dirname $__COLLECT_WARNINGS_FILE)
	if [[ $? == 1 ]]; then
		echo 'collect_warned.sh: failed to create file directory' >&2
		rm $tmplog
		exit 1
	fi
	echo $output >> $__COLLECT_WARNINGS_FILE
	if [[ $? == 1 ]]; then
		echo 'collect_warned.sh: failed to append to file' >&2
		rm $tmplog
		exit 1
	fi
fi

rm $tmplog
exit $code