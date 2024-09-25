
#include "main_m.h"

char *default_file_name = NULL; // first file name given in command line
char **buffer = NULL;   // 파일 내용을 저장하는 버퍼
int line_count = 0;     // 총 라인 수
int buf_limit = BUFFER_SIZE;

#define MAX_CMD 10
typedef int (*EXEC_CMD)(char **,Options *);

void init_command_table(EXEC_CMD exec_cmd_tab[])
{
    exec_cmd_tab [PRINT] = print;
    exec_cmd_tab [DEL] = del;
    exec_cmd_tab [SAVE] = save;
    exec_cmd_tab [INSERT] = insert;
    exec_cmd_tab [STATUS] = status;
    exec_cmd_tab [QUIT] = quit;
    exec_cmd_tab [HELP] = help;
    exec_cmd_tab [MAX_CMD-1] = 0;
}

int main(int argc, char *argv[]) {

    
    EXEC_CMD exec_cmd[MAX_CMD];

    init_command_table(exec_cmd) ;

    char prompt = '*';  // 기본 프롬프트
    Options option;
    
    // 명령줄 인수 처리
    FILE *fp = process_cmd_args(argc, argv, &prompt);
    
    // 파일 내용을 읽어 버퍼 초기화
    char **buffer = read_init_buffer(fp);

    if(buffer == NULL){
	printf("ERROR: Allocating Buffer Memory Failed\n");
        exit(1);
    }
    
    int ret = 0;
    while (1) {
        // 사용자로부터 명령을 읽음
        CMD cmd = get_cmd(prompt, &option);
	if(cmd >= 0 && cmd < MAX_CMD){
           ret = (exec_cmd[cmd])(buffer,&option);  // 명령 실행
           if (ret > 0) 
               printf("Error in command: %d\n", ret);
	   else if (ret < 0)
	       break;
        } else if (cmd == FORMAT_ERROR){
		printf("Please try again with line number(s). Enter 'h' if you need help\n");
	} else if (cmd == UNKNOWN_CMD_ERROR) {
		printf("Unknown Command Error. Enter 'h' if you need help\n");
	} else {
		printf("Critical Program Internal Error!\n");
		exit(1);
	}
    }
    
    return 0;
}

