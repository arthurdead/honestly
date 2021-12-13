if [[ -f /etc/lsb-release ]]; then
	while IFS="=" read key value
	do
		if [[ $key == 'DISTRIB_DESCRIPTION' ]]; then
			echo -n ${value:1:-1}
			exit 0
		fi
	done < /etc/lsb-release
fi

echo 'host_dist.sh: unknown' >&2
echo -n 'Unknown'
exit 1