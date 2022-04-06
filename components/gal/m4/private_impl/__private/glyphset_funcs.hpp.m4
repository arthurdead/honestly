m4_include(helpers.m4)`'BEGIN_NO_OUTPUT

m4_define(API_BRIDGE_CLASS, glyph_set)
m4_define(API_BRIDGE_ACCESS, impl.ref<__font::glyphs_impl>().)

m4_include(shared/__private/glyphset_funcs.hpp.m4)

END_NO_OUTPUT
