#ifndef TYPES_H
#define TYPES_H


#ifndef NULL
#define NULL ((void *)0)
#endif


#define MAX_TIME_SLICE 5

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef int bool;
typedef int int32_t;

struct heap_entry {
     struct heap_entry *parent, *left, *right;
};

typedef struct heap_entry heap_entry_t;

typedef int(*compare_f)(void *a, void *b);

static inline void heap_init(heap_entry_t *a) __attribute__((always_inline));
static inline heap_entry_t *heap_merge(
     heap_entry_t *a, heap_entry_t *b,
     compare_f comp);
static inline heap_entry_t *heap_insert(
     heap_entry_t *a, heap_entry_t *b,
     compare_f comp) __attribute__((always_inline));
static inline heap_entry_t *heap_remove(
     heap_entry_t *a, heap_entry_t *b,
     compare_f comp) __attribute__((always_inline));

static inline void
heap_init(heap_entry_t *a)
{
     a->left = a->right = a->parent = NULL;
}

static inline heap_entry_t *
heap_merge(heap_entry_t *a, heap_entry_t *b,
                compare_f comp)
{
     if (a == NULL) return b;
     else if (b == NULL) return a;
     
     heap_entry_t *l, *r;
     if (comp(a, b) == -1)
     {
          r = a->left;
          l = heap_merge(a->right, b, comp);
          
          a->left = l;
          a->right = r;
          if (l) l->parent = a;

          return a;
     }
     else
     {
          r = b->left;
          l = heap_merge(a, b->right, comp);
          
          b->left = l;
          b->right = r;
          if (l) l->parent = b;

          return b;
     }
}

static inline heap_entry_t *
heap_insert(heap_entry_t *a, heap_entry_t *b,
                 compare_f comp)
{
     heap_init(b);
     return heap_merge(a, b, comp);
}

static inline heap_entry_t *
heap_remove(heap_entry_t *a, heap_entry_t *b,
                 compare_f comp)
{
     heap_entry_t *p   = b->parent;
     heap_entry_t *rep = heap_merge(b->left, b->right, comp);
     if (rep) rep->parent = p;
     
     if (p)
     {
          if (p->left == b)
               p->left = rep;
          else p->right = rep;
          return a;
     }
     else return rep;
}



struct list_entry {
    struct list_entry *prev, *next;
};

typedef struct list_entry list_entry_t;

static inline void list_init(list_entry_t *elm) __attribute__((always_inline));
static inline void list_add(list_entry_t *listelm, list_entry_t *elm) __attribute__((always_inline));
static inline void list_add_before(list_entry_t *listelm, list_entry_t *elm) __attribute__((always_inline));
static inline void list_add_after(list_entry_t *listelm, list_entry_t *elm) __attribute__((always_inline));
static inline void list_del(list_entry_t *listelm) __attribute__((always_inline));
static inline void list_del_init(list_entry_t *listelm) __attribute__((always_inline));
static inline bool list_empty(list_entry_t *list) __attribute__((always_inline));
static inline list_entry_t *list_next(list_entry_t *listelm) __attribute__((always_inline));
static inline list_entry_t *list_prev(list_entry_t *listelm) __attribute__((always_inline));

static inline void __list_add(list_entry_t *elm, list_entry_t *prev, list_entry_t *next) __attribute__((always_inline));
static inline void __list_del(list_entry_t *prev, list_entry_t *next) __attribute__((always_inline));


static inline void
list_init(list_entry_t *elm) {
    elm->prev = elm->next = elm;
}


static inline void
list_add(list_entry_t *listelm, list_entry_t *elm) {
    list_add_after(listelm, elm);
}


static inline void
list_add_before(list_entry_t *listelm, list_entry_t *elm) {
    __list_add(elm, listelm->prev, listelm);
}


static inline void
list_add_after(list_entry_t *listelm, list_entry_t *elm) {
    __list_add(elm, listelm, listelm->next);
}


static inline void
list_del(list_entry_t *listelm) {
    __list_del(listelm->prev, listelm->next);
}


static inline void
list_del_init(list_entry_t *listelm) {
    list_del(listelm);
    list_init(listelm);
}


static inline bool
list_empty(list_entry_t *list) {
    return list->next == list;
}


static inline list_entry_t *
list_next(list_entry_t *listelm) {
    return listelm->next;
}


static inline list_entry_t *
list_prev(list_entry_t *listelm) {
    return listelm->prev;
}


static inline void
__list_add(list_entry_t *elm, list_entry_t *prev, list_entry_t *next) {
    prev->next = next->prev = elm;
    elm->next = next;
    elm->prev = prev;
}


static inline void
__list_del(list_entry_t *prev, list_entry_t *next) {
    prev->next = next;
    next->prev = prev;
}
#define offsetof(type, member)                                      \
    ((uint)(&((type *)0)->member))

#define to_struct(ptr, type, member)                               \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#define le2proc(le, member)         \
    to_struct((le), struct proc, member)


#endif    
