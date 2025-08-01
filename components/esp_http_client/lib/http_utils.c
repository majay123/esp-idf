/*
 * SPDX-FileCopyrightText: 2015-2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "esp_log.h"
#include "esp_check.h"
#include "http_utils.h"

#ifndef mem_check
#define mem_check(x) assert(x)
#endif

static const char *TAG = "http_utils";

char *http_utils_join_string(const char *first_str, size_t len_first, const char *second_str, size_t len_second)
{
    size_t first_str_len = len_first > 0 ? len_first : strlen(first_str);
    size_t second_str_len = len_second > 0 ? len_second : strlen(second_str);
    char *ret = NULL;
    if (first_str_len + second_str_len > 0) {
        ret = calloc(1, first_str_len + second_str_len + 1);
        ESP_RETURN_ON_FALSE(ret, NULL, TAG, "Memory exhausted");
        memcpy(ret, first_str, first_str_len);
        memcpy(ret + first_str_len, second_str, second_str_len);
    }
    return ret;
}

char *http_utils_assign_string(char **str, const char *new_str, int len)
{
    int l = len;
    if (new_str == NULL) {
        return NULL;
    }
    char *old_str = *str;
    if (l < 0) {
        l = strlen(new_str);
    }
    if (old_str) {
        // old_str should not be reallocated directly, as in case of memory exhaustion,
        // it will be lost and we will not be able to free it.
        char *tmp = realloc(old_str, l + 1);
        if (tmp == NULL) {
            free(old_str);
            old_str = NULL;
            ESP_RETURN_ON_FALSE(old_str, NULL, TAG, "Memory exhausted");
        }
        old_str = tmp;
        old_str[l] = 0; // Ensure the new string is null-terminated
    } else {
        old_str = calloc(1, l + 1);
        ESP_RETURN_ON_FALSE(old_str, NULL, TAG, "Memory exhausted");
    }
    memcpy(old_str, new_str, l);
    *str = old_str;
    return old_str;
}

char *http_utils_append_string(char **str, const char *new_str, int len)
{
    int l = len;
    int old_len = 0;
    char *old_str = *str;
    if (new_str != NULL) {
        if (l < 0) {
            l = strlen(new_str);
        }
        if (old_str) {
            old_len = strlen(old_str);
            // old_str should not be reallocated directly, as in case of memory exhaustion,
            // it will be lost and we will not be able to free it.
            char *tmp = realloc(old_str, old_len + l + 1);
            if (tmp == NULL) {
                free(old_str);
                old_str = NULL;
                ESP_RETURN_ON_FALSE(old_str, NULL, TAG, "Memory exhausted");
            }
            old_str = tmp;
            // Ensure the new string is null-terminated
            old_str[old_len + l] = 0;
        } else {
            old_str = calloc(1, l + 1);
            ESP_RETURN_ON_FALSE(old_str, NULL, TAG, "Memory exhausted");
        }
        memcpy(old_str + old_len, new_str, l);
        *str = old_str;
    }
    return old_str;
}

void http_utils_trim_whitespace(char **str)
{
    char *end, *start;
    if (str == NULL) {
        return;
    }
    start = *str;
    if (start == NULL) {
        return;
    }
    // Trim leading space
    while (isspace((unsigned char)*start)) start ++;

    if (*start == 0) {  // All spaces?
        **str = 0;
        return;
    }

    // Trim trailing space
    end = (char *)(start + strlen(start) - 1);
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    // Write new null terminator
    *(end + 1) = 0;
    memmove(*str, start, strlen(start) + 1);
}

esp_err_t http_utils_get_string_between(const char *str, const char *begin, const char *end, char **out)
{
    *out = NULL;
    char *found = strcasestr(str, begin);
    if (found) {
        found += strlen(begin);
        char *found_end = strcasestr(found, end);
        if (found_end) {
            *out = calloc(1, found_end - found + 1);
            ESP_RETURN_ON_FALSE(*out, ESP_ERR_NO_MEM, TAG, "Memory exhausted");
            memcpy(*out, found, found_end - found);
        }
    }
    return ESP_OK;
}

esp_err_t http_utils_get_string_after(const char *str, const char *begin, char **out)
{
    *out = NULL;
    char *found = strcasestr(str, begin);
    if (found) {
        found += strlen(begin);
        char *found_end = (char *)str + strlen(str);
        if (found_end) {
            *out = calloc(1, found_end - found + 1);
            ESP_RETURN_ON_FALSE(*out, ESP_ERR_NO_MEM, TAG, "Memory exhausted");
            memcpy(*out, found, found_end - found);
        }
    }
    return ESP_OK;
}

int http_utils_str_starts_with(const char *str, const char *start)
{
    int i;
    int match_str_len = strlen(str);
    int start_len = strlen(start);

    if (start_len > match_str_len) {
        return -1;
    }
    for (i = 0; i < start_len; i++) {
        if (tolower(str[i]) != tolower(start[i])) {
            return 1;
        }
    }
    return 0;
}
