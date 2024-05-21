/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** macros
*/

#pragma once

/**
 * @brief A macro to get the pointer to the element at the given index
 */
#define VEC_AT(vec, index) ((vec)->items + (index) * (vec)->item_size)

#define VEC_LAST(vec) ((vec)->items + ((vec)->nmemb - 1) * (vec)->item_size)
/**
 * @brief A macro to get the number of elements left after the given index
 */
#define VEC_ELEM_LEFT(vec, indx) ((vec)->nmemb - (indx))
/**
 * @brief A macro to get the number of bytes left after the given index
 */
#define VEC_BYTES_LEFT(vec, indx) (VEC_ELEM_LEFT(vec, indx) * (vec)->item_size)

#define IS_SAME_TYPE(a, b)  __builtin_types_compatible_p(typeof(a), typeof(b))
#define IS_POINTER_OR_ARRAY(p)  (__builtin_classify_type(p) == 5)
#define DECAY(p)  (&*__builtin_choose_expr(IS_POINTER_OR_ARRAY(p), p, NULL))

#define IS_PTR(p)  IS_SAME_TYPE(p, DECAY(p))
// Usage: VEC_FOREACH(&vec, elem) { printf("%d\n", *elem); }
#define VEC_IS_END(v, e) (e < (__typeof__(e)) VEC_LAST(v))
#define VEC_IS_START(v, e) (e >= (__typeof__(e)) (v)->items - sizeof(*(e)))

#define COMPILATION_COND(cond)  (sizeof(char[1 - 2 * !(cond)]))

#define VEC_IS_IN_RANGE(e, v) (VEC_IS_START(v, e) && VEC_IS_END(v, e))
// stop compilation if the e is not a pointer
#define IS_VALIDPTR(e) COMPILATION_COND(IS_PTR(e))
#define VEC_VALID_PTR(e, v) IS_VALIDPTR(e) && VEC_IS_IN_RANGE(e, v)
/**
 * @example usage:
 * int *elem = VEC_INIT_ITER(&vec, elem);
 * VEC_FOREACH(&vec, elem) {
 *     printf("%d\n", *elem);
 *     if (VEC_IS_LAST(&vec, elem)) {
 *         printf("Last element\n");
 *     }
 * }
 */
#define VEC_INIT_ITER(v, e)  (v)->items - sizeof(*(e))
#define VEC_FOREACH(v, e) while (VEC_VALID_PTR(e, v) && (e++))
#define VEC_IS_LAST(v, e) (VEC_LAST(v) == (void *) e)
#define BUF_INDEX(v, e) ((e - (v)->items) / (v)->item_size)
