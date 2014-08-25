#ifndef ORG_OPENSPLICE_CORE_EXCEPTION_HELPER_HPP_
#define ORG_OPENSPLICE_CORE_EXCEPTION_HELPER_HPP_

#include <string>
#include <org/opensplice/core/config.hpp>

namespace org { namespace opensplice { namespace core {

/**
* Produce a string suitable for populating an exception 'what' field.
* E.g:
* @code
throw dds::core::NullReferenceError(
                    org::opensplice::core::exception_helper(
                        OSPL_CONTEXT_LITERAL(
                            "dds::core::NullReferenceError : Unable to create ContentFilteredTopic. "
                            "Nil return from ::create_contentfilteredtopic"));
@endcode
* @param message A description of what went wrong / where we are
* @param ospl_error_info Should we try and include TSS OS_REPORT info about the
* last previous reported error condition.
* @param stack_trace Should we try and include a stack trace
* @return A string fit for passing to an exception constructor
*/
OSPL_ISOCPP_IMPL_API std::string exception_helper(const char* message,
                                                bool ospl_error_info = true,
                                                bool stack_trace = true);

/**
* Produce a string suitable for populating an exception 'what' field.
* E.g:
* @code
std::string message = "dds::core::InvalidDataError";
message += OSPL_CONTEXT_LITERAL("");
message += " some more information"
throw dds::core::NullReferenceError(
                    org::opensplice::core::exception_helper(message, false));
@endcode
* The above example show's use to produce an arbitrary-ish string. Note the
* non-default false second ospl_error_info argument that switches off the
* inclusion of the preceding erro info. This is appropriate if the error
* has not resulted from a 'DCPS' call.
* @param message A description of what went wrong / where we are
* @param ospl_error_info Should we try and include TSS OS_REPORT info about the
* last previous reported error condition.
* @param stack_trace Should we try and include a stack trace
* @return A string fit for passing to an exception constructor
*/
OSPL_ISOCPP_IMPL_API std::string exception_helper(const std::string& message,
                                                 bool ospl_error_info = true,
                                                 bool stack_trace = true);

/**
* Turn an old school return code into it's string form, e.g.: DDS::RETCODE_OK,
* DDS::RETCODE_ALREADY_DELETED etc..
* @param code The return code to be demystified.
* @return A string corresponding to the code
*/
OSPL_ISOCPP_IMPL_API std::string dds_return_code_to_string(DDS::ReturnCode_t code);

/**
* Check an old school return code and throw the new PSM execption if
* appropriate. E.g.: check_and_throw(result, OSPL_CONTEXT_LITERAL("Tried to create a topic"));
* @param code The value returned from the DCPS API method.
* @param context Some sort of clue to the receiver about what was
* called or what you were trying to do.
*/
OSPL_ISOCPP_IMPL_API void check_and_throw(DDS::ReturnCode_t code,
                                           const std::string& context = "");

#define OSPL_INT_TO_STRING(n) OSPL_I_TO_STR(n)
#define OSPL_I_TO_STR(n) #n

/* Allegedly __FUNCTION__ has been in VS since 2005 */
#if (defined (__GNUC__) && defined (__FUNCTION__)) || defined (_MSC_VER)
#   define OSPL_CONTEXT_LITERAL(foo) foo " in function " __FUNCTION__ "() at " __FILE__ ":" OSPL_INT_TO_STRING(__LINE__)
#else
/**
* Platform independentish 'where are we now' string literal macro
* @param foo Should produce "foo in my_func() at Bar.cpp:1234" with g++. Hopefully.
*/
#   define OSPL_CONTEXT_LITERAL(foo) foo " at " __FILE__ ":" OSPL_INT_TO_STRING(__LINE__)
#endif

} } }

#endif /* ORG_OPENSPLICE_CORE_EXCEPTION_HELPER_HPP_ */
