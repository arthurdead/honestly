if [[ -z $1 ]]; then
	echo 'missing source directory' >&2
	exit 1
fi

this_dir=$(cd $(dirname ${BASH_SOURCE[0]}) &> /dev/null && pwd)

if [[ $1 == '.' ]]; then
	input_dir=$this_dir
else
	input_dir=$(readlink -ne $1)
fi

if [[ -z $2 ]]; then
	output_dir=$input_dir
else
	output_dir=$(readlink -nm $2)
	mkdir -p $output_dir
fi

support_dir=$this_dir'/support'

target_wd=$(pwd)

glob=$input_dir'/'*'.ninja.m4'
for m4file in $glob; do
	if [[ $m4file == "${glob}" ]]; then
		continue
	fi

	ninja_file=$output_dir'/'$(basename ${m4file%.*})

	cd $this_dir
	m4 -EE -P -I$support_dir -I$input_dir -D__NINJA_FILE=$ninja_file -D__SUPPORT_DIR=$support_dir -D__OUTPUT_DIR=$output_dir ${@:3} $m4file > $ninja_file
	cd $target_wd
	code=$?
	if [[ $code != 0 ]]; then
		echo $m4file' failed to process' >&2
		rm -f $ninja_file
		exit $code
	fi
	sed -i '/^[[:space:]]*$/d' $ninja_file
	sed -Ei 's/ {2,}/ /g' $ninja_file
	#keep this in-sync with support/ninja_file.m4::__HACK_SPACE
	sed -i 's/£/  /g' $ninja_file
done
