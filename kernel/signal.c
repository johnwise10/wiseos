#include<signal.h>

int raise(int sig){
  return 0;
}

int kill(pid_t pid, int sig){
  return 0;
}

int sigaddset(sigset_t *mask, int signo){
  return 0;
}

int sigdelset(sigset_t *mask, int signo){
  return 0;
}

int sigemptyset(sigset_t *mask){
  return 0;
}

int sigfillset(sigset_t *mask){
  return 0;
}

int sigismember(sigset_t *mask, int signo){ /* 1 - is, 0 - not, -1 error */
  return 0;
}

int sigpending(sigset_t *set){
  return 0;
}

int sigprocmask(int how, sigset_t *set, sigset_t *oldset){
  return 0;
}

int sigsuspend(sigset_t *sigmask){
  return 0;
}

int sigaction(int sig, struct sigaction *act, struct sigaction *oldact){
  return 0;  
}