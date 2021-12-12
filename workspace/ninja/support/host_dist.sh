if [[ -f /etc/lsb-release ]]; then
	while IFS="=" read key value
	do
		if [[ $key == 'DISTRIB_DESCRIPTION' ]]; then
			echo -n ${value:1:-1}
			exit 0
		fi
	done < /etc/lsb-release
fi

echo -n 'Unknown'
exit 1