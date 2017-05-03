/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 01:44:29 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/04/26 02:09:35 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

static int	partition(int arr[], int min, int max)
{
	int i;
	int j;
	int pivot;

	pivot = arr[max];
	i = min - 1;
	j = min;
	while (j < max)
	{
		if (arr[j] <= pivot)
		{
			i++;
			ft_swap(&arr[i], &arr[j], sizeof(arr[i]));
		}
		++j;
	}
	ft_swap(&arr[i + 1], &arr[max], sizeof(arr[i + 1]));
	return (i + 1);
}

void		ft_qsort(int arr[], int min, int max)
{
	if (min < max)
	{
		int pivot;

		pivot = partition(arr, min, max);
		ft_qsort(arr, min, pivot - 1);
		ft_qsort(arr, pivot + 1, max);
	}
}

void printarray(int arr[], int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_printf("%d ",arr[i]);
		i++;
	}
}

int main(void)
{
	int arr[] = {5, 1, 10, 6, 8, 15, 21, 100, 4, 15};
	int size = sizeof(arr)/sizeof(arr[0]);
	ft_qsort(arr, 0, size - 1);
	printarray(arr, size);
	ft_putchar('\n');
}
