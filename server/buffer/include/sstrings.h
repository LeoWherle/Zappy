/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** strings
*/

#pragma once

#include "buffer.h"
#include "vector.h"


typedef struct string_s {
    void *items;
    size_t nmemb;
    size_t capacity;
    size_t _unused;
    dtor_t _unused0;
    cpctor_t _unused1;
} string_t;


/***************************** STRING CONSTRUCTORS ***************************/

/**
 * @brief creates a new string_t object
 *
 * @return WUR* can be NULL if allocation failed
 */
WUR string_t *str_new(void);

/**
 * @brief creates a new string_t object from a cstring
 *
 * @param cstr the cstring to initialize the string_t object with
 * Must be a valid cstring (ending with '\0')
 * @return WUR string_t* the newly created string_t object
 */
WUR string_t *str_from_cstr(const char *cstr);

void str_delete(string_t *str);

/**
 * @brief initializes a string_t object on the stack.
 * USE WITH CAUTION
 *
 * @param str the stack-allocated string_t object
 * @param cstr the cstring to initialize the string_t object with
 * Must be a valid cstring (ending with '\0')
 * Can be NULL or "" to initialize an empty string
 * @return WUR buf_error_t error code
 */
WUR buf_error_t str_init(string_t *str, const char *cstr);
/**
 * @brief Oposite of vec_init, frees the memory allocated for the vector's
 * items and sets the vector's items to NULL
 */
void str_reset(string_t *str);

/***************************** STRING ACCESSORS ******************************/

/**
 * @brief returns the character at the given index
 *
 * @param str the string to get the character from
 * @param index the index of the character to get
 * @return char the character at the given index or '\0' if the index is out
 * of bounds
 */
WUR char str_at(const string_t *str, size_t index);

/***************************** STRING MANIPULATION ***************************/

// THIS FUNCTION IS NOT SAFE, USE WITH CAUTION
WUR buf_error_t str_push_cstr(string_t *str, const char *cstr);
WUR buf_error_t str_push_str(string_t *str, const string_t *str_to_push);
WUR buf_error_t str_push_char(string_t *str, char c);
buf_error_t str_push_bytes(string_t *str, const void *bytes, size_t n);

void str_truncate(string_t *str, size_t new_size);

/**
 * @brief pops the last character of the string and returns it
 *
 * @param str the string to pop from
 * @return char the popped character or '\0' if the string is empty
 */
WUR char str_pop(string_t *str);

/**
 * @brief Deletes all the elements in the range `[start, end)`.
 */
WUR buf_error_t str_erase(string_t *str, size_t start, size_t end);

/**
 * @brief removes the character at the given index and returns it
 *
 * @param str the string to remove from
 * @param index the index of the character to remove
 * @return WUR char the removed character or '\0' if the index is out of bounds
 */
WUR char str_remove(string_t *str, size_t index);

/**
 * @brief inserts a character at the given index
 *
 * @param str the string to insert into
 * @param index the index to insert the character at
 * @param c the character to insert
 * @return WUR buf_error_t error code
 */
WUR buf_error_t str_insert(string_t *str, size_t index, char c);

/**
 * @brief Makes a copy of the bytes to insert.
 */
WUR buf_error_t str_insert_bytes(
    string_t *str, size_t index, const void *bytes, size_t nmemb);

/**
 * @brief Makes a copy of the cstr to insert.
 */
WUR buf_error_t str_insert_cstr(
    string_t *str, size_t index, const char *cstr);

/**
 * @brief Makes a copy of the string to insert.
 */
WUR buf_error_t str_insert_str(
    string_t *str, size_t index, const string_t *str_to_insert);

/**
 * @brief Retains only the elements that satisfy the predicate.
 * In other words, remove all characters `e` such that `predicate(e)` is false.
 * This method operates in-place, visiting each element only once, and
 * preserving the order of the elements.
 *
 * # Example
 * ```c
 * string_t *str = str_from_cstr("Hello, World!");
 * str_retain_if(str, isalpha);
 * // str is now "HelloWorld"
 * str_delete(str);
 * ```
 */
// TODO: implement this
// void str_retain_if(string_t *str, bool (*predicate)(char));

/***************************** STRING UTILITIES ******************************/

vector_t *str_to_vec(string_t *str);

/**
 * @brief Splits the string at the given index and returns the right part
 *
 * @param str the string to split
 * @param index the index to split at
 * @return WUR string_t* the right part of the split as a new string_t object
 */
WUR string_t *str_split_off(string_t *str, size_t index);

void str_clear(string_t *str);

struct str_fn {
    string_t *(*new)(void);
    string_t *(*from_cstr)(const char *cstr);
    void (*delete)(string_t *str);
    buf_error_t (*init)(string_t *str, const char *cstr);
    void (*reset)(string_t *str);
    char (*at)(const string_t *str, size_t index);
    buf_error_t (*push_cstr)(string_t *str, const char *cstr);
    buf_error_t (*push_str)(string_t *str, const string_t *str_to_push);
    buf_error_t (*push_char)(string_t *str, char c);
    char (*pop)(string_t *str);
    buf_error_t (*erase)(string_t *str, size_t start, size_t end);
    char (*remove)(string_t *str, size_t index);
    buf_error_t (*insert)(string_t *str, size_t index, char c);
    buf_error_t (*insert_bytes)(
        string_t *str, size_t index, const void *bytes, size_t nmemb);
    buf_error_t (*insert_cstr)(string_t *str, size_t index, const char *cstr);
    buf_error_t (*insert_str)(
        string_t *str, size_t index, const string_t *str_to_insert);
    vector_t *(*as_vec)(string_t *str);
    string_t *(*split_off)(string_t *str, size_t index);
    void (*clear)(string_t *str);
};

extern const struct str_fn STR;
