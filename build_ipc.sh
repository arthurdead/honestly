ipc_file=$(pwd)/.build_ipc

touch $ipc_file

clear

stoploop=false
function handle_sigint
{
	stoploop=true
}

trap handle_sigint SIGINT

while [[ $stoploop == false ]]; do
	line=$(tail -n 1 $ipc_file)
	if [[ -z $line ]]; then
		sleep 1s
		continue
	fi
	sed -i '$ d' $ipc_file
	clear
	echo $(date +'%H:%M:%S')
	cmd=$(cut -d' ' -f1 <<< $line)
	args=$(cut -d' ' -f2- <<< $line)
	if [[ $cmd == $args ]]; then
		args=''
	fi
	if [[ $cmd == 'build' ]]; then
		./build.sh
	elif [[ $cmd == 'build_debug' ]]; then
		./build.sh -DVERBOSE_BUILD -DCONFIGURATION=debug
	elif [[ $cmd == 'build_fast' ]]; then
		./build.sh -DFAST_BUILD
	elif [[ $cmd == 'build_custom' ]]; then
		./build.sh $args
	else
		echo 'unknown command:' $cmd >&2
	fi
	sleep 1s
done