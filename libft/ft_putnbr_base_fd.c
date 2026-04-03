/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:13:09 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/14 10:17:15 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#
#include <stddef.h>
#include <stdint.h>

void ft_putnbr_base_fd(size_t n, int radix, int fd)
{
    const char base[] = "0123456789abcdef";

    /* length of the number... */
    size_t n_l = 0;
    for (uint64_t tmp = n; tmp != 0; tmp /= radix) {
        n_l++;
    }

    /* append characters to array... */
    char buffer[64] = { 0 };
    for (size_t i = 0; n; i++, n /= radix) {
        buffer[i] = base[n % radix];
    }

    /* reverse the array... */
    for (size_t i = 0; i < n_l / 2; i++) {
        char tmp = buffer[i];
        buffer[i] = buffer[n_l - 1 - i];
        buffer[n_l - 1 - i] = tmp;
    }

    ft_putstr_fd(buffer, fd);
}
