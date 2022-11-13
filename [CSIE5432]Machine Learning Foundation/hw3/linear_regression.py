#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2020/11/14 上午 10:23
# @Author : Li, Yun-Fang
# @File : linear_regression.py
# @Software: PyCharm

import numpy as np


train_data_num = 1000
test_data_num = 3000


def preprocess_data(filename, num):
    data = np.genfromtxt(filename)
    X = data[:, :-1]
    X = np.c_[np.ones(num), X]
    Y = data[:, -1].reshape(num, 1)

    return X, Y


def cal_pseudo_inverse(X):
    X_t = np.transpose(X)
    X_tX = np.dot(X_t, X)
    X_tX_inverse = np.linalg.inv(X_tX)
    H = np.dot(X_tX_inverse, X_t)

    return H


def cal_square_error(w, X, Y):
    train_Y = np.dot(X, w)
    arr_error = Y - train_Y
    error = np.sum(arr_error ** 2) / train_data_num

    return error


def sign(s):
    if s > 0:
        return 1
    else:
        return -1


def cal_zero_one_error(w, X, Y, num):
    temp_Y = np.dot(X, w)
    error = 0
    for i in range(num):
        if sign(temp_Y[i][0]) != Y[i][0]:
            error += 1

    return error / num


def solve():
    train_X, train_Y = preprocess_data('train.dat', train_data_num)
    test_X, test_Y = preprocess_data('test.dat', test_data_num)
    pseudo_inverse = cal_pseudo_inverse(train_X)
    w_lin = np.dot(pseudo_inverse, train_Y)  # linear_regression weight
    squared_error_lin = cal_square_error(w_lin, train_X, train_Y)  # E_{in}^{sqr}(w_lin)
    print("Answer for problem 14: {0}".format(squared_error_lin))

    ITERS, eta = [], 0.001

    for i in range(1000):  # repeat the experiment for 1000 times
        w = np.zeros((len(train_X[0]), 1))
        iteration, squared_error = 0, 10000
        while squared_error >= 1.01 * squared_error_lin:
            # choose one example
            row_rand_array = np.arange(train_X.shape[0])
            np.random.shuffle(row_rand_array)
            x = train_X[row_rand_array[0:1]]
            y = train_Y[row_rand_array[0:1]]
            # update
            w = w + np.transpose(eta * 2 * np.dot((y - np.dot(x, w)), x))
            # calculate error
            squared_error = cal_square_error(w, train_X, train_Y)
            iteration += 1

        ITERS.append(iteration)
        # print("Case {0}: {1}".format(i + 1, iteration))

    print("Answer for problem 15: {0}".format(np.mean(ITERS)))

    error_in = cal_zero_one_error(w_lin, train_X, train_Y, train_data_num)
    error_out = cal_zero_one_error(w_lin, test_X, test_Y, test_data_num)
    print("Answer for problem 18: {0}".format(abs(error_in - error_out)))


if __name__ == '__main__':
    solve()
