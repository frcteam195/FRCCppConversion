#pragma once
/**
 * PURPOSE:
 *
 *  Polynomial Regression aims to fit a non-linear relationship to a set of
 *  points. It approximates this by solving a series of linear equations using 
 *  a least-squares approach.
 *
 *  We can model the expected value y as an nth degree polynomial, yielding
 *  the general polynomial regression model:
 *
 *  y = a0 + a1 * x + a2 * x^2 + ... + an * x^n
 *
 * LICENSE:
 *
 * MIT License
 * 
 * Copyright (c) 2020 Chris Engelsma
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * https://gist.github.com/chrisengelsma/108f7ab0a746323beaaf7d6634cf4add
 * @author Chris Engelsma
 */

#include <vector>
#include <stdlib.h>
#include <cmath>
#include <stdexcept>

template <class TYPE>
class PolynomialRegression
{
public:
    PolynomialRegression();
    virtual ~PolynomialRegression(){};

    bool fitIt(
        const std::vector<TYPE> &x,
        const std::vector<TYPE> &y,
        const int &order,
        std::vector<TYPE> &coeffs);
};
