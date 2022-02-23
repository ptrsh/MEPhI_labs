#include <stdio.h>
#include <malloc.h>
#include <math.h> // используется для возведения в степень
#include <readline/readline.h>

typedef struct Line {
    int size;
    int *data;
} Line;

typedef struct Matrix {
    int size;
    Line *data;
} Matrix;

void init_matrix(Matrix *matr, int m);

void free_matrix(Matrix *matr, int m);

void print_matrix(Matrix *matr, int m);

void add_to_matrix(Matrix *matr, int *line, int position);

size_t len(char *s);

int str_to_integer(char *s);

int read_integer();

int find_nearest_fibonacci(int n);

int* find_representation(int num);

int main() {
    
    printf("--Ввод m--\n");
    int m = read_integer();
    printf("Всего чисел: %d\n\n", m);

    Matrix matr;
    init_matrix(&matr, m);
    
    for (int i = 0; i < m; ++i) {
        printf("--Ввод числа #%d--\n", i + 1);
        int num = read_integer();
        add_to_matrix(&matr, find_representation(num), i);
    }

    print_matrix(&matr, m);
    free_matrix(&matr, m);

}

void init_matrix(Matrix *matr, int m) {
    matr->size = m;
    matr->data = (Line *)malloc(m * sizeof(Line));
    for (int i = 0; i < m; ++i) {
        matr->data[i].data = (int*)malloc(sizeof(int));
        matr->data[i].size = 1;
    }
}

void free_matrix(Matrix *matr, int m){
    for (int i = 0; i < m; ++i)
        free(matr->data[i].data);
    free(matr->data);
}

void print_matrix(Matrix *matr, int m){
    printf("\nИтоговая матрица:\n");
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < matr->data[i].size; j++)
            printf("%d ", matr->data[i].data[j]);
        printf("\n");
    }
}

void add_to_matrix(Matrix *matr, int *line, int position) {
    /*
        Добавляет в матрицу строку (разложение числа) на заданную позицию
    */
    matr->data[position].size = line[0];
    for (int i = 1; i <= line[0]; ++i) {
        matr->data[position].data = (int*)realloc(matr->data[position].data, (i + 1) * sizeof(int));
        matr->data[position].data[i - 1] = line[i];
    }
    free(line);
}

size_t len(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; ++i)
        ;                      
    return i;
    free(s);
}

int str_to_integer(char *s) {
    /*
        преобразовывает введенные пользователем данные в число
        примечание: если введенная строка не корректна (не число), то 
        функция возвращает 0
    */
    int num = 0;
    int tmp = pow(10, len(s));
    if (s[0] == '0') {
        free(s);
        return 0;
    }   
    for (int i = 0; s[i] != '\0'; ++i) {
        if ('0' > s[i] | s[i] > '9') {
            free(s);
            return 0;
        } else {
            tmp /= 10;
            num += (s[i] - '0') * tmp;
        }
     }
    free(s);
    return num < 0 ? 0 : num; // при переполнении int возвращаем 0
}

int read_integer() {
    int possible_num;
    do {
        possible_num = str_to_integer(readline("[+] "));
        if (possible_num) 
            return possible_num;
        else
            printf("Вы ввели некорректное число. Попробуйте ещё раз!\n");
    } while (!possible_num);    
}

int find_nearest_fibonacci(int n){
    /*
        находит наибольшее число Фибоначчи, меньшее n
    */
    if (n == 0 | n == 1)
        return n;
    int num1 = 0;
    int ans = 1;
    int num2 = 1;
    while (num2 <= n) {
        num1 = ans;
        ans = num2;
        num2 = num1 + ans;
    }
    return ans;
}

int* find_representation(int num){
    /*
        раскладывает введенное пользователем число в виде суммы чисел Фибоначчи и
        возвращает массив, первым элементом которого является кол-во чисел из
        разложения, а элементы a[1]..a[a[0]+1] - само разложение
    */
    int *array = (int*)malloc(sizeof(int));
    int count = 0;
    array[0] = count;
    while (num!=0) {
        int fib = find_nearest_fibonacci(num);
        count += 1;
        array = (int*)realloc(array, (count + 1) * sizeof(int));
        array[count] = fib;
        array[0] += 1;
        num -= fib;
    }
    return array;

}