#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2020/11/20 上午 11:59
# @Author : Li, Yun-Fang
# @File : homogeneous_polynomial_transform.py
# @Software: PyCharm

import numpy as np


train_data_num = 1000
test_data_num = 3000


def preprocess_data(filename, num, Q):
    data = np.genfromtxt(filename)
    X = data[:, :-1]
    original_X = X
    for i in range(2, Q + 1):
        X = np.c_[X, np.power(original_X, i)]
    X = np.c_[np.ones(num), X]
    Y = data[:, -1].reshape(num, 1)

    return X, Y


def cal_pseudo_inverse(X):
    X_t = np.transpose(X)
    X_tX = np.dot(X_t, X)
    X_tX_inverse = np.linalg.inv(X_tX)
    H = np.dot(X_tX_inverse, X_t)

    return H


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
    Q_19 = 3
    train_X, train_Y = preprocess_data('train.dat', train_data_num, Q_19)
    test_X, test_Y = preprocess_data('test.dat', test_data_num, Q_19)
    pseudo_inverse = cal_pseudo_inverse(train_X)
    w_lin = np.dot(pseudo_inverse, train_Y)  # linear_regression weight
    error_in = cal_zero_one_error(w_lin, train_X, train_Y, train_data_num)
    error_out = cal_zero_one_error(w_lin, test_X, test_Y, test_data_num)
    print("Answer for problem 19: {0}".format(abs(error_in - error_out)))

    Q_20 = 10
    train_X, train_Y = preprocess_data('train.dat', train_data_num, Q_20)
    test_X, test_Y = preprocess_data('test.dat', test_data_num, Q_20)
    pseudo_inverse = cal_pseudo_inverse(train_X)
    w_lin = np.dot(pseudo_inverse, train_Y)  # linear_regression weight
    error_in = cal_zero_one_error(w_lin, train_X, train_Y, train_data_num)
    error_out = cal_zero_one_error(w_lin, test_X, test_Y, test_data_num)
    print("Answer for problem 20: {0}".format(abs(error_in - error_out)))


if __name__ == '__main__':
    solve()
