#define LINE_BUF_SIZE 128   //Maximum input string length
#define ARG_BUF_SIZE 64     //Maximum argument string length
#define MAX_NUM_ARGS 8      //Maximum number of arguments
 
bool error_flag = false;
 
char line[LINE_BUF_SIZE];
char args[MAX_NUM_ARGS][ARG_BUF_SIZE];
 
//Function declarations
int cmd_help();
int cmd_wifi();
int cmd_mqtt();
 
//List of functions pointers corresponding to each command
int (*commands_func[])(){
    &cmd_help,
    &cmd_wifi,
    &cmd_mqtt,
};
 
//List of command names
const char *commands_str[] = {
    "help",
    "wifi",
    "mqtt"
};
 
 
int num_commands = sizeof(commands_str) / sizeof(char *);
 
void setup() {
    Serial.begin(115200);
    cli_init();
}
 
void loop() {
    my_cli();
}
