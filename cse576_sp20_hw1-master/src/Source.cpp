
#include <string>
#include "image.h"

using namespace std;



int main(int argc, char** argv)
{
   
    Image im = load_image("C:/Users/24078/Desktop/576Cv/cse576_sp20_hw1-master/data/dog.jpg");
    Image gray = rgb_to_grayscale(im);
    Image g = load_image("C:/Users/24078/Desktop/576Cv/cse576_sp20_hw1-master/output/pixel_modifying_output");
    TEST(same_image(gray, g));
   

    return 0;
}