/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>


void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysSub(int op1, int op2)
{
  return op1 - op2;
}

int SysMult(int op1, int op2)
{
  return op1 * op2;
}

int SysDiv(int op1, int op2)
{
  return op1 / op2;
}

int SysPow(int op1, int op2)
{
  int i;
  for(i=1;i<op2;i++){
	  op1=op1*op1;
  }
  return op1;
}

int SysCreate(int addr){
  int count = 0;
  int ch;
  char name[60];

  do{
    kernel->machine->ReadMem(addr,1,&ch);
    addr ++;
    name[count]=(char)ch;
  }while(ch!='\0' && count++<59);
  name[count]='\0';
  return creat(name,0777);
}

int SysOpen(int addr){
  int count = 0;
  int ch;
  char name[60];

  do{
    kernel->machine->ReadMem(addr,1,&ch);
    addr ++;
    name[count]=(char)ch;
  }while(ch!='\0' && count++<59);
  name[count]='\0';
  return open(name, O_CREAT |  O_RDWR ,0777);
}

int SysClose(int FileID){
  return close(FileID);
}

int SysWrite(int Addr,int Count,int FileID){
  int ch;
  int i=0;
  while (i<Count){
    kernel->machine->ReadMem(Addr,1,&ch);
    write(FileID,(char *)&ch,1);
    Addr++;
    i++;
  }
  return i;
}

int SysRead(int Addr,int Count,int FileID){
  char ch;
  int i=0;
  while (i<Count){
    read(FileID,&ch,1);
    kernel->machine->WriteMem(Addr,1,ch);
    Addr++;
    i++;
    write(FileID,&ch,1);
  }
  return i;
}

int SysExec(int addr){
  int count = 0;
  int ch;
  char cmd[60];

  do{
    kernel->machine->ReadMem(addr,1,&ch);
    addr ++;
    cmd[count]=(char)ch;
  }while(ch!='\0' && count++<59);
  cmd[count]='\0';
  pid_t child;
  child=vfork();
  if(child==0){
    execl("/bin/sh","/bin/sh","-c",cmd,NULL);
    _exit(EXIT_FAILURE);
  }else if(child <0){
    _exit(EXIT_FAILURE);
    return EPERM;
  }
  return child;
}


int SysJoin(int procid){
  pid_t retid;
  retid = waitpid((pid_t)procid,(int *) 0,0);
  return retid;
}

#endif /* ! __USERPROG_KSYSCALL_H__ */
