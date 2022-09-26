#include "Halide.h"
#include <halide_image_io.h>
#include <stdio.h>

using namespace Halide::Tools;

int main(int argc, char **argv)
{
    Halide::Buffer<uint8_t> input = load_image("images/square.png");

    Halide::Func laplacian;
    Halide::Var x, y;

    Halide::Func bounded_input = Halide::BoundaryConditions::repeat_edge(input);

    Halide::Expr Dxx = bounded_input(x+1, y) + bounded_input(x-1, y) - 2*bounded_input(x, y);
    Halide::Expr Dyy = bounded_input(x, y+1) + bounded_input(x, y-1) - 2*bounded_input(x, y);

    laplacian(x, y) = Dxx + Dyy;

    Halide::Buffer<uint8_t> output = laplacian.realize({input.width(), input.height()});

    save_image(output, "square_lapla.png");

    printf("Success!");
    return 0;
};
