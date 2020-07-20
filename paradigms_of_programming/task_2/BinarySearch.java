package search;

import java.util.Random;

public class BinarySearch {
    /**
     * inv:     pivot >= arr[i] for all i >= right_border &&
     * pivot < arr[i] for all i <= left_border
     * <p>
     * n is size of array
     * <p>
     * pre:     n >= 1 && arr[i- 1] <= arr[i] {i = 1..n - 1} && arr[n] == -inf &&
     * left_border == -1 && right_border == n
     * post:    inv && right_border - left_border == 1 =>
     * right_border == 'i' {'i' - minimum index of array, that arr[i] <= pivot}
     */
    public static long iterativeBinSearach(long[] arr, long pivot, int left_border, int right_border) {
        int mid;
        //inv:     pivot >= arr[i] for all i >= right_border &&
        //         pivot < arr[i] for all i <= left_border
        //pre:     right_border == -1 $$ left_border == n {n = args.length - 1}
        //         && arr[left_border] > pivot >= arr[right_border]
        while (right_border - left_border > 1) {
            mid = (left_border + right_border) / 2;
            if (arr[mid] <= pivot) {
                //I && pivot >= arr[mid]
                //  && arr[mid] >= arr[i] for all i >= mid
                right_border = mid;
            } else {
                // I && pivot < arr[mid]
                //   && arr[mid] < arr[i] for all i <= mid
                left_border = mid;
            }
            // Inv
        }
        //post:   right_border - left_border == 1 && arr[left_border] > pivot >= arr[right_border] && arr[i]' = arr[i] for all i
        //     => min index of array, that arr[i] <= pivot, is right_border
        return right_border;
    }

    /**
     * inv:     pivot >= arr[i] for all i >= right_border &&
     * pivot < arr[i] for all i <= left_border
     * pre:     n >= 1 && arr[i- 1] <= arr[i] {i = 1..n - 1} && arr[n] == -inf &&
     * -1 <= left_border < right_border + 1 && 0 <= right_border <= arr.length
     * post:    inv && right_border - left_border == 1 =>
     * right_border == 'i' {'i' - minimum index of array, that arr[i] <= pivot}
     */
    public static long recursiveBinSearch(long[] arr, long pivot, int left_border, int right_border) {
        //inv:     pivot >= arr[i] for all i >= right_border &&
        //         pivot < arr[i] for all i <= left_border
        //pre:     -1 <= left_border < right_border + 1 && 0 <= right_border <= arr.length
        //         && arr[left_border] > pivot >= arr[right_border]
        if (right_border - left_border == 1)
            //post:   right_border - left_border == 1 && arr[left_border] > pivot >= arr[right_border]
            //     => min index of array, that arr[i] <= pivot, is right_border
            return right_border;
        //         I && left_border + right_border >= 0
        int mid = (left_border + right_border) / 2;
        //         I && mid >= 0
        if (arr[mid] <= pivot) {
            //I && pivot >= arr[mid]
            //  && arr[mid] >= arr[i] for all i >= mid
            return recursiveBinSearch(arr, pivot, left_border, mid);
        } else {
            // I && pivot < arr[mid]
            //   && arr[mid] < arr[i] for all i <= mid
            return recursiveBinSearch(arr, pivot, mid, right_border);
        }
    }

    public static void main(String[] args) {
        Random random = new Random();
        long key = Long.parseLong(args[0]);
        long[] list = new long[args.length - 1];

        for (int i = 1; i < args.length; i++) {
            list[i - 1] = Long.parseLong(args[i]);
        }

        if (random.nextBoolean()) {
            System.out.println(iterativeBinSearach(list, key, -1, args.length - 1));
        } else {
        System.out.println(recursiveBinSearch(list, key, -1, args.length - 1));
        }
    }
}
