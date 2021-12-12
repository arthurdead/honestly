if [[ -z $1 ]]; then
	echo 'c_version.sh: missing compiler' 2>&1
	echo -n '0'
	exit 1
fi

if [[ $1 == 'gcc' ]]; then
	gcc -dumpfullversion | tr -d '\n'
elif [[ $1 == 'clang' ]]; then
	clang -dumpversion | tr -d '\n'
elif [[ $1 == 'zapcc' ]]; then
	ver=$(zapcc --version | grep -Eo 'zapcc clang version [1-9]+\.[0-9]+\.[0-9]+')
	echo -n ${ver:20}
elif [[ $1 == 'winegcc' ]]; then
	winegcc -dumpfullversion | tr -d '\n'
elif [[ $1 == 'emscripten-clang' ]]; then
	/opt/emscripten-llvm/bin/clang -dumpversion | tr -d '\n'
elif [[ $1 == 'mingw-64' ]]; then
	x86_64-w64-mingw32-gcc -dumpversion | tr -d '\n'
else
	echo 'c_version.sh: unknown compiler ' $2 2>&1
	echo -n '0'
	exit 1
fi