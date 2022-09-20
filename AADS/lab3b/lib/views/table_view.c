#include "stdio.h"
#include "string.h"

#include "../other/keyspace1_helper.h"
#include "../other/item_helper.h"
#include "../other/readline.h"
#include "item_view.h"
#include "table_view.h"

Table *read_table_size() {
    printf("Инициализация таблицы:\n");
    int size1 = read_num("Вы ввели некорректный размер!", 0, 100000);
    int size2 = read_num("Вы ввели некорректный размер!", 0, 100000);
    return table_init(size1, size2);
}

Item *read_element() {
    char *info = get_str("Информация: ");
    char *key1 = get_str("Ключ1: ");
    char *key2 = get_str("Ключ2: ");
    return item_init(info, key1, key2);
}

void read_keys(char **key1, char **key2) {
    *key1 = get_str("Ключ1: ");
    *key2 = get_str("Ключ2: ");
}

void read_key(char **key) {
    *key = get_str("Ключ: ");
}

void table_print(Table *this) {
    printf("+---------------+\n");
    printf("|    Таблица    |\n");
    printf("+---------------+\n");
    KeySpace1 *keySpace1 = file_load_keyspace1(this->keySpace1);
    for (int i = 0; i < keySpace1->used; i++) {
        Item *item = file_load_item(keySpace1->items[i]);
        printf("| %-5s | %-5s | --- ", item->key1, item->key2);
        print_item(item);
        printf("+---------------+\n");
    }
    keyspace1_free(keySpace1);
}
