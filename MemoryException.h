#ifndef MemoryException_h
#define MemoryException_h

#include <Exception.h>

/** Une exception lev�e lorsque des probl�mes d'allocation m�moire surviennent
 * @ingroup exception */
class MemoryException : public Exception
{
public:
	/** Le constructeur */
	MemoryException(const wxString & msg);
};

#endif
