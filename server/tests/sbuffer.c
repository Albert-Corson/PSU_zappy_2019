/*
** EPITECH PROJECT, 2020
** buffer
** File description:
** sbuffer
*/

#include <criterion/criterion.h>
#include <string.h>

#include <sbuffer/sbuffer.h>

Test(sbuffer, sbuffer_init)
{
    sbuffer_t buf;
    char *it = (char *)&buf;

    sbuffer_init(NULL);
    sbuffer_init(&buf);
    for (size_t i = 0; i < sizeof(buf); ++i) {
        cr_assert_eq(*it, 0);
        ++it;
    }
}

Test(sbuffer, sbuffer_write)
{
    sbuffer_t buf;
    char str1[] = "Hello ";
    char str2[] = "world!";

    sbuffer_init(&buf);
    cr_assert_eq(sbuffer_write(NULL, str1), false);
    cr_assert_eq(sbuffer_write(&buf, NULL), false);
    cr_assert_eq(sbuffer_write(NULL, NULL), false);
    cr_assert_eq(sbuffer_write(&buf, str1), true);
    cr_assert_eq(sbuffer_write(&buf, str2), true);
    cr_assert_str_eq(buf.buffer, "Hello world!");
    cr_assert_eq(buf.size, 13);
    sbuffer_destroy(&buf);
}

Test(sbuffer, sbuffer_clear)
{
    sbuffer_t buf;

    sbuffer_clear(NULL);
    sbuffer_init(&buf);
    sbuffer_write(&buf, "something");
    sbuffer_clear(&buf);
    cr_assert_eq(buf.size, 0);
    sbuffer_destroy(&buf);
}

Test(sbuffer, sbuffer_destroy)
{
    sbuffer_t buf;

    sbuffer_destroy(NULL);
    sbuffer_init(&buf);
    sbuffer_write(&buf, "something");
    sbuffer_destroy(&buf);
    cr_assert_eq(buf.buffer, NULL);
    cr_assert_eq(buf.size, 0);
}

Test(sbuffer, sbuffer_printf)
{
    sbuffer_t buf;

    sbuffer_init(&buf);
    cr_assert_eq(sbuffer_printf(NULL, "Hello"), false);
    cr_assert_eq(sbuffer_printf(&buf, NULL), false);
    cr_assert_eq(sbuffer_printf(NULL, NULL), false);
    cr_assert_eq(sbuffer_printf(&buf, "Hello x%d", 10), true);
    cr_assert_str_eq(buf.buffer, "Hello x10");
    cr_assert_eq(buf.size, 10);
    cr_assert_eq(sbuffer_printf(&buf, " %s", "world!"), true);
    cr_assert_str_eq(buf.buffer, "Hello x10 world!");
    cr_assert_eq(buf.size, 17);
    sbuffer_destroy(&buf);
}
