#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if (argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if (argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// for mp3
uint64
sys_thrdstop(void)
{
  int delay, thrdstop_context_id;
  uint64 handler, handler_arg;
  if (argint(0, &delay) < 0)
    return -1;
  if (argint(1, &thrdstop_context_id) < 0)
    return -1;
  if (argaddr(2, &handler) < 0)
    return -1;
  if (argaddr(3, &handler_arg) < 0)
    return -1;
  struct proc *p = myproc();
  
  if (thrdstop_context_id == -1)
  {
    for (int i = 0; i < 32; i++)
    {
      if(p->tf_used[i] == 0)
      {
        thrdstop_context_id = i;
        p->last_id = i;
        p->tf_used[i] = 1;
        break;
      }
    }
  }
  else
  {
    p->last_id = thrdstop_context_id;
  }

  p->thrdstop_handler = handler;
  p->handler_arg = handler_arg;
  p->delay = delay;
  p->curr_ticks = 0;
  p->alarm = 1;
  return thrdstop_context_id;
}

// for mp3
uint64
sys_cancelthrdstop(void)
{
  int thrdstop_context_id, is_exit;
  if (argint(0, &thrdstop_context_id) < 0)
    return -1;
  if (argint(1, &is_exit) < 0)
    return -1;
  struct proc *p = myproc();
  if (is_exit)
  {
    p->tf_used[thrdstop_context_id] = 0;
  }
  else
  {
    if (thrdstop_context_id != -1)
    {
      p->last_id = thrdstop_context_id;
      struct trapframe *tf = kalloc();
      memmove(tf, p->trapframe, PGSIZE);
      p->alarm_tf[p->last_id] = tf;
    }
  }
  p->alarm = 0;
  return p->curr_ticks;
}

// for mp3
uint64
sys_thrdresume(void)
{
  int thrdstop_context_id;
  if (argint(0, &thrdstop_context_id) < 0)
    return -1;
  struct proc *p = myproc();
  p->last_id = thrdstop_context_id;
  memmove(p->trapframe, p->alarm_tf[thrdstop_context_id], PGSIZE);
  return 0;
}
