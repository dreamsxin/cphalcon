
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Security\Random
 *
 * Secure random number generator class.
 *
 * Provides secure random number generator which is suitable for generating
 * session key in HTTP cookies, etc.
 *
 * It supports following secure random number generators:
 *
 * - random_bytes (PHP 7)
 * - libsodium
 * - openssl, libressl
 * - /dev/urandom
 *
 * `Phalcon\Security\Random` could be mainly useful for:
 *
 * - Key generation (e.g. generation of complicated keys)
 * - Generating random passwords for new user accounts
 * - Encryption systems
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * // Random binary string
 * $bytes = $random->bytes();
 *
 * // Random hex string
 * echo $random->hex(10); // a29f470508d5ccb8e289
 * echo $random->hex(10); // 533c2f08d5eee750e64a
 * echo $random->hex(11); // f362ef96cb9ffef150c9cd
 * echo $random->hex(12); // 95469d667475125208be45c4
 * echo $random->hex(13); // 05475e8af4a34f8f743ab48761
 *
 * // Random base62 string
 * echo $random->base62(); // z0RkwHfh8ErDM1xw
 *
 * // Random base64 string
 * echo $random->base64(12); // XfIN81jGGuKkcE1E
 * echo $random->base64(12); // 3rcq39QzGK9fUqh8
 * echo $random->base64();   // DRcfbngL/iOo9hGGvy1TcQ==
 * echo $random->base64(16); // SvdhPcIHDZFad838Bb0Swg==
 *
 * // Random URL-safe base64 string
 * echo $random->base64Safe();           // PcV6jGbJ6vfVw7hfKIFDGA
 * echo $random->base64Safe();           // GD8JojhzSTrqX7Q8J6uug
 * echo $random->base64Safe(8);          // mGyy0evy3ok
 * echo $random->base64Safe(null, true); // DRrAgOFkS4rvRiVHFefcQ==
 *
 * // Random UUID
 * echo $random->uuid(); // db082997-2572-4e2c-a046-5eefe97b1235
 * echo $random->uuid(); // da2aa0e2-b4d0-4e3c-99f5-f5ef62c57fe2
 * echo $random->uuid(); // 75e6b628-c562-4117-bb76-61c4153455a9
 * echo $random->uuid(); // dc446df1-0848-4d05-b501-4af3c220c13d
 *
 * // Random number between 0 and $len
 * echo $random->number(256); // 84
 * echo $random->number(256); // 79
 * echo $random->number(100); // 29
 * echo $random->number(300); // 40
 *
 * // Random base58 string
 * echo $random->base58();   // 4kUgL2pdQMSCQtjE
 * echo $random->base58();   // Umjxqf7ZPwh765yR
 * echo $random->base58(24); // qoXcgmw4A9dys26HaNEdCRj9
 * echo $random->base58(7);  // 774SJD3vgP
 *</code>
 *
 * This class partially borrows SecureRandom library from Ruby
 *
 * @link http://ruby-doc.org/stdlib-2.2.2/libdoc/securerandom/rdoc/SecureRandom.html
 */
ZEPHIR_INIT_CLASS(Phalcon_Security_Random) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Security, Random, phalcon, security_random, phalcon_security_random_method_entry, 0);

	return SUCCESS;

}

/**
 * Generates a random base58 string
 *
 * If $len is not specified, 16 is assumed. It may be larger in future.
 * The result may contain alphanumeric characters except 0, O, I and l.
 *
 * It is similar to `Phalcon\Security\Random::base64()` but has been
 * modified to avoid both non-alphanumeric characters and letters which
 * might look ambiguous when printed.
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->base58(); // 4kUgL2pdQMSCQtjE
 *</code>
 *
 * @see    \Phalcon\Security\Random:base64
 * @link   https://en.wikipedia.org/wiki/Base58
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, base58) {

	zval *len_param = NULL, _0, _1, _2;
	zend_long len, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &len_param);

	if (!len_param) {
		len = 0;
	} else {
		len = zephir_get_intval(len_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz");
	ZVAL_LONG(&_1, 58);
	ZVAL_LONG(&_2, len);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "base", NULL, 0, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates a random base62 string
 *
 * If $len is not specified, 16 is assumed. It may be larger in future.
 *
 * It is similar to `Phalcon\Security\Random::base58()` but has been
 * modified to provide the largest value that can safely be used in URLs
 * without needing to take extra characters into consideration because it is
 * [A-Za-z0-9].
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->base62(); // z0RkwHfh8ErDM1xw
 *</code>
 *
 * @see    \Phalcon\Security\Random:base58
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, base62) {

	zval *len_param = NULL, _0, _1, _2;
	zend_long len, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &len_param);

	if (!len_param) {
		len = 0;
	} else {
		len = zephir_get_intval(len_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	ZVAL_LONG(&_1, 62);
	ZVAL_LONG(&_2, len);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "base", NULL, 0, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates a random base64 string
 *
 * If $len is not specified, 16 is assumed. It may be larger in future.
 * The length of the result string is usually greater of $len.
 * Size formula: 4 * ($len / 3) rounded up to a multiple of 4.
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->base64(12); // 3rcq39QzGK9fUqh8
 *</code>
 *
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, base64) {

	zval *len_param = NULL, _0, _1;
	zend_long len, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &len_param);

	if (!len_param) {
		len = 0;
	} else {
		len = zephir_get_intval(len_param);
	}


	ZVAL_LONG(&_1, len);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "bytes", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("base64_encode", NULL, 168, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates a random URL-safe base64 string
 *
 * If $len is not specified, 16 is assumed. It may be larger in future.
 * The length of the result string is usually greater of $len.
 *
 * By default, padding is not generated because "=" may be used as a URL
 * delimiter. The result may contain A-Z, a-z, 0-9, "-" and "_". "=" is also
 * used if $padding is true. See RFC 3548 for the definition of URL-safe
 * base64.
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->base64Safe(); // GD8JojhzSTrqX7Q8J6uug
 *</code>
 *
 * @link https://www.ietf.org/rfc/rfc3548.txt
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, base64Safe) {

	zend_bool padding;
	zval *len_param = NULL, *padding_param = NULL, s, _0, _1, _2, _3, _4, _5, _6$$3;
	zend_long len, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&s);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &len_param, &padding_param);

	if (!len_param) {
		len = 0;
	} else {
		len = zephir_get_intval(len_param);
	}
	if (!padding_param) {
		padding = 0;
	} else {
		padding = zephir_get_boolval(padding_param);
	}


	ZVAL_LONG(&_1, len);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "base64", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_2, "base64_encode", NULL, 168, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "+/");
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "-_");
	ZEPHIR_CALL_FUNCTION(&s, "strtr", NULL, 82, &_2, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "#[^a-z0-9_=-]+#i");
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "");
	ZEPHIR_CALL_FUNCTION(&_5, "preg_replace", NULL, 40, &_3, &_4, &s);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&s, &_5);
	if (!(padding)) {
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "=");
		zephir_fast_trim(return_value, &s, &_6$$3, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
		RETURN_MM();
	}
	RETURN_CCTOR(&s);

}

/**
 * Generates a random binary string
 *
 * The `Random::bytes` method returns a string and accepts as input an int
 * representing the length in bytes to be returned.
 *
 * If $len is not specified, 16 is assumed. It may be larger in future.
 * The result may contain any byte: "x00" - "xFF".
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * $bytes = $random->bytes();
 * var_dump(bin2hex($bytes));
 * // Possible output: string(32) "00f6c04b144b41fad6a59111c126e1ee"
 *</code>
 *
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, bytes) {

	zval *len_param = NULL, handle, ret, _3, _6, _0$$4, _1$$5, _2$$6, _4$$7, _5$$7;
	zend_long len, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handle);
	ZVAL_UNDEF(&ret);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$5);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &len_param);

	if (!len_param) {
		len = 16;
	} else {
		len = zephir_get_intval(len_param);
	}


	if (len <= 0) {
		len = 16;
	}
	if ((zephir_function_exists_ex(SL("random_bytes") TSRMLS_CC) == SUCCESS)) {
		ZVAL_LONG(&_0$$4, len);
		ZEPHIR_RETURN_CALL_FUNCTION("random_bytes", NULL, 473, &_0$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SL("\\sodium\\randombytes_buf") TSRMLS_CC) == SUCCESS)) {
		ZVAL_LONG(&_1$$5, len);
		ZEPHIR_RETURN_CALL_FUNCTION("\\sodium\\randombytes_buf", NULL, 0, &_1$$5);
		zephir_check_call_status();
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SL("openssl_random_pseudo_bytes") TSRMLS_CC) == SUCCESS)) {
		ZVAL_LONG(&_2$$6, len);
		ZEPHIR_RETURN_CALL_FUNCTION("openssl_random_pseudo_bytes", NULL, 166, &_2$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&handle);
	ZVAL_BOOL(&handle, 0);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "/dev/urandom");
	if ((zephir_file_exists(&_3 TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_INIT_VAR(&_4$$7);
		ZVAL_STRING(&_4$$7, "/dev/urandom");
		ZEPHIR_INIT_VAR(&_5$$7);
		ZVAL_STRING(&_5$$7, "rb");
		ZEPHIR_CALL_FUNCTION(&handle, "fopen", NULL, 77, &_4$$7, &_5$$7);
		zephir_check_call_status();
	}
	if (UNEXPECTED(ZEPHIR_IS_FALSE_IDENTICAL(&handle))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "No random device available", "phalcon/Security/Random.zep", 257);
		return;
	}
	ZVAL_LONG(&_6, 0);
	ZEPHIR_CALL_FUNCTION(NULL, "stream_set_read_buffer", NULL, 474, &handle, &_6);
	zephir_check_call_status();
	ZVAL_LONG(&_6, len);
	ZEPHIR_CALL_FUNCTION(&ret, "fread", NULL, 73, &handle, &_6);
	zephir_check_call_status();
	zephir_fclose(&handle TSRMLS_CC);
	if (UNEXPECTED(zephir_fast_strlen_ev(&ret) != len)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "Unexpected partial read from random device", "phalcon/Security/Random.zep", 269);
		return;
	}
	RETURN_CCTOR(&ret);

}

/**
 * Generates a random hex string
 *
 * If $len is not specified, 16 is assumed. It may be larger in future.
 * The length of the result string is usually greater of $len.
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->hex(10); // a29f470508d5ccb8e289
 *</code>
 *
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, hex) {

	zval *len_param = NULL, _0, _1, _2, _3;
	zend_long len, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &len_param);

	if (!len_param) {
		len = 0;
	} else {
		len = zephir_get_intval(len_param);
	}


	ZVAL_LONG(&_1, len);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "bytes", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "H*");
	ZEPHIR_CALL_FUNCTION(&_3, "unpack", NULL, 475, &_2, &_0);
	zephir_check_call_status();
	ZEPHIR_MAKE_REF(&_3);
	ZEPHIR_RETURN_CALL_FUNCTION("array_shift", NULL, 12, &_3);
	ZEPHIR_UNREF(&_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates a random number between 0 and $len
 *
 * Returns an integer: 0 <= result <= $len.
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->number(16); // 8
 *</code>
 * @throws Exception If secure random number generator is not available, unexpected partial read or $len <= 0
 */
PHP_METHOD(Phalcon_Security_Random, number) {

	unsigned char _8;
	zval bin;
	zephir_fcall_cache_entry *_13 = NULL, *_18 = NULL, *_22 = NULL;
	zval *len_param = NULL, hex, mask, rnd, ret, _4, _6, _7, _23, _0$$4, _1$$4, _2$$5, _3$$5, _5$$6, _12$$7, _14$$7, _15$$7, _16$$7, _17$$7, _19$$7, _20$$7, _21$$7;
	zend_long len, ZEPHIR_LAST_CALL_STATUS, _9, _10, _11;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&hex);
	ZVAL_UNDEF(&mask);
	ZVAL_UNDEF(&rnd);
	ZVAL_UNDEF(&ret);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&bin);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &len_param);

	len = zephir_get_intval(len_param);


	ZEPHIR_INIT_VAR(&bin);
	ZVAL_STRING(&bin, "");
	if (UNEXPECTED(len <= 0)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_security_exception_ce, "Require a positive integer > 0", "phalcon/Security/Random.zep", 317);
		return;
	}
	if ((zephir_function_exists_ex(SL("random_int") TSRMLS_CC) == SUCCESS)) {
		ZVAL_LONG(&_0$$4, 0);
		ZVAL_LONG(&_1$$4, len);
		ZEPHIR_RETURN_CALL_FUNCTION("random_int", NULL, 476, &_0$$4, &_1$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	if ((zephir_function_exists_ex(SL("\\sodium\\randombytes_uniform") TSRMLS_CC) == SUCCESS)) {
		ZVAL_LONG(&_2$$5, len);
		ZEPHIR_CALL_FUNCTION(&_3$$5, "\\sodium\\randombytes_uniform", NULL, 0, &_2$$5);
		zephir_check_call_status();
		RETURN_MM_LONG((zephir_get_numberval(&_3$$5) + 1));
	}
	ZVAL_LONG(&_4, len);
	ZEPHIR_CALL_FUNCTION(&hex, "dechex", NULL, 477, &_4);
	zephir_check_call_status();
	if (((zephir_fast_strlen_ev(&hex) & 1)) == 1) {
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SV(&_5$$6, "0", &hex);
		ZEPHIR_CPY_WRT(&hex, &_5$$6);
	}
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "H*");
	ZEPHIR_CALL_FUNCTION(&_7, "pack", NULL, 478, &_6, &hex);
	zephir_check_call_status();
	zephir_concat_self(&bin, &_7 TSRMLS_CC);
	_8 = ZEPHIR_STRING_OFFSET(&bin, 0);
	ZEPHIR_INIT_NVAR(&_6);
	ZVAL_STRINGL(&_6, &_8, 1);
	ZEPHIR_CALL_FUNCTION(&mask, "ord", NULL, 176, &_6);
	zephir_check_call_status();
	_9 = ((int) (zephir_get_numberval(&mask)) | (((int) (zephir_get_numberval(&mask)) >> 1)));
	ZEPHIR_INIT_NVAR(&mask);
	ZVAL_LONG(&mask, _9);
	_10 = ((int) (zephir_get_numberval(&mask)) | (((int) (zephir_get_numberval(&mask)) >> 2)));
	ZEPHIR_INIT_NVAR(&mask);
	ZVAL_LONG(&mask, _10);
	_11 = ((int) (zephir_get_numberval(&mask)) | (((int) (zephir_get_numberval(&mask)) >> 4)));
	ZEPHIR_INIT_NVAR(&mask);
	ZVAL_LONG(&mask, _11);
	do {
		ZVAL_LONG(&_12$$7, zephir_fast_strlen_ev(&bin));
		ZEPHIR_CALL_METHOD(&rnd, this_ptr, "bytes", &_13, 0, &_12$$7);
		zephir_check_call_status();
		ZVAL_LONG(&_12$$7, 0);
		ZVAL_LONG(&_14$$7, 1);
		ZEPHIR_INIT_NVAR(&_15$$7);
		zephir_substr(&_15$$7, &rnd, 0 , 1 , 0);
		ZEPHIR_CALL_FUNCTION(&_16$$7, "ord", NULL, 176, &_15$$7);
		zephir_check_call_status();
		ZEPHIR_SINIT_NVAR(_17$$7);
		zephir_bitwise_and_function(&_17$$7, &_16$$7, &mask TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_16$$7, "chr", &_18, 173, &_17$$7);
		zephir_check_call_status();
		ZVAL_LONG(&_19$$7, 0);
		ZVAL_LONG(&_20$$7, 1);
		ZEPHIR_CALL_FUNCTION(&_21$$7, "substr_replace", &_22, 479, &rnd, &_16$$7, &_19$$7, &_20$$7);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&rnd, &_21$$7);
	} while (ZEPHIR_LT(&bin, &rnd));
	ZEPHIR_INIT_NVAR(&_6);
	ZVAL_STRING(&_6, "H*");
	ZEPHIR_CALL_FUNCTION(&ret, "unpack", NULL, 475, &_6, &rnd);
	zephir_check_call_status();
	ZEPHIR_MAKE_REF(&ret);
	ZEPHIR_CALL_FUNCTION(&_23, "array_shift", NULL, 12, &ret);
	ZEPHIR_UNREF(&ret);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("hexdec", NULL, 480, &_23);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates a v4 random UUID (Universally Unique IDentifier)
 *
 * The version 4 UUID is purely random (except the version). It doesn't
 * contain meaningful information such as MAC address, time, etc. See RFC
 * 4122 for details of UUID.
 *
 * This algorithm sets the version number (4 bits) as well as two reserved
 * bits. All other bits (the remaining 122 bits) are set using a random or
 * pseudorandom data source. Version 4 UUIDs have the form
 * xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx where x is any hexadecimal digit and
 * y is one of 8, 9, A, or B (e.g., f47ac10b-58cc-4372-a567-0e02b2c3d479).
 *
 *<code>
 * $random = new \Phalcon\Security\Random();
 *
 * echo $random->uuid(); // 1378c906-64bb-4f81-a8d6-4ae1bfcdec22
 *</code>
 *
 * @link https://www.ietf.org/rfc/rfc4122.txt
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, uuid) {

	zval ary, _0, _1, _2, _3, _4, _5, _6, _7;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ary);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);

	ZEPHIR_MM_GROW();

	ZVAL_LONG(&_1, 16);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "bytes", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "N1a/n1b/n1c/n1d/n1e/N1f");
	ZEPHIR_CALL_FUNCTION(&_3, "unpack", NULL, 475, &_2, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&ary, "array_values", NULL, 149, &_3);
	zephir_check_call_status();
	zephir_array_fetch_long(&_4, &ary, 2, PH_NOISY | PH_READONLY, "phalcon/Security/Random.zep", 398 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, ((((int) (zephir_get_numberval(&_4)) & 0x0fff)) | 0x4000));
	zephir_array_update_long(&ary, 2, &_2, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_fetch_long(&_5, &ary, 3, PH_NOISY | PH_READONLY, "phalcon/Security/Random.zep", 399 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_LONG(&_6, ((((int) (zephir_get_numberval(&_5)) & 0x3fff)) | 0x8000));
	zephir_array_update_long(&ary, 3, &_6, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "%08x-%04x-%04x-%04x-%04x%08x");
	ZEPHIR_MAKE_REF(&ary);
	ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 470, &ary, &_7);
	ZEPHIR_UNREF(&ary);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_7);
	ZVAL_STRING(&_7, "sprintf");
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_7, &ary);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generates a random string based on the number ($base) of characters
 * ($alphabet).
 *
 * If $n is not specified, 16 is assumed. It may be larger in future.
 *
 * @throws Exception If secure random number generator is not available or unexpected partial read
 */
PHP_METHOD(Phalcon_Security_Random, base) {

	unsigned char _7$$3, _10$$5;
	double _4$$3, _8$$5;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long base, ZEPHIR_LAST_CALL_STATUS;
	zval *alphabet_param = NULL, *base_param = NULL, *n = NULL, n_sub, __$null, bytes, idx, _0, _1, *_2, _3, _5$$4, _9$$6;
	zval alphabet, byteString;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&alphabet);
	ZVAL_UNDEF(&byteString);
	ZVAL_UNDEF(&n_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&bytes);
	ZVAL_UNDEF(&idx);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_9$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &alphabet_param, &base_param, &n);

	zephir_get_strval(&alphabet, alphabet_param);
	base = zephir_get_intval(base_param);
	if (!n) {
		n = &n_sub;
		n = &__$null;
	}


	ZEPHIR_INIT_VAR(&byteString);
	ZVAL_STRING(&byteString, "");
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "bytes", NULL, 0, n);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "C*");
	ZEPHIR_CALL_FUNCTION(&bytes, "unpack", NULL, 475, &_1, &_0);
	zephir_check_call_status();
	zephir_is_iterable(&bytes, 0, "phalcon/Security/Random.zep", 438);
	if (Z_TYPE_P(&bytes) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&bytes), _2)
		{
			ZEPHIR_INIT_NVAR(&idx);
			ZVAL_COPY(&idx, _2);
			_4$$3 = zephir_safe_mod_zval_long(&idx, 64 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&idx);
			ZVAL_DOUBLE(&idx, _4$$3);
			if (ZEPHIR_GE_LONG(&idx, base)) {
				ZVAL_LONG(&_5$$4, (base - 1));
				ZEPHIR_CALL_METHOD(&idx, this_ptr, "number", &_6, 0, &_5$$4);
				zephir_check_call_status();
			}
			_7$$3 = ZEPHIR_STRING_OFFSET(&alphabet, zephir_get_intval(&idx));
			zephir_concat_self_char(&byteString, _7$$3 TSRMLS_CC);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &bytes, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_3, &bytes, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&idx, &bytes, "current", NULL, 0);
			zephir_check_call_status();
				_8$$5 = zephir_safe_mod_zval_long(&idx, 64 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&idx);
				ZVAL_DOUBLE(&idx, _8$$5);
				if (ZEPHIR_GE_LONG(&idx, base)) {
					ZVAL_LONG(&_9$$6, (base - 1));
					ZEPHIR_CALL_METHOD(&idx, this_ptr, "number", &_6, 0, &_9$$6);
					zephir_check_call_status();
				}
				_10$$5 = ZEPHIR_STRING_OFFSET(&alphabet, zephir_get_intval(&idx));
				zephir_concat_self_char(&byteString, _10$$5 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, &bytes, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&idx);
	RETURN_CTOR(&byteString);

}

