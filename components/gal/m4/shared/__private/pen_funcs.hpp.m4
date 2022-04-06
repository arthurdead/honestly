m4_include(helpers.m4)`'BEGIN_NO_OUTPUT

m4_include(api_bridge.m4)

API_BRIDGE_FUNCS(`
	F2_V(point, std::initializer_list<struct point>, values, bool, relative)
	F2_V(line, std::initializer_list<struct point>, values, bool, relative)
	F2_V(rectangle, std::initializer_list<struct rectangle>, values, bool, filled)
	F1_V(segment, std::initializer_list<struct segment>, values)
	F2_V(arc, std::initializer_list<struct arc>, values, bool, filled)
	F3_V(fill, std::initializer_list<struct point>, values, shape_type, type, bool, relative)
')

END_NO_OUTPUT
