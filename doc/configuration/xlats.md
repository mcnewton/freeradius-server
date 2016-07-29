xlats
=====

FreeRADIUS often permits strings to be "expanded" to a fuller
value. For instance, the following string

    "The user name is %{User-Name}"

might, whilst processing a request where the User-Name request
attribute is "guestuser", be expanded to:

    "The user name is guestuser"

xlats are additional functionality further than just expanding
attributes; they can do string and number processing, or database
lookups. Although the FreeRADIUS core defines some xlat functions,
many are created by different modules. So, for instance, the
`rlm_ldap` module defines xlats to do LDAP group lookups, whereas
the `rlm_sql` module adds the ability to directly call SQL
statements.

This adds some very powerful functionality to the unlang
configuration. A list of xlats is shown below.

List of basic xlats
-------------------

### base64

Provided by module `rlm_expr`

Base64 encodes the provided string.

Example: `%{base64:foo}`
Output: "Zm9v"

### base64tohex

Provided by module `rlm_expr`

Decodes a base64 string and outputs as a hex string.

Example: `%{base64tohex:Zm9v}`
Output: "666f6f" *("foo" in hex)*

### cache *

Provided by module `rlm_cache`

-desc-

Example: `%{cache:...}`
Output: ``

### date *

Provided by module `rlm_date`

-desc-

Example: `%{date:...}`
Output: ``

### dhcp *

Provided by module `proto_dhcp`

-desc-

Example: `%{dhcp:...}`
Output: ``

### dhcp_options *

Provided by module `proto_dhcp`

-desc-

Example: `%{dhcp_options:...}`
Output: ``

### escape *

Provided by module `rlm_expr`

Replaces potentially unsafe characters in a string with safe
versions by escaping with '='.

Example: `%{escape:<img>foo.jpg</img>}`
Output: `=60img=62foo.jpg=60/img=62`

See also: `unescape`

### exec *

Provided by module `rlm_exec`

-desc-

Example: `%{exec:...}`
Output: ``

### explode *

Provided by module `rlm_expr`

Split an attribute into multiple new attributes based on a
delimiter.

Example: `%{explode:&ref <delim>}`
Output: ``

### expr *

Provided by module `rlm_expr`

Perform mathematical calulations. See `raddb/mods-available/expr`
for details.

Example: `%{expr:&NAS-Port + 20}`
Output: If `NAS-Port := 3`, the output would be `23`

### hmacmd5 *

Provided by module `rlm_expr`

Generate the HMAC-MD5 of the provided string.

Example: `%{hmacmd5:foo bar}`
Output: `31b6db9e5eb4addb42f1a6ca07367adc`

### hmacsha1 *

Provided by module `rlm_expr`

Generate the HMAC-SHA1 of the provided string.

Example: `%{hmacsha1:foo bar}`
Output: `85d155c55ed286a300bd1cf124de08d87e914f3a`

### idn *

Provided by module `rlm_idn`

-desc-

Example: `%{idn:...}`
Output: ``

### if *

Provided by module `rlm_unbound`

-desc-

Example: `%{if:...}`
Output: ``

### jpathvalidate *

Provided by module `rlm_json`

-desc-

Example: `%{jpathvalidate:...}`
Output: ``

### jsonquote *

Provided by module `rlm_json`

-desc-

Example: `%{jsonquote:...}`
Output: ``

### ldap *

Provided by module `rlm_ldap`

-desc-

Example: `%{ldap:...}`
Output: ``

### ldap_escape *

Provided by module `rlm_ldap`

-desc-

Example: `%{ldap_escape:...}`
Output: ``

### ldap_unescape *

Provided by module `rlm_ldap`

-desc-

Example: `%{ldap_unescape:...}`
Output: ``

### ldapquote *

Provided by module `rlm_ldap`

-desc-

Example: `%{ldapquote:...}`
Output: ``

### lpad *

Provided by module `rlm_expr`

Pad the beginning of the string with characters to make it the
stated length.

Example: `%{lpad:&User-Name 5 X}`
Output: If `User-Name := "foo"`, the output would be `XXfoo`

See also: `rpad`

### md5 *

Provided by module `rlm_expr`

Calculate the md5 hash.

Example: `%{md5:foo}`
Output: `acbd18db4cc2f85cedef654fccc4a4d8`

### modhextohex *

Provided by module `rlm_yubikey`

-desc-

Example: `%{modhextohex:...}`
Output: ``

### mschap *

Provided by module `rlm_mschap`

-desc-

Example: `%{mschap:...}`
Output: ``

### nexttime *

Provided by module `rlm_expr`

Calculate the number of seconds until the next 'n' hour(s),
day(s), week(s), year(s).

Example: `%{nexttime:1h}`
Output: If the time were currently 16:59:50, the output would be `10`.

### pairs *

Provided by module `rlm_expr`

Serialize all the attributes from the specified attribute list
(request, control, reply) as a comma-delimited string.

Example: `%{pairs:request:}`
Output: `User-Name = 'foo', User-Password = 'bar', ...`

### rand *

Provided by module `rlm_expr`

Get a random integer from 0 to n-1.

Example: `%{rand:100}`
Output: `85`

### randstr *

Provided by module `rlm_expr`

Get a random string, built from the following character classes:
    c  lowercase letters
    C  uppercase letters
    n  numbers
    a  alphanumeric
    !  punctuation
    .  alphanumeric + punctuation
    s  alphanumeric + "./"
    o  characters suitable for OTP (easily confused letters removed)
    h  binary data as lowercase hex
    H  binary data as uppercase hex

Examples:

    `%{randstr:CCCC!!cccnnn}` == `IPFL>{saf874`
    `%{randstr:oooooooo}` == `rfVzyA4y`
    `%{randstr:hhhh}` == `68d60de3`

### redis *

Provided by module `rlm_redis`

-desc-

Example: `%{redis:...}`
Output: ``

### rest *

Provided by module `rlm_rest`

-desc-

Example: `%{rest:...}`
Output: ``

### rpad *

Provided by module `rlm_expr`

Pad the end of the string with characters to make it the
stated length.

Example: `%{rpad:&User-Name 7 -}`
Output: If `User-Name := "bar"`, the output would be `bar----`

See also: `lpad`

### sha1 *

Provided by module `rlm_expr`

Calculate the SHA1 hash.

Example: `%{sha1:foo}`
Output: `0beec7b5ea3f0fdbc95d0dd47f3c5bc275da8a33`

### sha256 *

Provided by module `rlm_expr`

Calculate the sha256 hash.

Example: `%{sha256:foo}`
Output: `2c26b46b68ffc68ff99b453c1d30413413422d706...`

### sha512 *

Provided by module `rlm_expr`

Calculate the sha512 hash.

Example: `%{sha512:foo}`
Output: `f7fbba6e0636f890e56fbbf3283e524c6fa3204ae29838...`

### soh *

Provided by module `rlm_soh`

-desc-

Example: `%{soh:...}`
Output: ``

### sql *

Provided by module `rlm_sql`

-desc-

Example: `%{sql:...}`
Output: ``

### tolower *

Provided by module `rlm_expr`

Convert the string to lowercase characters.

Example: `%{tolower:Bar}`
Output: `bar`

### toupper *

Provided by module `rlm_expr`

Convert the string to uppercase characters.

Example: `%{toupper:Foo}`
Output: `FOO`

### unbound *

Provided by module `rlm_unbound`

-desc-

Example: `%{unbound:...}`
Output: ``

### unbound *

Provided by module `rlm_unbound`

-desc-

Example: `%{unbound:...}`
Output: ``

### unescape *

Provided by module `rlm_expr`

Convert an escaped string back to its original form.

Example: `%{unescape:=60img=62foo.jpg=60/img=62}`
Output: `<img>foo.jpg</img>`

See also: `escape`

### unpack *

Provided by module `rlm_unpack`

-desc-

Example: `%{unpack:...}`
Output: ``

### urlquote *

Provided by module `rlm_expr`

Quote special characters in a URI.

Example: `%{urlquote:http://freeradius.org/}`
Output: `http%3A%47%47freeradius.org%47`

See also: `urlunquote`

### urlunquote *

Provided by module `rlm_expr`

Convert a quoted URI back to its original form.

Example: `%{urlunquote:http%3A%47%47networkradius.org%47}`
Output: `http://networkradius.org/`

See also: `urlquote`

### xlat_name *

Provided by module `rlm_perl`

-desc-

Example: `%{xlat_name:...}`
Output: ``

