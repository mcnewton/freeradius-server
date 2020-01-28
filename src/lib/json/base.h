#pragma once
/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or (at
 *   your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/**
 * $Id$
 * @file lib/json/base.h
 * @brief Implements the evaluation and parsing functions for the FreeRADIUS version of jpath.
 *
 * @author Arran Cudbard-Bell
 *
 * @copyright 2015 Arran Cudbard-Bell (a.cudbardb@freeradius.org)
 * @copyright 2015 Network RADIUS SARL (legal@networkradius.com)
 * @copyright 2015 The FreeRADIUS Server Project
 */
RCSIDH(json_h, "$Id$")

#include "config.h"

#ifdef HAVE_JSON
#  if defined(HAVE_JSONMC_JSON_H)
#    include <json-c/json.h>
#  elif defined(HAVE_JSON_JSON_H)
#    include <json/json.h>
#  else
#    error "Need json-c headers"
#  endif
#  include "json_missing.h"

#  include <freeradius-devel/server/base.h>

/** Formatting options for fr_json_afrom_pair_list()
 *
 * These options control the format of JSON document which is
 * produced from fr_json_afrom_pair_list(). See rlm_json module
 * documentation and tests for more examples.
 *
 *
 * **format_array** controls whether a JSON object (i.e.
 * dictionary) or an array is generated. When false, the output
 * will be a JSON object. The keys will be the attribute names:
@verbatim
{"User-Name":{"value":["john"]},"User-Password":{"value":["testing123"]}}
@endverbatim
 * When true, the output will be a JSON array of objects, each
 * containing the attributes in order:
@verbatim
[{"name":"User-Name","value":"john"},{"name":"User-Password","value":"testing123"}]
@endverbatim
 *
 *
 * **simple** determines whether a simpler object or array is
 * generated. When false, the output is in a more structured
 * format; see the above examples for objects and arrays.
 *
 * When true, the output is simplified, e.g.
@verbatim
{"User-Name":"john","User-Password":"testing123"}
@endverbatim
 * Arrays with `simple` set will always be a list of the
 * attribute values only:
@verbatim
["john","testing123"]
@endverbatim
 *
 *
 * **include_type** will include the attribute type in the output
 * where possible. The type is the internal attribute type
 * (string, uint32, etc), not the output format type seen in the
 * JSON document. The type is therefore not affected by the
 * `always_string` or `enum_value` options.
 *
 * Object and array examples when false:
@verbatim
{"User-Name":{"value":["john"]},"User-Password":{"value":["testing123"]}}
[{"name":"User-Name","value":"john"},{"name":"User-Password","value":"testing123"}]
@endverbatim
 * Object and array examples when true:
@verbatim
{"User-Name":{"type":"string","value":["john"]},"User-Password":{"type":"string","value":["testing123"]}}
[{"name":"User-Name","type":"string","value":"john"},{"name":"User-Password","type":"string","value":"testing123"}]
@endverbatim
 *
 *
 * **value_as_list**, when true, ensures that all identical
 * attributes are listed only once, with all values in an array.
 * When false, those attributes should be separated out
 * individually if possible.
 *
 * This option has no effect when `format_array` is true and
 * `simple` is also true.
 *
 * Example when `format_array` is false and `value_as_list` is false:
@verbatim
{"User-Name":"john","Filter-Id":["f1","f2"]}
@endverbatim
 * Example when `format_array` is false and `value_as_list` is
 * true (note the `User-Name` value is now in a list, even though it
 * is a single value; `Filter-Id` is always a list, as there are
 * multiple attributes):
@verbatim
{"User-Name":["john"],"Filter-Id":["f1","f2"]}
@endverbatim
 *
 * Example when an array is being generated (`format_array` is
 * true) and `value_as_list` is false:
@verbatim
[{"name":"User-Name","value":"john"},{"name":"Filter-Id","value":"f1"},{"name":"Filter-Id","value":"f2"}]
@endverbatim
 * Array example when `value_as_list` is true:
@verbatim
[{"name":"User-Name","value":"john"},{"name":"Filter-Id","value":["f1","f2"]}]
@endverbatim
 *
 *
 * **always_string** ensures that all values are written as
 * strings in the JSON document.
 *
 * Example when `always_string` is false:
@verbatim
{"Tmp-Integer-1":{"type":"uint32","value":[999]}}
@endverbatim
 * Example when `always_string` is true:
@verbatim
{"Tmp-Integer-1":{"type":"uint32","value":["999"]}}
@endverbatim
 *
 *
 * **enum_value** determines whether enumerated values are written
 * in their string or integer form.
 *
 * When false, the string form is output:
@verbatim
{"Service-Type":{"type":"uint32","value":["Login-User"]}}
@endverbatim
 * When true, the integer is output:
@verbatim
{"Service-Type":{"type":"uint32","value":[1]}}
@endverbatim
 *
 *
 * **prefix** adds a string prefix to all attribute names in the
 * JSON document, with a colon delimiter.
 *
 * Example, when prefix is set to `foo`:
@verbatim
{"foo:User-Name":{"type":"string","value":["john"]}}
@endverbatim
 *
 */
struct fr_json_format_s {
	bool	format_array;	//!< When true, output is an array. Otherwise an object.

	bool	simple;		//!< Use a simplified output format.

	bool	include_type;	//!< Include attribute type where possible.

	bool	value_as_list;	//!< Use JSON array for multiple attribute values.

	bool	always_string;	//!< Output all data types as strings.

	bool	enum_value;	//!< Output enums as value, not their string representation.

	char const *prefix;	//!< Prefix to add to all attribute names
};

typedef struct fr_json_format_s fr_json_format_t;

extern CONF_PARSER const fr_json_format_config[];


/* jpath .c */
typedef struct fr_jpath_node fr_jpath_node_t;

size_t		fr_jpath_escape_func(UNUSED REQUEST *request, char *out, size_t outlen,
				     char const *in, UNUSED void *arg);

int		fr_jpath_evaluate_leaf(TALLOC_CTX *ctx, fr_value_box_t **out,
				       fr_type_t dst_type, fr_dict_attr_t const *dst_enumv,
				       json_object *root, fr_jpath_node_t const *jpath);

char		*fr_jpath_asprint(TALLOC_CTX *ctx, fr_jpath_node_t const *head);

ssize_t		fr_jpath_parse(TALLOC_CTX *ctx, fr_jpath_node_t **head, char const *in, size_t inlen);

/* json.c */
int		fr_json_object_to_value_box(TALLOC_CTX *ctx, fr_value_box_t *out, json_object *object,
					    fr_dict_attr_t const *enumv, bool tainted);

json_object	*json_object_from_value_box(TALLOC_CTX *ctx, fr_value_box_t const *data);

char		*fr_json_from_string(TALLOC_CTX *ctx, char const *s, bool include_quotes);

size_t    	fr_json_from_pair(char *out, size_t outlen, VALUE_PAIR const *vp);

void		fr_json_version_print(void);

char		*fr_json_afrom_pair_list(TALLOC_CTX *ctx, VALUE_PAIR **vps,
					 fr_json_format_t const *format);
#endif
