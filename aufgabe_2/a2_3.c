#include <stdio.h>
#include <stdlib.h>

extern char **environ;


int check_user_input(char* user_input) {
    int value = atoi(user_input);

    if (value < 0 || value >5) {
        printf("Invalid input: Please enter a number between 0 and 5.\n");
        return 9;
    }
    else return value;
}

void print_menu(){
    puts("---------------------");
    puts("Environment-List Menu");
    puts("---------------------");
    puts("[1]: Print environment list");
    puts("[2]: Print environment entry (getenv)");
    puts("[3]: Add environment entry (putenv)");
    puts("[4]: Modify environment entry (setenv)");
    puts("[5]: Remove environment entry (unsetenv)");
    puts("[0]: End");
}


int main() {
    

while(1) {
    char **env_variables = environ;

    print_menu();
    char user_input= readline();
    int value = check_user_input(&user_input);
    switch (value) {
        case 1: for (; *env_variables; env_variables++) 
                {
                    printf("%s\n", *env_variables);
                } break;
        case 2: puts("Placeholder for choice 2"); break;
        case 3: puts("Placeholder for choice 3"); break;
        case 4: puts("Placeholder for choice 4"); break; 
        case 5: puts("Placeholder for choice 5"); break;
        default: break;
        }
    }


}
