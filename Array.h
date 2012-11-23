#ifndef ARRAY_H_
#define ARRAY_H_

#include <AssertException.h>
#include <IndexOutOfBoundsException.h>
#include <IllegalArgumentException.h>
#include <Memory.h>

#ifdef WINVER
  // desactivation de certains avertissements de visual studio
  #pragma warning( disable:4800 )
#endif

#ifdef DEBUG
// A low overhead dynamic array allowing debugging
template<class TData> class ArrayDebugger
{
private:
  TData * buffer;
  int size;
public:
  ArrayDebugger() :
    buffer(NULL), size(0)
  {
    ;
  }
  void SetBuffer(TData * _buffer, int _size)
  {
    buffer = _buffer;
    size = _size;
  }
  TData & operator[](int index)
  {
    CheckBounds_Debug(index, 0, size - 1);
    ASSERT(buffer != NULL );
    return buffer[index];
  }
  const TData & operator[](int index) const
  {
    CheckBounds_Debug(index, 0, size - 1);
    ASSERT(buffer != NULL );
    return buffer[index];
  }
private:
  void operator=(const ArrayDebugger & ad)
  {
    ; // operation interdite
  }
};

class ReadOnlyInteger
{
private:
  int size;
public:
  ReadOnlyInteger() :
    size(0)
  {
    ;
  }
  void SetValue(int _size)
  {
    size = _size;
  }
  operator int() const
  {
    return this->size;
  }
};
#endif

/** @defgroup util Les utilitaires */

/** une classe tableau dynamique g�n�rique
 * @ingroup util */
template<class TData> class Array
{
public:
  /** Constantes permettant d'indiquer s'il faut pr�server le contenu */
  enum ContentPreservation
  {
    DO_NOT_PRESERVE_CONTENT,
    PRESERVE_CONTENT
  };
  /** Constantes permettant d'indiquer s'il faut r�duire l'utilisation de la m�moire */
  enum MemoryReduction
  {
    DO_NOT_REDUCE_MEMORY,
    REDUCE_MEMORY
  };
public:
  /** @internal */
  TData * buffer;
  /** @internal */
  unsigned int bufferSize;
  /** @internal  */
  unsigned int bufferReservedSize;
  /** @internal  */
  MemoryReduction defaultMemoryStrategy;
public:
  /** constructeur */
  Array() :
    buffer(NULL), bufferSize(0), bufferReservedSize(0),
        defaultMemoryStrategy(DO_NOT_REDUCE_MEMORY)
  {
    Update(); // on initialize size et data
  }
  /** constructeur de recopie */
  Array(const Array<TData> & a) :
    buffer(NULL), bufferSize(0), bufferReservedSize(0),
        defaultMemoryStrategy(DO_NOT_REDUCE_MEMORY)
  {
    Copy(a);
  }
  /** destructeur */
  ~Array()
  {
    Clear(REDUCE_MEMORY);
    Update();
  }
  /** indique la strat�gie de gestion de la m�moire par d�faut */
  void SetDefaultMemoryStrategy(const MemoryReduction mr)
  {
    defaultMemoryStrategy = mr;
  }
  /** permet d'obtenir la strat�gie de gestion de la m�moire par defaut */
  MemoryReduction GetDefaultMemoryStrategy() const
  {
    return defaultMemoryStrategy;
  }
  /** redimensionne un tableau : change lenombre d'�l�ments du tableau
   * @param newSize : le nombre d'�l�ments � la fin de la fonction
   * @param preserveContent : indique s'il faut pr�server le contenu lors du redimensionnement
   */
  inline void Resize(const int newSize,
      const ContentPreservation preserveContent = PRESERVE_CONTENT)
  {
    EnsureNonNegative(newSize);
    Reserve(newSize, preserveContent);
    bufferSize = newSize;
    Update();
  }
  /** R�serve de l'espace m�moire associ� � un tableau. Le nombre d'�l�ments du tableau n'est pas modifi� si newReservedSize >= size */
  inline void Reserve(const int newReservedSize,
      const ContentPreservation preserveContent = PRESERVE_CONTENT)
  {
    Reserve(newReservedSize, preserveContent, defaultMemoryStrategy);
  }
  /** R�serve de l'espace m�moire associ� � un tableau. Le nombre d'�l�ments du tableau n'est pas modifi� si newReservedSize >= size */
  inline void Reserve(const unsigned int newReservedSize,
      const ContentPreservation preserveContent,
      const MemoryReduction reduceMemory)
  {
    EnsureNonNegative(newReservedSize);

    if (newReservedSize == bufferReservedSize)
      return;

    if ( (newReservedSize > bufferReservedSize) ||((newReservedSize
        < bufferReservedSize) && (reduceMemory == REDUCE_MEMORY)))
    {
      buffer = ReallocMemory<TData>(buffer, bufferReservedSize,
          newReservedSize, preserveContent);
      bufferReservedSize = newReservedSize;

      if (bufferSize > newReservedSize)
        bufferSize = newReservedSize;
    }
    Update();
  }
  /** Ajoute un �l�ment au d�but du tableau */
  inline void PushFront(const TData & value)
  {
    insert( 0, value );
  }
  /** Ajoute un �l�ment � la fin du tableau */
  inline void PushBack(const TData & value)
  {
    if (bufferSize == bufferReservedSize)
    {
      Reserve(bufferReservedSize + 16);
    }
    buffer[bufferSize] = value;
    bufferSize++;
    Update();
  }
  /** Supprime l'�l�ment n�index du tableau */
  inline void Erase(const int index)
  {
    CheckBounds_Debug(index, 0, bufferSize - 1);
    memCopy(buffer + index + 1, buffer + index, bufferSize - index - 1);
    bufferSize--;
    Reserve(bufferSize);
    Update();
  }
  /** Insert un �l�ment value dans le tableau � la position index */
  inline void Insert(const int index, const TData value)
  {
    CheckBounds_Debug(index, 0, bufferSize);
    if (bufferSize + 1< bufferReservedSize)
      Reserve(bufferReservedSize + 16);
    memCopy(buffer + index, buffer + index + 1, bufferSize - index );
    buffer[index] = value;
    bufferSize++;
    Update();
  }
  /** Vide un tableau : size = 0 */
  inline void Clear(const MemoryReduction reduceMemory = DO_NOT_REDUCE_MEMORY)
  {
    Reserve(0, DO_NOT_PRESERVE_CONTENT, reduceMemory);
    bufferSize = 0;
    Update();
  }
  /** Initialise tous les �l�ments du tableau � la valeur value */
  inline void Fill(const TData & value)
  {
    for (int i = bufferSize - 1; i >= 0; --i )
      data[i] = value;
  }
  /** Copie le contenu du tableau a dans le tableau */
  void Copy(const Array<TData> & a)
  {
    Resize(a.bufferSize);
    MemCopy<TData>(a.buffer, buffer, bufferSize);
    Update();
  }
  /** op�rateur d'affectation */
  Array<TData> & operator=(const Array<TData> & a)
  {
    Copy(a);
    return *this;
  }

#ifdef DEBUG
public:
  ArrayDebugger<TData> data;
  ReadOnlyInteger size;
public:
  inline void Update()
  {
    data.SetBuffer(buffer, bufferSize);
    size.SetValue(bufferSize);
  }
#else
public:
  /** Les �l�ments du tableau */
  TData * data;
  /** Le nombre d'�l�ments du tableau */
  int size;
public:
  /** @internal Mise � jours des informations */
  inline void Update()
  {
    size = bufferSize;
    data = buffer;
  }
#endif

};

#endif
