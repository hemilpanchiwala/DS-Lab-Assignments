/* Node structure of fibonacci heap */
template <class V>
struct node
{
  public:
    node<V> *prev;
    node<V> *next;
    node<V> *child;
    node<V> *parent;
    V value;
    int degree;
    bool marked;
};

template <class V>
class FibonacciHeap
{
  public:
    node<V> *heap; /*root node of heap*/

    FibonacciHeap()
    {
        heap = NULL;
    }

    ~FibonacciHeap()
    {
        if (heap)
        {
            deleteAll(heap);
        }
    }

    void deleteAll(node<V> *n)
    {
        if (n)
        {
            node<V> *c = n;
            do
            {
                node<V> *d = c;
                c = c->next;
                deleteAll(d->child);
                delete d;
            } while (c != n);
        }
    }

    node<V> *create_node(V value)
    {
        node<V> *n = new node<V>;
        n->value = value;
        n->prev = n->next = n;
        n->degree = 0;
        n->marked = false;
        n->child = NULL;
        n->parent = NULL;
        return n;
    }

    node<V> *merge_heaps(node<V> *a, node<V> *b)/**/
    {
        if (!a)
            return b;
        if (!b)
            return a;
        if (a->value > b->value)
        {
            node<V> *temp = a;
            a = b;
            b = temp;
        }
        node<V> *an = a->next;
        node<V> *bp = b->prev;
        a->next = b;
        b->prev = a;
        an->prev = bp;
        bp->next = an;
        return a;
    }

    node<V> *insert(V value)/**/
    {
        node<V> *ret = create_node(value);
        heap = merge_heaps(heap, ret);
        return ret;
    }

    V get_min()/**/
    {
        if(heap==NULL)
            return V();
            
        return heap->value;
    }

    void addChild(node<V> *parent, node<V> *child)
    {
        child->prev = child->next = child;
        child->parent = parent;
        parent->degree++;
        parent->child = merge_heaps(parent->child, child);
    }

    node<V> *extract_min_helper(node<V> *n)
    {
        /* mark all childs as false and set their parent to null */
        if (n->child != NULL)
        {
            node<V> *c = n->child;
            do
            {
                c->marked = false;
                c->parent = NULL;
                c = c->next;
            } while (c != n->child);
        }
        /* done */

        if (n->next == n)
        {
            n = n->child;
        }
        else
        {
            n->next->prev = n->prev; /* detach n from doubly LL */
            n->prev->next = n->next; /* detach n from doubly LL */
            n = merge_heaps(n->next, n->child);
        }

        if (n == NULL)
            return n;

        node<V> *trees[64] = {NULL};

        while (true)
        {
            if (trees[n->degree] != NULL)
            {
                node<V> *t = trees[n->degree];
                if (t == n)
                    break;
                trees[n->degree] = NULL;
                if ((n->value) < (t->value))
                {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    addChild(n, t);
                }
                else
                {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    if (n->next == n)
                    {
                        t->next = t;
                        t->prev = t;
                        addChild(t, n);
                        n = t;
                    }
                    else
                    {
                        n->prev->next = t;
                        n->next->prev = t;
                        t->next = n->next;
                        t->prev = n->prev;
                        addChild(t, n);
                        n = t;
                    }
                }
                continue;
            }
            else
            {
                trees[n->degree] = n;
            }
            n = n->next;
        }
        node<V> *min = n;
        node<V> *start = n;
        do
        {
            if (n->value < min->value)
                min = n;
            n = n->next;
        } while (n != start);
        return min;
    }

    V extract_min()/**/
    {
        if(heap == NULL) return V();
        node<V> *old = heap;
        heap = extract_min_helper(heap);
        V ret = old->value;
        delete old;
        return ret;
    }

    node<V> *find_helper(node<V> *heap, V value)
    {
        node<V> *n = heap;
        if (n == NULL)
            return NULL;
        do
        {
            if (n->value == value)
                return n;
            node<V> *ret = find_helper(n->child, value);
            if (ret)
                return ret;
            n = n->next;
        } while (n != heap);
        return NULL;
    }

    node<V> *find(V value)
    {
        return find_helper(heap, value);
    }

    node<V> *cut(node<V> *heap, node<V> *n)
    {
        if (n->next == n)
        {
            n->parent->child = NULL;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n->parent->child = n->next;
        }
        n->next = n->prev = n;
        n->marked = false;
        return merge_heaps(heap, n);
    }

    node<V> *decrease_key_helper(node<V> *heap, node<V> *n, V value)
    {
        if (n->value < value)
            return heap;
        n->value = value;
        if (n->parent)
        {
            if (n->value < n->parent->value)
            {
                heap = cut(heap, n);
                node<V> *parent = n->parent;
                n->parent = NULL;
                while (parent != NULL && parent->marked)
                {
                    heap = cut(heap, parent);
                    n = parent;
                    parent = n->parent;
                    n->parent = NULL;
                }
                if (parent != NULL && parent->parent != NULL)
                    parent->marked = true;
            }
        }
        else
        {
            if (n->value < heap->value)
            {
                heap = n;
            }
        }
        return heap;
    }

    void decrease_key(V i, V value)/**/
    {
        node<V> *n = find(i);
        if(n==NULL)
        {
            return;
        }
        heap = decrease_key_helper(heap, n, value);
    }
};