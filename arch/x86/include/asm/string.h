#ifndef _STRING_H_
#define _STRING_H_

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

extern char * strerror(int errno);

/*
 * Este Include-String define todas las funciones de string como funciones
 * integras. Usa gcc. Tambien asumimos el es=ds=Espacio de datos, esto 
 * Deberia ser normal. La mayor parte de las funciones de string son dificiles
 * de entender y estan optimizadas a mano, Mirar especialmente strtok,strstr,str[c]spn.
 * Estas deberian funcionar, pero no son fáciles de entender. Todas estan hechas
 * Dentro del juego de registros, haciendo las funciones rápidas y limpias.
 * Las funciones de String han sido usadas en todas partes. haciendo el codigo
 * Ligeramente confuso:-)
 */
 
 /*
  * Copia la cadena apuntado por src a la cadena apuntada por dest
  * incluyendo el caracter nulo
  */
static inline char * strcpy(char * dest,const char *src)
{
__asm__ __volatile__ (
        "cld\n"
	"1:\tlodsb\n\t"
	"stosb\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b"
	::"S" (src),"D" (dest):"memory");
  return dest;	
}

/*
 * Copia no mas de n caracteres(count) de la cadena src a la cadena
 * dest. Si la cadena src es menor que n, añade caracteres nulos a 
 * dest. No añade el caracter nulo al final de la cadena copiada
 */
static inline char * strncpy(char * dest,const char *src,int count)
{
  __asm__ __volatile__( 
	"cld\n"
	"1:\tdecl %2\n\t"
	"js 2f\n\t"
	"lodsb\n\t"
	"stosb\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b\n\t"
	"rep\n\t"
	"stosb\n"
	"2:"
	::"S" (src),"D" (dest),"c" (count):"memory");
  return dest;
}

/*
 * Añade una copia de la cadena apuntada por src al final de la 
 * cadena apuntada por dest(incluyendo el caracter nulo). El
 * Caracter inicial de src sobreescribe el caracter nulo final de
 * dest.
 */
static inline char * strcat(char * dest,const char * src)
{
  __asm__ __volatile__( 
        "cld\n\t"
	"repne\n\t"
	"scasb\n\t"
	"decl %1\n"
	"1:\tlodsb\n\t"
	"stosb\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b"
	::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff):"memory");
  return dest;
}

/*
 * Añade no mas de N Caracteres(count, Un caracter nulo y los demás 
 * no son añadidos) de la cadena apuntada por src al final de la 
 * cadena apuntada por dest. El Caracter inicial de src sobreescribe 
 * el caracter nulo final de dest.
 */
static inline char * strncat(char * dest,const char * src,int count)
{
  __asm__ __volatile__(
	"cld\n\t"
	"repne\n\t"
	"scasb\n\t"
	"decl %1\n\t"
	"movl %4,%3\n"
	"1:\tdecl %3\n\t"
	"js 2f\n\t"
	"lodsb\n\t"
	"stosb\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b\n"
	"2:\txorl %2,%2\n\t"
	"stosb"
	::"S" (src),"D" (dest),"a" (0),"c" (0xffffffff),"g" (count)
	:"memory");
  return dest;
}

/*
 * Compara la cadena apuntada por cs con la cadena apuntada por ct
 * La funcion retorna mayor,igual o menor que 0 segun si la cadena
 * cs es mayor, igual o menor que ct
 */
static inline int strcmp(const char * cs,const char * ct)
{
  register int __res;
  __asm__ __volatile__(
        "cld\n"
	"1:\tlodsb\n\t"
	"scasb\n\t"
	"jne 2f\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b\n\t"
	"xorl %%eax,%%eax\n\t"
	"jmp 3f\n"
	"2:\tmovl $1,%%eax\n\t"
	"jl 3f\n\t"
	"negl %%eax\n"
	"3:"
	:"=a" (__res):"D" (cs),"S" (ct):"memory");
  return __res;
}

/*
 * Compara no mas de n caracteres(count, Caracteres posteriores al caracter 
 * nulo no se contemplan).
 * La funcion retorna mayor,igual o menor que 0 segun si la cadena
 * cs es mayor, igual o menor que ct
 */
static inline int strncmp(const char * cs,const char * ct,int count)
{
  register int __res;
  __asm__ __volatile__(
        "cld\n"
	"1:\tdecl %3\n\t"
	"js 2f\n\t"
	"lodsb\n\t"
	"scasb\n\t"
	"jne 3f\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b\n"
	"2:\txorl %%eax,%%eax\n\t"
	"jmp 4f\n"
	"3:\tmovl $1,%%eax\n\t"
	"jl 4f\n\t"
	"negl %%eax\n"
	"4:"
	:"=a" (__res):"D" (cs),"S" (ct),"c" (count):"memory");
  return __res;
}

/*
 * Localiza la primera aparicion de c en la cadena apuntada por s
 * incluyendo el caracter nulo. La función retorna un puntero a 
 * partir del caracter encontrado. si no se encuentra el caracter
 * devuelve un puntero null
 */
static inline char * strchr(const char * s,char c)
{
  register int __res;
  __asm__ __volatile__(
  	"cld\n\t"
	"movb %%al,%%ah\n"
	"1:\tlodsb\n\t"
	"cmpb %%ah,%%al\n\t"
	"je 2f\n\t"
	"testb %%al,%%al\n\t"
	"jne 1b\n\t"
	"movl $1,%1\n"
	"2:\tmovl %1,%0\n\t"
	"decl %0"
	:"=a" (__res):"S" (s),"0" (c):"memory");
  return (char *)__res;
}

/*
 * Localiza la última aparicion de c en la cadena apuntada por s
 * incluyendo el caracter nulo. La función retorna un puntero a 
 * partir del caracter encontrado. si no se encuentra el caracter
 * devuelve un puntero null
 */
static inline char * strrchr(const char * s,char c)
{
  register char * __res;
  __asm__ __volatile__(
  	"cld\n\t"
	"movb %%al,%%ah\n"
	"1:\tlodsb\n\t"
	"cmpb %%ah,%%al\n\t"
	"jne 2f\n\t"
	"movl %%esi,%0\n\t"
	"decl %0\n"
	"2:\ttestb %%al,%%al\n\t"
	"jne 1b"
	:"=d" (__res):"0" (0),"S" (s),"a" (c):"memory");
  return __res;
}

/*
 * Calcula el numero de caracteres de una subcadena inicial apuntada 
 * por cs que consiste en todos los caracteres formados por ct
 */
static inline int strspn(const char * cs, const char * ct)
{
  register char * __res;
  __asm__ __volatile__(
  	"cld\n\t"
	"movl %4,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"
	"movl %%ecx,%%edx\n"
	"1:\tlodsb\n\t"
	"testb %%al,%%al\n\t"
	"je 2f\n\t"
	"movl %4,%%edi\n\t"
	"movl %%edx,%%ecx\n\t"
	"repne\n\t"
	"scasb\n\t"
	"je 1b\n"
	"2:\tdecl %0"
	:"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
	:"memory");
  return (int)*__res;
}

/*
 * Cuenta el numero de caracteres de una subcadena inicia cs que 
 * no tenga ninguno de los caracteres en la cadena apuntada por ct
 */
static inline int strcspn(const char * cs, const char * ct)
{
  register char * __res;
  __asm__ __volatile__(
	"cld\n\t"
	"movl %4,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"
	"movl %%ecx,%%edx\n"
	"1:\tlodsb\n\t"
	"testb %%al,%%al\n\t"
	"je 2f\n\t"
	"movl %4,%%edi\n\t"
	"movl %%edx,%%ecx\n\t"
	"repne\n\t"
	"scasb\n\t"
	"jne 1b\n"
	"2:\tdecl %0"
	:"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
	:"memory");
  return (int)*__res;
}

/*
 * Localiza la primera posición de la cadena apuntad por cs de
 * Cualquier carácter de la cadena apuntada por s2
 */
static inline char * strpbrk(const char * cs,const char * ct)
{
  register char * __res ;
  __asm__ __volatile__(
        "cld\n\t"
	"movl %4,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"
	"movl %%ecx,%%edx\n"
	"1:\tlodsb\n\t"
	"testb %%al,%%al\n\t"
	"je 2f\n\t"
	"movl %4,%%edi\n\t"
	"movl %%edx,%%ecx\n\t"
	"repne\n\t"
	"scasb\n\t"
	"jne 1b\n\t"
	"decl %0\n\t"
	"jmp 3f\n"
	"2:\txorl %0,%0\n"
	"3:"
	:"=S" (__res):"a" (0),"c" (0xffffffff),"0" (cs),"g" (ct)
	:"memory");
  return __res;
}

/*
 * Localiza la primera aparicion en la cadena apuntada por cs
 * de la secuencia de caracteres(excluyendo el caracter nulo
 * en la cadena ct
 */
static inline char * strstr(const char * cs,const char * ct)
{
  register char * __res;
  __asm__ __volatile__(
        "cld\n\t" 
	"movl %4,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"	/* NOTE! This also sets Z if searchstring='' */
	"movl %%ecx,%%edx\n"
	"1:\tmovl %4,%%edi\n\t"
	"movl %%esi,%%eax\n\t"
	"movl %%edx,%%ecx\n\t"
	"repe\n\t"
	"cmpsb\n\t"
	"je 2f\n\t"		/* also works for empty string, see above */
	"xchgl %%eax,%%esi\n\t"
	"incl %%esi\n\t"
	"cmpb $0,-1(%%eax)\n\t"
	"jne 1b\n\t"
	"xorl %%eax,%%eax\n\t"
	"2:"
	:"=a" (__res):"0" (0),"c" (0xffffffff),"S" (cs),"g" (ct)
	:"memory");
  return __res;
}

/*
 * Calcula el número de caracteres de la cadena apuntada por s
 * La función retorna el número de caracteres hasta el caracter 
 * nulo 
 */
static inline int strlen(const char * s)
{
  register int __res;
  __asm__ __volatile__(
  	"cld\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %0\n\t"
	"decl %0"
	:"=c" (__res):"D" (s),"a" (0),"0" (0xffffffff):"memory");
  return __res;
}

static char * ___strtok;

/*
 * Rompe la cadena s en segmentos o tokens, el proceso destruye s
 * la forma de romper la cadena depende de ct, que contiene los 
 * Delimitadores /se debe arreglar)
 */
static inline char * strtok(char * s,const char * ct)
{
  register char * __res;
  __asm__ __volatile__(
  	"testl %1,%1\n\t"
	"jne 1f\n\t"
	"testl %0,%0\n\t"
	"je 8f\n\t"
	"movl %0,%1\n"
	"1:\txorl %0,%0\n\t"
	"movl $-1,%%ecx\n\t"
	"xorl %%eax,%%eax\n\t"
	"cld\n\t"
	"movl %4,%%edi\n\t"
	"repne\n\t"
	"scasb\n\t"
	"notl %%ecx\n\t"
	"decl %%ecx\n\t"
	"je 7f\n\t"			/* empty delimeter-string */
	"movl %%ecx,%%edx\n"
	"2:\tlodsb\n\t"
	"testb %%al,%%al\n\t"
	"je 7f\n\t"
	"movl %4,%%edi\n\t"
	"movl %%edx,%%ecx\n\t"
	"repne\n\t"
	"scasb\n\t"
	"je 2b\n\t"
	"decl %1\n\t"
	"cmpb $0,(%1)\n\t"
	"je 7f\n\t"
	"movl %1,%0\n"
	"3:\tlodsb\n\t"
	"testb %%al,%%al\n\t"
	"je 5f\n\t"
	"movl %4,%%edi\n\t"
	"movl %%edx,%%ecx\n\t"
	"repne\n\t"
	"scasb\n\t"
	"jne 3b\n\t"
	"decl %1\n\t"
	"cmpb $0,(%1)\n\t"
	"je 5f\n\t"
	"movb $0,(%1)\n\t"
	"incl %1\n\t"
	"jmp 6f\n"
	"5:\txorl %1,%1\n"
	"6:\tcmpb $0,(%0)\n\t"
	"jne 7f\n\t"
	"xorl %0,%0\n"
	"7:\ttestl %0,%0\n\t"
	"jne 8f\n\t"
	"movl %0,%1\n"
	"8:"
	:"=b" (__res),"=S" (___strtok)
	:"0" (___strtok),"1" (s),"g" (ct)
	:"memory");
  return __res;
}

/*
 * Copia los n primeros caracteres apuntados por src a dest.
 * la funcion retorna el valor de dest
 */
static inline void * memcpy(void * dest,const void * src, int n)
{
  __asm__ __volatile__(
	"cld\n\t"
	"rep\n\t"
	"movsb"
	::"c" (n),"S" (src),"D" (dest)
	:"memory");
  return dest;
}

/*
 * Copia los n primeros caracteres apuntados por src a dest.
 * Sin embargo se asegura que no estén superpuestos
 * La función retorna el valor de dest
 */
static inline void * memmove(void * dest,const void * src, int n)
{
  if (dest<src)
    __asm__ __volatile__(
          "cld\n\t"
	  "rep\n\t"
	  "movsb"
	  ::"c" (n),"S" (src),"D" (dest)
	  :"memory");
  else
    __asm__ __volatile__(
  	  "std\n\t"
	  "rep\n\t"
	  "movsb"
	  ::"c" (n),"S" (src+n-1),"D" (dest+n-1)
	  :"memory");
  return dest;
}

/*
 * Compara los N(count) primeros caracteres de cs (como unsigned char) 
 * con los N(count) primeros caracteres de ct (como unsigned char) 
 */
static inline int memcmp(const void * cs,const void * ct,int count)
{
  register int __res;
  __asm__ __volatile__(
  	"cld\n\t"
	"repe\n\t"
	"cmpsb\n\t"
	"je 1f\n\t"
	"movl $1,%%eax\n\t"
	"jl 1f\n\t"
	"negl %%eax\n"
	"1:"
	:"=a" (__res):"0" (0),"D" (cs),"S" (ct),"c" (count)
	:"memory");
  return __res;
}

/*
 * Localiza la primera aparición del caracter c, en los primeros
 * N(count) caracteres de cs(ambos interpretados como unsigned char
 */
static inline void * memchr(const void * cs,char c,int count)
{
  register void * __res;
  if (!count)
	return NULL;
  __asm__ __volatile__(
  	"cld\n\t"
	"repne\n\t"
	"scasb\n\t"
	"je 1f\n\t"
	"movl $1,%0\n"
	"1:\tdecl %0"
	:"=D" (__res):"a" (c),"D" (cs),"c" (count)
	:"memory");
  return __res;
}  

/*
 * Copia el valor de c (convertido a unsigned char) en cada uno
 * de los primeros N(count) caracteres de s 
 * retorna el valor de s
 */
static inline void * memset(void * s,char c,int count)
{
  __asm__ __volatile__(
  	"cld\n\t"
	"rep\n\t"
	"stosb"
	::"a" (c),"D" (s),"c" (count)
	:"memory");
  return s;
}

#endif /* _STRING_H_ */


