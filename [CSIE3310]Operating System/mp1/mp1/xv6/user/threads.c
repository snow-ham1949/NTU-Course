#include "kernel/types.h"
#include "user/setjmp.h"
#include "user/threads.h"
#include "user/user.h"

#define NULL 0
#define ul unsigned long

static struct thread* current_thread = NULL;
static struct thread* root_thread = NULL;
static struct thread* next_thread = NULL;
static struct thread* last_thread = NULL;
static int id = 1;
static int next = 0;
static jmp_buf env_st;
// static jmp_buf env_tmp;
// TODO: necessary declares, if any


struct thread *thread_create(void (*f)(void *), void *arg)
{
    struct thread *t = (struct thread*) malloc(sizeof(struct thread));
    //unsigned long stack_p = 0;
    unsigned long new_stack_p;
    unsigned long new_stack;
    new_stack = (unsigned long) malloc(sizeof(unsigned long)*0x100);
    new_stack_p = new_stack +0x100*8-0x2*8;
    t->fp = f;
    t->arg = arg;
    t->ID  = id;
    t->buf_set = 0;
    t->stack = (void*) new_stack;
    t->stack_p = (void*) new_stack_p;
    id++;
    return t;
}

void thread_add_runqueue(struct thread *t)
{
    if(current_thread == NULL){
        current_thread = root_thread = t;
        t->left = t->right = NULL;
        t->parent = t;
    }
    else{
        if (!current_thread->left)
        {
            current_thread->left = t;
        }
        else if (!current_thread->right)
        {
            current_thread->right = t;
        }

        t->left = t->right = NULL;
        t->parent = current_thread;
    }
}

void thread_yield(void)
{
    // TODO
    if (setjmp(current_thread->env) == 0)
    {
        current_thread->buf_set = 1;
        schedule();
        dispatch();
    }
}

void dispatch(void)
{
    // TODO
    if (current_thread->buf_set)
    {
        longjmp(current_thread->env, 1);
    }
    else
    {
        if (setjmp(current_thread->env) == 0)
        {
            current_thread->env->sp = (ul)current_thread->stack_p;
            // set ruturn address to be pointer point to the function to be executed
            current_thread->env->ra = (ul)current_thread->fp; 
            longjmp(current_thread->env, 1);
        }
        else
        {
            current_thread->fp(current_thread->arg);
        }
    }
    thread_exit();
}

void find_next_thread(struct thread *cur, struct thread *target)
{
    if (!cur || next == -1)
    {
        return;
    }

    if (next == 1)
    {
        next_thread = cur;
        next = -1;
        return;
    }

    if (cur == target)
    {
        next = 1;
    }

    find_next_thread(cur->left, target);
    find_next_thread(cur->right, target);
}

void find_last_preorder_thread(struct thread *last)
{
    if (!last)
    {
        return;
    }

    last_thread = last;
    find_last_preorder_thread(last->left);
    find_last_preorder_thread(last->right);
}

void schedule(void)
{
    // TODO
    next = 0;
    next_thread = NULL;
    find_next_thread(root_thread, current_thread);
    if (!next_thread)
    {
        current_thread = root_thread;
    }
    else
    {
        current_thread = next_thread;
    }
}

void thread_exit(void)
{
    if(!current_thread->left && !current_thread->right) // leaf node
    { 
        // TODO
        if (current_thread == root_thread) // only left root node
        {
            free_thread(current_thread);
            longjmp(env_st, 1);
            return;
        }
        else
        {
            next = 0;
            next_thread = NULL;
            find_next_thread(root_thread, current_thread);
            if (!next_thread)
            {
                next_thread = root_thread;
            }

            if (current_thread == current_thread->parent->left)
            {
                current_thread->parent->left = NULL;
            }
            else if (current_thread == current_thread->parent->right)
            {
                current_thread->parent->right = NULL;
            }
            free_thread(current_thread);
            current_thread = next_thread;
        }
    }
    else 
    {
        find_last_preorder_thread(current_thread);

        if (last_thread == last_thread->parent->left)
        {
            last_thread->parent->left = NULL;
        }
        else if (last_thread == last_thread->parent->right)
        {
            last_thread->parent->right = NULL;
        }

        if (current_thread != root_thread)
        {
            if (current_thread == current_thread->parent->left)
            {
                current_thread->parent->left = last_thread;
            }
            else if (current_thread == current_thread->parent->right)
            {
                current_thread->parent->right = last_thread;
            }
        }

        if (current_thread->right)
        {
            current_thread->right->parent = last_thread;
        }
        if (current_thread->left)
        {
            current_thread->left->parent = last_thread;
        }

        last_thread->right = current_thread->right;
        last_thread->left = current_thread->left;

        if (current_thread == root_thread)
        {
            root_thread = last_thread;
            last_thread->parent = last_thread;
        }
        else
        {
            last_thread->parent = current_thread->parent;
        }

        free_thread(current_thread);
        current_thread = last_thread;
        schedule();
    }
    dispatch();
}

void thread_start_threading(void)
{
    // TODO
    if (setjmp(env_st) == 0)
    {
        current_thread = root_thread;
        dispatch();
    }
}

void free_thread(struct thread *t)
{
    free(t->stack);
    free(t);
}
