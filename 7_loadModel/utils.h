#include <iostream>
#include<stb/stb_image_write.h>

// 画像保存
void imageSave(unsigned char* image_data, unsigned int width, unsigned height) {
	// 左右反転
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width / 2; x++) {
			int left_index = (y * width + x) * 3;
			int right_index = (y * width + (width - x - 1)) * 3;
			unsigned char r = image_data[left_index + 0];
			unsigned char g = image_data[left_index + 1];
			unsigned char b = image_data[left_index + 2];
			image_data[left_index + 0] = image_data[right_index + 0];
			image_data[left_index + 1] = image_data[right_index + 1];
			image_data[left_index + 2] = image_data[right_index + 2];
			image_data[right_index + 0] = r;
			image_data[right_index + 1] = g;
			image_data[right_index + 2] = b;
		}
	}
	// 180度回転
	unsigned char* rotated_image_data = (unsigned char*)malloc(width * height * 3);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = (y * width + x) * 3;
			int rotated_index = ((height - y - 1) * width + (width - x - 1)) * 3;
			rotated_image_data[rotated_index + 0] = image_data[index + 0];
			rotated_image_data[rotated_index + 1] = image_data[index + 1];
			rotated_image_data[rotated_index + 2] = image_data[index + 2];
		}
	}
	stbi_write_png("output.png", width, height, 3, rotated_image_data, width * 3);
	std::cout << "Save Window -*- output.png -*-" << std::endl;
	free(rotated_image_data);
}
