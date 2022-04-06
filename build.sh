reflex_root=/home/arthurdead/Downloads/RE-flex

export PATH=$PATH:$reflex_root'/bin'
export LIBRARY_PATH=$LIBRARY_PATH:$reflex_root'/lib'
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$reflex_root'/lib'
export CPATH=$CPATH:$reflex_root'/include'

export __TMP_HACK_REFLEX_LIB_DIR=$reflex_root'/lib'
export __TMP_HACK_REFLEX_INC_DIR=$reflex_root'/include'

./components/anc/configure.sh $(pwd)'/workspace/anc' $(pwd)'/artifacts' $@
code=$?
if [[ $code != 0 ]]; then
	exit $code
fi

./components/anc/remove_warned.sh $(pwd)'/artifacts'
samu -f$(pwd)'/artifacts/build.ninja' -j6
exit $?
