#ifndef IllegalArgumentException_h
#define IllegalArgumentException_h

#include <Exception.h>

/** Une excpetion lev�e lorsqu'un argument ill�gal est transmis � une fonction
 * @ingroup exception */
class IllegalArgumentException : public Exception
{
public:
	/** Constructeur */
	IllegalArgumentException(const wxString & msg);
};

/** \def EnsureNonNegative(value) L�ve une exception IllegalArgumentException si value < 0 */
#define EnsureNonNegative( Value ) \
 if (Value < 0) \
 { \
	IllegalArgumentException __e( wxT(#Value " must be a non negative value")); \
	RaiseException(__e); \
 }

/** \def EnsurePositive(value) L�ve une exception IllegalArgumentException si value <= 0 */
#define EnsurePositive( Value ) \
 if (Value <= 0) \
 { \
	IllegalArgumentException __e( wxT(#Value " must be a strictly positive value")); \
	RaiseException(__e); \
 }

/** \def EnsureValid(object) L�ve une exception IllegalArgumentException si object.valid() est faux */
#define EnsureValid( Object ) \
 if (!(Object.valid())) \
 { \
	IllegalArgumentException __e( wxT(#Object " must be valid")); \
	RaiseException(__e); \
 }

/** \def CheckArgument(test,msg) L�ve une exception IllegalArgumentException avec le message msg si la condition test est fausse */
#define CheckArgument( test, msg ) \
 if (!(test)) \
 { \
	IllegalArgumentException __e(msg); \
	RaiseException(__e); \
 }

#endif
