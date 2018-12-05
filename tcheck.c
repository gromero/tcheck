#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <signal.h>

void signal_handler(int signo, siginfo_t *si, void *data)
{
 ucontext_t *uc = (ucontext_t *)data; // Set a local pointer to uc.

 printf("* Received a SIGILL\n");
 printf("* uc->uc_mcontext.regs->nip= %p\n", (void *) uc->uc_mcontext.regs->nip);

 uc->uc_mcontext.regs->nip += 4; // Skip illegal instruction 
 // uc->uc_mcontext.gp_regs[32] += 4; // Same as above ;-)
}

int main(void)
{
 sigset_t sigset;

 struct sigaction sa;

 sa.sa_flags = SA_SIGINFO;
 sa.sa_sigaction = signal_handler;
 sigaction(SIGILL , &sa, NULL);

 printf(" * Executing 'tcheck'...\n");

 asm ("tcheck 0;");

 exit(0);
}
