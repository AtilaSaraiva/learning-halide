#include "Halide.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    Halide::Func gradient;
    Halide::Var x, y;
    Halide::Expr expr = x + y;

    gradient(x, y) = expr;

    Halide::Buffer<int32_t> output = gradient.realize({800,900});

    for (int j = 0; j < output.height(); j++){
        for (int i = 0; i < output.width(); i++){
            if (output(i, j) != i + j) {
                printf("Pixels %d and %d of the output should have the value %d,\nbut instead have %d",
                        i, j, output(i, j), i + j);
                return -1;
            };
        };
    };


    printf("Success!");
    return 0;
};
