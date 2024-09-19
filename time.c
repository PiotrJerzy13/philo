/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwojnaro <pwojnaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:13:44 by pwojnaro          #+#    #+#             */
/*   Updated: 2024/09/19 17:31:38 by pwojnaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> 

int main()
{
	struct timeval start;
	struct timeval end;
    long start_ms;
	long end_ms;
    long elapsed;
	
    gettimeofday(&start, NULL);
    sleep(2);
    gettimeofday(&end, NULL);
    start_ms = start.tv_sec * 1000 + start.tv_usec / 1000;
    end_ms = end.tv_sec * 1000 + end.tv_usec / 1000;
    elapsed = end_ms - start_ms;
    printf("Elapsed time: %ld milliseconds\n", elapsed);
    return 0;
}

