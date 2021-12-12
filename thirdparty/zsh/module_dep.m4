m4_include(helpers.m4)
BEGIN_NO_OUTPUT

m4_define(__MODULE_VAR, `m4_esyscmd(__ZSH_DIR/get_module_var.sh MODULE_PATH $1)')

m4_define(`__MODULE_NAME', __MODULE_VAR(name))
m4_define(`__MODULE_NAME', m4_patsubst(__MODULE_NAME, `/', `Qs'))

END_NO_OUTPUT
`#'ifndef have_`'__MODULE_NAME`'_module
`#'define have_`'__MODULE_NAME`'_module

`#' ifndef IMPORTING_MODULE_`'__MODULE_NAME
`#'  ifndef MODULE
`#'   define boot_ boot_`'__MODULE_NAME
`#'   define cleanup_ cleanup_`'__MODULE_NAME
`#'   define features_ features_`'__MODULE_NAME
`#'   define enables_ enables_`'__MODULE_NAME
`#'   define setup_ setup_`'__MODULE_NAME
`#'   define finish_ finish_`'__MODULE_NAME
`#'  endif /* !MODULE */
`#' endif /* !IMPORTING_MODULE_`'__MODULE_NAME */

/* Extra headers for this module */
FOREACH(`HEADER', (__MODULE_VAR(headers)), ``#' include "HEADER"
')

`#' undef mod_import_variable
`#' undef mod_import_function
`#' if defined(IMPORTING_MODULE_`'__MODULE_NAME) &&  defined(MODULE)
`#'  define mod_import_variable 
`#'  define mod_import_function 
`#' else
`#'  define mod_import_function
`#'  define mod_import_variable
`#' endif /* IMPORTING_MODULE_`'__MODULE_NAME && MODULE */

`#' undef mod_import_variable
`#' define mod_import_variable
`#' undef mod_import_variable
`#' define mod_import_variable
`#' ifndef mod_export
`#'  define mod_export 
`#' endif /* mod_export */

`#'endif /* !have_`'__MODULE_NAME`'_module */
