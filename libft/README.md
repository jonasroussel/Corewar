# 42-libft

## Defines
Name      | Value      |
----------|------------|
BUFF_SIZE | `1024`     |
SPLITTER  | `\n`       |
TRUE      | `1`        |
FALSE     | `0`        |

## Typedefs
Name   | Link            |
-------|-----------------|
t_byte | `unsigned char` |
t_bool | `unsigned char` |
t_list | `struct s_list` |

## Structures
Name   | Vars                                                      |
-------|-----------------------------------------------------------|
s_list | `void *content`<br>`size_t size`<br>`struct s_list *next` |

## Functions

### Memory
Function    | Prototype                                                                                  |
------------|--------------------------------------------------------------------------------------------|
ft_memset   | `void *ft_memset(void *mem, const t_byte byte, const size_t size)`                         |
ft_memput   | `void	*ft_memput(void *mem, const intmax_t data, const uint8_t size, const size_t amount)` |
ft_bzero    | `void ft_bzero(void *mem, const size_t size)`                                              |
ft_memcpy   | `void *(void *dest, const void *src, const size_t size)`                                   |
ft_memccpy  | `void *ft_memccpy(void *dest, const void *src, const t_byte byte, const size_t size)`      |
ft_memchr   | `void *ft_memchr(void *mem, const t_byte byte, const size_t size)`                         |
ft_memcmp   | `int ft_memcmp(const void *m1, const void *m2, const size_t size)`                         |
ft_memalloc | `void *ft_memalloc(const size_t size)`                                                     |
ft_memdel   | `void ft_memdel(void **ptr)`                                                               |

### String
Function       | Prototype                                                                       |
---------------|---------------------------------------------------------------------------------|
ft_strlen      | `size_t ft_strlen(const char *str)`                                             |
ft_strdup      | `char *ft_strdup(const char *str)`                                              |
ft_strcpy      | `char *ft_strcpy(char *dest, const char *src)`                                  |
ft_strncpy     | `char *ft_strncpy(char *dest, const char *src, const size_t size)`              |
ft_strcat      | `char *ft_strcat(char *dest, const char *src)`                                  |
ft_strncat     | `char *ft_strncat(char *dest, const char *src, const size_t size)`              |
ft_strchr      | `char *ft_strchr(const char *str, const char c)`                                |
ft_strrchr     | `char *ft_strrchr(const char *str, const char c)`                               |
ft_strstr      | `char *ft_strstr(const char *str, const char *search)`                          |
ft_strnstr     | `char *ft_strnstr(const char *str, const char *search, const size_t size)`      |
ft_strcmp      | `int ft_strcmp(const char *s1, const char *s2)`                                 |
ft_strncmp     | `int ft_strncmp(const char *s1, const char *s2, const size_t size)`             |
ft_strnew      | `char *ft_strnew(const size_t size)`                                            |
ft_strdel      | `void ft_strdel(char **ptr)`                                                    |
ft_strclr      | `void ft_strclr(char *str)`                                                     |
ft_striter     | `void ft_striter(char *str, void (*f)(char *))`                                 |
ft_strsub      | `char *ft_strsub(const char *str, const unsigned int start, const size_t size)` |
ft_strjoin     | `char *ft_strjoin(const char *s1, const char *s2)`                              |
ft_strtrim     | `char *ft_strtrim(const char *str)`                                             |
ft_strsplit    | `char **ft_strsplit(const char *str, const char c)`                             |
ft_strsplitdel | `void ft_strsplitdel(char ***split)`                                            |
ft_strupper    | `void ft_strupper(char *str)`                                                   |
ft_strlower    | `void ft_strlower(char *str)`                                                   |
ft_strcap      | `void ft_strcap(char *str)`                                                     |
ft_strreplace  | `void ft_strreplace(char *str, const char c, const char r)`                     |

### List
Function       | Prototype                                                                |
---------------|--------------------------------------------------------------------------|
ft_lstnew      | `t_list *ft_lstnew(const void *content, const size_t size)`              |
ft_lstfdel     | `void ft_lstfdel(t_list **plist)`                                        |
ft_lstdel      | `void ft_lstdel(t_list **plist)`                                         |
ft_lstlen      | `size_t ft_lstlen(t_list *list)`                                         |
ft_lstadd      | `void ft_lstadd(t_list **plist, t_list *new)`                            |
ft_lstaddi     | `void ft_lstaddi(t_list **plist, t_list *new, const unsigned int index)` |
ft_lstpush     | `void ft_lstpush(t_list **plist, t_list *new)`                           |
ft_lstremove   | `void ft_lstremove(t_list **plist, t_list *node)`                        |
ft_lstctn      | `t_bool ft_lstctn(t_list *list, void *content)`                          |
ft_lstget      | `t_list *ft_lstget(t_list *list, const unsigned int index)`              |
ft_lstiter     | `void ft_lstiter(t_list *list, void (*f)(t_list *node))`                 |

### Writers
Function  | Prototype                                                            |
----------|----------------------------------------------------------------------|
ft_printf | `int ft_printf(const char *format, ...)`                             |

### Testers
Function    | Prototype                                           |
------------|-----------------------------------------------------|
ft_isblank  | `t_bool ft_isblank(const char c)`                   |
ft_islower  | `t_bool ft_islower(const char c)`                   |
ft_isupper  | `t_bool ft_isupper(const char c)`                   |
ft_isalpha  | `t_bool ft_isalpha(const char c)`                   |
ft_isdigit  | `t_bool ft_isdigit(const char c)`                   |
ft_isalnum  | `t_bool ft_isalnum(const char c)`                   |
ft_isascii  | `t_bool ft_isascii(const char c)`                   |
ft_isprint  | `t_bool ft_isprint(const char c)`                   |
ft_isnumber | `t_bool ft_isnumber(const char *str)`               |
ft_equal    | `t_bool ft_equal(const char *s1, const char *s2)`   |

### Maths
Function | Prototype                               |
---------|-----------------------------------------|
ft_pow   | `double ft_pow(double nbr, uint_8 pow)` |

### Converters
Function      | Prototype                                                |
--------------|----------------------------------------------------------|
ft_atol       | `long ft_atol(const char *str)`                          |
ft_ltoa       | `char *ft_ltoa(intmax_t nbr)`                            |
ft_ultoa      | `char *ft_ultoa(uintmax_t nbr)`                          |
ft_ultoa_base | `char *ft_ultoa_base(uintmax_t nbr, const uint8_t base)` |
ft_toupper    | `int ft_toupper(int c)`                                  |
ft_tolower    | `int ft_tolower(int c)`                                  |

### Readers
Function | Prototype                               |
---------|-----------------------------------------|
ft_gnl   | `int ft_gnl(const int fd, char **line)` |
