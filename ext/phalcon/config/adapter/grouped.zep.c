
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Config\Adapter\Grouped
 *
 * Reads multiple files (or arrays) and merges them all together.
 *
 * @see Phalcon\Config\Factory::load To load Config Adapter class using 'adapter' option.
 *
 * <code>
 * use Phalcon\Config\Adapter\Grouped;
 *
 * $config = new Grouped(
 *     [
 *         "path/to/config.php",
 *         "path/to/config.dist.php",
 *     ]
 * );
 * </code>
 *
 * <code>
 * use Phalcon\Config\Adapter\Grouped;
 *
 * $config = new Grouped(
 *     [
 *         "path/to/config.json",
 *         "path/to/config.dist.json",
 *     ],
 *     "json"
 * );
 * </code>
 *
 * <code>
 * use Phalcon\Config\Adapter\Grouped;
 *
 * $config = new Grouped(
 *     [
 *         [
 *             "filePath" => "path/to/config.php",
 *             "adapter"  => "php",
 *         ],
 *         [
 *             "filePath" => "path/to/config.json",
 *             "adapter"  => "json",
 *         ],
 *         [
 *             "adapter"  => "array",
 *             "config"   => [
 *                 "property" => "value",
 *             ],
 *         ],
 *     ],
 * );
 * </code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Config_Adapter_Grouped) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Config\\Adapter, Grouped, phalcon, config_adapter_grouped, phalcon_config_ce, phalcon_config_adapter_grouped_method_entry, 0);

	return SUCCESS;

}

/**
 * Phalcon\Config\Adapter\Grouped constructor
 */
PHP_METHOD(Phalcon_Config_Adapter_Grouped, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL, *_6 = NULL, *_7 = NULL, *_10 = NULL;
	zval defaultAdapter;
	zval *arrayConfig_param = NULL, *defaultAdapter_param = NULL, configName, configInstance, configArray, _1, *_2, _3, _4$$5, _5$$5, _8$$4, _9$$3, _11$$9, _12$$9, _13$$12, _14$$12, _15$$11, _16$$10, _17$$16, _18$$16;
	zval arrayConfig;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&arrayConfig);
	ZVAL_UNDEF(&configName);
	ZVAL_UNDEF(&configInstance);
	ZVAL_UNDEF(&configArray);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$12);
	ZVAL_UNDEF(&_14$$12);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_17$$16);
	ZVAL_UNDEF(&_18$$16);
	ZVAL_UNDEF(&defaultAdapter);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &arrayConfig_param, &defaultAdapter_param);

	ZEPHIR_OBS_COPY_OR_DUP(&arrayConfig, arrayConfig_param);
	if (!defaultAdapter_param) {
		ZEPHIR_INIT_VAR(&defaultAdapter);
		ZVAL_STRING(&defaultAdapter, "php");
	} else {
	if (UNEXPECTED(Z_TYPE_P(defaultAdapter_param) != IS_STRING && Z_TYPE_P(defaultAdapter_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'defaultAdapter' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(defaultAdapter_param) == IS_STRING)) {
		zephir_get_strval(&defaultAdapter, defaultAdapter_param);
	} else {
		ZEPHIR_INIT_VAR(&defaultAdapter);
		ZVAL_EMPTY_STRING(&defaultAdapter);
	}
	}


	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	ZEPHIR_CALL_PARENT(NULL, phalcon_config_adapter_grouped_ce, getThis(), "__construct", &_0, 0, &_1);
	zephir_check_call_status();
	zephir_is_iterable(&arrayConfig, 0, "phalcon/Config/Adapter/Grouped.zep", 119);
	if (Z_TYPE_P(&arrayConfig) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arrayConfig), _2)
		{
			ZEPHIR_INIT_NVAR(&configName);
			ZVAL_COPY(&configName, _2);
			ZEPHIR_CPY_WRT(&configInstance, &configName);
			if (Z_TYPE_P(&configName) == IS_STRING) {
				if (ZEPHIR_IS_STRING_IDENTICAL(&defaultAdapter, "")) {
					ZEPHIR_INIT_NVAR(&_4$$5);
					object_init_ex(&_4$$5, phalcon_config_configfactory_ce);
					if (zephir_has_constructor(&_4$$5 TSRMLS_CC)) {
						ZEPHIR_CALL_METHOD(NULL, &_4$$5, "__construct", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_5$$5, &_4$$5, "load", &_6, 152, &configName);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "internalmerge", &_7, 11, &_5$$5);
					zephir_check_call_status();
					continue;
				}
				ZEPHIR_INIT_NVAR(&_8$$4);
				zephir_create_array(&_8$$4, 2, 0 TSRMLS_CC);
				zephir_array_update_string(&_8$$4, SL("filePath"), &configName, PH_COPY | PH_SEPARATE);
				zephir_array_update_string(&_8$$4, SL("adapter"), &defaultAdapter, PH_COPY | PH_SEPARATE);
				ZEPHIR_CPY_WRT(&configInstance, &_8$$4);
			} else if (!(zephir_array_isset_string(&configInstance, SL("adapter")))) {
				zephir_array_update_string(&configInstance, SL("adapter"), &defaultAdapter, PH_COPY | PH_SEPARATE);
			}
			zephir_array_fetch_string(&_9$$3, &configInstance, SL("adapter"), PH_NOISY | PH_READONLY, "phalcon/Config/Adapter/Grouped.zep", 104 TSRMLS_CC);
			if (ZEPHIR_IS_STRING_IDENTICAL(&_9$$3, "array")) {
				if (UNEXPECTED(!(zephir_array_isset_string(&configInstance, SL("config"))))) {
					ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_factory_exception_ce, "To use 'array' adapter you have to specify the 'config' as an array.", "phalcon/Config/Adapter/Grouped.zep", 108);
					return;
				}
				ZEPHIR_OBS_NVAR(&configArray);
				zephir_array_fetch_string(&configArray, &configInstance, SL("config"), PH_NOISY, "phalcon/Config/Adapter/Grouped.zep", 111 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&configInstance);
				object_init_ex(&configInstance, phalcon_config_ce);
				ZEPHIR_CALL_METHOD(NULL, &configInstance, "__construct", &_10, 8, &configArray);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&_11$$9);
				object_init_ex(&_11$$9, phalcon_config_configfactory_ce);
				if (zephir_has_constructor(&_11$$9 TSRMLS_CC)) {
					ZEPHIR_CALL_METHOD(NULL, &_11$$9, "__construct", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_12$$9, &_11$$9, "load", &_6, 152, &configInstance);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&configInstance, &_12$$9);
			}
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "internalmerge", &_7, 11, &configInstance);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &arrayConfig, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_3, &arrayConfig, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&configName, &arrayConfig, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CPY_WRT(&configInstance, &configName);
				if (Z_TYPE_P(&configName) == IS_STRING) {
					if (ZEPHIR_IS_STRING_IDENTICAL(&defaultAdapter, "")) {
						ZEPHIR_INIT_NVAR(&_13$$12);
						object_init_ex(&_13$$12, phalcon_config_configfactory_ce);
						if (zephir_has_constructor(&_13$$12 TSRMLS_CC)) {
							ZEPHIR_CALL_METHOD(NULL, &_13$$12, "__construct", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_14$$12, &_13$$12, "load", &_6, 152, &configName);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(NULL, this_ptr, "internalmerge", &_7, 11, &_14$$12);
						zephir_check_call_status();
						continue;
					}
					ZEPHIR_INIT_NVAR(&_15$$11);
					zephir_create_array(&_15$$11, 2, 0 TSRMLS_CC);
					zephir_array_update_string(&_15$$11, SL("filePath"), &configName, PH_COPY | PH_SEPARATE);
					zephir_array_update_string(&_15$$11, SL("adapter"), &defaultAdapter, PH_COPY | PH_SEPARATE);
					ZEPHIR_CPY_WRT(&configInstance, &_15$$11);
				} else if (!(zephir_array_isset_string(&configInstance, SL("adapter")))) {
					zephir_array_update_string(&configInstance, SL("adapter"), &defaultAdapter, PH_COPY | PH_SEPARATE);
				}
				zephir_array_fetch_string(&_16$$10, &configInstance, SL("adapter"), PH_NOISY | PH_READONLY, "phalcon/Config/Adapter/Grouped.zep", 104 TSRMLS_CC);
				if (ZEPHIR_IS_STRING_IDENTICAL(&_16$$10, "array")) {
					if (UNEXPECTED(!(zephir_array_isset_string(&configInstance, SL("config"))))) {
						ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_factory_exception_ce, "To use 'array' adapter you have to specify the 'config' as an array.", "phalcon/Config/Adapter/Grouped.zep", 108);
						return;
					}
					ZEPHIR_OBS_NVAR(&configArray);
					zephir_array_fetch_string(&configArray, &configInstance, SL("config"), PH_NOISY, "phalcon/Config/Adapter/Grouped.zep", 111 TSRMLS_CC);
					ZEPHIR_INIT_NVAR(&configInstance);
					object_init_ex(&configInstance, phalcon_config_ce);
					ZEPHIR_CALL_METHOD(NULL, &configInstance, "__construct", &_10, 8, &configArray);
					zephir_check_call_status();
				} else {
					ZEPHIR_INIT_NVAR(&_17$$16);
					object_init_ex(&_17$$16, phalcon_config_configfactory_ce);
					if (zephir_has_constructor(&_17$$16 TSRMLS_CC)) {
						ZEPHIR_CALL_METHOD(NULL, &_17$$16, "__construct", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_18$$16, &_17$$16, "load", &_6, 152, &configInstance);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&configInstance, &_18$$16);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "internalmerge", &_7, 11, &configInstance);
				zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &arrayConfig, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&configName);
	ZEPHIR_MM_RESTORE();

}

