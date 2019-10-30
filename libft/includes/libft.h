/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:42:52 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/30 15:51:39 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define EXIT 1
# define EASY 0
# define LEFT 1
# define RIGHT 2
# define BOTH 3
# define BUFF_SIZE 100
# define BLOCK 5000
# define ALL "-+ 0#hlL.123456789*"
# define FLAGS "-+ 0#"
# define MINUS 1u
# define PLUS 2u
# define SPACE 4u
# define ZERO 8u
# define HASH 16u
# define FIELD "hhllL"
# define HFIELD 1u
# define HHFIELD 2u
# define LFIELD 3u
# define LLFIELD 4u
# define LMAJFIELD 5u
# define TYPE "\%cspduoxXb"
# define PERTYPE 0u
# define CTYPE 1u
# define STYPE 2u
# define PTYPE 3u
# define DTYPE 4u
# define UTYPE 5u
# define OTYPE 6u
# define XTYPE 7u
# define XMAJTYPE 8u
# define BTYPE 9u
# define ULLCHAIN "61615590737044764481"
# define HASH_ELEMS_LIMIT 2
# define HASH_COLLISIONS_LIMIT 3
# include <stdarg.h>
# include <stddef.h>
#include <stdio.h>
#define PRINTPOS printf("%s %d", __func__, __LINE__)
#define PRINTPOSN printf("%s %d\n", __func__, __LINE__)
typedef int					(*t_hashfunc)(char *, long);

typedef struct				s_hash_elem
{
	void					*content;
	char					*key;
}							t_hash_elem;

typedef struct				s_hash_tab
{
	long					size;
	long					elems;
	long					collisions;
	long					elems_limit;
	long					collisions_limit;
	t_hashfunc				func;
	void					*array;
}							t_hash_tab;

typedef struct				s_lst
{
	void					*content;
	size_t					content_size;
	struct s_lst			*next;
	struct s_lst			*last;
}							t_lst;

typedef struct				s_gc_list
{
	unsigned				len;
	t_lst					*first;
	t_lst					*last;
}							t_gc_list;

typedef struct				s_arg
{
	unsigned int			flags;
	unsigned long long		min;
	unsigned long long		prec;
	unsigned long long		max;
	unsigned int			field;
	unsigned int			type;
	unsigned int			start;
	char					fill;
	char					*prefix;
}							t_arg;

typedef struct s_buf		t_buf;

typedef int					(*t_f)(t_arg *, t_buf *, va_list);

struct						s_buf
{
	char					*str;
	unsigned long long		pos;
	unsigned long long		size;
	t_f						tab[7];
};

int							add_to_buf(char *str, t_buf *buf);
int							ft_printf(const char *str, ...);
int							ft_fprintf(int fd, const char *str, ...);
int							ft_sprintf(char **res, const char *str, ...);
int							base_func(t_buf *buf, const char *str
	, va_list arg_list);
t_arg						*ft_init(t_buf *buf, t_arg *arg, int opt);
void						*ft_stralloc(char *str);
int							ft_realloc(void **zone, long curr_size
	, long to_add);
unsigned long long			ft_ato_ull(const char *str, int *pos);
int							ft_display(t_buf *buf, int opt);
int							set_arg(t_arg *arg, const char *str, t_buf *buf
	, va_list arg_list);
int							f_s(t_arg *arg, t_buf *buf, va_list arg_list);
int							f_c(t_arg *arg, t_buf *buf, va_list arg_list);
int							f_percent(t_arg *arg, t_buf *buf, va_list arg_list);
int							f_p(t_arg *arg, t_buf *buf, va_list arg_list);
int							f_num_s(t_arg *arg, t_buf *buf, va_list arg_list);
int							f_num_u(t_arg *arg, t_buf *buf, va_list arg_list);
char						*ft_ulltoa(unsigned long long n);
int							ft_itoa_base_u(unsigned long long n, char *base_to
	, t_buf *buf, t_arg *arg);
int							ft_pad(t_arg *arg, t_buf *buf);
char						*ft_stradd(char *sht, char *lng);
char						*ft_stradd_fract(char *sht, char *lng);
char						*ft_strmult(char *sht, char *lng);
char						*ft_strdiv(char **nb, int turns, int len, int pos);
void						*easymalloc(size_t size);
int							ft_abs(int a);
int							ft_atoi(const char *str);
int							ft_atoi_base(char *nbr, char *base_from);
long						ft_atou_mv(char **str, char opt);
void						ft_bzero(void *s, size_t n);
long long int				ft_pow(long long int nb, long long int pow);
int							ft_check_base(char *str, char *base);
char						*ft_convert_base(char *nbr, char *base_from
	, char *base_to);
void						ft_fili(char *file, int line);
void						ft_free(void **match);
void						easyfree(void **match);
int							ft_free_ptr(void **ptr);
int							ft_free_tab(void **tab, size_t len);
void						ft_free_gc(void);
int							ft_isalnum(int c);
int							ft_isalpha(int c);
int							ft_isascii(int c);
int							ft_isdigit(int c);
int							ft_isprint(int c);
int							ft_isspace(int c);
char						*ft_itoa(int n);
char						*ft_itoa_base(long int nb, char *base_to);
int							ft_lstcycle(t_lst *begin);
t_lst						*ft_lstnew(void const *content
	, size_t content_size);
void						ft_lstadd(t_lst **alst, t_lst *newl);
void						ft_lstadd_back(t_lst **alst, t_lst *newl);
t_lst						*ft_lstadd_new(t_lst **alst, void *content
	, int size);
t_lst						*ft_lstpop(t_lst **begin, void *match);
void						ft_lstdel(t_lst **alst
	, void (*del) (void *, size_t));
void						ft_lstdelone(t_lst **alst, void (*del) (void *
	, size_t));
void						ft_lstiter(t_lst *lst, void (*f_i) (t_lst *elem));
t_lst						*ft_lstmap(t_lst *lst, t_lst *(*f_m) (t_lst *elem));
t_lst						*ft_lstfind(t_lst *begin_list, void *match);
int							ft_lst_size(t_lst *begin_list);
void						ft_lst_sort(t_lst **begin_list, int (*f_cmp)());
void						ft_lstclr(t_lst **begin_list);
int							ft_max(int a, int b);
void						*ft_memchr(const void *s, int c, size_t n);
int							ft_memchr_pos(const void *s, int c, size_t n);
void						*ft_memset(void *b, int c, size_t len);
void						ft_memcset(void *o_s, int c, int stop);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						*ft_memccpy(void *dst, const void *src, int c
	, size_t n);
void						*ft_memmove(void *dst, const void *src, size_t len);
void						*ft_memalloc(size_t size);
void						ft_memdel(void **ap);
int							ft_min(int a, int b);
void						ft_putchar(char c);
void						ft_putchar_fd(char c, int fd);
void						ft_putendl(char const *s);
void						ft_putendl_fd(char const *str, int fd);
void						ft_putnbr(int n);
void						ft_putnbr_fd(int n, int fd);
void						ft_putstr(char const *s);
int							ft_putstr_ret(char const *s);
void						ft_putstr_fd(char const *str, int fd);
int							ft_putstr_fd_ret(char const *str, int fd);
char						*ft_strcat(char *s1, const char *s2);
int							ft_strcmp(const char *s1, const char *s2);
int							ft_strncmp(const char *s1, const char *s2i
	, size_t n);
char						*ft_strcpy(char *dst, char *src);
char						*ft_strdup(const char *s1);
unsigned int				ft_strlcat(char *dst, const char *src, size_t size);
size_t						ft_strlen(const char *s);
char						*ft_strncat(char *s1, const char *s2, size_t n);
char						*ft_strncpy(char *dst, const char *src, size_t len);
char						*ft_strrev(char *str);
char						*ft_strstr(const char *haystack
	, const char *needle);
char						*ft_strnstr(const char *haystack, const char *needle
	, size_t len);
char						*ft_strchr(const char *s, int c);
int							ft_strchr_pos(char *str, int c);
char						*ft_strrchr(const char *str, int c);
int							ft_strequ(char const *s1, char const *s2);
int							ft_strnequ(char const *s1, char const *s2
	, size_t n);
char						*ft_strsub(char const *s, unsigned int start
	, size_t len);
char						*ft_strjoin(char const *s1, char const *s2);
char						*ft_strjoin_free(char **s1, char **s2, int opt);
char						*ft_strtrim(char const *s);
char						*ft_strnew(size_t size);
void						ft_strdel(char **as);
void						ft_strclr(char *s);
char						**ft_strsplit(char const *s, char c);
void						ft_print_words_tables(char **tab);
char						*ft_strmap(char const *s, char (*f_m) (char));
char						*ft_strmapi(char const *s
	, char (*f_mi) (unsigned int, char));
void						ft_striter(char *s, void (*f_i)(char *));
void						ft_striteri(char *s
	, void (*f_ii)(unsigned int, char *));
void						ft_swap(void **a, void **b, int opt);
void						ft_swapstr(char **a, char **b);
int							ft_toupper(int c);
int							ft_tolower(int c);
int							ft_lstprint(t_lst *begin_list, int opt);
int							get_gc_data(int opt);
t_gc_list					*get_gc_list(int opt);
int							filler_gnl(int fd, char **line);

#endif
