/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cvecfer
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "vector/macros.h"
#include "buffer.h"

#define VEC_INIT_CAPACITY 8
#define VEC_GROWTH_FACTOR 2

#ifndef WUR
    #define WUR __attribute__((warn_unused_result))
#endif

/**
 * @brief The destructor takes a pointer to an element but SHOULD NOT free the
 * pointer itself. It should only free the memory allocated for the element.
 */
typedef void (*dtor_t)(void *);
/**
 * @brief The copy constructor takes a pointer to an element and a pointer to
 * another element and copies the content of the second element into the first
 */
typedef void (*cpctor_t)(void *, const void *);

/**
 * @brief A vector struct
 *
 * @param items the data of the vector
 * @param item_size the size of each element in the vector
 * @param nmemb the number of elements in the vector
 * @param capacity the capacity of the vector (the maximum number of elements)
 * (changes dynamically)
 * @param dtor the destructor function for the elements in the vector
 * @param cpctor the copy constructor function for the elements in the vector
 */
typedef struct vector_s {
    void *items;
    size_t nmemb;
    size_t capacity;
    size_t item_size;
    dtor_t dtor;
    cpctor_t cpctor;
} vector_t;

typedef void *(*map_fn_t)(const void *);
typedef void *(*map_fn_arg_t)(const void *, void *);
typedef bool (*filter_fn_t)(const void *);
typedef void (*for_fn_t)(void *);
typedef void (*for_fn_arg_t)(void *, void *);
typedef bool (*vec_pred_t)(void *);

/**
 * @brief creates a new vector with a given element size
 * @param dtor can be NULL if no destructor is needed
 */
WUR vector_t *vec_new(size_t elem_size, dtor_t, cpctor_t);
void vec_delete(vector_t *vec);

/**
 * @brief preallocates memory for the vector, reserving space for at least
 * `additional` elements
 * @return Sets the error code to BUF_ALLOC if the allocation fails
 */
WUR buf_error_t vec_reserve(vector_t *vec, size_t additional);

/**
 * @brief Initializes a vector with a given element size, the destructor and
 * the copy constructor
 *
 * @param vec the vector to initialize (should be allocated, (heap or stack))
 * and not have been initialized before
 * @param elem_size the size of each element in the vector
 * @param dtor the destructor function for the elements in the vector
 * @param cpctor the copy constructor function for the elements in the vector
 * @return returns BUF_OK if the initialization is successful
 */
WUR buf_error_t vec_init(vector_t *vec, size_t elem_size, dtor_t, cpctor_t);
/**
 * @brief Oposite of vec_init, frees the memory allocated for the vector's
 * items and sets the vector's items to NULL
 */
void vec_reset(vector_t *vec);

/**
 * @brief intialize a vector with preallocated memory of size * elem_size
 * @param dtor can be NULL if no destructor is needed
 */
WUR vector_t *vec_with_capacity(
    size_t size, size_t elem_size, dtor_t, cpctor_t);

/**
 * @brief Removes an element from the vector and returns it. Places the last
 * element in the vector in the position of the removed element. Use vec_remove
 * if you want to keep the order of the elements.
 * @return The element is not deallocated, so the caller is responsible for
 * freeing it. (It is reallocated)
 */
WUR void *vec_swap_remove(vector_t *vec, size_t index);

/**
 * @brief Inserts an element at position `index` within the vector, shifting
 * all elements after it to the right.
 * The element is copied into the vector, so the original can be safely
 * deallocated after the call if necessary.
 * @return Sets the error code to BUF_INDEX if the index is out of bounds
 */
WUR buf_error_t vec_insert(vector_t *vec, const void *elem, size_t index);

/**
 * @brief Inserts `nmemb` elements at position `index` within the vector,
 * shifting all elements after it to the right.
 * The elements are copied into the vector, so the original can be safely
 * deallocated after the call if necessary.
 * @note Doesn't handle copy constructors
 * @return Sets the error code to BUF_INDEX if the index is out of bounds
 */
WUR buf_error_t vec_insert_bytes(vector_t *vec, const void *buf, size_t nmemb,
    size_t index);

/**
 * @brief Removes an element at position `index` within the vector, shifting
 * all elements after it to the left.
 * The element is not deallocated, so the caller is responsible for freeing it.
 */
WUR void *vec_remove(vector_t *vec, size_t index);

/**
 * @brief Deletes the element at position `index` within the vector.
 * The element is deallocated using the destructor function.
 */
WUR buf_error_t vec_delete_at(vector_t *vec, size_t index);

/**
 * @brief Deletes all the elements in the range `[start, end)`.
 */
WUR buf_error_t vec_erase(vector_t *vec, size_t start, size_t end);

/**
 * @brief Removes all elements from the vector for which the predicate returns
 * `true`.
 * This method operates in place, visiting each element exactly once in the
 * original order, and preserves the order of the remaining elements.
 */
void vec_remove_if(vector_t *vec, bool (*predicate)(void *));

/**
 * @brief Retains only the elements specified by the predicate.
 * In other words, remove all elements `e` for which `f(&e)` returns `false`.
 * This method operates in place, visiting each element exactly once in the
 * original order, and preserves the order of the retained elements.
 *
 * # Example
 * ```c
 * bool is_even(const void *elem) {
 *     return *(int *)elem % 2 == 0;
 * }
 *
 * int main() {
 *     vector_t *vec = vec_new(sizeof(int), NULL; NULL);
 *     for (int i = 0; i < 10; i++) {
 *         vec_push(vec, &i);
 *     }
 *     vec_retain_if(vec, is_even);
 *     for (size_t i = 0; i < vec_size(vec); i++) {
 *         printf("%d\n", *(int *)vec_get(vec, i));
 *     }
 *     vec_delete(vec);
 * }
 */
void vec_retain_if(vector_t *vec, bool (*f)(const void *));

/**
 * @brief Appends an element to the end of the vector.
 * The element is copied into the vector, so the original can be safely
 * deallocated after the call if necessary.
 */
WUR buf_error_t vec_push(vector_t *vec, const void *elem);

/**
 * @brief Removes the last element from the vector.
 */
WUR buf_error_t vec_pop(vector_t *vec);

/**
 * @brief Moves all the elements of `src` into `dest` leaving `src` empty.
 * The elements are copied into `dest`, and the original elements from `src`
 * are deallocated.
 */
WUR buf_error_t vec_append(vector_t *dest, vector_t *src);

/**
 * @brief Moves all the elements of `dest` into `src`.
 * The elements are copied into `dest`, and the original elements from `src`
 * are deallocated.
 * @note This function is unsafe and should be used with caution.
 * because it doesn't check if the elements are of the same type (size).
 */
WUR buf_error_t vec_append_array(
    vector_t *dest, const void *buf, size_t nmemb, size_t item_size);

/**
 * @brief Clears the vector, deallocating all elements.
 */
void vec_clear(vector_t *vec);

WUR bool vec_is_empty(vector_t *vec);

/**
 * @brief Splits the collection into two at the given index.
 * Returns a newly allocated vector containing the elements in the range
 * `[at, len)`. After the call, the original vector will be left containing
 * the elements `[0, at)` with its previous capacity unchanged.
 * @return The newly allocated vector containing the elements in the range
 * `[at, len)`. Or NULL if the allocation fails (and the original vector is
 * unchanged).
 */
WUR vector_t *vec_split_off(vector_t *vec, size_t at);

/**
 * @brief Extend the vector by `n` clones of value.
 */
WUR buf_error_t vec_extend_with(vector_t *vec, const void *element, size_t n);

/**
 * @brief Removes consecutive repeated elements from the vector. Uses the
 * provided equality function to determine whether two elements are equal.
 */
void vec_dedup(vector_t *vec, bool (*eq)(const void *, const void *));

/**
 * @brief Duplicates the input vector. The elements are copied into the new
 * vector, so the original can be safely deallocated after the call if
 * necessary.
 */
WUR vector_t *vec_clone(const vector_t *vec);

/**
 * @brief The print function must use the printf format string to print the
 * element. For example, if the element is an int, the print function should be
 * `printf("%d", *(int)elem)`.
 * @param sep can be NULL and ", " will be used as the separator
 */
void vec_print(const vector_t *vec, void (*print)(const void *),
    const char *sep, const char *end);
/**
 * @brief Same as vec_print but uses a custom function to print the separators
 * This doesn't make printf a requirement within the print function
 */
void vec_display(const vector_t *vec, void (*print)(const void *),
    const char *sep, void (*)(const char *));

// Uses qsort to sort the vector
void vec_sort(vector_t *vec, int (*cmp)(const void *, const void *));

void vec_foreach(vector_t *vec, void (*f)(void *));
// Use a local struct to pass multiple arguments to the function if needed
void vec_foreach_arg(vector_t *vec, void (*f)(void *, void *), void *arg);

WUR void *vec_find(const vector_t *vec, bool (*fun)(const void *));
WUR void *vec_find_arg(
    const vector_t *vec, bool (*fun)(const void *, void *), void *arg);

WUR size_t vec_count(const vector_t *vec, bool (*fun)(const void *));
/**
 * @brief Returns a new vector containing the elements of the original vector
 * for which the predicate returns `true`.
 */
WUR vector_t *vec_filter(const vector_t *vec, filter_fn_t fun);

WUR vector_t *vec_map(const vector_t *vec, map_fn_t f);

// Use a local struct to pass multiple arguments to the function if needed
WUR vector_t *vec_map_arg(const vector_t *vec, map_fn_arg_t fun, void *arg);

// UNSAFE, use with caution (no bounds checking) and only if you know what you
// are doing
// Returns a pointer to the element at the given index or NULL if the index is
// out of bounds
WUR void *vec_at(const vector_t *vec, size_t index);

/**
 * @brief Returns the index of the element in the vector.
 * @param vec the vector to search in
 * @param elem the element to search for
 * @return WUR size_t the index of the element in the vector or -1 if the
 * element is not found
 */
WUR ssize_t vec_indexof(const vector_t *vec, const void *elem);
/******************** Builtin function for default types *********************/

WUR buf_error_t vec_push_int(vector_t *vec, int elem);
WUR buf_error_t vec_push_char(vector_t *vec, char elem);
WUR buf_error_t vec_push_float(vector_t *vec, float elem);
WUR buf_error_t vec_push_double(vector_t *vec, double elem);

WUR buf_error_t vec_insert_int(vector_t *vec, int elem, size_t index);
WUR buf_error_t vec_insert_char(vector_t *vec, char elem, size_t index);
WUR buf_error_t vec_insert_float(vector_t *vec, float elem, size_t index);
WUR buf_error_t vec_insert_double(vector_t *vec, double elem, size_t index);

WUR buf_error_t vec_pop_int(vector_t *vec);
WUR buf_error_t vec_pop_char(vector_t *vec);
WUR buf_error_t vec_pop_float(vector_t *vec);
WUR buf_error_t vec_pop_double(vector_t *vec);

WUR int vec_remove_int(vector_t *vec, size_t index);
WUR char vec_remove_char(vector_t *vec, size_t index);
WUR float vec_remove_float(vector_t *vec, size_t index);
WUR double vec_remove_double(vector_t *vec, size_t index);

WUR int vec_swap_remove_int(vector_t *vec, size_t index);
WUR char vec_swap_remove_char(vector_t *vec, size_t index);
WUR float vec_swap_remove_float(vector_t *vec, size_t index);
WUR double vec_swap_remove_double(vector_t *vec, size_t index);

WUR int *vec_at_int(const vector_t *vec, size_t index);
WUR char *vec_at_char(const vector_t *vec, size_t index);
WUR float *vec_at_float(const vector_t *vec, size_t index);
WUR double *vec_at_double(const vector_t *vec, size_t index);

/******************** Comparision function for default *********************/

void vec_sort_int(vector_t *vec);
void vec_sort_char(vector_t *vec);
void vec_sort_float(vector_t *vec);
void vec_sort_double(vector_t *vec);

/******************** Print function for default types *********************/

void vec_print_int(const vector_t *vec);
void vec_print_char(const vector_t *vec);
void vec_print_float(const vector_t *vec);
void vec_print_double(const vector_t *vec);

/******************** Methods for functions *********************/

struct vec_fn {
    vector_t *(*new)(size_t elem_size, dtor_t, cpctor_t);
    void (*delete)(vector_t *vec);
    buf_error_t (*reserve)(vector_t *vec, size_t additional);
    buf_error_t (*init)(vector_t *vec, size_t elem_size, dtor_t, cpctor_t);
    void (*reset)(vector_t *vec);
    vector_t *(*with_capacity)(
        size_t size, size_t elem_size, dtor_t, cpctor_t);
    void *(*swap_remove)(vector_t *vec, size_t index);
    buf_error_t (*insert)(vector_t *vec, const void *elem, size_t index);
    void *(*remove)(vector_t *vec, size_t index);
    buf_error_t (*delete_at)(vector_t *vec, size_t index);
    buf_error_t (*erase)(vector_t *vec, size_t start, size_t end);
    void (*remove_if)(vector_t *vec, bool (*predicate)(void *));
    void (*retain_if)(vector_t *vec, bool (*f)(const void *));
    buf_error_t (*push)(vector_t *vec, const void *elem);
    buf_error_t (*pop)(vector_t *vec);
    buf_error_t (*append)(vector_t *dest, vector_t *src);
    buf_error_t (*append_array)(
        vector_t *dest, const void *buf, size_t nmemb, size_t item_size);
    void (*clear)(vector_t *vec);
    bool (*is_empty)(vector_t *vec);
    vector_t *(*split_off)(vector_t *vec, size_t at);
    buf_error_t (*extend_with)(vector_t *vec, const void *element, size_t n);
    void (*dedup)(vector_t *vec, bool (*eq)(const void *, const void *));
    vector_t *(*clone)(const vector_t *vec);
    void (*print)(const vector_t *vec, void (*print)(const void *),
        const char *sep, const char *end);
    void (*display)(const vector_t *vec, void (*print)(const void *),
        const char *sep, void (*)(const char *));
    void (*sort)(vector_t *vec, int (*cmp)(const void *, const void *));
    void (*foreach)(vector_t *vec, void (*f)(void *));
    void (*foreach_arg)(vector_t *vec, void (*f)(void *, void *), void *arg);
    void *(*find)(const vector_t *vec, bool (*fun)(const void *));
    void *(*find_arg)(
        const vector_t *vec, bool (*fun)(const void *, void *), void *arg);
    size_t (*count)(const vector_t *vec, bool (*fun)(const void *));
    vector_t *(*filter)(const vector_t *vec, filter_fn_t fun);
    vector_t *(*map)(const vector_t *vec, map_fn_t f);
    vector_t *(*map_arg)(const vector_t *vec, map_fn_arg_t fun, void *arg);
    void *(*at)(const vector_t *vec, size_t index);
    ssize_t (*indexof)(const vector_t *vec, const void *elem);
};

extern const struct vec_fn VECTOR;
