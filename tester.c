#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "Libft/libft.h"
#ifndef TIMING
#define TIMING 40
#endif
// structs
typedef struct stack
{
    int *numbers;
    int lenght;
} stack;

void mysleep(int time)
{
    float q = 0;
    while (q < time)
        q += 0.001;
}

int printstacks(stack *A, stack *B, int moves)
{
#if 1
    mysleep(TIMING);

    printf("\e[0;32m\n==========================================================================================================\n");
    int j = 0;
    int k = 0;
    printf("stack A   \n");
    while (j < A->lenght)
    {
        printf("%6d ", A->numbers[j++]);
        if (j % 15 == 0)
            printf("|\n");
    }
    j = 0;
    printf("\n\nstack B\n");
    while (j < B->lenght)
    {
        printf("%6d ", B->numbers[j++]);
        if (j % 15 == 0) // (j % (len / 8) == 0)
            printf("|\n");
    }
    printf("\n==========================================================================================================\n");
    printf("number of moves: %d\n\n\n", moves);
    // printf("\033[2J");
#endif
    return (1);
}

int is_sorted(stack *A)
{
    int i = 1;
    while (i < A->lenght)
    {
        if (A->numbers[i] < A->numbers[i - 1])
        {
            ft_printf("\n\033[0;31m KO, numbers aren't sorted %d < %d\033[0;37m\n", A->numbers[i], A->numbers[i - 1]);
            return (0);
        }
        i++;
    }
    return (1);
}

// moves
int swap(stack *X)
{
    if (X->lenght > 1)
    {
        int tmp = X->numbers[0];
        X->numbers[0] = X->numbers[1];
        X->numbers[1] = tmp;
    }
    else
    {
        ft_printf("\033[0;31mKO in swap\033[0;37m\n");
        exit(-1);
    }
    return (1);
}

int rotate(stack *X)
{
    if (X->lenght > 1)
    {
        int tmp = X->numbers[0];
        ft_memmove(X->numbers, X->numbers + 1, (X->lenght - 1) * sizeof(int));
        X->numbers[X->lenght - 1] = tmp;
    }
    else
    {
        ft_printf("\n\"\033[0;31mKO rotate\"\033[0;37m\n");
        exit(-1);
    }
    return (1);
}

int reverse_rotate(stack *X)
{
    if (X->lenght > 1)
    {
        int tmp = X->numbers[X->lenght - 1];
        ft_memmove(X->numbers + 1, X->numbers, (X->lenght - 1) * sizeof(int));
        X->numbers[0] = tmp;
    }
    else
    {
        ft_printf("\n\"\033[0;31mKO reverse rotate\"\033[0;37m\n");
        exit(-1);
    }
    return (1);
}

int push(stack *src, stack *dst, int len)
{
    if (src->lenght)
    {
        ft_memmove(dst->numbers + 1, dst->numbers, (len - 1) * sizeof(int));
        dst->numbers[0] = src->numbers[0];
        ft_memmove(src->numbers, src->numbers + 1, (len - 1) * sizeof(int));
        src->lenght--;
        dst->lenght++;
    }
    else
    {
        ft_printf("\n\"\033[0;31mKO in push\"\033[0;37m\n");
        exit(-1);
    }
    return (1);
}

// reading
char *readline(int fd)
{
    int i;
    int j;
    char *res;
    char *tmp;
    char c;

    i = 0;
    j = 0;
    res = NULL;
    tmp = NULL;
    j = read(fd, &c, 1);
    while (j && c != '\n')
    {
        tmp = ft_strjoin(res, &c);
        free(res);
        res = ft_strdup(tmp);
        free(tmp);
        j = read(fd, &c, 1);
        if (j == 0)
            break;
        i++;
        res[i] = '\0';
    }
    return (res);
}

int main(int argc, char **argv)
{
    int process_id;
    int fd[2];
    stack A;
    stack B;
    int i;

    if (pipe(fd) < 0)
    {
        ft_printf("executing pipe failed\n");
        exit(-1);
    }
    process_id = fork();
    if (process_id == 0)
    {
        ft_printf("\n\nExecuting ./push_swap...\n");
        dup2(fd[1], STDOUT_FILENO);
        // ft_printf("child process: executing push_swap...\n");
        if (execve("../push_swap", argv, NULL) < 0)
        {
            ft_printf("\033[0;31mexecuting push swap failed\n");
            exit(-1);
        }
    }
    else if (process_id > 0)
    {
        // read numbers
        int i = 1;
        char *tmp = NULL;
        char *str = NULL;
        char **array = NULL;
        int len = 0;
        int moves;
        stack A;
        stack B;

        while (i < argc)
        {
            tmp = ft_strjoin3(str, " ", argv[i]);
            free(str);
            str = tmp;
            i++;
        }
        array = ft_split(str, ' ');
        len = ft_arrlen(array);
        // init stacks
        A.numbers = malloc((len + 1) * sizeof(int));
        B.numbers = malloc((len + 1) * sizeof(int));
        A.lenght = len;
        B.lenght = 0;
        moves = 0;
        ////////////////////////////////////////////////////////////
        i = 0;

        while (i < A.lenght)
        {
            A.numbers[i] = ft_atoi(array[i]);
            i++;
        }
        i = 0;
        ft_printf("arguments are:\n");
        while (i < A.lenght)
        {
            ft_printf("%d ", A.numbers[i++]);
        }
#if 0
        ft_printf("\n==============================\n");
        ft_printf("before moves\n");
        i = 0;
        ft_printf("A:\n");
        while (i < A.lenght)
        {
            ft_printf("%d ", A.numbers[i++]);
        }
        ft_printf("\nB:\n");
        i = 0;
        while (i < B.lenght)
        {
            ft_printf("%d ", B.numbers[i++]);
        }
        ft_printf("\n==============================\n");
        rotate(&A);
        rotate(&A);
        rotate(&A);
        push(&A, &B, len);
        push(&A, &B, len);


        ft_printf("after moves\n");
        i = 0;
        ft_printf("A:\n");
        while (i < A.lenght)
        {
            ft_printf("%d ", A.numbers[i++]);
        }
        ft_printf("\nB:\n");
        i = 0;
        while (i < B.lenght)
        {
            ft_printf("%d ", B.numbers[i++]);
        }
        exit(0);
#endif

        // execute moves
        close(fd[1]);
        wait(NULL); // wait for child process
        ft_printf("\nmoves are:\n");
        char *output;
        output = readline(fd[0]);
        while (output)
        {
            ft_printf("%s ", output);
            !ft_strcmp(output, "sa") && swap(&A) && moves++;
            !ft_strcmp(output, "sb") && swap(&B) && moves++;
            !ft_strcmp(output, "ra") && rotate(&A) && moves++;
            !ft_strcmp(output, "rb") && rotate(&B) && moves++;
            !ft_strcmp(output, "rra") && reverse_rotate(&A) && moves++;
            !ft_strcmp(output, "rrb") && reverse_rotate(&B) && moves++;
            !ft_strcmp(output, "ss") && swap(&A) && swap(&B) && moves++;
            !ft_strcmp(output, "rrr") && reverse_rotate(&A) && reverse_rotate(&B) && moves++;
            !ft_strcmp(output, "rr") && rotate(&A) && rotate(&B) && moves++;
            !ft_strcmp(output, "pa") && push(&B, &A, len) && moves++;
            !ft_strcmp(output, "pb") && push(&A, &B, len) && moves++;
            printstacks(&A, &B, moves);
            output = readline(fd[0]);
        }
        ft_printf("\n\nnumbers after sorting:\n");
        i = 0;
        while (i < A.lenght)
        {
            printf("%6d ", A.numbers[i++]);
            if (i % 15 == 0) // (j % (len / 8) == 0)
                printf("|\n");
        }
        if(is_sorted(&A))
            printf("\n\nnumbers are sorted\n");
        printf("\nyou did %d move\033[0;37m\n", moves);
    }
    else
    {
        ft_printf("\033[0;31mprogram failed");
        exit(-1);
    }
}
