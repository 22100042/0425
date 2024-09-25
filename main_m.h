#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LINE_SIZE 10

typedef enum {FORMAT_ERROR=-2, UNKNOWN_CMD_ERROR=-1, PRINT=0, DEL=1, SAVE, INSERT, STATUS, QUIT, HELP} CMD;

typedef struct opt { 
	int begin;
	int end;
	char *argv[3];
} Options;

extern char *default_file_name;
extern char **buffer ;   // 파일 내용을 저장하는 버퍼
extern int line_count ;     // 총 라인 수
extern int buf_limit;

// 함수 선언
int print(char **buf, Options* opt);
int del(char **buf, Options* opt);
int save(char **buf, Options* opt);
int insert(char **buf, Options* opt);
int quit(char **buf, Options* opt);
int status(char **buf, Options* opt);
int help(char **buf, Options* opt);

FILE *process_cmd_args(int argc, char *argv[], char *prompt);
char **read_init_buffer(FILE *fp);
int get_cmd(char prompt, Options* opt);



