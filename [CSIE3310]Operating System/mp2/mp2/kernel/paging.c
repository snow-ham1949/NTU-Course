#include "param.h"
#include "types.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"
#include "proc.h"

/* NTU OS 2022 */
/* Page fault handler */
int handle_pgfault() {
    /* Find the address that caused the fault */
    /* uint64 va = r_stval(); */

    /* TODO */
    uint64 va = PGROUNDDOWN(r_stval());
    struct proc *proc = myproc();
    pte_t *pte = walk(proc->pagetable, va, 1);
    if (*pte & PTE_S)
    {
        char *pa = kalloc();

        begin_op();
        uint64 blockno = PTE2BLOCKNO(*pte);
        read_page_from_disk(ROOTDEV, (char *)pa, blockno);
        bfree_page(ROOTDEV, blockno);
        *pte = PA2PTE(pa) | PTE_FLAGS(*pte);
        end_op();

        *pte |= PTE_V;
        *pte &= ~PTE_S;
    }
    else
    {
        char *mem = kalloc();
        // if (mem == 0)
        // {
        //     proc->killed = 1;
        //     return -4;
        // }
        memset(mem, 0, PGSIZE);
        if (mappages(proc->pagetable, va, PGSIZE, (uint64)mem, PTE_R | PTE_U | PTE_W | PTE_X) != 0)
        {
            kfree(mem);
            return -3;
        }
    }
    return 0;
}
