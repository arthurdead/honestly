m4_include(helpers.m4)`'BEGIN_NO_OUTPUT

m4_ifdef(`API_BRIDGE_TYPE', `', `
	ERROR(please define API_BRIDGE_TYPE to the appropriate type)
')

m4_ifdef(`__API_BRIDGE_PROJECT', `', `
	m4_ifdef(`PROJECT', `
		m4_define(`__API_BRIDGE_PROJECT', PROJECT)
	', `
		ERROR(missing project)
	')
')

m4_define(`__API_BRIDGE_PROJECT_LOWER', __API_BRIDGE_PROJECT)
m4_define(`__API_BRIDGE_PROJECT_UPPER', UPPERCASE(__API_BRIDGE_PROJECT))

m4_define(__API_BRIDGE_HANDLE_BEGIN, `
	m4_ifelse(
	$1, PUBLIC, `
		m4_define(`__API_BRIDGE_FUNC_API', __API_BRIDGE_PROJECT_UPPER`'_SHARED_API)
		m4_define(`__API_BRIDGE_FUNC_CALL', __API_BRIDGE_PROJECT_UPPER`'_SHARED_API_CALL)
		m4_define(`__API_BRIDGE_FUNC_END', ;)
	',
	$1, INTERFACE, `
		m4_define(`__API_BRIDGE_FUNC_API', virtual)
		m4_define(`__API_BRIDGE_FUNC_END', = 0;)
	',
	$1, DECLARATION, `
		m4_define(`__API_BRIDGE_FUNC_END', override final;)
	',
	$1, IMPLEMENTATION, `
		m4_ifdef(`API_BRIDGE_CLASS', `
			m4_define(`__API_BRIDGE_CLASS', API_BRIDGE_CLASS::)
		', `
			m4_define(`__API_BRIDGE_CLASS', `')
		')
		m4_define(`__API_BRIDGE_FUNC_DO_BODY', `')
	')
END_NO_OUTPUT')

m4_define(__API_BRIDGE_HANDLE_END, `
	m4_undefine(`__API_BRIDGE_FUNC_API')
	m4_undefine(`__API_BRIDGE_FUNC_CALL')
	m4_undefine(`__API_BRIDGE_FUNC_END')
	m4_undefine(`__API_BRIDGE_CLASS')
	m4_undefine(`__API_BRIDGE_FUNC_DO_BODY')
BEGIN_NO_OUTPUT')

m4_define(`__API_BRIDGE_FUNC_BODY_V', `{ m4_defn(`API_BRIDGE_ACCESS')`'$1(m4_shift($@)); }')
m4_define(`__API_BRIDGE_FUNC_BODY', `{ return m4_defn(`API_BRIDGE_ACCESS')`'$1(m4_shift($@)); }')

m4_define(`F3_V', `
m4_defn(`__API_BRIDGE_FUNC_API') void m4_defn(`__API_BRIDGE_FUNC_CALL') m4_defn(`__API_BRIDGE_CLASS')$1($2 $3, $4 $5, $6 $7) noexcept m4_defn(`__API_BRIDGE_FUNC_END')
	m4_ifdef(`__API_BRIDGE_FUNC_DO_BODY', `
__API_BRIDGE_FUNC_BODY_V($1, $3, $5, $7)
	')
')

m4_define(`F2_V', `
m4_defn(`__API_BRIDGE_FUNC_API') void m4_defn(`__API_BRIDGE_FUNC_CALL') m4_defn(`__API_BRIDGE_CLASS')$1($2 $3, $4 $5) noexcept m4_defn(`__API_BRIDGE_FUNC_END')
	m4_ifdef(`__API_BRIDGE_FUNC_DO_BODY', `
__API_BRIDGE_FUNC_BODY_V($1, $3, $5)
	')
')

m4_define(`F1_V', `
m4_defn(`__API_BRIDGE_FUNC_API') void m4_defn(`__API_BRIDGE_FUNC_CALL') m4_defn(`__API_BRIDGE_CLASS')$1($2 $3) noexcept m4_defn(`__API_BRIDGE_FUNC_END')
	m4_ifdef(`__API_BRIDGE_FUNC_DO_BODY', `
__API_BRIDGE_FUNC_BODY_V($1, $3)
	')
')

m4_ifelse(API_BRIDGE_TYPE, PRIVATE, `
	m4_define(API_BRIDGE_FUNCS, `BEGIN_NO_OUTPUT
		__API_BRIDGE_HANDLE_BEGIN(DECLARATION)
`#'ifdef __API_BRIDGE_DECLARATION
`#'define `__API_BRIDGE_FUNC_API' m4_defn(`__API_BRIDGE_FUNC_API')
`#'define `__API_BRIDGE_FUNC_CALL' m4_defn(`__API_BRIDGE_FUNC_CALL')
`#'define `__API_BRIDGE_FUNC_END' m4_defn(`__API_BRIDGE_FUNC_END')
`#'define `__API_BRIDGE_CLASS' m4_defn(`__API_BRIDGE_CLASS')
		__API_BRIDGE_HANDLE_END

		__API_BRIDGE_HANDLE_BEGIN(INTERFACE)
`#'elif defined __API_BRIDGE_INTERFACE
`#'define `__API_BRIDGE_FUNC_API' m4_defn(`__API_BRIDGE_FUNC_API')
`#'define `__API_BRIDGE_FUNC_CALL' m4_defn(`__API_BRIDGE_FUNC_CALL')
`#'define `__API_BRIDGE_FUNC_END' m4_defn(`__API_BRIDGE_FUNC_END')
`#'define `__API_BRIDGE_CLASS' m4_defn(`__API_BRIDGE_CLASS')
		__API_BRIDGE_HANDLE_END

		__API_BRIDGE_HANDLE_BEGIN(IMPLEMENTATION)
`#'elif defined __API_BRIDGE_IMPLEMENTATION
`#'define `__API_BRIDGE_FUNC_API' m4_defn(`__API_BRIDGE_FUNC_API')
`#'define `__API_BRIDGE_FUNC_CALL' m4_defn(`__API_BRIDGE_FUNC_CALL')
`#'define `__API_BRIDGE_FUNC_END' m4_defn(`__API_BRIDGE_FUNC_END')
`#'define `__API_BRIDGE_CLASS' m4_defn(`__API_BRIDGE_CLASS')
`#'else
`#'error
`#'endif
		__API_BRIDGE_HANDLE_END

		m4_undefine(`__API_BRIDGE_FUNC_BODY_V')
		m4_undefine(`__API_BRIDGE_FUNC_BODY')

		m4_define(`__API_BRIDGE_FUNC_API', `__API_BRIDGE_FUNC_API')
		m4_define(`__API_BRIDGE_FUNC_CALL', `__API_BRIDGE_FUNC_CALL')
		m4_define(`__API_BRIDGE_FUNC_END', `__API_BRIDGE_FUNC_END')
		m4_define(`__API_BRIDGE_CLASS', `__API_BRIDGE_CLASS ')
		m4_define(`__API_BRIDGE_FUNC_DO_BODY', `')

END_NO_OUTPUT
`#'ifdef __API_BRIDGE_IMPLEMENTATION
`#'define `__API_BRIDGE_FUNC_BODY_V'(n, ...) { m4_defn(`API_BRIDGE_ACCESS')`'n(__VA_ARGS__); }
`#'define `__API_BRIDGE_FUNC_BODY'(n, ...) { return m4_defn(`API_BRIDGE_ACCESS')`'n(__VA_ARGS__); }
`#'else
`#'define `__API_BRIDGE_FUNC_BODY_V'(n, ...)
`#'define `__API_BRIDGE_FUNC_BODY'(n, ...)
`#'endif

$1

`#'undef `__API_BRIDGE_FUNC_API'
`#'undef `__API_BRIDGE_FUNC_CALL'
`#'undef `__API_BRIDGE_FUNC_END'
`#'undef `__API_BRIDGE_CLASS'
`#'undef `__API_BRIDGE_FUNC_BODY_V'
`#'undef `__API_BRIDGE_FUNC_BODY'
`#'undef __API_BRIDGE_INTERFACE
`#'undef __API_BRIDGE_IMPLEMENTATION
`#'undef __API_BRIDGE_DECLARATION

	')
', `
	m4_define(API_BRIDGE_FUNCS, `BEGIN_NO_OUTPUT
		__API_BRIDGE_HANDLE_BEGIN(API_BRIDGE_TYPE)
$1
		__API_BRIDGE_HANDLE_END

		END_NO_OUTPUT
	')
')

m4_define(API_BRIDGE_DEFINES, `
`#'ifdef __`'__API_BRIDGE_PROJECT_UPPER`'_IS_STATIC
	`#'define __API_BRIDGE_PROJECT_UPPER`'_SHARED_API
	`#'define __API_BRIDGE_PROJECT_UPPER`'_SHARED_API_CALL
`#'elif defined __`'__API_BRIDGE_PROJECT_UPPER`'_IS_SHARED
	`#'ifdef __COMPILING_`'__API_BRIDGE_PROJECT_UPPER
		`#'define __API_BRIDGE_PROJECT_UPPER`'_SHARED_API CTL_SHARED_EXPORT
	`#'else
		#define __API_BRIDGE_PROJECT_UPPER`'_SHARED_API CTL_SHARED_IMPORT
	`#'endif
	`#'define __API_BRIDGE_PROJECT_UPPER`'_SHARED_API_CALL CTL_SHARED_CALL
`#'else
	`#'error
`#'endif
')