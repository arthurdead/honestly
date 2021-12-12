m4_include(helpers.m4)`'BEGIN_NO_OUTPUT

m4_define(API_BRIDGE_CLASS, pen)
m4_define(API_BRIDGE_ACCESS, impl.ref<__pen::impl>().)

m4_include(shared/__private/pen_funcs.hpp.m4)

END_NO_OUTPUT
