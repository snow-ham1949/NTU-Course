#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2020/11/16 下午 01:37
# @Author : Li, Yun-Fang
# @File : logistic_regression.py
# @Software: PyCharm

import numpy as np


data_num = 1000


def preprocess_data(filename):
    data = np.genfromtxt(filename)
    X = data[:, :-1]
    X = np.c_[np.ones(data_num), X]
    Y = data[:, -1].reshape(data_num, 1)

    return X, Y


def cal_pseudo_inverse(X):
    X_t = np.transpose(X)
    X_tX = np.dot(X_t, X)
    X_tX_inverse = np.linalg.inv(X_tX)
    H = np.dot(X_tX_inverse, X_t)

    return H


def sigmoid(s):
    return 1 / (1 + np.exp(-s))


def cal_cross_entropy_error(w, X, Y):
    error = 0.0

    for i in range(len(X)):
        error += np.log(1 + np.exp(-Y[i] * np.dot(X[i], w)))

    return error / data_num


def solve():
    train_X, train_Y = preprocess_data('train.dat')
    pseudo_inverse = cal_pseudo_inverse(train_X)
    w_lin = np.dot(pseudo_inverse, train_Y)  # linear_regression weight

    ERRORS_16, ERRORS_17, eta = [], [], 0.001

    for i in range(1000):  # repeat the experiment for 1000 times
        w_16 = np.zeros((len(train_X[0]), 1))
        w_17 = w_lin
        for iteration in range(500):
            # choose one example
            row_rand_array = np.arange(train_X.shape[0])
            np.random.shuffle(row_rand_array)
            x = train_X[row_rand_array[0:1]]
            y = train_Y[row_rand_array[0:1]]
            # update
            w_16 = w_16 + eta * y * np.transpose(sigmoid(-y * np.dot(x, w_16)) * x)
            w_17 = w_17 + eta * y * np.transpose(sigmoid(-y * np.dot(x, w_17)) * x)

        # calculate error
        error = cal_cross_entropy_error(w_16, train_X, train_Y)
        ERRORS_16.append(error)
        error = cal_cross_entropy_error(w_17, train_X, train_Y)
        ERRORS_17.append(error)

    print("Answer for problem 16: {0}".format(np.mean(ERRORS_16)))
    print("Answer for problem 17: {0}".format(np.mean(ERRORS_17)))


if __name__ == '__main__':
    solve()
