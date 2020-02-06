# Locate clang-format tool
# This module defines
#  CLANG_FORMAT_BIN
#  CLANG_FORMAT_VERSION_STR
#  CLANG_FORMAT_VERSION
#
#  Usage:
#  find_package(ClangFormat)
#  if(CLANG_FORMAT_BIN)
#    if(CLANG_FORMAT_VERSION VERSION_GREATER "3.8")
#      ...
#    endif()
#  endif()

find_program(
	CLANG_FORMAT_BIN
	NAMES
	clang-format-6.0
	clang-format-5.0
	clang-format-4.0
	clang-format-3.9
	clang-format-3.8
	clang-format-3.7
	clang-format-3.6
	clang-format-3.5
	clang-format-3.4
	clang-format
	PATHS 
	/usr/bin/
)

mark_as_advanced(CLANG_FORMAT_BIN)

if(CLANG_FORMAT_BIN)
	execute_process(
		COMMAND ${CLANG_FORMAT_BIN} -version
		OUTPUT_VARIABLE CLANG_FORMAT_VERSION_STR
		ERROR_QUIET
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	string(
		REGEX REPLACE
		"clang-format version ([.0-9]+).*" "\\1"
		CLANG_FORMAT_VERSION
		"${CLANG_FORMAT_VERSION_STR}"
	)
endif()