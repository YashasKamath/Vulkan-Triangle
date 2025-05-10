#include "VulkanTriangle.h"

int main() {
	VulkanTriangle triangle;
	try {
		triangle.run();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}