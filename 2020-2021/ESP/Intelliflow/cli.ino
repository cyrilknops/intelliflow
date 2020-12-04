void cli_init(){
    Serial.println("Welcome Intelliflow command line interface (CLI).");
    Serial.println("Type \"help\" to see a list of commands.");
}
 
 
void my_cli(){
  if(cliMode)
    Serial.print("> ");
 
    read_line();
    if(!error_flag){
        parse_line();
    }
    if(!error_flag){
        execute();
    }
 
    memset(line, 0, LINE_BUF_SIZE);
    memset(args, 0, sizeof(args[0][0]) * MAX_NUM_ARGS * ARG_BUF_SIZE);
 
    error_flag = false;
}

void read_line(){
    String line_string;
    if(cliMode)
      while(!Serial.available());
 
    if(Serial.available()){
        line_string = Serial.readStringUntil('\n');
        if((line_string.length() < LINE_BUF_SIZE)){
          line_string.toCharArray(line, LINE_BUF_SIZE);
          Serial.println(line_string);
        }
        else{
          Serial.println("Input string too long.");
          error_flag = true;
        }
    }
}
 
void parse_line(){
    char *argument;
    int counter = 0;
 
    argument = strtok(line, " ");
 
    while((argument != NULL)){
        if(counter < MAX_NUM_ARGS){
            if(strlen(argument) < ARG_BUF_SIZE){
                strcpy(args[counter],argument);
                argument = strtok(NULL, " ");
                counter++;
            }
            else{
                Serial.println("Input string too long.");
                error_flag = true;
                break;
            }
        }
        else{
            break;
        }
    }
}
 
int execute(){  
    for(int i=0; i<num_commands; i++){
        if(strcmp(args[0], commands_str[i]) == 0){
            return(*commands_func[i])();
        }
    }
    if(cliMode)
      Serial.println("Invalid command. Type \"help\" for more.");
    return 0;
}

int cmd_help(){
    if(args[1] == NULL){
        help_help();
    }
    else if(strcmp(args[1], commands_str[0]) == 0){
        help_help();
    }
    else if(strcmp(args[1], commands_str[1]) == 0){
        help_wifi();
    }
    else if(strcmp(args[1], commands_str[2]) == 0){
        help_mqtt();
    }
    else{
        help_help();
    }
}
 
void help_help(){
    Serial.println("The following commands are available:");
 
    for(int i=0; i<num_commands; i++){
        Serial.print("  ");
        Serial.println(commands_str[i]);
    }
    Serial.println("");
    Serial.println("You can for instance type \"help wifi\" for more info on the wifi command.");
}
void help_wifi(){
    Serial.println("To change the wifi setting");
    Serial.println("First enter the SSID (case sensitive)");
    Serial.println("Enter the password");
    Serial.println("Type cli to save");
}
void help_mqtt(){
    Serial.println("To change the broker setting");
    Serial.println("First enter the IP or URL of the broker");
    Serial.println("Enter the port of the broker");
    Serial.println("Type cli to save");
}

int cmd_wifi(){
  Serial.println("Type in the SSID you want to connect to (Case sensitive)");
  read_line();
  if(!error_flag){
      Serial.println(line);
      EEPROM.writeString(0, String(line));
      Serial.println("Type in the password");
  }
  read_line();
  if(!error_flag){
      Serial.println(line);
      EEPROM.writeString(100, String(line));
      EEPROM.commit();
      Serial.println("Type cli to save");
  }
  
}

int cmd_mqtt(){
  Serial.println("Enter the IP or URL of the broker");
  read_line();
  if(!error_flag){
      Serial.println(line);
      EEPROM.writeString(200, String(line));
      Serial.println("Enter the port of the broker");
  }
  read_line();
  if(!error_flag){
      Serial.println(line);
      EEPROM.writeString(300, String(line));
      EEPROM.commit();
      Serial.println("Type cli to save");
  }
}
int cmd_cli(){
  cliMode = !cliMode;
  Serial.print("CLI mode is ");
  Serial.println(cliMode);
  if(!cliMode)
    ESP.restart();
}
