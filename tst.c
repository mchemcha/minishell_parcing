#include <stdio.h>

static int ft_arrylen(char **str) {
    int i = 0;
    int s = 0;

    while (str[i]) 
	{
        s += 1;
        i++;
    }
    return s;
}

int main() {
    char *cmd[3];  
    int i = 0;
    int j = 0;

    for (int k = 0; k < 3; k++) {
        cmd[k] = NULL;
    }

    while (i < 2) {
        cmd[i] = "aaa";
        i++;
    }
    cmd[i] = NULL;

    while (cmd[j]) {
        printf(">%s\n", cmd[j]);
        j++;
    }

    int len = ft_arrylen(cmd);
    printf("len: ===>%d<===\n", len);

    return 0;
}
