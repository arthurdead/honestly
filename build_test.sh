clear

args=$args' '-DTOOLSET=llvm
#args=$args' '-DTOOLSET=gnu
args=$args' '-DLD=lld
#args=$args' '-DLD=ld
#args=$args' '-DLD=wasm-lld
args=$args' '-DLIBRT=compiler-rt
#args=$args' '-DLIBRT=libgcc
args=$args' '-DLIBUNWIND=libgcc
#args=$args' '-DLIBUNWIND=none
args=$args' '-DLIBC=glibc
#args=$args' '-DLIBC=musl
#args=$args' '-DLIBC=crt
args=$args' '-DLIBCPP=libstdc++
#args=$args' '-DLIBCPP=libc++
#args=$args' '-DLIBCPP_ABI=libc++abi
args=$args' '-DLIBCPP_ABI=libsupc++
args=$args' '-DARCHITECTURE=x86-64
#args=$args' '-DARCHITECTURE=wasm-32
args=$args' '-DCONFIGURATION=debug
#args=$args' '-DEMSCRIPTEN
#args=$args' '-DWASI
#args=$args' '-DZAPCC
#args=$args' '-DMINGW
#args=$args' '-DWINE
#args=$args' '-DLSB
#args=$args' '-DVERBOSE_BUILD
args=$args' '-DFAST_BUILD
args=$args' '-DCCACHE=ccache
#args=$args' '-DCOMPDB_COMPATIBLE
args=$args' '-DCOLLECT_WARNED
args=$args' '-DINFO_COMMENT

./build.sh $args