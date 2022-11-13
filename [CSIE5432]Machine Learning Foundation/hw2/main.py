#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time : 2020/10/22 下午 09:58
# @Author : Li, Yun-Fang
# @File : main.py
# @Software: PyCharm

import numpy as np
import statistics


tau = 0.1
ITER = 10000
data_size = 200


def sign(x):
    if x >= 0.0:
        return 1
    else:
        return -1


def f(x):
    if np.random.rand() < (1 - tau):
        return sign(x)
    else:
        return -sign(x)


def h(x, s, theta):
    return s * sign(x - theta)


def train(THETA, S, X, Y):
    E_in = 10000000
    E_out = 0
    for theta in THETA:
        for s in S:
            error = 0
            for i in range(data_size):
                x, y = X[i], Y[i]
                if h(x, s, theta) != y:
                    error += 1
            if error / data_size < E_in:
                E_in = error / data_size
                E_out = (1 - 2 * tau) * (s * abs(theta) - s + 1) / 2 + tau

    return E_out - E_in


def main():
    RESULT = []
    for time in range(ITER):
        X = np.random.uniform(-1, 1, data_size)
        X.sort()
        Y = [f(x) for x in X]

        S = [-1, 1]
        THETA = [-1]
        for i in range(data_size - 1):
            if X[i] != X[i + 1]:
                THETA.append((X[i] + X[i + 1]) / 2.0)

        result = train(THETA, S, X, Y)

        print("Case {0}: {1}".format(time, result))

        RESULT.append(result)

    print("mean: {0}".format(statistics.mean(RESULT)))


if __name__ == '__main__':
    main()
