if [[ -z $1 ]]; then
	echo 'c_version.sh: missing compiler' >&2
	echo -n '0'
	exit 1
fi

if [[ $1 == 'gcc' ]]; then
	gcc -dumpfullversion | tr -d '\n'
elif [[ $1 == 'clang' ]]; then
	clang -dumpversion | tr -d '\n'
elif [[ $1 == 'zapcc' ]]; then
	zapcc --version | tr -d '\n' | sed -E 's/zapcc clang version ([1-9]+\.[0-9]+\.[0-9]+).*/\1/'
elif [[ $1 == 'winegcc' ]]; then
	winegcc -dumpfullversion | tr -d '\n'
elif [[ $1 == 'emscripten-clang' ]]; then
	$EMSCRIPTEN_LLVM_ROOT/bin/clang -dumpversion | tr -d '\n'
elif [[ $1 == 'mingw-64' ]]; then
	x86_64-w64-mingw32-gcc -dumpfullversion | tr -d '\n'
else
	echo 'c_version.sh: unknown compiler ' $2 >&2
	echo -n '0'
	exit 1
fi
