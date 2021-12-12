if [[ -z $1 ]]; then
	echo 'get_module_var.sh: missing filename' 2>&1
	echo -n ''
	exit 1
fi

if [[ -z $2 ]]; then
	echo 'get_module_var.sh: missing variable' 2>&1
	echo -n ''
	exit 1
fi

file=$(readlink -nm $1)

source $file

if [[ $2 == 'name' ]]; then
	echo -n $name
elif [[ $2 == 'headers' ]]; then
	if [[ -n $headers ]]; then
		for h in $headers; do
			if [[ $h == '../config.h' ]]; then
				h='zsh_config.h'
			fi
			echo -n $h','
		done
	else
		echo -n ''
	fi
else
	echo 'get_module_var.sh: unknown variable ' $2 2>&1
	echo -n ''
	exit 1
fi