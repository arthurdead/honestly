arch=$(uname -m)

if [[ "$arch" == "x86_64" ]]; then
	echo -n 'x86-64'
else
	echo -n $arch
fi