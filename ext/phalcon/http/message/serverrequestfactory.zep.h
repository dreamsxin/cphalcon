
extern zend_class_entry *phalcon_http_message_serverrequestfactory_ce;

ZEPHIR_INIT_CLASS(Phalcon_Http_Message_ServerRequestFactory);

PHP_METHOD(Phalcon_Http_Message_ServerRequestFactory, createServerRequest);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_http_message_serverrequestfactory_createserverrequest, 0, 2, Psr\\Http\\Message\\ServerRequestInterface, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_http_message_serverrequestfactory_createserverrequest, 0, 2, IS_OBJECT, "Psr\\Http\\Message\\ServerRequestInterface", 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
	ZEND_ARG_INFO(0, uri)
	ZEND_ARG_ARRAY_INFO(0, serverParams, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_http_message_serverrequestfactory_method_entry) {
	PHP_ME(Phalcon_Http_Message_ServerRequestFactory, createServerRequest, arginfo_phalcon_http_message_serverrequestfactory_createserverrequest, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
