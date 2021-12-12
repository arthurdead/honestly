clear

export __GLX_VENDOR_LIBRARY_NAME=nvidia
export __NV_PRIME_RENDER_OFFLOAD=1
export __NV_PRIME_RENDER_OFFLOAD_PROVIDER=NVIDIA-0
export __VK_LAYER_NV_optimus=NVIDIA_only
#export DISABLE_LAYER_NV_OPTIMUS_1=1
#export NODEVICE_SELECT=1
export DRI_PRIME=1

unset MESA_VK_DEVICE_SELECT
unset DISABLE_LAYER_NV_OPTIMUS_1
unset NODEVICE_SELECT
unset MESA_VK_VERSION_OVERRIDE

unset VK_LAYER_DISABLES

unset mesa_no_error
unset MESA_NO_ERROR
export MESA_DEBUG='incomplete_tex;incomplete_fbo;context'
export LIBGL_DEBUG=verbose
export VK_LOADER_DEBUG='error,warn'
export VK_LOADER_DISABLE_INST_EXT_FILTER=1

gdb -ex=run --args launcher.elf