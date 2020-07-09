#include "../image.h"
#include "../utils.h"

#include <string>

using namespace std;

int main(int argc, char** argv)
{
    // Image manipulation for fun testing.

    Image im2 = load_image("data/dog.jpg");
    for (int i = 0; i < im2.w; i++)
        for (int j = 0; j < im2.h; j++)
            im2(i, j, 0) = 0;
    im2.save_image("output/pixel_modifying_output");

    // Running example tests

    run_tests();

    return 0;
}