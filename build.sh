reflex_root=/home/arthurdead/Downloads/RE-flex

export PATH=$PATH:$reflex_root'/bin'
export LIBRARY_PATH=$LIBRARY_PATH:$reflex_root'/lib'
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$reflex_root'/lib'
export CPATH=$CPATH:$reflex_root'/include'

export __TMP_HACK_REFLEX_LIB_DIR=$reflex_root'/lib'
export __TMP_HACK_REFLEX_INC_DIR=$reflex_root'/include'

./workspace/ninja/configure.sh '.' $(pwd)'/artifacts' $@
code=$?
if [[ $code != 0 ]]; then
	exit $code
fi

./workspace/ninja/remove_warned.sh $(pwd)'/artifacts'
#ninja -f $(pwd)'/artifacts/build.ninja' -t compdb > $(pwd)'/artifacts/compile_commands.json'
#samu -f $(pwd)'/artifacts/build.ninja' -j 6
exit $?