#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <signal.h>

void signal_handler(int signo, siginfo_t *si, void *ucp)
{
 ucontext_t *uc = (ucontext_t *)ucp;

 if (signo == SIGILL) {
 	printf(" * Received a SIGILL\n");
 }  else if (signo == SIGTRAP) {
	printf(" * Received a SIGTRAP\n");
 } else {
	printf(" * Unexpected signal, aborting...\n");
	exit(1);
 }

 printf(" * uc->uc_mcontext.regs->nip= %p\n", (void *) uc->uc_mcontext.regs->nip);

 uc->uc_mcontext.regs->nip += 4; // Skip illegal / trap instruction 
}

int main(void)
{
 sigset_t sigset;

 struct sigaction sa;

 sa.sa_flags = SA_SIGINFO;
 sa.sa_sigaction = signal_handler;
 sigaction(SIGILL , &sa, NULL);
 sigaction(SIGTRAP, &sa, NULL);

 printf(" * Executing 'tcheck'...\n");
 asm ("tcheck 0;");

 printf(" * Executing 'trap'...\n");
 asm ("tbegin.;  trap;");

 printf(" * Executing illegal...\n");
 asm ("tbegin.; .long 0x0;");

 printf(" * Exiting...\n");
 exit(0);
}
