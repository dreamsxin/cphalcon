
extern zend_class_entry *phalcon_html_interfaces_attributesinterface_ce;

ZEPHIR_INIT_CLASS(Phalcon_Html_Interfaces_AttributesInterface);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_html_interfaces_attributesinterface_getattributes, 0, 0, Phalcon\\Html\\Attributes, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_html_interfaces_attributesinterface_getattributes, 0, 0, IS_OBJECT, "Phalcon\\Html\\Attributes", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_phalcon_html_interfaces_attributesinterface_setattributes, 0, 1, Phalcon\\Html\\Interfaces\\AttributesInterface, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_html_interfaces_attributesinterface_setattributes, 0, 1, IS_OBJECT, "Phalcon\\Html\\Interfaces\\AttributesInterface", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, attributes, Phalcon\\Html\\Attributes, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_html_interfaces_attributesinterface_method_entry) {
	PHP_ABSTRACT_ME(Phalcon_Html_Interfaces_AttributesInterface, getAttributes, arginfo_phalcon_html_interfaces_attributesinterface_getattributes)
	PHP_ABSTRACT_ME(Phalcon_Html_Interfaces_AttributesInterface, setAttributes, arginfo_phalcon_html_interfaces_attributesinterface_setattributes)
	PHP_FE_END
};
