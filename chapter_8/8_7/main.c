#include <stdio.h>
#include <limits.h>

#define malloc __malloc
#define calloc __calloc
#define free __free
#define NALLOC 1024
typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};
typedef union header Header;

static Header base;
static Header *freep = NULL;

void *calloc(unsigned n, size_t size);
void *malloc(unsigned nbytes);
static Header *morecore(unsigned nunits);
void free(void *ap);
char *sbrk(int);

int main()
{
    char *b = malloc(0);
    free(b);
    free(&base);
    free(freep);
    return 0;
}

void *calloc(unsigned n, size_t size)
{
    char *p;
    if ((p = malloc(n * size)) == NULL)
        return NULL;
    for (unsigned i = 0; i < n * size; i++)
        p[i] = '\0';
    return p;
}

void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    if (nbytes == 0 || nbytes > UINT_MAX - sizeof(Header)) {
        printf("Error: invalid nbytes size request %d\n", nbytes);
        return NULL;
    }
    
    unsigned nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits) 
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }
}

static Header *morecore(unsigned nunits)
{
    char *cp;
    Header *up;
    if (nunits < NALLOC)
        nunits = NALLOC;
    cp = sbrk(nunits * sizeof(Header));
    if (cp == (char *) -1)
        return NULL;
    up = (Header*) cp;
    up->s.size = nunits;
    free((void *) (up + 1));
    return freep;
}

void free(void *ap)
{
    Header *bp, *p;
    if (ap == NULL) {
        printf("Error: null pointer passed to myfree\n");
        return;
    }
    bp = (Header *) ap - 1;
    if (bp->s.size == 0) {
        printf("Error: can't free ap with 0 units\n");
        return;
    }
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    if (bp + bp->s.size == p->s.ptr && bp->s.size < UINT_MAX - p->s.ptr->s.size) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
    	bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp && p->s.size < UINT_MAX - bp->s.size) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
