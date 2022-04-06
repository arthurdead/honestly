m4_include(helpers.m4)`'BEGIN_NO_OUTPUT

m4_include(api_bridge.m4)

API_BRIDGE_FUNCS(`
	F3_V(render, const gal::window &, win, std::size_t, x, std::size_t, y)
')

END_NO_OUTPUT
