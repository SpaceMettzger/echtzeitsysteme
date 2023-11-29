#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <readline/readline.h>

extern char **environ;

#define CLEAR "\e[1;1H\e[2J"


int check_user_input(char* user_input) {
    int value = atoi(user_input);

    if (value < 0 || value >5) {
        printf("Invalid input: Please enter a number between 0 and 5.\n");
        return 9;
    }
    else return value;
}

void print_menu(){
    printf("%s",CLEAR);
    puts("---------------------");
    puts("Environment-List Menu");
    puts("---------------------");
    puts("[1]: Print environment list");
    puts("[2]: Print environment entry (getenv)");
    puts("[3]: Add environment entry (putenv)");
    puts("[4]: Modify environment entry (setenv)");
    puts("[5]: Remove environment entry (unsetenv)");
    puts("[0]: End");
    puts("---------------------");
}

void get_env() {
    char* env_var_name = readline("Enter the name of the environment variable: ");
    char* env_value = getenv(env_var_name);
    if (env_value) {
        printf("%s=%s\n", env_var_name, env_value);
    } else {
        printf("Environment variable '%s' not found.\n", env_var_name);
    }
    free(env_var_name); 
}

void add_env() {
    char* env_var = readline("Enter the name of the new environment variable in the form \"VARIABLE_NAME=VALUE\": ");
    char* equal_sign = strchr(env_var, '=');
    
    if (equal_sign) {
        int ret = putenv(env_var);
        if (ret == 0) {
            printf("Environment variable has been set: %s\n", env_var);
        } 
        else {
            puts("Environment variable could not be set"); 
        }
    } 
    else {
        puts("Invalid input. Please use the format \"VARIABLE_NAME=VALUE\".");
    }
    //free(env_var); 
}

void modify_env() {
    char* var_name = readline("Enter the name of the environment variable to modify: ");
    char* new_value = readline("Enter the new value for the environment variable: ");

    if (setenv(var_name, new_value, 1) == 0) {
        printf("Environment variable %s has been updated to: %s\n", var_name, new_value);
    } else {
        printf("Failed to modify the environment variable.\n");
    }

    free(var_name);
    free(new_value);
}

void remove_env() {
    char* var_name = readline("Enter the name of the environment variable to be removed: ");

    if (unsetenv(var_name) == 0) {
        printf("Environment variable %s has been removed\n", var_name);
    } else {
        printf("Failed to remove the environment variable.\n");
    }
    free(var_name);
}


int main() {
    

while(1) {
    char **env_variables = environ;
    
    print_menu();
    char* user_input = readline("Please choose an option: ");
    int value = check_user_input(user_input);
    switch (value) {
        case 1: ;
            char **env_copy = NULL;
            int num_env = 0;
            while (env_variables[num_env]) {
                num_env++;
            }
            env_copy = (char **)malloc((num_env + 1) * sizeof(char *));
            if (env_copy == NULL) {
                perror("Memory allocation failed");
                exit(1);
            }
            for (int i = 0; i < num_env; i++) {
                env_copy[i] = strdup(env_variables[i]);
            }
            env_copy[num_env] = NULL;

            for (int i = 0; env_copy[i]; i++) {
                char* var = strchr(env_copy[i], '=');
                if (var) {
                    *var = '\0';
                    printf("%s\n", env_copy[i]);
                }
            }

            for (int i = 0; env_copy[i]; i++) {
                free(env_copy[i]);
            }
            free(env_copy);
            puts("Press Enter to Continue\n");  
            getchar();   
            break;

        case 2: 
            get_env();
            puts("Press Enter to Continue\n");  
            getchar();   
            break;
        case 3: ;
            add_env();
            puts("Press Enter to Continue\n");  
            getchar();   
            break;
        case 4: 
            modify_env(); 
            puts("Press Enter to Continue\n");  
            getchar();   
            break; 
        case 5: 
            remove_env();
            puts("Press Enter to Continue\n");  
            getchar();   
            break;
        case 0:
            free(user_input); 
            return 0;
        default: break;
        }

        free(user_input);
    }

}
